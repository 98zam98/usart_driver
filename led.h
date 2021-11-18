#ifndef LED_H_
#define LED_H_

#include "hardware.h"


void led_init();
void led_on();
void led_off();
void led_toggle();
void led_ontooff(char on,char off);

#endif /* LED_H_ */