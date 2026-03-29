#include <msp430.h>
#define SW1 BIT3
#define LED1 BIT6
#define LED2 BIT0
void main(void) {
  WDTCTL = WDTPW | WDTHOLD;
  P1DIR &= ~SW1;
  P1DIR |= LED1;
  P1DIR |= LED2;
  P1REN |= SW1;
  P1OUT |= SW1;
  P1IES |= SW1;
  P1IE |= SW1;
  P1OUT |= LED2;
  __bis_SR_register(GIE);
  while (1)
    ;
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void) {
  volatile unsigned long i;

  if (P1IFG & SW1) {
    for (i = 0; i < 10000; i++);
    if(P1IES & SW1){
    P1OUT ^= LED1;
    P1OUT &= ~LED2;
  } 
  else
   {

    P1OUT &= ~LED1;
    P1OUT |= LED2;
  }
  P1IES ^= SW1;
    P1IFG &= ~SW1;
}
}