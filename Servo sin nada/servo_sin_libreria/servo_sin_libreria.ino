
#define SERVO_PIN 5
int freq = 50; //El servo trabaja a 50 Hz
int channel = 0;
int resolution = 10; //Resolución de 10 bits



void setup() {
  Serial.begin(115200);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(SERVO_PIN, channel);
  
}

void loop() {

    int i;
    i=26; // 0.5 ms (-90°)*2^10/20ms = 26
    Serial.println(i);
    ledcWrite(channel, i);      
    delay(1000);  
    i=123; // 2.4 ms (+90°)*2^10/20ms = 123
    Serial.println(i);
    ledcWrite(channel, i);       
    delay(1000);  

}
