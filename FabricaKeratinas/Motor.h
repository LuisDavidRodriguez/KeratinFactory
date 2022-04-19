#pragma once
#include <Arduino.h>
#include "RetardosConMicros.h"
#include <HardwareSerial.h>

#define IZQUIERDA 0x00
#define DERECHA 0x01
#define PULSO_HIGH true
#define PULSO_LOW false
#define MOTOR_IS_RUNING true
#define MOTOR_IS_STOPPED false
#define DRIVER_ENABLE 0x00
#define DRIVER_OFF 0x01

class Motor
{
private:
	uint8_t pinPulsos;
	uint8_t pinDireccion;
	uint8_t pinEnabled;
	bool motorStatus = MOTOR_IS_STOPPED;
	uint8_t direccionActual;

	RetardosConMicros retardo1;
	RetardosConMillis retardoBackAndFord;

	/*
	Qeremos controlar el cambio del pulso de high a low
	*/
	bool highLow = false;

	int contadorAceleracion = 0;			//contaremos el numero de pulsos que se le han enviado al motor en modo aceleracion
	int velocidadInicial = 1500; //us
	int pulsosEnAceleracion = 1000;
	int velocidadDecrementarPorPulso = 0;
	int velocidadActual = 0;

	bool inicioAceleracion = true;
	bool inicioDesaceleracion = true;



public:
	Motor(uint8_t pinPul, uint8_t pinDirec,uint8_t pinEnabled, int velocidadInicial, int pulsosEnAceleracion);

	void inicializar();

	void mover(uint8_t direccion, int velocidad);

	void detener();

	void setDireccion(uint8_t direccion);

	bool enviarPulso(unsigned long duracion);

	void apagarDriver();
	void encenderDriver();



	void arrancar(int velocidadFinal);


	void setAceleracion(int aceleracionInicial, int pulsosEnAceleracion);

	void backAndFord(int duracion, int velocidad);

	

};

