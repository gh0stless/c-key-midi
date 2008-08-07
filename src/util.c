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
#include <inttypes.h>
#include <avr/eeprom.h>
#include "util.h"

void update_eeprom(void* address,uint8_t data) {
  uint8_t tmp;
  
  while(!eeprom_is_ready());
  tmp=eeprom_read_byte(address);
  if(tmp!=data)
  while(!eeprom_is_ready());
  eeprom_write_byte(address,data);
}

