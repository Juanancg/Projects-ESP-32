#ifndef COORDINADOR_H
#define COORDINADOR_H

#include "HmacSha256.h"
#include "WiFi_MQTT.h"

class Coordinador {

  public:

    //char mensaje[100];
    bool auth = 0;
    char *mensaje_recibido;
  
    bool check_auth(char *mensaje_to_check) {


      char *hmac_recibido;
      char *hmac_generado;
      char *key = "secretKey";

      /*  EXTRAEMOS EL MENSAJE RECIBIDO */
      mensaje_recibido = get_msg(mensaje_to_check);
      //      Serial.println("El mensaje recibido es: ");
      //      Serial.print(mensaje_recibido);
      //      Serial.print(" y tiene una longitud de:  ");
      //      Serial.print(strlen(mensaje_recibido));

      /* EXTRAEMOS LA FIRMA DIGITAL */
      hmac_recibido = get_digital_sig(mensaje_to_check);
      //      Serial.println();
      //      Serial.println("El HMAC recibido es: ");
      //      Serial.println(hmac_recibido);

      /* GENERAMOS LA FIRMA DIGITAL QUE DEBERÍA SER */
      hmac_generado  = compute_HMAC(key, mensaje_recibido);
      //      Serial.println("El HMAC debería ser: ");
      //      Serial.println(hmac_generado);
      //      Serial.println();

      /* COMPARAMOS AMBAS FIRMAS */
      auth = comparacion(hmac_recibido, hmac_generado);
      flag_msg_recibido = 0;
      return auth;
      //      if(auth == true) Serial.println( "Las firmas son iguales ! El mensaje es auténtico!");
      //      else Serial.println( "Las firmas son diferentes! El mensaje no es auténtico! ");
    }

};


#endif
