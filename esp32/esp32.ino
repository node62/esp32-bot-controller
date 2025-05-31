#define BLYNK_TEMPLATE_ID "TMPL3O2HseJge"
#define BLYNK_TEMPLATE_NAME "UGV Controller"
#define BLYNK_AUTH_TOKEN "4HKhj_6cOXyv27G6NBIOR8toelnFNxww"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials
char ssid[] = "iPhone";
char pass[] = "goodquestion";

float linear = 0;
float angular = 0;

#define WHEEL_DISTANCE 0.65
#define MAX_PWM 255
#define MAX_LINEAR_VEL 1.0

BLYNK_WRITE(V0) {
  linear = param.asFloat();
  sendMotorCommand();
}

BLYNK_WRITE(V1) {
  angular = param.asFloat();
  sendMotorCommand();
}

void sendMotorCommand() {
  float left_speed = linear - angular * WHEEL_DISTANCE / 2.0;
  float right_speed = linear + angular * WHEEL_DISTANCE / 2.0;

  int left_pwm = constrain(int((abs(left_speed) / MAX_LINEAR_VEL) * MAX_PWM), 0, MAX_PWM);
  int right_pwm = constrain(int((abs(right_speed) / MAX_LINEAR_VEL) * MAX_PWM), 0, MAX_PWM);

  int left_dir = left_speed >= 0 ? 0 : 1;
  int right_dir = right_speed >= 0 ? 0 : 1;

  // Format command string
  String command = "<" + String(left_dir) + "," + String(left_pwm) + "," + 
                         String(right_dir) + "," + String(right_pwm) + "> ";
//                         <Linear: " + String(linear) + 
//                         ", Ang: "+ String(angular)+ ">\n";

  Serial.print(command);  // Send to Arduino
}

void setup() {
  Serial.begin(9600);  // Must match Arduino's serial baud
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}