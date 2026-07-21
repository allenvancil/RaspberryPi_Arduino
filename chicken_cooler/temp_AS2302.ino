#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22 //AM2302 type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
}

void loop(){
    delay(2000);

    float humidity = dht.readHumidity();
    float tempC = dht.readTemperature();
    float tempF = dht.readTemperature(True);


    if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
    Serial.print(F("Humdity: "));
    Serial.print(humidity)
    Serial.print(F("% Temperature: "));
    Serial.print(tempC)
}