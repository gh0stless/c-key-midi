/*
    C=Key - Commodore <-> PS/2 Interface
    Copyright Jim Brain and RETRO Innovations, 2004-2011

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    config.h: User-configurable options to simplify hardware changes and/or
              reduce the code/ram requirements of the code.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "autoconf.h"

#define PS2_ENABLE_HOST
#define PS2_ENABLE_DEVICE
#define KB_SCAN_PORTS     // scan the KB ports for joystick activity

#ifndef TRUE
#define FALSE                 0
#define TRUE                  (!FALSE)
#endif

// log2 of the PS2 buffer size, i.e. 6 for 64, 7 for 128, 8 for 256 etc.
#define PS2_RX_BUFFER_SHIFT   3
#define PS2_TX_BUFFER_SHIFT   3

#define ENABLE_UART0
// log2 of the UART buffer size, i.e. 6 for 64, 7 for 128, 8 for 256 etc.
#define UART0_TX_BUFFER_SHIFT  3
//#define UART0_RX_BUFFER_SHIFT  3
#define UART0_BAUDRATE CONFIG_UART_BAUDRATE

#if CONFIG_HARDWARE_VARIANT == 1

#define MODE_DETECT       (PIND & (1 << PIN4))
#define RESET_INIT()      do {PORTD |= (1 << PIN5); } while(0)
#define RESET_ON()        do {DDRD |= (1 << PIN5); PORTD &= (uint8_t)~(1 << PIN5); } while(0)
#define RESET_OFF()       do {DDRD &= (uint8_t)~(1 << PIN5); PORTD |= ~(1 << PIN5); } while(0)

#define KB_ROW_HI_OUT     PORTB
#define KB_ROW_HI_IN      PINB
#define KB_ROW_HI_DDR     DDRB
#define KB_ROW_LO_OUT     PORTC
#define KB_ROW_LO_IN      PINC
#define KB_ROW_LO_DDR     DDRC
#define KB_COL_OUT        PORTA
#define KB_COL_IN         PINA
#define KB_COL_DDR        DDRA

#define PS2_CLK_DDR       DDRD
#define PS2_CLK_OUT       PORTD
#define PS2_CLK_IN        PIND
#define PS2_CLK_PIN       _BV(PD3)
#define PS2_DATA_DDR      DDRD
#define PS2_DATA_OUT      PORTD
#define PS2_DATA_IN       PIND
#define PS2_DATA_PIN      _BV(PD2)

#define PORT_SW_OUT       PORTE
#define PORT_SW_IN        PINE
#define PORT_SW_DDR       DDRE

#define XPT_PORT_DATA_OUT   PORTB
#define XPT_DDR_DATA        DDRB
#define XPT_PORT_STROBE_OUT PORTD
#define XPT_DDR_STROBE      DDRD

#define XPT_PIN_STROBE (1<<PIN6)

#define SW_4080         PIN1
#define SW_CAPSENSE     PIN0
#define SW_RESTORE      PIN2

#endif

#ifdef CONFIG_DEBUG_DATA
#define debug(x)          uart_putc(x)
#else
#define debug(x)          do {} while(0)
#endif

#endif /*CONFIG_H*/
