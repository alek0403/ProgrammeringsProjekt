#include "stm32f30x_conf.h" // STM32 config

void timersetup(){
    RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 15;

    // Enable clock for TIM15
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);

    TIM15->CR1 = 0x001; // Configure timer 15
    TIM15->ARR = 900; // Set reload value
    TIM15->PSC = 999; // Set prescale value
    TIM15->DIER |= 0x0001; // Enable timer 15 interrupts
    NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0); // Set interrupt priority
    NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn); // Enable interrupt
}

// laver struktur som har tid og et flag.
struct tick {
    volatile int32_t h;
    volatile int32_t m;
    volatile int32_t s;
    volatile int32_t hs;
    volatile int8_t flag;
};

struct tick ticks; // Laver instans af tick.

void TIM1_BRK_TIM15_IRQHandler(void) {
    ticks.hs++;
    if (ticks.hs > 100) {
        ticks.s++;
        ticks.hs = 0;
        ticks.flag = 1; // efter 1 sekund sættes flaget højt. (skal sættes igen sættes til 0 af update funktion).
    }
    if (ticks.s > 60) {
        ticks.m++;
        ticks.s = 0;
    }
    if (ticks.m > 60) {
        ticks.h++;
        ticks.m = 0;
    }

    TIM15->SR &= ~0x0001; // Clear interrupt bit, dvs. loop i main fortsætter.
}

