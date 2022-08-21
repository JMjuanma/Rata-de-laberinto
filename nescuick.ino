#define pM(a, b) pinMode(a, b) 
#define O OUTPUT
#define I INPUT
#define dW(a, b) digitalWrite(a, b)
#define dR(a) digitalRead(a)
const int mda = 2, mdr = 3, mia = 4, mir = 5, sft = 6, sfe = 7, sdt = 8, sde = 9, sit = 12, sie = 13, actI = 10, actD = 11; //motor derecha adelante, motor derecha retro, motor izquierda adelante . . .
 
int inches = 0;
 
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
  digitalWrite(mia, 1);
  analogWrite(actI, 130);
  digitalWrite(mdr, 1);
  analogWrite(actD, 130);
  delay(x);
  stop();
}
 
void izquierda( int x)
{
  digitalWrite(mda, 1);
  analogWrite(actD, 130);
  digitalWrite(mir, 1);
  analogWrite(actI, 130);
  delay(x);
  stop();
}
 
void avanzar()
{
    (detector_izquierda() > detector_derecho()) ? izquierda( 200 ) : derecha( 200 );
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


void setup()
{
  pM(mda, O);
  pM(mdr, O);
  pM(mia, O);
  pM(mir, O);
}
 
void loop()
{
	while(detector_frontal() < 5)
	{
		if(detector_derecho() < 5)
		{
			stop();
			derecha(800);
			break;
		}
		avanzar();
	}
	stop();
	if(detector_izquierda() < 5)
	{
		stop();
		izquierda(800);
	}
	else
	{
		izquierda(1600);
	}
    stop();
    avanzar();
    delay(5000);
  if (detector_derecho()>detector_izquierdo())
  {
    derecha(200);
  }
  else if (detector_izquierda()>detector_derecho())
  {
    izquierda(200);
  }
}