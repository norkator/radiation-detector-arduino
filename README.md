# Radiation Detector
Arduino code for Nitramite Nuclear Radiation Detector Android application. 
This repository exists so that app users can get code, open issues and make contributions.

To get started see [firmware versions](#firmware-versions) part or look table of contents for more.

Table of contents
=================
* [Related links](#related-links)
* [Firmware versions](#firmware-versions)
* [Hardware schematic](#schematic)
* [Oled screen support (optional)](#oled-screen-support)
    * [Module](#module)
    * [Pinouts](#pinouts)
    * [Required libraries](#required-libraries)
    * [More information](#more-information)
    * [Real life image](#real-life-image)
* [Fritzing parts (for schematic drawing)](#fritzing-parts)



Related links
============
[Android Application](https://play.google.com/store/apps/details?id=com.nitramite.radiationdetector)  
[Web page](http://www.nitramite.com/radiation-detector.html)  
[Youtube promo video](https://youtu.be/VzV9t7CP7Yc)  


Firmware Versions
============
To use only basic Geiger counter, Bluetooth module and Arduino combo, just download 
[basic first version code relase 1.0.0](https://github.com/norkator/radiation-detector-arduino/archive/1.0.0.zip).

To support oled screen or any other future hardware, download 
[current main branch code](https://github.com/norkator/radiation-detector-arduino/archive/main.zip).


Schematic
============
Repository has updated Schematic made with Fritzing. Some more information could be found 
[from here](http://www.nitramite.com/radiation-detector.html).

![Schematic](./schematic.png) 


Oled screen support
============
Here is some information about Oled screen support.

Module
-----
SSD1306 Oled

Pinouts
-----
* SDA -> A4 (i2c)
* SCL -> A5 (i2c)
* GND -> Ground
* VDD -> 5v (Screen pin labeled as VCC or VDD)

Required libraries
-----
* Adafruit BusIO
* Adafruit-GFX-Library
* Adafruit_SSD1306

More information
-----
Good tutorial:  
https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/

Real life image
-----
![OledScren](./i2c_screen.jpg) 


Fritzing parts
============
Custom parts which may not be found from Fritzing by default

* [HC-06 module](https://github.com/RafaGS/Fritzing/blob/master/Bluetooth%20HC-06.fzpz)  
* [Oled Screen](https://ajcreatif.com/oled_128x64_I2C_monochrome_display.fzpz)  
