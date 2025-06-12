#include <ServoPico.h>

ServoPico servo;

void setup() {
  Serial.begin(115200);
  servo.attach(15);
  servo.write(90);
  delay(1000);
  servo.detach();
  Serial.println("Servo detached.");
}

void loop() {
  // Servo tidak akan bergerak setelah detach
}
