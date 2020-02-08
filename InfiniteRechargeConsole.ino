  
#include <Joystick.h>
#include <LiquidCrystal_I2C.h>
/*
* name id 
* constant for type 
* number of buttons (limit 16 on drivestation) 
* number of POV hats (limit 2)
* x axis t/f 
* y axis t/f 
* z axis t/f 
* rudder / paddle / other names of no meaning to me 4 * t/f  
* throttle t/f 
* 3 * t/f 
* see arduino joystick on github for more info 
*/
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
0, 2,
false, false, false, 
false, false, false,  
false, false,
false, false, false);

LiquidCrystal_I2C lcd(0x3F, 20, 4);

int PosSwPin = A0;
int PosSwMax = 1023;
int PosSwMin = 0;
int PosSwSegments = 5;
int PosSwIncrement = PosSwMax / PosSwSegments;
int PosSwMidPoint = PosSwIncrement / 2;
int PosSwPosition = 0;
int PosSwPin2 = A1;
int PosSwMax2 = 1023;
int PosSwMin2 = 0;
int PosSwSegments2 = 5;
int PosSwIncrement2 = PosSwMax / PosSwSegments;
int PosSwMidPoint2 = PosSwIncrement / 2;
int PosSwPosition2 = 0;

void setup() {
  // put your setup code here, to run once:

  Joystick.begin();
  lcd.init();
  lcd.clear();
  lcd.setBacklight(255);
  
}                                 
  String strPosSwitchStatement = "V3 2/19/19";
                                 
void loop() {
    lcd.home();

    int PosSwValue = analogRead(PosSwPin);
    int PosSwValue2 = analogRead(PosSwPin2);

    int PosSwPosition = (PosSwValue * PosSwSegments + PosSwMidPoint) / PosSwMax;
    int PosSwPosition2 = (PosSwValue2 * PosSwSegments2 + PosSwMidPoint2) / PosSwMax2;
    
    lcd.print("StartPos:");
    lcd.setCursor(0,1);
    lcd.print("Pattern:");

    String strStartPos = "one    ";
    String strStartPos2 = "one    ";

    switch(PosSwPosition2){
        case 0:
            strStartPos2 = "one    ";
            break;
        case 1:
            strStartPos2 = "two    ";
            break;
        case 2:
            strStartPos2 = "three  ";
            break; 
        default :
            strStartPos2 = "unknown";
    }
    switch(PosSwPosition){
        case 0:
            strStartPos = "one    ";
            break;
        case 1:
            strStartPos = "two    ";
            break;
        case 2:
            strStartPos = "three  ";
            break; 
        default :
            strStartPos = "unknown";
    }
   lcd.setCursor(10,0);
   lcd.print(strStartPos);
   lcd.setCursor(10,1);
   lcd.print(strStartPos2);

   Joystick.setHatSwitch(0, PosSwPosition*45);
   Joystick.setHatSwitch(1, PosSwPosition2*45);
  
}