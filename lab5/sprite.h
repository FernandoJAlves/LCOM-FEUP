#ifndef _SPRITE_H_
#define _SPRITE_H_


typedef struct {
	int x,y;
	int width, height;
	int xspeed,yspeed;
	char *map;
} Sprite;

Sprite *create_sprite(char *pic[], int x, int y, int xspeed, int yspeed);

void destroy_sprite(Sprite *sp);

#endif
