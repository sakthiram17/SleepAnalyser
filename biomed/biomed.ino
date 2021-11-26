#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#include<string.h>
#ifndef STASSID

int day = 0;
#include <cstring>
#endif
#define _SSID "Redmix"        
#define _PASSWORD "redmi1021"    
#define PROJECT_ID "sleepanalyzer2-b9951-default-rtdb"
int sensorpin = 3;
int switchpin = 5;
const int wifi_rest = 3;
char* sleeplist = "";
String sleeplist1 = "";
char* timearray = "";
  Firebase firebase("sleepanalyzer2-b9951-default-rtdb");    
char* FIREBASE_HOST =  "your FIREBASE HOST";
char * FIREBASE_AUTH = "Your secret";
int t = 0;


void setup(void) {
  Serial.begin(115200);
   
    
  Serial.println(" sdfgsdfg sdfg sdfg sdfg sdfg sdfg");
 WiFi.begin(_SSID ,_PASSWORD);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(5,HIGH);

String dayurl = "/Day";
String dataurl = "/data";

day = firebase.getInt(dayurl);
Serial.println("git day" );
}

void loop(){

/*if(0){
  //digitalRead(wifi_reset)){
 String ssid = "";
  String password = "";
  ssid = firebase.getString("ssid");
   password = firebase.getString("password");
  WiFi.begin(ssid,password);
  
  }
*/
int data = digitalRead(sensorpin);
Serial.println("In loop" );
 String data_c; 

  if(data == 1)
  {
   data_c= "1";
    }
    else{
       data_c = "0";
      }
sleeplist1 = sleeplist1 + data_c;

if(digitalRead(2)== HIGH ){
Serial.println("Sending Data");
if(day==0){
  firebase.setString("data0",sleeplist1);
}
if(day==1){
  firebase.setString("data1",sleeplist1);
}
if(day==2){
  firebase.setString("data2",sleeplist1);
}
if(day==3){
  firebase.setString("data3",sleeplist1);
}
if(day==4){
  firebase.setString("data4",sleeplist1);
}
if(day==5){
  firebase.setString("data5",sleeplist1);
}
if(day==6){
  firebase.setString("data6",sleeplist1);
}
  digitalWrite(5,HIGH);
  delay(1000); 
  digitalWrite(5,LOW);
}
  delay(1000);
}
