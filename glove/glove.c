/*
 * PulseSensorTest.c
 *
 * Created: 4/26/2024 12:46:36 AM
 * Author : Kidus
 */ 

#define F_CPU 16000000UL
#define USART_BAUD_RATE 9600
#define USART_BAUD_PRESCALER (((F_CPU / (USART_BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PULSE_THRESHOLD 550
#define LED_PIN 5  // Assuming you have an LED on PD5

volatile uint32_t lastBeatTime = 0;
volatile int beatDetected = 0;
volatile int beatsPerMinute = 0;

volatile uint32_t milliseconds = 0;


ISR(TIMER0_COMPA_vect) {
	milliseconds++;
}

// UART SET UP Master End.
void uart_init(void) {
	UBRR0H = (uint8_t)(USART_BAUD_PRESCALER >> 8);
	UBRR0L = (uint8_t)(USART_BAUD_PRESCALER);
	UCSR0B = (1 << TXEN0); // Enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, no parity, 1 stop bit
}

void uart_transmit(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
	UDR0 = data; // Put data into buffer, sends the data
}

void timer0_init() {
	TCCR0A = (1 << WGM01); // CTC mode
	TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler: 64
	OCR0A = 249; // Compare match value for 1ms interrupt
	TIMSK0 = (1 << OCIE0A); // Enable compare match interrupt
	sei(); // Enable global interrupts
}

uint32_t millis() {
	uint32_t ms;
	cli(); // Disable interrupts
	ms = milliseconds;
	sei(); // Enable interrupts
	return ms;
}

void adc_init() {
	ADMUX = (1 << REFS0);  // AVCC with external capacitor at AREF pin
	ADCSRA = (1 << ADEN)  // Enable ADC
	| (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Prescaler at 128 so we have an 125 KHz clock source
}

uint16_t adc_read(uint8_t ch) {
	ADMUX = (ADMUX & 0xF8) | (ch & 0x07);  // select the correct channel: 0-7
	ADCSRA |= (1 << ADSC);  // start ADC conversion
	while (ADCSRA & (1 << ADSC));  // wait until conversion finishes
	return ADC;
}

void process_heartbeat(uint16_t adc_value) {
	uint32_t currentTime = millis();  // Implement this function to return milliseconds
	if (adc_value > PULSE_THRESHOLD && (currentTime - lastBeatTime > 200)) {  // 200 ms to avoid noise
		beatsPerMinute = 60000 / (currentTime - lastBeatTime);  // 60000 ms per minute
		lastBeatTime = currentTime;
		beatDetected = 1;
		PORTD |= (1 << LED_PIN);  // Turn on LED
		} else {
		PORTD &= ~(1 << LED_PIN);  // Turn off LED
	}
}



int main(void)
{
	uart_init();
	adc_init();
	timer0_init(); // Initialize Timer0 for millis()
	DDRD |= (1 << LED_PIN); // set LED pin as output

	 

	while(1) {
		uint16_t adc_value = adc_read(0); // read the value from ADC0
		process_heartbeat(adc_value);
		if (beatDetected) {
			beatDetected = 0;
		}
		if (beatsPerMinute >= 72) {
			// Lies, send the lie signal to the slave
			uart_transmit('L');
			uart_transmit('\n');
			_delay_ms(100); // Delay for 1 second
			 
		} else {
			// likely true, send truth signal to the slave
			uart_transmit('T');
			uart_transmit('\n');
			_delay_ms(100); // Delay for 1 second
			 
		}

		_delay_ms(2); // delay for about 2 milliseconds
	}
}
