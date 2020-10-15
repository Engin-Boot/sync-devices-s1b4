#include"PublisherOptions.h"
#include"ClientConnection.h"
#include"publisher_main.h"

char* getURL(struct pubsub_opts *optspub)
{
	char *url=NULL;
	if (optspub->connection)
		url = optspub->connection;
	else
	{
		url = malloc(100);
		sprintf(url, "%s:%s", optspub->host, optspub->port);
		
	}
	return url;

}
int  Exit(char* buffer, MQTTClient client, struct pubsub_opts *opts)
{
	int rc;
	if (opts->filename || opts->stdin_lines)
		free(buffer);
	rc = MQTTClient_disconnect(client, 0);

	MQTTClient_destroy(&client);

	return EXIT_SUCCESS;
}
void printURLWhenVerboseSpecified(char* url, int verbose)
{
	if (verbose)
		printf("URL is %s\n", url);
}

int messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* m)
{
	return 1;
}
void printFailureMessageWhenClientNotCreated(int rc, struct pubsub_opts *opts)
{
	if (rc != MQTTCLIENT_SUCCESS)
	{
		if (!(opts->quiet))
			fprintf(stderr, "Failed to create client, return code: %s\n", MQTTClient_strerror(rc));
		exit(EXIT_FAILURE);
	}
}
void printFailureMessageWhenCallBackNotSet(int rc, struct pubsub_opts *opts)
{
	if (rc != MQTTCLIENT_SUCCESS)
	{
		if (!opts->quiet)
			fprintf(stderr, "Failed to set callbacks, return code: %s\n", MQTTClient_strerror(rc));
		exit(EXIT_FAILURE);
	}

}
int  setOptions(int argc, char*argv[],  struct pubsub_opts *opts)
{
	return(getopts(argc, argv, opts) != 0);
		

}

void printDataLengthWhenVerboseGiven(int verbose, int data_len)
{
	if (verbose)
	{
		fprintf(stderr, "Syncing the  data of length %d with other vendors \n", data_len);
	}
}


char* getMessage(char* message)
{
	if (message)
		return message;
	return NULL;
}
int  getMessageLength(char* message)
{
	int data_len = 0;
	if (message)
	{
		data_len = (int)strlen(message);
	}

	return data_len;
}

