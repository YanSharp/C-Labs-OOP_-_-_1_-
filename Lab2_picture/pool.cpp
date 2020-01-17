#include "pool.h"

bool save_picture(Image * myImage, string fileName) {
	ofstream picture(fileName, ios::out | ios::binary);
	if (!picture.is_open()) {
		cout << "Can't open file. Check it please!" << endl;
		return false;
	}

	picture << myImage->type<<'\n' << myImage->width << " " << myImage->height << "\n" <<(int)myImage->Maxval<< "\n";
	for (int i = 0; i < myImage->height; i++) {
		for (int j = 0; j < myImage->width; j++) {			
			picture<<myImage->canvas[i][j].r<<myImage->canvas[i][j].g <<myImage->canvas[i][j].b;
		}
		//picture << endl;
	}
	picture.close();
	return true;
}


 bool upload_picture(Image *& myImage, string fileName) {
	char line[MAX];
	char * ptr; 
	int temp;
	int sizeX = 0;
	int sizeY = 0;
	int colorMax = 0;

	ifstream picture(fileName, ios::binary);
	if (!picture.is_open()) {
		cout << "Can't open file. Check it please!" << endl;
		return false;
	}
	cout << "File opened!" << endl;

#pragma region Read Head

	picture.read(line, MAX);
	
	if (line[0] != 'P'&&  line[1] != '6')//read magic number
	{
		cout << line << "\nThis is not .PPM file!" << endl;
		return false;
	}
	char type[3];
	strncpy(type, line, 2);
	type[2] = '\0';
	cout << type << endl;
	ptr = line + 2;
	while (!colorMax)
	{
		temp = 0;
		if (*ptr == '#')while (*ptr != '\n')ptr++;//without comment
		while (*ptr == ' ')ptr++; //
		if (*ptr == '\n' || *ptr == '\r' || *ptr == '\t')
			ptr++;
		temp = atoi(ptr);// read number
		if (temp)
		{
			if (!sizeX)
				sizeX = temp;
			else
				if (!sizeY)
					sizeY = temp;
				else
					if (!colorMax)
						colorMax = temp;

			int delta = temp * 10;
			while (delta = delta / 10)// how many digit next
			{
				ptr++;
			}
		}
	}
#pragma endregion

	picture.seekg(ptr - line + 1, picture.beg);//set position after maxcolor	
	myImage =new Image(type,colorMax,sizeX, sizeY);
	
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			picture.read(&myImage->canvas[i][j].r, 1);
			picture.read(&myImage->canvas[i][j].g, 1);
			picture.read(&myImage->canvas[i][j].b, 1);
			//myImage->canvas[i][j].a = 0;
		}
	}
	picture.close();
	return true;
}

bool upload_picture(Memory_Pool & album, string fileName){
	 char line[MAX];
	 char * ptr;
	 int temp;
	 int sizeX = 0;
	 int sizeY = 0;
	 int colorMax = 0;

	 ifstream picture(fileName, ios::binary);
	 if (!picture.is_open()) {
		 cout << "Can't open file. Check it please!" << endl;
		 return false;
	 }
	 cout << "File opened!" << endl;

#pragma region Read Head

	 picture.read(line, MAX);
	 
	 if (line[0] != 'P'&&  line[1] != '6')//read magic number
	 {
		 cout << line << "\nThis is not .PPM file!" << endl;
		 return false;
	 }
	 char type[3];
	 strncpy(type, line, 2);
	 type[2] = '\0';
	 cout << type << endl;
	 ptr = line + 2;
	 while (!colorMax)
	 {
		 temp = 0;
		 if (*ptr == '#')while (*ptr != '\n')ptr++;//without comment
		 while (*ptr == ' ')ptr++; //
		 if (*ptr == '\n' || *ptr == '\r' || *ptr == '\t')
			 ptr++;
		 temp = atoi(ptr);// read number
		 if (temp)
		 {
			 if (!sizeX)
				 sizeX = temp;
			 else
				 if (!sizeY)
					 sizeY = temp;
				 else
					 if (!colorMax)
						 colorMax = temp;

			 int delta = temp * 10;
			 while (delta = delta / 10)// how many digit next
			 {
				 ptr++;
			 }
		 }
	 }
#pragma endregion

	 picture.seekg(ptr - line + 1, picture.beg);//set position after maxcolor	
	 Image * myImage = album.pool_new(type, colorMax, sizeX, sizeY);
	 if(myImage==nullptr)
		 return false;
	
	 for (int i = 0; i < sizeY; i++) {
		 for (int j = 0; j < sizeX; j++) {
			 picture.read(&myImage->canvas[i][j].r, sizeof(char));
			 picture.read(&myImage->canvas[i][j].g, sizeof(char));
			 picture.read(&myImage->canvas[i][j].b, sizeof(char));
			 myImage->canvas[i][j].a = 0;
		 }
	 }	 
	 picture.close();
	 return true;
 }

 Image * Memory_Pool::pool_new(char * type,  char color, const int x, const int y)
 {
	 for (size_t i = 0; i < BLOCK_COUNT; i++)
	 {
		 if (pool[i].ptr_image == nullptr && sizeof(Image) + x*y < BLOCK_SIZE)
		 {
			 pool[i].ptr_image = new(pool[i].allocate(sizeof(*new Image(type, color, x, y)))) Image(type, color, x, y);
			 return pool[i].ptr_image;
		 }
	 }
	 return nullptr;
 }


void Memory_Pool::pool_delete(Image* ptr)
{
	for (size_t i = 0; i < BLOCK_COUNT; i++)
	{
		if (pool[i].ptr_image == ptr)
		{
			pool[i].ptr_image = nullptr;
			pool[i].ptr_last = pool[i].memory;
			return;
		}
	};
}
