#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <math.h>

#include "vbe.h"
#include "graphics.h"
#include "timer.h"
#include "i8254.h"
#include "video_gr.h"

/* Private global variables */

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static char *drawing_buf;	/* buffer where the bitmaps will be printed*/
static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

int vg_init(unsigned short mode){

	struct reg86u reg;
	reg.u.w.ax = 0x4F02; // VBE call, function 02 -- set VBE mode
	reg.u.w.bx = 1<<14|mode; // set bit 14: linear framebuffer
	reg.u.b.intno = 0x10;
	if( sys_int86(&reg) != OK ) {
	printf("set_vbe_mode: sys_int86() failed to set mode \n");
		return 1;
	}

	vbe_mode_info_t vbe;
	vbe_get_mode_info(mode, &vbe);

	h_res = vbe.XResolution;
	v_res = vbe.YResolution;
	bits_per_pixel = vbe.BitsPerPixel;



	int r;
	struct mem_range mr;
	unsigned int vram_base = (unsigned int) vbe.PhysBasePtr;  /* VRAM's physical addresss */
	unsigned int vram_size = h_res*v_res*(bits_per_pixel/8);  /* VRAM's size, but you can use
	                            the frame-buffer size, instead */
	/* frame-buffer VM address */

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes) vram_base;
	mr.mr_limit = mr.mr_base + vram_size;

	if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	   panic("sys_privctl (ADD_MEM) failed: %d\n", r);

	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
	drawing_buf = (char*) malloc(h_res*v_res*bits_per_pixel/8);

	if(video_mem== MAP_FAILED)
	   panic("couldn't map video memory");
	return 0;
}

int vg_setColor(unsigned short x, unsigned short y, unsigned short color){
	if(x > h_res || y > v_res){
		return 1;
	}
	*(video_mem + y*h_res + x) = color;
	return 0;
}

int vg_drawSquare(unsigned short x,unsigned short y,unsigned short size,unsigned long color){
	unsigned int i,j;
	for (i = y; i < y+size;i++){
		for (j = x; j < x+size;j++){
			if(vg_setColor(j+ceil(h_res/2.0),i+ceil(v_res/2.0),color) != 0){
				return 1;
			}
		}
	}
	return 0;
}

/*
int vg_drawMap(char *xpm[], unsigned short xi, unsigned short yi){
	if(xi > h_res || yi > v_res){
		printf("Coordinates out of range\n");
		return 1;
	}
	int width;
	int height;
	char * pixmap;
	pixmap = read_xpm(xpm,&width,&height,h_res,v_res);
	unsigned int i,j;

	for(i = 0; i < height; i++){

		for(j = 0; j < width; j++){
			vg_setColor(j+xi,i+yi,*(pixmap + i*width + j));
		}

	}

	return 0;
}
*/

int vg_drawLine(unsigned short xi, unsigned short yi,
        unsigned short xf, unsigned short yf, unsigned long color){

	int delta_x = xf-xi;
	int delta_y = yf-yi;
	float decl = (float) delta_y/delta_x;
	int count_x = 0;
	int count_y = 0;

	while((count_x < delta_x) || (count_y < delta_y)){

		if(count_y < decl * count_x){

			while(count_y < decl * count_x){
				yi++;
				count_y++;
				vg_setColor(xi,yi,color);
			}

		}
		else{
			vg_setColor(xi,yi,color);
		}

		xi++;
		count_x++;

	}
	return 0;

}

int vg_drawLine_new(unsigned short xi, unsigned short yi,
        unsigned short xf, unsigned short yf, unsigned long color){
	int delta_x = xf-xi;
		int delta_y = yf-yi;
		float decl = (float) delta_y/delta_x;
		int count_x = 0;
		int count_y = 0;
	if(delta_x > 0 || delta_y > 0){

	        while((count_x < delta_x) || (count_y < delta_y)){
	                if(count_y < decl * count_x){
	                        while(count_y < decl * count_x){
	                                yi++;
	                                count_y++;
	                                vg_setColor(xi,yi,color);
	                        }
	                }
	                else{
	                       vg_setColor(xi,yi,color);
	                }
	                xi++;
	                count_x++;
	        }
	    }


	    else if(delta_x < 0 || delta_y > 0){

	        while((abs(count_x) < abs(delta_x)) || (abs(count_y) < abs(delta_y))){
	                if(abs(count_y) < fabs(decl * count_x)){
	                        while(count_y < decl * count_x){
	                                yi++;
	                                count_y++;
	                                vg_setColor(xi,yi,color);
	                        }
	                }
	                else{
	                        vg_setColor(xi,yi,color);
	                }
	                xi--;
	                count_x--;
	        }
	    }


	    else if(delta_x < 0 || delta_y < 0){

	        while((abs(count_x) < abs(delta_x)) || (abs(count_y) < abs(delta_y))){
	                if(abs(count_y) < fabs(decl * count_x)){
	                        while(count_y < decl * count_x){
	                                yi--;
	                                count_y--;
	                                vg_setColor(xi,yi,color);
	                        }
	                }
	                else{
	                        vg_setColor(xi,yi,color);
	                }
	                xi--;
	                count_x--;
	        }
	    }

	    else if(delta_x > 0 || delta_y < 0){

	        while((abs(count_x) < abs(delta_x)) || (abs(count_y) < abs(delta_y))){
	                if(abs(count_y) < fabs(decl * count_x)){
	                        while(count_y < decl * count_x){
	                                yi--;
	                                count_y--;
	                                vg_setColor(xi,yi,color);
	                        }
	                }
	                else{
	                        vg_setColor(xi,yi,color);
	                }
	                xi++;
	                count_x++;
	        }
	    }
	return 0;
}

int vg_clear(){
	unsigned int i,j;
	for(i = 0;i < v_res;i++){
		for(j = 0; j < h_res;j++){
			*(video_mem + i*h_res + j) = COLOR_BLACK;
		}
	}
	return 0;
}

int vg_exit() {
  struct reg86u reg86;

  reg86.u.b.intno = 0x10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/

  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}

unsigned getHorResolution(){
	return h_res;
}

unsigned getVerResolution(){
	return v_res;
}

char * getGraphicsBuffer(){
	return video_mem;
}

char * getDrawingBuffer(){
	return drawing_buf;
}

void pageFlip(){
	memcpy(video_mem,drawing_buf,h_res*v_res*bits_per_pixel/8);
}
