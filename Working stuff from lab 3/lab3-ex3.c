#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "led.h"
#include "button.h"
#include "../../../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define LED_PIO PIO_DEFINE(PORT_C, 2)


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}
static const char possible_chars[] = {
    'P', 'R', 'S'
};

int index_of_char(char character)
{
	int index = -1;
	if (character == possible_chars[0]) {
		index = 0;
	} else if (character == possible_chars[1]) {
		index = 1;
	} else if (character == possible_chars[2]) {
		index = 2;
	}
	return index;
}


int main (void)
{
    int char_index = 0;
    char character;
    int away_char = -1;
    char received_char;
    bool char_received_success = 0;
    


    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init ();
    

    /* TODO: Initialise IR driver.  */
    ir_uart_init();
	led_init ();
	button_init ();

    pacer_init (PACER_RATE);

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
        button_update();
        if (button_push_event_p(BUTTON1) & char_received_success) {
			display_character('H');
			tinygl_update();
			led_set (LED1, 0);
			break;	
		}
		
        
        character = possible_chars[char_index];
        
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (char_index == 2) {
                char_index = 0;
            } else {
                char_index ++;
            }
        }
        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (char_index == 0) {
                char_index = 2;
            } else {
                char_index--;
            }
		}

        /* TODO: Transmit the character over IR on a NAVSWITCH_PUSH
           event.  */
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
			ir_uart_putc(character);
			
		}
		
		
		if (ir_uart_read_ready_p()) {
			char ch;
			ch = ir_uart_getc();
			received_char = index_of_char(ch);
			away_char = received_char;
				
		}
		if (away_char != -1) {
			char_received_success = 1;
			led_set (LED1, 1);
				
		} else {
			led_set(LED1, 0);
		}
		
		
		
        
       
        display_character (character);
        
    }
    tinygl_clear();
	
    
    while (1) {
		display_character(possible_chars[away_char]);
		tinygl_update();
	}
    
    

    return 0;
}
