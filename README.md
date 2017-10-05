## Project name: Air Guitar System(AGS)

Group memeber: 

Carmen Sing

John Kim

Yiyi Yan

Harry Li

Ringo Wong

## Introduction

The Air Guitar System (AGS) is designed to mimic the abilities of an electric guitar but playability of a simple button pushing device.  

Much of the design consideration has been geared towards stimulating accurate sound of electric guitar and creating easy to use interface in order to mitigate a learning curve.  

With these requirements in mind, our team created a fully functional instrument that can be played anytime, anywhere.  Our "guitar" do not require strings, large sound board or further tuning.  Aside from mimicking the ability of a regular guitar to stop music and vary volumes based on strumming patterns, many additional features have been included to improve upon a regular guitar such as one for all strumming distance, virtual button replacing the painful picking experiencec. 

## Motivation

Throughout history a common outlet for creativity is through music.  Research has shown that guitar is gaining traction by fast becoming the most popular instrument played due to its versatility, relatively lower cost (compared to pianos) and the rise of rock and pop music.  Our team aims to bring the freedom of creative expression to everyone while addressing some common complaints.  There have been similar projects in the past, however, our project aims to further improve the instrument by targeting problematic areas such as further reducing the cost of, and improving the portability and ease of composition.  We aim to accomplish two things: to simplify the instrument and to construct an intuitive design.  

## Prerequisities
* [Arduino](https://www.arduino.cc/en/Main/Software)
* [SFE_MMA8452Q library](https://learn.sparkfun.com/tutorials/mma8452q-accelerometer-breakout-hookup-guide/example-code)
* [toneAC library](https://playground.arduino.cc/Code/ToneAC)

## Modules 
Modules | Designation
--- | :---:
1 | Team_Resistor (main)
2 | Components
3 | Sound Calculation

### Components

This module is implemented in Project.header file. The functions of Components module included ultrasonic(), accGyro(), buttons() and pitch(). Each of the functions act as the driver for each sensors. 

### Sound Calculation

This module composes of two functions: playSound(), setPin() and the header file pitch.h, which has the wave defination od different notes to generate a song. The array chords in the Project header is a tester for the function. 

## Code Example

\#include "Project.h"
Project guitar; 
void setup() 
{
  guitar.setPin();
}
void loop() 
{
  guitar.playSound(); 
}


## References

Included in the folder

## Contributors
Carmen Sing: csing00@langara.bc.ca

John Kim:hkim52@langara.bc.ca

Yiyi Yan: yyan10@langara.bc.ca

Harry Li: mli43@langara.bc.ca 

Ringo Wong: rwong22@langara.bc.ca 



