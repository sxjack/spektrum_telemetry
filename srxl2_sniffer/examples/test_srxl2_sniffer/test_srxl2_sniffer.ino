/* -*- tab-width: 2; mode: c; -*-
 * 
 * Program to sniff for Spektrum SRXL2 on a signal.
 * 
 * Steve Jack, November 2022
 * 
 * Notes
 *
 * 
 */

#include <Arduino.h>

#include "srxl2_sniffer.h"

SRXL2_Sniffer srxl2;

//

#if defined(ARDUINO_ARCH_AVR)

#define SERIAL_SRXL2   Serial

const int status_do = 13;

#elif defined(ARDUINO_RASPBERRY_PI_PICO)

#define SERIAL_SRXL2  Serial2
#define SERIAL_DEBUG   Serial

const int status_do = 25;

#elif defined(ARDUINO_RASPBERRY_PI_PICO_W)

// Why did they change the LED output on the Pico W?

#include <pico/cyw43_arch.h>

#define SERIAL_SRXL2  Serial2
#define SERIAL_DEBUG   Serial

#else

#warning "Not tested on this processor."

#define SERIAL_SRXL2 Serial

const int status_do = 13;

#endif

/*
 *
 */

void setup() {

  int      i;
  uint32_t status;

#if defined(SERIAL_DEBUG)

  SERIAL_DEBUG.begin(115200);
  srxl2.debug(&SERIAL_DEBUG);

#endif

  status = srxl2.begin(&SERIAL_SRXL2);

#if not defined(ARDUINO_RASPBERRY_PI_PICO_W)
  pinMode(status_do,OUTPUT);
  digitalWrite(status_do,LOW);
#endif

#if defined(SERIAL_DEBUG)

  SERIAL_DEBUG.print("\r\nsetup() returning.\r\n\n");
  
#endif

  return;
}

/*
 *
 */

void loop() {

  int             status;
#if defined(SERIAL_DEBUG)
  char            text[128];
  uint32_t        msecs;
  static uint32_t last_report = 0, header = 0;
#endif

  status = srxl2.sniffer();

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
  cyw43_arch_gpio_put(0,(status) ? HIGH: LOW);
#else
  digitalWrite(status_do,(status) ? HIGH: LOW);
#endif

#if defined(SERIAL_DEBUG)

  msecs = millis();

  if ((!header)&&(msecs > 999)) {

    sprintf(text,"\r\nSRXL2 Sniffer\r\n%s\r\n\n",__DATE__);
    SERIAL_DEBUG.print(text);

    header = 1;  
  } 
  
  if ((header)&&((msecs - last_report) > 99)) {

    sprintf(text,"\r %8lu %4d %4u %4u %4u %4u ",
            msecs,status,srxl2.channel(1),srxl2.channel(2),srxl2.channel(3),srxl2.channel(4));
    SERIAL_DEBUG.print(text);

    last_report = msecs;
  }

#endif

  return;
}

/*
 *
 */
