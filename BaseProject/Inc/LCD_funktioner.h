#ifndef LCD_FUNKTIONER_H_
#define LCD_FUNKTIONER_H_

#include "LCD_funktioner.c"

lcd_write_string(char* string, uint8_t line, uint8_t* graphics_buffer);
lcd_update(char* string);
void lcd_scroll_text(const char* text, uint8_t* graphics_buffer, uint8_t scroll_interval);



#endif /* LCD_FUNKTIONER_H_ */
