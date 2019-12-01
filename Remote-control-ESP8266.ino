/*

  Controller-ESP8266

  Code

*/



#include<ESP8266WiFi.h>

const char* ssid = "My_Car";
const char* host = "192.168.1.1";
String light_get;
int test = 0;
int tesx = 0;
int direction;

int My_digitalRead(uint8_t pin) {
  pinMode(pin, INPUT);
  return digitalRead(pin);
}

int Remote_potentiometer() {
  // 1 forward
  // 2 back
  // 3 left
  // 4 right
  if (My_digitalRead(D7) == LOW) {
    return 1;
    
  } else if (My_digitalRead(D8) == HIGH) {
    return 2;

  } else if (My_digitalRead(D6) == HIGH) {
    return 3;

  } else if (My_digitalRead(D5) == LOW) {
    return 4;

  }
  return 5;
}

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

void loop() {
    test = Remote_potentiometer();
    light_get = "/opera?opera=" + String(test);
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("Cannot Request" + * host);
      return;
    }
    client.print(String("GET ") + light_get + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    delay(50);
}
