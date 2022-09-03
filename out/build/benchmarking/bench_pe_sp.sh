#!/bin/bash
#!/bin/bash

#cd bin


#gnome-terminal -e "bash -c './analyzeBench_out10 ClientBench10 ipc:///tmp/pubsub.ipc ServerBench9 ipc:///tmp/pubsub1.ipc; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out9 ClientBench9 ipc:///tmp/pubsub.ipc ServerBench9 ipc:///tmp/pubsub1.ipc; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out8 ClientBench8 ipc:///tmp/pubsub.ipc ServerBench8 ipc:///tmp/pubsub1.ipc; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out7 ClientBench7 ipc:///tmp/pubsub.ipc ServerBench7 ipc:///tmp/pubsub1.ipc; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out6 ClientBench6 ipc:///tmp/pubsub.ipc ServerBench6 ipc:///tmp/pubsub1.ipc; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out5 ClientBench5 ipc:///tmp/pubsub.ipc ServerBench5 ipc:///tmp/pubsub1.ipc; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out4 ClientBench4 ipc:///tmp/pubsub.ipc ServerBench4 ipc:///tmp/pubsub1.ipc; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out3 ClientBench3 ipc:///tmp/pubsub.ipc ServerBench3 ipc:///tmp/pubsub1.ipc; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out2 ClientBench2 ipc:///tmp/pubsub11.ipc ServerBench2 ipc:///tmp/pubsub2.ipc; sleep 3'" &
gnome-terminal -e "bash -c './analyzeBench_out1 ClientBench1 ipc:///tmp/pubsub11.ipc ServerBench1 ipc:///tmp/pubsub2.ipc; sleep 3'" &
gnome-terminal -e "bash -c './probeBench_out serverBench ipc:///tmp/pubsub11.ipc; sleep 3'" &


#if [[ "$middleware" = "PAHO" ]] && [[ "$module" = "ALL" ]] ; then
#cd benchmarking
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench10 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench9 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench8 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench7 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench6 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench5 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench4 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench3 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench2 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientBench1 tcp://localhost:1883 ExampleClientBench1 tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './probeBench_out ServerBench tcp://localhost:1883; sleep 3'" &
#fi