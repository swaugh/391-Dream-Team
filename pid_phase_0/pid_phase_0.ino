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
   double OE_Setpoint, OE_PID_Input, OE_PID_Output;
   PID OE_PID(&OE_PID_Input, &OE_PID_Output, &OE_Setpoint,0.5,0,0, DIRECT); // in, out, Kp, Ki, Kd, direction

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RE_lag_pin, INPUT);
  pinMode(OE_lag_pin, INPUT);
  attachInterrupt(0, OE_ISR, RISING); //optical encoder isr, will trigger on rising edge of channel A
  attachInterrupt(1, RE_ISR, RISING); //rotary encoder isr, will trigger on rising edge of channel A
 
  //initalize Roatry PID
  OE_PID_Input = OE_angle; //input to RE PID controller is the actal measured angle
  OE_Setpoint = 54; //for now we set a test setpoint to 90 degrees
  OE_PID.SetMode(AUTOMATIC); //turn on the PID to automatic mode
  OE_PID.SetOutputLimits(64, 127); //cap the output of the OE_PID to 64(motor off) to 127 (max speed)
}

void loop() {
  // put your main code here, to run repeatedly:
   OE_PID_Input = OE_angle; //input to RE PID controller is the actal measured angle
   OE_PID.Compute();

  
  //Serial.write((int) OE_PID_Output);
  Serial.print((int) OE_PID_Output);
  Serial.print('\n');
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
       Serial.print(OE_PID_Output);
   Serial.print('\n');
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


