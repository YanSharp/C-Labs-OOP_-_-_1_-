#include "panel.h"

Panel::Panel(){
    logical_drives();
}

void Panel::logical_drives(){    
    current_directory = "Disks";
    cursor = 0;
    start_index = 0;
    folders_to_display.clear();
    files_to_display.clear();
    content.clear();

    DWORD dir = GetLogicalDrives();
    string temp;
    for(int i = 0; i < (sizeof(DWORD)*8); i++){
        if(dir & 1<<i){
            folders_to_display.push_back(folder());
            temp = static_cast<char>(i + 65);
            folders_to_display.back().name = (temp + ":" + "\0");
            content.push_back(container());
            content.back().name = folders_to_display.back().name;
            content.back().size = "";
            content.back().time = "";
        }
    }
}

void Panel::create_dir(string name){
    _SECURITY_ATTRIBUTES security;
    security.nLength = sizeof(SECURITY_ATTRIBUTES);
    security.lpSecurityDescriptor = NULL;
    security.bInheritHandle = TRUE;
    string path = current_directory + name;
    if (path.length() > (MAX_PATH - 3)){
        cout<<"Directory path is too long.\n";
        return;
    }
    if(current_directory=="Disks"){
        MessageBox(NULL, "You can't create folders here!",TEXT("Create directory"), MB_ICONWARNING|MB_OK);
        return;
    }
    if(!CreateDirectory(path.c_str(), &security)){
        MessageBox(NULL, "Not enough rihgts!",TEXT("Create directory") ,MB_ICONINFORMATION|MB_OK);
        return;
    }
    change_dir(name);
}

void Panel::change_dir(string path){
    if (path.length() > (MAX_PATH - 3)){
        MessageBox(NULL, "Directory path is too long!",TEXT("Change directory"), MB_ICONWARNING|MB_OK);
        return;
    }
    string dir = current_directory=="Disks"?"":current_directory;
    if(path != ".."){
        path += "\\";
        dir+=path;
    }
    else{
        std::size_t found = dir.find_last_of("\\");
        dir = dir.substr(0, found);
        found = dir.find_last_of("\\");
        dir = dir.substr(0, found + 1); 
    } 
    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;  
    dir+="*";

    hFind = FindFirstFileA(dir.c_str(), &ffd);
    if (INVALID_HANDLE_VALUE == hFind){
       MessageBox(NULL, "Ooops! Directory has some problem",TEXT("Change directory"), MB_ICONWARNING|MB_OK);
      return ;
    } 

    //меняем значение  current_directory после успешного FindFirstFileA(...)
    current_directory=dir.substr(0,dir.size()-1);
    
    cursor=0;
    start_index=0;
    folders_to_display.clear();
    files_to_display.clear();
    content.clear();
    while (FindNextFile(hFind, &ffd) != 0){
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
            folders_to_display.push_back(folder());
            folders_to_display.back().name = ffd.cFileName;
            folders_to_display.back().time.LowPart = ffd.ftCreationTime.dwLowDateTime;
            folders_to_display.back().time.HighPart = ffd.ftCreationTime.dwHighDateTime;
        }
        else{
            files_to_display.push_back(file());
            files_to_display.back().name = ffd.cFileName;
            files_to_display.back().size.LowPart = ffd.nFileSizeLow;
            files_to_display.back().size.HighPart = ffd.nFileSizeHigh;
            files_to_display.back().time = ffd.ftLastWriteTime;
        }
    }
    FindClose(hFind);    
    get_content();
}

void Panel::del(){
    if(is_current_Directory()){
        if(current_directory=="Disks")
            return;
        else
            delete_dir();
    }
    else
        delete_file();
}

void Panel::delete_file(){
    int index_file = this->cursor - this->folders_to_display.size();
    string file_name = this->files_to_display[index_file].name;
    string message("Delete "+file_name +"\nAre you shure ? ");
    int result = MessageBox( NULL,TEXT(message.c_str()),TEXT("Delete file"),MB_ICONQUESTION |MB_YESNO);
    if( result==IDNO)   
        return;
    else if(result==IDYES){
       BOOL fSuccess = FALSE;
       string full_path (current_directory+'\\'+file_name);
       fSuccess= DeleteFile(TEXT(full_path.c_str()));
       if (!fSuccess){
            message.assign("Can not to delete "+file_name);
            MessageBox( NULL,TEXT(message.c_str()),TEXT("Delete file"),MB_ICONWARNING |MB_OK);
        }
        else{
            message.assign(file_name+" file was deleted.");
            MessageBox( NULL,TEXT(message.c_str()),TEXT("Delete file"),MB_ICONINFORMATION |MB_OK);
            files_to_display.erase(files_to_display.begin()+index_file);
            content.erase(content.begin()+cursor);
            cursor--;
        }
    }

}

void Panel::delete_dir(){
    string dir_name = this->folders_to_display[cursor].name;
    string message("Delete "+dir_name +"\nAre you shure ? ");
    int result = MessageBox( NULL,TEXT(message.c_str()),TEXT("Delete directory"),MB_ICONQUESTION |MB_YESNO);
    if(result == IDNO)
        return;
    else if(result == IDYES){
        dir_name.resize(dir_name.length()+2);
        string dir_path(current_directory+'\\'+dir_name);   
        SHFILEOPSTRUCT shfo = {
            NULL,
            FO_DELETE,
            dir_path.c_str(),
            NULL,
            FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION,
            FALSE,
            NULL,
            NULL };

        bool fSuccess=(SHFileOperation(&shfo) == 0);        
        if (!fSuccess){
            message.assign("Can not to delete "+dir_name);
            MessageBox( NULL,TEXT(message.c_str()),TEXT("Delete directory"),MB_ICONWARNING |MB_OK);
        }
        else{
            message.assign(dir_name+" directory was deleted.");
            MessageBox( NULL,TEXT(message.c_str()),TEXT("Delete directory"),MB_ICONINFORMATION |MB_OK);
            folders_to_display.erase(folders_to_display.begin()+cursor);
            content.erase(content.begin()+cursor);
            cursor--;
        }
    }
}

void Panel::copy(string fromPath, string name){


    if(current_directory == "Disks" || fromPath == "Disks"){
        string message("You can't copy logica driver or to logical drivers!");
        MessageBox( NULL,TEXT(message.c_str()),TEXT("Copy"),MB_ICONWARNING |MB_OK);
        return;
    }
    name.resize(name.length()+2);
    string dir_path_from(fromPath+'\\'+name);   
    string dir_path_to(current_directory+'\\'+name);

    SHFILEOPSTRUCT shfo = {
        NULL,
        FO_COPY,
        dir_path_from.c_str(),
        dir_path_to.c_str(),
        FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION,
        FALSE,
        NULL,
        NULL };


    if(!SHFileOperation(&shfo)==0){
        string message("Can not copy "+ name);
        MessageBox( NULL,TEXT(message.c_str()),TEXT("Copy"),MB_ICONWARNING |MB_OK);
    }
}

void Panel::move(string fromPath, string name){
    if(current_directory == "Disks" || fromPath == "Disks"){
        string message("You can't move logical driver or to logical drivers!");
        MessageBox( NULL,TEXT(message.c_str()),TEXT("Move"),MB_ICONWARNING |MB_OK);
        return;
    }
    name.resize(name.length()+2);
    string dir_path_from(fromPath+'\\'+name);   
    string dir_path_to(current_directory+'\\'+name);

    SHFILEOPSTRUCT shfo = {
        NULL,
        FO_MOVE,
        dir_path_from.c_str(),
        dir_path_to.c_str(),
        FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION,
        FALSE,
        NULL,
        NULL };


    if( !SHFileOperation(&shfo)==0){
        string message("Can not move "+ name);
        MessageBox( NULL,TEXT(message.c_str()),TEXT("Move"),MB_ICONWARNING |MB_OK);
    }
}

void Panel::rename(string name){
    if(current_directory == "Disks"){
        string message("You can't rename logica drivers!");
        MessageBox( NULL,TEXT(message.c_str()),TEXT("Rename"),MB_ICONWARNING |MB_OK);
    }
    string dir_path_from;
    string dir_path_to;
    ///
    if(is_current_Directory()){
        dir_path_from = current_directory+'\\'+folders_to_display[cursor].name;
        dir_path_to = current_directory+'\\'+name;
    }
    else{
        dir_path_from = current_directory+'\\'+files_to_display[cursor - folders_to_display.size()].name;
        if(name.find_last_of('.') != string::npos){
            string message("Do you want to change files extention?");
            int result = MessageBox( NULL,TEXT(message.c_str()),TEXT("Rename"),MB_ICONQUESTION |MB_YESNO);
            if(result == IDYES)
                dir_path_to = current_directory+'\\'+name;
            else if(result == IDNO){
                std::size_t foundp = files_to_display[cursor - folders_to_display.size()].name.find_last_of('.');
                string fname = name + files_to_display[cursor - folders_to_display.size()].name.substr(foundp);
                dir_path_to = current_directory+'\\'+fname;
            }
        }
        else{
            std::size_t foundp = files_to_display[cursor - folders_to_display.size()].name.find_last_of('.');
            string fname = name + files_to_display[cursor - folders_to_display.size()].name.substr(foundp);
            dir_path_to = current_directory+'\\'+fname;
        }
    }
    dir_path_from.resize(dir_path_from.length()+2);
    dir_path_to.resize(dir_path_to.length()+2);
    SHFILEOPSTRUCT shfo = {
        NULL,
        FO_RENAME,
        dir_path_from.c_str(),
        dir_path_to.c_str(),
        FOF_SILENT | FOF_NOERRORUI | FOF_NOCONFIRMATION,
        FALSE,
        NULL,
        NULL };

    int a = SHFileOperation(&shfo);
    if( a != 0 ){
        string message("Can not rename "+ name);
        MessageBox( NULL,TEXT(message.c_str()),TEXT("Rename"),MB_ICONWARNING |MB_OK);
        cout<<hex<<a<<endl;
    }
}

void Panel::search(string name, vector<string>& found){
    queue<string> subfolders;
    subfolders.push(current_directory);

    while(!subfolders.empty()){ // пока очередь посещения клеток непустая
        string cur = subfolders.front();  
        subfolders.pop();
        search_in_folder(name, cur, found, subfolders);
    }

    return;
}

void Panel::search_in_folder(string name, string path, vector<string>& found, queue<string>& subfolders){
    if (path.length() > (MAX_PATH - 3)){
        cout<<"Directory path is too long.\n";
        return;
    }
    string dir = path;
    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;  
    dir+="*";
    hFind = FindFirstFileA(dir.c_str(), &ffd);
    if (INVALID_HANDLE_VALUE == hFind){
      cout<<"3 "<<current_directory<<'\t'<<dir<<endl;
      return ;
    }
    FindNextFile(hFind, &ffd);
    while (FindNextFile(hFind, &ffd) != 0){
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
            if(ffd.cFileName == name)
                found.push_back(path + ffd.cFileName + '\\');
            subfolders.push(path + ffd.cFileName + '\\');
        }
        else{
            if(ffd.cFileName == name)
                found.push_back(path + ffd.cFileName);
        }
    }
    FindClose(hFind);
}

void Panel::get_content(){
    for(int i = 0; i < folders_to_display.size(); i++){
        content.push_back(container());
        content.back().name = folders_to_display[i].name;
        content.back().size = "";
        content.back().time = "";
    }

    for(int i = 0; i < files_to_display.size(); i++){
        content.push_back(container());
        string line = files_to_display[i].name;
        while(line.size() > 25){
            for(int j = 0; j < 3; j++)
                line.pop_back();
            line += "..";
        }
        content.back().name = line;
        line.erase();
        SYSTEMTIME stUTC, stLocal;
        FileTimeToSystemTime(&files_to_display[i].time, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
        line += to_string(stLocal.wMonth);
        line += '.';
        line += to_string(stLocal.wDay);
        line += '.';
        line += to_string(stLocal.wYear);
        line += '\t';
        line += to_string(stLocal.wHour);
        line += ':';
        line += to_string(stLocal.wMinute);
        line += '\t';
        content.back().time = line;
        if(files_to_display[i].size.QuadPart < pow(1024,2))
            line = to_string(INT(files_to_display[i].size.QuadPart / 1024)) + " KB";
        else if(files_to_display[i].size.QuadPart < pow(1024,3))
            line = to_string(INT(files_to_display[i].size.QuadPart / pow(1024,2))) + " MB";
        else if(files_to_display[i].size.QuadPart < pow(1024,4))
            line = to_string(INT(files_to_display[i].size.QuadPart / pow(1024,3))) + " GB";
        content.back().size = line;
    }
}