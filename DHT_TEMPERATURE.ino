#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
//DHT SETTINGS
#include "DHT.h"
#define DHTTYPE DHT22
// DHT SensorPIN SETTING
#define DHTPin 4  
// WIFI SETTINGS
const char *ssid = "Jan router5RysowałTrójkąty";
const char *password = "";
//SCKETIO SETTINGS
const char *socketServer = "onandon2.herokuapp.com";
SocketIoClient socket;

  
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                
float Temperature;
float Humidity;
//////////////////////////




void setup() {
  Serial.begin(115200); //SERIAL PORT INICIALIZATION
  dht.begin();    // DHT22 SENSOR INICIALIZATION 
  //WIFI CONFIG/RESET
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.begin(ssid, password);//CONNECT TO WIFI

  while (WiFi.status() != WL_CONNECTED) //WAITING FOR CONNECTED
  {
    delay(100);
    Serial.print(".");
  }  
  
///CONNECT WITH SERVER
  socket.begin(socketServer);

}


void loop() {
    socket.loop();
    
        Temperature = dht.readTemperature(); // Gets the values of the temperature
        Humidity = dht.readHumidity(); // Gets the values of the humidity
        
        char temperatureBuffer[20];
        char *dataTemperature;
        dataTemperature = dtostrf(Temperature, 6, 2, temperatureBuffer);
        
        char humidityBuffer[20];
        char *dataHumidity;
        dataHumidity = dtostrf(Humidity, 6, 2, humidityBuffer);
        
        socket.emit("temperature", dataTemperature);
        socket.emit("humidity", dataHumidity);   
   
   

  delay(1000);
}
