#include <Servo.h>

// Define pin numbers for components
const int pH_Pin = A3;          // pH sensor analog pin
const int waterLevel_Pin = A2;  // Water level sensor analog pin
const int temp_Pin = A1;        // Temperature sensor analog pin
const int pump_Pin = 2;         // Pump control pin
const int servo_Pin = 5;        // Servo control pin

// Define threshold values
const float pH_Low = 6.5;
const float pH_High = 9;
const int waterLevel_Low = 50; // adjust these values according to your sensor calibration
const int waterLevel_High = 100;
const int temp_High = 30;       // Temperature threshold in Celsius
const int temp_Low = 21;        // Temperature threshold in Celsius
// Create servo object
Servo servoMotor;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Attach servo to pin
  servoMotor.attach(servo_Pin);

  // Set pump pin as output
  pinMode(pump_Pin, OUTPUT);
}

void loop() {
  // Read sensor values
  float pH_Value = analogRead(pH_Pin)* 0.00488758553; // Convert analog value to voltage
  int waterLevel_Value = analogRead(waterLevel_Pin);
  int temp_Value = analogRead(temp_Pin);
  
  // Convert temperature sensor value to Celsius
  float temp_Celsius = (temp_Value / 1023.0) * 5.0 * 100.0;
  
  // Print sensor values
  Serial.print("pH: ");
  Serial.println(pH_Value);
  Serial.print("Water Level: ");
  Serial.println(waterLevel_Value);
  Serial.print("Temperature: ");
  Serial.println(temp_Celsius);
  
  // Check pH levels and control servo
  if (pH_Value < pH_Low) {
    // Add base
    servoMotor.write(90); // Adjust angle as per your requirement
    delay(1000); // Delay for servo to act
    servoMotor.write(0); // Return to initial position
  } else if (pH_Value > pH_High) {
    // Add acid
    servoMotor.write(180); // Adjust angle as per your requirement
    delay(1000); // Delay for servo to act
    servoMotor.write(0); // Return to initial position
  }
  
  // Check water level and control pump
  if (waterLevel_Value < waterLevel_Low) {
    // Turn on pump
    digitalWrite(pump_Pin, HIGH);
  } else if (waterLevel_Value > waterLevel_High) {
    // Turn off pump
    digitalWrite(pump_Pin, LOW);
  }
  
  // Check temperature and add water if too high
  if (temp_Celsius > temp_High) {
    // Turn on pump
    digitalWrite(pump_Pin, HIGH);
    delay(5000); // Pump water for 5 seconds
    digitalWrite(pump_Pin, LOW);
  }
  
  // Wait for some time before next iteration
  delay(1000); // Adjust delay time as per your requirement
}