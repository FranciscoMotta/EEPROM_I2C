/* 
 * File:   Usart.h
 * Author: EDWIN
 *
 * Created on 7 de julio de 2019, 01:31 AM
 */

#ifndef USART_H
#define	USART_H

#include <xc.h>
#define _XTAL_FREQ 20000000UL

//Seteo de Pines
#define Tris_Rx TRISCbits.TRISC7
#define Tris_Tx TRISCbits.TRISC6

//Funciones
void Tx_str(char);
void Tx_num(uint8_t);
char Rx(void);
void Confi_Blue (int SPBRG_DATO);
void UART0_Tx_String(char *str);
void UART0_Tx_Integer(int32_t num);

#endif	/* USART_H */

