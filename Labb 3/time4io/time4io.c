#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

//f
int getsw(void) {

	return (PORTD >> 8) & 0x000f;
}

//g
int getbtns(void) {

	return (PORTD >> 5) & 0x0007;
}