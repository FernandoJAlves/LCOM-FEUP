#ifndef _DUCK_H_
#define _DUCK_H_

#include "bitmap.h"
#include "extras.h"

typedef enum{START, RIGHT_HOR, LEFT_HOR, RIGHT_UP, LEFT_UP, RIGHT_DOWN, LEFT_DOWN, SHOT, FALL} duck_direction; /**< @brief possible directions of the duck */


typedef struct{
	int pos_x; /**< @brief x coordinate */
	int pos_y; /**< @brief y coordinate */
	Bitmap* bmp[8]; /**< @brief array of the bitmaps */
	int x_speed; /**< @brief x speed */
	int y_speed; /**< @brief y speed */
	int index; /**< @brief for animation purposes */
	int current_state; /**< @brief current state of the animation */
	duck_direction direction; /**< @brief direction of the duck */
	int auto_counter; /**< @brief counter for random movement */
	int count; /**< @brief counter for animation */
	int count_shot; /**< @brief counter for animation */
	//bool is_dead;

} Duck;

/**
 * @brief      Creates a duck.
 *
 * @param[in]  y     The y coord
 *
 * @return     Returns a pointer to a Duck
 */
Duck* create_duck(int y);

/**
 * @brief      Destroys a duck sprite
 *
 * @param      d1    The Duck
 */
void destroy_duck(Duck * d1);

/**
 * @brief      changes the movement of the duck depending on the input
 *
 * @param[in]  scancode  The scancode
 * @param      d1        The Duck
 */
void move_duck(unsigned long scancode, Duck * d1);

/**
 * @brief     Changes between movement sprites to animate the duck
 *
 * @param[in]  scancode  The scancode
 * @param      d1        The Duck
 */
void animate_duck(unsigned long scancode, Duck * d1);

/**
 * @brief      Changes the state of the duck in the case of collision
 *
 * @param      d1    The Duck
 * @param      aim   The aim
 */
void shot_duck(Duck * d1,Aim * aim);

/**
 * @brief      Changes the state of multiple duck in the case of collision
 *
 * @param      d1           The d 1
 * @param      aim          The aim
 * @param      number_hits  The number hits
 */
void shot_duck2(Duck * d1,Aim * aim, int * number_hits);

/**
 * @brief      changes the movement of the duck automatically
 *
 * @param      d1    The d 1
 */
void move_duck_auto(Duck * d1);

/**
 * @brief      Selects a new route the duck
 *
 * @param      d1    The duck
 */
void select_new_route(Duck * d1);

/**
 * @brief      calculates the number o ducks spawned in the following round
 *
 * @param[in]  round  The round
 *
 * @return     the number of ducks of the following round
 */
int next_round_ducks(int round);

/**
 * @brief      calculates the number o bullets given in the following round
 *
 * @param[in]  round  The round
 *
 * @return     the number of bullets of the following round
 */
int next_round_bullets(int round);

/**
 * @brief      calculates the number o bullets given in the following round for the multiplayer mode
 *
 * @param[in]  round  The round
 *
 * @return     the number of bullets of the following round
 */
int next_round_bullets_mp(int round);

/**
 * @brief      Checks if every duck in the field is on the ground
 *
 * @param      ducks_list  The ducks list
 *
 * @return     1 if all ducks are dead, otherwise 0
 */
int all_ducks_dead(Duck** ducks_list);

/**
 * @brief      Places all the ducks in the starting position
 *
 * @param      ducks_list  The list of ducks
 */
void place_ducks_start(Duck** ducks_list);

/**
 * @brief      Makes a duck get shot and sends that info through serial port
 *
 * @param      d1           The d 1
 * @param      aim          The aim
 * @param      number_hits  The number hits
 */
void shot_duck2_transmit(Duck * d1,Aim * aim, int * number_hits);

/**
 * @brief      Receives through serial port if the duck is dead
 *
 * @param      d1             The duck
 * @param      received_char  The received character
 */
void shot_duck2_receive(Duck * d1,unsigned long  * received_char);

/**
 * @brief      Checks if there's still ducks falling
 *
 * @param      ducks_list  The list of ducks
 *
 * @return     1 if are still ducks falling, otherwise 0
 */
int any_ducks_falling(Duck** ducks_list);

/**
 * @brief      places the the duck in the starting position in the multiplayer mode
 *
 * @param      d1    The d 1
 */
void place_duck_start_mp(Duck * d1);


#endif
