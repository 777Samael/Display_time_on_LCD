// Arduino Nano Real Time Clock DS3231 with I2C LCD Display

#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set lcd address to 0x27

void setup() {
  
  Wire.begin();       // Start the I2C interface
  Serial.begin(9600); // Start the serial interface

  lcd.begin(16,2);    // Init the LCD 2x16
  lcd.backlight();    // turn of backlight
  
}

void loop() {

  // Print to the serial monitor.
  // YEAR
  Serial.print("Year ");
  Serial.print("20");
  Serial.print(Clock.getYear(), DEC);
  Serial.print(' ');
  
  // MONTH
  Serial.print("Month: ");
  Serial.print(Clock.getMonth(Century), DEC);
  Serial.print(' ');
  
  // DAY
  Serial.print("Day: ");
  Serial.print(Clock.getDate(), DEC);
  Serial.print(' ');
  
  // DAY OF THE WEEK
  Serial.print("DayOfWeek: ");
  Serial.print(Clock.getDoW(), DEC);
  Serial.print(' ');
  Serial.print('\n');
  
  // HOUR, MINUTE, SECOND
 Serial.print("HMS: ");
  Serial.print(Clock.getHour(h12, PM), DEC);
  Serial.print(' ');
  Serial.print(Clock.getMinute(), DEC);
  Serial.print(' ');
  if (Clock.getSecond() < 10) {
    Serial.print("0");
    Serial.print(Clock.getSecond(), DEC);
  } else {
    Serial.print(Clock.getSecond(), DEC);
  }
  // Add AM/PM indicator
  if (h12) {
    if (PM) {
      Serial.print(" PM ");
    } else {
      Serial.print(" AM ");
    }
  } else {
    Serial.print(" 24h ");
  }
  
  // TEMP -  Display the temperature
  Serial.print("Temp = ");
  Serial.print(Clock.getTemperature(), 2);
  
  // Tell whether the time is (likely to be) valid
  if (Clock.oscillatorCheck()) {
    Serial.print(" O+");
  } else {
    Serial.print(" O-");
  }
  
  // ALARM - Indicate whether an alarm went off
  if (Clock.checkIfAlarm(1)) {
    Serial.print(" A1!");
  }
  if (Clock.checkIfAlarm(2)) {
    Serial.print(" A2!");
  }
  // New line on display
  Serial.print('\n');
  
    // ALARM 1 - Display Alarm 1 information
    Serial.print("Alarm 1: ");
    Clock.getA1Time(ADay, AHour, AMinute, ASecond, ABits, ADy, A12h, Apm);
    Serial.print(ADay, DEC);
    if (ADy) {
      Serial.print(" DoW");
    } else {
      Serial.print(" Date");
    }
    Serial.print(' ');
    Serial.print(AHour, DEC);
    Serial.print(' ');
    Serial.print(AMinute, DEC);
    Serial.print(' ');
    Serial.print(ASecond, DEC);
    Serial.print(' ');
    if (A12h) {
      if (Apm) {
        Serial.print('pm ');
      } else {
        Serial.print('am ');
      }
    }
    if (Clock.checkAlarmEnabled(1)) {
      Serial.print("enabled");
    } else {
      Serial.print("disabled");
    }
    Serial.print('\n');
    
    // ALARM 2 - Display Alarm 2 information
    Serial.print("Alarm 2: ");
    Clock.getA2Time(ADay, AHour, AMinute, ABits, ADy, A12h, Apm);
    Serial.print(ADay, DEC);
    if (ADy) {
      Serial.print(" DoW");
    } else {
      Serial.print(" Date");
    }
    Serial.print(' ');
    Serial.print(AHour, DEC);
    Serial.print(' ');
    Serial.print(AMinute, DEC);
    Serial.print(' ');
    if (A12h) {
      if (Apm) {
        Serial.print('pm');
      } else {
        Serial.print('am');
      }
    }
    if (Clock.checkAlarmEnabled(2)) {
      Serial.print("enabled");
    } else {
      Serial.print("disabled");
    }
    
    // display alarm bits
    Serial.print('\nAlarm bits: ');
    Serial.print(ABits, BIN);
  
    Serial.print('\n');
    Serial.print('\n');

  //Print to LCD
  lcd.setCursor(0,0); // Set the cursor in position 0,0 (first column, first row)
  
  lcd.print("Date: 20");
  lcd.print(Clock.getYear(), DEC);
  lcd.print("-");
  if (Clock.getMonth(Century) < 10) {
    lcd.print("0");
    lcd.print(Clock.getMonth(Century), DEC);
  } else {
    lcd.print(Clock.getMonth(Century), DEC);
  }
  lcd.print("-");
  lcd.print(Clock.getDate(), DEC);

  lcd.setCursor(0,1); // Set the cursor in position 0,1 (first column, second row)

  lcd.print("Time: ");
  lcd.print(Clock.getHour(h12, PM), DEC);
  lcd.print(":");
  lcd.print(Clock.getMinute(), DEC);
  lcd.print(":");
  if (Clock.getSecond() < 10) {
    lcd.print(0, DEC);
    lcd.print(Clock.getSecond(), DEC);
  } else {
    lcd.print(Clock.getSecond(), DEC);
  }
  
  delay(1000);
}
