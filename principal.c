/*
 * File:   principal.c
 * Author: HP
 *
 * Created on 4 de abril de 2020, 11:39 PM
 */


#include <xc.h>
#include "Config.h"
#include "I2C.h"
#include <stdint.h>
#include <pic16f877a.h>
#include "Usart.h"

char Mensaje_De_Envio[] = "HOLA";

void main(void) {
    int Variable_De_Conteo = 0;

    /*
     * Inicializamos el USART para la terminal SERIAL
     */

    Confi_Blue(32); /*Librer�a propia del ingiero Torres que configura el terminal serial*/
    /*************************************************************************************************/
    /*
     *EN LA LIBRER�A SE MODIFIC� EL SPBRG a un VALOR DE 32 para cumplir con el datasheet al poner un cristal de 20mhz
     * /
    
    
    //          /*
    //     * Para configurar las salidas an�logas como digitales quitar de comentario la siguiente line de codigo:
    //     * ADCON1 = 0x06;
    //     */
    I2C_Inicializar(); /*Iniciamos y configuramos los bits necesarios del protocolo de comunicaci�n I2C*/
    //
    //    /*
    //     * Para la memoria 24C32 el fabricante nos dice que para iniciar tenemos que dar el comando de START
    //     * y luego indicar a que esclavo nos queremos dirigir y el modo en el que va a esta (LECTURA O ESCRITURA) (R/W)
    //     */
    //
    //    I2C_Inicio(); /*Damos el comando de START para iniciar la transmisi�n*/
    //
    //    I2C_Escribir(0b10100000);
    //    /*
    //     * Del apartado anteior cabe resaltar que los primeros 4 bits son dados por defecto con la memoria 24C32
    //     * Los siguientes 3 bits son relativos a A3-A2-A1 que son la direcci�n propia del sclavo pues pueden haber muchas memorias del mismo tipo dentro del 
    //     * grupo de esclavos, los bits mencionados (A3-A2-A1) se definen de manera f�sica dentro del circuito como se ver� en el proteus
    //     * Para finalizar, el ultimo bit es el bit relativo al comado de (R/W) es decir en 0 est� en modo escritura para poder escribir dentro de la memoria EEPROM
    //     * en 1 podremos leer los datos que contenga
    //     */
    //
    //    /*ENVIAMOS LAS DIRECCIONES EN DONDE DE ESCRIBIRAN LOS DATOS CORRESPONDIENTES*/
    //
    //    I2C_Escribir(0x00); /*ELEGIMOS LAS PRIMERAS DIRECCIONES DEL ESCLAVO PARA ESTE CASO EN PARTICULAR*/
    //    I2C_Escribir(0x00);
    //
    //    /*
    //     * Cabe mencionar que la direcci�n de la memoria en cuesti�n se divide en 2 registros de 1 byte 
    //     * se los llama como FIRST ADDRESS Y SECOND ADRESS
    //     */
    //
    //    /*ENVIAMOS EL DATO A ESCRIBIR*/
    //
    //    I2C_Escribir(0XAA);
    //
    //    /*Damos el comando de parada de la comunicaci�n*/
    //
    //    I2C_Detener();
    //
    //
    //    /*
    //     * LA ETAPA ANTERIOR ES PARA EL GUARDADO DE UN SOLO CARACTER EN LA EEPROM 
    //     * ACONTINUACION GUARDAREMOS EL MENSAJE DE "HOLA"     
    //     */

    I2C_Inicio(); /*Se inicializa la transferencia de datos*/
    I2C_Escribir(0b10100000); /*Se pone el ADRES propio de la EEPROM, se toma en cuenta los pines A3-A2-A1 y se coloca en modo escritura*/
    I2C_Escribir(0x00); /*Ubicamos la primera direcci�n a escribir*/
    I2C_Escribir(0x00);
    /*
     * En el modo de escritura recuencial solo hace falta dar la primera direcci�n, pues los dem�s datos se guardaran en la direcci�n siguiente a la misma
     */

    for (Variable_De_Conteo = 0; Variable_De_Conteo < 4; Variable_De_Conteo++) { /*Creamos una funci�n de conteo para poder sacar y escribir los datos guardados en la matriz "Mensaje_De_Envio"*/

        I2C_Escribir(Mensaje_De_Envio[Variable_De_Conteo]);
    }
    I2C_Detener(); /*Detenemos  la transmisi�n con el comando de parada*/


    __delay_ms(50); /*Damos un tiempo para el guardado de los datos en la EEPROM*/

    /*
     * Esta etapa consiti� en la escritura del mensaje
     */

    I2C_Inicio(); /*Damos el comando de START del protocolo de comunicaci�n*/
    I2C_Escribir(0b10100000); /*Se pone el ADRES propio de la EEPROM, se toma en cuenta los pines A3-A2-A1 y se coloca en modo escritura*/
    I2C_Escribir(0); /*Este paso es importante para poder ubicar la posici�n inicial desde la cual se proceder� a leer los datos en la EEPROM es importante ponerlo*/
    I2C_Escribir(0);

    I2C_Reinicio(); /*Damos un comando de parada y uno de inicio para dar pase a la lectura*/

    I2C_Escribir(0b10100001); /*Se pone el ADRES propio de la EEPROM, se toma en cuenta los pines A3-A2-A1 y se coloca en modo lectura*/
    /*
     * A diferencia del modo de escritura el ultimo bit del DEVICE ADDRESS es 1 lo que indica que los datos se leeran 
     */
    for (Variable_De_Conteo = 1; Variable_De_Conteo < 5; Variable_De_Conteo++) { /*Funci�n de conteo para contavilizar los datos que van a ser le�dos*/

        Tx_str(I2C_Leer()); /*Motramos por el terminar SERIAL el dato que se est� leyendo*/

        if (Variable_De_Conteo == 4) { /*Preguntamos si la variable lleg� a 4 que corresponde al n�mero de caracteres que componen el mensaje a guardar "HOLA"*/
            I2C_nack(); /*Si se cumple datos el dato de No ack para terminar el proceso de lectura*/
        } else {
            I2C_ack(); /*Si no se cumple  damos el dato ACK para seguir con el proceso de lectura*/
            __delay_ms(100); /*Damos un tiempo, que no es necesario, solo para ver como los caracteres llegan de 1 en 1 */
        }
    }
    I2C_Detener();
    while (1) {

    }

    return;
}
