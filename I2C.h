/* 
 * File:   I2C.h
 * Author: HP
 *
 * Created on 4 de abril de 2020, 11:48 PM
 */

#ifndef I2C_H
#define	I2C_H


#define _XTAL_FREQ 20000000UL

/*
 * Macros
 */

#define BAUDRATE 100000UL
#define VALOR_VELOCIDAD_DE_TRANSMISION ((_XTAL_FREQ/(4UL*BAUDRATE))-1)
#define TRIS_SDA TRISCbits.TRISC4
#define TRIS_SCL TRISCbits.TRISC3


/*
 * Funciones
 */

/****************************************************************************
 * Nombre de la función: I2C_Inicializar
 * retorna : Nada
 * ingresa: Nada
 * Descripción : Permite configurar los registros para el protocolo I2C
 * Notas : Solo llamar una vez en el codigo principal
 *****************************************************************************/

void I2C_Inicializar(void);

/****************************************************************************
 * Nombre de la función: I2C_Inicio
 * retorna : Nada
 * ingresa: Nada
 * Descripción : Permite iniciar la comunicación por I2C ´(Comando de START)
 * Notas : Importante al inicial la primera transmición de datos
 *****************************************************************************/

void I2C_Inicio(void);

/****************************************************************************
 * Nombre de la función: I2C_Reinicio
 * retorna : Nada
 * ingresa: Nada
 * Descripción : Permite reiniciar la comunicación por I2C ´(Comando de START)
 * Notas : Importante se usa para modalidades seguidas es decir entre modalidad de lectura y escritura 
 * puede ir esa función
 * 
 * Se puede entender con un comando de END seguido de uno de START
 * 
 *****************************************************************************/

void I2C_Reinicio(void);

/****************************************************************************
 * Nombre de la función: I2C_Detener
 * retorna : Nada
 * ingresa: Nada
 * Descripción : Permite detemer la comunicación por I2C 
 * Notas : Se usa para poner fin a una transmisión véase como el comando END
 * 
 *****************************************************************************/

void I2C_Detener(void);

/****************************************************************************
 * Nombre de la función: I2C_Leer
 * retorna : 1 byte leído CARACTER
 * ingresa: Nada
 * Descripción : Permite leer el dato que retorna el slave
 * Notas : Importante determinar la direccións desde la cual se va a leer los datos
 * 
 *****************************************************************************/

char I2C_Leer(void);

/****************************************************************************
 * Nombre de la función: I2C_ack
 * retorna : nada
 * ingresa: Nada
 * Descripción : Permite dar el procesor de reconocimiento
 * Notas : Importante en el proceso de lectura pues permite seguir leyedo la secuencia de datos
 * 
 *****************************************************************************/

void I2C_ack(void);

/****************************************************************************
 * Nombre de la función: I2C_nack
 * retorna : nada
 * ingresa: Nada
 * Descripción : Permite dar el procesor de NO reconocimiento
 * Notas : Importante en la transmisión pues permite detener el proceso antes de Terminarlo
 * 
 *****************************************************************************/

void I2C_nack(void);

/****************************************************************************
 * Nombre de la función: I2C_Escribir
 * retorna : Caracter
 * ingresa: Byte a transmitir para la dirección o para ser guardado
 * Descripción : Permite transmitir un dato por I2C
 * Notas : Importante garantizar que el dato a enviar es de 1 byte
 * 
 *****************************************************************************/

char  I2C_Escribir(char I2C_data);

#endif	/* I2C_H */

