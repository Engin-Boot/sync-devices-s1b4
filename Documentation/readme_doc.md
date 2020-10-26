# Synchronize Devices

## Prerequisites:
1. If on system broker to be used then install Mosquitto x64 else online broker can also be used
2. Install Open-SSL win64 and also add the path "C:\Program Files\OpenSSL-Win64\bin\cnf.openssl.cnf" in system variables
3. Install C-Make x64 and also add the path "C:\Program Files\CMake\bin" in system variables


## Initial Steps:
1. Git-clone eclipse/paho.mqtt.c repo (Link is given in readme file of sync-devices repo)
2. Run cbuild.bat
3. Tests cases of cbuild.bat may fail; but no issues
4. Check build.paho folder present in paho.mqtt.c cloned repo. There check if some .cmake files, .h files and some folders are created or not.
5. If these files are not created then try out command ".\cbuild.bat" in visual studio terminal
6. For creating python client, refer the link present in readme file of sync-devices repo

### Note: .dll and application files should be in the same folder.

## Execution:
1. If mosquitto broker is used then mosquitto must be running in the background else skip this step.
2. Run all clients in different terminals.There are 3 devices in C and 1 device in python.
3. For C devices pass the input from command arguments in second position. (Like for subscribing pass "sub" and for publishing pass "pub")
4. For python device give input from console. (Either "sub" or "pub")
