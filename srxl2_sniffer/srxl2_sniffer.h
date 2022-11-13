/* -*- tab-width: 2; mode: c; -*-
 *
 * C++ class for detecting Spektrum SRXL2.
 *
 * Copyright (c) 2022 Steve Jack
 *
 */

#ifndef SRXL2_SNIFFER_H
#define SRXL2_SNIFFER_H

#define SRXL2_RX_SIZE 82

#define SRXL_ID        0xa6

#define CONTROL_DATA   1
#define CHECK_THROTTLE 0

/*
 *
 */

class SRXL2_Sniffer {

  public:
                      SRXL2_Sniffer();
    unsigned long int begin(HardwareSerial *);
    uint16_t          sniffer(void);
    uint16_t          channel(int);
    void              debug(Stream *);

  private:

    void              checksum(uint8_t *,int,uint8_t *,uint8_t *);

    int               srxl2_detected;
    uint16_t          channel_value[32];
    Stream           *Debug_Serial;
    HardwareSerial   *srxl2;    
};

#endif

/*
 *
 */
