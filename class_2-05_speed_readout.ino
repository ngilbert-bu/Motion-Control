void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(3,INPUT);

  attachInterrupt(digitalPinToInterrupt(2),myFunction,RISING);
  Serial.begin(9600);
}

volatile long int count=0;
void loop() {
  Serial.printin(getSpeed());
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
  theta0=count0*1.5 // degrees
  delay(100)
  count1=count;
  theta1=count0*1.5
  w=(theta1-theta0)/.1; // degrees per second
  return(w/360.0*60.0) // revolutions per minute (rpm)
}
