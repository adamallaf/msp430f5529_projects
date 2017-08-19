#include <msp430f5529.h>


volatile unsigned int updown, counter;


int main(){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog

    P1SEL |= BIT2;      // P1.2 PWM output for timerA0.1

    P1DIR = 0;
    P1DIR |= BIT2 | BIT0;
    P1OUT &= ~(BIT0);

    /* Button s2 P1.1 */
    P1REN |= BIT1;      // enable pullup/pulldown resistor
    P1OUT |= BIT1;      // P1.1 is pulled up
    P1IE |= BIT1;       // Interrupt enable for P1.1
    P1IES |= BIT1;      // Interrupt edge enable, IFG set with a high to low transition
    P1IFG &= ~BIT1;     // clear P1.1 interrupt flag

    TA0CCR0 = 0x3e8;    // T = 1ms
    TA0CCR1 = 0x3e7;    // 100% duty cycle
    counter = 0x3e8;
    updown = 0;         // start counting down

    // timerA0 init
    // ID_0 -> /1 divider
    // MC_1 -> up mode, count up to CCR0
    // TASSEL_2 -> SMCLK as timer clock source
    TA0CTL |= TASSEL_2 | ID_0 | MC_1 | TAIE;
    TA0CCTL0 |= CCIE;   // when timer count from CCR0 ot 0x0 an interrupt is generated
    TA0CCTL1 |= OUTMOD_2;  // set/reset mode, set on CCR1 and reset on CCR0

    __bis_SR_register(CPUOFF | GIE); // LPM0 with interrupts enabled

    for(;;);
    return 0;
}

void __attribute__((interrupt(PORT1_VECTOR))) Port1_ISR()
{
    P1OUT ^= BIT0;      // Toggle LED on P1.0 on button press
    P1IFG &= ~BIT1;
}


void __attribute__((interrupt(TIMER0_A0_VECTOR))) Timer0_A0_ISR()
{
    TA0CTL &= ~1;       // clear timer interrupt flag
    if(updown)
        counter++;
    else
        counter--;
    TA0CCR1 = counter;
    if(counter >= TA0CCR0)
        updown = 0;
    if(counter <= 1)
        updown = 1;
}
