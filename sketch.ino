#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// =====================================================
// ESP32-S3 DUAL JOYSTICK + POTENTIOMETER + LCD
// =====================================================

// ---------------- JOYSTICK 1 ----------------
#define JOY1_X   1
#define JOY1_Y   2
#define JOY1_SW  3

// ---------------- JOYSTICK 2 ----------------
#define JOY2_X   4
#define JOY2_Y   5
#define JOY2_SW  6

// ---------------- POTENTIOMETER ----------------
#define POT_PIN  7

// ---------------- I2C LCD ----------------
#define LCD_SDA  8
#define LCD_SCL  9

// Common I2C address: 0x27
// Some LCD modules use 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // Joystick push buttons
  pinMode(JOY1_SW, INPUT_PULLUP);
  pinMode(JOY2_SW, INPUT_PULLUP);

  // 12-bit ADC
  analogReadResolution(12);

  // Start I2C
  Wire.begin(LCD_SDA, LCD_SCL);

  // Start LCD
  lcd.init();
  lcd.backlight();

  // Startup screen
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("JOYSTICK SYSTEM");

  lcd.setCursor(0, 1);
  lcd.print("ESP32-S3 READY");

  delay(2000);

  lcd.clear();

  Serial.println("======================================");
  Serial.println(" ESP32-S3 JOYSTICK CONTROL SYSTEM");
  Serial.println("======================================");
}


// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // ---------------- READ JOYSTICK 1 ----------------

  int joy1X = analogRead(JOY1_X);
  int joy1Y = analogRead(JOY1_Y);
  bool joy1Pressed = (digitalRead(JOY1_SW) == LOW);


  // ---------------- READ JOYSTICK 2 ----------------

  int joy2X = analogRead(JOY2_X);
  int joy2Y = analogRead(JOY2_Y);
  bool joy2Pressed = (digitalRead(JOY2_SW) == LOW);


  // ---------------- READ POTENTIOMETER ----------------

  int potValue = analogRead(POT_PIN);

  float potVoltage = (potValue / 4095.0) * 3.3;

  int potPercent = map(potValue, 0, 4095, 0, 100);


  // ===================================================
  // SERIAL MONITOR
  // ===================================================

  Serial.println("--------------------------------------");

  Serial.print("JOY1  X: ");
  Serial.print(joy1X);

  Serial.print("  Y: ");
  Serial.print(joy1Y);

  Serial.print("  SW: ");
  Serial.println(joy1Pressed ? "PRESSED" : "RELEASED");


  Serial.print("JOY2  X: ");
  Serial.print(joy2X);

  Serial.print("  Y: ");
  Serial.print(joy2Y);

  Serial.print("  SW: ");
  Serial.println(joy2Pressed ? "PRESSED" : "RELEASED");


  Serial.print("POT   ADC: ");
  Serial.print(potValue);

  Serial.print("  Voltage: ");
  Serial.print(potVoltage, 2);

  Serial.print(" V  ");

  Serial.print("Level: ");
  Serial.print(potPercent);

  Serial.println("%");


  // ===================================================
  // LCD DISPLAY
  // ===================================================

  // Screen 1: Joystick 1
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("J1 X:");
  lcd.print(joy1X);

  lcd.setCursor(9, 0);
  lcd.print("Y:");
  lcd.print(joy1Y);

  lcd.setCursor(0, 1);
  lcd.print("SW:");
  lcd.print(joy1Pressed ? "PRESS" : "OPEN ");

  lcd.setCursor(10, 1);
  lcd.print("J2");

  delay(1000);


  // Screen 2: Joystick 2
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("J2 X:");
  lcd.print(joy2X);

  lcd.setCursor(9, 0);
  lcd.print("Y:");
  lcd.print(joy2Y);

  lcd.setCursor(0, 1);
  lcd.print("SW:");
  lcd.print(joy2Pressed ? "PRESS" : "OPEN ");

  delay(1000);


  // Screen 3: Potentiometer
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("POT:");

  lcd.print(potPercent);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("V:");
  lcd.print(potVoltage, 2);
  lcd.print("V");

  delay(1000);
}