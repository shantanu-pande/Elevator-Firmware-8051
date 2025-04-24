#include <reg51.h>

#define t_SEGMENT_MASK 0x78
#define C_SEGMENT_MASK 0x39
#define L_SEGMENT_MASK 0x38
#define O_SEGMENT_MASK 0x3F
#define CLEAR_DISPLAY 0x00

void delay_ms(unsigned int ms);
void init_io();
void display_segments(unsigned char pattern);

void main() {
	init_io();	
	
	while (1) {
		if (~CL | ~CL&~GL){
			BZ on
			display_segments(C_SEGMENT_MASK);
		}
		else if (~GL){
			BZ on
			display_segments(L_SEGMENT_MASK);
		}
		else if (~DF | ~UF){
			display_segments(t_SEGMENT_MASK);
		}
		else if (DF & CL & GL & UF){
			display_segments(CLEAR_DISPLAY);
			FN on
			delay_ms(2000);
			DN on
			
			while(DL off){}
			
			if (DL on){
				2S on
			}
			
			
			
			
		}
		
  }
}

void display_segments(unsigned char pattern) {
    if (pattern & 0x01) {
        P2 |= 0x04;  // Set P2.2 (a) high
    } else {
        P2 &= ~0x04; // Set P2.2 (a) low
    }
    if (pattern & 0x02) {
        P2 |= 0x02;  // Set P2.1 (b) high
    } else {
        P2 &= ~0x02; // Set P2.1 (b) low
    }
    if (pattern & 0x04) {
        P2 |= 0x01;  // Set P2.0 (c) high
    } else {
        P2 &= ~0x01; // Set P2.0 (c) low
    }
    if (pattern & 0x08) {
        P0 |= 0x80;  // Set P0.7 (d) high
    } else {
        P0 &= ~0x80; // Set P0.7 (d) low
    }
    if (pattern & 0x10) {
        P0 |= 0x10;  // Set P0.4 (e) high
    } else {
        P0 &= ~0x10; // Set P0.4 (e) low
    }
    if (pattern & 0x20) {
        P0 |= 0x20;  // Set P0.5 (f) high
    } else {
        P0 &= ~0x20; // Set P0.5 (f) low
    }
    if (pattern & 0x40) {
        P0 |= 0x40;  // Set P0.6 (g) high
    } else {
        P0 &= ~0x40; // Set P0.6 (g) low
    }
}

void init_io(){
	P0 = 0x00;  			//LD3 LD2 LD1 LD0 E F G D --> out
	P1 = 0xFF;				//DF DL UF UL GL CL C3 C2 --> in
	P2 = 0x00;				//C B A BZ UP DN 2S RC --> out
	P3 = P3 | 0x7F;		//C1 C0 ST DZ OB UR DR --> in
	P3 = P3 & ~0x80; 	// FN --> out
}

void delay_ms(unsigned int ms) {
	unsigned int i, j;
	for (i = 0; i < ms; i++) {
		for (j = 0; j < 120; j++) {
			//120 for 11.0592 MHz clock
			}
		}
}