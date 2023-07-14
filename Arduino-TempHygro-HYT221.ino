//Include libraries.
#include <Wire.h>                                           //Already installed with Arduino IDE
#include <DHT.h>                                            //DHT sensor library by Adafruit
#include <LiquidCrystal_I2C.h>                              //LiquidCrystal I2C by Marco Schwartz

//For ease of use some definitions
#define DHTPIN 2                                            //Datapin for DHT11 connected to D2
#define DHTTYPE DHT11                                       //Used DHT type
#define LCDI2CADDRESS 0x27                                  //Address for I2C communication                   
#define LCDCOLUMS 16                                        //Number of LCD Display colums
#define LCDLINES 2000                                       //Number of LCD Display lines

LiquidCrystal_I2C lcd(LCDI2CADDRESS, LCDCOLUMS, LCDLINES);  //Create lcd object with defined parameters
DHT dht(DHTPIN, DHTTYPE, 6);                                //Create dht object with defined parameters. Third parameter not used anymore by library. Default of 6 is a good option.

void setup()
{
  lcd.init();                                               //Initialize lcd
  lcd.backlight();                                          //Turn on backlight of LCD
  dht.begin();                                              //Initialize dht
}

void loop()
{
  lcd.clear();                                              //Clear screen of LCD
  lcd.print("T:  ");                                        //Print in first line of LCD the shown string
  lcd.print(String(dht.readTemperature(), 2));              //Print Temperature reading of DHT as String
  lcd.print(" C");                                          //Print C for Celsius at the end
  lcd.setCursor (0,1);                                      //Move cursor to first colum in second line
  lcd.print("rF: ");                                        //Print rF for relative Feuchte (relative Humidity)
  lcd.print(String(dht.readHumidity(), 2));                 //print Humidity reading of DHT as String
  lcd.print(" %");                                          //print % at the end
  delay(2000);                                              //Delay loop for 2000ms (2 seconds)
}
