#include "image.h"

void create_white(Image *white) {	
	for (int i = 0; i < white->height; i++) {
		for (int j = 0; j < white->width; j++) {			 
			//white->canvas[i][j].argb = 0xFFFFFF;//or
			white->canvas[i][j].r = 255;
			white->canvas[i][j].g = 255;
			white->canvas[i][j].b = 255;
			white->canvas[i][j].a = 0;
			}
		}
}

void create_red(Image *white) {
	for (int i = 0; i < white->height; i++) {
		for (int j = 0; j < white->width; j++) {
			white->canvas[i][j].r = 255;
			white->canvas[i][j].g = 0;
			white->canvas[i][j].b = 0;
			white->canvas[i][j].a = 0;
		}
	}
}

void create_green(Image *white) {
	for (int i = 0; i < white->height; i++) {
		for (int j = 0; j < white->width; j++) {
			white->canvas[i][j].r = 0;
			white->canvas[i][j].g = 255;
			white->canvas[i][j].b = 0;
			white->canvas[i][j].a = 0;
		}
	}
}

void create_black(Image * black) {
	for (int i = 0; i < black->height; i++) {
		for (int j = 0; j < black->width; j++) {
			//white->canvas[i][j].argb = 0;//or
			black->canvas[i][j].r = 0;
			black->canvas[i][j].g = 0;
			black->canvas[i][j].b = 0;
			black->canvas[i][j].a = 0;
		}
	}
}

void create_color(Image * variant) {
	for (int i = 0; i < variant->height; i++) {
		for (int j = 0; j < variant->width; j++) {
			variant->canvas[i][j].r = j;
			variant->canvas[i][j].g = j;
			variant->canvas[i][j].b = j;
			variant->canvas[i][j].a = 0;
		}
	}
}


