# Radiation Detector
Arduino code for Nitramite Nuclear Radiation Detector Android application. 
This repository exists so that app users can get code, open issues and make contributions.

### Related links
[Android Application](https://play.google.com/store/apps/details?id=com.nitramite.radiationdetector)  
[Web page](http://www.nitramite.com/radiation-detector.html)  
[Youtube promo video](https://youtu.be/VzV9t7CP7Yc)  

### Schematic
Repository has updated Schematic made with Fritzing

![Schematic](./schematic.png) 


### Oled screen support

Here is some information about Oled screen support.

#### Module
SSD1306 Oled

#### Pinouts
* SDA -> A4 (i2c)
* SCL -> A5 (i2c)
* GND -> Ground
* VDD -> 5v (Screen pin labeled as VCC or VDD)

#### Required libraries
* Adafruit BusIO
* Adafruit-GFX-Library
* Adafruit_SSD1306

#### More information
Good tutorial:  
https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/

#### Real life image
![OledScren](./i2c_screen.jpg) 