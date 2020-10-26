import paho.mqtt.client as mqtt #import the client1
import time
import smtplib, ssl
import config

smtp_server = "smtp.gmail.com"
port = 587  # For starttls
sender_email = config.EMAIL_ADDRESS1
password = config.PASSWORD
receiver_email=config.EMAIL_ADDRESS2


########################################
def on_message(client, userdata, message):
    print("message received ",message.payload.decode("utf-8"))
    print("message topic=",message.topic)
    print("\n")
    
########################################

def CheckCatheter(catheter_count):
    if(catheter_count<3):
        context = ssl.create_default_context()
    catheter_count=str(catheter_count)
    message="No of catheters remaining is "+catheter_count
# Try to log in to server and send email
    try:
        server = smtplib.SMTP(smtp_server,port)
        server.ehlo() # Can be omitted
        server.starttls(context=context) # Secure the connection
        server.ehlo() # Can be omitted
        server.login(sender_email, password)
        server.sendmail(sender_email,receiver_email,message)
    except Exception as e:
    # Print any error messages to stdout
        print(e)
    finally:
        server.quit() 


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

if mode=="pub":
    catheter_count=int(input("Enter the number of catheters available"))
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
        if(procedure=="cardiac"):
            catheter_count-=1
            CheckCatheter(catheter_count)
        client.publish("Patient/Procedure",procedure)
        
        ch = input("Do you want to continue? enter (Y-yes/N-No)")
        
time.sleep(100) # wait
client.loop_stop() #stop the loop
