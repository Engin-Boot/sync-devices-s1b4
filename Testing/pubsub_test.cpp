#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
extern "C"{
	
	#include "ClientConnection.h"
	#include "ClientConnectionOptions.h"
	#include "PublisherOptions.h"
	#include"publisher_main.h"
	#include"subscribe_main.h"
	#include "subscribeOptions.h"
	#include"pubsub_opts.h"
	}





TEST_CASE("when the verbose option is given then isverboseOptionEntered function reports true  ")
{
	struct pubsub_opts opts =
	{
		1, 0, 1, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, (char*)"localhost", (char*)"1883", NULL, 10, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	
	opts.verbose = 1;
	REQUIRE(isverboseOptionEntered(opts.verbose) == TRUE);

}
TEST_CASE("When the argument count,options array(argv[]) and the options structure is given "
	"then setOptions function sets the options structure")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, (char*)"localhost", (char*)"1883", NULL, 10, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	char* argvPub[5] = { (char*)"publisher",(char*)"-t",(char*)"Patient/Name",(char*)"-m",(char*)"hello" };
	int argvPubCount = 5;
	REQUIRE(setOptions(argvPubCount, argvPub, &opts) == 0);
	REQUIRE(opts.message == "hello");
}

TEST_CASE("When the connection options are given then the setConnectionOptions functions sets with corresponding options")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, (char*)"localhost", (char*)"1883", NULL, /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	opts.MQTTVersion = MQTTVERSION_DEFAULT;
	opts.keepalive = 20;
	opts.username = (char*)"Harish";
	opts.password = (char*)"Harish18";
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	SetConnectionOption(&conn_opts,&opts);
	REQUIRE(conn_opts.keepAliveInterval == 20);
	REQUIRE(conn_opts.username =="Harish");
	REQUIRE(conn_opts.password == "Harish18");
	REQUIRE(conn_opts.MQTTVersion == MQTTVERSION_DEFAULT);



}
TEST_CASE("Given the option structure with SSL connection or WSS then reports true stating connection is SSL or WSS")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, NULL, NULL,NULL, /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	opts.connection = (char*)"ssl://mqtt.eclipse.org:1883";
	REQUIRE(isConnectionIsSSLorWSS(&opts) == true);
	opts.connection = (char*)"wss://mqtt.eclipse.org:1883";
	REQUIRE(isConnectionIsSSLorWSS(&opts) == true);
}
TEST_CASE("Given the option structure with ssl options then set the given options to ssl_Options")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, NULL, NULL,(char*)"ssl://mqtt.eclipse.org:1883", /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;
	SetSSLOption(&opts, &conn_opts, &ssl_opts);
	REQUIRE(ssl_opts.verify == 1);
	opts.insecure = 1;
	SetSSLOption(&opts, &conn_opts, &ssl_opts);
	REQUIRE(ssl_opts.verify == 0);


}
TEST_CASE("when verbose as 1 and rc as 0 are given then reports true stating connection is success")
{
	int verbose = 1;
	int rc = 0;
	REQUIRE(isConnectionSuccess(verbose, rc) == true);
}
TEST_CASE("when quiet as 0 and rc as 1 are given then reports true stating connection is failed")
{
	int quiet = 0;
	int rc = 1;
	REQUIRE(isConnectionFailed(quiet, rc) == true);
}

TEST_CASE("When the Will_topic of NULL value are given then setWillTopicOption function does not sets the options structure with corresponding will options")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, (char*)"localhost", (char*)"1883", NULL, /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_willOptions will_opts = MQTTClient_willOptions_initializer;
	SetConnectionOption(&conn_opts, &opts);
	SetWillTopicOption(&opts, &conn_opts, &will_opts);
	REQUIRE(opts.will_topic == NULL);
	REQUIRE(opts.will_payload == NULL);
	



}
//publisher_main
TEST_CASE("When the  connection option is given then return the connection as URL")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, NULL, NULL,(char*)"http://eclipse", /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	REQUIRE(getURL(&opts) == "http://eclipse");
}
TEST_CASE("When the connection option is not  given then return the localhost and port  as URL")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, (char*)"localhost", (char*)"1883", NULL, /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	REQUIRE(strcmp(getURL(&opts),"localhost:1883")==0);
}
TEST_CASE("When the invalid Client Object and the options for connection are given then report 0 stating EXIT_SUCCESS")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, (char*)"localhost", (char*)"1883", NULL, /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	MQTTClient client = NULL;
	char* buffer = NULL;
	
	REQUIRE(Exit(buffer, client, &opts) == 0);

}

TEST_CASE("Given the client handle,options then create the client with corresponding options reporting 0 for succesfull creation")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, (char*)"localhost", (char*)"1883", NULL, /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	MQTTClient client;
	char* url = getURL(&opts);
	MQTTClient_createOptions createOpts = MQTTClient_createOptions_initializer;
	int rc;
	rc = MQTTClient_createWithOptions(&client,url,opts.clientid, MQTTCLIENT_PERSISTENCE_NONE,NULL, &createOpts);
	REQUIRE(rc == MQTTCLIENT_SUCCESS);
}

TEST_CASE("Given the empty(NULL) client handle and options for call back then MQTTClient_setcallBacks function reports 1 for failure ins setting callback")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, (char*)"localhost", (char*)"1883", NULL, /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	MQTTClient client=NULL;
	int rc;
	rc = MQTTClient_setCallbacks(client, NULL, NULL, messageArrived, NULL);
	REQUIRE(rc == MQTTCLIENT_FAILURE);
	
}
TEST_CASE("Given the client handle,options then make connection of client with options reporting 0 for succesfull creation")
{
	struct pubsub_opts opts =
	{
		1, 0, 0, 0, (char*)"\n", 100,  	/* debug/app options */
		NULL, NULL, 1, 0, 0, /* message options */
		/*MQTT_version*/MQTTVERSION_DEFAULT, NULL, (char*)"paho-cs-pub", 0, 0, NULL, NULL, (char*)"localhost", (char*)"1883", NULL, /*keepAliveInterval*/20, /* MQTT options */
		NULL, NULL, 0, 0, /* will options */
		0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* TLS options */
		0, {NULL, NULL}, /* MQTT V5 options */
	};
	MQTTClient client;
	char* url = getURL(&opts);
	MQTTClient_createOptions createOpts = MQTTClient_createOptions_initializer;
	int rc;
	rc = MQTTClient_createWithOptions(&client, url, opts.clientid, MQTTCLIENT_PERSISTENCE_NONE, NULL, &createOpts);
	rc = myconnect(client, &opts);
	REQUIRE(rc == MQTTCLIENT_SUCCESS);
	
}
TEST_CASE("when the options and the user details are given then report the for succesfull connection and publishing")
{
	char* argvPub[7] = {(char*)"publish",(char*)"-t",(char*)"patient/#",(char*)"-m",(char*)"henry oxford",(char*)"-c",(char*)"tcp://mqtt.eclipse.org:1883" };
	int argvPubCount = 7;

	int rc;
	rc=PUBLISHmain(argvPubCount, argvPub);
	REQUIRE(rc == 0);


}


