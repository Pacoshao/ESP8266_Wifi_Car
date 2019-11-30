/* 
Controller-ESP8266
Code
*/

#include<ESP8266WiFi.h>

const char* ssid = “Paco’s_Car”;
const char* host = "192.168.1.1";
String light_get; 
int test=0;
int tesx=0;
void setup() 
{
Serial.begin(115200);
Serial.println("启动");
delay(10);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("IP: ");
Serial.println(WiFi.localIP());
}



void loop(){
while(!Serial.available() > 0);
if (Serial.available() > 0) {
if(Serial.readString() == "forward"){
test=1;
Serial.println("Forward");
}else if (Serial.readString() == "back") {
test=2;
Serial.println("Back"); 
}else if (Serial.readString() == "left") {
test=3;
Serial.println("Left"); 
}else if (Serial.readString() == "right") {
test=4;
Serial.println("Right"); 
}else{
test=5;
Serial.println("Stop"); 
}
}
light_get = "/opera?opera="+String(test);
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
Serial.println("Cannot Request" + * host);
return;
}
client.print(String("GET ") + light_get + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
while(client.available()) {
String line = client.readStringUntil('\r');
Serial.print(line);
}
delay(50);
}
