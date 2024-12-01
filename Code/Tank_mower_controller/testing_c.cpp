#include <stdio.h>
#include <stdint.h>

void setBool(uint8_t* bool_carrier, uint8_t bool_place){
  *bool_carrier |= 0b1 << bool_place;
}

int main()
{
  uint8_t test_bool = 0b00000000;
  uint8_t place = 2;
  std:fprintf(stdout, "Testing %p with position %u",test_bool, place);

  setBool(&test_bool, place);
  std:fprintf(stdout, "outcome %p with position %u",test_bool, place);
  return 0;
}
