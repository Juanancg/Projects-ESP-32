#include "HmacSha256.h"


void setup() {
  char *mensaje; 
  Serial.begin(115200);
  char *key = "secretKey";
  char *payload = "get";

  mensaje = compute_HMAC(key,payload);

  Serial.println(mensaje);

}

void loop() {
  // put your main code here, to run repeatedly:

}
