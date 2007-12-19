/*
    Copyright Jim Brain and Brain Innovations, 2004
  
    This file is part of C=Key.

    C=Key is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    C=Key is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with C=Key; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include <avr/io.h>
#include <inttypes.h>
#include "led.h"

static uint8_t led_mask;
static uint8_t led_counter=0;
static uint8_t led_count[8];
/*
 * 00000000 = Off
 * 11111111 = On
 * bbbbbbbb = blink b times
 * 
 */
static uint8_t led_program[8];

void LED_init(uint8_t led) {
  LED_DDR |=(1<<led);
  led_mask|=(1<<led);
  LED_off(led);
}

void LED_blink(uint8_t led, uint8_t count, uint8_t flags) {
  led_program[led]=count| flags; 
  led_count[led]=0;
}

void LED_on(uint8_t led) {
  led_program[led]=0xff; 
  led_count[led]=0;
} 

void LED_off(uint8_t led) {
  led_program[led]=0; 
  led_count[led]=0;
}

void LED_irq(void) {
  uint8_t i;
  
  led_counter++;
  if(led_counter==12) {
    led_counter=0;
    for(i=0;i<8;i++) {
      if(led_mask&(1<<i)) {
        switch(led_program[i]) {
          case 0xff:  //LED on
            LED_PORT|=(1<<i);
            break;
          case 0x00:  // LED off
            LED_PORT&=(uint8_t)~(1<<i);
            break;
          default:  // LED blink
            if(LED_PORT&(1<<i)) {
              LED_PORT&=(uint8_t)~(1<<i);
            } else {
              led_count[i]++;
              if(led_count[i]<=(led_program[i]&LED_COUNT_MASK)) {
                LED_PORT|=(1<<i);
              } else if(led_program[i]&LED_FLAG_END_ON) {
                LED_PORT|=(1<<i);
                led_program[i]=0xff;
              }
            }
        }
      }
    }
  }
}