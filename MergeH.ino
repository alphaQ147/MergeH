
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define a  D0
#define b  D1
#define c  D2

#define HOST "mergeh-1f447.firebaseio.com"
#define AUTH "WItIuPtmShUzM38dQGObtBFbwJRvy5z21QANlOxg"
#define ssid "Insecure Channel"
#define pass "divyansh14474"

void setup() {
  Serial.begin(115200);
  pinMode(A0,INPUT);
  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  
  // connect to wifi.
  WiFi.begin(ssid, pass);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(HOST,AUTH);
}


void loop() 
{
  float s1=0,s2=0,s3=0;
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  
  
//sensor 1
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,HIGH);
  s1 = analogRead(A0);
  s1 = (s1/1024)*28;
  
  delay(50);
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);

//sensor 2
  digitalWrite(a,LOW);
  digitalWrite(b,HIGH);
  digitalWrite(c,LOW);
  s2 = analogRead(A0);
  s2 = (s2/1024)*5;
  delay(50);
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);

//sensor 3
  digitalWrite(a,HIGH);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  s3 = analogRead(A0);
  s3 = (s3/1024)*7;
  delay(50);
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  
  // set value
  Firebase.setFloat("Carbon Monoxide", s1);
  Firebase.setFloat("Ozone", s2);
  Firebase.setFloat("Dihydrogen Sulphide", s3);
  // handle error
  if (Firebase.failed()) {
      Serial.println(Firebase.error());  
      return;
  }
  delay(100);
  
  // remove value
  Firebase.remove("number");
  delay(100);

  

}
