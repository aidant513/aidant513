// This blank Starter has all of the basics covered so you can focus on your code
#include "globals.h" 
#include <Adafruit_BMP280.h>


Adafruit_BMP280 bmp; 

  void setup() {
  // put your setup code here, to run once:
  bmp.begin(0x76) ;

   /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */



  //double Patm = 100 ;

    Serial.begin(115200);
  while(!Serial && millis() < 10000);
  pinMode(2,OUTPUT);          // set pin 2 high for the reference resistor
  digitalWrite(2,HIGH);
  analogReadResolution(16);   // use as high a resolution as is supported

  

}

//get initial pressure reading
double Patm() {
  double sum = 0 ;
  for (int i=0; i<100; i++)  sum += bmp.readPressure() ;
  return sum/100 ;  
}

void loop() {
  // put your main code here, to run repeatedly:

//print output headers
 Serial.print("Time_[s]") ;
 Serial.print(", ") ;
 Serial.print("Light_[%]") ; 
 Serial.print(", ") ;
 Serial.print("Thermistor_T_[C]") ; 
 Serial.print(", ") ;
 Serial.print ("BMP280_T_[C]"); 
 Serial.print(", ") ;
  Serial.println ("delta_P_[Pa]");



  // uno.run();  // monitors your code for how fast it goes through loops
  // Update the global variables for the time in this loop
 timeLast = timeNow;      // the last time we went through the loop, microseconds
 timeNow = micros();      // the time we started this loop, microseconds
  dt = timeNow - timeLast; // the time difference since last loop, microseconds
    double tN= timeNow/1000000 ;
    double z = 1.0 ;
    double w = min (1.0, tN/z) ; 
  
 
  Serial.print (timeNow/1000000) ;
  Serial.print(", ") ;

//print light percentage
  float lightPercent = getLightPercent () ; 
  static double lightPercentSmooth = 0.0 ;
  lightPercentSmooth = lightPercent *w + lightPercentSmooth * (1-w) ;
  Serial.print(lightPercentSmooth, 1) ; 
  Serial.print(", ") ;

//print averaged and smoothed thermistor temp reading
  float temp = getAvgThermT() ;
  static double tempSmooth = 0.0 ;
  tempSmooth = temp *w + tempSmooth*(1-w) ;
  Serial.print (tempSmooth, 1) ;
  Serial.print(", ") ;

//print smoothed presure reading
  float bmpPressure = bmp.readPressure() ;
  static double bmpPressureSmooth = 0.0 ;
  bmpPressureSmooth = bmpPressure * w + bmpPressureSmooth*(1-w) ;
  Serial.print (bmpPressureSmooth, 1) ; 
  Serial.print(", ") ;

//print smoothed bmp temp reading
  float bmpTemp = bmp.readTemperature() ; 
  static double bmpTempSmooth = 0.0 ;
  bmpTempSmooth = bmpTemp * w + bmpTempSmooth * (1-w) ;
  Serial.print (bmpTempSmooth, 1) ;
  Serial.print(", ") ;

  float deltaP = ( bmpPressure - Patm() ) ; //find change in pressure
  Serial.println(deltaP) ;  

  


  

  


  // put your main code here, to run repeatedly:



  

  // Leave the rest of this code in place, but comment out when you don't need it
//  Serial.printf("Average dt = %8.1f us, this loop %8.1f us, maximum %8.1f\n", 
//                  uno.dtAvg(), uno.dt(), uno.dtMax());
 //delay(1000);  // delay only to slow things down so you can see

}