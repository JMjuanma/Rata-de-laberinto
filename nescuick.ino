#include <vector>

#define pM(a, b) pinMode(a, b) 
#define O OUTPUT
#define I INPUT
#define dW(a, b) digitalWrite(a, b)
#define dR(a) digitalRead(a)
const int mda = 2, mdr = 3, mia = 4, mir = 5, sft = 6, sfe = 7, sdt = 8, sde = 9, sit = 12, sie = 13, actI = 10, actD = 11; //motor derecha adelante, motor derecha retro, motor izquierda adelante . . .
int inches = 0, cm=0, g=800, v=1600, c=200, brujula=0;
vector<bool>v[4];
bool l [4];
 
int cm = 0;
 
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}
 
long distancia(int x, int y)
{
  return 0.01723 * readUltrasonicDistance(x, y);
}
void stop()
{
  dW(mda, 0);
  dW(mdr, 0);
  dW(mia, 0);
  dW(mir, 0);
}
 
void derecha( int x)
{
  brujula = (2*brujula-1)%3;
  digitalWrite(mia, 1);
  analogWrite(actI, 130);
  digitalWrite(mdr, 1);
  analogWrite(actD, 130);
  delay(x);
  stop();
}
 
void izquierda( int x)
{
  brujula = (brujula+1)%3;
  digitalWrite(mda, 1);
  analogWrite(actD, 130);
  digitalWrite(mir, 1);
  analogWrite(actI, 130);
  delay(x);
  stop();
}
 
void avanzar()
{
    (detector_izquierda() > detector_derecho()) ? izquierda( c ) : derecha( c );
  digitalWrite(mda, 1); //definir velocidad
  analogWrite(actD, 130);
  digitalWrite(mia, 1);
  analogWrite(actI, 130);
  delay(300)
}

void retroceder()
{
  digitalWrite(mdr, 1); //definir velocidad
  analogWrite(actD, 130);
  digitalWrite(mir, 1);
  analogWrite(actI, 130);
}

void giro()
{
  brujula = (brujula+2)%3;
  derecha(v);
}
 
int detector_frontal()
{
  return distancia(sft, sfe);
}
int detector_izquierda()
{
  return distancia(sit, sie);
}
int detector_derecho()
{
  return distancia(sdt, sde);
}

void nav( int x )
{
  if(x==0)
  {
    avanzar();
  }
  else if (x==1)
  {
    derecha(g);
  }
  else if (x==2)
  {
    giro();
  }
  else
  {
    izquierda(g);
  }
}

void setup()
{
  pM(mda, O);
  pM(mdr, O);
  pM(mia, O);
  pM(mir, O);
  brujula = 0;
}
 
void loop()
{
	if ((detector_derecho()>10)+(detector_izquierda()>10)+(detector_frontal()>10)>1)
  {
    l[brujula]=(detector_frontal()>10);
    l[(brujula+1)%3]=(detector_izquierda()>10);
    l[(brujula+3)%3]=(detector_derecho()>10);
    l[(brujula+2)%3]=0;
    v.push_back(l);
    if(v.front[0]) { nav(0); v.front[0]=0; }
    else if(v.front[1]) { nav(1); v.front[1]=0; }
    else if(v.front[3]) { nav(3); v.front[3]=0; }
    else { nav(2); v.pop(); }
  }
  else if (detector_derecho()>5)
  {
    derecha(g);
  }
  else if(detector_izquierda()>5)
  {
    izquierda(g);
  }
  else if (detector_frontal()<4)
  {
    giro();
  }
  avanzar();
}