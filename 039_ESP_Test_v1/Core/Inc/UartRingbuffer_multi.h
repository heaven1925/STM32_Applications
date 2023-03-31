/*
 * UartRingbuffer.h
 *
 *  Created on: 10-Jul-2019
 *      Author: Controllerstech
 */

#ifndef UARTRINGBUFFER_H_
#define UARTRINGBUFFER_H_


#include "stm32f4xx_hal.h"

/* change the size of the buffer */
#define UART_BUFFER_SIZE 64

typedef struct
{
  unsigned char buffer[UART_BUFFER_SIZE];
  volatile unsigned int head;
  volatile unsigned int tail;
} ring_buffer;


/* rx_buffer'daki verileri okur ve verilen UART'ın rx_buffer'daki tail sayısını artırır*/
int Uart_read(UART_HandleTypeDef *uart);

/* veriyi tx_buffer'a yazar ve tx_buffer'da head sayısını artırır*/
void Uart_write(int c, UART_HandleTypeDef *uart);

/* String'i uart'a gönderir. */
void Uart_sendstring(const char *s, UART_HandleTypeDef *uart);

/* Herhangi bir numarayı yazdırır.*/
void Uart_printbase (long n, uint8_t base, UART_HandleTypeDef *uart);

/* Ring buffer'ı başlatır. */
void Ringbuf_init(void);

void Uart_flush (UART_HandleTypeDef *uart);

/* Verilerin uart'ın rx_buffer'ında okunabilir olup olmadığını kontrol eder*/
int IsDataAvailable(UART_HandleTypeDef *uart);

/* Verilen tamponda belirli bir dizeyi arar
  * Dize bulunursa @return 1 ve bulunamazsa -1
  * @USAGE :: if (Look_for ("bir dizi", tampon)) bir şey yap
 */
int Look_for (char *str, char *buffertolookinto);

/* tail sayısını artırmadan Rx Tamponundaki verilere göz atar
* Karakteri verir
* KULLANIM: / (Uart_peek () == 'M') bir şeyler yap
*/
int Uart_peek(UART_HandleTypeDef *uart);


/* Verileri Rx arabelleğinden arabelleğe (Upto) ve girilen dizeyi dahil ederek kopyalayın
* Bu kopyalama, engelleme modunda gerçekleşeceğinden, başka hiçbir işlem gerçekleştiremeyeceksiniz
* Başarı durumunda 1, aksi takdirde -1 döndürür
* KULLANIM: while (! (Copy_Upto ("bir dizi", arabellek, uart)));
*/
int Copy_upto (char *string, char *buffertocopyinto, UART_HandleTypeDef *uart);


/* Girilen karakter sayısını (engelleme modu) belirli bir dizge algılandıktan sonra Rx arabelleğinden arabelleğe kopyalar
* Başarı durumunda 1, aksi takdirde -1 döndürür
* KULLANIM: while (! (Get_after ("bir dizi", 6, arabellek, uart)));
*/
int Get_after (char *string, uint8_t numberofchars, char *buffertosave, UART_HandleTypeDef *uart);

/* Rx Buffer'da belirli bir dizge algılanana kadar bekleyin
* Başarı durumunda 1, aksi takdirde -1 döndür
* KULLANIM: while (! (Bekle ("bir dizi", uart)));
*/
int Wait_for (char *string, UART_HandleTypeDef *uart);

/* uart için ISR. IRQ işleyicisine koyma */
void Uart_isr (UART_HandleTypeDef *huart);

/*** verilen dizgenin gelen veri içindeki konumunu al.
  * Dizenin bittiği konumu döndürür */
//int16_t Get_position (char *string, UART_HandleTypeDef *uart);


#endif /* UARTRINGBUFFER_H_ */
