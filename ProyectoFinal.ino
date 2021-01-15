#include <ESP8266WiFi.h>     
#include <ESP8266HTTPClient.h> 
#include <ArduinoJson.h>             
 
const char* ssid = "INFINITUM24Q5_2.4";       
const char* password = "X6V7HzbWwN";      

int salida[8]={16,5,4,0,2,14,12,13};
                 
void setup() 
{
  delay(10);
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  pinMode(salida[0], OUTPUT); 
  pinMode(salida[1], OUTPUT);
  pinMode(salida[2], OUTPUT);
  pinMode(salida[3], OUTPUT);
  pinMode(salida[4], OUTPUT);
  pinMode(salida[5], OUTPUT);
  pinMode(salida[6], OUTPUT);
  pinMode(salida[7], OUTPUT);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  
}

void loop() 
{
  for(int i=0; i<8;i++)
  {
    if(WiFi.status()==WL_CONNECTED)
    {
        HTTPClient http;
        http.begin("http://tsmpjgv9.000webhostapp.com/luzPost.php");
        http.addHeader("Content-Type", "application/json");

        StaticJsonDocument<100> doc;
        doc["id"]=salida[i];

        String request;
        serializeJson(doc, request);
        int httpCode= http.POST(request);

        if(httpCode>0)
        {
           String respuesta = http.getString();
           Serial.println("Respuesta: "+respuesta);
           if (respuesta [12]=='1')
           {
             digitalWrite(salida[i], HIGH);
           }
           else
           {
             digitalWrite(salida[i], LOW);
           }
           http.end();
        }
        else
        {
           Serial.println("Error");
           break;
        }
        delay(500);   
     }
  }
}
