  #include <PID_v1.h>
 
  
  volatile double RE_angle; //rotary encoder angle
  volatile int RE_dir; //rotary encoder direction
  const int RE_lead_pin = 3;
  const int RE_lag_pin = 13;

  volatile double OE_angle; //optical encoder angle
  volatile int OE_dir; //optical encoder direction
  const int OE_lead_pin = 2;
  const int OE_lag_pin = 12;

  //RE PID variables
   double RE_Setpoint, RE_PID_Input, RE_PID_Output;
   PID RE_PID(&RE_PID_Input, &RE_PID_Output, &RE_Setpoint,2,5,1, DIRECT);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RE_lag_pin, INPUT);
  pinMode(OE_lag_pin, INPUT);
  attachInterrupt(0, OE_ISR, RISING); //optical encoder isr, will trigger on rising edge of channel A
  attachInterrupt(1, RE_ISR, RISING); //rotary encoder isr, will trigger on rising edge of channel A
 
  //initalize Roatry PID
  RE_PID_Input = RE_angle; //input to RE PID controller is the actal measured angle
  RE_Setpoint = 54; //for now we set a test setpoint to 90 degrees
  RE_PID.SetMode(AUTOMATIC); //turn on the PID to automatic mode
}

void loop() {
  // put your main code here, to run repeatedly:
   RE_PID_Input = RE_angle; //input to RE PID controller is the actal measured angle
   RE_PID.Compute();
  // Serial.print(RE_PID_Output);
  
  //Serial.write(30);
  delayMicroseconds(50);
  //Serial.write(200);
  delay(1);
}

 void OE_ISR (){
  
      if (digitalRead(OE_lag_pin) == HIGH){
      OE_dir = -1;
      OE_angle = OE_angle - 3.6;
      if (OE_angle <= -360)
          OE_angle = OE_angle + 360;
          
       Serial.print("optical Moving Backwards, angle = :  ");
       Serial.print(OE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
    }

    else if (digitalRead(OE_lag_pin) == LOW){
      OE_dir = 1;
      OE_angle = OE_angle + 3.6;
       if (OE_angle >= 360)
         OE_angle = OE_angle - 360;

       Serial.print("optical Moving Forwards, angle = :  ");
       Serial.print(OE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
       
    }
 }

 void RE_ISR (){
  
      if (digitalRead(RE_lag_pin) == HIGH){
      RE_dir = -1;
      RE_angle = RE_angle - 15;
      if (RE_angle <= -360)
          RE_angle = RE_angle + 360;
          
       Serial.print("rotary Moving Backwards, angle = :  ");
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

       Serial.print("rotary Moving Forwards, angle = :  ");
       Serial.print(RE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
       
    }
 }


