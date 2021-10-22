# Spektrum Telemetry GPS/Vario

## Bill of Material

* Arduino Pro Mini 3.3V 8Hz
* GPS module
* MS5611 module
* 4 pin JST-ZH pigtail

The GPS module needs to be one that can be programmed to output NMEA GGA and RMC at 38400 baud. 
A link to one that I have used is below.

## Tools

* Arduino IDE
* Arduino ISP programmer. I use an Arduino Nano or USBasp.
* U-blox u-center (optional).
* FTDI USB to TTL serial interface (optional).

## Build

* Solder headers on to the Arduino to allow it to be programmed though its ISP interface. You have to program it using the ISP as if you have a bootloader on the chip it will not be ready when 
the Spektrum TM1000 (or telemetry receiver) enumerates the bus.
* Solder the JST-ZH pigtail to the Arduino:
  * Common to GND
  * Servo Bus +V to RAW
  * SCL to A5
  * SDA to A4
* Solder the wires from the GPS to the Arduino:
  * G to GND
  * V to VCC
  * T to RXI
  * R to TXO
* Solder the wires from the MS5611 module to the Arduino:
  * GND to GND
  * VCC to VCC
  * SDA to A0
  * SCL to A1
* Make the following connections on the MS5611 module:
  * GND to CSB
  * VCC to PS
* Inspect and test the board.
* Program the Arduino with the hex file.
* Clean off any flux residue, strain relieve the wires with some gobs of silicon
and put some clear heatshrink over the Arduino and MS5611 module being careful not to block the 
holes on the MS5611.

## Notes

* The sketch should program the GPS on startup.
* Diagnostics (including VDOP and HDOP) transmitted using TEXTGEN.
* The command to write the hex file to the Arduino will be something like:
>"C:\Program Files\Arduino\hardware\tools\avr\bin\avrdude" "-CC:\Program Files\Arduino\hardware\tools\avr\etc\avrdude.conf" -v -patmega328p -cstk500v1 -PCOM3 -b19200 -Uflash:w:spektrum_gps_vario_diag.hex:i

## Resources

* [Specification for Spektrum X-Bus Telemetry Sensors](https://www.spektrumrc.com/ProdInfo/Files/SPM_Telemetry_Developers_Specs.pdf)
* [Arduino Pro Mini 3.3V](https://www.banggood.com/3_3V-8MHz-ATmega328P-AU-Pro-Mini-Microcontroller-Board-With-Pins-p-916211.html)
* [Geekcreit 5Hz GPS](https://www.banggood.com/1-5Hz-VK2828U7G5LF-TTL-Ublox-GPS-Module-With-Antenna-p-965540.html)
* [MS5611 module](https://www.banggood.com/MS5611-GY-63-Atmospheric-Pressure-Sensor-Module-IICSPI-Communication-p-965980.html)

