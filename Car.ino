//The car...
#include <FS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
IPAddress apIP(192, 168, 1, 1);
ESP8266WebServer server (80);

void setup() {
pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);
pinMode(D7, OUTPUT);
pinMode(D8, OUTPUT);
  WiFi.softAP("My_Car");
  Serial.begin (115200);
  Serial.println("Loading...");  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  Serial.println(WiFi.localIP());
  server.begin();
  server.on("/",file);
  server.on("/Service", Service);
}

void file(){
  File file = SPIFFS.open("/index.html", "r");
server.streamFile(file, "text/html");
  file.close();
}

void Service() {
  String word = server.arg("Service");
 
  Serial.println(word);
  if(word=="1"){
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    
    digitalWrite(D7, HIGH);
    digitalWrite(D8, LOW);
    
    }if(word=="2"){
      digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    
    digitalWrite(D7, LOW);
    digitalWrite(D8, HIGH);
      }if(word=="3"){
        digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    
    digitalWrite(D7, LOW);
    digitalWrite(D8, HIGH);
        }if(word=="4"){
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    
    digitalWrite(D7, HIGH); 
    digitalWrite(D8, LOW);
          }if(word=="5"){
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
            }
server.send(200, "text/plain", "ok");
}


void loop() {
  server.handleClient();
      delay(50);
}
