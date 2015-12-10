#include "register.h"
#include "error.h"

//create the register table
int registers[16] = {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

const char * register_name(int r) {
	switch(r) {
		case 0:
			return "%rax";
		case 1:
			return "%rbx";
		case 2:
			return "%rcx";
		case 3:
			return "%rdx";
		case 4:
			return "%rsi";
		case 5:
			return "%rdi";
		case 6:
			return "%rbp";
		case 7:
			return "%rsp";
		case 8:
			return "%r8";
		case 9:
			return "%r9";
		case 10:
			return "%r10";
		case 11:
			return "%r11";
		case 12:
			return "%r12";
		case 13:
			return "%r13";
		case 14:
			return "%r14";
		case 15:
			return "%r15";
	}
}

int register_alloc() {
	int i;
	for(i = 0; i<16; i++){
		if(registers[i] == 0){
			registers[i] = 1;
			return i;
		}
	}
	register_error();
}

void register_free(int r) {
	if(r != 0)
		registers[r] = 0;
}
