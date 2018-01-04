#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {
	struct reg86u reg;
	reg.u.w.ax = 0x4F01; // VBE call, function 01 -- get VBE mode
	lm_init();
	mmap_t mem_map;
	lm_alloc(sizeof(vbe_mode_info_t), &mem_map);
	reg.u.w.es = PB2BASE(mem_map.phys);
	reg.u.w.di = PB2OFF(mem_map.phys);
	reg.u.w.cx = 1<<LINEAR_MODEL_BIT|mode;
	reg.u.b.intno = 0x10;
	if( sys_int86(&reg) != OK ) {
		lm_free(&mem_map);
		printf("vbe_get_mode_info: sys_int86() failed to obtain mode info \n");
		return 1;
	}
	vmi_p->PhysBasePtr = ((vbe_mode_info_t *) mem_map.virtual)->PhysBasePtr;
	vmi_p->XResolution = ((vbe_mode_info_t *) mem_map.virtual)->XResolution;
	vmi_p->YResolution = ((vbe_mode_info_t *) mem_map.virtual)->YResolution;
	vmi_p->BitsPerPixel = ((vbe_mode_info_t *) mem_map.virtual)->BitsPerPixel;
	return 0;

}

int vbe_get_controller(VbeInfoBlock *vbe){
	struct reg86u reg;
		reg.u.w.ax = 0x4F00;
		lm_init();
		mmap_t mem_map;
		lm_alloc(sizeof(VbeInfoBlock), &mem_map);
		reg.u.w.es = PB2BASE(mem_map.phys);
		reg.u.w.di = PB2OFF(mem_map.phys);
		reg.u.b.intno = 0x10;
		if (sys_int86(&reg) != OK) {
				printf("vbe_get_controller: sys_int86() failed to obtain controller info\n");
				lm_free(&mem_map);
				return 1;
			}
		vbe = (VbeInfoBlock *) mem_map.virtual;
	return 0;
}


