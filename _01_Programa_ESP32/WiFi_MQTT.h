#include <WiFi.h>
#include "HmacSha256.h"
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client;		
char mensaje[100];
bool auth=0;
int flag_msg_recibido = 0;
char *mensaje_recibido;
void init(const char* ssidd, const char* pswd, const char* mqtt_Server ,const int mqtt_Port ,const char* mqtt_Usr ,const char* mqtt_Pswd ){
	
	client.setClient(espClient);
	
	WiFi.begin(ssidd, pswd);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.println("Connecting to WiFi..");
	}

	Serial.println("Connected to the WiFi network");

	client.setServer(mqtt_Server, mqtt_Port);
	

	while (!client.connected()) {

		Serial.println("Connecting to MQTT...");

		if (client.connect("ESP32Client", mqtt_Usr, mqtt_Pswd )) {

			Serial.println("connected"); 
			client.publish("esp/test1", "ESP32 conectado !"); 
		} 
		else { 

			Serial.print("failed with state ");
			Serial.print(client.state());
			delay(2000);
		}
	}
	client.subscribe("esp/test");
}

void callback(char* topic, byte* payload, unsigned int length) { //Estas variables son de este scope, no se pueden utilizar en otro lado
  
  flag_msg_recibido=0;
  auth=0;
  delay(100);
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  //Serial.print("Message:");
  for (int i = 0; i < length; i++) {

    mensaje[i]=payload[i];
    Serial.print((char)payload[i]);
  }
  
  client.publish("esp/test1", "Mensaje recibido!");
  flag_msg_recibido=1;
  delay(100);
  Serial.println();
  Serial.println("-----------------------");

  //char *mensaje ; 
  
  char *hmac_recibido;
  char *hmac_generado;
  char *key = "secretKey";
  
    /*  EXTRAEMOS EL MENSAJE RECIBIDO */
  mensaje_recibido = get_msg(mensaje);
  Serial.println("El mensaje recibido es: ");  
  Serial.print(mensaje_recibido);
  Serial.print(" y tiene una longitud de:  ");  
  Serial.print(strlen(mensaje_recibido));  

  /* EXTRAEMOS LA FIRMA DIGITAL */
  hmac_recibido = get_digital_sig(mensaje);
  Serial.println();
  Serial.println("El HMAC recibido es: ");
  Serial.println(hmac_recibido);

  /* GENERAMOS LA FIRMA DIGITAL QUE DEBERÍA SER */
  hmac_generado  = compute_HMAC(key,mensaje_recibido);
  Serial.println("El HMAC debería ser: ");
  Serial.println(hmac_generado);
  Serial.println();
  
  /* COMPARAMOS AMBAS FIRMAS */
  auth = comparacion(hmac_recibido,hmac_generado);
  if(auth == true) Serial.println( "Las firmas son iguales ! El mensaje es auténtico!");
  else Serial.println( "Las firmas son diferentes! El mensaje no es auténtico! ");
 
}
		

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
