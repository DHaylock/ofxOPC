#include "ofMain.h"
#include "ofxNetwork.h"
#include "NeoPixelRing24px.h"
#include "NeoPixelRing16px.h"
#include "NeoPixelRing12px.h"
#include "NeoPixelStrip.h"
#include "NeoPixelGrid8x8.h"
#include "NeoPixelShield5x8.h"


#define NUM_BYTES 4+(24*3)

enum NeoPixelUnit{
    OFX_NEOPIXEL_RING24PX,
    OFX_NEOPIXEL_RING16PX,
    OFX_NEOPIXEL_RING12PX,
    OFX_NEOPIXEL_STICK,
    OFX_NEOPIXEL_STRIP,
    OFX_NEOPIXEL_GRID,
    OFX_NEOPIXEL_SHIELD
};

struct NeoPixelUnitInfo{
    int NUM_OF_BYTES;
    
};

class ofxOPC  {
    
public:
    
    string _address;
    int _port;
    int _w,_h;
    
    void setup(string address,int port);
    
    void setDithering(bool enabled = true);
    void setInterpolation(bool enabled = true);
    
    void setStatusLED(bool value);
    
    void sendFirmwareConfigPacket();
    
    void draw();
    void update();
    
    
    void writeChannelOne(ofPixels pix);
    void writeChannelTwo(vector <uint8_t> data);
    void writeChannelThree(vector <uint8_t> data);
    
    void close();

    bool isConnected();
    void tryConnecting();
    
  
    vector <uint8_t> txData;
    vector <ofColor> colors;
    
    unsigned char * packetData[4+(24*3)];
    unsigned char * firmwareConfig;
    
private:
    void connect();
    void disconnect();
    ofxTCPClient client;
};