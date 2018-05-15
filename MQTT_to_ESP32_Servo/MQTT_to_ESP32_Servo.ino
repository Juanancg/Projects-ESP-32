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


char msg_received[7]; // Solo puede recibir "Servo+90" o "Servo-90"
int flag=0; 

void callback(char* topic, byte* payload, unsigned int length) { //Función que se llama cuando se un mensaje llega.   

  Serial.print("Message arrived in topic: ");

  Serial.println(topic);

  Serial.print("Message:");

  for (int i = 0; i < length; i++) {

    Serial.print(msg_received[i]=((char)payload[i])); //It works!!
  }
  Serial.println();
  Serial.println("-----------------------");
  flag=0;

}


/* SERVO */
#define SERVO_PIN 18
int freq = 50; //El servo trabaja a 50 Hz
int channel = 0;
int resolution = 10; //Resolución de 10 bits



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

  //Configuración del SERVO
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(SERVO_PIN, channel);  
  ledcWrite(channel, 61); //Para llevarlo a 90 
}



void loop() {

  client.loop();
  
  //Controlar el servo
  if(msg_received[0]=='1' && flag==0){ // 1 -> 26 = -90º
    Serial.print("Moviendo servo a posición: ");
    Serial.println(msg_received);
    ledcWrite(channel, 26);      
    delay(1000);
    flag=1;
  }

  if(msg_received[0]=='2' && flag==0){ // 2 -> 61 = 0º
    Serial.print("Moviendo servo a posición: ");
    Serial.println(msg_received);
    ledcWrite(channel, 61);      
    delay(1000);
    flag=1;
  }  

  if(msg_received[0]=='3' && flag==0){ // 3 -> 123 = +90º
    Serial.print("Moviendo servo a posición: ");
    Serial.println(msg_received);
    ledcWrite(channel, 123);      
    delay(1000);
    flag=1;
  }   

}

