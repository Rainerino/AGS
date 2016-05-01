
// Acclelerometer
#include <Wire.h> 
#include <SFE_MMA8452Q.h> 

#include <Arduino.h>

// Tone 
#include <toneAC.h>
#include "pitches.h"

//ultrasonic pins 
#define LED1 4
#define LED2 5
#define LED3 6 
#define LED4 7
#define trigPin 8
#define echoPin 9


//button pin
#define button1Pin A1
#define button2Pin A2
#define button3Pin A3
#define button4Pin A4

// US constants
const int USsize = 5;
const int MaxDistance = 80;
const int MinDistance = 10;
const int NoteSize = 6;

// button
const int lightBrightness = 60;

//Acc
const double miniVolume = 0.3;
const int sizeOfDecay = 8;

using namespace std;

class Project
{
private:

//US
  int fret_number;
  long duration, distance;
  
//AG
  MMA8452Q accel;
  double currAcc; 
  double lastAcc;

//buttons
  int button_1; 
  int button_2;
  int button_3;
  int button_4;  
  int buttonReturn;
  int previousString;
  
//sound
  long PITCH; // frequency 
  int fret;
  int oldNote;
  int volume;
  int index;
  int string;
  
public:
  Project();
  int ultrasonic();
  double accGyro();
  int buttons();
  void playSound();
  void pitch( int fret, int string );
  void setPin();
  
  };

