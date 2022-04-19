#include "Motor.h"


Motor::Motor(uint8_t pinPul, uint8_t pinDirec, uint8_t pinEnabled, int velocidadInicial, int pulsosEnAceleracion)
{
	this->pinPulsos = pinPul;
	this->pinDireccion = pinDirec;	
	this->pinEnabled = pinEnabled;
	this->pulsosEnAceleracion = pulsosEnAceleracion;
	this->velocidadInicial = velocidadInicial;
	retardo1 = RetardosConMicros();
	retardoBackAndFord = RetardosConMillis();

}

void Motor::inicializar()
{
	pinMode(pinPulsos, OUTPUT);
	pinMode(pinDireccion, OUTPUT);
	pinMode(pinEnabled, OUTPUT);

	digitalWrite(pinPulsos, LOW);
	digitalWrite(pinDireccion, LOW);
	digitalWrite(pinEnabled, HIGH);		//desabilitamos el driver con high

	retardo1.inicializarMillis();
	retardoBackAndFord.inicializarMillis();
}

void Motor::mover(uint8_t direccion, int velocidad) {
	
	if (direccionActual != direccion && motorStatus== MOTOR_IS_RUNING) {
		//si la nueva direccion es diferente a la actual
		
		detener();
		setDireccion(direccion);
	}
	

	if (motorStatus == MOTOR_IS_STOPPED) {
		setDireccion(direccion);
		arrancar(velocidad);					//este metodo mantiene al procesador en un bucle hasta que termina
	}
	else {
		//si el motor esta corriendo
		enviarPulso(velocidad);
	}





}

void Motor::setDireccion(uint8_t direccion) {
	
	direccionActual = direccion;
	digitalWrite(pinDireccion, direccion);
}

bool Motor::enviarPulso(unsigned long velocidad) {
	
	retardo1.setRetardo(velocidad);

	if (retardo1.seHaCumplido(true)) {

		if (highLow == LOW) {
			digitalWrite(pinPulsos, HIGH);
			highLow = HIGH;								//EL PULSO ACTUAL ESTA EN HIGH
		}
		else {
			digitalWrite(pinPulsos, LOW);
			highLow = LOW;
		}

		return true;
		
	}
	else {
		return false;
	}
	
	
}

void Motor::setAceleracion(int aceleracionInicial, int pulsosEnAceleracion){
		this->velocidadInicial = aceleracionInicial;
		this->pulsosEnAceleracion = pulsosEnAceleracion;
		
	}

void Motor::detener()
{
	if (motorStatus == MOTOR_IS_STOPPED) return;

	for (int i = 0; i < pulsosEnAceleracion; i++)
	{
		if (i == 0) {
			//significa que es el primer pulso comenzaremos calculando los valores iniciales
			this->velocidadDecrementarPorPulso = ((this->velocidadInicial - velocidadActual) / pulsosEnAceleracion) + 1; //le sumamos un micro segundo por la perdida de los decimales
			//Serial.println(String(velocidadDecrementarPorPulso));
			//Serial.println(String(velocidadActual));
			//Serial.println(String(pulsosEnAceleracion));
		}

		//Serial.println(String(velocidadActual));
		delayMicroseconds(velocidadActual);
		if (highLow == LOW) {
			digitalWrite(pinPulsos, HIGH);
			highLow = HIGH;								//EL PULSO ACTUAL ESTA EN HIGH
		}
		else {
			digitalWrite(pinPulsos, LOW);
			highLow = LOW;
		}

		velocidadActual += velocidadDecrementarPorPulso;

		if (velocidadActual > velocidadInicial) {
			break;
		}

	}
	motorStatus = MOTOR_IS_STOPPED;
	apagarDriver();
	
}

void Motor::arrancar(int velocidadFinal) {
	encenderDriver();
	for (int i = 0; i < pulsosEnAceleracion; i++)
	{
		if (i == 0) {
			//significa que es el primer pulso comenzaremos calculando los valores iniciales
			this->velocidadDecrementarPorPulso = ((this->velocidadInicial - velocidadFinal) / pulsosEnAceleracion) + 1; //le sumamos un micro segundo por la perdida de los decimales
			this->velocidadActual = velocidadInicial;						
			//Serial.println(String(velocidadDecrementarPorPulso));
			//Serial.println(String(velocidadActual));
			//Serial.println(String(velocidadFinal));
			//Serial.println(String(pulsosEnAceleracion));
		}

		//Serial.println(String(velocidadActual));
		delayMicroseconds(velocidadActual);
		if (highLow == LOW) {
			digitalWrite(pinPulsos, HIGH);
			highLow = HIGH;								//EL PULSO ACTUAL ESTA EN HIGH
		}
		else {
			digitalWrite(pinPulsos, LOW);
			highLow = LOW;
		}

		velocidadActual -= velocidadDecrementarPorPulso;

		if (velocidadActual < velocidadFinal) {
			break;
		}

	}
	motorStatus = MOTOR_IS_RUNING;

}

void Motor::apagarDriver() {
	digitalWrite(pinEnabled, DRIVER_OFF);
}

void Motor::encenderDriver() {
	digitalWrite(pinEnabled, DRIVER_ENABLE);
}

void Motor::backAndFord(int duracion, int velocidad) {
	retardoBackAndFord.setRetardo(duracion);		//le establecemos la duracion del va y ven

	
	
	
	if (retardoBackAndFord.seHaCumplido(true)) {

				

		
			if (direccionActual == IZQUIERDA) {
				
				mover(DERECHA, velocidad);
				
			}
			else {
				
				mover(IZQUIERDA, velocidad);
				
			}		

		
		
	}
	
		mover(direccionActual, velocidad);
	
}


	

