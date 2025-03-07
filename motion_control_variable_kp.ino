volatile long int count=0;
int v_out=0, pause=0;
double w=0, wtarget=240, error=240, dv=0, kp=0.2;
double radius = 2.95, dist = 70, amax = 9.5, vmax = 0, atime = 0, rpmmax = 0; 
unsigned long int t0, t;
int hold = 1;
// Define min and max kp values
double kp_min = 0.1;
double kp_max = 0.4;
// Define corresponding speed thresholds
double w_min = 40;     // RPM
double w_max = rpmmax; // Max RPM calculated in setup()

void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  
  attachInterrupt(digitalPinToInterrupt(2),myFunction,RISING);
  Serial.begin(9600);

  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  digitalWrite(5,LOW);
  digitalWrite(6,LOW); 

  vmax = sqrt(dist * amax);          // inches/sec
  atime = (vmax / amax) * 1000;      // acceleration time in ms
  rpmmax = (vmax * 9.549) / radius;  // converts radians/sec to max RPM
  
  t0=millis(); 
}

void loop() {
  t=millis()-t0;

  if (t < atime) { 
    wtarget = rpmmax * (double(t) / atime);
} else if (t < 2 * atime) { 
    wtarget = rpmmax * (2 * atime - double(t)) / atime;
} else if (t < 2 * atime + pause) { 
    wtarget = 0;
} else if (t < 3 * atime + pause) {
    wtarget = -rpmmax * ((double(t) - (2 * atime + pause)) / atime);
} else if (t < 4 * atime + pause) {
    wtarget = -rpmmax * ((4 * atime + pause - double(t)) / atime);
} else {
    wtarget = 0;
    hold = 0;
    v_out = 0;
}

// Variable kp adjustment
  double abs_wtarget = abs(wtarget);
  if (abs_wtarget <= w_min) {
    kp = kp_min;
  } else if (abs_wtarget >= w_max) {
    kp = kp_max;
  } else {
    kp = kp_min + (kp_max - kp_min) * ((abs_wtarget - w_min) / (w_max - w_min));
  }
  
  w = getSpeed();
  Serial.println(w);
  error = wtarget - w;
  dv = kp * error*hold;
  v_out = v_out + int(dv);

  if (wtarget >= 0) {
    analogWrite(5, v_out);
    analogWrite(6, 0);
  } else {
    analogWrite(5, 0);
    analogWrite(6, abs(v_out)); // Inverted signal for reverse
  }
}

void myFunction(){
  if (digitalRead(3) == HIGH)
    count++;
  else
    count--;
}

double getSpeed() {
  long int count0, count1;
  double theta0, theta1;
  double w;
  count0 = count;
  theta0 = count0 * 1.5; 
  delay(100);
  count1 = count;
  theta1 = count1 * 1.5;
  w = (theta1 - theta0) / 0.1; 
  return (w / 360.0 * 60.0); 
}
