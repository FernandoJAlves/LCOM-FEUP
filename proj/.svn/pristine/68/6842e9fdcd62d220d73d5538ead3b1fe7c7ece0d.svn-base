#ifndef _MENU_H_
#define _MENU_H_

#define MENU_DELAY           200000 // Delay to wait user action on the menu


#include "bitmap.h"
#include "extras.h"

typedef enum{END_GAME, MENU, GAME_A, SCORE_MENU, GAME_B_MENU, GAME_B_DUCK, GAME_B_HUNTER} game_state;

/**
 * @brief      the interface of the main menu
 *
 * @return     0 if no errors occurred during execution
 */
int main_menu();

/**
 * @brief      the interface before playing game b
 *
 * @param      state  The state
 *
 * @return     0 if no errors occurred during execution
 */
int game_b_menu(game_state * state);

/**
 * @brief      Updates the new position of the menu pointer
 *
 * @param[in]  scancode  The scancode
 * @param      mp        The menu pointer
 */
void change_pointer(unsigned long scancode, MenuPointer * mp);

/**
 * @brief      Updates the new position of the menu pointer (used in game_b_menu)
 *
 * @param[in]  scancode  The scancode
 * @param      mp        The menu pointer
 */
void change_pointer_b(unsigned long scancode, MenuPointer * mp);

/**
 * @brief      Calls the correct gamemode depending on the state
 *
 * @param      mp     The menu pointer
 * @param      state  The state
 */
void menu_option(MenuPointer * mp, game_state * state);

/**
 * @brief      Calls the correct gamemode depending on the state (used in game_b_menu)
 *
 * @param      mp     The menu pointer
 * @param      state  The state
 */
void menu_option_b(MenuPointer * mp, game_state * state);

/**
 * @brief      Menu where the highscore is shown
 *
 * @return     0 if no errors occurred during execution
 */
int score_menu();

#endif
