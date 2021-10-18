
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLSKr-1bNr" 
#define BLYNK_DEVICE_NAME "Car Parking"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

#define APP_DEBUG

#define USE_NODE_MCU_BOARD 

#include "BlynkEdgent.h"
// install required lib
#include<Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//initalize the pins
LiquidCrystal_I2C lcd(0x27,16,2);

#define ir_entry D2
#define ir_exit D3

#define slot1_ir D6
#define slot2_ir D7
#define slot3_ir D8

#define servo1 D4
#define servo2 D5

Servo myservo1;
Servo myservo2; 

void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();

  Wire.begin(D1,D0);
  lcd.init();
  lcd.backlight();
  
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Smart ");
  lcd.setCursor(1,1);
  lcd.print("Car Parking");
  delay(2000);

  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Slot1:");
  lcd.setCursor(9,0);
  lcd.print("Slot2:");
  lcd.setCursor(1,1);
  lcd.print("Slot3:");

  pinMode(ir_entry,INPUT);
  pinMode(ir_exit,INPUT);

  pinMode(slot1_ir,INPUT);
  pinMode(slot2_ir,INPUT);
  pinMode(slot3_ir,INPUT);

  myservo1.attach(servo1);
  myservo1.write(0);
  myservo2.attach(servo2);
  myservo2.write(0);
  
}

void loop() {
  BlynkEdgent.run();

  int ir_entry_val = digitalRead(ir_entry);
  int ir_exit_val = digitalRead(ir_exit);

  if(ir_entry_val==0){
    myservo1.write(90);
    delay(3000);
  }
  else(ir_entry_val==1);{
    myservo1.write(0);
  }

  if(ir_exit_val==0){
    myservo2.write(90);
    delay(3000);
  }
  else(ir_exit_val==1);{
    myservo2.write(0);
  }
  int val_slot1_ir=digitalRead(slot1_ir);
  int val_slot2_ir=digitalRead(slot2_ir);
  int val_slot3_ir=digitalRead(slot3_ir);

  if(val_slot1_ir==0){
    lcd.setCursor(7,0);
    lcd.print("O");
  }
  else(val_slot1_ir==1);{
    lcd.setCursor(7,0);
    lcd.print("V");
  }
  if(val_slot2_ir==0){
    lcd.setCursor(15,0);
    lcd.print("O");
  }
  else(val_slot2_ir==1);{
    lcd.setCursor(15,0);
    lcd.print("V");
  }
  if(val_slot3_ir==0){
    lcd.setCursor(7,1);
    lcd.print("O");
  }
  else(val_slot3_ir==1);{
    lcd.setCursor(7,1);
    lcd.print("V");
  }
  // to upload data to blynk server
  Blynk.virtualWrite(V0,val_slot1_ir);
  Blynk.virtualWrite(V1,val_slot2_ir);
  Blynk.virtualWrite(V2,val_slot3_ir);
 
}
