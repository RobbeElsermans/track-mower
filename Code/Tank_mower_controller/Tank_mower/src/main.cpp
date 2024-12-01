#include <Arduino.h>
#include "main.h"
// #include <Adafruit_BMP280.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "PCF8574.h"
#include "ESP32MotorControl.h" 	// https://github.com/JoaoLopesF/ESP32MotorControl

#define DEBUG

#include <BluetoothSerial.h>

//Battery voltage
float voltage_battery = 0.0; // In V
const float delta_v = 0.000805664;
const double scaler_battery_voltage = 12; //6.5

//Currents
float current_mower = 0.0;    // In mA
float current_track_1 = 0.0;  // In mA
float current_track_2 = 0.0;  // In mA
const float delta_i = 0.0021416; //delta_v/i_res
const float mid_current = 4096/2.0 * delta_i;

//State variable
float round_trip_time;

//Bluetooth commands and placeholders
BluetoothSerial SerialBT;
uint8_t read_char[8];
uint8_t command_index_end = 0;
const uint8_t FORWARD_COMMAND = 'F';
const uint8_t REVERSE_COMMAND = 'B';
const uint8_t RIGHT_COMMAND = 'R';
const uint8_t LEFT_COMMAND = 'L';
const uint8_t MOWER_COMMAND = 'M';

//Boolean locations
#define BOOL_FORWARD 0
#define BOOL_REVERSE 1
#define BOOL_LEFT 2
#define BOOL_RIGHT 3

//Boolean locations
#define BOOL_FORWARD_ACTIVE 4
#define BOOL_REVERSE_ACTIVE 5
#define BOOL_LEFT_ACTIVE 6
#define BOOL_RIGHT_ACTIVE 7

//Boolean locations
#define BOOL_MOWER 0
#define BOOL_MOWER_RAMP_DONE 1
#define BOOL_MOWER_ACTIVE 4

////Boolean containers
uint8_t bool_holder_1 = 0b00000000;
uint8_t bool_holder_2 = 0b00000000;

//Time of command execution
#define FORWARD_TIME 1000
#define REVERSE_TIME 1000
#define LEFT_TIME 500
#define RIGHT_TIME 500
#define MOWER_RAMP_TIME 10
#define MOWER_FALL_TIME 1

long forward_timer;
long left_timer;
long right_timer;
long reverse_timer;
long ramp_timer;

#define MOWER_MAX_VALUE 255
uint8_t mower_value;


//Library Motor control
ESP32MotorControl MotorControl = ESP32MotorControl();

//Library IO expansion Module
TwoWire I2Ctwo = TwoWire(1); //Default on 21 and 22
PCF8574 pcf8574(&I2Ctwo, 0x20); 

//OLED display
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);
#define SCREEN_UPDATE_TIME 100
long screen_update_timer;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // make sure your Serial Monitor is also set at this baud rate.
  SerialBT.begin("tankBot");

  //attach the motors
  MotorControl.attachMotors(MOTOR_TRACK_1_1, MOTOR_TRACK_1_2, MOTOR_TRACK_2_2, MOTOR_TRACK_2_1); //1.1 1.2 2.2 2.1

  // pinMode(MOTOR_TRACK_1_1, OUTPUT);
  // pinMode(MOTOR_TRACK_1_2, OUTPUT);
  // pinMode(MOTOR_TRACK_2_1, OUTPUT);
  // pinMode(MOTOR_TRACK_2_2, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.setRotation(2); //Rotate 180°

  //Add and enable VCC of motors
  // pinMode(VCC_MOTOR_MOWER_EN, OUTPUT);
  pinMode(VCC_MOTOR_TRACK_EN, OUTPUT);
  // digitalWrite(VCC_MOTOR_MOWER_EN, HIGH);
  digitalWrite(VCC_MOTOR_TRACK_EN, HIGH);

  //Add current pins
  pinMode(MOTOR_CURRENT_MOWER, INPUT);
  pinMode(MOTOR_TRACK_1_CURRENT, INPUT);
  pinMode(MOTOR_TRACK_2_CURRENT, INPUT);

  //Add mower motor
  pinMode(MOTOR_MOWER_EN, OUTPUT);  

  pcf8574.begin();
  delay(100);

  pcf8574.pinMode(LED_1, OUTPUT);
  pcf8574.pinMode(LED_2, OUTPUT);
  pcf8574.pinMode(LED_3, OUTPUT);
  pcf8574.pinMode(LED_4, OUTPUT);
  pcf8574.pinMode(MOTOR_TRACK_1_EN, OUTPUT);
  pcf8574.pinMode(MOTOR_TRACK_2_EN, OUTPUT);
  pcf8574.pinMode(MOTOR_TRACK_1_FAULT, INPUT);
  pcf8574.pinMode(MOTOR_TRACK_2_FAULT, INPUT);
  
  delay(1000);
  
  pcf8574.digitalWrite(MOTOR_TRACK_2_EN, HIGH);
  pcf8574.digitalWrite(MOTOR_TRACK_1_EN, HIGH);

  // LED fancy thing
  pcf8574.digitalWrite(LED_1, HIGH);
  delay(500);
  pcf8574.digitalWrite(LED_1, LOW);
  pcf8574.digitalWrite(LED_2, HIGH);
  delay(500);
  pcf8574.digitalWrite(LED_2, LOW);
  pcf8574.digitalWrite(LED_3, HIGH);
  delay(500);
  pcf8574.digitalWrite(LED_3, LOW);
  pcf8574.digitalWrite(LED_4, HIGH);
  delay(500);
  pcf8574.digitalWrite(LED_4, LOW);
}

void loop()
{
  float time = millis();
  readCommand();
  // Process the command
  handleCommand();
  //run command  
  executeCommand();

  //Read current
  calculateCurrent(MOTOR_CURRENT_MOWER, &current_mower);
  calculateCurrent(MOTOR_TRACK_1_CURRENT, &current_track_1);
  calculateCurrent(MOTOR_TRACK_2_CURRENT, &current_track_2);

  calculateVoltage(BATTERY_VOLTAGE_SCALED, &voltage_battery);
  // Display the used command on the OLED
  displayData();

  round_trip_time = (millis() - time);
}

void displayData()
{
  if ((millis() - screen_update_timer) > SCREEN_UPDATE_TIME){
    display.clearDisplay();
    display.setTextSize(1,1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,1);
    display.println("Hello Tank Mower");
    // display.println("Welcome!");
    display.print("trip time:");
    display.print(round_trip_time);
    display.println("ms");
    display.print("Command ");
    display.println(bool_holder_1, BIN);
    
    display.print("MI: ");
    display.print(current_mower);
    display.print(" mA, ");

    display.print("T1I: ");
    display.print(current_track_1);
    display.print(" mA, ");

    display.print("T2I: ");
    display.print(current_track_2);
    display.print(" mA, ");

    display.print("Vcc: ");
    display.print(voltage_battery);
    display.print(" V, ");
    
    display.setCursor(0,0);
    display.display();
    screen_update_timer = millis();
  }
}

void calculateVoltage(uint8_t pin, float* voltage)
{
  int analog_value = analogRead(pin);
  *voltage = analog_value*delta_v*scaler_battery_voltage;
  Serial.printf("raw:%d, cal: %f \r\n", analog_value, *voltage);
}

void calculateCurrent(uint8_t pin, float* current)
{
  int analog_current = 0;
  int cycles = 50;

  for(uint8_t i = 0; i < cycles; i++)
  {
    analog_current += analogRead(pin);
  }

  analog_current /= cycles;

  *current = (float)(analog_current*delta_i)-mid_current;
  if (*current < 0){
    *current = 0;
  }
  *current *= 1000; //Set to mA.
}

void readCommand()
{
  while (SerialBT.available())
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      read_char[i] = SerialBT.read();
      if (read_char[i] == (uint8_t)13)
      {
        // A new command has entered the building!
        command_index_end = i - 1;
      }
    }
  }

  // Run the bot if a command has been received.

  // Forward is executed 1 second
  if (read_char[command_index_end] == FORWARD_COMMAND)
  {
    setBool(&bool_holder_1, (uint8_t)BOOL_FORWARD);
  }

  // Reverse is executed 1 second

  if (read_char[command_index_end] == REVERSE_COMMAND)
  {
    setBool(&bool_holder_1, (uint8_t)BOOL_REVERSE);
  }

  // Left is executed 0.2 second

  if (read_char[command_index_end] == LEFT_COMMAND)
  {
    setBool(&bool_holder_1, (uint8_t)BOOL_LEFT);
  }
  // Right is executed 0.2 second

  if (read_char[command_index_end] == RIGHT_COMMAND)
  {
    setBool(&bool_holder_1, (uint8_t)BOOL_RIGHT);
  }

  if (read_char[command_index_end] == MOWER_COMMAND)
  {
    setBool(&bool_holder_2, (uint8_t)BOOL_MOWER);
  }

  read_char[command_index_end] = 0;
}

void handleCommand()
{
  // Check if forward is activated
  if (checkBool(&bool_holder_1, BOOL_FORWARD))
  {
    // deactivate
    clearBool(&bool_holder_1, (uint8_t)BOOL_FORWARD);
    setBool(&bool_holder_1, (uint8_t)BOOL_FORWARD_ACTIVE);
    // run for X amount of seconds

  //Serial.println("Forward activated!");

    forward_timer = millis(); // Set timer to deactivate
  }

  // Run timer to deactivate
  if (((millis() - forward_timer) >= (long)FORWARD_TIME) && checkBool(&bool_holder_1, BOOL_FORWARD_ACTIVE))
  {
  //Serial.println("Forward deactivated!");
    clearBool(&bool_holder_1, BOOL_FORWARD_ACTIVE);
  }

  if (checkBool(&bool_holder_1, BOOL_REVERSE))
  {
    // deactivate
    clearBool(&bool_holder_1, (uint8_t)BOOL_REVERSE);
    setBool(&bool_holder_1, (uint8_t)BOOL_REVERSE_ACTIVE);
    // run for X amount of seconds

  //Serial.println("Reverse activated!");
    reverse_timer = millis(); // Set timer to deactivate
  }

  // Run timer to deactivate
  if (((millis() - reverse_timer) >= (long)REVERSE_TIME) && checkBool(&bool_holder_1, BOOL_REVERSE_ACTIVE))
  {
  //Serial.println("Reverse deactivated!");
    clearBool(&bool_holder_1, BOOL_REVERSE_ACTIVE);
  }

  if (checkBool(&bool_holder_1, BOOL_LEFT))
  {
    // deactivate
    clearBool(&bool_holder_1, (uint8_t)BOOL_LEFT);
    setBool(&bool_holder_1, (uint8_t)BOOL_LEFT_ACTIVE);
    // run for X amount of seconds
  //Serial.println("Left activated!");
    left_timer = millis(); // Set timer to deactivate
  }

  // Run timer to deactivate
  if (((millis() - left_timer) >= (long)LEFT_TIME) && checkBool(&bool_holder_1, (uint8_t)BOOL_LEFT_ACTIVE))
  {
  //Serial.println("Left deactivated!");
    clearBool(&bool_holder_1, BOOL_LEFT_ACTIVE);
  }

  if (checkBool(&bool_holder_1, (uint8_t)BOOL_RIGHT))
  {
    // deactivate
    clearBool(&bool_holder_1, (uint8_t)BOOL_RIGHT);
    setBool(&bool_holder_1, (uint8_t)BOOL_RIGHT_ACTIVE);
    // run for X amount of seconds

  //Serial.println("Right activated!");
    right_timer = millis(); // Set timer to deactivate
  }

  // Run timer to deactivate
  if (((millis() - right_timer) >= (long)RIGHT_TIME) && checkBool(&bool_holder_1, (uint8_t)BOOL_RIGHT_ACTIVE))
  {
  //Serial.println("Right deactivated!");
    clearBool(&bool_holder_1, BOOL_RIGHT_ACTIVE);
  }

  if( checkBool(&bool_holder_2, (uint8_t)BOOL_MOWER))
  {
    if(checkBool(&bool_holder_2, (uint8_t)BOOL_MOWER_ACTIVE))
    {
      clearBool(&bool_holder_2, (uint8_t) BOOL_MOWER_ACTIVE);
    //Serial.println("Mower de-activated!");
    }
    else
    {
    //Serial.println("Mower activated!");
      setBool(&bool_holder_2, (uint8_t) BOOL_MOWER_ACTIVE);
    }

    clearBool(&bool_holder_2, (uint8_t) BOOL_MOWER);
  }
}

//bool toggle = false;
void executeCommand()
{
  // if(toggle){
  // // MotorControl.motorForward(0, 255);
  // // MotorControl.motorForward(1, 255);
  // digitalWrite(MOTOR_TRACK_1_1, HIGH);
  // digitalWrite(MOTOR_TRACK_1_2, LOW);
  // toggle = false;
  // delay(1000);
  // }
  // else{
  //   // MotorControl.motorReverse(0, 255);
  //   // MotorControl.motorReverse(1, 255);

  // digitalWrite(MOTOR_TRACK_1_2, HIGH);
  // digitalWrite(MOTOR_TRACK_1_1, LOW);
  // toggle= true;
  //   delay(1000);
  // }
  // Serial.println(toggle);

  if (checkBool(&bool_holder_1, BOOL_FORWARD_ACTIVE)){
    MotorControl.motorForward(0, 255);
    MotorControl.motorForward(1, 255);
  }

  if (checkBool(&bool_holder_1, BOOL_REVERSE_ACTIVE)){
    MotorControl.motorReverse(0, 255);
    MotorControl.motorReverse(1, 255);
  }

  if (checkBool(&bool_holder_1, BOOL_LEFT_ACTIVE)){
    MotorControl.motorForward(0, 255);
    MotorControl.motorReverse(1, 255);
  }

  if (checkBool(&bool_holder_1, BOOL_RIGHT_ACTIVE)){
    MotorControl.motorReverse(0, 255);
    MotorControl.motorForward(1, 255);
  }

  if (
    checkBool(&bool_holder_1, BOOL_FORWARD_ACTIVE) == 0 && 
    checkBool(&bool_holder_1, BOOL_REVERSE_ACTIVE) == 0 && 
    checkBool(&bool_holder_1, BOOL_LEFT_ACTIVE)  == 0 && 
    checkBool(&bool_holder_1, BOOL_RIGHT_ACTIVE) == 0 )
    {
      MotorControl.motorsStop();
    }

  if (checkBool(&bool_holder_2, BOOL_MOWER_ACTIVE))
  {
    if((millis()-ramp_timer) > MOWER_RAMP_TIME && (!checkBool(&bool_holder_2, BOOL_MOWER_RAMP_DONE) || (mower_value != 0)))
    {
      ramp_timer = millis();     

      if(mower_value == MOWER_MAX_VALUE)
      {
        setBool(&bool_holder_2, BOOL_MOWER_RAMP_DONE);
      }
      else
      {
        mower_value++;
      }
      analogWrite(MOTOR_MOWER_EN, mower_value);
      
    }

    // analogWrite(MOTOR_MOWER_EN, MOWER_MAX_VALUE);
  }
  else
  {
    if((millis()-ramp_timer) > MOWER_FALL_TIME && (checkBool(&bool_holder_2, BOOL_MOWER_RAMP_DONE) || (mower_value != MOWER_MAX_VALUE) ))
    {
      ramp_timer = millis();     

      if(mower_value == 0)
      {
        clearBool(&bool_holder_2, BOOL_MOWER_RAMP_DONE);
      }
      else
      {
        mower_value--;
      }
      analogWrite(MOTOR_MOWER_EN, mower_value);
      
    }

    // analogWrite(MOTOR_MOWER_EN, 0);
  }
}

void setBool(uint8_t *bool_carrier, uint8_t bool_place)
{
  *bool_carrier |= 0b1 << bool_place;
}

void clearBool(uint8_t *bool_carrier, uint8_t bool_place)
{
  *bool_carrier &= ~(0b1 << bool_place);
}

uint8_t checkBool(uint8_t *bool_carrier, uint8_t bool_place)
{
  return *bool_carrier & (0b1 << bool_place);
}