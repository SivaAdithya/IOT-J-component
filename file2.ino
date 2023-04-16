#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11
#define sensorPower 7
#define sensorPin A1
const int moistureAO = 0;
int AO = 0;
int temp = 0;
int buzzpin = 9;
int LED = 13;
int val = 0;
DHT dht(DHTPIN, DHTTYPE);
void setup() 
{
  Serial.begin(9600);
  dht.begin();
  Serial.println("soil moisture sensor");
  pinMode(moistureAO,INPUT);
  pinMode(buzzpin,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(sensorPower, OUTPUT);
	// Set to LOW so no power flows through the sensor
	digitalWrite(sensorPower, LOW);	
	Serial.begin(9600);
}
void loop() {
  temp = analogRead(moistureAO);
  if(temp!=AO)
  {
    AO = temp;
    Serial.print("A = ");
    Serial.println(AO);
  }
  delay(1000);
  if (analogRead(0)>900)
  {
    digitalWrite(buzzpin, HIGH);
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(buzzpin, LOW);
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(buzzpin, LOW);
    digitalWrite(LED, LOW);
  }
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);
 if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
 }
      float hif = dht.computeHeatIndex(f, h);
   // Compute heat index in Celsius (isFahreheit = false)
   float hic = dht.computeHeatIndex(t, h, false);
   Serial.print ("Humidity: ");
   Serial.print (h);
   Serial.print (" %\t");
   Serial.print ("Temperature: ");
   Serial.print (t);
   Serial.print (" *C ");
   Serial.print (f);
   Serial.print (" *F\t");
   Serial.print ("Heat index: ");
   Serial.print (hic);
   Serial.print (" *C ");
   Serial.print (hif);
   Serial.println (" *F");
   int level = readSensor();
	Serial.print("Water level: ");
	Serial.println(level);
	delay(1000);
}
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// wait 10 milliseconds
	val = analogRead(sensorPin);		// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// send current reading
}

