  #include <PID_AutoTune_v0.h>
  #include <PID_v1.h>
 
  //Note: RE is now actually a secondary OE
  volatile double RE_angle; //rotary encoder angle
  volatile int RE_dir; //rotary encoder direction
  const int RE_lead_pin = 3;
  const int RE_lag_pin = 13;

  volatile double OE_angle; //optical encoder angle
  volatile int OE_dir; //optical encoder direction
  const int OE_lead_pin = 2;
  const int OE_lag_pin = 12;

  //OE PID variables
   double OE_Setpoint, OE_PID_Input, OE_PID_Output;
   PID OE_PID(&OE_PID_Input, &OE_PID_Output, &OE_Setpoint,1.42,0,1.2, DIRECT); // in, out, Kp, Ki, Kd, direction Best So far (1.15,0.15,0.8)
   
  //OE PID variables
   double RE_Setpoint, RE_PID_Input, RE_PID_Output;
   PID RE_PID(&RE_PID_Input, &RE_PID_Output, &RE_Setpoint,1.1,0.0075,0.85, DIRECT); // in, out, Kp, Ki, Kd, direction Best So far 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RE_lag_pin, INPUT);
  pinMode(OE_lag_pin, INPUT);
  attachInterrupt(0, OE_ISR, RISING); //optical encoder isr, will trigger on rising edge of channel A
  attachInterrupt(1, RE_ISR, RISING); //rotary encoder isr, will trigger on rising edge of channel A
  
  //initalize Optical PID
  OE_PID_Input = OE_angle; //input to RE PID controller is the actal measured angle
  OE_Setpoint = 25.2; //for now we set a test setpoint to 90 degrees
  OE_PID.SetMode(AUTOMATIC); //turn on the PID to automatic mode
  OE_PID.SetOutputLimits(65, 92); //cap the output of the OE_PID to 64(motor off) to 127 (max speed)

  //initalize Rotary PID
  RE_PID_Input = RE_angle; //input to RE PID controller is the actal measured angle
  RE_Setpoint = -36; //for now we set a test setpoint, test on -36,-72
  RE_PID.SetMode(AUTOMATIC); //turn on the PID to automatic mode
  RE_PID.SetOutputLimits(140, 243); //cap the output of the RE_PID to 128 (full reverse) to 255 (full forward), 192 is stopped
}

void loop() {
  // Optical encoder angle should never be negative (starts at 0 deg)
   if (OE_angle < 0)
   {
    OE_angle = 0;
   }
   //Compute PID output for OE and RE
   OE_PID_Input = OE_angle; //input to OE PID controller is the actal measured angle
   OE_PID.Compute();
   
   RE_PID_Input = RE_angle; //input to RE PID controller is the actal measured angle
   RE_PID.Compute();
   
   //write output to motor 1 (Lift)
   Serial.write((int)OE_PID_Output);
   //delayMicroseconds(50); //delay unecessary??
   //Write to motor 2 (Yaw)
   Serial.write((int) RE_PID_Output);
   /*
   Serial.print('\n');
   Serial.print(OE_PID_Output);
   Serial.print('\t');
   Serial.print((int)OE_PID_Output);
   Serial.print('\t');
   Serial.print(OE_angle);
   Serial.print('\t');
   Serial.print(OE_PID_Input);
   Serial.print('\n');
   */
   /*Pre-written code to run demo
    * First we level at horizontal (OE_SP = 28.8, RE_SP = 0); -> initalize set points to these values
    * Then we rotate 180degree (RE_SP = 180)
    * Code is as follows:
    * @@@@@@@@@@@@@@@@@@@@@@@@@@@
    * 
    * //wait for arm to reach desired set point steadily
    * If OE_angle == OE_SP
    *  OE_Count = OE_Count + 1; 
    *  
    * If OE_Count == 1000  //can vary this value, probably need to play with delays to get a good number
    *   RE_SP = 180;  //Perform 180
    *   
    *If RE_angle == RE_SP
    * RE_Count = RE_Count + 1;
    * 
    *if RE_Count == 1000  //Vary this based on timings
    *  OE_SP = 0; //Lower arm to base position
    * 
    * @@@@@@@@@@@@@@@@@@@@@@@@@@@
    */
}

 void OE_ISR (){
  
      if (digitalRead(OE_lag_pin) == HIGH){
      OE_dir = -1;
      OE_angle = OE_angle - 3.6;
      if (OE_angle <= -360)
          OE_angle = OE_angle + 360;
       /*   
       Serial.print("optical Moving Backwards, angle = :  ");
       Serial.print(OE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
       */
    }

    else if (digitalRead(OE_lag_pin) == LOW){
      OE_dir = 1;
      OE_angle = OE_angle + 3.6;
       if (OE_angle >= 360)
         OE_angle = OE_angle - 360;
         
       /*
       Serial.print("optical Moving Forwards, angle = :  ");
       Serial.print(OE_angle);
       Serial.print('\t');
         Serial.print("degrees");
       Serial.print('\n');
       */
       
    }
       //Serial.print(OE_PID_Output);
       /*Serial.print('\n');
       Serial.print(OE_angle);
       Serial.print('\n');
       */
 }

 void RE_ISR (){
  
      if (digitalRead(RE_lag_pin) == HIGH){
      RE_dir = -1;
      RE_angle = RE_angle - 3.6;
      if (RE_angle <= -360)
          RE_angle = RE_angle + 360;
       /*   
       Serial.print("rotary Moving Backwards, angle = :  ");
       Serial.print(RE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
       */
    }

    else if (digitalRead(RE_lag_pin) == LOW){
      RE_dir = 1;
      RE_angle = RE_angle + 3.6;
       if (RE_angle >= 360)
         RE_angle = RE_angle - 360;
        /*
       Serial.print("rotary Moving Forwards, angle = :  ");
       Serial.print(RE_angle);
       Serial.print('\t');
       Serial.print("degrees");
       Serial.print('\n');
       */
    }
 }

 /* some useful debugging code
   Serial.print(RE_PID_Output);
   Serial.print('\t');
   Serial.print((int)RE_PID_Output);
   Serial.print('\t');
   Serial.print(RE_angle);
   Serial.print('\t');
   Serial.print(RE_PID_Input);
   Serial.print('\n');
   */


