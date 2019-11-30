#include <EEPROM.h>

volatile int forward;
volatile int back;
volatile int left;
volatile int right;

unsigned long eepromReadLong(int address) {
  union u_tag {
  	byte b[4];
  	unsigned long ULtime;
  }
  time;
  time.b[0] = EEPROM.read(address);
  time.b[1] = EEPROM.read(address+1);
  time.b[2] = EEPROM.read(address+2);
  time.b[3] = EEPROM.read(address+3);
  return time.ULtime;
}

void eepromWriteLong(int address, unsigned long value) {
  union u_tag {
  	byte b[4];
  	unsigned long ULtime;
  }
  time;
  time.ULtime=value;
  EEPROM.write(address, time.b[0]);
  EEPROM.write(address+1, time.b[1]);
  if (time.b[2] != EEPROM.read(address+2) ) EEPROM.write(address+2, time.b[2]);
  if (time.b[3] != EEPROM.read(address+3) ) EEPROM.write(address+3, time.b[3]);
}

int set(int Pin) {
  int x;
  tone(12,500);
  delay(1000);
  noTone(12);
  for (int i = 1; i <= 20; i = i + (1)) {
    x = x + analogRead(Pin);
  }
  x = x / 20;
  tone(12,500);
  delay(300);
  noTone(12);
  delay(300);
  tone(12,500);
  delay(300);
  noTone(12);
  return x;
}

void setup(){
  forward = 0;
  back = 0;
  left = 0;
  right = 0;
  if (eepromReadLong(0) == 0) {
    forward = set(A0);
    back = set(A0);
    left = set(A1);
    right = set(A1);
    forward = forward - 300;
    back = back + 300;
    left = left - 300;
    right = right + 300;
    eepromWriteLong(0, 1);
    eepromWriteLong(1, forward);
    eepromWriteLong(2, back);
    eepromWriteLong(3, left);
    eepromWriteLong(4, right);

  }
  forward = eepromReadLong(1);
  back = eepromReadLong(2);
  left = eepromReadLong(3);
  right = eepromReadLong(4);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  if (analogRead(A0) >= forward) {
    Serial.println("forward");
  } else if (analogRead(A0) <= back) {
    Serial.println("back");
  } else if (analogRead(A1) >= left) {
    Serial.println("left");
  } else if (analogRead(A1) <= right) {
    Serial.println("right");
  } else {
    Serial.println("stop");

  }

}
