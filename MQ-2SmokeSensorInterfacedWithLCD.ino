#include <LiquidCrystal_I2C.h>


//indicates smoke level is above safe value
int redLed = 8;

//indicates smoke level is within the safe value
int amberLed = 10;

//indicates smoke level is well below safe value
int greenLed = 9;

int smokePin = A0;

LiquidCrystal_I2C lcd(0x27,16,2);

// Your threshold value
int criticalSensorThres = 150;
int norminalSensorThres = 130;
String level = "LEVEL : ";
String levelOutput = "";
String levelPrint = "";

void setup()
{
  lcd.begin();
  lcd.backlight();
  lcd.print("Stand by");
  
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(amberLed, OUTPUT);
  pinMode(smokePin, INPUT);
  Serial.begin(9600);
  
}

void loop() 
{
  
  int analogSensor = analogRead(smokePin);

  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  
  if (analogSensor > criticalSensorThres && analogSensor > norminalSensorThres)
  {
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
      digitalWrite(amberLed, LOW);
      
      lcd.setCursor(0,0);
      lcd.print("STATUS : CRITICAL");
      
      lcd.setCursor(0,1);
      lcd.print(" EVACUATE NOW! ");
      delay(1000);
   
  }
  else if(!(analogSensor > criticalSensorThres) && analogSensor > norminalSensorThres)
  {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(amberLed, HIGH);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("STATUS : STABLE");
        
        levelOutput = (String)analogSensor;
        levelPrint = level + levelOutput;
        lcd.setCursor(0,1);
        lcd.print(levelPrint);
        Serial.println(levelPrint);
        
        delay(1000);
   
  }
   else
  {
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, HIGH);
        digitalWrite(amberLed, LOW);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("STATUS : G00D");
        
        levelOutput = (String)analogSensor;
        levelPrint = level + levelOutput;
        lcd.setCursor(0,1);
        lcd.print(levelPrint);
        Serial.println(levelPrint);
        delay(1000);
   
  }

 
  delay(1000);
}
