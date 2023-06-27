/* Libraries for the OLED display, This code uses Adafruit Library */
#include <Wire.h>
#include <Adafruit_SSD1306.h>

const int buzzer = 3;   // pin 3 for buzzer 
const int button1 = 7;  // pin 7 for button 1
const int button2 = 8;  // pin 8 for button 2
const int ledPin = 10;  // pin 10 for LED

/* connection details of the OLED */
// OLED{GND, VCC, SCL, SDA}  = Arudion{GND, 5V, A5, A4} 

int button1State = 0;
int button2State = 0;
bool ledState = false;     // a variable to track if the LED (and siren) is on

/* The following texts will be used to simulate the VAULT door in OLED */
String text1 = "VAULT DOOR IS CLOSED";
String text3 = "VAULT DOOR IS OPEN";

#define SCREEN_WIDTH 128  // OLED display width,  in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define NOTE_DS4 311      // Note for the buffer to ring

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Now creating a melody:
int melody[] = {NOTE_DS4, NOTE_DS4};
int noteDurations[] = {1, 1};       // note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:

void setup() {
  pinMode(button1, INPUT_PULLUP);   // set the button pin as input with a pull-up resistor
  pinMode(button2, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);          // set the LED pin as output
  // Serial.begin(9600);            // was used for testing before implementing OLED
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
}

void loop() {
  button1State = digitalRead(button1);  // reading the state of button 1 and 2 
  button2State = digitalRead(button2);
  
  if (button1State == LOW && button2State == LOW){ // if both buttons are pressed and the LED is not already on    
   
    while (button2State == LOW | button1State == LOW){ //for some reason A OR B != B OR A
      /* Serial print Implemented in the test phase
      Serial.println("");
      Serial.println("Both buttons are pressed.");
      Serial.println("LED is turned on!"); */
      
      oled.clearDisplay();         // clear display
      oled.setTextSize(1.5);       // text size
      oled.setTextColor(WHITE);    // text color
      oled.setCursor(5, 30);       // position to display
      oled.println(text3);         // text to be printed
      oled.display();
      tone(buzzer, 311, 500);         // play a note D#4 = 311 note for 500ms
      ledState = !ledState;           // toggles the led state
      digitalWrite(ledPin, ledState); // 
      delay(500);
      button1State = digitalRead(button1);
      button2State = digitalRead(button2);
    }
  
  } 
    
  else if (button1State == HIGH & button2State == HIGH){ //& ledState){ 
    // if the button is released and the LED is on    
    /*Serial.println("");
    Serial.println("Both buttons are released.");
    Serial.println("LED is off!");*/
    oled.clearDisplay();         // clear display
    oled.setTextSize(1.5);       // text size
    oled.setTextColor(WHITE);    // text color
    oled.setCursor(5, 30);       // position to display
    oled.println(text1);         // text to be printed
    oled.display();

    digitalWrite(ledPin, LOW); // turn off the LED
    ledState = false; // set ledOn to false to indicate that the LED is off
      
  } 
}
