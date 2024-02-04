#include <banda.h>
banda banda;
int s1 = 29;
int s2 = 28;
int s3 = 27;
int s4 = 26;
int der = 22;
int izq = 23;
int sw = 37;
int p1 = 36;
int p2 = 35;
int tiempo;

void setup() {
  banda.iniciar();
  pinMode(der, OUTPUT);
  pinMode(izq, OUTPUT);
  pinMode(sw, INPUT);
  pinMode(p1, INPUT);
  pinMode(p2, INPUT);
  Serial.begin(9600);
  Serial.println("Inicio");
}


void loop()
{

  
}



