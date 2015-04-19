#include <Trackpoint.h>

/*
 * Created on 14/03/2014
 * Author: Cong Nguyen
 *
 * Using an Arduino Leonardo to interface with a TrackPoint
 * Pin 3 (int.0)	: CLOCK
 * Pin 2			: DATA
 * Pin 4			: RESET
 */


#define	CLOCK		3
#define DATA		2
#define RESET		0
#define CLOCK_INT	0
#define LEFT_BUTTON     4
#define RIGHT_BUTTON    5

TrackPoint trackpoint(CLOCK, DATA, RESET, true);
int leftButtonState = 0;
int rightButtonState = 0;

void setup()
{	
        pinMode(LEFT_BUTTON, INPUT);
       // pinMode(RIGHT_BUTON, INPUT);
       Serial.begin(9600);
	
        Mouse.begin();
  
	trackpoint.reset();
	trackpoint.setSensitivityFactor(0x1E);
	trackpoint.setStreamMode();

	attachInterrupt(CLOCK_INT, clockInterrupt, FALLING);
}

void loop()
{	
         leftButtonState = digitalRead(LEFT_BUTTON);
         rightButtonState = digitalRead(RIGHT_BUTTON);
         
         if(leftButtonState == HIGH)
         {
             //click
             Mouse.press(MOUSE_LEFT);
         }
         else 
         {
           Mouse.release(MOUSE_LEFT);
         }
         
         if(rightButtonState == HIGH)
         {
             //click
             Mouse.press(MOUSE_RIGHT);
         }
         else 
         {
           Mouse.release(MOUSE_RIGHT);
         }
         
         
	if(trackpoint.reportAvailable()) {
		TrackPoint::DataReport d = trackpoint.getStreamReport();
		Mouse.move(d.x, -d.y*2.3, 0);
	} 
	
}

void clockInterrupt(void) {
	trackpoint.getDataBit();
}
