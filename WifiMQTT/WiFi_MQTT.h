#include <WiFi.h>

#include <PubSubClient.h>






class WiFi_MQTT {

	public:
		
		WiFiClient espClient;
		PubSubClient client;		
		
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

		

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
};