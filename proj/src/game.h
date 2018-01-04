#ifndef _GAME_H_
#define _GAME_H_

typedef enum{PLAYING, GAME_OVER, GAME_WON} play_state;

/**
 * @brief      Where Game A logic happens
 *
 * @return     0 if no erros, otherwise 1
 */
int game_a();

/**
 * @brief      A test game made for debug during development
 *
 * @return     0 if no erros, otherwise 1
 */
int game_b();

/**
 * @brief      Where Game B logic happens in the duck perspective
 *
 * @return     0 if no erros, otherwise 1
 */
int game_b_hunter();

/**
 * @brief      Where Game B logic happens in the hunter perspective
 *
 * @return     0 if no erros, otherwise 1
 */
int game_b_duck();

/**
 * @brief      The menu to choose between duck or the hunter
 *
 * @return     0 if no erros, otherwise 1
 */
int game_b_menu();

/**
 * @brief      gameover screen in game A
 *
 * @param[in]  score  The score
 * @param[in]  state  The state
 *
 * @return     0 if no erros, otherwise 1
 */
int gameover_screen_a(int score, play_state state);

/**
 * @brief      gameover screen in game B
 *
 * @param[in]  state  The state
 *
 * @return     0 if no erros, otherwise 1
 */
int gameover_screen_b(play_state state);

#endif
