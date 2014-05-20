/**************************************
* "uart_int.h":                       *
* Header file for Mega32 UART driver. *
* Henning Hargaard, 3/11 2011         *
***************************************/ 
#ifndef  UART_INT_H
#define UART_INT_H
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char RX_int);
unsigned char CharReady();
char ReadChar();
void SendChar(char Tegn);
void SendString(char* Streng);
void SendInteger(int Tal);
void ReadString(char* Buffer, int ID);
#endif
/**************************************/
