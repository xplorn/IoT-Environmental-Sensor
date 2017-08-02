#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "cactus_io_BME280_I2C.h"
#include <math.h>
#include <Wire.h>


// Create BME280 object
// BME280_I2C bme; // I2C using address 0x77
BME280_I2C bme(0x76); // I2C using address 0x76

int temperature;
int humidity;
int pressure;
String ssid = "ADD YOUR SSID HERE";
String password = "YOUR PASSWORD";
String webString="";     // String to display

ESP8266WebServer server(80);

void handle_root() {
  server.send(200, "text/plain", "ESP8266 Weather Web sensor, read from /temp or /humidity or /pressure");
  delay(100);
}

void setup() {
  IPAddress ip(192, 168, 9, 209);            // IP Address
  IPAddress subnet(255, 255, 255, 0);        // Subnet mask
  IPAddress gt(192, 168, 9, 1);              // Gateway IP
  
  Serial.begin(115200);
  Serial.println("Begin ESP8266");

  char charBuf[50];
  char charBuf2[50];
  ssid.toCharArray(charBuf, 50);
  password.toCharArray(charBuf2, 50);
  WiFi.config(ip, gt, subnet);
  WiFi.begin(charBuf , charBuf2);
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  server.on("/", handle_root);
  
  server.on("/temp", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    temperature=round(bme.getTemperature_F());       // read sensor
    webString="Temperature: "+String((int)temperature)+" F";
    server.send(200, "text/plain", webString);            // send to someones browser when asked
  });
 
  server.on("/humidity", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    humidity=round(bme.getHumidity());           // read sensor
    webString="Humidity: "+String((int)humidity)+"%";
    server.send(200, "text/plain", webString);               // send to someones browser when asked
  });

  server.on("/pressure", [](){  // if you add this subdirectory to your webserver call, you get text below :)
    pressure=round(bme.getPressure_MB());           // read sensor
    webString="Pressure: "+String((int)pressure)+"mb";
    server.send(200, "text/plain", webString);               // send to someones browser when asked
  });
  
  server.begin();
  Serial.println("HTTP server started");

  Serial.println("Bosch BME280 Pressure - Humidity - Temp Sensor");
  Serial.println("");

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  while (1);
  }

  delay(5000);

//  Serial output/debugging   
//  Serial.println("Pressure\tHumidity\tTemp");

  bme.setTempCal(-1);// Temp was reading high so subtract 1 degree

}

void loop() {
  bme.readSensor();

/*   Serial output/debugging  
  temperature=round(bme.getTemperature_F());
  humidity=round(bme.getHumidity());
  pressure=round(bme.getPressure_MB());
  Serial.print(pressure); Serial.print(" mb\t\t"); // Pressure in millibars
  Serial.print(humidity); Serial.print(" %\t\t");
  Serial.print(temperature); Serial.println(" *F");
// Add a 1 second delay.
  delay(1000); //just here to slow down the output.
*/

  server.handleClient();

}
