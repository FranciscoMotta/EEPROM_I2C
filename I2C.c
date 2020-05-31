


#include <xc.h>
#include <pic16f877a.h>
#include "I2C.h"

void I2C_Inicializar() {

    TRIS_SCL = 1;
    TRIS_SDA = 1;

//    SSPSTATbits.SMP = 1; /*Configuramos la velocidad de transmisión en el estandar de 100 Khz - 1Mhz*/
//    SSPSTATbits.CKE = 0; /*No trabajamos con las especificaciones del bus SMB*/

    /*
     *Nota: Las lineas de código anterior las ponemos simplicar en la siguiente linea SSPSTAT = 0b1000000;
     */

    SSPSTAT = 0b1000000;
    
//    SSPCONbits.SSPEN = 1; /*Habilitamos los pines de SCA y SCL para la transmición de datos*/
//    SSPCONbits.SSPM = 0b1000; /*Configuramos el PIC como maestro con un reloj = FOSC/(4 * (SSPADD + 1)) para la transmición de datos*/
   
    /*
     * Nota: Las lineas de código anterior se puede resumir en:     SSPCON = 0b00101000; /
     */

    SSPCON = 0b00101000;
    
    SSPCON2 = 0x00; /*Este registro se emplea iniciada la transmisión de datos*/
    
    SSPADD = VALOR_VELOCIDAD_DE_TRANSMISION;
}


void I2C_Inicio(void) {

    SSPCON2bits.SEN = 1; /*Inicia la comunicación i2c */
    while (SSPCON2bits.SEN == 1); /*Bucle de inicio de la transmisión de datos*/
}

void I2C_Reinicio(void) {

    SSPCON2bits.RSEN = 1; /* Reinicia la comunicación i2c */
    while (SSPCON2bits.RSEN == 1); /*Bucle de reinicio de la transmisión*/
}

void I2C_Detener(void) {

    SSPCON2bits.PEN = 1; /*Damos la condición de stop de la comunicación serial*/
    while (SSPCON2bits.PEN == 1); /*Bucle para confirmar si ya se cumplió la comdición de parada*/
}

char I2C_Leer(void) {

    PIR1bits.SSPIF = 0; /*Se limpia la interrupcion del puerto serial SSP*/
    SSPCON2bits.RCEN = 1; /*Mandamos el bit de inicio de lectura*/
    while (PIR1bits.SSPIF == 0); /*Esperamos a que sucesa la interrupcion*/
    return SSPBUF; /*Devuelve el valor leído*/
}

void I2C_ack(void) {
    PIR1bits.SSPIF = 0; /*Se limpia la interrupcion del puerto serial SSP*/
    SSPCON2bits.ACKDT = 0; /*Limpiamos el bit de reconocimiento de transmición de datos*/
    SSPCON2bits.ACKEN = 1; /*Habilitamos el bit de secuencia de reconocimiento*/
    while (PIR1bits.SSPIF == 0); /*Esperamos a que se termine la transmisión que al ocurrir activa la bandera de interrupción*/
}

void I2C_nack(void) {
    PIR1bits.SSPIF = 0; /*Se limpia la interrupcion del puerto serial SSP*/
    SSPCON2bits.ACKDT = 1; /*Ponemosel bit de reconocimiento de transmición de datos eso es para decir que estamos en el N-ACK para terminar el proceso de transmisión*/
    SSPCON2bits.ACKEN = 1; /*Habilitamos el bit de secuencia de reconocimiento*/
    while (PIR1bits.SSPIF == 0); /*Esperamos a que se termine la transmisión que al ocurrir activa la bandera  de interrupción*/
}

char I2C_Escribir(char I2C_data) {
    PIR1bits.SSPIF = 0;
    SSPBUF = I2C_data; //Envia data por I2C
    while (PIR1bits.SSPIF == 0); //Wait for interrupt flag to go high indicating transmission is complete
    if (ACKSTAT)
        return 1;
    else
        return 2;
}