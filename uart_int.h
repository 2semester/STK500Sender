#ifndef  UART_INT_H
#define UART_INT_H
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char RX_int);
char ReadChar();
void ReadString(char *Buffer, int ID);
#endif

