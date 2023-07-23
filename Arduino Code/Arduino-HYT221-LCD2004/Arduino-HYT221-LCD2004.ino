//Include libraries.
#include <Wire.h>                                           //Already installed with Arduino IDE
#include <LiquidCrystal_I2C.h>                              //LiquidCrystal I2C by Marco Schwartz

//For ease of use some definitions
#define HYTADDR 0x28                                        //Address for HYT 221 communication
#define LCDI2CADDRESS 0x27                                  //Address for I2C communication                   
#define LCDCOLUMS 20                                        //Number of LCD Display colums
#define LCDLINES 4                                          //Number of LCD Display lines
#define OFFSET_TEMP -0.031                                  //Offset for HYT221 Temperature reading
#define OFFSET_HUM 3.4                                      //Offset for HYT221 Humidity reading

double mintemp = 150;
double maxtemp = -50;
double minhum = 150;
double maxhum = -50;

LiquidCrystal_I2C lcd(LCDI2CADDRESS, LCDCOLUMS, LCDLINES);  //Create lcd object with defined parameters

void setup()
{
  lcd.init();                                               //Initialize lcd
  lcd.backlight();                                          //Turn on backlight of LCD
  lcd.clear();                                              //Clear screen of LCD
}

void writeLCD(double reading, int i)
{
    char buffer1[6];                                        //buffer for dtostrf
    char buffer2[6];                                        //buffer for sprintf
    lcd.setCursor(0,i);                                     //set cursor in colum 0, line 0
    if (i == 0)
    {
      sprintf(buffer2,"T: %s C",dtostrf(reading,i+4,i+2,buffer1));   //Convert double temperature to String with 6 digits, 3 decimal and store in buffer 1 and create a formated string for temperature, based on buffer1, and store in buffer 2
    }
    else
    {
      sprintf(buffer2,"rF:%s %%",dtostrf(reading,i+4,i+1,buffer1));  //Convert double humidity to String with 5 digits, 2 decimal and store in buffer 1 and create a formated string for humidity, based on buffer1, and store in buffer 2
    }
    lcd.print(buffer2);                                     //print buffer2 to LCD
}

void writeLCDhistory(double mitemp, double matemp, double mihum, double mahum)
{
  char buffer1[6];
  char buffer2[6];
  char buffer3[6];
  lcd.setCursor(0,2);
  sprintf(buffer3,"T: %s C",dtostrf(mitemp,4,1,buffer1));
  lcd.print(buffer3);
  sprintf(buffer3,"/ %s C",dtostrf(matemp,1,1,buffer2));
  lcd.setCursor(10,2);
  lcd.print(buffer3);
  lcd.setCursor(0,3);
  sprintf(buffer3,"rF:%s %%",dtostrf(mihum,4,1,buffer1));
  lcd.print(buffer3);
  lcd.setCursor(10,3);
  sprintf(buffer3,"/ %s %%",dtostrf(mahum,4,1,buffer2));
  lcd.print(buffer3);
}

double readTemperature(int b3, int b4)
{
    // combine temperature bytes and calculate temperature
    b4 = (b4 >> 2);                                         //Mask away 2 least significant bits see /Datasheets/HYT_Documentation.pdf
    int rawTemperature = b3 << 6 | b4;
    return(165.0 / pow(2,14) * rawTemperature - 40 + OFFSET_TEMP);        //calculate temperature. Calculation provided in HYT221 documentation
}

double readHumidity(int b1, int b2)
{
    int rawHumidity = b1 << 8 | b2;                         //combine humidity bytes 
    rawHumidity =  (rawHumidity &= 0x3FFF);                 //compound bitwise to get 14 bit measurement first two bits are status/stall bit
    return(100.0 / pow(2,14) * rawHumidity + OFFSET_HUM);                //calculate humidity. Calculation provided in HYT221 documentation
}

void loop()
{
  Wire.beginTransmission(HYTADDR);                          // Begin transmission with given device on I2C bus
  Wire.requestFrom(HYTADDR, 4);                             // Request 4 bytes
  // Read the bytes if they are available
  // The first two bytes are humidity the last two are temperature
  if(Wire.available() == 4) 
  {                   
    int b1 = Wire.read();                                   //store first byte
    int b2 = Wire.read();                                   //store second byte
    int b3 = Wire.read();                                   //store third byte
    int b4 = Wire.read();                                   //store fourth byte
    Wire.endTransmission();                                 //End transmission and release I2C bus
    lcd.setCursor(0,0);
    writeLCD(readTemperature(b3, b4), 0);                   //Call write to LCD function and call readTemperature function as parameter
    writeLCD(readHumidity(b1, b2), 1);                      //Call write to LCD function and call readHumidity function as parameter
    if (mintemp > readTemperature(b3, b4))
    {
      mintemp = readTemperature(b3, b4);
    }
    if (maxtemp <= readTemperature(b3, b4))
    {
      maxtemp = readTemperature(b3, b4);
    }
    if (minhum > readHumidity(b1, b2))
    {
      minhum = readHumidity(b1, b2);
    }
    if (maxhum <= readHumidity(b1, b2))
    {
      maxhum = readHumidity(b1, b2);
    }

    writeLCDhistory(mintemp, maxtemp, minhum, maxhum);
    
    delay(2000);                                            //Delay loop for 2000ms (2 seconds)
  }
  else
  {
    lcd.clear();                                            //Clear screen of LCD
    lcd.print("Not enough bytes available on wire.");       //Print given String to LCD
    delay(2000);                                            //Delay loop for 2000ms (2 seconds)
  }
}
