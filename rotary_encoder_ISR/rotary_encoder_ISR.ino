
  double RE_angle; //Rotary encoder angle
  int RE_dir; //rotary encoder direction
  const int RE_lead_pin = 5;
  const int RE_lag_pin = 13; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RE_lag_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(RE_lead_pin) == HIGH) {
    if (digitalRead(RE_lag_pin) == LOW)
      RE_dir = 1;
    else if (digitalRead(RE_lag_pin) == HIGH)
      RE_dir = -1;
  while(digitalRead(RE_lead_pin) == HIGH){
       //ISR DOES STUFF
      }
    if (RE_dir == 1){
       RE_angle = RE_angle + 15;
       if (RE_angle > 360)
          RE_angle = RE_angle - 360;
          
       Serial.print("Moving Forwards, angle = :  ");
       Serial.print(RE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
    }
    else if (RE_dir == -1){
      RE_angle = RE_angle - 15;
      if (RE_angle < -360)
          RE_angle = RE_angle + 360;
          
       Serial.print("Moving Backwards, angle = :  ");
       Serial.print(RE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
    }
  }
  delayMicroseconds(125);
  
}
