/*
 * GccApplication2.c
 *
 * Created: 09-Feb-24 2:10:50 PM
 * Author : user
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <string.h>

#include <avr/interrupt.h>
#include <math.h>
#include <time.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#define USART_BAUD_RATE      9600
#define USART_BAUD_PRESCALER (((F_CPU / (USART_BAUD_RATE * 16UL))) - 1)
#define BACKGROUND_COLOR BLACK

#include "uart.h"
#include "ST7735.h"
#include "LCD_GFX.h"

char String[25];

#define MAX_TRUTH_QUESTIONS 10

#define MAX_DARE_QUESTIONS 5
#define QUESTION_LENGTH 50

 char questionsDare[MAX_DARE_QUESTIONS][80] = {
    "Imitate a celebrity of the group's choosing for 2 minutes.",
    "Try to lick your elbow while singing the alphabet.",
    "Try to juggle 3 items from the room.",
    "Use lipstick to write the word 'dare' on your forehead.",
    "Give a piggyback ride to the person on your right."
};
char questionsTruth[MAX_TRUTH_QUESTIONS][80] = {
    "What is your deepest fear?",
    "What is one secret you are hiding from your best friend?",
    "If you could change one thing about your past, what would it be?",
    "What is the most embarrassing thing you've ever done?",
    "Who in this room do you think would be the worst date?",
    "What's something you're glad your mom doesn't know about you?",
    "Have you ever cheated in an exam?",
    "What is the biggest lie you've ever told without getting caught?",
    "Who is your secret crush?",
    "What is the most childish thing you still do?"
};

volatile int isPlaying = 0;
volatile int truthOrDare = 0;

void Initialize()
{
	cli();
	DDRD &= ~(1 << DDD7);

	PORTD |= (1 << PORTD7);
	 DDRD &= ~(1 << DDD0);
	 PORTD |= (1 << PORTD0);
	
	// Set PB4 as output pin for the LED
	DDRB |= (1 << DDB4);
	DDRD |= (1 << DDD1);  // PD1 as output
	
	// Set clock source for Timer 1 with prescaler of 8
	TCCR1B |= (1 << CS11);
	
	// Configure Timer 1 for input capture mode with rising and falling edge detection
	//TCCR1B |= (1 << ICES1);    // Set to capture rising edge first
	//TIFR1 |= (1 << ICF1);
	//TIMSK1 |= (1 << ICIE1);    // Enable input capture interrupt
	PCICR |= (1 << PCIE2); // Enable pin change interrupt for PORTD (PCINT16-23)
	PCMSK2 |= (1 << PCINT23) | (1 << PCINT16); // Enable pin change interrupt for PD7
	// Enable all global interrupts
	// Clear power reduction bit for ADC
	PRR0 &= ~(1 << PRADC);
	
	// Select Vref = AVcc
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	
	// Select Channel ADC0 (pin C0)
	ADMUX &= ~(1 << MUX0);
	ADMUX &= ~(1 << MUX1);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX3);
	
	ADCSRA |= (1 << ADATE);   // Autotriggering of ADC

	// Free running mode ADTS[2:0] = 000
	ADCSRB &= ~(1 << ADTS0);
	ADCSRB &= ~(1 << ADTS1);
	ADCSRB &= ~(1 << ADTS2);
	 
	// Disable digital input buffer on ADC pin
	DIDR0 |= (1 << ADC0D);

	// Enable ADC
	ADCSRA |= (1 << ADEN);

	// Start conversion
	ADCSRA |= (1 << ADSC);

	

	sei();
}

// Interrupt Service Routine for Timer 1 input capture event
ISR(PCINT2_vect) //
{
	//volatile int score1 = "WORK BIATCH";
	//char str[5];
    //sprintf(str, "%d", score1);
	//LCD_drawString(57, 63, str, BLACK, BACKGROUND_COLOR);
	//// Clear the input capture flag by writing 1 to ICF1 bit
	TIFR1 |= (1 << ICF1);
	
	// Read the state of PB0 to determine button press status
	if (!(PIND & (1 << PIND7))){ // Button released
	//{	sprintf(String,"inHelper");
		//UART_putstring(String);
		// Turn off the LED connected to PB1
		
		
		PORTB &= ~(1 << PORTB4);
		TCCR1B |= (1 << ICES1);    // Set to capture rising edge first
	}
	else // Button pressed
	{
		truthOrDare++;
		if (truthOrDare % 2 == 0) {
			LCD_drawString(57, 63, "TRUTH MODE", WHITE, BACKGROUND_COLOR);
		} else {
			LCD_drawString(57, 63, "TRUTH MODE", WHITE, BACKGROUND_COLOR);
		}
		
		// Turn on the LED connected to PB1
		PORTB |= (1 << PORTB4);
		TCCR1B &= ~(1 << ICES1);
	}
	
	if (!(PIND & (1 << PIND0))) // Button released
	{	
		// Turn off the LED connected to PD1
		PORTD &= ~(1 << PORTD1);
		TCCR1B |= (1 << ICES1);    // Set to capture rising edge first
	}
	else // Button pressed
	{
		isPlaying = 1;
		// Turn on the LED connected to PD1
		PORTD |= (1 << PORTD1);
		TCCR1B &= ~(1 << ICES1);
	}
	
}

int main(void)
{
	volatile int value;
	// Initialize the microcontroller
	lcd_init();
	
	// Set up screen
	LCD_setScreen(BACKGROUND_COLOR);

	Initialize();
	while (1) {
	if (isPlaying == 1) {
		
		if(truthOrDare % 2 == 0) {
			value = rand() % MAX_TRUTH_QUESTIONS;
			LCD_drawString(57, 63, "TRUTH", BLACK, BACKGROUND_COLOR);
			LCD_setScreen(BACKGROUND_COLOR);
			Delay_ms(5000);
			LCD_drawString(57, 63, questionsTruth[value], BLACK, BACKGROUND_COLOR);
			Delay_ms(10000);
			LCD_setScreen(BACKGROUND_COLOR);
		} else {
			value = rand() % MAX_DARE_QUESTIONS;
			LCD_drawString(57, 63, "DARE", BLACK, BACKGROUND_COLOR);
			LCD_setScreen(BACKGROUND_COLOR);
			Delay_ms(5000);
			LCD_drawString(57, 63, questionsDare[value], BLACK, BACKGROUND_COLOR);
			Delay_ms(10000);
			LCD_setScreen(BACKGROUND_COLOR);
		}
		isPlaying = 0;
		
	}
	}
	
}