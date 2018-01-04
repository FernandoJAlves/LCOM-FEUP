#ifndef _POINTS_H_
#define _POINTS_H_

#include "bitmap.h"
#include "extras.h"

extern unsigned long day; /**< @brief Global variable that holds the day of the highscore */
extern unsigned long month; /**< @brief Global variable that holds the month of the highscore */
extern unsigned long year; /**< @brief Global variable that holds the year of the highscore */
extern unsigned long hour; /**< @brief Global variable that holds the hour of the highscore */
extern unsigned long minute; /**< @brief Global variable that holds the minute of the highscore */
extern unsigned int highscore; /**< @brief Global variable that holds the value of the highscore */
extern char name[9]; /**< @brief Global variable that holds the name of the player with the highscore */

Bitmap * number_0; /**< @brief Global bitmap of the number zero */
Bitmap * number_1; /**< @brief Global bitmap of the number one */
Bitmap * number_2; /**< @brief Global bitmap of the number two */
Bitmap * number_3; /**< @brief Global bitmap of the number three */
Bitmap * number_4; /**< @brief Global bitmap of the number four */
Bitmap * number_5; /**< @brief Global bitmap of the number five */
Bitmap * number_6; /**< @brief Global bitmap of the number six */
Bitmap * number_7; /**< @brief Global bitmap of the number seven */
Bitmap * number_8; /**< @brief Global bitmap of the number eight */
Bitmap * number_9; /**< @brief Global bitmap of the number nine */
Bitmap * double_dot; /**< @brief Global bitmap of a double dot */
Bitmap * line; /**< @brief Global bitmap of line */

Bitmap * number_0_small; /**< @brief Global bitmap of the small number zero */
Bitmap * number_1_small; /**< @brief Global bitmap of the small number one */
Bitmap * number_2_small; /**< @brief Global bitmap of the small number two */
Bitmap * number_3_small; /**< @brief Global bitmap of the small number three */
Bitmap * number_4_small; /**< @brief Global bitmap of the small number four */
Bitmap * number_5_small; /**< @brief Global bitmap of the small number five */
Bitmap * number_6_small; /**< @brief Global bitmap of the small number six */
Bitmap * number_7_small; /**< @brief Global bitmap of the small number seven */
Bitmap * number_8_small; /**< @brief Global bitmap of the small number eight */
Bitmap * number_9_small; /**< @brief Global bitmap of the small number nine */
Bitmap * double_dot_small; /**< @brief Global bitmap of the small double dot */
Bitmap * line_small; /**< @brief Global bitmap of the small line */
Bitmap * duck_bmp; /**< @brief Global bitmap of the duck icon for the counter */
Bitmap * bullet_bmp; /**< @brief Global bitmap of the bullet icon for the counter */


Bitmap * letter_a; /**< @brief Global bitmap of the letter a */
Bitmap * letter_b; /**< @brief Global bitmap of the letter b */
Bitmap * letter_c; /**< @brief Global bitmap of the letter c */
Bitmap * letter_d; /**< @brief Global bitmap of the letter d */
Bitmap * letter_e; /**< @brief Global bitmap of the letter e */
Bitmap * letter_f; /**< @brief Global bitmap of the letter f */
Bitmap * letter_g; /**< @brief Global bitmap of the letter g */
Bitmap * letter_h; /**< @brief Global bitmap of the letter h */
Bitmap * letter_i; /**< @brief Global bitmap of the letter i */
Bitmap * letter_j; /**< @brief Global bitmap of the letter j */
Bitmap * letter_k; /**< @brief Global bitmap of the letter k */
Bitmap * letter_l; /**< @brief Global bitmap of the letter l */
Bitmap * letter_m; /**< @brief Global bitmap of the letter m */
Bitmap * letter_n; /**< @brief Global bitmap of the letter n */
Bitmap * letter_o; /**< @brief Global bitmap of the letter o */
Bitmap * letter_p; /**< @brief Global bitmap of the letter p */
Bitmap * letter_q; /**< @brief Global bitmap of the letter q */
Bitmap * letter_r; /**< @brief Global bitmap of the letter r */
Bitmap * letter_s; /**< @brief Global bitmap of the letter s */
Bitmap * letter_t; /**< @brief Global bitmap of the letter t */
Bitmap * letter_u; /**< @brief Global bitmap of the letter u */
Bitmap * letter_v; /**< @brief Global bitmap of the letter v */
Bitmap * letter_w; /**< @brief Global bitmap of the letter w */
Bitmap * letter_x; /**< @brief Global bitmap of the letter x */
Bitmap * letter_y; /**< @brief Global bitmap of the letter y */
Bitmap * letter_z; /**< @brief Global bitmap of the letter z */

#define DEC(x)            (((x) >> 4) & 0x0000F) /**< @brief Returns the second digit of x  */
#define UNIT(x)           ((x) & 0x000F) /**< @brief Returns the second digit of x */

/**
 * @brief      Loads the bmps of the large digits
 */
void loadDigits_large();

/**
 * @brief      Deletes the large digits
 */
void deleteDigits_large();

/**
 * @brief      Draws the score with 6 large digits
 *
 * @param[in]  score  The score
 * @param[in]  x_pos  The x position to draw
 * @param[in]  y_pos  The y position to draw
 *
 * @return     Returns zero
 */
int draw_score_6_digits_large(int score, int x_pos, int y_pos);

/**
 * @brief      Loads the bmps of the small digits
 */
void loadDigits_small();

/**
 * @brief      Deletes the bmps od the small digits
 */
void deleteDigits_small();

/**
 * @brief      Loads the bmps of the font
 */
void loadFont();

/**
 * @brief      Deletes the bmps of the font
 */
void deleteFont();

/**
 * @brief      Draws the score with 6 digits small.
 *
 * @param[in]  score  The score
 * @param[in]  x_pos  The x position
 * @param[in]  y_pos  The y position
 *
 * @return     returns zero
 */
int draw_score_6_digits_small(int score, int x_pos, int y_pos);

/**
 * @brief      Draws the remaining duck icons and the remaining bullets icons
 *
 * @param[in]  ducks    The number of remaining ducks
 * @param[in]  bullets  The number of remaining bullets
 * @param[in]  x_pos    The x position
 * @param[in]  y_pos    The y position
 *
 * @return     returns zero
 */
int draw_ducks_bullets(int ducks, int bullets, int x_pos, int y_pos);

/**
 * @brief      Reads the actual highscore in a text file
 */
void read_score();

/**
 * @brief      Writes the actual highscore in a text file
 */
void write_score();

/**
 * @brief      Resets the actual highscore to zero in the variables and in the text file
 */
void reset_score();

/**
 * @brief      If points is superior to the actual highscore, updates the highscore
 *
 * @param[in]  points  The points
 * @param      nome    The name
 */
void update_score(unsigned int points, char nome[9]);

/**
 * @brief      Draws the date with small digits
 *
 * @param[in]  dia     The day
 * @param[in]  mes     The month
 * @param[in]  ano     The year
 * @param[in]  hora    The hour
 * @param[in]  minuto  The minute
 * @param[in]  x_pos   The x position
 * @param[in]  y_pos   The y position
 */
void draw_date_small(int dia, int mes, int ano, int hora, int minuto, int x_pos, int y_pos);

/**
 * @brief      Draws the date with large digits
 *
 * @param[in]  dia     The day
 * @param[in]  mes     The month
 * @param[in]  ano     The year
 * @param[in]  hora    The hour
 * @param[in]  minuto  The minute
 * @param[in]  x_pos   The x position
 * @param[in]  y_pos   The y position
 */
void draw_date_large(int dia, int mes, int ano, int hora, int minuto, int x_pos, int y_pos);

/**
 * @brief      Draws a single small digit
 *
 * @param[in]  value  The value
 * @param[in]  x_pos  The x position
 * @param[in]  y_pos  The y position
 */

void small_digit_display(int value, int x_pos, int y_pos);

/**
 * @brief      Draws a single large digit
 *
 * @param[in]  value  Number to draw
 * @param[in]  x_pos  The x position
 * @param[in]  y_pos  The y position
 */

void large_digit_display(int value, int x_pos, int y_pos);

/**
 * @brief      Draws a character.
 *
 * @param[in]  c      Char to draw
 * @param[in]  x_pos  The x position
 * @param[in]  y_pos  The y position
 */

void draw_char(char c, unsigned int x_pos, unsigned int y_pos);

/**
 * @brief      Draws a string.
 *
 * @param      nome   The nome
 * @param[in]  x_pos  The x position
 * @param[in]  y_pos  The y position
 */
void draw_string(char *nome, unsigned int x_pos, unsigned int y_pos);

/**
 * @brief      Writes a character in the global name string
 *
 * @param      c         Character to write
 * @param[in]  scancode  The scancode
 */
void write_char(char * c, unsigned long scancode);

#endif
