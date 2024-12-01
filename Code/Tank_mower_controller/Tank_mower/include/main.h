#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdint.h>

//Define pinouts
#define IO_EXTENDER_INTERUPT 17

#define SS 5
#define SCK 18
#define MISO 19
#define MOSI 23

#define VCC_MOTOR_TRACK_EN 13
//#define VCC_MOTOR_MOWER_EN 35  //Not working
// #define VCC_MOTOR_TRACK_EN 33
// #define VCC_MOTOR_MOWER_EN 36

//#define ENCODER_1 33
//#define ENCODER_2 36

#define BATTERY_VOLTAGE_SCALED 35//12
#define MOTOR_CURRENT_MOWER 32
#define MOTOR_TRACK_1_CURRENT 34
#define MOTOR_TRACK_2_CURRENT 39

#define MOTOR_TRACK_1_1 25
#define MOTOR_TRACK_1_2 26

#define MOTOR_TRACK_2_1 27
#define MOTOR_TRACK_2_2 14
#define MOTOR_MOWER_EN 4
#define MOTOR_TRACK_1_FAULT P5
#define MOTOR_TRACK_2_FAULT P4
#define MOTOR_TRACK_1_EN P7
#define MOTOR_TRACK_2_EN P6

#define LED_1 P3
#define LED_2 P2
#define LED_3 P1
#define LED_4 P0

void readCommand();
void calculateCurrent(uint8_t pin, float* current);
void calculateVoltage(uint8_t pin, float* voltage);
void displayData();
void handleCommand();
void executeCommand();
void setBool(uint8_t *bool_carrier, uint8_t bool_place);

void clearBool(uint8_t *bool_carrier, uint8_t bool_place);

uint8_t checkBool(uint8_t *bool_carrier, uint8_t bool_place);

#endif