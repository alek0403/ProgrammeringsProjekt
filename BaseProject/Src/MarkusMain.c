#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"

typedef enum {
    PLAYER,
    ENEMY,
	BULLET,
} EntityType;

typedef struct{
	uint8_t xpos;
	uint8_t ypos;
	uint8_t active;
	uint8_t lives;
	uint8_t score;
	EntityType type;
}Entity;



void drawEntity (Entity *entity){
	if(entity->active == 1){
	if (entity->type != BULLET){
	char shape[10][10] = {
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
		    	gotoxy(entity->xpos,entity->ypos+i);
		        for (j = 0; j < 10; j++) {
		            printf("%c", shape[i][j]);
		        }
		    }
	}
	else if (entity->type == BULLET){
		char shape[10][10] = {
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
			    	gotoxy(entity->xpos,entity->ypos+i);
			        for (j = 0; j < 10; j++) {
			            printf("%c", shape[i][j]);
			        }
			    }
		}
	}
}

void initEntity(Entity *entity, EntityType type, uint8_t xpos, uint8_t ypos) {
    entity->xpos = xpos;
    entity->ypos = ypos;
    entity->active = 1;
    entity->lives = 3;
    entity->score = 0;
    entity->type = type;
    drawEntity(entity);
}

void shoot(Entity *entity) {
    uint8_t xpos = entity->xpos;
    uint8_t ypos = entity->ypos - 11;
    Entity bullet;
    initEntity(&bullet, BULLET, xpos, ypos);

    while (bullet.active == 1) {
    	clearEntity(&bullet);
        ypos -= 10;
        if (collision(&bullet, entity) == 1) {
            bullet.active = 0;
        }
        else if (ypos < 5 || ypos > 240) {
            bullet.active = 0; // Bullet reached the top boundary
        } else {
            bullet.ypos = ypos;
            drawEntity(&bullet);
        }

    }
}

void playerControl(Entity *player){ //checks if the bit values, for a certain bit index in jsBit in joyStick.c is greater than 0, if so, move in the dirrection
	if(((readyJoystick() & (1 << 2)) > 0) && ( player->xpos > 0+2 )){//move left
		clearEntity(player);
		 player->xpos--;
		 drawEntity(player);
	}
	if(((readyJoystick() & (1 << 3)) > 0) && ( player->xpos < 201-10 )){//move right
		clearEntity(player);
		player->xpos++;
		drawEntity(player);
		}
	if((readyJoystick() & (1 << 4)) > 0){//Resereved for shooting
		shoot(player);
		}
	}

collision(Entity* bullet, Entity *entity){
	if((bullet->xpos - entity->xpos <= 10) && (entity->xpos - bullet->xpos <= 10) &&
		(bullet->ypos - entity->ypos <= 10) && (entity->ypos - bullet->ypos <= 10)){
		entity->lives -= 1;
	    if(entity->type == BULLET){
	    	entity->lives =0;
	    	clearEntity(entity);
	    }
	    checkEntityStatus(entity);
		return 1;
	}
	return 0;
}

void clearEntity(Entity *entity){
    for ( uint8_t i = 0; i < 10; i++) {
        	gotoxy(entity->xpos, entity->ypos + i);
            printf("          ");

    }
}

void checkEntityStatus(Entity* entity) {
    if (entity->lives == 0) {
        entity->active = 0;
        clearEntity(entity);
    }
}

void createEnemies(Entity *enemies, uint8_t numEnemies) {
    for (uint8_t i = 0; i < numEnemies; i++) {
        uint8_t xpos = (15*i)+5;
        uint8_t ypos = 10;
        initEntity(&enemies[i], ENEMY, xpos, ypos);
    }
}

void getEnemyPositions(Entity *enemies, uint8_t numEnemies, uint8_t (*posArray)[3]) {
    for (uint8_t i = 0; i < numEnemies; i++) {
        posArray[i][0] = enemies[i].xpos;
        posArray[i][1] = enemies[i].ypos;
    }
}


int main(void){
	// Setup communication with the PC
	uart_init(200000);
	pinSetup();
	clrscr();
	Bane();


	uint8_t numEnemies = 5;
	Entity enemies[numEnemies];
	createEnemies(enemies, numEnemies);
	uint8_t enemyPos[numEnemies][3]; //Rows = number of enemies, colloums [0] xpos, [1] ypos, [2] = lives

	Entity player;
	initEntity(&player, PLAYER, 100, 230);

	while (1){
		playerControl(&player);
		getEnemyPositions(enemies, numEnemies, enemyPos);
	}
}

