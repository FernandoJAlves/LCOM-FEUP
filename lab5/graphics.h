#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#define GRAPH_MODE      0x105 // Graphic mode directive
#define COLOR_BLACK               0 // Color number

char *read_xpm(char *map[], int *wd, int *ht, unsigned HRES,unsigned VRES);
char* vg_getPixmap(char *xpm[], int *w, int *h);

#endif
