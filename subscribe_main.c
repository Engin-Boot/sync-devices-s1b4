#include "subscribe_main.h"


//change 3
void IsTopicNameGiven(int argc, char** argv, MQTTClient_nameValue* infos, const char* program_name)
{
	if (getopts(argc, argv, &opts) != 0)
		usage(&opts, (pubsub_opts_nameValue*)infos, program_name);
}


//change 11
//void ExitIfCheckConnectionIsNotSuccess(MQTTClient client)
//{
//	if (myconnect(client, &opts) != MQTTCLIENT_SUCCESS)
//		goto exit;
//}


//**********************MAIN BEGINS*************************//
//**********************MAIN BEGINS*************************//
//**********************MAIN BEGINS*************************//
//**********************MAIN BEGINS*************************//
//**********************MAIN BEGINS*************************//
int  SUBSCRIBEmain(int argc, char** argv)
{
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_createOptions createOpts = MQTTClient_createOptions_initializer;
	int rc = 0;
	char* url;
	const char* version = NULL;

	#if !defined(_WIN32)
		struct sigaction sa;
	#endif

	const char* program_name = "paho_cs_sub";
	MQTTClient_nameValue* infos = MQTTClient_getVersionInfo();

	//void argCountLessThanTwo(argc, infos, program_name);					//change 2

	//void IsTopicNameGiven( argc,  argv, infos, program_name);			//change3
	if (getopts(argc, argv, &opts) != 0)
		usage(&opts, (pubsub_opts_nameValue*)infos, program_name);

	opts.verbose = wildCardCheckInTopicName();							//change 4

	url = CheckconnectionToWhichHost();									//change 5

	void printUrlIfVerboseIsTrue(url);									//change 6

	//void settingTraceCallBackAndLevel();								//change 7

	//createOpts.MQTTVersion = setVerionEqualToFiveIfGreater();			//change 8

	rc = MQTTClient_createWithOptions(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE,
		NULL, &createOpts);

	void printMQTTClientErrorMessage(int rc);							//change 9

	void interruptAndTerminate();										//change 10

	//void ExitIfCheckConnectionIsNotSuccess(client);						//change 11
	if (myconnect(client, &opts) != MQTTCLIENT_SUCCESS)
		goto exit;

	//rc = ChangeResponseAndReasonCodeIfMqttVersionGreaterThanFive(rc,client);	//change 12
		
	rc = MQTTClient_subscribe(client, opts.topic, opts.qos);

	bool check = 0;
	check= PrintAndExitIfRcNotEqualToClientSuccessAndQos(rc);						//change 13
	if (check)
		goto exit;
	
	while (!toStop)
	{
		char* topicName = NULL;
		int topicLen;
		MQTTClient_message* message = NULL;

		rc = MQTTClient_receive(client, &topicName, &topicLen, &message, 1000);

		if (message)
		{
			//size_t delimlen = 0;

			void PrintTopicNameIfVerboseIsTrue(topicName);									//change 14

			//delimlen = SetDelimiterLength();												//change 15

			//void printPayloadlenAndPayload(message, delimlen);								//change 16
						
			printf("%.*s%s", message->payloadlen, (char*)message->payload, opts.delimiter);

			void PassingMQttpropertiesToLogProperties(message);											//change 17
			
			fflush(stdout);
			MQTTClient_freeMessage(&message);
			MQTTClient_free(topicName);
		}
		void connectClientToServer(rc, client);															//change 18
	}
exit:
	MQTTClient_disconnect(client, 0);

	MQTTClient_destroy(&client);

	return EXIT_SUCCESS;
}
