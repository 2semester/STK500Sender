/*
 * CFile1.c
 *
 * Created: 5/6/2014 08:45:29
 *  Author: Kris
 */ 
#include "State.h"


bool firstState(char *handle)
{
	if (&handle == '!')
	return true;
	else return false;
}

bool secondState(char *getAddress)
{
	if (&getAddress == '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9' || 'a' || 'b' || 'c' || 'd' || 'e' || 'f')
	sendAddress = *getAddress;
	return true;
	else return false;
}

bool thirdState(char *getCommand)
{
	if(&getCommand == 'o' ||'f')
	sendCommand = *getCommand;
	return true;
}

void forthState(char sendAddress, char sendCommand)
{
	
}