#ifndef __TIMER_H
#define __TIMER_H


/**
 * @brief      Sets the timer frequency
 *
 * @param[in]  timer  The timer
 * @param[in]  freq   The frequency
 *
 * @return     0 if no errors occurred during execution
 */
int timer_set_frequency(unsigned char timer, unsigned long freq);


/**
 * @brief      Subscribes to the timer interrupts
 *
 * @return     0 if no errors occurred during execution
 */
int timer_subscribe_int(void );


/**
 * @brief      Unsubscribe to the timer interrupts
 *
 * @return     0 if no errors occurred during execution
 */
int timer_unsubscribe_int();


/**
 * @brief      Handles the timer interrupts
 */
void timer_int_handler();


/**
 * @brief      Gets the timer configuration
 *
 * @param[in]  timer  The timer
 * @param      st     Where the configuration will be saved
 *
 * @return     0 if no errors occurred during execution
 */
int timer_get_conf(unsigned char timer, unsigned char *st);


/**
 * @brief      Displays the timer configuration in the correct format
 *
 * @param[in]  conf  The conf
 *
 * @return     0 if no errors occurred during execution
 */
int timer_display_conf(unsigned char conf);


/**
 * @brief      First function that was required, sets the freq
 *
 * @param[in]  freq  The frequency
 *
 * @return     0 if no errors occurred during execution
 */
int timer_test_time_base(unsigned long freq);

/**
 * @brief      Second function that was required, returns the configuration of the provided timer
 *
 * @param[in]  timer  The timer
 *
 * @return     0 if no errors occurred during execution
 */
int timer_test_config(unsigned char timer);

//Global variables
unsigned int timer_counter;

#endif /* __TIMER_H */
