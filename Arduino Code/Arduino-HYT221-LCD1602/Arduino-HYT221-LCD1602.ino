//Include libraries.
#include <Wire.h>                                           //Already installed with Arduino IDE
#include <LiquidCrystal_I2C.h>                              //LiquidCrystal I2C by Marco Schwartz

//For ease of use some definitions
#define HYTADDR 0x28                                        //Address for HYT 221 communication
#define LCDI2CADDRESS 0x27                                  //Address for I2C communication                   
#define LCDCOLUMS 16                                        //Number of LCD Display colums
#define LCDLINES 2                                          //Number of LCD Display lines

LiquidCrystal_I2C lcd(LCDI2CADDRESS, LCDCOLUMS, LCDLINES);  //Create lcd object with defined parameters

void setup()
{
  lcd.init();                                               //Initialize lcd
  lcd.backlight();                                          //Turn on backlight of LCD
}

void loop()
{
  double humidity;                                          //Variable for huiḿidity
  double temperature;                                       //Variable for temperature
  char buffer1[6];                                          //buffer for dtostrf
  char buffer2[6];                                          //buffer for sprintf

  Wire.beginTransmission(HYTADDR);                          // Begin transmission with given device on I2C bus
  Wire.requestFrom(HYTADDR, 4);                             // Request 4 bytes

  // Read the bytes if they are available
  // The first two bytes are humidity the last two are temperature
  if(Wire.available() == 4) 
  {                   
    int b1 = Wire.read();
    int b2 = Wire.read();
    int b3 = Wire.read();
    int b4 = Wire.read();
    
    Wire.endTransmission();                                 //End transmission and release I2C bus

    int rawHumidity = b1 << 8 | b2;                         //combine humidity bytes 
    rawHumidity =  (rawHumidity &= 0x3FFF);                 //compound bitwise to get 14 bit measurement first two bits are status/stall bit
    humidity = 100.0 / pow(2,14) * rawHumidity;             //calculate humidity. Calculation provided in HYT221 documentation
    
    // combine temperature bytes and calculate temperature
    b4 = (b4 >> 2);                                         // Mask away 2 least significant bits see /Datasheets/HYT_Documentation.pdf
    int rawTemperature = b3 << 6 | b4;
    temperature = 165.0 / pow(2,14) * rawTemperature - 40;  //calculate temperature. Calculation provided in HYT221 documentation
  
    lcd.clear();                                            //Clear screen of LCD
    lcd.setCursor(0,0);                                     //set cursor in colum 0, line 0
    dtostrf(temperature,6,3,buffer1);                       //Convert double temperature to String with 6 digits, 3 decimal and store in buffer 1
    sprintf(buffer2,"T:  %s C",buffer1);                    //Create a formated string for temperature, based on buffer1, and store in buffer 2
    lcd.print(buffer2);                                     //print buffer2 to LCD
    lcd.setCursor(0,1);                                    //set cursor in colum 0, line 1
    dtostrf(humidity,5,2,buffer1);                          //Convert double humidity to String with 5 digits, 3 decimal and store in buffer 1
    sprintf(buffer2,"rF: %s  %%",buffer1);                  //Create a formated string for humidity, based on buffer1, and store in buffer 2
    lcd.print(buffer2);                                     //print buffer2 to LCD
    delay(2000);                                            //Delay loop for 2000ms (2 seconds)
  }
  else
  {
    lcd.clear();                                            //Clear screen of LCD
    lcd.print("Not enough bytes available on wire.");       //Print given String to LCD
    delay(2000);                                            //Delay loop for 2000ms (2 seconds)
  }
}
