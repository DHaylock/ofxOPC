ofxOPC
======

A openFrameworks addon for Open Pixel Control and FadeCandy Server

ofxOPC is an addon for openFrameworks (v0.8.0+) that allows users to communicate to Neopixel LED units through Fadecandy and open pixel control. Draw graphics to the oF window, place the Neopixel grabber on the screen and the addon collects, encodes and sends the pixel data to the Fadecandy.

It is a work in progress and there are still some issues that need to be addressed. However, it works as it stands.

If you would like to contribute to the addon feel free to fork, hack and mod the code.
Also drop me a line and let me know how you end up using the addon.

@david_haylock

## Requirements

- openFrameworks v0.8.0+
- ofxNetwork - comes as part of the openFrameworks download
- Fadecandy unit @scanlime
- Fadecandy server <a href='https://github.com/scanlime/fadecandy'>https://github.com/scanlime/fadecandy</a> 

## What the addon includes

- The ofxOPC client class
- So far every (known) Neopixel unit in its own class with its own implementation.
- 12px Ring
- 16px Ring
- 24px Ring
- 60px Ring
- Neopixel Strip
- Neopixel Stick
- Neopixel Grid 8x8
- Neopixel Grid 32x32
- Neopixel Shield 5x8

## Getting Started

- After downloading ofxOPC, place it inside your openFrameworks addon folder.

- Create a new openFrameworks project in Project Generator and select the ofxOPC and ofxNetwork addons.

- Alternatively you will need to add the addons manually, drag and drop the folders into the addon folder in xCode. Then make sure the paths are linked inside Build Settings. 

- In your testApp.h or ofApp.h file, link the addon's .h file, by adding  ```#include "ofxOPC.h"``` underneath ```#include "ofMain.h"```.

- Create an ofxOPC client and a Neopixel unit in your .h file.

<code>
	ofxOPC opcClient;
	NeoPixelRing24px ring;
</code>

- Then in the .cpp file setup the LED unit and the OPC client.

<code>
	opcClient.setup("127.0.0.1", 7890);
	ring.setupLedRing();
</code>

- Then grab the image data you want by positioning the grabber over the area. The isConnected method protects the application from crashing if connection is lost to the server.

<code>
	ring24px.grabImageData(ofPoint(ofGetWidth()/2,ofGetHeight()/2));
    
    ring24px.update();
    
    if (!opcClient.isConnected())
    {
        opcClient.tryConnecting();
    }
    else
    {
        opcClient.writeChannelOne(ring24px.colorData());
    }
</code>

- Draw the resulting data to our visualisor

<code>
    ofBackground(0);
   
    ring24px.drawGrabRegion(hide);

    ring24px.drawRing(50, 50);
</code>

- Your Leds should start to flash or fade depending on what you put underneath the grabber.

- See the examples for more specific details on each of the Neopixel units.

## Examples
- 12px Ring
- 16px Ring
- 24px Ring
- 60px Ring
- Neopixel Strip
- Neopixel Stick
- Neopixel Grid 8x8
- Neopixel Shield 5x8
- Neopixel Multiple Strips
- Neopixel Chained Rings
- Multiple Neopixel units and Syphon

## Important 

- The Fadecandy drives 8 x 64 LEDS = 512 LEDs, thats one DMX Universe. However, each pin only drives 64 LEDs. If you want to connect 1 or more units with 64 LEDs each, separate the data accross two channels. For clarity and less risk of overwriting your data.

<code>
	opcClient.writeChannelOne(ring60px.colorData());
	opcClient.writeChannelTwo(ring60px.colorData());
</code>

If you would like to use the 32x32grid please alter line 24 of ofOPC.cpp from

<code>uint16_t data_length = 8 * 64 * sizeof(OPCPacket_SPCData_t);</code>

to 

<code> uint16_t data_length = 16 * 64 * sizeof(OPCPacket_SPCData_t);</code>

To use the 32x32 grid check this guide.

<a href='http://docs.pixelmatix.com/SmartMatrix/'>http://docs.pixelmatix.com/SmartMatrix/</a>

Thanks to @rorypickering.

## To Do

- Allow users to specify the size of the elements in setup procedure
- Create return methods with data about the elements.
- Need to Create a Single Neopixel unit
