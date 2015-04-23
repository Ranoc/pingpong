// compile with:
// g++ -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -Wall -I../ -lrf24-bcm nRF24l01_receive.cpp -o nRF24l01_receive

#include <cstdlib>
#include <iostream>

#include <string>
#include <sstream>
#include <vector>

#include "pingpong.h"

unsigned int  errors = 0;
unsigned long last = 0;
//buffer[64];
uint8_t pipe_num;
void loop(bool sendAck){
	
	if(radio.available(&pipe_num))
	{
		
		// read from radio until payload size is reached
        //uint8_t len = radio.getDynamicPayloadSize();
		unsigned long value;
        radio.read(&value, sizeof(unsigned long));
		
		// send ack
		if(sendAck) {
			unsigned char ack = (value & 0xff);
			radio.powerUp();
			radio.writeAckPayload( pipe_num, &ack, sizeof(unsigned char) );
            // Now, continue listening
            radio.powerUp();
            radio.startListening();
		}
		
		if(last==0 || last+1==value) {
			// OK 
			cout << "OK !" << endl;
			
		} else {
			// errore
			++errors;
			cout << "ERRORE N. " << errors << endl;
		}
		last = value;
		
	}
	
	
	
}




int main(int argc, char** argv){
	
	setup_radio();
	
	//cout << "Tu sei qui" << endl;
	
	
	radio.powerUp();
	radio.startListening();
	while(1) loop(false);	
	return 0;
	
}


