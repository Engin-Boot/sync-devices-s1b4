#include "subscribe_main.h"
#include "FileHandling.h"

#if defined(_WIN32)
#define sleep Sleep
#else
#include <sys/time.h>
#endif

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




int  SUBSCRIBEmain(int argc, char** argv)
{
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_createOptions createOpts = MQTTClient_createOptions_initializer;
	int rc = 0;
	const char* url;
	const char* version = NULL;
#if !defined(_WIN32)
	struct sigaction sa;
#endif
	const char* program_name = "paho_cs_sub";
	MQTTClient_nameValue* infos = MQTTClient_getVersionInfo();
	
	if (getopts(argc, argv, &opts) != 0)
		usage(&opts, (pubsub_opts_nameValue*)infos, program_name);

	opts.verbose = wildCardCheckInTopicName(opts);	

	url = CheckconnectionToWhichHost(opts);			


	printUrlIfVerboseIsTrue( url,opts);	

	

	rc = MQTTClient_createWithOptions(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE,
		NULL, &createOpts);
	


	printMQTTClientErrorMessage(rc,opts); 

	void interruptAndTerminate();			

	bool check = 0;

	check= CheckConnectionSuccessOrNot(client,opts);		
	

	
	check = PrintAndExitIfRcNotEqualToClientSuccessAndQos(rc,opts);				
	if (check)
		goto exit;

	rc = MQTTClient_subscribe(client, opts.topic, opts.qos);

	while (!toStop)
	{
		char* topicName = NULL;
		int topicLen;
		MQTTClient_message* message = NULL;

		rc = MQTTClient_receive(client, &topicName, &topicLen, &message, 1000);
		if (message)
		{

			printf("%s\t", topicName);

			printf("%.*s%s", message->payloadlen, (char*)message->payload, opts.delimiter);
			const char* str = message->payload;
			writeIntoCsvFile("patientDetails.csv",str,topicName);
			PassingMQttpropertiesToLogProperties(message,opts);		

			fflush(stdout);
			MQTTClient_freeMessage(&message);
			MQTTClient_free(topicName);
		}
		void connectClientToServer( rc,  client,opts);		
	}
exit:
	MQTTClient_disconnect(client, 0);

	MQTTClient_destroy(&client);

	return EXIT_SUCCESS;
}
