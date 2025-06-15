#include <ServoPico.h>

ServoPico servo;

void setup() {
  Serial.begin(115200);
  servo.attach(15); // GPIO 15
}

void loop() {
  for (int16_t i = 0; i <= 180; i += 10) {
    servo.write(i);
    Serial.print("Angle: "); Serial.println(servo.read());
    delay(500);
  }

  for (int16_t i = 180; i >= 0; i -= 10) {
    servo.write(i);
    Serial.print("Angle: "); Serial.println(servo.read());
    delay(500);
  }
}
