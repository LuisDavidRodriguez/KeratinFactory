#pragma once
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

class Pantalla {
	
private:
	LiquidCrystal_I2C* pantalla;

public:
	Pantalla(LiquidCrystal_I2C* pan);//Le pido como parametro un objeto liquidCristal hay que crearlo en el archibo ino y pasarselo a este cosntructor
	Pantalla(uint8_t direccion);

	void inicializar();
	void pantallaPrincipal(int RPM, String modo, int duracion);
	 
	
};