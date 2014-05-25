#include "ofMain.h"
#include "ofxNetwork.h"

enum {
    OFX_LED_TYPE_RING,
    OFX_LED_TYPE_STRIP,
    OFX_LED_TYPE_GRID
};

class ofxOPC  {
    
public:
    
    string _address;
    int _port;
    int _w,_h;
    
    void setup(string address,int port,ofVec2f layout);
    void setup(string address, int port, int layout);
    void draw();
    void update();
    
    void setupLedRing(int size,float x, float y,float radius);
    vector <ofColor> ringColors;
    vector <ofVec2f> ringPos;
    int _rw,_rh;
    int _radius;
    int _size;
    
    // Draw into the FBO
    void begin();
    void end();
    
    void writeData();
    void writeData(uint8_t data,int size);
    void close();

    bool isConnected();
    bool tryConnecting();
    
    // Set Type of NeoPixel
    
    void drawRing(int x, int y);
    void ledStrip(int count, float x, float y, float spacing);
    void ledRing(int count, float x, float y, float radius);
    void ledGrid(int index, int stripLength, int numStrips, float x, float y,
                 float ledSpacing, float stripSpacing, float angle, bool zigzag);
    void ledGrid8x8(int index, float x, float y, float spacing, float angle, bool zigzag);
    
    vector <uint8_t> txData;
    vector <ofColor> colors;

    
private:
    void connect();
    void disconnect();
    ofxTCPClient client;
    ofFbo windowTexture;
    ofFbo ringTexture;
    ofPixels pixels;
    ofPixels ringPixels;
};