#pragma once
#include "RetardosConMillis.h"

class RetardosConMicros:public RetardosConMillis
{
public:
	RetardosConMicros() :RetardosConMillis() {}; //invocamos a los constructores de la clase base

	RetardosConMicros(unsigned long retardo) : RetardosConMillis(retardo) {};		//invocamos a los constructores de la clase base

	unsigned long getTime();
	
};



