/* credits to VDEngineering video for the kalman filter algorithm
 *  youtube video: https://www.youtube.com/watch?v=ruB917YmtgE
 */

// ULTRASONIC //
// Pins
const int echo = 2;
const int trig = 3;
// Constrains
const int maxdist = 335;
const float mindist = 2.5;

double distance, duration;
double kaldist;

double kalman(double U){
  static const double R = 40;
  static const double H = 1.00;
  static double Q = 10;
  static double P = 0;
  static double U_hat = 0;
  static double K = 0;
  K = P*H/(H*P*H+R);
  U_hat += + K*(U-H*U_hat);
  P = (1-K*H)*P+Q;
  return U_hat;
}

void setup(){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void usonic_transmit() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
}

void loop(){
  usonic_transmit();
  
  duration = pulseIn(echo, HIGH);
  distance = (duration*.034)/2;
  kaldist = kalman(distance);

  Serial.print("Distance (in cm): %f", distance);
  Serial.print("Corrected distance (in cm): %f", kaldist);
  
  delay(1/30);
}
