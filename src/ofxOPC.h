#include "ofMain.h"
#include "ofxNetwork.h"

class ofxOPC  {
    
public:
    
    string _address;
    int _port;
    int _w,_h;
    
    void setup(string address,int port,ofVec2f layout);
    
    void draw();
    void update();
    
    void begin();
    void end();
    
    void writeData(vector <uint8_t> &data);
    void writeData(uint8_t *data,int size);
    void close();

    bool isConnected();
    bool tryConnecting();
    
    vector <uint8_t> txData;
    vector <ofColor> colors;
    
private:
    void connect();
    void disconnect();
    ofxTCPClient client;
    ofFbo windowTexture;
    ofPixels pixels;
};