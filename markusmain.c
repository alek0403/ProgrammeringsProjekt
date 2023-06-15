#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "LUT.h"

struct entity{ //creates the player
 	volatile uint8_t xpos;
 	volatile uint8_t ypos;
 	volatile uint8_t score;
};
struct entity player;


typedef struct{ //boxes and bullets
 	volatile uint8_t xpos;
 	volatile uint8_t ypos;
 	volatile uint8_t lives;
 	volatile uint8_t active;
 } Box,Bullet;


struct posArr{
	 volatile uint16_t posArr[32][3]; //x,y
 };
struct posArr pab; //possition array box;

 Box makeBox(uint8_t i){//assigns different boxes, different values and returns a new box-struct
	Box box;
	box.xpos = (15*i)+5;
	box.ypos = 10;
	box.active = 1;
	box.lives = 3;
	return box;
}

 Bullet makeBullet(){ //assigns different boxes, different values and returns a new box-struct
	Bullet bullet;
	bullet.xpos = player.xpos;
	bullet.ypos = player.ypos - 10;
	bullet.active = 1;
	return bullet;
}

 void drawBullet(Bullet bullet){ //Draws boxes
	if(bullet.active == 1){
		uint8_t x = bullet.xpos;
		uint8_t y = bullet.ypos;
		char letter_E[10][10] = {
 		        {' ', ' ', ' ', 219, 219, 219, 219, ' ', ' ', ' '},
 		        {' ', ' ', 219, 219, 219, 219, 219, 219, ' ', ' '},
 		        {' ', ' ', 219, 219, 219, 219, 219, 219, ' ', ' '},
 		        {' ', 219, 219, 219, 219, 219, 219, 219, 219, ' '},
 		        {' ', 219, 219, 219, 219, 219, 219, 219, 219, ' '},
 		        {' ', 219, 219, 219, 219, 219, 219, 219, 219, ' '},
 		        {' ', 219, 219, 219, 219, 219, 219, 219, 219, ' '},
 		        {' ', 219, 219, 219, 219, 219, 219, 219, 219, ' '},
 		        {' ', 219, 219, 219, 219, 219, 219, 219, 219, ' '},
 		        {' ', 219, 219, 219, 219, 219, 219, 219, 219, ' '}
 		    };
 		    uint8_t i, j;
 		    for (i = 0; i < 10; i++) {
 		    	gotoxy(x,y+i);
 		        for (j = 0; j < 10; j++) {
 		            printf("%c", letter_E[i][j]);
 		        }
 		    }
	}
 }

void drawBoxes(Box box){ //Draws boxes
	if(box.active == 1){
		uint16_t x = box.xpos;
		uint16_t y = box.ypos;
		char letter_E[10][10] = {
		        {219, 219, 219, 219, 219, 219, 219, 219, 219, 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, 219, 219, 219, 219, 219, 219, 219, 219, 219}
		    };

		    uint8_t i, j;
		    for (i = 0; i < 10; i++) {
		    	gotoxy(x,y+i);
		        for (j = 0; j < 10; j++) {
		            printf("%c", letter_E[i][j]);
		        }
		       }
		      }
}


void drawPlayer(){ //Draws the player
	uint8_t x=player.xpos;
	uint8_t y=player.ypos;
	char letter_E[10][10] = {
		        {219, 219, 219, 219, 219, 219, 219, 219, 219, 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 219},
		        {219, 219, 219, 219, 219, 219, 219, 219, 219, 219}
		    };

		    uint8_t i, j;

		    for (i = 0; i < 10; i++) {
		    	gotoxy(x,y+i);
		        for (j = 0; j < 10; j++) {
		            printf("%c", letter_E[i][j]);
		        }
		    }
}

void drawClear(){ //Clears (Currently) the players position
	gotoxy(player.xpos,player.ypos);
	uint8_t x=player.xpos;
	uint8_t y=player.ypos;
		        for ( uint8_t i = 0; i < 10; i++) {
		        	gotoxy(x,y+i);
		            printf("          ");
		    }
}

void drawClearBullet(Bullet bullet){ //Clears (Currently) the players position
	uint8_t x=bullet.xpos;
	uint8_t y=bullet.ypos;
    for ( uint8_t i = 0; i < 10; i++) {
        	gotoxy(x,y+i);
            printf("          ");

    }
}

void drawClearBox(uint8_t x, uint8_t y){ //Clears (Currently) the players position
    for ( uint8_t i = 0; i < 10; i++) {
        	gotoxy(x,y+i);
            printf("          ");

    }
}


uint8_t bulletCollision(Bullet bullet){ //BulletCollision
	for(uint8_t i = 0; i<32; i++){
		uint8_t x_box = pab.posArr[i][0];
		uint8_t y_box = pab.posArr[i][1];
		if (((bullet.xpos - x_box <= 10) && (x_box - bullet.xpos <= 10)) &&
		    ((bullet.ypos - y_box <= 10) && (y_box - bullet.ypos <= 10))) {
				pab.posArr[i][2] -= 1 ;
				bullet.active = 0;
				drawClearBullet(bullet);
				if(pab.posArr[i][2] < 1){
					drawClearBox(x_box,y_box);
					pab.posArr[i][0] = 0;
					pab.posArr[i][1] = 0;
					gotoxy(x_box,y_box);
					player.score += 100;
					printf("%d", player.score);
		return 1;
			}
	}
	}
	return 0;
}

void shoot(){
	Bullet myBullet = makeBullet();
	while(myBullet.active == 1){
		drawClearBullet(myBullet);
		myBullet.ypos-=10;
			if((myBullet.ypos <= 10) || (bulletCollision(myBullet) == 1)){
				myBullet.ypos+=10;
				drawClearBullet(myBullet);
				myBullet.active = 0;
		}
			drawBullet(myBullet);
		}
}

void playerControl(){
	//checks if the bit values, for a certain bit index in jsBit in joyStick.c is greater than 0, if so, move in the dirrection
	if(((readyJoystick() & (1 << 2)) > 0) && (player.xpos > 0+2 )){//move left
		drawClear();
		player.xpos--;
		drawPlayer();
	}
	if(((readyJoystick() & (1 << 3)) > 0) && (player.xpos < 201-10 )){//move right
		drawClear();
		player.xpos++;
		drawPlayer();
		}
	if((readyJoystick() & (1 << 4)) > 0){//Resereved for shooting
		shoot();
		}
	}

	void boxLogic(uint8_t numberOfBoxes){
		for(uint8_t i = 0 ; i < numberOfBoxes; i++){
				Box tempBox = makeBox(i);
				drawBoxes(tempBox);
					uint8_t x = tempBox.xpos;
					uint8_t y = tempBox.ypos;
				        pab.posArr[i][0] = x;
				        pab.posArr[i][1] = y;
				        pab.posArr[i][2] = 3;
		}
	}

int main(void){
	// Setup communication with the PC
	uart_init(200000);
	pinSetup();
	// Setup map and player
	clrscr();
	Bane();
	player.xpos=100;
	player.ypos=230;
	drawPlayer();
	boxLogic(6);

	while (1){
		playerControl();
	}
}

