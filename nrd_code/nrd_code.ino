/**
* Arduino radiation Geiger counter Project
* Coding started 15.06.2019
* Code constructed from various sources to archieve CPM and uSv/h counts
* Transforming CPM (Counts per minute) to uSV/h here at Arduino side
* Send reading to front end via bluetooth every 10 sec
*
* Changelog
* # 15.06.2019, Initial code
* # 16.06.2019, Added Serial.println("t;"); to play sound on Android app
* # xx.12.2020, Week 51, Added code for i2c screen support, requested by user 
*/

/**
 * ### Chart ##
 * CPM    uSv/hr    Description
 * ------------------------------------
 * 12     0.10      Average background
 * 25     0.21      World average
 * 50     0.42      Normal on short duration
 * 60     0.5       Larger peak of short duration
 * 100    0.83      Larger peak of longer duration
 * 150    1.25      Getting into dangerous area
 * 500    4.17      Dangerous, leave immediately!
 */

 /**
  * Sample output
  * cpm=924;uSv/h=7.5029
  * cpm=780;uSv/h=6.3336
  * cpm=816;uSv/h=6.6259
  */

/* 
 *  Oled screen support
 *  To enable following screen support you need to install libs: "Adafruit BusIO", "Adafruit-GFX-Library" and "Adafruit_SSD1306"
 *  Display pins:
 *     SDA -> A4 (i2c)
 *     SCL -> A5 (i2c)
 *     GND -> Ground
 *     VDD -> 5v (Screen pin labeled as VCC or VDD)
 */
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include <Wire.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// Pins
const int GEIGER_COUNTER_PIN = 3;
unsigned long OLED_SCREEN_I2C_ADDRESS = 0x00; // 0x00 = disabled

// Variables
long count = 0;
long countPerMinute = 0;
float usvh = 0.0;
long timePreviousMeassure = 0;

// Conversion factor - CPM to uSV/h
#define CONV_FACTOR 0.00812

// Setup
void setup() {  

  // Init serial
  Serial.begin(9600);

  delay(2000);

  // Init pins
  pinMode(GEIGER_COUNTER_PIN, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(GEIGER_COUNTER_PIN), tick, FALLING); //define external interrupts
  Serial.println("Init arduino geiger counter");

  OLED_SCREEN_I2C_ADDRESS = findOledScreen();
  if (OLED_SCREEN_I2C_ADDRESS != 0x00) {
    // Just note, every tutorial screen has same address, 0x3C
    Serial.println("--> " + OLED_SCREEN_I2C_ADDRESS);
    display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_I2C_ADDRESS);
    display.clearDisplay();
  }
}


// Loop
void loop() {
  if (millis() - timePreviousMeassure > 10000){
    countPerMinute = 6 * count;
    usvh = countPerMinute * CONV_FACTOR;
    timePreviousMeassure = millis();
    Serial.print("cpm="); 
    Serial.print(countPerMinute, DEC);
    Serial.print(";"); 
    Serial.print("uSv/h=");
    Serial.println(usvh, 4);
    writeOledScreenText((String) countPerMinute, (String) usvh); // Todo, verify this
    count = 0;
  }
}


void tick() {
  Serial.println("t;");
  detachInterrupt(0);
  count++;
  while(digitalRead(GEIGER_COUNTER_PIN) == 0){
  }
  attachInterrupt(0, tick, FALLING);
}


/**
 * Find first responding i2c address
 * because we only have one i2c device connected (hopefully)
 */
long findOledScreen() {
  Serial.println ("Scanning for I2C Oled screen.");
  byte count = 0;
  Wire.begin();
  for (byte i = 1; i < 127; i++) {
    // Serial.println("Scanning " + i);
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0) {
           
      Serial.print("Found i2c address: ");
      Serial.print(i, DEC);
      Serial.print(" | ");
      Serial.println(i, HEX);
      
      return i;

      count++;
      delay (1); 
      } 
  }
  return 0x00;
}


/**
 * Write oled screen content
 * Good tutorial: https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/
 */
void writeOledScreenText(String cpm, String usvh) {
  if (OLED_SCREEN_I2C_ADDRESS != 0x00) {
    display.clearDisplay();

    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("CPM | uSv/h");
    display.setTextSize(2);
    display.setCursor(0,10);
    display.print(cpm);
    display.print(" | ");
    display.print(usvh);

    // Draw content
    display.display();
  }
}
