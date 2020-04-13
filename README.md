Logging Temperature & Humidity and logging it in a Google spreadsheet in the cloud
==================================================================================

Boards used:
* Adafruit Si7021
* ESP32 TTGO T8 v1.7.1

Good information about sensor (also check other subpages):
https://learn.adafruit.com/adafruit-si7021-temperature-plus-humidity-sensor/overview

How to use
==========

Connect Si7021 to ESP32
-----------------------

i2C pins on the esp:
* SDA = 21
* SCL = 22

Connect 5V of the ESP to the Vin of the Si7021.
The 3V pin is an output pin (up to 100mA).

Download VSCode and install platformio package
----------------------------------------------

Follow this video to flash your device.
https://www.youtube.com/watch?v=qbETf0c3jZM

Create google spreadsheet
---------------------------

There is a script here called googleScripts.gs
It was adjusted from this video:
https://www.youtube.com/watch?v=fS0GeaOkNRw

Follow the instructions in the video to see how to set it up.
Note: If you want to update the script, I always had to select a new version, otherwise nothing happened.

Set up Environment.hpp
----------------------

Take EnvironmentTemplate.hpp and rename it to Environment.hpp.
Fill in the missing values:
- wifi ssid
- wifi password
- google app service id

That should be everything, have fun. :)