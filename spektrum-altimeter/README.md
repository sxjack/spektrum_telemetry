# Spektrum Telemetry Altimeter

## Bill of Material

* Arduino Pro Mini 3.3V
* BMP280 module
* 4 pin JST-ZH pigtail

## Tools

* Arduino IDE
* Arduino ISP programmer. I use a USBasp.

## Build<

* Solder headers on to the Arduino to allow it to be programmed though its ISP interface.
You have to program it using the ISP as if you have a bootloader on the chip it will not be ready when 
the Spektrum TM1000 (or telemetry receiver) enumerates the bus.
* Solder the JST-ZH pigtail to the Arduino
  * Common to GND
  * Servo Bus +V to RAW
  * SCL to A5
  * SDA to A4
* Connect the BMP280 to the Arduino -
  * VCC to VCC
  * GND to GND
  * SCL to A1
  * SDA to A0
  * CSB to VCC
  * SDO to GND
* Program the Arduino with the hex file.
* Inspect and test the board.
* Clean off any flux residue, strain relieve the wires with some gobs of silicon
and put some clear heatshrink over the Arduino.

## Notes

* The command to write the hex file to the Arduino will be something like:
>"C:\Program Files\Arduino\hardware\tools\avr\bin\avrdude" "-CC:\Program Files\Arduino\hardware\tools\avr\etc\avrdude.conf" -v -patmega328p -cstk500v1 -PCOM3 -b19200 -Uflash:w:spektrum_altimeter.hex:i

## Resources</h3>

* [Specification for Spektrum X-Bus Telemetry Sensors](https://www.spektrumrc.com/ProdInfo/Files/SPM_Telemetry_Developers_Specs.pdf)
* [Arduino Pro Mini 3.3V](https://www.banggood.com/3_3V-8MHz-ATmega328P-AU-Pro-Mini-Microcontroller-Board-With-Pins-p-916211.html)
* [BMP280 module](https://www.banggood.com/3Pcs-GY-BMP280-3_3-High-Precision-Atmospheric-Pressure-Sensor-Module-For-Arduino-p-1113782.html)
