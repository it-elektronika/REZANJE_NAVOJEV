/// IT ELEKTRONIKA /////
// STROJ ZA NAVIJANJE //
///////// 2018 /////////

#include <EEPROM.h>

#define motor_navijanje 6
#define motor_odvijanje 5
#define podajalni_cilinder_naprej 13 
#define podajalni_cilinder_nazaj 11
#define gripper 9
#define omejilec_hoda 10  
#define frekvencnik_izhod 3
#define motor_mazanje 7

#define start A1
#define reset A0
#define razbremenitev_cilindra_naprej 2
#define razbremenitev_cilindra_nazaj A11
#define podajalni_cilinder_koncni_polozaj A8
#define obracanje_motorja A6
#define gripper_odprt A5
#define gripper_zaprt A4
#define omejilec_hoda_na_poziciji A3
#define omejilec_hoda_umaknjen A2

int state;
int count;

int t1;
int st1;
int et1;

int t2;
int st2;
int et2;


int state1;
int state2;
int state3;
int state4;
int state5;
int state6;
int state7;
int state8;
int state9;
int state10;
int lastState1;
int lastState2;
int lastState3;
int lastState4;
int lastState5;
int lastState6;
int lastState7;
int lastState8;
int lastState9;
int lastState10;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long lastDebounceTime4 = 0;
unsigned long lastDebounceTime5 = 0;
unsigned long lastDebounceTime6 = 0;
unsigned long lastDebounceTime7 = 0;
unsigned long lastDebounceTime8 = 0;
unsigned long lastDebounceTime9 = 0;
unsigned long lastDebounceTime10 = 0;

unsigned long debounceDelay;

void setup() 
{
  pinMode(motor_navijanje, OUTPUT);
  pinMode(motor_odvijanje, OUTPUT);
  pinMode(podajalni_cilinder_naprej, OUTPUT);
  pinMode(podajalni_cilinder_nazaj, OUTPUT);
  pinMode(gripper, OUTPUT);
  pinMode(omejilec_hoda, OUTPUT);
  pinMode(frekvencnik_izhod, OUTPUT);
  pinMode(motor_mazanje, OUTPUT);

  pinMode(start, INPUT);
  pinMode(reset, INPUT);
  pinMode(razbremenitev_cilindra_naprej, INPUT);
  pinMode(razbremenitev_cilindra_nazaj, INPUT);
  pinMode(podajalni_cilinder_koncni_polozaj, INPUT);
  pinMode(obracanje_motorja, INPUT);
  pinMode(gripper_odprt, INPUT);
  pinMode(gripper_zaprt, INPUT);
  pinMode(omejilec_hoda_na_poziciji, INPUT);
  pinMode(omejilec_hoda_umaknjen, INPUT);
  count = EEPROM.read(0);
  count = 0;
  state = 12;  
  debounceDelay = 20;

  t1 = 150;
  t2 = 300;
  delay(100);
}

void loop() 
{
  Serial.print("STATE-main: ");//printing name
  Serial.println(state);//printing RED color frequency
  //Serial.print("millis ");
  //Serial.println(millis());
  //Serial.print("lastdebouncetime8: ");//printing name
  //Serial.println(lastDebounceTime8);//printing RED color frequency
  int reading1 = digitalRead(start);
  int reading2 = digitalRead(reset);
  int reading3 = digitalRead(razbremenitev_cilindra_naprej);
  int reading4 = digitalRead(razbremenitev_cilindra_nazaj);
  int reading5 = digitalRead(podajalni_cilinder_koncni_polozaj);
  int reading6 = digitalRead(obracanje_motorja);
  int reading7 = digitalRead(gripper_odprt);
  int reading8 = digitalRead(gripper_zaprt);
  int reading9 = digitalRead(omejilec_hoda_na_poziciji);
  int reading10 = digitalRead(omejilec_hoda_umaknjen);
  
  if(reading1 != lastState1)
  {
    lastDebounceTime1 = millis();
  } 
  if(reading2 != lastState2)
  {
    lastDebounceTime2 = millis();
  }
  if(reading3 != lastState3)
  {
    lastDebounceTime3 = millis();
  }
  if(reading4 != lastState4)
  {
    lastDebounceTime4 = millis();
  } 
  if(reading5 != lastState5)
  {
    lastDebounceTime5 = millis();
  }
  if(reading6 != lastState6)
  {
    lastDebounceTime6 = millis();
  }
  if(reading7 != lastState7)
  {
    lastDebounceTime7 = millis();
  }
  if(reading8 != lastState8)
  {
    lastDebounceTime8 = millis();
  }
  if(reading9 != lastState9)
  {
    lastDebounceTime9 = millis();
  }
  if(reading10 != lastState10)
  {
    lastDebounceTime10 = millis();
  }
  
 
  if((millis() - lastDebounceTime2) > debounceDelay && state != 12 && state != 13 && state != 14 && state != 0) // napaka 
  {
    if(reading2 != state2)
    {
      state2 = reading2;
      if(state2 == LOW)
      {
        state = 12;
      }
    }
  }
  
  if(state == 0)
  {
    if((millis() - lastDebounceTime1) > debounceDelay)
    {
      if(reading1 != state1)
      {
        state1 = reading1;
        if(state1 == HIGH)
        {
          digitalWrite(motor_navijanje, HIGH); // vklop motorja
            // vklop motorja za mazanje
          count++;
          EEPROM.update(0, count);
          state = 1;
        }
      }
    }
  }
    
  else if(state == 1)
  {
    digitalWrite(gripper, HIGH); // zapiranje gripperja
    state = 2; 
  }
  
  else if(state == 2)
  {
    if((millis() - lastDebounceTime8) > debounceDelay)
    {
      if(reading8 != state8)
      {
        state8 = reading8;
        if(state8 == HIGH)
        {
          digitalWrite(omejilec_hoda, LOW);  //neomejevanje hoda
          state = 3;
        }
      }  
    }
  }
  else if(state == 3)
  {
    if((millis() - lastDebounceTime10) > debounceDelay)
    {
      if(reading10 != state10)
      {
        state10 = reading10;
        if(state10 == HIGH)
        {   
          digitalWrite(podajalni_cilinder_nazaj, LOW);
          digitalWrite(podajalni_cilinder_naprej, HIGH);
          // pomik cilindra naprej
          st2 = millis();
          
          state = 4;
        }
      }
    }
  }
  if(state == 4)
  {
    et2 = millis();
    if((et2 - st2) > t2)
    {
      digitalWrite(motor_mazanje, LOW);
      state = 5;  
    }
  }
  
  else if(state == 5)
  {
    if((millis() - lastDebounceTime3) > debounceDelay)
    {
      if(reading3 != state3)
      { 
        state3 = reading3;
        if(state3 == HIGH)
        {  
          digitalWrite(podajalni_cilinder_naprej, LOW);  //izklop cilindra naprej
          digitalWrite(podajalni_cilinder_nazaj, LOW);
          state = 6;
        }
      }
    }
  }

  
  else if(state == 6)
  {
    if((millis() - lastDebounceTime6) > debounceDelay)
    {
      if(reading6 != state6)  
      {
        state6 = reading6;  
        if(state6 == HIGH)
        {
          digitalWrite(motor_navijanje, LOW);        // obracanje smeri motorja
          digitalWrite(motor_odvijanje, HIGH);
          digitalWrite(frekvencnik_izhod, HIGH);
          digitalWrite(podajalni_cilinder_naprej, LOW);
          digitalWrite(podajalni_cilinder_nazaj, HIGH);
          
          st1 = millis();
          state = 7;   
        }
      }
    }
  }

  if(state == 7)
  {
    et1 = millis();
    if((et1 - st1) > t1)
    {
      digitalWrite(podajalni_cilinder_naprej, LOW);
      digitalWrite(podajalni_cilinder_nazaj, LOW);
      state = 8;    
     }
  }

  
  else if(state == 8)
  {
    if((millis() - lastDebounceTime4) > debounceDelay)
    {
      if(reading4 != state4)
      {  
        state4= reading4;
        if(state4 == HIGH)
        {
          digitalWrite(podajalni_cilinder_nazaj, HIGH);  // pomik cilindra nazaj
          digitalWrite(podajalni_cilinder_naprej, LOW);
          state = 9;
        }
      }
    }
  }
  else if(state == 9)
  {
    if((millis() - lastDebounceTime5) > debounceDelay)
    {
      if(reading5 != state5)  
      {  
        state5 = reading5;
        if(state5 == HIGH)
        {
          digitalWrite(podajalni_cilinder_nazaj, LOW);
          digitalWrite(podajalni_cilinder_naprej, LOW);
          digitalWrite(omejilec_hoda, HIGH);  // izklop motorja && omejevanje hoda 
          digitalWrite(motor_odvijanje, LOW);
          digitalWrite(motor_mazanje, HIGH);  
          digitalWrite(frekvencnik_izhod, LOW);
          digitalWrite(gripper, LOW);
          state = 10;
        }
      }
    }
  }
  
  else if(state == 10)
  {
    if((millis() - lastDebounceTime7) > debounceDelay)
    {
      if(reading7 != state7)
      {
        state7 = reading7;
        if(state7 == HIGH)
        {  
          state = 11;   
        }
      }
    }
  }

  else if(state == 11)
  {
    if((millis() - lastDebounceTime9) > debounceDelay)
    {
      if(reading9 != state9)
      {
        state9 = reading9;
        if(state9 == HIGH)
        {  
          state = 0;   // izhodiscno stanje
        }
      }
    }
  }
   
  
  else if(state == 12)
  {
    digitalWrite(motor_odvijanje, LOW);  //izklop vseh funkcij
    digitalWrite(motor_navijanje, LOW);
    digitalWrite(frekvencnik_izhod, LOW);
    digitalWrite(motor_mazanje, HIGH);
    digitalWrite(gripper, LOW);
    digitalWrite(omejilec_hoda, LOW);
    digitalWrite(podajalni_cilinder_naprej, LOW);
    digitalWrite(podajalni_cilinder_nazaj, HIGH);
    if((millis() - lastDebounceTime5) > debounceDelay)
    {
      if(reading5 != state5)  
      {
        state5 = reading5;  
        if(state5 == HIGH)
        {
          digitalWrite(podajalni_cilinder_nazaj, LOW);
          digitalWrite(podajalni_cilinder_naprej, LOW);
          state = 13;
        }
      }  
    }
  }
  
  else if(state == 13)
  {
    if((millis() - lastDebounceTime2) > debounceDelay)
    {
      if(reading2 != state2)
      {
        state2 = reading2; 
        if(state2 == LOW)
        {
          digitalWrite(omejilec_hoda, HIGH);
          state = 14;
        }
      }
    }  
  }
  else if(state==14)
  {
    if((millis() - lastDebounceTime9) > debounceDelay)
    {
      if(reading9 != state9)
      {  
        state9 = reading9;
        if(state9 == HIGH)
        {
          state = 0;
        }
      }
    }
  }  
  
  lastState1 = reading1;
  lastState2 = reading2;
  lastState3 = reading3;
  lastState4 = reading4;
  lastState5 = reading5;
  lastState6 = reading6;
  lastState7 = reading7;
  lastState8 = reading8;
  lastState9 = reading9;
  lastState10 = reading10;
  
}
