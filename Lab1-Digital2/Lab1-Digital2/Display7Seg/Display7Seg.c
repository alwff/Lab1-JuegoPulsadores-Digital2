/*
 * Display7Seg.c
 *
 * Created: 1/30/2025 6:25:38 PM
 *  Author: Alejandra Cardona
 */ 
#include "Display7Seg.h"
#include <avr/io.h>

void displayNum(uint8_t simbolo){
	switch(simbolo){
		case 0: //Muestra 0 en el display de 7 segmentos
			PORTD = 0b11111100; // a, b, c, d, e, encendidos
			PORTB = 0b00000000; // g, pd apagados
			break;
		case 1: //Muestra 1 en el display de 7 segmentos
			PORTD = 0b00011000; 
			PORTB = 0b00000000; 
			break;
		case 2: //Muestra 2 en el display de 7 segmentos
			PORTD = 0b01101100;
			PORTB = 0b00000001; 
			break;
		case 3: //Muestra 3 en el display de 7 segmentos
			PORTD = 0b00111100; // a, b, c, d encendidos
			PORTB = 0b00000001; // g encendido, f apagado
			break;
		case 4: //Muestra 4 en el display de 7 segmentos
			PORTD = 0b10011000; // b, c encendidos
			PORTB = 0b00000001; // g encendido, f apagado
			break;
		case 5: //Muestra 5 en el display de 7 segmentos
			PORTD = 0b10110100; // a, c, d, f encendidos
			PORTB = 0b00000001; // g encendido, f apagado
			break;
		case 6: //Muestra 6 en el display de 7 segmentos
			PORTD = 0b11110100;  // 10111110 -> a, c, d, e, f, g encendidos
			PORTB = 0b00000001;  // 00000000 -> dp apagado
			break;
		case 7: //Muestra 7 en el display de 7 segmentos
			PORTD = 0b00011100;  // 11100000 -> a, b, c encendidos
			PORTB = 0b00000000;  // 00000000 -> g apagado, dp apagado
			break;
		case 8: //Muestra 8 en el display de 7 segmentos
			PORTD = 0b11111100;  // 11111110 -> Todos los segmentos encendidos
			PORTB = 0b00000001;  // 00000000 -> dp apagado
			break;
		case 9: //Muestra 9 en el display de 7 segmentos
			PORTD = 0b10011100;  // 11110110 -> a, b, c, d, f, g encendidos
			PORTB = 0b00000001;  // 00000000 -> dp apagado
			break;
		  case 10:  //Muestra A en el display de 7 segmentos
			  PORTD = 0b11011100;  // 11101110 -> A
			  PORTB = 0b00000001;
			  break;
		  case 11:  //Muestra B en el display de 7 segmentos
			  PORTD = 0b11111100;  // 00111110 -> B
			  PORTB = 0b00000001;
			break;
		  case 12:  //Muestra C en el display de 7 segmentos
			  PORTD = 0b11100100;  // 10011100 -> C
			  PORTB = 0b00000000;
			  break;
		  case 13:  //Muestra D en el display de 7 segmentos
			  PORTD = 0b11111100;  // 01111010 -> D
			  PORTB = 0b00000000;
			  break;
		  case 14:  //Muestra E en el display de 7 segmentos
			  PORTD = 0b11100100;  // 10011110 -> E
			  PORTB = 0b00000001;
			  break;
		  case 15:  //Muestra F en el display de 7 segmentos
			  PORTD = 0b00011100;  // 10001110 -> F
			  PORTB = 0b00000001;
			  break;
			}
}

