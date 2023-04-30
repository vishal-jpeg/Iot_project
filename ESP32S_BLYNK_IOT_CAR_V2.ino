

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLuQ3TyJ9d"
#define BLYNK_TEMPLATE_NAME "NEW CAR"
#define BLYNK_AUTH_TOKEN "Kr8Ntj7xuYUisn0Zlw7LY_GCyRCaZUBa"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//gas
int SensorMQ135=34;
int SensorMQ7=35;
//temp
int SensorTemp=32;

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Airtel fiber";
char pass[] = "Jaishnu@123";

int IN1 = 4;
int IN2 = 5;
int IN3 = 12;
int IN4 = 13;

//blynk timer
BlynkTimer timer;

BLYNK_WRITE(V1) { //move forward  
  digitalWrite(IN2, param.asInt());
  digitalWrite(IN4, param.asInt());
}

BLYNK_WRITE(V2) { //move backward
  digitalWrite(IN1, param.asInt());
  digitalWrite(IN3, param.asInt());
}

BLYNK_WRITE(V3) { //turn left
  digitalWrite(IN2, param.asInt());
  digitalWrite(IN3, param.asInt());
}

BLYNK_WRITE(V4) { //turn right
  digitalWrite(IN1, param.asInt());
  digitalWrite(IN4, param.asInt());
}

//gas function
void SendSensorMQ135(){
  int analog_data=analogRead(SensorMQ135);
  Serial.println(analog_data);
  Blynk.virtualWrite(V0,analog_data);
  delay(300);
}
void SendSensorMQ7(){
  int analog_data=analogRead(SensorMQ7);
  Serial.println(analog_data);
  Blynk.virtualWrite(V5,analog_data);
  delay(500);
}
//temperature sensor
void SendSensorTemp(){
   int adcData = analogRead(SensorTemp);
  // Convert that ADC Data into voltage
  float voltage = adcData * (5.0 / 1024.0);
  // Convert the voltage into temperature 
  float temperature = voltage * 100;
  // Print the temperature data
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("*C");
   // wait a second between readings
  Blynk.virtualWrite(V6,temperature);
  delay(800);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  //gas tiimer
  timer.setInterval(100L,SendSensorMQ135);
  timer.setInterval(100L,SendSensorMQ7);
  timer.setInterval(100L,SendSensorTemp);
}

void loop()
{
  Blynk.run();
  //gas timer run
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
