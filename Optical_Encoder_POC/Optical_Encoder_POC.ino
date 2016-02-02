
  double optical_angle = 0;
  int Channel_A = 0;
  int Channel_B = 0;
  int count_encoder = 0;
  double OE_direction;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Channel_A = digitalRead(5);
  Channel_B = digitalRead(4);

  if (Channel_A == HIGH) {
    count_encoder = count_encoder + 1;
    if (Channel_B == LOW)
      OE_direction = 1;
    else if (Channel_B == HIGH)
      OE_direction = -1;
    while(Channel_A == HIGH){
       //ISR DOES STUFF
      }
    if (Channel_B == LOW)
      OE_direction = -1;
    else if (Channel_B == HIGH)
      OE_direction = 1;
  }
  if (OE_direction == 1)
     optical_angle = optical_angle + 3.6;
  else if (OE_direction == -1);
    optical_angle = optical_angle - 3.6;

  if (optical_angle > 360)
    optical_angle = optical_angle - 360;
  else if (optical_angle < -360)
    optical_angle = optical_angle + 360;
  if (OE_direction = 1)
    Serial.print("Moving Forwards, angle = :  ");
  else if (OE_direction = -1)
    Serial.print("Moving Backwards, angle = :  ");
    
   Serial.print(optical_angle);
   Serial.print('\n');
}
