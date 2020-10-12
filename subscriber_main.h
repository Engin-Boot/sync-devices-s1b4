#if !defined(SUBSCRIBE_MAIN_H)
#define SUBSCRIBE_MAIN_H

#pragma once

#include "MQTTClient.h"
#include "MQTTClientPersistence.h"
#include "pubsub_opts.h"
#include "ClientConnection.h"
#include"TraceCallBacks.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

#if defined(_WIN32)
#define sleep Sleep
#else
#include <sys/time.h>
#endif

struct pubsub_opts opts =
{
	0, 0, 1, 0, "\n", 100,  	/* debug/app options */
	NULL, NULL, 1, 0, 0, /* message options */
	MQTTVERSION_DEFAULT, NULL, "paho-cs-sub", 0, 0, NULL, NULL, "localhost", "1883", NULL, 10, /* MQTT options */
	NULL, NULL, 0, 0, /* will options */
	0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
	0, {NULL, NULL}, /* MQTT V5 options */
};

volatile int toStop = 0;

void cfinish(int sig)
{
	signal(SIGINT, NULL);
	toStop = 1;
}

//change 2
//void argCountLessThanTwo(int argc, MQTTClient_nameValue* infos, const char* program_name)
//{
//	if (argc < 2)
//		usage(&opts, (pubsub_opts_nameValue*)infos, program_name);
//}

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
//void settingTraceCallBackAndLevel()
//{
//	if (opts.tracelevel > 0)
//	{
//		MQTTClient_setTraceCallback(trace_callback);
//		MQTTClient_setTraceLevel(opts.tracelevel);
//	}
//}

//change 8
//int setVerionEqualToFiveIfGreater()
//{
//	if (opts.MQTTVersion >= MQTTVERSION_5)
//		return MQTTVERSION_5;
//}

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

//change 12
//int ChangeResponseAndReasonCodeIfMqttVersionGreaterThanFive(int rc, MQTTClient client)
//{
//	if (opts.MQTTVersion >= MQTTVERSION_5)
//	{
//		MQTTResponse response = MQTTClient_subscribe5(client, opts.topic, opts.qos, NULL, NULL);
//		rc = response.reasonCode;
//		MQTTResponse_free(response);
//	}
//	else
//		rc = MQTTClient_subscribe(client, opts.topic, opts.qos);
//}

//change 13
bool PrintAndExitIfRcNotEqualToClientSuccessAndQos(int rc)
{
	if (rc != MQTTCLIENT_SUCCESS && rc != opts.qos)
	{
		if (!opts.quiet)
			fprintf(stderr, "Error %d subscribing to topic %s\n", rc, opts.topic);
		return true;
	}
	return false;
}

//change 14
void PrintTopicNameIfVerboseIsTrue(char* topicName)
{
	if (opts.verbose)
		printf("%s\t", topicName);
}

//change 15
//size_t SetDelimiterLength()
//{
//	if (opts.delimiter)
//		return strlen(opts.delimiter);
//}

//change 16
//void printPayloadlenAndPayload(MQTTClient_message* message, size_t delimlen)
//{
//	if (opts.delimiter == NULL || (message->payloadlen > delimlen &&
//		strncmp(opts.delimiter, &((char*)message->payload)[message->payloadlen - delimlen], delimlen) == 0))
//		printf("%.*s", message->payloadlen, (char*)message->payload);
//}

//change 17
void PassingMQttpropertiesToLogProperties(MQTTClient_message* message)
{
	if (message->struct_version == 1 && opts.verbose)
		logProperties(&message->properties);
}

//change 18
void connectClientToServer(int rc, MQTTClient client)
{
	if (rc != 0)
		myconnect(&client, &opts);
}


int SUBSCRIBEmain(int argc, char** argv);
#endif
