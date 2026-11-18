#include <Arduino.h>
#include <WiFi.h>
#include <EMailSender.h>//Added the necesary libraries to use the esp32, to use wifi, and to send the email

// put function declarations here:
const int trig1 = 13;
const int trig2 = 26;//Trig 1&2 are the pins for... trig...
const int echo1 = 14;
const int echo2 = 27;//Echo 1 & 2 are the pins for.... echo... yeah...
int distance1;
int distance2;//Distance 1 & 2 are the variables that are used to store the distance at wich the tras is
const float soundSpeed = 0.034;//The speed of sound in cm/miocroseconds, this value is gonna be used to calculate the distance at wich objects are

const char* ssid = "moto g power (2021)_1453";//You can change the wifi name in here
const char* password = "22ixfvakffebvx8";//You can change the password of the wifi that you are connecting to in here


EMailSender emailSend("edcmtynl@gmail.com", "ubos xlni zlug noic");//Add both the email that is gonna send the email, and then you put the app pasword forthat email account

void enviarCorreo(){
 EMailSender::EMailMessage message;
  message.subject = "Classrom 41";//Put the title of the email in here
  message.message = "The trashcan in classroom 41 is full, please empty it.";//put the body of the email in here

  EMailSender::Response resp = emailSend.send("edcmtynl@gmail.com", message);//Put the email address that you want to send the email to in here

  Serial.print("Sending status: ");
  Serial.println(resp.status);
  Serial.println(resp.desc);//Here you print the status of the email, if it was sent or not, etc...
}
void setup() {
 Serial.begin(115200);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
 Serial.println("Connecting to Wi-Fi...");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");//Line 37 to 42 is a loop that is used to connect to the inetrnet, it won't continue reading the next lines of code until this loop is finished
  }
Serial.println("\nConnected to WiFi");//Once the esp32 has connected to the internet, this line will print that the esp32 is connmected to the wifi


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);


  distance1 = pulseIn(echo1, HIGH) * soundSpeed / 2; // Calculate distance in cm for distance1

  delay(50);

  digitalWrite(trig1, LOW);
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);


  distance2 = pulseIn(echo2, HIGH) * soundSpeed / 2;// Calculate distance in cm for distance2
  delay(50);
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm"); //line 44-49 print in the serial monitor the distance measured by the two ultrasonic sensors

  if(distance1 <= 20 && distance2 <= 20) {
delay(5000); // A delay is made to confirm that this value is right and that the object is still there

// put your main code here, to run repeatedly:
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);


  distance1 = pulseIn(echo1, HIGH) * soundSpeed / 2; // Calculate distance in cm for distance1

  delay(50);//This delay is used to make sure that the ultrasonic sound waves dont interfere with each other, if this delay wasn't here, the soundwaves would merge and the distance values would be incorrect

  digitalWrite(trig1, LOW);
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);


  distance2 = pulseIn(echo2, HIGH) * soundSpeed / 2;// Calculate distance in cm for distance2
  delay(50);
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm"); //line 44-49 print in the serial monitor the distance measured by the two ultrasonic sensors


  if(distance1 <= 20 && distance2 <= 20) {//In here we say that if both distance 1&2 are less or equal to 20 we are gonna send the email...
    Serial.println("Object detected in front of both sensors");
    Serial.println("Sending e-mail");
    enviarCorreo();
    delay(5000);//A delay is put to prevent sending multiple emails in a short time, you can change this value to your liking
  }//It is better to leave a good amount of time in the delay, something like 10 minutes is alright, that is 600000 milliseconds, but you can change it to your liking

  }

}
