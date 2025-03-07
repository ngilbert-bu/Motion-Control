volatile long int count=0;
int v_out=0;
double w=0, wtarget=150, error=150, dv=0, kp=.8; // Experiment with kp to find point where it reaches target as fast as possible w/o jumping
unsigned long int t0, t;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(3,INPUT);

  attachInterrupt(digitalPinToInterrupt(2),myFunction,RISING);
  Serial.begin(9600);

  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  digitalWrite(6,LOW); // same as digitalWrite(6,0)
  t0=millis(); //sets time setup ends to t0
}

void loop() {
  //set the target velocity as a function of time
  t=millis()-t0; //gives us time at start each loop
  if (t<10000) //10s is our mid point of velocity graph
    wtarget=150.0*(double(t)/10000.0); //sets velocity to function of time from 0 to 10s
  else if (t<20000) //function ends at 20s, t=0.
    wtarget=150.0*(20000.0-double(t))/10000.0; //sets function to decrease velocity from 10-20s
  else
    wtarget=0;
  
  analogWrite(5,v_out);
  //delay(500); don't need delay when target is constantly changing
  w=getSpeed();
  Serial.println(w);
  error=wtarget-w;
  dv=kp*error;
  v_out=v_out+int(dv);
  
}

void myFunction(){
  if(digitalRead(3)==HIGH)
    count++;
   else
    count--;
}

double getSpeed(){
  long int count0, count1;
  double theta0, theta1;
  double w;
  count0=count;
  theta0=count0*1.5; // degrees
  delay(100);
  count1=count;
  theta1=count1*1.5;
  w=(theta1-theta0)/.1; // degrees per second
  return(w/360.0*60.0); // revolutions per minute (rpm)
}
