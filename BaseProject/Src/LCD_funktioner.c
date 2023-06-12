#include <stdint.h>
#include <string.h>
#include <charset.h>
#include <timing_config.h>

// funktion der tager en string og en position i bufferen fra 0-512 og indsætter stringen på den position.
void lcd_write_string(char* string, uint8_t line, uint8_t* graphics_buffer) {
  uint8_t buffer_index = line; // Each character is 5 slices wide
  uint8_t char_index;

  while (*string) {
    char_index = *string - 32; // Subtract 32 to match character map indexes

    // Copy character data from the character map to the graphics buffer
    for (uint8_t i = 0; i < 5; i++) {
      graphics_buffer[buffer_index+ i] = character_data[char_index][i];
    }

    buffer_index += 5; // Move to the next character in the buffer
    string++; // Move to the next character in the input string
  }
}

// En update funktion som når flaget er højt tilføjer til en string og derefter sætter flaget lavt.
void lcd_update(char* string) {
    if (ticks.flag == 1) {
        strcat(string, "42"); // Append "42" to the end of the string
        printf("%s\n", string);
        ticks.flag = 0;
    } else {
        ticks.flag = 0; // Reset the flag
    }
}


// en funktion som tager en tekst og bufferen og scroller den med et niveau altså interval.
void lcd_scroll_text(const char* text, uint8_t* graphics_buffer, uint8_t scroll_interval) {

	//definerer værdier for LCD skærmen og måden hvorpå den er inddelt.
    static uint8_t buffer_index = 0;
    static const uint8_t LCD_WIDTH = 128;
    static const uint8_t LCD_HEIGHT = 32;
    static const uint8_t SLICE_HEIGHT = 8;
    static const uint8_t SLICES_PER_ROW = 16;
    static const uint16_t BUFFER_SIZE = 512;

    if (ticks.flag == 1) {
        buffer_index++;
        if (buffer_index >= strlen(text) + SLICES_PER_ROW) {
            buffer_index = 0; // Wrap back to the starting position
        }
        ticks.flag = 0;
    }

    // Clear the graphics buffer
    memset(graphics_buffer, 0, BUFFER_SIZE);

    // Copy the text into the graphics buffer
    uint8_t text_length = strlen(text);
    for (uint8_t row = 0; row < LCD_HEIGHT; row += SLICE_HEIGHT) {
        for (uint8_t slice = 0; slice < SLICES_PER_ROW; slice++) {
            uint8_t char_index = text[(buffer_index + slice) % text_length] - 32; // Subtract 32 to match character map indexes

            // Copy character data from the character map to the graphics buffer
            for (uint8_t i = 0; i < SLICE_HEIGHT; i++) {
            	graphics_buffer[(row + i) * SLICES_PER_ROW + slice] = character_data[char_index][i + 3];

            }
        }
    }
}

void LCD_liv(uint8_t *liv, uint8_t* graphics_buffer){
	lcd_write_string("liv",0, graphics_buffer);
	if(liv = 0){
		lcd_write_string("1",130, graphics_buffer);
	}
	if(liv = 1){
		lcd_write_string("2",130, graphics_buffer);
	}
	if(liv = 2){
		lcd_write_string("3",130, graphics_buffer);
	}
}

void LCD_LVL(uint8_t *lvl, uint8_t* graphics_buffer){
	lcd_write_string("lvl",50, graphics_buffer);
	if(lvl = 0){
		lcd_write_string("0",180, graphics_buffer);
	}
	if(lvl = 1){
		lcd_write_string("1",180, graphics_buffer);
	}
	if(lvl = 2){
		lcd_write_string("2",180, graphics_buffer);
	}
}

void LCD_Score(uint8_t *score, uint8_t* graphics_buffer){
	char str[100];
	sprintf(str, "%d", score);
	lcd_write_string("score", 100, graphics_buffer);
	lcd_write_string(str, 230, graphics_buffer);

}

