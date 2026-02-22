#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define trigPin 11
#define echoPin 12
#define buzzer 8

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  myServo.attach(9);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {

  // Gerak kiri ke kanan
  for(int pos = 0; pos <= 180; pos += 2) {
    myServo.write(pos);
    delay(20);
    distance = readDistance();
    tampilLCD(pos, distance);
    cekBuzzer(distance);
  }

  // Gerak kanan ke kiri
  for(int pos = 180; pos >= 0; pos -= 2) {
    myServo.write(pos);
    delay(20);
    distance = readDistance();
    tampilLCD(pos, distance);
    cekBuzzer(distance);
  }
}

int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  int jarak = duration * 0.034 / 2;

  return jarak;
}

void tampilLCD(int sudut, int jarak) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Sudut: ");
  lcd.print(sudut);

  lcd.setCursor(0,1);
  lcd.print("Jarak: ");
  lcd.print(jarak);
  lcd.print(" cm");
}

void cekBuzzer(int jarak) {
  if(jarak > 0 && jarak <= 20) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }
}
