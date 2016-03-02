
  volatile double RE_angle; //Rotary encoder angle
  volatile int RE_dir; //rotary encoder direction
  const int RE_lead_pin = 3;
  const int RE_lag_pin = 13; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RE_lag_pin, INPUT);
  attachInterrupt(1, RE_ISR, RISING); //rotary encoder isr, will trigger on rising edge of channel A
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
}

 void RE_ISR (){
  
      if (digitalRead(RE_lag_pin) == HIGH){
      RE_dir = -1;
      RE_angle = RE_angle - 15;
      if (RE_angle <= -360)
          RE_angle = RE_angle + 360;
          
       Serial.print("Moving Backwards, angle = :  ");
       Serial.print(RE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
    }

    else if (digitalRead(RE_lag_pin) == LOW){
      RE_dir = 1;
      RE_angle = RE_angle + 15;
       if (RE_angle >= 360)
         RE_angle = RE_angle - 360;

       Serial.print("Moving Forwards, angle = :  ");
       Serial.print(RE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
       
    }
 }


