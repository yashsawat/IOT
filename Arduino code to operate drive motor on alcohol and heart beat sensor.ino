#define USE_ARDUINO_INTERRUPTS true                     //Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>                      //Includes the PulseSensorPlayground Library.   
//Variable Declaration
const int PulseWire = 0;                                // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED_3 = 13;                                    //LED to detect when the heart is beating. The LED is connected to PIN 3 on the Arduino UNO.
const int Motor = 2;
const int Buzzer = 3;
int Threshold = 550;                                      //Determine which Signal to "count as a beat" and which to ignore.
PulseSensorPlayground pulseSensor;                        //Creates an instance of the PulseSensorPlayground object called "pulseSensor"
void setup() {   
  Serial.begin(9600);                                     //Set's up Serial Communication at certain speed.
  pinMode(13,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED_3);                           //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);
  if (pulseSensor.begin()) {
    Serial.println("Welcome to my project !");               //This prints one time at Arduino power-up,  or on Arduino reset.  
  }   
}
void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute();             //Calls function on our pulseSensor object that returns BPM as an "int". "myBPM" hold this BPM value now.
  int alcohol=analogRead(A1);
  
  
  
  
  /*if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
  //Serial.println("♥  A HeartBeat Happened ! ");

} */
  if(myBPM>60&&myBPM<130 && alcohol<450)
  {
      
      Serial.println("Normal Alcohol level");
      Serial.println("BPM :");
      Serial.println(myBPM);
      
      digitalWrite(2,LOW);
      digitalWrite(4,HIGH);  
       
             
  }
  else if(alcohol>=450)
  {
           
           
           digitalWrite(4,LOW);
           digitalWrite(2,HIGH);
           Serial.println("High alcohol level detected :");
           
           
                  
  }
  else{
    
  Serial.println("Abnormal BPM");
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  
    }
     delay(5000) ;                                                
}
