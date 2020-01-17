#include "head.h"

union Pixel
{
	UINT argb;
	struct  {		
	char r;
	char g;
	char b;
	char a;
	};
};


//Розробити структуру даних для збереження інформації про зображення
//(в динамічній купі оперативної пам’яті).
struct Image {

	UINT width;//width
	UINT height;//height
	char type[3];//magic number
	unsigned char Maxval;//The maximum color value (Maxval) char beacose <=255 
	Pixel **canvas; //value of color

	void setPixel(int i, int j, Pixel p){	canvas[i][j] = p;}
	Pixel getPixel(int i, int j ){return canvas[i][j];	}

	Image(char * t, UINT color,const int w, const int h):
		Maxval(color),width(w), height(h){
		strcpy(type, t);
		canvas = new Pixel*[height];
		for (int i = 0; i < height; i++)
		{
			canvas[i] = new Pixel[width];
		}

	}
	//Конструктор копирования
	Image(const Image & img) {
		strcpy(type,img.type);
		Maxval = img.Maxval;
		width = img.width;
		height = img.height;
		canvas = new Pixel*[height];
		for (int i = 0; i <height; i++)
		{
			canvas[i] = new Pixel[width];
		}
		//copy all values
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				canvas[i][j].argb =img.canvas[i][j].argb;
			}
		}


	}
	~Image() {		
		for (int i = 0; i < height; i++)
		{
			delete[] canvas[i];
		}
		delete[] canvas;
	}
};