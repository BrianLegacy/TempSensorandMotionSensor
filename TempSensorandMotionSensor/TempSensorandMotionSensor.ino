/*
 Name:		TempSensorandMotionSensor.ino
 Created:	2/1/2018 7:59:19 PM
 Author:	Jcardif
*/

// include the library code:
#include <LiquidCrystal.h>


// initialize the library by associating any needed LCD interface pin with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//Assigning the analog pins
const int tempSensor = A1;

//Assigning digital pins
const int buzzer = 7;
const int fan = 8;
const int motionLED = 10;
const int motionSensor = 6;
const int tempLED = 13;


//declare all other variables
float tempValue; 
float vout;  
int motionValue ;

// the setup function runs once when you press reset or power the board
void setup()
{
	pinMode(tempSensor, INPUT); 
	pinMode(buzzer, OUTPUT);
	pinMode(motionSensor, INPUT);
	pinMode(fan, OUTPUT);
	pinMode(motionLED, OUTPUT);
	pinMode(tempLED, OUTPUT);
	Serial.begin(9600);
	delay(500);

	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	vout = analogRead(tempSensor);
	motionValue = digitalRead(motionSensor);
	tempValue = (vout * 500) / 1023; // Storing value in Degree Celsius

	lcd.setCursor(0, 1);
	lcd.print(tempValue);
	lcd.print(char(223));
	lcd.print("C");

	if (tempValue>30)
	{
		digitalWrite(buzzer, HIGH);
		digitalWrite(tempLED, HIGH);
		delay(500);
		digitalWrite(buzzer, LOW);
		digitalWrite(tempLED, LOW);
		delay(500);
	}
	if (motionValue != 0)
	{
		digitalWrite(motionLED, HIGH);
		digitalWrite(fan, HIGH);
		if ( motionValue != 0 && tempValue>20)
		{
			digitalWrite(buzzer, HIGH);
			//delay(100);
		}
		lcd.setCursor(0, 0);
		lcd.print("Motion Present!");
		delay(1500);
		lcd.clear();
	}
	else if (motionValue == 0)
	{
		digitalWrite(motionLED, LOW);
		digitalWrite(fan, LOW);
		if (motionValue != 0 && tempValue>20)
		{
			digitalWrite(buzzer, LOW);

		}
		lcd.setCursor(0, 0);
		lcd.print("Motion absent!");
		delay(1500);
		lcd.clear();
	}
	/*Serial.print("in DegreeC=");
	Serial.print("\t");
	Serial.print(tempValue);
	Serial.println();
	delay(1000);

	Serial.print(motion);
	Serial.println();
	delay(1000); //Delay of 1 second for ease of viewing
	*/
}
