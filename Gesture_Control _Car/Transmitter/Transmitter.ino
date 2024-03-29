//       Made by Anneshu Nag      // 
//    C++ Codes on Arduino IDE    //
// Gesture Control with RF-Module //
//       Transmitter Rover        //
#include <Wire.h>
#include <MPU6050.h>
#include <VirtualWire.h>

#define MPU_ADDRESS 0x68
#define TX_PIN 3
#define LED_PIN 13

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  vw_set_tx_pin(TX_PIN);
  vw_setup(2000);  // Bits per sec
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Setup Complete! Ready to roll!");
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);
  Serial.print(ax);
  Serial.print(", ");
  Serial.print(ay);
  Serial.print(" | ");

  char command = 's'; // Default to stop
  // Adjust these thresholds based on your gesture detection
  if (ay > 12000) {
    command = 'f'; // Forward
  } else if (ay < -12000) {
    command = 'g'; // Backward
  } else if (ax > 10000) {
    command = 'r'; // Right
  } else if (ax < -10000) {
    command = 'l'; // Left
  }
  Serial.println(command);
  digitalWrite(LED_PIN, HIGH); // LED on while transmitting
  vw_send((uint8_t *)&command, 1);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(LED_PIN, LOW); // LED off after transmitting
  
  delay(100); // Adjust delay as needed for responsiveness
}
