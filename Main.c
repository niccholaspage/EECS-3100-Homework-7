// *******************************************************************
// main.s
// Author: Nicholas Nassar
// Date Created: 10/27/2020
// Last Modified: 11/3/2020
// Section Number: Lecture 001, Lab 002
// Instructor: Devinder Kaur
// Homework Number: 7
// Includes the functions and assembly subroutines
// that implements the functionality required by
// homework #7.
// *******************************************************************


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

// Question 5 declarations
// Fixed - strcpy needs to be defined as an extern function
// so that the compiler knows that this function exists as an
// assembly procedure.
extern void strcpy(char* destination, char* source);

char src[25] = "Hello";
char dst[25];

// Question 6 declarations
extern void remove_occurrences(char* str, char character);

char str[] = "The Quick Brown Fox Jumps Over a Lazy Dog";

// Question 7 declarations
extern void string_swap(char** first, char** second);

char* first_string = "Chicken is a test";
char* second_string = "Cake is good";

// Question 8 declarations
extern signed int max4(signed int num1, signed int num2, signed int num3, signed int num4);

signed int result = 0;

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
	strcpy(dst, src);
	
	// Question 6 Testing
	remove_occurrences(str, 'o');
	
	// Question 7 Testing
	string_swap(&first_string, &second_string);
	
	// Question 8 Testing
	result = max4(1, 100, 200, 99);
	result = max4(99, 1, 100, 200);
	result = max4(200, 99, 1, 100);
	result = max4(100, 200, 99, 1);
	
	while (1) {
	}
}
