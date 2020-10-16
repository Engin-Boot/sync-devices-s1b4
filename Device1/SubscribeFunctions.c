#include "subscribe_main.h"

 
int wildCardCheckInTopicName(struct pubsub_opts opts)
{
	if (strchr(opts.topic, '#') || strchr(opts.topic, '+'))
		return 1;
	return 0;
}
//Change 5
char* CheckconnectionToWhichHost(struct pubsub_opts opts)
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

//change 11
bool CheckConnectionSuccessOrNot(MQTTClient client, struct pubsub_opts opts)
{
	if (myconnect(client, &opts) != MQTTCLIENT_SUCCESS)
		return 1;
	return 0;
}
