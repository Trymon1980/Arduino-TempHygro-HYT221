#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE, 6);

void setup()
{
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop()
{
  lcd.clear();
  lcd.print("T:  ");
  lcd.print(String(dht.readTemperature(), 2));
  lcd.print(" C");
  lcd.setCursor (0,1);
  lcd.print("rF: ");
  lcd.print(String(dht.readHumidity(), 2));
  lcd.print(" %");
  delay(2000);
}
