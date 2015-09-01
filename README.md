# eag
Arduino Neopixel Matrix Electroaudiogram

Requires:
8x8 Neopixel Matrix connected to digital pin 2
Arduino Sound Sensor connected to analog pin 0
optional LED or laser diode connected to digital pin 4

Samples the voltage from the sound sensor 200 times per second and draws a dot in the next column.  The brightness varies by amplitude and the color cycles at varying rates based on amplitude.
