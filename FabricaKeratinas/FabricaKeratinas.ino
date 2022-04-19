/*
 Name:		FabricaKeratinas.ino
 Created:	19/05/2021 15:50:33
 Author:	david
*/

// the setup function runs once when you press reset or power the board
#include "Pantalla.h"
#include "Motor.h"
#include "RetardosConMillis.h"
#include <HardwareSerial.h>



Pantalla *lcd = new Pantalla(0x3F); //0x27 0x3f

int potenciometroVelocidad = 0;
int potenciometroTiempo = 0;

Motor motor1(9, 8,7,1200,500);

RetardosConMillis retardoPantalla = RetardosConMillis(250);


bool detener = false;
bool direccion = IZQUIERDA;
bool backAndFord = false;


bool ledEstatus = false;


void setup() {
	lcd->inicializar();
	motor1.inicializar();
	retardoPantalla.inicializarMillis();
	Serial.begin(9600);

	pinMode(3, INPUT_PULLUP);
	pinMode(4, INPUT_PULLUP);
	pinMode(5, INPUT_PULLUP);
	pinMode(13, OUTPUT);			//EL PIN DEL LED
	
	
	
	
	potenciometroVelocidad = analogRead(A0);
	potenciometroTiempo = analogRead(A1);
	detener = digitalRead(3);
	direccion = digitalRead(4);
	backAndFord = digitalRead(5);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (retardoPantalla.seHaCumplido(true)) {
		potenciometroVelocidad = analogRead(A0);
		potenciometroTiempo = analogRead(A1)*10;			//nos dara lecturas de 0 a 1024, lo podremos usar como millis entonces el maximo seria 1.02Segundos al multiplicarlo por 10 nos dara hasta 10 segundos en una sola direccion


		//lcd->pantallaPrincipal(potenciometroVelocidad, "Continuo", 10);

		detener = digitalRead(3);
		direccion = digitalRead(4);
		backAndFord = digitalRead(5);

		/*
		Se ha determinado con el osciloscopio que cuando la lectura analogica es de 150 us hacia abajo
		el motor comienza a tener problemas de pasos porque ya va muy rapido.
		porque la lectura analogica la estamos usando directamente como US
		Los pulsos tienen que ser parejos el mismo periodo abajo que arriba.
		duracion del pulso arriba en 
		us	|	frecuencia	|RPM
		1.02ms	488hz		140
		950us	526hz		159
		897us	560			168
		750		670			200
		650		763			230
		550		919			280
		450		1.1kh		330
		350		1.44kh		430
		250		2kh			600
		150		3.17kh		950
					
		*/
		if (potenciometroVelocidad < 180) {
			potenciometroVelocidad = 180;		//limitamos la velocidad maxima
		}



		if (ledEstatus) {
			//si el led esta encendido lo apagamos
			digitalWrite(13, LOW);
			ledEstatus = false;
		}
		else {
			digitalWrite(13, HIGH);
			ledEstatus = true;
		}

		
	}

	
	if (!backAndFord) {
		motor1.backAndFord(potenciometroTiempo, potenciometroVelocidad);

	}
	else {
		if (direccion == IZQUIERDA) {
			motor1.mover(IZQUIERDA, potenciometroVelocidad);
		}
		if (direccion == DERECHA) {
			motor1.mover(DERECHA, potenciometroVelocidad);
		}
	
	}
	
	
	
	
}
