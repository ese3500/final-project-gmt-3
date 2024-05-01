/*
 * CuriosityBox.c
 *
 * Created: 4/26/2024 6:31:04 AM
 * Author : Kidus
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

#include "ST7735.h"
#include "LCD_GFX.h"


#define MAX_TRUTH_QUESTIONS 9

#define MAX_DARE_QUESTIONS 5
#define QUESTION_LENGTH 50

char questionsDare[MAX_DARE_QUESTIONS][2][31] = {
	{
		"Imitate a celebrity of the ",
		"group's choosing for 2 minutes."
	},
	{
		"Try to lick your elbow while ",
		"singing the alphabet."
	},
	{
		"Try to juggle 3 items from the",
		" room."
	},
	{
		"Use lipstick to write the word",
		" 'dare' on your forehead."
	},
	{
		"Give a piggyback ride to the ",
		"person on your right."
	}
};
char questionsTruth[MAX_TRUTH_QUESTIONS][2][31] = {
	{
		"What is your deepest fear?",
		""
	},
	{
		"What is one secret you are hi-",
		"ding from your best friend?",
	},
	{
		"If you could change a thing in",
		"your past, what would it be?"
	},
	{
		"What is the most embarrassing ",
		"thing you've ever done?"
	},
	{
		"Who in this room do you think ",
		"would be the worst date?"
	},
	{
		"What's something that your",
		"mom doesn't know about you?"
	},
	{
		"Have you ever cheated in an",
		" exam?"
	},
	{
		"What is the biggest lie you've ",
		"told without getting caught?"
	},
	{
		"Who is your secret crush?",
		""
	}
};

volatile int isPlaying = 0;
volatile int truthOrDare = 0;
volatile int nextQ = 0;

void initPWM() {
	DDRD |= (1 << DDD3); // Set PD3/OC2B as an output

	// Set fast PWM mode with TOP in OCR2A (Mode 7 on Timer2)
	TCCR2A = (1 << WGM21) | (1 << WGM20) | (1 << COM2B1);
	TCCR2B = (1 << WGM22) | (1 << CS22) | (1 << CS20); // Fast PWM, set prescaler to 64

	// Set OCR2A for a 50Hz frequency based on a prescaler of 64
	OCR2A = 499; // 50Hz = 16MHz / (64 * (1 + OCR2A))

	// Initial duty cycle (e.g., middle position)
	OCR2B = 125; // Mid-point for 1ms pulse width, adjust for calibration
}

void setServoAngle(int angle) {
	// Calculate OCR2B value from angle (mapping 0 to 180 degrees to 1ms to 2ms pulse width)
	OCR2B = (angle * (249 - 125) / 180) + 125; // Adjust based on your servo's datasheet
}

void uart_init(void) {
	UBRR0H = (uint8_t)(USART_BAUD_PRESCALER >> 8);
	UBRR0L = (uint8_t)(USART_BAUD_PRESCALER);
	UCSR0B = (1 << RXEN0); // Enable receiver
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, no parity, 1 stop bit
}

uint8_t uart_receive(void) {
	while (!(UCSR0A & (1 << RXC0))); // Wait for data to be received
	return UDR0; // Get and return received data from buffer
}

void Initialize()
{
	cli();
	DDRD &= ~(1 << DDD7);

	PORTD |= (1 << PORTD7);
	DDRD &= ~(1 << DDD4);
	PORTD |= (1 << PORTD4);
	DDRD |= (1 << DDRD2); // BUZZER
	
	// Set PB4 as output pin for the LED
	DDRB |= (1 << DDB4);
	DDRD |= (1 << DDD5);  // PD5 as output
	DDRC |= (1 << DDC0);
	
	// Set clock source for Timer 1 with prescaler of 8
	TCCR1B |= (1 << CS11);
	
	// Configure Timer 1 for input capture mode with rising and falling edge detection
	//TCCR1B |= (1 << ICES1);    // Set to capture rising edge first
	//TIFR1 |= (1 << ICF1);
	//TIMSK1 |= (1 << ICIE1);    // Enable input capture interrupt
	PCICR |= (1 << PCIE2); // Enable pin change interrupt for PORTD (PCINT16-23)
	PCMSK2 |= (1 << PCINT23) | (1 << PCINT20); //(1 << PCINT16); // Enable pin change interrupt for PD7
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
		//{ sprintf(String,"inHelper");
		//UART_putstring(String);
		// Turn off the LED connected to PB1
		
		
		//PORTB &= ~(1 << PORTB4);
		TCCR1B |= (1 << ICES1);    // Set to capture rising edge first
	}
	else // Button pressed
	{
		truthOrDare++;
		if (truthOrDare % 2 == 0) {
			LCD_setScreen(BACKGROUND_COLOR);
			LCD_drawString(57, 63, "TRUTH MODE", WHITE, BACKGROUND_COLOR);
			nextQ = 0;
			} else {
			//PORTC |= (1 << PORTC0);
			//Delay_ms(5000);
			//PORTC &= ~(1 << PORTC0);
			LCD_setScreen(BACKGROUND_COLOR);
			LCD_drawString(57, 63, "DARE MODE", WHITE, BACKGROUND_COLOR);
			nextQ = 0;
		}
		
		// Turn on the LED connected to PB1
		//PORTB |= (1 << PORTB4);
		TCCR1B &= ~(1 << ICES1);
	}
	
	if (!(PIND & (1 << PIND4))) // Button released
	{
		// Turn off the LED connected to PD5
		PORTD &= ~(1 << PORTD5);
		TCCR1B |= (1 << ICES1);    // Set to capture rising edge first
	}
	else // Button pressed
	{
		nextQ = 1;
		isPlaying = 1;
		// Turn on the LED connected to PD5
		PORTD |= (1 << PORTD5);
		TCCR1B &= ~(1 << ICES1);
	}
	
}


int main(void)
{
	volatile int value;
	// intialize uart for receive
	uart_init();
	
	char received_message[2]; // Buffer to store the received message
	uint8_t message_index = 0;
	
	// Initialize the microcontroller
	lcd_init();
	
	// Set up screen
	LCD_setScreen(BACKGROUND_COLOR);

	Initialize();
	initPWM();
	while (1) {
		
	if (isPlaying == 1) {
		LCD_setScreen(BACKGROUND_COLOR);
		
		
		if (truthOrDare % 2 == 0) {
			value = rand() % MAX_TRUTH_QUESTIONS;
			LCD_drawString(57, 63, "TRUTH", WHITE, BACKGROUND_COLOR);
			Delay_ms(5000);
			LCD_setScreen(BACKGROUND_COLOR);
			LCD_drawString(1, 63, questionsTruth[value][0], WHITE, BACKGROUND_COLOR);
			LCD_drawString(1, 71, questionsTruth[value][1], WHITE, BACKGROUND_COLOR);
			
			
			
			} else {
			value = rand() % MAX_DARE_QUESTIONS;
			LCD_drawString(57, 63, "DARE", WHITE, BACKGROUND_COLOR);
			
			Delay_ms(5000);
			LCD_setScreen(BACKGROUND_COLOR);
			LCD_drawString(1, 63, questionsDare[value][0], WHITE, BACKGROUND_COLOR);
			LCD_drawString(1, 71, questionsDare[value][1], WHITE, BACKGROUND_COLOR);
			
		}
		
		isPlaying = 0;
		
		
		
		
		////just until we have the data in 0 and 1 form
		//if (truthOrDare % 4 == 0) {
		//truthOrLie = 0;
		//} else {
		//truthOrLie = 1;
		//}
		
	}
	
	if (truthOrDare % 2 == 0 && nextQ == 1) {
		uint8_t received_data = uart_receive();
			if (received_data != '\n') {
				received_message[message_index++] = received_data;
				} else {
				received_message[message_index] = '\0'; // Null-terminate the string

				if (strcmp(received_message, "L") == 0) {
					setServoAngle(0);   // Move servo to 45 degrees
					PORTD |= (1 << PORTD2); // Lies buzzer high
					
					} else {
						setServoAngle(90);   // Move servo to 45 degrees	
						PORTD &= ~(1 << PORTD2); // truth buzzer low			
					}
					message_index = 0; // Reset the message index for the next message
			} 
		} 
		if (truthOrDare % 2 == 1) {
			PORTD &= ~(1 << PORTD2); // truth buzzer low
		}
	
}
			}