# Evaluating Infrastructure Technologies for Automotive Intrusion Detection Systems

This repository provides a comprehensive set of examples and benchmarks for various messaging and middleware libraries including Nanomsg, ZeroMQ, Paho MQTT, Cyclone DDS, vSomeIP, and Iceoryx. It includes source code, compilation instructions, and usage examples for different scenarios.

## Table of Contents
1. [Introduction](#introduction)
2. [Requirements](#requirements)
3. [Compilation Instructions](#compilation-instructions)
4. [Execution Examples](#execution-examples)
5. [Benchmarking](#benchmarking)
6. [License](#license)

## Introduction
This project aims to demonstrate and benchmark the usage of different messaging libraries and middleware technologies. It covers:

- **Nanomsg**: A simple high-performance implementation of several "scalability protocols".
- **ZeroMQ**: A high-performance asynchronous messaging library.
- **Paho MQTT**: An Eclipse project providing scalable open-source implementations of open and standard messaging protocols aimed at new, existing, and emerging applications for M2M and IoT.
- **Cyclone DDS**: An open-source implementation of the Data Distribution Service (DDS) specification, providing low-latency data connectivity.
- **vSomeIP**: A middleware for handling inter-process communication (IPC) in automotive applications.
- **Iceoryx**: A middleware for inter-process communication, focusing on efficiency and deterministic data transfer.

## Requirements
To compile and run the examples, ensure you have the following dependencies installed:
- GCC
- Nanomsg
- ZeroMQ
- Paho MQTT
- Cyclone DDS
- vSomeIP
- Iceoryx
- SQLite3
- Libxml2

## Compilation Instructions
### Nanomsg
```sh
gcc probe.c nanoMsg/nano_pubsub.c zeroMq/zeromq_pubsub.c pahomqtt/pahomq_pubsub.c utils/configread.c factory/handlerFactory.c -I/usr/include/libxml2 -lxml2 -lnanomsg -lczmq -lzmq -lpaho-mqtt3a -w -o output/syscall

gcc responses.c nanoMsg/nano_pubsub.c zeroMq/zeromq_pubsub.c pahomqtt/pahomq_pubsub.c utils/configread.c factory/handlerFactory.c -I/usr/include/libxml2 -lxml2 -lnanomsg -lczmq -lzmq -lpaho-mqtt3a -w -o output/syscall_format

gcc analyze.c nanoMsg/nano_pubsub.c zeroMq/zeromq_pubsub.c pahomqtt/pahomq_pubsub.c utils/configread.c utils/database.c factory/handlerFactory.c -lnanomsg -I/usr/include/libxml2 -lxml2 -lsqlite3 -std=c99 -lczmq -lzmq -lpaho-mqtt3a -w -o output/syscall_analyze

gcc anomaly_detection.c ../nanoMsg/nano_pubsub.c -lnanomsg -std=c99 -o anomaly

gcc probeBench.c ../utils/configread.c ../utils/database.c -lsqlite3 -I/usr/include/libxml2 -lxml2 -o bench
```

### ZeroMQ
```sh
gcc probe.c nanoMsg/nano_pubsub.c zeroMq/zeromq_pubsub.c utils/configread.c factory/handlerFactory.c -I/usr/include/libxml2 -lxml2 -lnanomsg -lczmq -lzmq -o output/syscall

gcc probe.c zeroMq/zeromq_pubsub.c -lczmq -lzmq -o syscallzero

gcc responses.c zeroMq/zeromq_pubsub.c -lczmq -lzmq -o syscall_formatzero

gcc -o sqlite test_sqlite.c -lsqlite3 -std=c99

gcc anomaly_detection_ws.c ../nanoMsg/nano_pubsub.c -lnanomsg -std=c99 -o anomalyws

gcc anomaly_send.c ../nanoMsg/nano_pubsub.c -lnanomsg -std=c99 -o anomaly_send
```

### Paho MQTT
```sh
gcc probe.c pahomqtt/pahosub.c pahomqtt/mqttpaho_pub.c utils/configread.c -I/usr/include/libxml2 -lxml2 -lpaho-mqtt3c -o syscall

gcc responses.c pahomqtt/mqttpaho_pub.c pahomqtt/pahosub.c -lpaho-mqtt3c -o syscall_format

gcc analyze.c pahomqtt/pahosub.c pahomqtt/mqttpaho_pub.c utils/configread.c utils/database.c -I/usr/include/libxml2 -lxml2 -lsqlite3 -lpaho-mqtt3c -std=c99 -o syscall_analyze
```

## Execution Examples
### Nanomsg
```sh
sudo ./output/syscall server ipc:///tmp/pubsub.ipc
sudo ./output/syscall_format Client ipc:///tmp/pubsub.ipc Server1 ipc:///tmp/pubsub1.ipc
sudo ./output/syscall_analyze Client1 ipc:///tmp/pubsub1.ipc Server2 ipc:///tmp/pubsub2.ipc
sudo ./anomaly Client ipc:///tmp/pubsub2.ipc

sudo ./output/syscall Server tcp://localhost:1883
sudo ./output/syscall_format ExampleClientpub tcp://localhost:1883 ExampleClientpub tcp://localhost:1883
sudo ./output/syscall_analyze Client1 tcp://localhost:1883 Client1 tcp://localhost:1883

mosquitto_sub -h localhost -t "Tracer" -p 1883
sudo ./output/syscall Server tcp://localhost:1883
sudo ./output/syscall_format ExampleClientpub tcp://localhost:1883 ExampleClientPub tcp://localhost:1883
sudo ./output/syscall_analyze Client1 tcp://localhost:1883 Server2 tcp://localhost:1883
```

### ZeroMQ
```sh
sudo ./syscallzero server ipc:///tmp/pubsub.ipc
sudo ./syscall_formatzero client ipc:///tmp/pubsub.ipc client0
```

### Paho MQTT
```sh
sudo ./syscall server tcp://127.0.0.1:1883
sudo ./syscall_format client tcp://127.0.0.1:1883 client0 tcp://127.0.0.2:1883
sudo ./syscall_analyze client tcp://127.0.0.2:1883 server tcp://127.0.0.3:1883

paho_c_pub -t "Filter" -m "HELLo" --connection "tcp://localhost:1883"
paho_c_sub -t "Filter" --connection "tcp://localhost:1883"
```

## Benchmarking
```sh
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
sudo ./iox-roudi -c /home/job2/Thesis/out/build/etc/iceoryx/roudi_config_example.toml
```

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

---
