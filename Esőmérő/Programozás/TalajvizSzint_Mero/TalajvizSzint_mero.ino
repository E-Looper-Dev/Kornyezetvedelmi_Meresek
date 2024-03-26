#include <SPI.h>
#include <SD.h>
#include <Wire.h>

const int trigPin = 6;  // HC-SR04 trig pin
const int echoPin = 7; // HC-SR04 echo pin

const int chipSelect = 10; // SD card CS pin

File dataFile;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("Hiba a MicroSD kártya inicializálásakor!");
    return;
  }

  Serial.println("MicroSD kártya inicializálva.");

  dataFile = SD.open("talaj_viz_szint.txt", FILE_WRITE);

  if (!dataFile) {
    Serial.println("Hiba a fájl megnyitásakor!");
    return;
  }

  Serial.println("Fájl megnyitva.");
}

void loop() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Távolság: ");
  Serial.println(distance);

  int maxDistance = 200;
  int difference = maxDistance - distance;

  Serial.print("A talajvíz szintje: ");
  Serial.print(difference);
  Serial.println("cm");

  dataFile.print("Mért távolság: ");
  dataFile.print(distance);
  dataFile.println("cm");
  dataFile.print("A talajvíz szintje: ");
  dataFile.print(difference);
  dataFile.println("cm");

  delay(86400000);
}
