#if !defined(PUBLISHEROPTIONS_H)
#define PUBLISHEROPTIONS_H

#include"MQTTClient.h"
#include"pubsub_opts.h"
#include <stdlib.h>

char* getURL(struct pubsub_opts *optspub);
int  Exit(char* buffer, MQTTClient client, struct pubsub_opts *opts);
int  setOptions(int argc, char*argv[], struct pubsub_opts *opts);
int publishMessage(struct pubsub_opts *opts, char* buffer, MQTTClient client);
void printDataLengthWhenVerboseGiven(int verbose, int data_len);
char* getMessage(char* message);
int getMessageLength(char* message);
int messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* m);
void printFailureMessageWhenClientNotCreated(int rc, struct pubsub_opts *opts);
void printFailureMessageWhenCallBackNotSet(int rc, struct pubsub_opts *opts);
void printURLWhenVerboseSpecified(char* url, int verbose);
int publishMessage(struct pubsub_opts *opts,char* buffer,MQTTClient client);

#endif
