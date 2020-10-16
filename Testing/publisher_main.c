

#include "MQTTClient.h"
#include "MQTTClientPersistence.h"
#include "pubsub_opts.h"
#include "ClientConnection.h"

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include"publisher_main.h"
#include"subscribe_main.h"
#include"PublisherOptions.h"

#if defined(_WIN32)
#define sleep Sleep
#else
#include <sys/time.h>
#endif

volatile int tostop = 0;


void cfinishpub(int sig)
{
	signal(SIGINT, NULL);
	tostop = 1;
}



struct pubsub_opts optspub =
{
	1, 0, 1, 0, "\n", 100,  	/* debug/app options */
	NULL, NULL, 1, 0, 0, /* message options */
	MQTTVERSION_DEFAULT, NULL, "paho-cs-pub", 0, 0, NULL, NULL, "localhost", "1883", NULL, 10, /* MQTT options */
	NULL, NULL, 0, 0, /* will options */
	0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
	0, {NULL, NULL}, /* MQTT V5 options */
};





int publishMessage(struct pubsub_opts *opts, char* buffer, MQTTClient client)
{
#if defined(_WIN32)
	signal(SIGINT, cfinishpub);
	signal(SIGTERM, cfinishpub);
//#else
//	memset(&sa, 0, sizeof(struct sigaction));
//	sa.sa_handler = cfinish;
//	sa.sa_flags = 0;
//
//	sigaction(SIGINT, &sa, NULL);
//	sigaction(SIGTERM, &sa, NULL);
#endif
	int rc;
	while (!tostop)
	{
		int data_len = 0;
		buffer = getMessage(opts->message);
		data_len = getMessageLength(opts->message);

		
		printDataLengthWhenVerboseGiven(opts->verbose, data_len);
		rc = MQTTClient_publish(client, opts->topic, data_len, buffer, opts->qos, opts->retained, NULL);
		if (opts->stdin_lines == 0)
			break;


		if (rc != 0)
		{
			myconnect(client, opts);
			rc = MQTTClient_publish(client, opts->topic, data_len, buffer, opts->qos, opts->retained, NULL);
		}

	}
	return rc;
}





int PUBLISHmain(int argc, char** argv)
{
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_createOptions createOpts = MQTTClient_createOptions_initializer;
	char* buffer = NULL;
	int rc = 0;
	char* url="";
	const char* version = NULL;
//#if !defined(_WIN32)
//	struct sigaction sa;
//#endif
//	
	

	
	setOptions(argc, argv,&optspub);
	url = getURL(&optspub);

	rc = MQTTClient_createWithOptions(&client, url, optspub.clientid, MQTTCLIENT_PERSISTENCE_NONE,
		NULL, &createOpts);
	printFailureMessageWhenClientNotCreated(rc,&optspub);



	rc = MQTTClient_setCallbacks(client, NULL, NULL, messageArrived, NULL);
	printFailureMessageWhenCallBackNotSet(rc, &optspub);
	
	if (myconnect(client, &optspub) != MQTTCLIENT_SUCCESS)
		rc = Exit(buffer, client, &optspub);


	rc=publishMessage(&optspub,buffer,client);
	


	MQTTClient_destroy(&client);

	return EXIT_SUCCESS;
}
