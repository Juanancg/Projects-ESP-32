#include <WiFi.h>

#include <PubSubClient.h>
 
/* WiFi */
const char* ssid = "****************";
const char* password =  "*************";

/* MQTT - Utilizando CloudMQTT */
const char* mqttServer = "*************";
const int mqttPort = **********;
const char* mqttUser = "**************";
const char* mqttPassword = "**********";
 
 

WiFiClient espClient;
PubSubClient client(espClient);

char msg_received[7]; // Solo debería recibir "Servo+90" o "Servo-90"

void callback(char* topic, byte* payload, unsigned int length) { //Función que es llamada cuando se un mensaje llega.   

  Serial.print("Message arrived in topic: ");

  Serial.println(topic);

  Serial.print("Message:");

  for (int i = 0; i < length; i++) {

    Serial.print(msg_received[i]=((char)payload[i])); //It works!!
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
  
  if(msg_received[0]=='H'){ //Actualmente, si el ultimo mensaje empieza por H, se repite todo el rato.
    Serial.print("He pasado!: ");
    Serial.println(msg_received);
  }
//  int giro=0; //Probablemente esta variable se tenga que poner fuera para no resetearla (Probar con un codigo simple de en el loop poner i++;
//  CAMBIAR TODO ESTO ->
//  if (msg_received="Servo+90"){
//  
//    for(giro = 0;giro<MAX_PWN;giro++){
//      
//      analog.write(giro); //NO ES ASÍ !! SUBIR EL CODIGO A GITHUB PARA TENERLO ACCESIBLE
//    } 
//  }
}

