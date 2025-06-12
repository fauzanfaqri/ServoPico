#include <ServoPico.h>

ServoPico servos[4];

const uint8_t servoPins[4] = {15, 16, 17, 18};

void setup() {
  for (uint8_t i = 0; i < 4; i++) {
    servos[i].attach(servoPins[i]);
  }
}

void loop() {
  for (uint8_t angle = 0; angle <= 180; angle += 30) {
    for (uint8_t i = 0; i < 4; i++) {
      servos[i].write(angle);
    }
    delay(500);
  }

  for (uint8_t angle = 180; angle >= 0; angle -= 30) {
    for (uint8_t i = 0; i < 4; i++) {
      servos[i].write(angle);
    }
    delay(500);
  }
}
