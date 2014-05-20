/*
 * IncFile1.h
 *
 * Created: 19-May-14 15:40:56
 *  Author: Kris
 */ 
#ifndef INCFILE1_H_
#define INCFILE1_H_
void InitAtmel(void);
int convertToBinary(char *Buffer);
void SendByte(int convertToBinary);
void CTCBurst(void);
void switchSetCTC(void);
void Send_1(void);
void Send_0(void);
void Burst();
#endif