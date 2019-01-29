# Display_time_on_LCD

This code is based on default DS3231_test sample code created by Eric Ayars included in DS3231 library.
Modifications made by Przemyslaw Kepka.

The code was tested on:
- copy of Arduino Nano with ATMEL ATMEGA328P-AU microcontroller and CH340G USB converter
- Shield I/O for Arduino NANO 3.0
- DS3231 RTC module
- LCD 1602 HD44780 with IIC/I2C serial interface adapter module

The code includes printing data to serial monitor and to the 2x16 LCD display.

Data printed to serial monitor:
- Year - first 2 digits are hardcoded, but it won't make any difference until 2100;)
- Month
- Day
- Day of week - 1 is Sunday
- Hour - based on clock type it's 12h or 24h
- Minute
- Second
- Temperature of DS3231
- Oscillator check indicator
- Data from both alarms:
    - Day
    - Hour
    - Minute
    - Clock status - enabled/disabled
    - Alarm bits

Data printed to LCD:
- Date in YYYY-MM-DD format with "Date: " prefix
- Time in HH:MM:SS format with "Time: " prefix