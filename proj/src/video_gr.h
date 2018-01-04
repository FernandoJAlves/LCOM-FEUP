#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 * 
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen, 
 *  and the number of colors
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
int vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 * 
 * @return 0 upon success, non-zero upon failure
 */
int vg_clear();

/**
 * @brief      Sets the color of the specified pixel
 *
 * @param[in]  x      x coordinate
 * @param[in]  y      y coordinate
 * @param[in]  color  The color
 *
 * @return     0 upon success, non-zero upon failure
 */
int vg_setColor(unsigned short x, unsigned short y, unsigned short color);

/**
 * @brief      Draws a square
 *
 * @param[in]  x      x coordinate
 * @param[in]  y      y coordinate
 * @param[in]  size   The size of the square
 * @param[in]  color  The color
 *
 * @return     0 upon success, non-zero upon failure
 */
int vg_drawSquare(unsigned short x,unsigned short y,unsigned short size,unsigned long color);

/**
 * @brief      Draws a line
 *
 * @param[in]  xi     x starting coordinate
 * @param[in]  yi     y starting coordinate
 * @param[in]  xf     x final coordinate
 * @param[in]  yf     y final coordinate
 * @param[in]  color  The color
 *
 * @return     0 upon success, non-zero upon failure
 */
int vg_drawLine(unsigned short xi, unsigned short yi,
        unsigned short xf, unsigned short yf, unsigned long color);

/**
 * @brief      Gets the horizontal resolution.
 *
 * @return     The horizontal resolution.
 */
unsigned getHorResolution();

/**
 * @brief      Gets the vertical resolution.
 *
 * @return     The vertical resolution.
 */
unsigned getVerResolution();

/**
 * @brief      Gets the graphics buffer.
 *
 * @return     The graphics buffer.
 */
char * getGraphicsBuffer();

/**
 * @brief      Gets the drawing buffer.
 *
 * @return     The drawing buffer.
 */
char * getDrawingBuffer();

/**
 * @brief      Copies the drawing buffer to the vram
 */
void pageFlip();

/**
 * @brief      Exits graphic mode
 *
 * @return     0 upon success, non-zero upon failure
 */
int vg_exit(void);

 /** @} end of video_gr */
 
#endif /* __VIDEO_GR_H */
