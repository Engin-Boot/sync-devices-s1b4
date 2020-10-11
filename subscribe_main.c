#include "subscribe_main.h"

volatile int toStop = 0;


struct pubsub_opts opts =
{
	0, 0, 1, 0, "\n", 100,  	/* debug/app options */
	NULL, NULL, 1, 0, 0, /* message options */
	MQTTVERSION_DEFAULT, NULL, "paho-cs-sub", 0, 0, NULL, NULL, "localhost", "1883", NULL, 10, /* MQTT options */
	NULL, NULL, 0, 0, /* will options */
	0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
	0, {NULL, NULL}, /* MQTT V5 options */
};





void cfinish(int sig)
{
	signal(SIGINT, NULL);
	toStop = 1;
}
//change 1
void compilationTarget()
{
#if !defined(_WIN32)
	struct sigaction sa;
#endif
}

//change 2
void argCountLessThanTwo(int argc, MQTTClient_nameValue* infos, const char* program_name)
{
	if (argc < 2)
		usage(&opts, (pubsub_opts_nameValue*)infos, program_name);
}

//change 3
void IsTopicNameGiven(int argc, char** argv, MQTTClient_nameValue* infos, const char* program_name)
{
	if (getopts(argc, argv, &opts) != 0)
		usage(&opts, (pubsub_opts_nameValue*)infos, program_name);
}

//change 4
int wildCardCheckInTopicName()
{
	if (strchr(opts.topic, '#') || strchr(opts.topic, '+'))
		return 1;
}

//Change 5
char* CheckconnectionToWhichHost()
{
	char* url;
	if (opts.connection)
		url = opts.connection;
	else
	{
		url = malloc(100);
		sprintf(url, "%s:%s", opts.host, opts.port);
	}
	return url;
}

//change 6
void printUrlIfVerboseIsTrue(char* url)
{
	if (opts.verbose)
		printf("URL is %s\n", url);
}

//change 7
void settingTraceCallBackAndLevel()
{
	if (opts.tracelevel > 0)
	{
		MQTTClient_setTraceCallback(trace_callback);
		MQTTClient_setTraceLevel(opts.tracelevel);
	}
}

//change 8
int setVerionEqualToFiveIfGreater()
{
	if (opts.MQTTVersion >= MQTTVERSION_5)
		return MQTTVERSION_5;
}

//change 9
void printMQTTClientErrorMessage(int rc)
{
	if (rc != MQTTCLIENT_SUCCESS)
	{
		if (!opts.quiet)
			fprintf(stderr, "Failed to create client, return code: %s\n", MQTTClient_strerror(rc));
		exit(EXIT_FAILURE);
	}
}


//change 10
void interruptAndTerminate()
{
#if defined(_WIN32)
	signal(SIGINT, cfinish);
	signal(SIGTERM, cfinish);
#else
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = cfinish;
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
#endif
}

//change 11
//void ExitIfCheckConnectionIsNotSuccess(MQTTClient client)
//{
//	if (myconnect(client, &opts) != MQTTCLIENT_SUCCESS)
//		goto exit;
//}


//change 12
int ChangeResponseAndReasonCodeIfMqttVersionGreaterThanFive(int rc, MQTTClient client)
{
	if (opts.MQTTVersion >= MQTTVERSION_5)
	{
		MQTTResponse response = MQTTClient_subscribe5(client, opts.topic, opts.qos, NULL, NULL);
		rc = response.reasonCode;
		MQTTResponse_free(response);
	}
	else
		rc = MQTTClient_subscribe(client, opts.topic, opts.qos);
}

//change 13
//void PrintAndExitIfRcNotEqualToClientSuccessAndQos(int rc)
//{
//	if (rc != MQTTCLIENT_SUCCESS && rc != opts.qos)
//	{
//		if (!opts.quiet)
//			fprintf(stderr, "Error %d subscribing to topic %s\n", rc, opts.topic);
//		goto exit;
//	}
//}

//change 14
void PrintTopicNameIfVerboseIsTrue(char* topicName)
{
	if (opts.verbose)
		printf("%s\t", topicName);
}

//change 15
size_t SetDelimiterLength()
{
	if (opts.delimiter)
		return strlen(opts.delimiter);
}

//change 16
void printPayloadlenAndPayload(MQTTClient_message* message, size_t delimlen)
{
	if (opts.delimiter == NULL || (message->payloadlen > delimlen &&
		strncmp(opts.delimiter, &((char*)message->payload)[message->payloadlen - delimlen], delimlen) == 0))
		printf("%.*s", message->payloadlen, (char*)message->payload);
	
}

//change 17
void PassingMQttpropertiesToLogProperties(MQTTClient_message* message)
{
	if (message->struct_version == 1 && opts.verbose)
		logProperties(&message->properties);
}

//change 18
void connectClientToServer(rc, client)
{
	if (rc != 0)
		myconnect(&client, &opts);
}


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

	void compilationTarget();											//change1

	const char* program_name = "paho_cs_sub";
	MQTTClient_nameValue* infos = MQTTClient_getVersionInfo();

	//argCountLessThanTwo
	void argCountLessThanTwo(argc, infos, program_name);					//change 2

	//IsTopicNameGiven
	//void IsTopicNameGiven( argc,  argv, infos, program_name);			//change3
	if (getopts(argc, argv, &opts) != 0)
		usage(&opts, (pubsub_opts_nameValue*)infos, program_name);

	//wildCardCheckInTopicName
	opts.verbose = wildCardCheckInTopicName();							//change 4

	//CheckconnectionToWhichHost
	url = CheckconnectionToWhichHost();									//change 5

	//printUrlIfVerboseIsTrue
	void printUrlIfVerboseIsTrue(url);									//change 6

	//settingTraceCallBackAndLevel
	void settingTraceCallBackAndLevel();								//change 7

	//setVerionEqualToFiveIfGreater
	createOpts.MQTTVersion = setVerionEqualToFiveIfGreater();			//change 8

	rc = MQTTClient_createWithOptions(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE,
		NULL, &createOpts);

	//printMQTTClientErrorMessage
	void printMQTTClientErrorMessage(int rc);							//change 9

	//interruptAndTerminate
	void interruptAndTerminate();										//change 10

	//ExitIfCheckConnectionIsNotSuccess									
	//void ExitIfCheckConnectionIsNotSuccess(client);						//change 11
	if (myconnect(client, &opts) != MQTTCLIENT_SUCCESS)
		goto exit;

	//ChangeResponseAndReasonCodeIfMqttVersionGreaterThanFive
	//rc = ChangeResponseAndReasonCodeIfMqttVersionGreaterThanFive(rc,client);	//change 12
	if (opts.MQTTVersion >= MQTTVERSION_5)
	{
		MQTTResponse response = MQTTClient_subscribe5(client, opts.topic, opts.qos, NULL, NULL);
		rc = response.reasonCode;
		MQTTResponse_free(response);
	}
	
	rc = MQTTClient_subscribe(client, opts.topic, opts.qos);


	//PrintAndExitIfRcNotEqualToClientSuccessAndQos
	//void PrintAndExitIfRcNotEqualToClientSuccessAndQos(rc);						//change 13
	if (rc != MQTTCLIENT_SUCCESS && rc != opts.qos)
	{
		if (!opts.quiet)
			fprintf(stderr, "Error %d subscribing to topic %s\n", rc, opts.topic);
		goto exit;
	}
	
	while (!toStop)
	{
		char* topicName = NULL;
		int topicLen;
		MQTTClient_message* message = NULL;

		rc = MQTTClient_receive(client, &topicName, &topicLen, &message, 1000);

		if (message)
		{
			size_t delimlen = 0;

			//PrintTopicNameIfVerboseIsTrue
			void PrintTopicNameIfVerboseIsTrue(topicName);									//change 14

			//SetDelimiterLength
			delimlen = SetDelimiterLength();												//change 15

			//printPayloadlenAndPayload		
			void printPayloadlenAndPayload(message, delimlen);								//change 16
						
			printf("%.*s%s", message->payloadlen, (char*)message->payload, opts.delimiter);

			//PassingMQttpropertiesToLogProperties
			void PassingMQttpropertiesToLogProperties(message);											//change 17
			
			fflush(stdout);
			MQTTClient_freeMessage(&message);
			MQTTClient_free(topicName);
		}

		//connectClientToServer
		void connectClientToServer(rc, client);															//change 18
	}
exit:
	MQTTClient_disconnect(client, 0);

	MQTTClient_destroy(&client);

	return EXIT_SUCCESS;
}
