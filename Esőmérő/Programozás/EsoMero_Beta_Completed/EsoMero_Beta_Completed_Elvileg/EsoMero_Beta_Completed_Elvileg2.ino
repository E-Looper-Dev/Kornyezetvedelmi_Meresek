#include <SPI.h>  
#include <SD.h>

#define HALL_SENSOR_PIN 2

#define FILE_NAME "csapadek.txt"



File dataFile;

void setup() {
  Serial.begin(9600);

  pinMode(HALL_SENSOR_PIN, INPUT);
  
  if (!SD.begin(10)) {   // A reed relé a D2-es tüskére van csatlakoztatva                                          
    Serial.println("Hiba a SD kártya inicializálásakor!");
    return;
  }

  dataFile = SD.open(FILE_NAME, FILE_WRITE);                      
  if (!dataFile) {                                              
    Serial.println("Hiba a fájl megnyitásakor!");
    return;
  }

  Serial.println("Hall-érzékelő és SD kártya inicializálva.");   
}

void loop() {
  float hallValue = digitalRead(HALL_SENSOR_PIN);
  
  if (hallValue != 0) {
    Serial.print("Jel értéke a tüskén ");
    Serial.print(HALL_SENSOR_PIN);
    Serial.print(": ");
    Serial.println(hallValue);

    float csapadek = 0;
    csapadek += 4.15;
    float csapadekHektar = csapadek * 100000000 / 216.4243;

    dataFile = SD.open(FILE_NAME, FILE_WRITE);
    if (dataFile) {                                                 
      dataFile.print("Mágneses mező változás észlelve a tüskén ");
      dataFile.print(HALL_SENSOR_PIN);
      dataFile.println(": ");
      dataFile.print("Jel értéke: ");
      dataFile.println(hallValue);
      dataFile.print("Csapadék összesen: ");
      dataFile.print(csapadek);
      dataFile.println("cm³");
      dataFile.print("Csapadék egy hektár területen összesen: ");
      dataFile.print(csapadekHektar);
      dataFile.println("cm³");
      dataFile.close();
    } else {                                                       
      Serial.println("Hiba a fájl írása közben!");
    }
  }
}
