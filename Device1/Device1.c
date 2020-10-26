#include "publisher_main.h"
#include "../src/MQTTClient.h"
#include "subscribe_main.h"
#include"pubsub_opts.h"
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<Windows.h>

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

int CheckConsumables(char*procedure,int catheter_count)
{
    int i = catheter_count;
    if (strcmp(procedure,"cardiac\n")==0)
    {
        i--;
        if (i < 2)
        {
            print("catheter count is less");
        }
    }return i;
}

void getUserDetails(char ch, char*argvPub[], int argvPubCount,int count)
{
	char* patientName = (char*)malloc(sizeof(char) * 30);;
	char* consumables = (char*)malloc(sizeof(char) * 30);;
	char*  procedure = (char*)malloc(sizeof(char) * 30);;
    int catheter_count = count;

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
        	catheter_count = CheckConsumables(procedure,catheter_count);
		PUBLISHmain(argvPubCount, argvPub);
		printf("Do you wanr to continue? enter (Y-yes/N-No)");

		ch = getchar();
		while ((getchar()) != '\n');
	}


}

int main(int argc, char* argv[])
{


	char* argvSub[7] = { argv[0],"-t","Patient/#" ,"-i","id1","-c","tcp://mqtt.eclipse.org:1883" };
	int argvSubCount = 7;

	char* argvPub[7] = { argv[0],"-t","","-m","","-c","tcp://mqtt.eclipse.org:1883" };
	int argvPubCount = 7;

    char* a=argv[2];
    int catheter_count = atoi(a);

	char ch = 'Y';
	if (checkIfModeIsPub(argv[1]))
	{
		getUserDetails(ch, argvPub, argvPubCount,catheter_count);
	}
	else if (checkIfModeIssub(argv[1]))
	{

		SUBSCRIBEmain(argvSubCount, argvSub);
	}


	return 0;






}

