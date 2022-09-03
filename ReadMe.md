----Nanomsg----
gcc probe.c nanoMsg/nano_pubsub.c zeroMq/zeromq_pubsub.c pahomqtt/pahomq_pubsub.c utils/configread.c factory/handlerFactory.c -I/usr/include/libxml2 -lxml2 -lnanomsg -lczmq -lzmq -lpaho-mqtt3a -w -o output/syscall

gcc responses.c nanoMsg/nano_pubsub.c zeroMq/zeromq_pubsub.c pahomqtt/pahomq_pubsub.c utils/configread.c  factory/handlerFactory.c -I/usr/include/libxml2 -lxml2 -lnanomsg -lczmq -lzmq -lpaho-mqtt3a -w -o output/syscall_format

gcc analyze.c nanoMsg/nano_pubsub.c zeroMq/zeromq_pubsub.c pahomqtt/pahomq_pubsub.c  utils/configread.c utils/database.c factory/handlerFactory.c -lnanomsg -I/usr/include/libxml2 -lxml2 -lsqlite3 -std=c99 -lczmq -lzmq -lpaho-mqtt3a -w -o output/syscall_analyze

gcc anomaly_detection.c ../nanoMsg/nano_pubsub.c -lnanomsg -std=c99 -o anomaly

gcc probeBench.c ../utils/configread.c ../utils/database.c -lsqlite3 -I/usr/include/libxml2 -lxml2 -o bench  

sudo ./syscall server ipc:///tmp/pubsub.ipc

sudo ./syscall_format Client ipc:///tmp/pubsub.ipc Server1 ipc:///tmp/pubsub1.ipc

sudo ./syscall_analyze Client1 ipc:///tmp/pubsub1.ipc Server2 ipc:///tmp/pubsub2.ipc

sudo ./anomaly Client ipc:///tmp/pubsub2.ipc


sudo ./syscall Server tcp://localhost:1883

sudo ./syscall_format ExampleClientpub tcp://localhost:1883 ExampleClientpub tcp://localhost:1883

sudo ./syscall_analyze Client1 tcp://localhost:1883 Client1 tcp://localhost:1883 

mosquitto_sub -h localhost -t "Tracer" -p 1883
 
 
sudo ./syscall Server tcp://localhost:1883

sudo ./syscall_format ExampleClientpub tcp://localhost:1883 ExampleClientPub tcp://localhost:1883

sudo ./syscall_analyze Client1 tcp://localhost:1883 Server2 tcp://localhost:1883
----Zeromq----
gcc probe.c nanoMsg/nano_pubsub.c zeroMq/zeromq_pubsub.c utils/configread.c factory/handlerFactory.c -I/usr/include/libxml2 -lxml2 -lnanomsg -lczmq -lzmq -o output/syscall

gcc probe.c zeroMq/zeromq_pubsub.c -lczmq -lzmq -o syscallzero
sudo ./syscallzero server ipc:///tmp/pubsub.ipc

gcc responses.c zeroMq/zeromq_pubsub.c -lczmq -lzmq -o syscall_formatzero
sudo ./syscall_formatzero client ipc:///tmp/pubsub.ipc client0
 
gcc -o sqlite test_sqlite.c -lsqlite3 -std=c99

gcc anomaly_detection_ws.c ../nanoMsg/nano_pubsub.c -lnanomsg -std=c99 -o anomalyws

gcc anomaly_send.c ../nanoMsg/nano_pubsub.c -lnanomsg -std=c99 -o anomaly_send

sudo ./anomalyws client ws://127.0.0.1

sudo ./anomaly_send client ws://127.0.0.1

----PahoMqtt----
gcc probe.c pahomqtt/pahosub.c pahomqtt/mqttpaho_pub.c utils/configread.c -I/usr/include/libxml2 -lxml2  -lpaho-mqtt3c -o syscall

gcc responses.c pahomqtt/mqttpaho_pub.c pahomqtt/pahosub.c -lpaho-mqtt3c -o syscall_format

gcc analyze.c pahomqtt/pahosub.c pahomqtt/mqttpaho_pub.c utils/configread.c utils/database.c  -I/usr/include/libxml2 -lxml2 -lsqlite3 -lpaho-mqtt3c -std=c99 -o syscall_analyze




sudo ./syscall server tcp://127.0.0.1:1883

sudo ./syscall_format client tcp://127.0.0.1:1883 client0 tcp://127.0.0.2:1883

sudo ./syscall_analyze client tcp://127.0.0.2:1883 server tcp://127.0.0.3:1883



EXTRA----
paho_c_pub -t "Filter" -m "HELLo" --connection "tcp://localhost:1883"
paho_c_sub -t "Filter" --connection "tcp://localhost:1883"

-lpaho-mqtt3c
-lpaho-mqtt3a async msg


Benchmarking-----
./analyzeBench_out2 ExampleClientpub1 tcp://localhost:1883 ExampleClientPub1 tcp://localhost:1883
./analyzeBench_out1 ExampleClientpub tcp://localhost:1883 ExampleClientPub tcp://localhost:1883
./probeBench_out Server tcp://localhost:1883

./analyzeBench_out2 Client2 ipc:///tmp/pubsub.ipc Server2 ipc:///tmp/pubsub1.ipc
./analyzeBench_out1 Client ipc:///tmp/pubsub.ipc Server1 ipc:///tmp/pubsub1.ipc
./probeBench_out server ipc:///tmp/pubsub.ipc


cmake -S . -B out/build/ --target clean

make -C out/build/

/bin/sh benchi.sh

/bin/sh bench_pe_sp.sh

phoronix-test-suite benchmark pts/perl-benchmark 

sudo ./iox-roudi -c  /home/job2/Thesis/out/build/etc/iceoryx/roudi_config_example.toml

