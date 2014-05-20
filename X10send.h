/*
 * IncFile1.h
 *
 * Created: 19-May-14 15:40:56
 *  Author: Kris
 */ 
#ifndef X10SEND_H
#define X10SEND_H
void InitAtmel(void);
int convertToBinary(char *Buffer);
void SendByte(int convertToBinary);
void CTCBurst(void);
void switchSetCTC(void);
void Send_1(void);
void Send_0(void);
void Burst();
#endif 