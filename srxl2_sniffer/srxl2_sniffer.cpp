/* -*- tab-width: 2; mode: c; -*-
 * 
 * C++ class for detecting Spektrum SRXL2.
 *
 * Copyright (c) 2022 Steve Jack
 *
 *
 * Notes
 *
 *
 *
 *
 *
 */

#include <Arduino.h>

#pragma GCC diagnostic warning "-Wunused-variable"

#include "srxl2_sniffer.h"

/*
 *
 */

SRXL2_Sniffer::SRXL2_Sniffer() {

  memset(channel_value,0,sizeof(channel_value));

  srxl2_detected  =    0;

  Debug_Serial    = NULL;
  srxl2           = NULL;
  
  return;
}

/*
 *
 */

unsigned long int SRXL2_Sniffer::begin(HardwareSerial *serial) {

  srxl2_detected = 0;
  srxl2          = serial;

  srxl2->begin(115200,SERIAL_8N1);
  
  return 1;
}

/*
 *
 */

uint16_t SRXL2_Sniffer::sniffer() {

  int              len, i;
  uint8_t          c, crc_l, crc_h;
  static int       rx_index = 0;
  static uint8_t   rx_buffer[SRXL2_RX_SIZE];

  
  for (i = 0; (i < 32)&&(srxl2->available()); ++i) {

    c = rx_buffer[rx_index] = srxl2->read();

    if ((rx_index)||((rx_index == 0)&&(c == 0xa6))) {

      if (++rx_index > (SRXL2_RX_SIZE - 3)) {

        rx_index = 0;
      }
    }

    if ((rx_index > 4)&&(rx_index == (len = (int) rx_buffer[2]))) {
      
      checksum(rx_buffer,len - 2,&crc_h,&crc_l);

      if ((crc_h == rx_buffer[len - 2])&&(crc_l == rx_buffer[len - 1])) {

        // We have a valid packet.

        srxl2_detected = 1;
        
        switch (rx_buffer[1]) {

          case 0xcd: // control data

            if (rx_buffer[3] == 0x00) {

              int      j, k, channel = 0, offset = 12;
              uint8_t  mask;

              for (j = 0; j < 4; ++j) {

                mask = rx_buffer[8 + j];

                for (k = 0; (k < 8)&&(offset < len); ++k, ++channel) {

                  if ((mask >> k) & 0x01) {

                    channel_value[channel] = (rx_buffer[offset] >> 5) | (rx_buffer[offset + 1] <<  3);

                    offset += 2;
                  }
                }
              }
            }
 
            break;

          default:
            break;
        }
      }

      rx_index = 0;
    }
  }

#if CHECK_THROTTLE
  return channel_value[0];
#else
  return (uint16_t) srxl2_detected;
#endif
}

/*
 *
 */

uint16_t SRXL2_Sniffer::channel(int index) {

  return ((index > 0)&&(index < 33)) ? channel_value[index - 1]: 0;
}

/*
 *
 */

void SRXL2_Sniffer::debug(Stream *D) {

  Debug_Serial = D;

  return;
}

/*
 *
 */

void SRXL2_Sniffer::checksum(uint8_t *data,int length,uint8_t *high,uint8_t *low) {

  int      i, j;
  uint16_t crc;

  for (crc = 0, j = 0; j < length; ++j) {
  
    crc ^= ((uint16_t) data[j] << 8);
            
    for(i = 0; i < 8; ++i) {
      
      if (crc & 0x8000) {
        
        crc = (crc << 1) ^ 0x1021;

      } else {

        crc = crc << 1;
      }
    }
  }

  *low  = (uint8_t) crc;
  *high = (uint8_t) (crc >> 8);
  
  return;
}

/*
 *
 */
