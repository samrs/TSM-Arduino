#include <ESP8266WiFi.h>     
#include <ESP8266HTTPClient.h> 
#include <ArduinoJson.h>             
 
const char* ssid = "INFINITUM24Q5_2.4";       
const char* password = "X6V7HzbWwN";                  
                 
void setup() 
{
  delay(10);
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  pinMode(1, OUTPUT); 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  //Llegado este punto debería ya haberse conectado
  
}

void loop() 
{
  for(int i=1; i<9;i++)
  {
    if(WiFi.status()==WL_CONNECTED)
    {
        HTTPClient http;
        http.begin("http://tsmpjgv9.000webhostapp.com/luzPost.php");
        http.addHeader("Content-Type", "application/json");

        StaticJsonDocument<69> doc;
        doc["id"]=i;

        String request;
        serializeJson(doc, request);
        int httpCode= http.POST(request);

        if(httpCode>0)
        {
           String respuesta = http.getString();
           Serial.print("Respuesta: "+respuesta);
           if (respuesta [12]=='1')
           {
             digitalWrite(i, HIGH);
           }
           else
           {
             digitalWrite(i, LOW);
           }
           http.end();
        }
        delay(50);   
     }
  }
}
