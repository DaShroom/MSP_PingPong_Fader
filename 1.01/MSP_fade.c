/* This one actually works :-), and is tested :-D. 'Twas 430am and I decided to try out the TI launchpad I bought ages ago, with, as always, LEDs and Ping-Pong Balls. Done to be easy to read, port, and to teach newbs (including me :-D  ), so no timers, interupts, blah, blah blah.
Should be easily portable. and the pins can be changed in the defintions. Theoretically it should work with any, but on my board 1.4 didn't work.
There could be a proper reason, or it could just be a faulty board.

visit dashroom66.org - for blog and bloggy stuff
visit dashroom66.com - for more info, tutorials .etc

Licensed under Creative Commons BY SA */

//#include <msp430x20x2.h>
#include <msp430.h>
#include <signal.h>

#define UP 0x00
#define DOWN 0x01
#define KEEP 0x02
#define RBIT BIT3
#define GBIT BIT2
#define BBIT BIT5

//variables

volatile  int calcall = 0;
int speed = 100;
volatile char red = DOWN;
volatile char blue = KEEP;
volatile char green = UP;
volatile char rbuff = 7;
volatile char gbuff;
volatile char bbuff;
volatile char rhold;
volatile char ghold;
volatile char bhold;
void draw();
void colcalc();
//start of main
void main(void)
{
//set WDT to interval mode
//WDTCTL = WDT_MDLY_0_064;
WDTCTL = WDTPW + WDTHOLD;
//pin setup
P1DIR |= BIT5 + BIT2 + BIT3;
P1OUT |= BIT5 + BIT2 + BIT3;
P1OUT &= 0x00;
//set interrupts
//IE1 |= WDTIE;
//eint();
//turn KEEP CPU
//_BIS_SR(CPUKEEP);



while (1)
{
 colcalc();
 draw();
}



}//end main

//interrupt(WDT_VECTOR) watchdog_timer(void)
//{
//}

void draw (void)
{
 for (char i = 0; i<8; i++)
 {
  if (rbuff >= i + 1)
  {
   P1OUT |= RBIT;
  }
  else
  {
   P1OUT &= ~RBIT;
  }
  if (gbuff >= i + 1)
  {
   P1OUT |= GBIT;
  }
  else
  {
   P1OUT &= ~GBIT;
  }
  if (bbuff >= i + 1)
  {
   P1OUT |= BBIT;
  }
  else
  {
   P1OUT &= ~BBIT;
  }
 }
}

void colcalc (void)
{
 calcall++;
 if (calcall == speed)
 {
  calcall = 0;
  //red
  if (red == UP)
  {
   rbuff++;
   if (rbuff == 7) {red = DOWN;}
  }
  if (red == DOWN)
  {
  rbuff = rbuff - 1;
  if (rbuff == 0) {red = KEEP; rhold = 0;} 
  }
  if (red == KEEP)
  {
  rhold++;
  if (rhold == 7) {red = UP;}
  }
  //green
  if (green == UP)
  {
   gbuff++;
   if (gbuff == 7) {green = DOWN;}
  }
  if (green == DOWN)
  {
  gbuff = gbuff - 1;
  if (gbuff == 0) {green = KEEP; ghold = 0;} 
  }
  if (green == KEEP)
  {
  ghold++;
  if (ghold == 7) {green = UP;}
  }
  //blue
  if (blue == UP)
  {
   bbuff++;
   if (bbuff == 7) {blue = DOWN;}
  }
  if (blue == DOWN)
  {
  bbuff = bbuff - 1;
  if (bbuff == 0) {blue = KEEP; bhold = 0;} 
  }
  if (blue == KEEP)
  {
  bhold++;
  if (bhold == 7) {blue = UP;}
  }
 }
}

