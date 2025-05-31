#define DIR1 4
#define PWM1 5
#define DIR2 6
#define PWM2 7

void setup() {
  pinMode(DIR1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM2, OUTPUT);

  Serial.begin(9600); // Match ROS baud rate
}

// Controls a motor (DIR + PWM pin, and speed from -255 to 255)
void setMotor(int dirPin, int pwmPin, int speed) {
  if (speed >= 0) {
    digitalWrite(dirPin, LOW);    // Forward
    analogWrite(pwmPin, speed);   // Reverse
  } else {
    digitalWrite(dirPin, HIGH);
    analogWrite(pwmPin, -speed);
  }
}

void loop() {
  static String inputString = "";

  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      inputString.trim();

      if (inputString.startsWith("<") && inputString.endsWith(">")) {
        inputString = inputString.substring(1, inputString.length() - 1); // Remove < >

        int l_dir, l_pwm, r_dir, r_pwm;
        int parsed = sscanf(inputString.c_str(), "%d,%d,%d,%d", &l_dir, &l_pwm, &r_dir, &r_pwm);

        if (parsed == 4) {
          // Invert right motor direction if needed
          int l_speed = l_dir == 0 ? l_pwm : -l_pwm;
          int r_speed = r_dir == 0 ? -r_pwm : r_pwm;
          setMotor(DIR1, PWM1, l_speed);
          setMotor(DIR2, PWM2, r_speed);


          Serial.println("Command received and executed.");
        } else {
          Serial.println("Parsing error!");
        }
      }

      inputString = "";  // Clear buffer
    } else {
     inputString += c;
    }
  }

}
