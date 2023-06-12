#define ESC 0x1B
#include <stdio.h>
#include <stdint.h>
#include <Lut1.h>

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr(){
	printf("%c[2J",ESC);
	printf("%c[H", ESC);
}

void clreol(){
	printf("%c[2K",ESC);
}

void gotoxy(uint8_t x, uint8_t y){
	printf("%c[%d;%df",ESC, y, x);
}

void underline(uint8_t on){
	if (on==0){
	printf("%c[24m",ESC);
	}
	else {
		printf("%c[4m",ESC);
	}
}
void blink(uint8_t on){
	if (on==0){
		printf("%c[25m",ESC);
		}
		else {
			printf("%c[5m",ESC);
		}
}

void inverse(uint8_t on){
	if (on==0){
		printf("%c[27m",ESC);
		}
		else {
			printf("%c[7m",ESC);
		}
}

void Bane(){ //printer bane som er 256x201 felter.

	 fgcolor(10);
	 gotoxy(0,0);

	for(int i = 0; i<201;i++){
		printf("%c",219);
	}

	for(int k = 0;k<255;k++){
		gotoxy(0,k);
		printf("%c",219);
		gotoxy(201,k);
		printf("%c",219);
	}

	gotoxy(0,255);

	for(int j = 0; j<201;j++){
			printf("%c",219);
	}

}











