#include <stdint.h>

#define NVIC_ST_CTRL_R		(*((volatile uint32_t *)0xE000E010)) 
#define NVIC_ST_RELOAD_R	(*((volatile uint32_t *)0xE000E014)) 
#define NVIC_ST_CURRENT_R	(*((volatile uint32_t *)0xE000E018))
#define NVIC_SYS_PRI3_R		(*((volatile uint32_t *)0xE000ED20))

void SystemInit() {
}

void Q1_SysTick_Init() {
	NVIC_ST_CTRL_R = 0; 
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x00000005;
}

// Adapted from page 215 of book
void Q1_SysTick_Wait1ms() {
	NVIC_ST_RELOAD_R = 50000 - 1; // number of counts to wait - clock cycles in 1 ms (assuming 50 MHz clock)
	NVIC_ST_CURRENT_R = 0; // any value written to CURRENT clears
	while ((NVIC_ST_CTRL_R & 0x00010000) == 0) { // wait for count flag
	}
}

void EnableInterrupts() {
}

void Q2_SysTick_Init_100us_Interrupt() {
	NVIC_ST_CTRL_R = 0; // disable SysTick during init
	NVIC_ST_RELOAD_R = 7999; // assuming 80 MHz, 12.5 ns * 8000 (from 7999 + 1) = 100,000 ns or 100 us
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) |0x20000000; // priority 1
	NVIC_ST_CURRENT_R = 0; // clear flag
	NVIC_ST_CTRL_R = 0x07; // Arm and enable SysTick with interrupts
	EnableInterrupts(); // Enable interrupts
}

#define SIZE 64

struct Student {
	unsigned long id;
	unsigned long score;
	unsigned char grade; // you will enter 'P' or 'F'
};

typedef struct Student STyp;

unsigned long Grades(STyp class[SIZE]){
	unsigned int i;
	
	unsigned long sumOfScores = 0;

	for (i = 0; i < SIZE; i++) {
		STyp* student = &class[i];
		
		// Set student's grade to passing or failing
		student->grade = student->score >= 75 ? 'P' : 'F';

		sumOfScores += student->score; // Sum up all student scores
	}

	return sumOfScores / SIZE; // Average sum of scores by dividing by amount of scores
}

// Question 3 declarations
STyp class[SIZE];
unsigned long studentIterator;
unsigned long average;

int main(void) {
	// Question 1 Testing
	Q1_SysTick_Init();
	Q1_SysTick_Wait1ms();
	
	// Question 2 Testing
	Q2_SysTick_Init_100us_Interrupt();

	// Question 3 Testing
	for (studentIterator = 0; studentIterator < SIZE; studentIterator++) {
		// Initialize each student's ID to our student iterator
		STyp* student = &class[studentIterator];
		
		student->id = studentIterator;
		
		// Initialize the score to 50 or 100 based
		// on where we are at in the loop.
		if (studentIterator < SIZE / 2) {
			student->score = 50;
		} else {
			student->score = 100;
		}
	} // At this point, each student's ID and score should be initialized.
	// If we average 50 (32 times) and 100 (32 times), we end up with 75!
	average = Grades(class); // 75 is in fact the average, so this works!
	
	// Question 5 Testing
	char src[25] = "Hello";
	char dst[25];

	strcpy(dst, src);
	
	while (1) {
	}
}