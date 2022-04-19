#include "Pantalla.h"

Pantalla::Pantalla(LiquidCrystal_I2C* pan)
{
	this->pantalla = pan;
}

Pantalla::Pantalla(uint8_t direccion)
{
	pantalla = new LiquidCrystal_I2C(direccion, 20, 4);
	//pantalla es una variable de tipo puntero es decir que guardara una direccion de la memoria donde se crea el objeto
	//por eso usamos la palabra reservada new para crear un nuevo objeto pero new ya entrega una referencia es decir una 
	//direccion de la memoria donde se creo el nuevo objeto y la direcicon se almacenara en pantalla que es un puntero
	//entocnes podremos usar ambos constructores, tanto el superior que es creando el objeto liquidCristal fuera de esta clase
	//y pasandole solo su referencia de memoria, o pasando la direccion y creando aqui el objeto liquidCristal
}

void Pantalla::inicializar()
{
	pantalla->init();
}

void Pantalla::pantallaPrincipal(int RPM, String modo, int duracion)
{
	this->pantalla->backlight();
	//pantalla->clear();
	this->pantalla->setCursor(0, 0);
	this->pantalla->print("Rpm:" + String(RPM) + " Modo: " + modo);
	this->pantalla->setCursor(0, 1);
	this->pantalla->print("Tiempo:" + String(duracion));
}

