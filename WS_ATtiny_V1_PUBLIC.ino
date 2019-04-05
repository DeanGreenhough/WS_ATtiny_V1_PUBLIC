/*  Author Dean Anthony Greenhough
 *  ATtiny 13a used as EEPROM counter for ultra low power mode 
 *  In conjunction with TPL5110, DonePin and Logic for NPN MOSFET
 */ 


#include <EEPROM.h>

//SLEEP ATtiny
//#include <avr/sleep.h>
// ATtiny macros
//#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
//#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC

//TPL5110
#define DONEPIN             0           //PIN 0 TPL5110 SWITCH OFF PIN
#define GREEN_LEDPIN        1           //PIN 1
//#define YELLOW_LEDPIN     2           //PIN 2 
#define START_POWER_PIN     3           //PIN 3 NPN GATE  HIGH

//VARIABLES
int TPL5110_Counter       = 0;          //TPL COUNTER EVERY 2 HOURS
int EEaddress             = 0;          //EEPROM START ADDRESS
int loopTime              = 0;          //LOOP TIMER
unsigned long startMillis;              //LOOP TIMER
unsigned long currentMillis;            //LOOP TIMER

void setup() {

      //ATtiny SLEEP MODE                      
      //adc_disable(); // ADC uses ~320uA
      //set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        startMillis = millis();           //START LOOPTIME 
        pinMode(START_POWER_PIN, OUTPUT);
        digitalWrite(START_POWER_PIN, LOW);
        pinMode(GREEN_LEDPIN, OUTPUT);
        digitalWrite(GREEN_LEDPIN, LOW);      
        pinMode(DONEPIN, OUTPUT);
        digitalWrite(DONEPIN, LOW);  
     
             
      //INIT EEPROM
        EEPROM.begin(); 
      
      
      //TPL5110 COUNTER
        TPL5110_Counter = (EEPROM.get(EEaddress, TPL5110_Counter));
      
        if      (TPL5110_Counter >= 12)
                {
                 digitalWrite(START_POWER_PIN, HIGH);     //NPN GATE HIGH = ON 
                 delay(100);
                 TPL5110_Counter = 0;                                  
                 EEPROM.put(EEaddress,TPL5110_Counter+1);                                 
                 digitalWrite(DONEPIN, HIGH);              //SEND DONE TO TPL5110 TO SHUT DOWN                
                 delay(10);
                
              }
          
       else   {
                 
                EEPROM.put(EEaddress,TPL5110_Counter+1);                                               
                digitalWrite(GREEN_LEDPIN, HIGH);
                delay(10); 
                digitalWrite(GREEN_LEDPIN, LOW);           
                digitalWrite(DONEPIN, HIGH);                           //SEND DONE TO TPL5110 TO SHUT DOWN                
                delay(10);
               
              }                                    
         
                  
                    
              
               
               
      }

void loop() {
  

            }
