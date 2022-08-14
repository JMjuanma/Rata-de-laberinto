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
	cm = 0.01723 * readUltrasonicDistance(x, y);
	return cm;
}
 
void derecha()
{
	digitalWrite(mia);
 	analogWrite(actI, 130);
 	digitalWrite(mdr);
 	analogWrite(actD, 130);
 	delay(800);
 	stop();
}
 
void izquierda()
{
 	digitalWrite(mda);
 	analogWrite(actD, 130);
 	digitalWrite(mir);
 	analogWrite(actI, 130);
 	delay(800);
 	stop();
}
 
void avanzar()
{
 	digitalWrite(mda); //definir velocidad
 	analogWrite(actD, 130);
 	digitalWrite(mia);
 	analogWrite(actI, 130);
}

void retroceder()
{
 	digitalWrite(mdr); //definir velocidad
 	analogWrite(actD, 130);
 	digitalWrite(mir);
 	analogWrite(actI, 130);
}
 
bool detector_frontal()
{
 	if (distancia(sft, sfe) < 3)
 	{
 		return true;
 	}
 
}
bool detector_izquierda()
{
	if(distancia(sit, sie) < 3)
	{
		return true;
	}
}
void detector_derecho()
{
 if (distancia(sdt, sde) < 3)
	{
		return true;
	}
}
void stop()
{
	dW(mda, 0);
	dW(mdr, 0);
	dW(mia, 0);
	dW(mir, 0);
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
	avanzar();
	delay(2000);
	stop();
	derecha();
	delay(500)
	if(detector_derecho)
	{
		retroceder();
		delay(2000);
	}
	else
	{
		izquierda();
	}

}