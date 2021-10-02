  
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

const int SWCount = 4;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
SWCount, 2,
true, true, true, 
false, false, false, 
false, true,
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

int ShootSpeedPin = A4;
int ShootSpeedMax = 1023;
int ShootSpeedMin = 0;
int ShootOffPin = A5;
int ShootOffMax = 1023;
int ShootOffMin = 0;

//int climbAllowPin = 4;
//int climbLastState = 0;
//int climbButton = 0;
int SWPin [] = {4, 5, 6, 7};
int SWButton [] = {0, 1, 2, 3};
int SWLastState [] = {0, 0, 0, 0};
int iSWIndex = 0;

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
  Joystick.setZAxisRange(0,1023);
  Joystick.setThrottleRange(0,1023);

  //pinMode(climbAllowPin, INPUT_PULLUP);
  for (iSWIndex = 0; iSWIndex < SWCount; iSWIndex++) {
    pinMode(SWPin[iSWIndex], INPUT_PULLUP);
    Joystick.releaseButton(iSWIndex);
  }

  lcd.init();
  lcd.clear();
  lcd.setBacklight(255);
  
}                                 
  String strPosSwitchStatement = "V5 2021 9/2/2021";
  String strAutoCommand = "";
                                 
void loop() {
    lcd.home();

    int PosSwValue = analogRead(PosSwPin);
    int PosSwValue2 = analogRead(PosSwPin2);

    int PosSwPosition = (PosSwValue * PosSwSegments + PosSwMidPoint) / PosSwMax;
    int PosSwPosition2 = (PosSwValue2 * PosSwSegments2 + PosSwMidPoint2) / PosSwMax2;

    int TurnRate = map(analogRead(TurnRatePin), 0, 1023, TurnRateMin, TurnRateMax);
    int CameraAngle = map(analogRead(IntakeCameraPin), 0, 1023, IntakeCameraMin, IntakeCameraMax);
    int ShootSpeed = map(analogRead(ShootSpeedPin), 0, 1023, ShootSpeedMin, ShootSpeedMax);
    int ShootOff = map(analogRead(ShootOffPin), 0, 1023, ShootOffMin, ShootOffMax);

    //int currentClimbState = !digitalRead(climbAllowPin);
    //if (currentClimbState != climbLastState) {
    //    Joystick.setButton(climbButton, currentClimbState);
    //    climbLastState = currentClimbState;
    //}
    for (iSWIndex = 0; iSWIndex < SWCount; iSWIndex++) {
    int SWCurrState = !digitalRead(SWPin[iSWIndex]);
    if (SWCurrState != SWLastState[iSWIndex]) {
      Joystick.setButton(SWButton[iSWIndex], SWCurrState);
      SWLastState[iSWIndex] = SWCurrState;
    }
    //sprintf(SWLine,"%1u%1u", SWButton[iSWIndex], SWLastState[iSWIndex]);
    //strcat(println[3], SWLine);
  }
   
    lcd.print("Swtch:");

    String strStartPos = "one    ";
    String strStartPos2 = "one    ";

    switch(PosSwPosition){
        case 0:
            strStartPos2 = "left   ";
            break;
        case 1:
            strStartPos2 = "middle ";
            break;
        case 2:
            strStartPos2 = "right  ";
            break;
        case 3:
            strStartPos2 = "unk    ";
            //break;
        case 4:
            strStartPos2 = "unk     ";
            //break;
        case 5:
            strStartPos2 = "unk     ";
        default:    
            //break;
            strStartPos2 = "unknown";
    }

    switch(PosSwPosition2){
        case 0:
            strStartPos = "zero   ";
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
            break;    
        default:
            strStartPos = "unknown";
    }

    //strAutoCommand = PosPatMap[PosSwPosition2][PosSwPosition];

   lcd.setCursor(6,0);
   lcd.print(strStartPos);
   lcd.print(strStartPos2);
   lcd.setCursor(0,1);
   //lcd.print(strAutoCommand);
   lcd.setCursor(0, 2);
   lcd.print("Turn:");
   lcd.print(TurnRate);
   lcd.print("   ");
   lcd.setCursor(12, 2);
   lcd.print("Cam:");
   lcd.print(CameraAngle);
   lcd.print("   ");
   lcd.setCursor(0,3);
   lcd.print("Shooter:");
   lcd.print(ShootSpeed);
   lcd.print(" ");
   lcd.print(ShootOff);
   lcd.print("   ");

   Joystick.setHatSwitch(0, PosSwPosition*45);
   Joystick.setHatSwitch(1, PosSwPosition2*45);
   Joystick.setXAxis(TurnRate);
   Joystick.setYAxis(CameraAngle);
   Joystick.setZAxis(ShootSpeed);
   Joystick.setThrottle(ShootOff);

   delay(20);
  
}