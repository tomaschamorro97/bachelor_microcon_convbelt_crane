#ifndef banda_h
#define banda_h

#include "Arduino.h"
#include "TimerOne.h"


class banda
{	   		
    public:
    	banda();
		void iniciar(); 
		void enviar(String);
};


#endif
