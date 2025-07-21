#include "unity.h"
#include "unity_internals.h"

void setUp(void) {};
void tearDown(void) {};

int main(void) {
  stdio_init_all();
  sleep_ms(10000);

  UNITY_BEGIN();

  UNITY_END();

  while (true) {
    sleep_ms(1000);
  }
}
