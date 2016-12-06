#include "switches.h"

#define ADDR_SLIDESWITCHES  ((volatile long * ) 0xFF200040)

int switch_is_on(int switch_bit){
	return *ADDR_SLIDESWITCHES & (1 << switch_bit);
}