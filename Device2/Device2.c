#include "publisher_main.h"
#include "MQTTClient.h"
#include "subscribe_main.h"
#include"pubsub_opts.h"
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


bool checkIfModeIsPub(char* mode)
{
	if (strcmp(mode, "pub") == 0)
		return true;
	return false;
}
bool checkIfModeIssub(char* mode)
{
	if (strcmp(mode, "sub") == 0)
		return true;
	return false;
}


void getUserDetails(char ch, char*argvPub[], int argvPubCount)
{
	char* patientName = (char*)malloc(sizeof(char) * 30);;
	char* consumables = (char*)malloc(sizeof(char) * 30);;
	char*  procedure = (char*)malloc(sizeof(char) * 30);;

	while (ch == 'Y')
	{
		printf("Enter the PatientName:");
		fgets(patientName, 30, stdin);
		argvPub[2] = "Patient/Name";
		argvPub[4] = patientName;
		PUBLISHmain(argvPubCount, argvPub);
		printf("Enter the Consumables Used:");
		fgets(consumables, 30, stdin);
		argvPub[2] = "Patient/Consumables";
		argvPub[4] = consumables;
		PUBLISHmain(argvPubCount, argvPub);
		printf("Enter the Procedure:");
		fgets(procedure, 30, stdin);
		argvPub[2] = "Patient/Procedure";
		argvPub[4] = procedure;
		PUBLISHmain(argvPubCount, argvPub);
		printf("Do you wanr to continue? enter (Y-yes/N-No)");

		ch = getchar();
		while ((getchar()) != '\n');
	}


}

int main(int argc, char* argv[])
{


	char* argvSub[7] = { argv[0],"-t","Patient/#" ,"-i","id12","-c","tcp://mqtt.eclipse.org:1883" };
	int argvSubCount = 7;

	char* argvPub[7] = { argv[0],"-t","","-m","","-c","tcp://mqtt.eclipse.org:1883" };
	int argvPubCount = 7;


	char ch = 'Y';
	if (checkIfModeIsPub(argv[1]))
	{
		getUserDetails(ch, argvPub, argvPubCount);
	}
	else if (checkIfModeIssub(argv[1]))
	{

		SUBSCRIBEmain(argvSubCount, argvSub);
	}


	return 0;






}
