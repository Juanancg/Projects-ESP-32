#include "Wifi_MQTT.h"
WiFi_MQTT Esp32;
/* WiFi */
const char* ssid = "      ";
const char* password =  "        ";

/* MQTT - Utilizando CloudMQTT */
const char* mqttServer = "      ";
const int mqttPort =  ;
const char* mqttUser = "       ";
const char* mqttPassword = "   ";

char mensaje[100];
    void callback(char* topic, byte* payload, unsigned int length) { //Estas variables son de este scope, no se pueden utilizar en otro lado
      
      delay(100);
      Serial.print("Message arrived in topic: ");
      Serial.println(topic);

      //Serial.print("Message:");
      for (int i = 0; i < length; i++) {

        mensaje[i]=payload[i];
      //Serial.print((char)payload[i]);
      }
      
      Esp32.client.publish("esp/test1", "Mensaje recibido!");
      delay(100);
      Serial.println();
      Serial.println("-----------------------");
     
    }
void setup() {
 
  Serial.begin(115200);
  delay(2000); //Necesito tiempo para abrir la consola!
  
  Esp32.init(ssid,password,mqttServer,mqttPort,mqttUser,mqttPassword);
  Esp32.client.setCallback(callback);
  //client.publish("esp/test", "Hello from ESP32"); //Primero el "Tópico" y segundo el mensaje
 
}
 
void loop() {
  Esp32.client.loop();
  //Esp32.client.publish("esp/test", "Hello from ESP32");
  delay(2000);
}

