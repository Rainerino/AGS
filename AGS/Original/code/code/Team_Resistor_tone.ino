/*
 * Program name : Team_Resistor
 * Project name : Arduino Air Guitar System 
 * Purpose : outputs sound of guitar notes which are determined by several sensors: ultrasonic sensor, accelerometer, and photoresistors 
 * Author: Ringo Wong, John Kim, Carmen Sing, Harry Li, Yiyi Yan
 * Date: 21 Mar 2016 to 18 April 2016
 * Course: CPSC 1490 Langara College
 * 
 * Note : Serial Output functions ( for monitoring ) are commented out
 */

#include "Project.h"
Project guitar; // initialize class

void setup() 
{
  guitar.setPin();
}
void loop() 
{
  guitar.playSound(); 
}
