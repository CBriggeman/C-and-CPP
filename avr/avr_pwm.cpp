/*
 * avr_pwm.cpp
 *
 * Created: 11/19/2012 8:45:57 PM
 *  Author: Chris
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	/*This is a program I use to drive my flyback transformer.*/
	/*Target processor is an ATMEGA328P.*/
	
	/*Sets pin 3 on portB as output.*/
	DDRB = (1 << DDB3);
	
	/*Since the frequency of the wave needs to be increased, one has to change some register values.
	*TCCR2A is a register to set the waveform and what the MCU does when it matches value of 
	* output compare register. TCCR2B sets clock with no prescaling. This causes the frequency to increase 
	* to 62.5KHz. */
	TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
	TCCR2B = (1 << CS20);
	
	/*In fast pwm, MCU counts from 0 to 255. With COM2A1 set to 1 the voltage is cleared to 0
	* when counter matches output compare register(OCR2A). Duty cycle of 85.1% */
	OCR2A = 217;
	
    while(1)
    {
     
    }
}