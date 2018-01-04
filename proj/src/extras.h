#ifndef _EXTRAS_H_
#define _EXTRAS_H_

#include "bitmap.h"

typedef struct{
	unsigned int x,y; /**< @brief x and y coordinates */
	Bitmap * bmp; /**< @brief pointer bitmap */
	unsigned int op; /**< @brief gamemode to call */
}MenuPointer;

typedef struct{
	int x,y; /**< @brief x and y coordinates */
	Bitmap * bmp; /**< @brief aim bitmap */
	int aim_x, aim_y; /**< @brief x and y coordinates of the center of the aim */
	int shot; /**< @brief tells if the player has shot */
} Aim;

/**
 * @brief      Creates a menu pointer.
 *
 * @param[in]  x     the x coord
 * @param[in]  y     the y coord
 *
 * @return     the created menu pointer
 */
MenuPointer * create_MenuPointer(unsigned int x, unsigned int y);

/**
 * @brief      destroys a menu pointer
 *
 * @param      mp    The menu pointer
 */
void destroy_MenuPointer(MenuPointer * mp);

/**
 * @brief      Creates an aim.
 *
 * @return     The created aim
 */
Aim * create_Aim();

/**
 * @brief      Destroys an aim
 *
 * @param      mp    The aim
 */
void destroy_Aim(Aim * mp);

/**
 * @brief      Updates the coords of the aim
 *
 * @param      mouse_packet  The mouse packet
 * @param      aim           The aim
 */
void aim_update(unsigned long * mouse_packet, Aim * aim);

/**
 * @brief      Subscirbes all the interrupts of
 *  the game
 *
 * @return     0 if no errors have occured, otherwise 1
 */
int game_subscribe_int();

/**
 * @brief      unsubscribes all the interrupts of the game
 *
 * @return     0 if no errors have occured, otherwise 1
 */
int game_unsubscribe_int();


#endif
