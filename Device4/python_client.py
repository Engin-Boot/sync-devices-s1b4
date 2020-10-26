import paho.mqtt.client as mqtt #import the client1
import time

########################################
def on_message(client, userdata, message):
    print("message received ",message.payload.decode("utf-8"))
    print("message topic=",message.topic)
    print("\n")
    
########################################

broker_address="mqtt.eclipse.org"
#broker_address="test.mosquitto.org"
#broker_address="iot.eclipse.org"
print("creating new instance")
client = mqtt.Client("P1") #create new instance
client.on_message=on_message #attach function to callback
print("connecting to broker")
client.connect(broker_address,1883,10) #connect to broker
client.loop_start() #start the loop

ch = 'Y'
mode = input("Enter sub or pub")

if mode == "sub" :
 print("Subscribing to topic")
 print("\n")
 client.subscribe("Patient/#")

while ch == 'Y' :
    if mode == "pub" :
        print("Publishing message to topic")
        print("\n")
        patientName = input("Enter the PatientName:")
        client.publish("Patient/Name",patientName)
    
        print("\n")
        consumables = input("Enter the Consumables Used:")
        client.publish("Patient/Consumables",consumables)
    
        print("\n")
        procedure = input("Enter the Procedure:")
        client.publish("Patient/Procedure",procedure)
        
        ch = input("Do you want to continue? enter (Y-yes/N-No)")
        
time.sleep(100) # wait
client.loop_stop() #stop the loop
