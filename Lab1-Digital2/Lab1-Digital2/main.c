/* Universidad del Valle de Guatemala
Electrónica Digital 2
Lab1.c
Autor: Alejandra Cardona
Hardware: ATMEGA328P
Creado: 28/01/2025
Ultima modificacion: 28/01/2025

****************************************************************** */

// LIBRER?AS

#define F_CPU 16000000 //Frecuencia en la que opera el sistema - 16 MHz

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Display7Seg/Display7Seg.h"


//Variable Formato: Tipo nombre = Valor

//No lee otras entradas del boton mientras boton 1 este activo
volatile uint8_t interrupcion_btn1 = 0; // Variable de estado

//Variables: Display Hexadecimal
int valueInicio = 0;

//Variables: Contador 4 bits
uint8_t contador4bits_p1 = 0;  //Contador de 4 bits en 0 - Jugador 1
uint8_t contador4bits_p2 = 0;  //Contador de 4 bits en 0 - Jugador 2
uint8_t finalizador = 0;  //Al comparar el estado de los contadores, si uno ha llegado ha ganado

//******************************************************************

void setup(void);

int main(void){ //Funcion main
	
	setup();

	//LOOP 
	while (1){

		
	}
	
}

void setup(void){ //Se utiliza void cuando no se emplean par?metros
	
	cli(); //Deshabilita interrupciones
	
	UCSR0B = 0; //Deshabilita RX y TX
	
	// Puerto D como salidas
	DDRD = 0xFF;
	PORTD = 0;
	
	// Puerto B como salidas
	DDRB = 0xFF;
	PORTB = 0;
	
	//Pines PC3 y PC4 como salidas
	DDRC |= (1 << PC3) | (1 << PC4);
	PORTC &= ~((1 << PC3) | (1 << PC4));

	
	//Pines PC0, PC1 y PC2 como entradas
	DDRC &= ~(1 << PINC0) | ~(1 << PINC1) | ~(1 << PINC2);
	PORTC |= (1 << PINC0) | (1 << PINC1) | (1 << PINC2);
	
	
	// Interrupcion del contador 4 bits
	PCICR |= (1<<PCIE1); // PCIE0 para puerto C de 7:0
	PCMSK1 |= ((1<<PCINT8)|(1<<PCINT9)|(1<<PCINT10)); // Habilita la interrupcion en el puerto C -- PCMSK0 corresponde al puerto C de pines 7:0
	
	sei(); // Habilita las interrupciones 
	
}

//Interrupciones


ISR(PCINT1_vect){
	
	if (!(PINC & (1 << PINC0))) {
		 if (interrupcion_btn1) return; // Si ya está activa, ignorar
		 if (finalizador == 1) return;  // Al acabar el juego sale de la interrupcion

		 interrupcion_btn1 = 1; // Bloquear otros botones
		 
		 // Cuando boton 0 presionado:
		 valueInicio++;
		 
		 		
		 		if (valueInicio==1)
		 		{
			 		//A3 (PC3) es LEDs y A4 (PC4) es display
			 		PORTC &= ~(1 << PC3); // Apaga el transistor (LEDs se apagan)
			 		PORTC |= (1 << PC4); //D12 - Enciende el transistor, activa el display
			 		_delay_ms(1000);
			 		
			 		displayNum(5);
			 		_delay_ms(1000);
			 		displayNum(4);
			 		_delay_ms(1000);
			 		displayNum(3);
			 		_delay_ms(1000);
			 		displayNum(2);
			 		_delay_ms(1000);
			 		displayNum(1);
			 		_delay_ms(1000);
			 		displayNum(0);
			 		_delay_ms(1000);
			 		
					 PORTD = 0;
					 PORTB = 0;					 
			 		PORTC |= (1 << PC3); //Enciende el transistor, desactiva el display
			 		_delay_ms(500);
					PORTC &= ~(1 << PC4); // Apaga el transistor
					contador4bits_p1=0;
					contador4bits_p2=0;
			 		valueInicio=0;
			 		
		 		}
		 
		 // Duracion del proceso
	
		 interrupcion_btn1 = 0; // Liberar botones al terminar
	}
	    else if (!interrupcion_btn1) { // Si no está activa la exclusión y otro botón es presionado

		    if (!(PINC & (1 << PINC1))) {  // Botón 2 en PC1
			    if (finalizador == 0){
				// Aumenta contador del jugador 1
			    contador4bits_p1++;
				_delay_ms(250);
				
			    // Si el contador llega a 4
			    if (contador4bits_p1 >= 4) {
					finalizador = 1;
					
				    PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5); // 1111
				    PORTD &= ~((1 << PD6) | (1 << PD7)); 
				    PORTB &= ~((1 << PB0) | (1 << PB1)); 
					
					_delay_ms(500);
					PORTC &= ~(1 << PC3); // Apaga el transistor (LEDs se apagan)
					PORTC |= (1 << PC4); //D12 - Enciende el transistor, activa el display
					displayNum(1);
					
					return;
			    }

			    switch (contador4bits_p1) {
				    case 1: PORTD |= (1 << PD2); PORTD &= ~((1 << PD3) | (1 << PD4)| (1 << PD5)); break;  // 0001
				    case 2: PORTD |= (1 << PD3); PORTD &= ~((1 << PD2) | (1 << PD4)| (1 << PD5)); break;  // 0010
				    case 3: PORTD |= (1 << PD4); PORTD &= ~((1 << PD3) | (1 << PD2)| (1 << PD5)); break;  // 0100
				    case 4: PORTD |= (1 << PD5); PORTD &= ~((1 << PD3) | (1 << PD4)| (1 << PD2)); break;  // 1000
			    }
		      }
			}

		    else if (!(PINC & (1 << PINC2))) { // Botón 3 en PC2
			    
				if (finalizador == 0){
				
				// Aumenta contador del jugador 1
			    contador4bits_p2++;
			    _delay_ms(250);

			    // Si el contador llega a 4, finaliza el juego
			    if (contador4bits_p2 >= 4) { // 1111
					finalizador = 1;
				    PORTD |= (1 << PD6) | (1 << PD7);
				    PORTB |= (1 << PB0) | (1 << PB1);
				    PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));
					
					_delay_ms(500);
					PORTC &= ~(1 << PC3); // Apaga el transistor (LEDs se apagan)
					PORTC |= (1 << PC4); //D12 - Enciende el transistor, activa el display
					displayNum(2);
					return;

			    }

			    switch (contador4bits_p2) {
				    case 1: PORTD |= (1 << PD6); PORTD &= ~(1 << PD7); PORTB &= ~((1 << PB0) | (1 << PB1)); break;  // 0001
				    case 2: PORTD |= (1 << PD7);  PORTD &= ~(1 << PD6); PORTB &= ~((1 << PB0) | (1 << PB1)); break;  // 0010
				    case 3: PORTD &= ~((1 << PD6) | (1 << PD7)); PORTB |= (1 << PB0); PORTB &= ~(1 << PB1); break;  // 0100
				    case 4: PORTD &= ~((1 << PD6) | (1 << PD7)); PORTB |= (1 << PB1); PORTB &= ~(1 << PB0); break;  // 1000
				}
			  }
			}	
	    }
    }