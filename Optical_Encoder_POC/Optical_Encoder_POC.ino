
  double optical_angle;
  int Channel_A;
  int Channel_B;
  int count_encoder;
  double OE_direction;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(5) == HIGH) {
    count_encoder = count_encoder + 1;
    delayMicroseconds(50);
    if (digitalRead(4) == LOW)
      OE_direction = 1;
    else if (digitalRead(4) == HIGH)
      OE_direction = -1;
  while(digitalRead(5) == HIGH){
       //ISR DOES STUFF
      }
    if (OE_direction == 1){
       optical_angle = optical_angle + 3.6;
       if (optical_angle > 360)
          optical_angle = optical_angle - 360;
          
       Serial.print("Moving Forwards, angle = :  ");
       Serial.print(optical_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
    }
    else if (OE_direction == -1){
      optical_angle = optical_angle - 3.6;
      if (optical_angle < -360)
          optical_angle = optical_angle + 360;
          
       Serial.print("Moving Backwards, angle = :  ");
       Serial.print(optical_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
    }
  }
  delayMicroseconds(50);
  
}
