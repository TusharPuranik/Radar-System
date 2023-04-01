#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#include<wire.h>
#include<SPI.h>
Adafruit_SSD1306 display(-1);
const int led1=2;//green
const int led2=3;//red
const int led3=4;//blue
const int buzzer=5;
const int soundTriggerPin = 11;
const int soundEchoPin = 12;
const int startingAngle = 0;
const int minimumAngle = 0;
const int maximumAngle = 180;
const int rotationSpeed = 1;
int firstAngle;
int lastAngle;
int sizeOfObject;
int timer;

void setup(void) 
{
  Serial.begin(9600);
  pinMode(led3,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(soundTriggerPin, OUTPUT);
  pinMode(soundEchoPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC , 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  
}
void loop(void)
{
    static int motorAngle = startingAngle;
    static int motorRotateAmount = rotationSpeed;
    int distance=CalculateDistance();
    delay(10);
    SerialOutput(motorAngle, CalculateDistance());
    motorAngle += motorRotateAmount;
    if(motorAngle <= minimumAngle || motorAngle >= maximumAngle) 
    {
        motorRotateAmount = -motorRotateAmount;
    }
    if(distance<=50)
        {
          timer++;
          sizeOfObject=timer;
        }
        else
        {
          timer=0;
          sizeOfObject=0;
        }
   oledMonitor(sizeOfObject);
}
void cd()
{
  display.clearDisplay();
}

void oledMonitor(int sizeOfObject)
{
   digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
 if(sizeOfObject<=5 && sizeOfObject>0)
  {
    cd();
    printing("Micro Object","No Problem");
    digitalWrite(led1,HIGH);
  }
  else if(sizeOfObject<=10 && sizeOfObject>5)
  {
    cd();
    printing("Mini Object","Good To Go");
    digitalWrite(led1,HIGH);
    delay(100);
    digitalWrite(led1,LOW);
  }
  else if(sizeOfObject>10 && sizeOfObject<=15)
  {
    cd();
    printing("Normal Object","Observe");
    digitalWrite(led3,HIGH);
  }
  else if(sizeOfObject>15 && sizeOfObject<=20)
  {
    cd();
    printing("Lev-1 Object","Be Careful");
    digitalWrite(led3,HIGH);
    delay(100);
    digitalWrite(led3,LOW);
     digitalWrite(buzzer,HIGH);
     delay(100);
    digitalWrite(buzzer,LOW);
  }
  else if(sizeOfObject>20 && sizeOfObject<=25)
  {
    cd();
    printing("Lev-2 Object","Risk");
    digitalWrite(led2,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);  
    digitalWrite(led2,LOW);
  }
  else if(sizeOfObject>25 && sizeOfObject<=30)
  {
    cd();
    printing("Lev-3 Object","High Risk");
    digitalWrite(led2,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
  }
  else if(sizeOfObject>30 && sizeOfObject<=35)
  {
    cd();
    printing("Lev-3 Object","Very High Risk");
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
     digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
  }
  else if(sizeOfObject>35)
  {
    cd();
    printing("Mega Object","Escape");
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
  }
}
void printing(String x,String y)
{
  display.setTextSize(1);
  display.setCursor(25,5);
  display.println(x);
  display.setCursor(25,20);
  display.println(y);
  display.display();
  
}
int CalculateDistance(void)
{
    //digitalWrite(soundTriggerPin, LOW);
    //delayMicroseconds(2);
    digitalWrite(soundTriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(soundTriggerPin, LOW);
      long duration = pulseIn(soundEchoPin, HIGH);
    float distance = duration * 0.017F;
    return int(distance);
}
void SerialOutput(const int angle, const int distance)
{
    String angleString = String(angle);
    String distanceString = String(distance);
    Serial.println(angleString + "," + distanceString);
}
