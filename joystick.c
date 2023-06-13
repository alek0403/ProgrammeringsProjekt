#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
void pinSetup(){


	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C
	RCC->AHBENR |= RCC_AHBPeriph_GPIOF; // Enable clock for GPIO Port F

	// Set pin PA4 to input (UP)
			GPIOA->MODER |=  (0x00000000 << (4 * 2));
			GPIOA->MODER &= ~(0x00000000 << (4 * 2));
			GPIOA->PUPDR |=  (0x00000002 << (4 * 2));
			GPIOA->PUPDR &= ~(0x00000003 << (4 * 2));

			// Set pin PB0 to input (DOWN)
			GPIOB->MODER |=  (0x00000000 << (0 * 2));
			GPIOB->MODER &= ~(0x00000000 << (0 * 2));
			GPIOB->PUPDR |=  (0x00000002 << (0 * 2));
			GPIOB->PUPDR &= ~(0x00000003 << (0 * 2));

			// Set pin PB5 to input (CENTER)
			GPIOB->MODER |=  (0x00000000 << (5 * 2));
			GPIOB->MODER &= ~(0x00000000 << (5 * 2));
			GPIOB->PUPDR |=  (0x00000002 << (5 * 2));
			GPIOB->PUPDR &= ~(0x00000003 << (5 * 2));


			// Set pin PC0 to input (RIGHT)
			GPIOC->MODER |=  (0x00000000 << (0 * 2));
			GPIOC->MODER &= ~(0x00000000 << (0 * 2));
			GPIOC->PUPDR |=  (0x00000002 << (0 * 2));
			GPIOC->PUPDR &= ~(0x00000003 << (0 * 2));


			// Set pin PC1 to input  (LEFT)
			GPIOC->MODER |=  (0x00000000 << (1 * 2));
			GPIOC->MODER &= ~(0x00000000 << (1 * 2));
			GPIOC->PUPDR |=  (0x00000002 << (1 * 2));
			GPIOC->PUPDR &= ~(0x00000003 << (1 * 2));
}

readyJoystick(){ //reads the value of the joystick and assigns it to jsBit at the specified place.
	uint8_t jsBit = 0;
	uint16_t up 	= GPIOA->IDR & (0x0001 << 4); //reads PA4
	uint16_t down 	= GPIOB->IDR & (0x0001 << 0); //reads PB0
	uint16_t left 	= GPIOC->IDR & (0x0001 << 1); //reads PC1
	uint16_t right 	= GPIOC->IDR & (0x0001 << 0); //reads PC0
	uint16_t center = GPIOB->IDR & (0x0001 << 5); //reads PB5

	//Assigns the value of bit (xxxx) depending on input.
	if(up > 0){
		jsBit |= 1 << 0;}
	if(down > 0){
		jsBit |= 1 << 1;}
	if(left > 0){
		jsBit |= 1 << 2;}
	if(right > 0){
		jsBit |= 1 << 3;}
	if(center  > 0){
		jsBit |= 1 << 4;}
	return jsBit;
}
