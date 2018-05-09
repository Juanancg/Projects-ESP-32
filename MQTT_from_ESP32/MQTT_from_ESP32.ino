#include <WiFi.h> //Libreria necesaria para conectarse a la WiFi
 
#include <PubSubClient.h> //Libreria necesaria para publicar mensajes en MQTT

/* WiFi */
const char* ssid = "*******************";
const char* password =  "***************";
/* MQTT - Utilizando CloudMQTT */
const char* mqttServer = "****************";
const int mqttPort = ********;
const char* mqttUser = "***********";
const char* mqttPassword = "***********";
 
WiFiClient espClient; //Objeto que permite establecer una conexión a una IP y puerto definidos 
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  delay(2000); //Necesito tiempo para abrir la consola!
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network !!");

 
  client.setServer(mqttServer, mqttPort); // Establecemos a que servidr MQTT queremos conectarnos
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP32"); //Primero el "Tópico" y segundo el mensaje
 
}
 
void loop() {
  client.loop();
}
