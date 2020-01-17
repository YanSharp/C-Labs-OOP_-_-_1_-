#include "image.h"


//Реалізувати виділення пам’яті для зображень з пулу пам’яті фіксованого розміру.

struct Memory_Block {
	char memory[BLOCK_SIZE];
	char* ptr_last;
	Image * ptr_image ;
	void* allocate(int size);
	Memory_Block() : ptr_last(memory), ptr_image(nullptr) {};
};

inline void * Memory_Block::allocate(int size)
{
	void * ptr_first = ptr_last;
	ptr_last += size;
	return ptr_first;
}

struct Memory_Pool
{
	Memory_Block pool[BLOCK_COUNT];
	Image  * pool_new(char * type, char color, const int x, const int y);
	void pool_delete(Image*);
};
//create_white - функція, що створює біле полотно заданого розміру;
void create_white(Image *);

// create_black - функція, що створює чорне полотно заданого розміру;
void create_black(Image *);


void create_red(Image *);
void create_green(Image *);


//- create_color - функція, що створює полотно, де {ВАРІАНТ}​.
void create_color(Image *);

//Реалізувати функції збереження/завантаження зображення до/з файлу в форматі PPM.
bool save_picture(Image * myImage, string fileName);
bool upload_picture(Image *& myImage, string fileName);
bool upload_picture(Memory_Pool & album, string fileName);
