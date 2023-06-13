#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#define PINUP A2
#define PINDOWN A0
#define PINSTOP A1


/* Makes the Arduino wait 8 seconds */
void wait8s(){
  noInterrupts ();
   // disable ADC
  ADCSRA = 0;
  // clear various "reset" flags
  MCUSR = 0;    
  // allow changes, disable reset
  WDTCSR = bit (WDCE) | bit (WDE);
  // set interrupt mode and an interval
  WDTCSR = bit (WDIE) | bit (WDP3) | bit (WDP0);  // set WDIE, and 8 seconds delay
  wdt_reset();

  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  // timed sequence follows
  sleep_enable();

  // turn off brown-out enable in software
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS);
  interrupts ();             // guarantees next instruction executed
  sleep_mode ();

  // cancel sleep as a precaution
  sleep_disable();
}

/* Makes the Arduino wait 1 second */
void wait1s(){
  noInterrupts ();
  // disable ADC
  ADCSRA = 0;
  sleep_enable();
  // clear various "reset" flags
  MCUSR = 0;
  // allow changes, disable reset
  WDTCSR = bit (WDCE) | bit (WDE);
  // set interrupt mode and an interval
  WDTCSR = bit (WDIE) | bit (WDP2) | bit (WDP1);    // set WDIE, and 8 seconds delay
  wdt_reset();

  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  sleep_enable();
 
  // turn off brown-out enable in software
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS);
  interrupts ();             // guarantees next instruction executed
  sleep_mode ();

  // cancel sleep as a precaution
  sleep_disable();
}

void waitT(unsigned int T = 8){
  int huitNum = (int) T/8;
  byte resteS = T-huitNum*8;
  for (int i = 0; i < huitNum; i++)
    wait8s();
  for (int i = 0; i < resteS; i++)
    wait1s();
}


const char ecartCoucher [] PROGMEM = {-1,0,-1,-1,-1,-3,-1,-1,-2,-1,-2,-2,-2,-1,-2,-2,-2,-2,-3,-1,-2,-3,-2,-2,-3,-2,-3,-2,-3,-3,-3,-2,-2,-4,-2,-3,-3,-3,-2,-4,-2,-4,-2,-3,-3,-3,-4,-2,-4,-2,-3,-4,-2,-4,-3,-3,-3,-3,-4,-3,-2,-4,-3,-4,-3,-3,-3,-3,-3,-4,-3,-3,-4,-3,-2,-4,-3,-3,-3,-4,-3,-3,-4,-3,-2,-4,-3,-3,-3,-4,-3,-3,-4,-2,-3,-4,-3,-3,-3,-3,-3,-3,-4,-3,-2,-3,-4,-2,-3,-4,-2,-3,-3,-3,-3,-3,-2,-4,-2,-3,-3,-3,-2,-2,-4,-2,-3,-2,-2,-3,-3,-2,-2,-2,-3,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-2,-1,-2,-2,-1,-2,-1,-2,0,-1,-2,-1,0,-1,-1,-1,-1,0,-1,0,0,-1,1,0,-1,0,1,0,0,1,0,1,0,1,0,1,2,0,1,2,0,1,2,1,2,2,0,2,2,1,2,2,2,2,2,1,2,2,4,2,2,2,2,2,2,3,3,2,3,2,2,4,2,3,2,3,3,3,2,3,3,3,3,3,2,3,4,2,3,3,4,3,2,3,3,4,3,2,3,3,4,3,3,3,4,3,2,3,3,4,3,3,3,3,4,3,3,3,4,3,2,3,4,3,3,3,4,3,3,3,4,2,3,3,4,3,3,3,3,3,4,3,2,4,3,2,4,3,2,4,3,2,4,2,4,2,3,3,3,3,3,2,3,3,3,2,2,4,2,3,2,2,3,2,2,3,2,2,2,2,2,2,2,2,1,2,1,3,1,2,1,1,1,1,2,1,1,1,0,1,0,1,1,0,0,0,1,-1,1,-1,1,-1,-1,1,-1,-1,-1,0,-2};
const char ecartLever [] PROGMEM = {1,0,1,1,1,2,2,1,1,2,1,3,1,2,1,3,1,2,3,2,1,3,2,2,3,2,3,2,3,2,4,2,2,3,3,3,2,4,2,3,3,3,3,2,4,2,4,3,3,3,2,4,3,3,3,3,4,2,4,3,3,3,3,4,3,3,4,2,3,4,3,3,4,3,3,3,3,3,3,4,3,3,4,3,3,3,3,3,3,4,3,3,4,3,2,4,3,3,3,4,2,3,4,3,3,2,4,3,2,4,3,2,3,4,2,3,3,3,3,2,4,2,3,2,3,3,2,3,2,3,2,3,2,2,3,2,2,2,2,2,2,2,2,2,3,0,2,2,1,2,2,1,2,1,1,1,1,2,0,1,0,2,1,0,1,0,0,1,0,-1,1,0,0,-1,0,0,-1,0,-1,0,-1,0,-2,-1,0,-2,-1,0,-2,-1,-2,-2,-1,-1,-2,-1,-2,-2,-2,-2,-2,-1,-2,-2,-3,-3,-2,-2,-2,-2,-2,-3,-2,-3,-3,-2,-2,-3,-3,-3,-2,-3,-2,-4,-2,-3,-3,-2,-4,-3,-2,-3,-3,-3,-3,-3,-3,-4,-2,-3,-3,-3,-4,-2,-3,-3,-3,-4,-3,-3,-3,-4,-2,-3,-3,-3,-4,-3,-3,-3,-3,-4,-3,-3,-3,-4,-2,-3,-3,-4,-3,-3,-3,-4,-3,-3,-3,-3,-3,-3,-3,-4,-3,-2,-4,-3,-3,-4,-2,-3,-4,-2,-3,-4,-2,-3,-4,-2,-3,-3,-3,-3,-3,-2,-4,-2,-4,-2,-2,-4,-2,-3,-2,-3,-3,-2,-3,-2,-2,-3,-2,-2,-3,-2,-1,-3,-2,-2,-1,-3,-1,-2,-1,-2,-2,-2,-1,-1,-1,-1,-2,-1,-1,-1,-1,0,0,-1,-1,-1,1,-1,0,0,0,0,0,0,1,0,0,1,1,0,2};

long dureeCoucher;
long dureeLever;
int jrActuel;
int d_tpsJusquaMatin;
int firstDay;
int stateOfDay; // 0: baissé - nuit, 1: ouvert - matin, 2: semi-ouvert : 12h; 3: laisse légèrement passer la lumière : 17h;

/*
 * Une ouverture à moitié : 8000ms, une ouverture complete : 20000ms
 */

void blinkLed(){
  for (int i=0; i<5; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(5);
    digitalWrite(LED_BUILTIN, LOW);
    delay(5);
  }
}

void monter(int tempsMs = 8000){
  pinMode(PINDOWN, OUTPUT);
  pinMode(PINSTOP, OUTPUT);
  pinMode(PINUP, OUTPUT);
  blinkLed();
  digitalWrite(PINUP, HIGH);
  delay(1000);
  digitalWrite(PINUP, LOW);
  delay(tempsMs-1000);
  digitalWrite(PINSTOP, HIGH);
  delay(1000);
  digitalWrite(PINSTOP, LOW);
  blinkLed();
  pinMode(PINDOWN, INPUT);
  pinMode(PINSTOP, INPUT);
  pinMode(PINUP, INPUT);
}

void descendre(int tempsMs = 8000){
  pinMode(PINDOWN, OUTPUT);
  pinMode(PINSTOP, OUTPUT);
  pinMode(PINUP, OUTPUT);
  blinkLed();
  digitalWrite(PINDOWN, HIGH);
  delay(1000);
  digitalWrite(PINDOWN, LOW);
  delay(tempsMs-1000);
  digitalWrite(PINSTOP, HIGH);
  delay(1000);
  digitalWrite(PINSTOP, LOW);
  blinkLed();
  pinMode(PINDOWN, INPUT);
  pinMode(PINSTOP, INPUT);
  pinMode(PINUP, INPUT);
}

// watchdog interrupt
ISR (WDT_vect) 
{
   wdt_disable();  // disable watchdog
}  // end of WDT_vect

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  dureeCoucher = 54012;
  dureeLever = 28848;
  jrActuel = 53;
  stateOfDay = 0;
  d_tpsJusquaMatin = 3600*9;
  firstDay = 1;
}


void loop() {
  // put your main code here, to run repeatedly:
  //waitT(dureeCoucher);
  if (firstDay){
      waitT(d_tpsJusquaMatin);
      firstDay = 0;
  }
  switch(stateOfDay){
    case 0:
      monter(20000); //7h30
      stateOfDay+=1;
      waitT(3600*5);
      break;
    case 1:
      descendre(5000); //12h30
      stateOfDay+=1;
      waitT(3600*3);
      break;
    case 2:
      descendre(7000); //17h30
      stateOfDay+=1;
      waitT(3600*3+60*30);
      break;
    case 3:
      descendre(20000); //21h
      stateOfDay = 0;
      waitT(3600*10+60*30);
      break;
    default:
      stateOfDay = 0;
  }
  dureeCoucher += pgm_read_byte_near(ecartCoucher + jrActuel)*60;
  waitT(dureeLever);
  dureeLever += pgm_read_byte_near(ecartLever + jrActuel)*60;
  jrActuel++;
}
