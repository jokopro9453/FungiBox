#include "DHT.h"

#define DHT_PIN 8 // Pin del sensor DHT11.
#define DHTTYPE 11 // Declaramos que la version del sensor DHT es la 11.

#define HUM_PIN 6   
#define TEMP_PIN 10 


DHT dht(DHT_PIN,DHTTYPE); // Se crea el objeto dht indicando (PIN, vesion de DHT).
void setup() {
  // put your setup code here, to run once:
  pinMode(HUM_PIN, OUTPUT); // Definimos el pin 6 para informar el humbral de humedad.
  pinMode(TEMP_PIN, OUTPUT); // Definimos el pin 10 para informar el humbral de temperatura.

  Serial.begin(9600);

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000); //La libreria recomendaba 2 segundos entre medicion

  float hum = dht.readHumidity(); // Leer humedad
  float temp = dht.readTemperature(); // Leer temeperatura
  
  Serial.print(hum);
  Serial.print(" % ");
  Serial.print(temp);
  Serial.println(" °C");

  
  if(temp > 19){
    Serial.println("Se a exedido el humbral de temperatura");

    digitalWrite(TEMP_PIN, HIGH);
  } else {
    digitalWrite(TEMP_PIN, LOW);
  }
  if (hum < 70){
    Serial.println("La humedad del ambiente es muy baja");

    digitalWrite(HUM_PIN, HIGH);

  } else{
    digitalWrite(HUM_PIN, LOW);
  }
}
