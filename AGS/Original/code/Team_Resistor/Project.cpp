  
 #include "Project.h"

 const int chords[4][5] = { { NOTE_GS2, NOTE_G2, NOTE_FS2, NOTE_F2, NOTE_E2 },   // frequencies of 4 strings and 5 frets of a guitar ( bass guitar ) 
                          { NOTE_CS3, NOTE_C3, NOTE_B2, NOTE_AS2, NOTE_A2 },     // chords[string#][fret#] 
                          { NOTE_FS3, NOTE_F3, NOTE_E3, NOTE_DS3, NOTE_D3 },
                          { NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_GS3, NOTE_G3 } };
                      
 const int soundDecay[] = { 10, 9, 8, 7, 6, 4, 2, 0 }; // set of volumes for sound fading sequecence
 
  Project::Project()
  {
    //default pitch
    PITCH = 39;
    index = 0;
  }
  
  /* Ultrasonic()
   * The following function returns the corresponding NOTE# based on the distance reading from the ultrasonic sensor
   * NOTE: the NOTE return can be bigger than 3. The filter function is pitch
   * 
   * @parameter(void)
   * @return(int) (NOTE_number) - the NOTE number from user
  */
  int Project::ultrasonic()
  {
    
   //the maximum value of raw data from ultrasonic
   int temp = 16000;
   
   // collect data three times, and use the smallest value to improve accuracy 
   // single data reading takes approximately 60ms average
   
  for(int i = 0 ; i < 3 ; i++)
  {
    // emit ultrasonic sound wave  (trigger)
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5); 
    digitalWrite(trigPin, LOW);

    // time took to recieve the emitted ultrasonic (reciever)
    duration = pulseIn(echoPin, HIGH, 3000);
    
    if( duration != 0)
    {
      //if raw data ( duration ) is not zero ( out of bound or error ), store the minimum value
      temp = min(temp, duration);
    }
    else
    {
      //if raw data is zero ( out of bound or error ) read data again
      i--;
    }
  }
  
    //convert raw data to the distance for easier calculation ( arbitrary unit )
    distance = temp / 20;
    
    //map the distance into 5 regions ( 0 to 4 ), which will be considered as NOTE#
    fret_number = map( distance, MinDistance, MaxDistance, 0, NoteSize - 1 );
    
    /* 
     * The following function controls the LED's based on the value of distance 
     * the LED's will light up to corresponding regions and help user visulalize which NOTE is being played
     * 
     */
    switch (fret_number)
    {
      case 0:  // open string 
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
      
      case 1:  // first NOTE 
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      break;
      
      case 2:  //second NOTE 
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      break;
      
      case 3:  //third NOTE 
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      break;
      
      case 4:  //fourth NOTE
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, HIGH);
      break;
      
      default: 
      break;
    }
    return fret_number;
}

/*
 * accGyro()
 * The following function will return a volume between 0 and 10 based on the acceleration of the accelerometer 
 * Default volume is 2 
 * 
 * @parameter(void)
 * @return(double) (temp) - movement of the accelerometer ( strumming )
 */
  double Project::accGyro()
  {
    if ( accel.available() ) //if accelerometer is available 
    {
        accel.read(); // take raw reading
        currAcc = accel.cx + 4; // x-axis coordinate value is stored 
        double temp = abs(currAcc - lastAcc); // stores the difference in coordinates 
        lastAcc = currAcc; // stores to compare it with the next reading
        return temp;
      }
  }
  
  /*
   * The following function deteremines the string# from photoresistor reading value
   * returns string# of 0, 1, 2, 3 
   * 
   * @parameter(void)
   * @return(int) - the string number user inputs
   */
  int Project::buttons()
  {
    //read photoresistor, and if covered with finger, return true ( 1 )
    button_1 = ( analogRead(button1Pin) < lightBrightness ) ? 1 : 0 ; 
    button_2 = ( analogRead(button2Pin) < lightBrightness ) ? 1 : 0 ; 
    button_3 = ( analogRead(button3Pin) < lightBrightness ) ? 1 : 0 ; 
    button_4 = ( analogRead(button4Pin) < lightBrightness ) ? 1 : 0 ; 
 
    if( ( button_1 == 1 && button_2 == 0 && button_3 == 0 && button_4 == 0 ) ) // button_1 represents first string 
    {
      return 0;
    }
    else if( button_1 == 0 && button_2 == 1 && button_3 == 0 && button_4 == 0 ) // button_2 represents second string 
    {
      return 1;
    }
    else if( button_1 == 0 && button_2 == 0 && button_3 == 1 && button_4 == 0 ) // button_3 represents third string 
    {
      return 2;
    }
    else if( button_1 == 0 && button_2 == 0 && button_3 == 0 && button_4 == 1 ) // button_4 represents fourth string 
    {
      return 3;
    }
    else
    {
      return 4; //error vaule
    }
}

    /* playSound()
     * chooses the corresponding frequency and outputs to the speaker
     * 
     * @parameter(void)
     * @return(void)
     */
  void Project::playSound()
  {
      fret = ultrasonic(); // the fret number 
      double temp = accGyro();
      string = buttons(); // the string number
      
      pitch(fret, string); // call function pitch()

      if( temp > miniVolume ) // if the value exceeds the maximum possible value
      { 
        index = 0; // volume is 0 
      }
        index = (index < sizeOfDecay) ? index : sizeOfDecay - 1; // when strumming ends, fade out the sound 
        volume = soundDecay[index++]; // the sound fades out in the patter defined as an array 
       
        toneAC(PITCH, volume); // output the note to the corresponding volume
        delay(50); // delay to eliminate any error
  }
  
  /* pitch()
   * The following function filters noise crated by ultrasonic sensor and 
   * buttons. selection 1 will filter the NOTEs and election 2 will filter the buttons
   * and store the frequency of the note to a variable 
   * 
   * @parameter(int)(fret) & (string) - fret number and string number from the functions above
   * @return (void)
   */
  void Project::pitch(int fret, int string)
  {
    if(string != 4 && fret <= 4 && fret >= 0) // if the values are valid 
    {
       // store the frequency of the corresponing notes
       PITCH = chords[string][fret]; 
       //store 
       previousString = string;
    }
    else if(fret <= 4 && fret >= 0) //if values from the ultrasonic sensor are not valid 
    {
       // store the frequency of the corresponding notes from the previous execution
       PITCH = chords[previousString][fret];
    }
  }
  
  /* setPin()
   * The following function will initiate all the pins including leds, us, buttons
   * and the accelerometer object
   * 
   * @parameter(void)
   * @return(void) 
   */
void Project::setPin()
{
    //BAUD rate initialize for Arduino Mega
    Serial.begin(9600);
    
    // Initialize LED pins
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    // Initialize ultrasonic pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Initialize Accelerometer
    accel.init(SCALE_4G, ODR_800);

    // Initialize photoresistor pins
    pinMode(button1Pin, INPUT);
    pinMode(button2Pin, INPUT);
    pinMode(button3Pin, INPUT);
    pinMode(button4Pin, INPUT);
    
}

