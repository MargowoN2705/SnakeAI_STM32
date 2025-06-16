/*
 * lcd.h
 *
 *  Created on: Aug 16, 2024
 *      Author: barte
 */


#include <stdint.h>

#define LCD_WIDTH	160
#define LCD_HEIGHT	128


#define RED     0xF800   // 🍎 czerwony
#define GREEN   0x07E0   // 🐍 zielony
#define BLUE    0x001F   // 🔵 niebieski
#define BLACK   0x0000
#define WHITE   0xFFFF


void lcd_init(void);
void lcd_put_pixel(int x, int y, uint16_t color);
void lcd_copy(void);

void lcd_default ();
void lcd_draw_image(int x, int y, int width, int height, const uint8_t* data);
void lcd_clear_screen(uint16_t color);

void lcd_draw_char(int x, int y, char c, uint16_t color);
void lcd_draw_text(int x, int y, const char *text, uint16_t color);
void lcd_fill_rect(int x, int y, int width, int height, uint16_t color);


#ifndef SRC_LCD_H_
#define SRC_LCD_H_



#endif /* SRC_LCD_H_ */
