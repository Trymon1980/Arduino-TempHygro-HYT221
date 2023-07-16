# Arduino-TempHygro-HYT221

## Used Libraries:
- Wire.h, included with Arduino IDE
- [LiquidCrystal_I2C.h](https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c)

## Used Hardware:
- [Arduino nano](Datasheets/Arduino_nano_datasheet.pdf)
- [LCD Display 16 x 2 with I2C module](LCDscreen16x2.pdf)
- [I2C module](I2C_1602_LCD.pdf)
- [IST HYT 221 Datasheet](Datasheet_Digital_humidity_sensor_HYT221_.pdf)
- [IST HYT 221 Documentation](HYT_Documentation.pdf)

# PIN connections:
## Arduino:
-  In development phase powered by USB
-  5V:  5V Power supply for LCD and Sensor
-  GND: Ground for LCD and Sensor
-  A4:  SDA
-  A5:  SCL

## LCD I2C module:
   Usual default for address 0x27. Can be changed by soldering jumpers
-  GND:  To Arduino
-  5V:   To Arduino
-  SDA:  To A4
-  SCL:  To A5

## IST HYT 221:
  Usual default fo raddress 0x28. Can be changed by sending commands to device, described in documentation.
- 1:    SDA
- 2:    GND
- 3:    VCC 2.7V - 5.5V
- 4:    SCL

This project is to utilize an Arduino nano with the IST HYT 221 high precission temperature and humidity 
sensor for very precise readings. Display out via 16x2 LCD. 
Arduino code to receive information adapted from https://github.com/stylesuxx/Arduino-HYT-221-I2C/tree/master



