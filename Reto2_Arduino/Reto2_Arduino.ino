int estado = 0, destino, tiempo, inicio, comprobacion;
unsigned int tiempoActual = 0;
unsigned int tiempoAnterior = 0;
int hora_inicio = 0;
int hora_actual = 0;
int der = 22;            // der en el pin 22
int izq = 23;           // izq en el pin 22
int s1  = 37;           // s1 en el pin 30
int s2  = 36;           // s2 en el pin 31
int s3  = 35;           // s3 en el pin 32
int s4  = 34;           // s4 en el pin 33
int pos_actual; 
int Sn;// 

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  pinMode(der, OUTPUT);       // configura el der como salida
  pinMode(izq, OUTPUT);       // configura el izq como salida
  pinMode(s1, INPUT);   // configura s1 como entrada
  pinMode(s2, INPUT);   // configura s2 como entrada
  pinMode(s3, INPUT);   // configura s3 como entrada
  pinMode(s4, INPUT);   // configura s4 como entrada
  Serial3.print("Estado: ");
  Serial3.println(estado);
}


void Retardo()
{
  hora_inicio = millis();
  hora_actual = millis();
  while ((hora_actual - hora_inicio) < 500)
  { hora_actual = millis();
  }
}

void ingreso_datos()
{
  Serial3.println("Ingrese destino");
  while (Serial.available() == 0)
  {
  }
  destino = Serial.parseInt();
  Serial3.println("Ingresetiempo");
  while (Serial.available() == 0)
  {
  }
  tiempo = Serial.parseInt();
  Serial3.println("Ingrese 1 para iniciar");
  while (Serial.available() == 0)
  {
  }
  inicio = Serial.read();
}

void posicion_banda()
{
  if (digitalRead(s1) == HIGH)
  {
    Sn = 1;
  }
  else if (digitalRead(s2) == HIGH)
  {
    Sn = 2;
  }
  else if (digitalRead(s3) == HIGH)
  {
    Sn = 3;
  }
  else if (digitalRead(s4) == HIGH)
  {
    Sn = 4;
  }
  else
  {
    Sn = 0;
  }
  
  
  return Sn;}

void loop()
{
  posicion_banda();
  Serial.write(Sn);
  //Serial3.print("SENSOR: ");
  //Serial3.println(Sn);
  switch (estado)                             // Estructura switch
  {
    case 0:   digitalWrite(der, LOW);   // desactiva der
      digitalWrite(izq, LOW);   // desactiva izq
      tiempo = 0;
      destino = 0;
      ingreso_datos();
      while (digitalRead(s1) == LOW)
      {
      Serial3.println("Favor poner la moneda en la posición 1");
      Retardo();
      }
      posicion_banda();
      Serial.write(Sn);
      Serial3.print("Estado: ");
      Serial3.println(estado);
      estado = 1; // Vaya al estado 1

      
      break;

    case 1:  digitalWrite(der, LOW);  // desactiva der
      digitalWrite(izq, HIGH);  // activa izq
      posicion_banda();
      Serial.write(Sn);
      if ((digitalRead(s2) == HIGH) && destino == 2)
      {
        estado = 2;
        Serial3.print("Estado: ");
        Serial3.println(estado);
        tiempoAnterior = millis();
      }
      if (digitalRead(s3) == HIGH && destino == 3)
      {
        estado = 2;
        Serial3.print("Estado: ");
        Serial3.println(estado); 
        tiempoAnterior = millis();
      }
      if (digitalRead(s4) == HIGH && destino == 4)
      {
        estado = 2;
        Serial3.print("Estado: ");
        Serial3.println(estado);
        tiempoAnterior = millis();
      }
      break;

    case 2:  digitalWrite(der, LOW);  // desactiva der
      digitalWrite(izq, LOW);   // desactiva izq
      tiempoActual = millis();
      if ((tiempoActual - tiempoAnterior) > (tiempo * 1000))
      {
        estado = 3;
        Serial3.print("Estado: ");
        Serial3.println(estado);
      }
      break;

    case 3: digitalWrite(izq, LOW);   // desactiva izq
      digitalWrite(der, HIGH);  // activa der
      posicion_banda();
      Serial.write(Sn);
      if ((digitalRead(s1) == HIGH))
      {
        estado = 0;
        Serial3.print("Estado: ");
        Serial3.println(estado);
      }
      break;
  }

}
