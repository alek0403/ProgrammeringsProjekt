#ifndef LCD_FUNKTIONER_H_
#define LCD_FUNKTIONER_H_

#include "LCD_funktioner.c"

lcd_write_string(char* string, uint8_t line, uint8_t* graphics_buffer);
lcd_update(char* string);
lcd_scroll_text(const char* text, uint8_t* graphics_buffer, uint8_t scroll_interval);
LCD_liv(uint8_t *liv, uint8_t* graphics_buffer);
LCD_LVL(uint8_t *lvl, uint8_t* graphics_buffer);
LCD_Score(uint8_t *score, uint8_t* graphics_buffer);


#endif /* LCD_FUNKTIONER_H_ */
