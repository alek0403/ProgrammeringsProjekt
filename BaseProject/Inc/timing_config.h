#ifndef TIMING_CONFIG_H_
#define TIMING_CONFIG_H_

timersetup();
// laver struktur som har tid og et flag.
struct tick {
    volatile int32_t h;
    volatile int32_t m;
    volatile int32_t s;
    volatile int32_t hs;
    volatile int8_t flag;
};




struct tick ticks; // Laver instans af tick.

#endif /* TIMING_CONFIG_H_ */
