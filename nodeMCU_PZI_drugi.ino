#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

/*Put your SSID & Password*/
const char* ssid = "Galaxy-S8";  // Enter SSID here
const char* password = "stoka123";  //Enter Password here

ESP8266WebServer server(80);

// DHT Sensor
uint8_t DHTPin = D2; 
               
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);

  dht.begin();              

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  
  server.handleClient();
  
}

void handle_OnConnect() {

  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float TempCstat,float Humiditystat){
  String page = "<!DOCTYPE html> <html>\n";
  page +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  page +="<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  page +="<title>ESP8266 Weather Report</title>\n";
  page +="<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n";
  page +="body{margin-top: 50px; background-color: lightblue;}\n";
  page +="h1 {margin: 50px auto 30px;}\n";
  page +=".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
  page +=".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}\n";
  page +=".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  page +=".humidity{font-weight: 300;font-size: 60px;color: #3498db;}\n";
  page +=".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n";
  page +=".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  page +=".temperature{font-weight: 300;font-size: 60px;color: #f39c12;}\n";
  page +=".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
  page +=".data{padding: 10px;}\n";
  page +="</style>\n";
  page +="<script>\n";
  page +="setInterval(loadDoc,200);\n";
  page +="function loadDoc() {\n";
  page +="var xhttp = new XMLHttpRequest();\n";
  page +="xhttp.onreadystatechange = function() {\n";
  page +="if (this.readyState == 4 && this.status == 200) {\n";
  page +="document.getElementById(\"webpage\").innerHTML =this.responseText}\n";
  page +="};\n";
  page +="xhttp.open(\"GET\", \"/\", true);\n";
  page +="xhttp.send();\n";
  page +="}\n";
  page +="</script>\n";
  page +="</head>\n";
  page +="<body>\n";
  page +="<div id=\"webpage\">\n";
  page +="<h1>ESP8266 Weather Report</h1>\n";
  page +="<div class=\"data\">\n";
  page +="<div class=\"side-by-side temperature-icon\">\n";
  page +="<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n";
  page +="width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n";
  page +="<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n";
  page +="c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n";
  page +="c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n";
  page +="c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n";
  page +="c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"/>\n";
  page +="</svg>\n";
  page +="</div>\n";
  page +="<div class=\"side-by-side temperature-text\">Temperature</div>\n";
  page +="<div class=\"side-by-side temperature\">";
  page +=(int)TempCstat;
  page +="<span class=\"superscript\">°C</span></div>\n";
  page +="</div>\n";
  page +="<div class=\"data\">\n";
  page +="<div class=\"side-by-side humidity-icon\">\n";
  page +="<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n";
  page +="<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n";
  page +="c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n";
  page +="</svg>\n";
  page +="</div>\n";
  page +="<div class=\"side-by-side humidity-text\">Humidity</div>\n";
  page +="<div class=\"side-by-side humidity\">";
  page +=(int)Humiditystat;
  page +="<span class=\"superscript\">%</span></div>\n";
  page +="</div>\n";
  page +="</div>\n";
  page +="</body>\n";
  page +="</html>\n";
  return page;
}
