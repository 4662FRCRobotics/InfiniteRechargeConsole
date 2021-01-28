  
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
true, true, false, 
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

int TurnRatePin = A2;
int TurnRateMax = 1023;
int TurnRateMin = 0;

int IntakeCameraPin = A3;
int IntakeCameraMax = 1023;
int IntakeCameraMin = 0;

String PosPatMap[6][6] = {
    {"X Auto              ", "X Auto              ", "X Auto              ", "-                   ", "-                   ", "-                   "},
    {"Shoot + X           ", "Shoot + X           ", "Shoot + X           ", "-                   ", "-                   ", "-                   "},
    {"Shoot + X           ", "Shoot + X + Wheel   ", "Shoot + X + Wheel   ", "-                   ", "-                   ", "-                   "},
    {"Shoot + X           ", "Shoot + X           ", "Shoot+Collect+Shoot ", "-                   ", "-                   ", "-                   "},
    {"-                   ", "-                   ", "-                   ", "-                   ", "-                   ", "-                   "},
    {"-                   ", "-                   ", "-                   ", "-                   ", "-                   ", "-                   "}
};

void setup() {
  // put your setup code here, to run once:

  Joystick.begin();
  Joystick.setXAxisRange(0,1023);
  Joystick.setYAxisRange(0,1023);
  
  lcd.init();
  lcd.clear();
  lcd.setBacklight(255);
  
}                                 
  String strPosSwitchStatement = "V4 2021 1/18/2021";
  String strAutoCommand = "";
                                 
void loop() {
    lcd.home();

    int PosSwValue = analogRead(PosSwPin);
    int PosSwValue2 = analogRead(PosSwPin2);

    int PosSwPosition = (PosSwValue * PosSwSegments + PosSwMidPoint) / PosSwMax;
    int PosSwPosition2 = (PosSwValue2 * PosSwSegments2 + PosSwMidPoint2) / PosSwMax2;

    int TurnRate = map(analogRead(TurnRatePin), 0, 1023, TurnRateMin, TurnRateMax);
    int CameraAngle = map(analogRead(IntakeCameraPin), 0, 1023, IntakeCameraMin, IntakeCameraMax);
   
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
        case 3:
            strStartPos2 = "four   ";
            break;
        case 4:
            strStartPos2 = "five    ";
            break;
        case 5:
            strStartPos2 = "Six     ";
        default:    
            break;
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
        case 3:
            strStartPos = "four   ";
            break;
        case 4:
            strStartPos = "five    ";
            break;
        case 5:
            strStartPos = "Six     ";     
        default:
            strStartPos = "unknown";
    }

    strAutoCommand = PosPatMap[PosSwPosition2][PosSwPosition];

   lcd.setCursor(10,0);
   lcd.print(strStartPos);
   lcd.setCursor(10,1);
   lcd.print(strStartPos2);
   lcd.setCursor(0, 2);
   lcd.print("Auto Pattern:");
   lcd.setCursor(0, 3);
   lcd.print(strAutoCommand);

   Joystick.setHatSwitch(0, PosSwPosition*45);
   Joystick.setHatSwitch(1, PosSwPosition2*45);
   Joystick.setXAxis(TurnRate);
   Joystick.setYAxis(CameraAngle);
  
}