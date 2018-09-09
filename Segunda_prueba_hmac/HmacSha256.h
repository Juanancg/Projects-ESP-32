#include "mbedtls/md.h"

char mensaje[1000];

char* compute_HMAC(char* key, char* payload){
	
	
	//char *key = "secretKey";
	//char *payload = "get";
	byte hmacResult[32];

	mbedtls_md_context_t ctx;
	mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

	const size_t payloadLength = strlen(payload);
	const size_t keyLength = strlen(key);            

	mbedtls_md_init(&ctx);
	mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
	mbedtls_md_hmac_starts(&ctx, (const unsigned char *) key, keyLength);
	mbedtls_md_hmac_update(&ctx, (const unsigned char *) payload, payloadLength);
	mbedtls_md_hmac_finish(&ctx, hmacResult);
	mbedtls_md_free(&ctx);


	
	for(int i = 0; i< sizeof(hmacResult); i++){
		char str[3];
		int x = 0;
		sprintf(str, "%02x", (int)hmacResult[i]);
		
		if(i==0){strcpy(mensaje,str);}
		else{
			strcat(mensaje, str);
		}
		// for(int z = 0; z < 3 ; z++){
			// x = i*3 + z;
			// mensaje[x] = str[z];
			// Serial.print(mensaje[x]);
		// }
	  
	}
	
	Serial.println();
	strcat(mensaje,payload);
	return (mensaje);

}

	