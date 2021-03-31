/* @file 30_Button_Keypad_plus_WASD_Joystick_dannerbam.ino
  || @version 1.0
  || @author dannerbam
  || @contact office@dannerbam.at
  ||
  || @description
  || | Ein Keypad mit WASD Joystick.
  || #
*/

#include <Keypad.h>
#include <Keyboard.h>
#include <HID_Buttons.h>  // Must import AFTER Keyboard.h

const uint8_t Pin_XAxis = A3;  // Pin for joy horizontal axis
const uint8_t Pin_YAxis = A2;  // Pin for joy vertical axis

const int JoyCenter   = 1023 / 2;  // max value for 10-bit ADC / 2
const int JoyDeadzone = 50;        // +/- area around the center to ignore

KeyboardButton moveForward('w');
KeyboardButton moveLeft('a');
KeyboardButton moveBackward('s');
KeyboardButton moveRight('d');

const byte ROWS = 6; //6 rows
const byte COLS = 5; //5 columns


//define the chars on the buttons of the keypad
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3','X'},
  {'4','5','6','7','P'},
  {'8','9','U','B','Q'},
  {'C','W','E','F','R'},
  {'G','H','I','J','V'},
  {'K','L','M','N','T'}
 };
 
byte rowPins[ROWS] = {15, 14, 19, 18, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 8, 7, 6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  customKey();
  joystick();
}

void customKey(void){
  char customKey = customKeypad.getKey();
  
    if (customKey) {
    //Serial.println(customKey);
    Keyboard.write(customKey);
    }
}

void joystick(void){
  int x = analogRead(Pin_XAxis);  // Read X axis
  int y = analogRead(Pin_YAxis);  // Read Y axis

  moveLeft.set(x < JoyCenter - JoyDeadzone);
  moveRight.set(x > JoyCenter + JoyDeadzone);

  moveForward.set(y < JoyCenter - JoyDeadzone);
  moveBackward.set(y > JoyCenter + JoyDeadzone);
}
