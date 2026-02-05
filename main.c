/*
 * lab1_2020.cpp
 *
 * Created: 1/9/2020 Based on Lab_1_2019
 * Author : WWClark
 */ 

/*
This program is a solution to Lab 1 -- 
	Pushbutton switches are connected to Pins PD3 and PD4 (pulled high when switch is open).
	LEDs are connected to Pins PD6 and PD7 (active low). 
	
	The program causes the LEDs to mimic the input pin states (i.e. when Pin PD3 is high, the LED connected to Pin PD6 is on.  Likewise for Pins PD4 and PD7).

*/

#include <avr/io.h>
volatile int switch1_press_count = 0;  
volatile int prev_sw1 = 0;            

int main(void)
{
    DDRD = 0b11000000;  // set bits PD7-PD6 as output, PD5-PD0 as input
                        // (this covers Pins 3 and 4 as needed for inputs, and 6 and 7 as needed for outputs)
                        // Follows a practice of making unused pins to be input (safer)

    PORTD = 0b11000000; // set output bits on PORTD so that all outputs are off (they are wired as active low)

    // ============================================
    // P R O G R A M L O O P
    // ============================================

    // Put sw1 outside the loop so it is easier to observe in debugging windows
    int sw1; // sw1 = 1 pressed, sw1 = 0 no press

    while (1)
    {
        // ------------------------------------------------------------
        // Switch 1 (PD3) -> LED 1 (PD6)
        // ------------------------------------------------------------

        if (PIND & 0b00001000) // Check the status of Switch 1.
            // This line checks the switch status by doing a Boolean operation between PIND (where the switch is connected)
            // and a binary number that targets the single pin that we are trying to read (Pin 3).
            // The argument of the If is TRUE only if the switch is closed (and Pin3 is a high voltage),
            // in which case we want to turn on LED 1.
        {
            sw1 = 1;
        }
        else
        {
            sw1 = 0;
        }

        if (sw1 == 1)
        {
            PORTD &= 0b10111111; // Turn on LED 1.
            // This line uses Boolean arithmetic to clear pin PD6 while leaving the other bits on PORTD unchanged.
            // Specifically, it forces PD6 to be 0. Since the LED on PD6 is wired as active low, this turns it ON.
        }
        else
        {
            PORTD |= 0b01000000; // Turn off LED 1.
            // Boolean arithmetic to force PD6 to be 1 (high). Since the LED is active low, this turns it OFF.
        }

        // Lab 2B requirement: count how many times Switch 1 is pressed
        // Only add 1 when the switch changes from not pressed (0) to pressed (1)
        if ((sw1 == 1) && (prev_sw1 == 0)) // only +1 when pressed
        {
            switch1_press_count = switch1_press_count + 1;
        }
        prev_sw1 = sw1; // refresh for the next loop

        // ------------------------------------------------------------
        // Repeat for LED and Switch 2 (PD4 -> LED2 on PD7)
        // ------------------------------------------------------------

        if (PIND & 0b00010000) // Check the status of Switch 2.
            // Same as above but pin PD4 is the target.
        {
            PORTD &= 0b01111111;  // Turn on LED 2.
            // Same as in first If but pin PD7 is the target.
            // Active low, so clearing PD7 turns LED2 ON.
        }
        else
        {
            PORTD |= 0b10000000; // Turn off LED 2.
            // Same as in first Else but pin PD7 is the target.
            // Active low, so setting PD7 high turns LED2 OFF.
        }
    }

    return 0;
}
// ============================================
// S U B R O U T I N E S
// ============================================


