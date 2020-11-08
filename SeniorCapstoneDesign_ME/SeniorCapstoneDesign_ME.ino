/*
 * SeniorCapstoneDesign_ME.ino
 * 
 * SKKU
 * School of Mechanical Engineering
 * School of Electromagnetic Engineering
 * School of Bio-Mechatronics
 * 
 * Undergraduated student
 * 
 * 2020.05.22
 * 
 * Modified history :
 * 
 *            2020.05.22, Controlled by Bluetooth Only
 *            2020.06.06, Add IMU Sensor(MPU6050)
 *            2020.06.12, Add PID Control
 *            
 *   NOTE : Rollivery, Rolling Delievery robot
 *   
 *          Wireless Operation by using bluetooth
 *          Self-Balance System by PID
 */

#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "MPU6050.h"

// For MPU9250, SCL - A5, SDA - A4

int state = 0;          //Initial state for operation
int servoPin = 12;       //ServoPin
int blueTx = 2;         //TXD Pin
int blueRx = 3;         //RXD Pin

int firstDCinput1 = 5;  //Digital pins for PWM control
int firstDCinput2 = 6;
int secondDCinput1 = 10;
int secondDCinput2 = 11;

int value;              //save values from bluetooth

int PID = 0;            // General state for PID.
                        // Initially, PID is turned off.

float aRes, gRes;       // scale resolutions per LSB for the sensors
int16_t accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
float ax, ay, az;       // Stores the real accel value in g's
int16_t gyroCount[3];   // Stores the 16-bit signed gyro sensor output
float gx, gy, gz;       // Stores the real gyro value in degrees per seconds
float gyroBias[3] = {0, 0, 0};
float accelBias[3] = {0, 0, 0}; // Bias corrections for gyro and accelerometer
int16_t tempCount;              // Stores the real internal chip temperature in degrees Celsius
float temperature;
float SelfTest[6];
float q[4] = {1.0f, 0.0f, 0.0f, 0.0f}; // vector to hold quaternion
uint32_t delt_t = 0;                   // used to control display output rate
uint32_t count = 0;                    // used to control display output rate
float pitch, yaw, roll;

// parameters for 6 DoF sensor fusion calculations
float GyroMeasError = PI * (40.0f / 180.0f);     // gyroscope measurement error in rads/s (start at 60 deg/s), then reduce after ~10 s to 3
float beta = sqrt(3.0f / 4.0f) * GyroMeasError;  // compute beta
float GyroMeasDrift = PI * (2.0f / 180.0f);      // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
float zeta = sqrt(3.0f / 4.0f) * GyroMeasDrift;  // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value
float deltat = 0.0f;                             // integration interval for both filter schemes
uint32_t lastUpdate = 0, firstUpdate = 0;        // used to calculate integration interval
uint32_t Now = 0;                                // used to calculate integration interval

float ref = 0;     // Initial servo value
float error = 0;   // Initial error
float previous_error = 0;     // To compare errors from present and past
float integrated_error = 0;   // define two errors

float Kp = 12;     // Values came from PID Adjustment
float Ki = 0.2;
float Kd = 20;

float K  = 6.3;    // This value will be multiplied by angular velocity
                   // For dual PID
  
// Define Object

Servo servo;
SoftwareSerial mySerial(blueTx, blueRx);
MPU6050lib mpu;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin();
  servo.attach(servoPin);         // servo is connected at digital pin 7
  servo.writeMicroseconds(1500);  // DM-S1300MD has PWM 1000~2000mus rotation angle
                                  // 1000 is 0 degree, 2000 is 180 degree
                                  // Set servo motor at 90 degree

  mpu.MPU6050SelfTest(SelfTest);  // Start by performing self test and reporting values
  mpu.calibrateMPU6050(gyroBias, accelBias);  // Calibrate gyro and accelerometers, load biases in bias registers
  mpu.initMPU6050();              // Initialize MPU 6050
  
  pinMode(firstDCinput1, OUTPUT); // Set PWM Pins as OUTPUT
  pinMode(firstDCinput2, OUTPUT);
  pinMode(secondDCinput1, OUTPUT);
  pinMode(secondDCinput2, OUTPUT);
}

void loop() {
  // values came from bluetooth will be saved at value
  // if value is over 240, then it would be state
  // ==========================================
  // state == 250 : Operation Mode
  // state == 251 : Stop Mode
  // ==========================================

  // ==========================================
  // value == 200  ===> Move Forward
  // value == 201  ===> Move Backward
  // value == 210  ===> Stop
  // ==========================================
  
  // ==========================================
  // 0 < value < 180 ===> Rotate Servo
  // ==========================================
  
  if(mySerial.available() > 0){
    value = mySerial.read();      // Read value send by bluetooth
    // Set state
    if(value > 240) {
      state = value;
    }
    // Operation Mode
    if(state == 250) {
      if(value <= 190) {          // Rotate servo
        servo.write(value);
      }
      else if(value == 210) {     // Stop
        digitalWrite(firstDCinput1, LOW);
        digitalWrite(firstDCinput2, LOW); 
        digitalWrite(secondDCinput1, LOW);
        digitalWrite(secondDCinput2, LOW);
      }
      else if(value == 200) {     // Move Forward
        digitalWrite(firstDCinput1,120);
        digitalWrite(firstDCinput2,0);
        digitalWrite(secondDCinput1,120);
        digitalWrite(secondDCinput2,0);
      }
      else if(value == 201) {     // Move Backward
        digitalWrite(firstDCinput1,0);
        digitalWrite(firstDCinput2,120);
        digitalWrite(secondDCinput1,0);
        digitalWrite(secondDCinput2,120);
      }
      PID = 0;
    }
    else if(state == 251) {       // Stop Mode
      servo.write(90);
      digitalWrite(firstDCinput1, LOW);
      digitalWrite(firstDCinput2, LOW);
      digitalWrite(secondDCinput1, LOW);
      digitalWrite(secondDCinput2, LOW);
      PID = 1;
    }
  }

  if(PID) {
    mpu.readAccelData(accelCount);  // Read the x/y/z adc values
    aRes = mpu.getAres();

    // Now we'll calculate the accleration value into actual g's
    ax = (float)accelCount[0] * aRes; // get actual g value, this depends on scale being set
    ay = (float)accelCount[1] * aRes;
    az = (float)accelCount[2] * aRes;

    mpu.readGyroData(gyroCount);  // Read the x/y/z adc values
    gRes = mpu.getGres();

    // Calculate the gyro value into actual degrees per second
    gx = (float)gyroCount[0] * gRes; // get actual gyro value, this depends on scale being set
    gy = (float)gyroCount[1] * gRes;
    gz = (float)gyroCount[2] * gRes;

    tempCount = mpu.readTempData();  // Read the x/y/z adc values
    temperature = ((float) tempCount) / 340. + 36.53; // Temperature in degrees Centigrade
  
    Now = micros();
    deltat = ((Now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last filter update
    lastUpdate = Now;
    
    // update LCD once per half-second independent of read rate
    delt_t = millis() - count;
    if (delt_t > 500) { 
      MadgwickQuaternionUpdate(ax, ay, az, gx * PI / 180.0f, gy * PI / 180.0f, gz * PI / 180.0f);
  
      yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);  
      pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
      roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);

      pitch *= 180.0f / PI;
      yaw   *= 180.0f / PI;
      roll  *= 180.0f / PI;
      count = millis();
    }
    error = roll - ref;
  
    integrated_error = integrated_error + error * deltat;
    float error_past_pid_controller = Kp * error + Ki * integrated_error + Kd * (error - previous_error) / deltat;

    // Dual PID is here.
    // The robot was unstable with only PID Control.
    // Additioanl control by angular velocity with Coefficient, K,
    // The robot could have stable position with more faster speed
    float pulse = error_past_pid_controller + 1500 + K*gx; 

    // The pulse of DM-S1300MD is PWM 1000~2000mus rotation angle
    // But we will not use over about 150 degree and under 30 degree
    // Therefoare, the pulse over 1800 will be 1800 and
    // under 1200 will be 1200
    if (pulse > 1800) {
      pulse = 1800;
    } else if ( pulse < 1200 ) {
      pulse = 1200;
    }

    // Enter pulse to servo and save error
    myservo.writeMicroseconds(pulse);
    previous_error = error;
  }
}

void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz) {
  float q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];         // short name local variable for readability
  float norm;                                               // vector norm
  float f1, f2, f3;                                         // objetive funcyion elements
  float J_11or24, J_12or23, J_13or22, J_14or21, J_32, J_33; // objective function Jacobian elements
  float qDot1, qDot2, qDot3, qDot4;
  float hatDot1, hatDot2, hatDot3, hatDot4;
  float gerrx, gerry, gerrz, gbiasx, gbiasy, gbiasz;        // gyro bias error

  // Auxiliary variables to avoid repeated arithmetic
  float _halfq1 = 0.5f * q1;
  float _halfq2 = 0.5f * q2;
  float _halfq3 = 0.5f * q3;
  float _halfq4 = 0.5f * q4;
  float _2q1 = 2.0f * q1;
  float _2q2 = 2.0f * q2;
  float _2q3 = 2.0f * q3;
  float _2q4 = 2.0f * q4;
  float _2q1q3 = 2.0f * q1 * q3;
  float _2q3q4 = 2.0f * q3 * q4;

  // Normalise accelerometer measurement
  norm = sqrt(ax * ax + ay * ay + az * az);
  if (norm == 0.0f) return; // handle NaN
  norm = 1.0f/norm;
  ax *= norm;
  ay *= norm;
  az *= norm;
            
  // Compute the objective function and Jacobian
  f1 = _2q2 * q4 - _2q1 * q3 - ax;
  f2 = _2q1 * q2 + _2q3 * q4 - ay;
  f3 = 1.0f - _2q2 * q2 - _2q3 * q3 - az;
  J_11or24 = _2q3;
  J_12or23 = _2q4;
  J_13or22 = _2q1;
  J_14or21 = _2q2;
  J_32 = 2.0f * J_14or21;
  J_33 = 2.0f * J_11or24;
          
  // Compute the gradient (matrix multiplication)
  hatDot1 = J_14or21 * f2 - J_11or24 * f1;
  hatDot2 = J_12or23 * f1 + J_13or22 * f2 - J_32 * f3;
  hatDot3 = J_12or23 * f2 - J_33 *f3 - J_13or22 * f1;
  hatDot4 = J_14or21 * f1 + J_11or24 * f2;
            
  // Normalize the gradient
  norm = sqrt(hatDot1 * hatDot1 + hatDot2 * hatDot2 + hatDot3 * hatDot3 + hatDot4 * hatDot4);
  hatDot1 /= norm;
  hatDot2 /= norm;
  hatDot3 /= norm;
  hatDot4 /= norm;
            
  // Compute estimated gyroscope biases
  gerrx = _2q1 * hatDot2 - _2q2 * hatDot1 - _2q3 * hatDot4 + _2q4 * hatDot3;
  gerry = _2q1 * hatDot3 + _2q2 * hatDot4 - _2q3 * hatDot1 - _2q4 * hatDot2;
  gerrz = _2q1 * hatDot4 - _2q2 * hatDot3 + _2q3 * hatDot2 - _2q4 * hatDot1;
            
  // Compute and remove gyroscope biases
  gbiasx += gerrx * deltat * zeta;
  gbiasy += gerry * deltat * zeta;
  gbiasz += gerrz * deltat * zeta;
  gx -= gbiasx;
  gy -= gbiasy;
  gz -= gbiasz;
            
  // Compute the quaternion derivative
  qDot1 = -_halfq2 * gx - _halfq3 * gy - _halfq4 * gz;
  qDot2 =  _halfq1 * gx + _halfq3 * gz - _halfq4 * gy;
  qDot3 =  _halfq1 * gy - _halfq2 * gz + _halfq4 * gx;
  qDot4 =  _halfq1 * gz + _halfq2 * gy - _halfq3 * gx;

  // Compute then integrate estimated quaternion derivative
  q1 += (qDot1 -(beta * hatDot1)) * deltat;
  q2 += (qDot2 -(beta * hatDot2)) * deltat;
  q3 += (qDot3 -(beta * hatDot3)) * deltat;
  q4 += (qDot4 -(beta * hatDot4)) * deltat;

  // Normalize the quaternion
  norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
  norm = 1.0f/norm;
  q[0] = q1 * norm;
  q[1] = q2 * norm;
  q[2] = q3 * norm;
  q[3] = q4 * norm;
}
