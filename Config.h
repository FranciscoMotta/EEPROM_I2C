/* 
 * File:   Config.h
 * Author: Franciaco
 *
 * Created on 31 de marzo de 2020, 01:49 AM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>

/*
 * Declaramos Variables
 */

int variable_prueba = 0;
int potencia = 0;
/*
 * Declaramos funciones 
 */

void Funcion_prueba (void);

/*
 * Declaramos macros
 */

#define NIVEL_ALTO 1 
#define NIVEL_BAJO 0
#define TODO_SALIDA 0X00
#define TODO_ENTRADA 0xFF


/*
 * bits de configuración
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#endif	/* CONFIG_H */

