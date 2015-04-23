#include <RF24/RF24.h>


using namespace std;

// This is also act as base value for sensor nodeId addresses.
// Change this (or channel) if you have more than one sensor network.
//#define BASE_RADIO_ID ((uint64_t)0xC0C0C0CF00LL)
#define BASE_RADIO_ID ((uint64_t)0x1212121200LL)
#define RADIO_CHANNEL 98


// This is the nodeId for sensor net gateway receiver sketch (where all sensors should send their data).
#define GATEWAY_ADDRESS ((uint8_t)0)
#define BROADCAST_ADDRESS ((uint8_t)0xFF)
#define TO_ADDR(x) (BASE_RADIO_ID + x)

#define WRITE_PIPE ((uint8_t)0)
#define CURRENT_NODE_PIPE ((uint8_t)1)
#define BROADCAST_PIPE ((uint8_t)2)


RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}






void setup_radio(void)
{
    // init radio for reading
    radio.begin();
    radio.enableDynamicPayloads();
    radio.setAutoAck(true);
radio.setAutoAck(BROADCAST_PIPE, false); // Turn off auto ack for broadcast	
radio.enableAckPayload();
    radio.setRetries(15,15);
    radio.setDataRate(RF24_250KBPS);
//    radio.setDataRate(RF24_1MBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(RADIO_CHANNEL);
    radio.setCRCLength(RF24_CRC_16);
//radio.openWritingPipe(0xF0F0F0F0D2LL);
// All nodes listen to broadcast pipe (for FIND_PARENT_RESPONSE messages)
radio.openReadingPipe(BROADCAST_PIPE, TO_ADDR(BROADCAST_ADDRESS));

radio.openReadingPipe(WRITE_PIPE, BASE_RADIO_ID);
radio.openReadingPipe(CURRENT_NODE_PIPE, BASE_RADIO_ID);


  
  //  radio.openReadingPipe(3, 0xF0F0F0F0E1LL);
  
      radio.printDetails();

  
//    radio.powerUp();
//    radio.startListening();


}


