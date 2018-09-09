#include "HmacSha256.h"


void setup() {
  char *msg; 
  Serial.begin(115200);
  char *key = "secretKey";
  char *payload = "get";

  msg = compute_HMAC(key,payload);

  Serial.println(msg);


  char *msg1; 
  char *key1 = "secretKey1";
  char *payload1 = "get";
  msg1 = compute_HMAC(key1,payload1);
  Serial.println(msg1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
