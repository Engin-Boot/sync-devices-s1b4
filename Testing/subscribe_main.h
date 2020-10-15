
#if !defined(SUBSCRIBE_MAIN_H)
#define SUBSCRIBE_MAIN_H
#include"pubsub_opts.h"
#include "MQTTClient.h"
#include "MQTTClientPersistence.h"
#include "pubsub_opts.h"
#include "ClientConnection.h"

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>


int wildCardCheckInTopicName(struct pubsub_opts opts);
char* CheckconnectionToWhichHost(struct pubsub_opts opts);
void printUrlIfVerboseIsTrue(const char* url, struct pubsub_opts opts);
void printMQTTClientErrorMessage(int rc, struct pubsub_opts opts);
bool CheckConnectionSuccessOrNot(MQTTClient client, struct pubsub_opts opts);
void interruptAndTerminate();
bool PrintAndExitIfRcNotEqualToClientSuccessAndQos(int rc, struct pubsub_opts opts);
void PassingMQttpropertiesToLogProperties(MQTTClient_message* message, struct pubsub_opts opts);
void connectClientToServer(int rc, MQTTClient client, struct pubsub_opts opts);
int SUBSCRIBEmain(int argc, char** argv);
#endif
