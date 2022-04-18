#include <Servo.h>

//SETTINGS
//servo
int startAngle = 85;//больше число - ниже опускается
int stopAngle = 10; //меньше число - выше поднимается
int delayMilisec = 10;
int servoPin = 6; //D6

//distance sensor
int distanceSensorPin = A7;

Servo servo;


void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(startAngle);  
  delay(2000);  
  pinMode(distanceSensorPin, INPUT);
}

bool isInitiated = false;
void loop() 
{
  if(getSensorValue())
  {
    openCap();
    while(getSensorValue()){}//ждём пока уберёт руку
    delay(2000); //после того как убрали руку задержка
  }
  else
  {
    if(!isInitiated) //при первом запуске не закрывать
    {
      isInitiated = true;  
    }
    else
    {
      closeCap();
    }
    while(!getSensorValue())//ждём пока поднесёт руку
    {
      delay(10);
    }
  }
}

bool getSensorValue()
{
  int sum = 0;
  for(int i=0;i<10;i++)
  {
    sum += digitalRead(distanceSensorPin);
  }
  return sum == 0;
}

void closeCap()
{
  Serial.println("Close cap");
  for(int i=stopAngle;i<=startAngle;i++)
  {
    servo.write(i);    
    delay(delayMilisec);                 
  }
}

void openCap()
{
  Serial.println("Open cap");
  for(int i=startAngle;i>=stopAngle;i--)
  {
    servo.write(i);    
    delay(delayMilisec/2);                 
  }
}
