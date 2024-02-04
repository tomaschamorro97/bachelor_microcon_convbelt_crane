#include "Arduino.h"
#include "banda.h"
String cadenaanterior="";

banda::banda()
{
}

void banda::enviar(String cadena)
{
 if(cadena != cadenaanterior)
 {
 	Serial.println(cadena);
	cadenaanterior=cadena;
 }
}

static void funcion()
{
  extern int s1;
  extern int s2;
  extern int s3;
  extern int s4;
  extern int der;
  extern int izq;
  static int estado;
  static int encender;
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);

  if (Serial3.available() > 0)
  {
    estado = Serial3.read();
	if(estado=='@')
	{
	  int val1,val2,val3,val4;
	  val1 = Serial3.read()-48;
	  val2 = Serial3.read()-48;
	  val3 = Serial3.read()-48;
	  val4 = Serial3.read()-48;
	  estado=((val1*1000)+(val2*100)+(val3*10)+val4);
	}
  }
  if (digitalRead(der) == HIGH && digitalRead(izq) == LOW)
  {
    encender = '1';
  }
  if (digitalRead(izq) == HIGH && digitalRead(der) == LOW)
  {
    encender = '2';
  }
  if (((digitalRead(der) == LOW) && (digitalRead(izq) == LOW))||((digitalRead(der) == HIGH) && (digitalRead(izq) == HIGH)))
  {
    encender = '0';
  }

  String dato="";
  dato="*";
  dato.concat(encender);
  Serial3.println(dato);

  if (estado == 1)
  {
    digitalWrite(s1, 1);
    digitalWrite(s2, 0);
    digitalWrite(s3, 0);
    digitalWrite(s4, 0);
  }
  if (estado == 2)
  {
    digitalWrite(s1, 0);
    digitalWrite(s2, 1);
    digitalWrite(s3, 0);
    digitalWrite(s4, 0);
  }
  if (estado == 4)
  {
    digitalWrite(s1, 0);
    digitalWrite(s2, 0);
    digitalWrite(s3, 1);
    digitalWrite(s4, 0);
  }
  if (estado == 8)
  {
    digitalWrite(s1, 0);
    digitalWrite(s2, 0);
    digitalWrite(s3, 0);
    digitalWrite(s4, 1);
  }
  if (estado == 0)
  {
    digitalWrite(s1, 0);
    digitalWrite(s2, 0);
    digitalWrite(s3, 0);
    digitalWrite(s4, 0);
  }
}

void banda::iniciar()
{
	Serial3.begin(57600);
	Timer1.initialize(50000);
    Timer1.attachInterrupt(funcion);
}
