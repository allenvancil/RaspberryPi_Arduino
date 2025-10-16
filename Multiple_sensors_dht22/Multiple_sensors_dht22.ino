#include "DHT.h"

#define DHTPIN1 2
#define DHTPIN2 4
#define DHTTYPE DHT22
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht1.begin();
  dht2.begin();
}

void loop() {
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature(true);
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature(true);

  if (isnan(h1) || isnan(t1)) {
    Serial.print("Failed to read from DHT1 sensor!");
    return;
  }
  if (isnan(h2) || isnan(t2)) {
    Serial.print("Fail to read DHT2 sensor...idiot!!!");
    return;
  }
  

  Serial.print("H1: ");
  Serial.print(h1);
  Serial.print("\t");
  Serial.print("T1: ");
  Serial.print(t1);
  Serial.print(" *F");
  Serial.print("\t\t");
  Serial.print("H2:  ");
  Serial.print(h2);
  Serial.print("\t");
  Serial.print("T2: ");
  Serial.print(t2);
  Serial.println(" *F");

  delay(10000);
}

