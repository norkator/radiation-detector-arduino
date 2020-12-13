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
* 
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
    cpm=924;uSv/h=7.5029
    cpm=780;uSv/h=6.3336
    cpm=816;uSv/h=6.6259
  */


// Pins
const int GEIGER_COUNTER_PIN = 3;

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

  // Init pins
  pinMode(GEIGER_COUNTER_PIN, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(GEIGER_COUNTER_PIN), tick, FALLING); //define external interrupts
  Serial.println("Init arduino geiger counter");
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
