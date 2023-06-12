
 Test
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "LUT.h"


void timer2(){
	RCC->APB1ENR |= RCC_APB1Periph_TIM2;
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	// Set pin PB10 to output (BUZZER)
	GPIOB->OSPEEDR 	&= ~(0x00000003 << (10 * 2));
	GPIOB->OSPEEDR 	|= (0x00000002 << (10 * 2));
	GPIOB->OTYPER 	&= ~(0x0001 << (10 * 1));
	GPIOB->OTYPER 	|= (0x0000 << (1));
	GPIOB->MODER 	&= ~(0x00000003 << (10 * 2));
	GPIOB->MODER 	|= (0x00000002 << (10 * 2)); //alternate function
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);

	TIM2 ->CR1 		= 0x01; //Primary Config
	TIM2 ->PSC 		=999; //Prescaler
	TIM2->DIER 		|= 0x0001; // Enable timer 2 interrupts


	TIM2->CCER 		&= ~TIM_CCER_CC3P; // Clear CCER register
	TIM2->CCER 		|= 0x00000001 << 8; // Enable OC3 output
	TIM2->CCMR2 	&= ~TIM_CCMR2_OC3M; // Clear CCMR2 register
	TIM2->CCMR2 	&= ~TIM_CCMR2_CC3S;
	TIM2->CCMR2 	|= TIM_OCMode_PWM1; // Set output mode to PWM1
	TIM2->CCMR2 	&= ~TIM_CCMR2_OC3PE;
	TIM2->CCMR2 	|= TIM_OCPreload_Enable;
}

void timer15(){

	RCC->AHBENR |= RCC_AHBPeriph_GPIOA; // Enable clock for GPIO Port A
	RCC->AHBENR |= RCC_AHBPeriph_GPIOB; // Enable clock for GPIO Port B
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC; // Enable clock for GPIO Port C

	RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;
	TIM15 ->CR1 = 0x001; //Primary Config
	TIM15 ->ARR = 908; //Auto-reload
	TIM15 ->PSC = 999; //Prescaler
	TIM15->DIER |= 0x0001; // Enable timer 15 interrupts
}

struct tick{
 	volatile uint32_t hs;
 	volatile uint32_t sec;
 	volatile uint32_t min;
 	volatile uint32_t hour;
};

struct tick ticks1;

void TIM1_BRK_TIM15_IRQHandler(void){ //Timer
	ticks1.hs++;
	if( ticks1.hs > 25){
		ticks1.sec++;
		ticks1.hs = 0;
	}
	if(ticks1.sec > 7){
		ticks1.min ++;
		ticks1.sec = 0;
	}
	if(ticks1.min > 60){
		ticks1.hour ++;
		ticks1.min = 0;
	}
	TIM15->SR &= ~0x0001; // Clear interrupt bit
}


 uint16_t getNoteFrequency(const char *note) {
   const char* letterNotes[] = {
		   "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
		   "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
		   "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
		   "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5",
		   "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6",
		   "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7"
    };

    uint16_t notes[] = {
    		65, 69, 78, 82, 87, 92, 98, 104, 110, 117, 123, 131, 139, 147,
			156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311,
			330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659,
			698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319,
			1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489,
			2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
    };
    	for (uint8_t i = 0; i < 64; i++){
    		if(strcmp(note, letterNotes[i]) == 0){
    			return notes[i];
    		}
    	}
    	return 0;
 };


void setFreq(uint16_t freq) {
uint32_t reload = 64e6 / freq / (999 + 1) - 1;
TIM2->ARR = reload; // Set auto reload value
TIM2->CCR3 = reload/2; // Set compare register
TIM2->EGR |= 0x01;
}

void song(){
	/*TIM1_BRK_TIM15_IRQHandler();
	const char* arr[] = {"G4","G4","C4","F4"};
	for (uint8_t i = 0; times.BEAT<4; i++ ){
		setFreq(getNoteFrequency(arr[i]));
		}
	};

int main(void){

	// Setup communication with the PC
	uart_init(9600);
	timer15();
	timer2();
	NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 1);
	NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt
	TIM1_BRK_TIM15_IRQHandler();

	clrscr();
	while (1){
		gotoxy(0,0);
		printf("H: %d, Min: %d, sec: %d, hs: %d", ticks1.hour, ticks1.min, ticks1.sec ,ticks1.hs);
		if 		(ticks1.sec < 0){
				setFreq(getNoteFrequency("C4"));
			}
		else if (ticks1.sec < 1){
				setFreq(getNoteFrequency("D4"));
			}
		else if (ticks1.sec < 2){
				setFreq(getNoteFrequency("E4"));
				}
		else if (ticks1.sec < 3){
				setFreq(getNoteFrequency("F4"));
					}
		else if (ticks1.sec < 4){
				setFreq(getNoteFrequency("G4"));
			}
		else if (ticks1.sec < 5){
				setFreq(getNoteFrequency("A5"));
				}
		else if (ticks1.sec < 6){
				setFreq(getNoteFrequency("B5"));
					}
		else if (ticks1.sec < 7){
				setFreq(getNoteFrequency("C5"));
//
	}
}



*/
