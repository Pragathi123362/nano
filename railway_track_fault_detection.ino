    // Includes the PulseSensorPlaygr
#include <SoftwareSerial.h>
//#include <TinyGPS.h>
#include <TinyGPS++.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,7,8,9,10);
int Value=0,i=0;
    void getgps();                             // Otherwise leave the default "550" value. 
   void sendsms();                            

TinyGPSPlus gps;
//TinyGPS gps;
//SoftwareSerial ss(8,9);
float flat=0, flon=0;
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;
int x,y,c1=0,c2=0;
const int x_out = A0; /* connect x_out of module to A1 of UNO board */
const int y_out = A1; /* connect y_out of module to A2 of UNO board */
const int z_out = A2; /* connect z_out of module to A3 of UNO board */
String msg;
int m = 10;
int trigPin = 13;//Trig – green Jumper
int echoPin = 6;    //Echo – yellow Jumper
long duration, cm, inches;

void setup()
{
   pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
   pinMode(5,OUTPUT);

   
  pinMode(A0,OUTPUT);
pinMode(11,OUTPUT);
 Serial.begin(9600);
//  ss.begin(9600);
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
  lcd.begin(16,2);
  //Serial.println(TinyGPS::library_version());
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GPS traking....");
  delay(2000);
  lcd.clear();
  
getgps();
 
  delay(2000);
}

void loop()
{
   digitalWrite(2, HIGH);
     digitalWrite(3, LOW);
     digitalWrite(4, HIGH);
       digitalWrite(5, LOW);
   digitalWrite(trigPin, LOW);
 delayMicroseconds(5);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 pinMode(echoPin, INPUT);
 duration = pulseIn(echoPin, HIGH);
 cm = (duration/2) / 29.1;
 inches = (duration/2) / 74;
 Serial.print(cm);
 Serial.println();
 delay(350);
 if(cm<8)
 {
  Serial.println("no fault");
   lcd.setCursor(0,0);
  lcd.print("no fault");
  delay(2000);
  lcd.clear();
  c1=0;
 }
 else
 {
 Serial.println("fault");
  lcd.setCursor(0,0);
  lcd.print("fault detected");
  delay(2000);
  lcd.clear();
  if(c1==0)
    {
      Serial.println("in if gps...................................");
    getgps();
     Serial.println("in if gps..");
    
    msg= "fault detected"; 
//    Value=i;
    sendsms();
    
   c1=1;
    }
 
  delay(1000);
  }
}
void displayInfo()
{
 
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    flat=gps.location.lat();
    flon=gps.location.lng();
    Serial.print(flat, 6);
    Serial.print(F(","));
    Serial.print(flon, 6);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LAT:");
    lcd.setCursor(0,1);
    lcd.print("LON:");
    lcd.setCursor(8,0);
    lcd.print(flat);
    lcd.setCursor(8,1);
    lcd.print(flon);
    delay(2000);
    lcd.clear();
  }

}
void getgps()
{
 
 for (unsigned long start = millis(); millis() - start < 1000;)
  {
 while (Serial.available())
   {
     char c = Serial.read();
    if (gps.encode(c))
    {
      displayInfo();
    }
   }

  }  
  }
  


void sendsms()
{
  Serial.println("sms");
   Serial.println("AT");  
    delay(500);
   Serial.println("ATE0");  
    delay(500);
   Serial.println("AT+CMGF=1");   
    delay(500);
   Serial.println("AT+CMGS=\"+919182371171\"\r"); 
    delay(500);
  Serial.print(msg);
  // Serial.println(Value);
   
    delay(200);
     Serial.print( "http://www.google.com/maps/place/" + String(flat) + "," + String(flon));
     
    delay(500);
  Serial.println((char)26);
    delay(500);
   
    
   Serial.println("message sent");
    lcd.setCursor(0,0);
  lcd.print("message sent");
  delay(2000);
  lcd.clear();
  }

