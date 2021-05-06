
#include <dht.h>
#define DHT11_PIN 4

dht DHT;
void setup(){

 pinMode(DHT11_PIN,INPUT);
 Serial.begin(9600);
}

void loop()
{
 int d = DHT.read11(DHT11_PIN);
 Serial.println(DHT.temperature);
 Serial.println("H");
 Serial.println(DHT.humidity);
 
 delay(1000);
}

//#define sensorPin  A0
//
//void setup() {
//  Serial.begin(9600);
//}
//
//void loop()
//{
//  int reading = analogRead(sensorPin);
//  float voltage = reading * 5.0;
//  voltage /= 1024.0;
//  float temperatureC = (voltage - 0.5) * 100 ;
//  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
//
//  Serial.print(voltage); Serial.print(" volts  -  ");
//  Serial.print(temperatureC); Serial.print(" degrees C  -  ");
//  Serial.print(temperatureF); Serial.println(" degrees F");
//
//  delay(1000);
//}
