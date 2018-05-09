#include <WiFi.h>

#include <PubSubClient.h>

const char* ssid = "yourNetworkName";

const char* password =  "yourNetworkPassword";

const char* mqttServer = "m11.cloudmqtt.com";

const int mqttPort = 12948;

const char* mqttUser = "yourMQTTuser";

const char* mqttPassword = "yourMQTTpassword";

 
//char* msg_received[7] = "Servo+90" o "Servo-90"
WiFiClient espClient;

PubSubClient client(espClient);


void callback(char* topic, byte* payload, unsigned int length) { //Función que se llama cuando se un mensaje llega.   

  Serial.print("Message arrived in topic: ");

  Serial.println(topic);

  Serial.print("Message:");

  for (int i = 0; i < length; i++) {

    Serial.print(msg_received[i]=((char)payload[i])); //Probar esto en Visual Studio 

  }
  Serial.println();
  Serial.println("-----------------------");

}

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {

    Serial.println("Connecting to MQTT...");
    
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {

      Serial.println("connected");  
    } 
    else { 

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  client.subscribe("esp/test");
}

 

void loop() {

  client.loop();
  
  //Controlar el servo
  
  int giro=0; //Probablemente esta variable se tenga que poner fuera para no resetearla (Probar con un codigo simple de en el loop poner i++;
  
  if (msg_received="Servo+90"){
  
    for(giro = 0;giro<MAX_PWN;giro++){
      
      analog.write(giro); //NO ES ASÍ !! SUBIR EL CODIGO A GITHUB PARA TENERLO ACCESIBLE
    } 
}
}

