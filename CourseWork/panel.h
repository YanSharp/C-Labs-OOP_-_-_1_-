#pragma once
#include "headers.h"

struct file{
    string name;
    _LARGE_INTEGER size;
    FILETIME time;
};

struct folder{
    string name;
    _LARGE_INTEGER time;
};

struct container{
    string name;
    string time;
    string size;
};

class Panel{

    public:
        string current_directory;
        vector <folder> folders_to_display;
        vector <file> files_to_display;
        vector <container> content;
        int cursor;
        int start_index;

        Panel( );
        void change_dir(string path);
        void create_dir(string name);
        void del();
        void copy(string fromPath, string name);
        void move(string fromPath, string name);
        void rename(string name);
        void search(string name, vector<string>& found);
        void search_in_folder(string name, string path, vector<string>& found, queue<string>& subfolders);
        void logical_drives();
        bool is_current_Directory(){
            return cursor<folders_to_display.size();

        }

    private:
        void get_content();
        void delete_dir();
        bool clear_dir_recursive(string dir_name);
        void delete_file();
        
};