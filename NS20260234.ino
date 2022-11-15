// This blank Starter has all of the basics covered so you can focus on your code
// 2022-01-10 removed dotstar elements because the base M0 feather doesn't need it.
#include "globals.h" 
#include "RTClib.h"
unsigned short hist[4096] = {0}; 
unsigned histOffset = 2024; 

//initializing values later used in the loop
double x = 0 ; 
double xNow=0;
double xLast = 0 ;
double xNoisyLast = 0;
double xNoisyNow=0 ; 

void setup() {
  // put your setup code here, to run once:
  setup217Kit();
  Serial.print("\n\nMECH 217 Blank Starter\n\n"); 
  
  //Print titles for each output
  Serial.print("t" ",") ; 
  Serial.print("x_noisy" ",") ;
  Serial.print("d/dt_noisy" ",") ;
  Serial.print("delta_x" ",") ;
  Serial.print("delta_t" ",") ;
  Serial.println() ;
}

void loop() {
  // Update the global variables for the time in this loop
  timeLast = timeNow;      // the last time we went through the loop, microseconds
  timeNow = micros();      // the time we started this loop, microseconds
  dt = (timeNow - timeLast)/100000.; // the time difference since last loop, microseconds
  
  // put your main code here, to run repeatedly:

  // Leave the rest of this code in place, but comment out when you don't need it
//  Serial.printf("Average dt = %8.1f us, this loop %8.1f us, maximum %8.1f\n", 
//                  uno.dtAvg(), uno.dt(), uno.dtMax());

//  delay(20);  // delay only to slow things down so you can see

//  for (int i=0; i<4096; i++) hist[i] = 0; 
// double sum = 0 ; 
// double sum2= 0 ; 
//  for (int i=0; i<1000; i++) {

//   int k= getUniformNoise(21) +getUniformNoise(21)  ; 
//   hist[ k+histOffset]++; 
//   sum+=k;
//   sum2+=k*k ; 
//  }
//  Serial.printf("\nMean: %8.2f RMS: %8.2f\n", sum/1000,
//                  sqrt((sum2-sum*sum / 1000)/1000)); 
//  for (int i=0; i<4096; i++){
//    if (hist[i]) {
//      Serial.printf("%4d: %4d:", i-histOffset, hist[i]) ; 
//      for(int j=0; j<hist[i]; j+=4) Serial.print("*") ; 
//      Serial.println() ; 
//    }

//   }                
//  Serial.println() ; 
//  delay(10000) ; 
  
  

  xLast = x ; // value of x from last loop
  x = sin((timeNow/50000.)) * 2047.5 + 2047.5 ; //x value with sin wave
  double deltaX= x-xLast ; //difference between the current x value and the x value form last loop

  
  double xNoisyLast=xNoisyNow ; //value of noisy x from last loop
  double xNoisyNow = x + getUniformNoise(100) ; //x value with added noise
  double deltaNoisyX = xNoisyLast-xNoisyNow ; //difference between the current x value and the x value from the last loop
 
  double derivBase = deltaX/dt ; //derivative of the base x value
  double derivNoisy = deltaNoisyX/dt ; //derivative of noisy x value

  double time = (timeNow/100000.) ; //current time value since loop started in seconds

  


//print each of the computed values
  Serial.print(time) ;
  Serial.print(", ") ; 
  Serial.print(xNoisyNow) ; 
  Serial.print(", ") ; 
  Serial.print(x) ; 
  Serial.print(", ") ; 
  Serial.print(derivNoisy) ;
  Serial.print(", ") ; 
  Serial.print(derivBase) ; 
  Serial.print (", ") ; 
  Serial.print(deltaX) ;
  Serial.print(", ") ; 
  Serial.print(dt) ;  
  Serial.println() ; 
  
  delay(6) ; 

  
}
 

