void setup() {
  // put your setup code here, to run once:
  double optical_angle = 0;
  Serial.begin(9600);
  int Channel_A = 0;
  int Channel_B = 0;
  int count_encoder = 0;
  char OE_direction[9];
}

void loop() {
  // put your main code here, to run repeatedly:
  Channel_A = digitalread(5);
  Channel_B = digitalread(4);

  if Channel_A == HIGH{
    count_encoder = count_encoder + 1;
    if Channel_B == LOW
      OE_direction = "forward";
    else if Channel_B == HIGH
      OE_direction = "backward";
    while(Channel_A == HIGH){
       //ISR DOES STUFF
      }
    if Channel_B == LOW
      OE_direction = "backward";
    else if Channel_B == HIGH
      OE_direction = "forward";
  }
  if OE_direction == "forward"
     optical_angle = optical_angle + 3.6;
  else if OE_diection == "backward";
    optical_angle = optical_angle - 3.6;

  if optical_angle > 360
    optical_angle = optical_angle - 360;
  else if optical_angle < -360
    optical_angle = optical_angle + 360;

  print("direction = %s , angle = %d \n", OE_direction, optical_angle);
    
}
