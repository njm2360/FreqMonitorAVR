#include <avr/io.h>
#include <avr/interrupt.h>

#define SYSCLK 16000000

ISR(TIMER1_CAPT_vect);
ISR(TIMER2_COMPA_vect);
int main(void);

volatile char secflag = 0;
volatile uint16_t valuecount;
volatile uint32_t valuesum;
volatile uint16_t cycletime;
volatile uint16_t lastvalue;
volatile uint16_t nowvalue;
volatile unsigned int TCNT2H;
uint16_t freq;

ISR(TIMER1_CAPT_vect)
{
    TIFR1 |= (1 << ICF1);
    nowvalue = ICR1;
    cycletime = nowvalue - lastvalue;
    lastvalue = nowvalue;
    valuesum += cycletime;
    valuecount++;
}

ISR(TIMER2_COMPA_vect)
{
    TCNT2H++;
    if (TCNT2H >= 1000)
    {
        TCNT2H = 0;
        secflag = 1;
    }
}

int main(void)
{
    cli();
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT1 = 0;
    TCCR1B |= (1 << CS11);   
    TCCR1B |= (1 << ICNC1);  
    TIMSK1 |= (1 << ICIE1);
    TCCR2A |= (1 << WGM21); 
    TCCR2B |= (1 << CS22); 
    TCCR2B |= (1 << CS20); 
    OCR2A = 125 - 1; 
    TIMSK2 |= (1 << OCIE2A);
    sei();
    while (1)
    {
        if (secflag) 
        {
            secflag = 0;
            uint32_t valuesumtemp;
            uint16_t valuecounttemp;
            cli();
            valuecounttemp = valuecount;
            valuesumtemp = valuesum;
            valuecount = 0;
            valuesum = 0;
            sei();
            freq = (double)SYSCLK /8 / (double)((float)valuesumtemp / (float)valuecounttemp) * 1000.;
        }
    }
}