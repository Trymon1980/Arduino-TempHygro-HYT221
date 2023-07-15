# Arduino-TempHygro-HYT221

## Used Libraries:
```
Wire.h, included with Arduino IDE
DHT.h; DHT sensor library by Adafruit; https://www.arduinolibraries.info/libraries/dht-sensor-library
LiquidCrystal_I2C.h; LiquidCrystal I2C by Marco Schwartz; https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
```

## Used Hardware:
```
Arduino nano: https://docs.arduino.cc/hardware/nano
LCD Display 16 x 2 with I2C module: https://wiki-content.arduino.cc/documents/datasheets/LCDscreen.PDF
I2C module: http://www.handsontec.com/dataspecs/module/I2C_1602_LCD.pdf
IST HYT 221: https://www.ist-ag.com/sites/default/files/downloads/HYT221.pdf
```

# PIN connections:
## Arduino:
```
  In development phase powered by USB
  5V:  5V Power supply for LCD and Sensor
  GND: Ground for LCD and Sensor
  A4:  SDA
  A5:  SCL
```
## LCD I2C module:
```
  Usual default for address 0x27. Can be changed by soldering jumpers
  GND:  To Arduino
  5V:   To Arduino
  SDA:  To A4
  SCL:  To A5
```
## IST HYT 221:
```
  Usual default fo raddress 0x28. Can be changed by sending commands to device, described in documentation.
  1:    SDA
  2:    GND
  3:    VCC 2.7V - 5.5V
  4:    SCL
```

This project is to utilize an Arduino nano with the IST HYT 221 high precission temperature and humidity 
sensor for very precise readings. Display out via 16x2 LCD.
In the current state DH11 is used instead of HYT221 to start the Project.
As soon HYT221 is delivered the code will be rewritten to utilize the correct sensor.
README won't cover details of DH11 and this will be removed as soon the chosen sensor could be used. 
