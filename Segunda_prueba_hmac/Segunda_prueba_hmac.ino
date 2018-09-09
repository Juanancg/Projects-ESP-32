#include "HmacSha256.h"

/* CÓDIGO PARA TRABAJAR CON HMAC-SHA256
 *  
 *  La idea es comunicarse con otro programa, pero para probar el código
 *  firmamos digitalmente un mensaje. Este mensaje será el utilizado como
 *  mensaje que hemos recibido y tenemos que comprobar su autenticidad.
 *  
 */

void setup() {
  char *mensaje ; 
  char *mensaje_recibido;
  char *hmac_recibido;
  char *hmac_generado;
  char hash[64];
  bool auth;
  
  Serial.begin(115200);
  char *key = "secretKey";
  char *payload = "get";
  char *key1 = "secretKey1";

  /* CALCULAMOS EL HMAC DEL MENSAJE A ENVIAR */
  mensaje = compute_HMAC(key1,payload);
  strcat(mensaje,payload);
  Serial.println(mensaje);

  /*  EXTRAEMOS EL MENSAJE RECIBIDO */
  mensaje_recibido = get_msg(mensaje);
  Serial.println("El mensaje recibido es: ");  
  Serial.println(mensaje_recibido);

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

void loop() {
  

}
