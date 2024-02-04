import serial, time, sys, threading

ser = serial.Serial('COM1', 9600)
time.sleep(2)
estado = 0
event = threading.Event();

def readArduino(datoser):
    a = datoser.splitlines()
    b = str(a[0])
    c = b.replace('b','')
    d = c.replace("'",'')
    estado = float(d)
    return estado

while True:


    print ("Ingrese destino 2, 3 o 4")
    destino = str(input())
    if int(destino) not in [2,3,4]:
        print('Error. No existe este destino')
        continue
    ser.write(destino.encode())
    time.sleep(0.5)
    print ("Ingrese tiempo en segundos de un solo digito")
    tiempo = str(input())
    ser.write(tiempo.encode())
    time.sleep(0.5)
    print ("Oprima 1 para comenzar")
    comienzo = str(input())
    ser.write(comienzo.encode())
    time.sleep(0.5)
    sensor = int(ser.read()[-1])

    
    while sensor == 0:
        print('Favor ponga la moneda en la posición 1. La banda se encuentra apagada(Estado 0)')
        sensor = int(ser.read()[-1])
    print("----------------------------------------------------------------------------------------------")
    print('La moneda ya se encuentra en la posicion 1 y la banda comenzara a girar hacia la izquierda (Estado 1)')
    print("----------------------------------------------------------------------------------------------")

    for i in range(2,int(destino)+1):
        print("La moneda no ha pasado por el sensor {}".format(i))
        while i != sensor:
            sensor = int(ser.read()[-1])
            
        print("----------------------------------------------------------------------------------------------")  
        print("La moneda ha pasado por el sensor {}".format(i))
        print("----------------------------------------------------------------------------------------------")  
        time.sleep(1)
          
    print('La moneda ha llegado a su destino (Destino es el sensor {}). La banda ahora se encuentra en estado 2 y se esperaran {} segundos para devolverse a posicion inicial'.format(i,int(tiempo)))
    time.sleep(int(tiempo))
    print("----------------------------------------------------------------------------------------------")
    print('Tiempo de espera ha culminado. Estado 3 en ejecución. Banda girando hacia la derecha')
    print("----------------------------------------------------------------------------------------------")
    
    for i in range(int(destino),0,-1):
        print("La moneda no ha pasado por el sensor {}".format(i))
        while i != sensor:
            sensor = int(ser.read()[-1])
        print("----------------------------------------------------------------------------------------------")  
        print("La moneda ha pasado por el sensor {}".format(i)) 
        time.sleep(1)
        
    print("----------------------------------------------------------------------------------------------")
    print('La moneda ha retornado al origen. Se volverá de nuevo al estado 0')
    print('Gracias profe por el 5')

        

    
        
    




ser.close()
