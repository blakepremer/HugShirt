#include <SoftwareSerial.h>
#include <String.h>
String lat = "52.6272690";
String lng = "-1.1526180";
SoftwareSerial sim800l(2, 3); // RX, TX
float sensorValue;
const int buttonPin = 7; 
int buttonState = 0; 
int fsrAnalogPin = A5; // FSR is connected to analog 5
int fsrReading;      // the analog reading from the FSR resistor divider
float tempC; 
float tempCavg; 
int avgcount = 0;
void setup()
{
 
  pinMode(buttonPin, INPUT); 
  sim800l.begin(9600);
  Serial.begin(9600);   
  delay(500);
}
 
void loop()
{

  fsrReading = analogRead(fsrAnalogPin);

  buttonState = digitalRead(buttonPin);
 
  if (buttonState == 0 && fsrReading >= 250) {


    
   //// while(avgcount < 50){
    ////sensorValue = analogRead(A0);
    ////tempC = sensorValue * 5.0;
    ////tempC = tempC / 1024.0; 
    ////tempC = (tempC - 0.05) * 100;
   //// tempCavg = tempCavg + tempC; 
   //// avgcount++;
   //// }
    delay(300);
/////    Serial.println(tempCavg/ 50);
/////    tempCavg = tempCavg / 50;

Serial.println(fsrReading);

    SendTextMessage(); 
//// DialVoiceCall();
 }
 
  if (sim800l.available()){ 
    Serial.write(sim800l.read()); 
  }
}
 
void SendTextMessage()
{
  Serial.println("Sending Text...");
  sim800l.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
 
  sim800l.print("AT+CMGS=\"+1305*******\"\r"); //Fill in Phone Number here.
  delay(200);
//  sim800l.print("http://maps.google.com/?q=");
//  sim800l.print(lat);
//  sim800l.print(",");
//  sim800l.print(lng);
 //// sim800l.print("The temperature is: ");
 //// sim800l.print(tempCavg);
 //// sim800l.print(" degrees C");

sim800l.print("The Frs reading is ");
sim800l.print(fsrReading);
sim800l.print(" units");
 
  sim800l.print("\r"); //the content of the message
  delay(500);
  sim800l.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  sim800l.println();
  Serial.println("Text Sent.");
   delay(500);
    tempCavg = 0;
    avgcount = 0;
}
 
void DialVoiceCall()
{
  sim800l.println("ATD+1305*******;");//dial the number, must include country code
  delay(100);
  sim800l.println();
}
