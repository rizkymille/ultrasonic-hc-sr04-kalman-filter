/* credits to VDEngineering video for the kalman filter algorithm
 *  youtube video: https://www.youtube.com/watch?v=ruB917YmtgE
 *
 *  This program was made in Arduino Uno, please customize those
 *  pins according to your board/needs
 */

const int echo = 2; //using Pin 2
const int trig = 3; //using Pin 3
const int maxdist = 335;
const float mindist = 2.5;
double kalman(double U);

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

double distance, duration;

void setup(){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration*.034)/2;

  Serial.print("Distance (in cm): ");

  double fildist;
  fildist = kalman(distance);
  Serial.println(fildist);
  Serial.println(distance);
  
  delay(50);
}
