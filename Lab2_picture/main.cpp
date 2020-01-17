#include "pool.h"

#define MAX 255

#define FIX_SIZE 921600


int main() {
	char type[3] = "P6";//{'P','6','\0'}
	Memory_Pool album;
	Image * first = album.pool_new(type, 255, 100, 100);
	create_black(first);
	save_picture(first, "whiteSaveTest.ppm");
	

	Image * second = album.pool_new(type, 255, 100, 100);
	create_black(second);
	save_picture(second, "blackSaveTest.ppm");


	Image * third = album.pool_new(type, 255, 100, 100);
	create_color(third);
	save_picture(third, "colorSaveTest.ppm");

	Image * fourth = album.pool_new(type, 255, 100, 100);
	create_green(fourth);
	save_picture(fourth, "greenSaveTest.ppm");

	album.pool_delete(second);

	

	Image * picture=nullptr;
	if( upload_picture(picture ,"picture.ppm"))
		save_picture(picture, "savedTest.ppm");

	cout << "END";
	return 1;
}