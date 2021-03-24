byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
int receiver_input_channel_1, receiver_input_channel_2,receiver_input_channel_3,receiver_input_channel_4;
unsigned long timer_1, timer_2, timer_3, timer_4;
int PWM_Pin = 3;

void setup() {
  // put your setup code here, to run once:
  //Arduino inputs declarations
  
  pinMode(PWM_Pin, OUTPUT);
  PCICR |= (1 << PCIE0); //ustawia PCIE0 aby załączyć PCMSK0 skan
  PCMSK0 |= (1 << PCINT0); // wejście cyfrowe 8, uruchamie przerwanie
  PCMSK0 |= (1 << PCINT1); // wejście cyfrowe 9, uruchamie przerwanie
  PCMSK0 |= (1 << PCINT2); // wejście cyfrowe 10, uruchamie przerwanie
  PCMSK0 |= (1 << PCINT3); // wejście cyfrowe 11, uruchamie przerwanie
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(250);
  print_signals();
  
}
//Funkcje przerwań
ISR(PCINT0_vect){
  //Channel 1=====================================
  if(last_channel_1 == 0 && PINB & B00000001 ){
    last_channel_1 = 1;
    timer_1 = micros();
  }
  else if(last_channel_1 == 1 && !(PINB & B00000001)){
    last_channel_1 = 0;
    receiver_input_channel_1 = micros() - timer_1;
    if (receiver_input_channel_1 < 1000)
        receiver_input_channel_1 = 1000;
  }
  //Channel 2=====================================
  if(last_channel_2 == 0 && PINB & B00000010 ){
    last_channel_2 = 1;
    timer_2 = micros();
  }
  else if (last_channel_2 == 1 && !(PINB & B00000010)){
    last_channel_2 = 0;
    receiver_input_channel_2 = micros() - timer_2;
    if (receiver_input_channel_2 < 1000)
        receiver_input_channel_2 = 1000;
  }
  //Channel 3=====================================
  if(last_channel_3 == 0 && PINB & B00000100 ){
    last_channel_3 = 1;
    timer_3 = micros();
  }
  else if (last_channel_3 == 1 && !(PINB & B00000100)){
    last_channel_3 = 0;
    receiver_input_channel_3 = micros() - timer_3;
    if (receiver_input_channel_3 < 1000)
        receiver_input_channel_3 = 1000;
  }
  //Channel 4=====================================
  if(last_channel_4 == 0 && PINB & B00001000 ){
    last_channel_4 = 1;
    timer_4 = micros();
  }
  else if (last_channel_4 == 1 && !(PINB & B00001000)){
    last_channel_4 = 0;
    receiver_input_channel_4 = micros() - timer_4 + 8;
    if (receiver_input_channel_4 < 1000)
        receiver_input_channel_4 = 1000;
  }

}

void print_signals(){
  Serial.print("Roll:");
  if(receiver_input_channel_1 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_1 - 1520 > 0)Serial.print(">>>");
  else Serial.print("+");
  Serial.print(receiver_input_channel_1);
 
  Serial.print("Nick:");
  if(receiver_input_channel_2 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_2 - 1520 > 0)Serial.print(">>>");
  else Serial.print("+");
  Serial.print(receiver_input_channel_2);

  Serial.print("Gas:");
  if(receiver_input_channel_3 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_3 - 1520 > 0)Serial.print(">>>");
  else Serial.print("+");
  Serial.print(receiver_input_channel_3);

  Serial.print("Yaw:");
  if(receiver_input_channel_4 - 1480 < 0)Serial.print("<<<");
  else if(receiver_input_channel_4 - 1520 > 0)Serial.print(">>>");
  else Serial.print("+");
  Serial.println(receiver_input_channel_4);
  analogWrite(PWM_Pin,45);

}
