volatile long int count=0;
long int target=240, theta, theta0, error; //target 240 = 1 revolution
double kp=0.7;
int v_out=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(3,INPUT);

  attachInterrupt(digitalPinToInterrupt(2),myFunction,RISING);
  Serial.begin(9600);

  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  digitalWrite(6,LOW); // same as digitalWrite(6,0)
  theta0=count;
}

void loop() {
  if (error>0)
    {
     v_out=15+int(kp*error);
     digitalWrite(6,LOW);
     analogWrite(5,v_out);
     }
  else if (error<0)
   {
     v_out=15-int(kp*error);
     digitalWrite(5,LOW);
     analogWrite(6,v_out);
   }

  theta=count-theta0; //measured in pulses
  error=target-theta;
  Serial.println(theta);
}

void myFunction(){
  if(digitalRead(3)==HIGH)
    count++;
   else
    count--;
}//If motor spins wrong way, swap ++ and --

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
