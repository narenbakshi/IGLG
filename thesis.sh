#!/bin/bash
cd out/build

#cd bin

middleware=$(grep -oP '(?<=MIDDLEWARE>)[^<]+' "/home/job2/Thesis/config.xml")
module=$(grep -oP '(?<=MODULEOPTION>)[^<]+' "/home/job2/Thesis/config.xml")
echo $middleware
echo $module

if [[ "$middleware" = "VSOMEIP" ]] && [[ "$module" = "ALL" ]]; then
gnome-terminal -e "bash -c './responses_out Client1 ipc:///tmp/pubsub1.ipc Server2 ipc:///tmp/pubsub2.ipc; sleep 3'" &
gnome-terminal -e "bash -c './analyze_out Client ipc:///tmp/pubsub.ipc Server1 ipc:///tmp/pubsub1.ipc; sleep 3'" &
gnome-terminal -e "bash -c './probe_out server ipc:///tmp/pubsub.ipc; sleep 3'" &
fi

if [[ "$middleware" = "CYCDDS" ]] && [[ "$module" = "ALL" ]]; then
gnome-terminal -e "bash -c './responses_out Client1 ipc:///tmp/pubsub1.ipc Server2 ipc:///tmp/pubsub2.ipc; sleep 3'" &
gnome-terminal -e "bash -c './analyze_out Client ipc:///tmp/pubsub.ipc Server1 ipc:///tmp/pubsub1.ipc; sleep 3'" &
gnome-terminal -e "bash -c './probe_out server ipc:///tmp/pubsub.ipc; sleep 3'" &
fi

if [[ "$middleware" = "ICEORYX" ]] && [[ "$module" = "ALL" ]]; then
gnome-terminal -e "bash -c './responses_out Client1 ipc:///tmp/pubsub1.ipc Server2 ipc:///tmp/pubsub2.ipc; sleep 3'" &
gnome-terminal -e "bash -c './analyze_out Client ipc:///tmp/pubsub.ipc Server1 ipc:///tmp/pubsub1.ipc; sleep 3'" &
gnome-terminal -e "bash -c './probe_out server ipc:///tmp/pubsub.ipc; sleep 3'" &
#gnome-terminal -e "bash -c './iox-roudi'" &
fi


if [[ "$middleware" = "ZEROMQ" ]] && [[ "$module" = "ALL" ]]; then
gnome-terminal -e "bash -c './responses_out Client1 ipc:///tmp/pubsub1.ipc Server2 ipc:///tmp/pubsub2.ipc; sleep 3'" &
gnome-terminal -e "bash -c './analyze_out Client ipc:///tmp/pubsub.ipc Server1 ipc:///tmp/pubsub1.ipc; sleep 3'" &
gnome-terminal -e "bash -c './probe_out server ipc:///tmp/pubsub.ipc; sleep 3'" &
fi


if [[ "$middleware" = "NANO" ]] && [[ "$module" = "ALL" ]] ; then
gnome-terminal -e "bash -c './responses_out Client1 ipc:///tmp/pubsub1.ipc Server2 ipc:///tmp/pubsub2.ipc; sleep 3'" &
gnome-terminal -e "bash -c './analyze_out Client ipc:///tmp/pubsub.ipc Server1 ipc:///tmp/pubsub1.ipc; sleep 3'" &
gnome-terminal -e "bash -c './probe_out server ipc:///tmp/pubsub.ipc; sleep 3'" &
fi

if [[ "$middleware" = "PAHO" ]] && [[ "$module" = "ALL" ]] ; then
gnome-terminal -e "bash -c './responses_out Client1 tcp://localhost:1883 Server2 tcp://localhost:1883; sleep 3'" &
gnome-terminal -e "bash -c './analyze_out ExampleClientpub tcp://localhost:1883 ExampleClientPub tcp://localhost:1883; sleep 3'" &
gnome-terminal -e "bash -c './probe_out Server tcp://localhost:1883; sleep 3'" &
#cd benchmarking
#gnome-terminal -e "bash -c './analyzeBench_out1 ExampleClientpub tcp://localhost:1883 ExampleClientPub tcp://localhost:1883; sleep 3'" &
#gnome-terminal -e "bash -c './probeBench_out Server tcp://localhost:1883; sleep 3'" &
fi

if [[ "$module" = "probe" ]]; then 
    if [[ "$middleware" = "ZEROMQ" ]] || [[ "$middleware" = "NANO" ]]; then
        gnome-terminal -e "bash -c './probe_out server ipc:///tmp/pubsub.ipc; sleep 3'" &
    else
        gnome-terminal -e "bash -c './probe_out Server tcp://localhost:1883; sleep 3'" &
    fi
fi

if [[ "$module" = "analyze" ]]; then 
    if [[ "$middleware" = "ZEROMQ" ]] || [[ "$middleware" = "NANO" ]]; then
        gnome-terminal -e "bash -c './analyze_out Client ipc:///tmp/pubsub.ipc Server1 ipc:///tmp/pubsub1.ipc; sleep 3'" &
    else
        gnome-terminal -e "bash -c './analyze_out ExampleClientpub tcp://localhost:1883 ExampleClientPub tcp://localhost:1883; sleep 3'" &
    fi
fi

if [[ "$module" = "responses" ]]; then 
    if [[ "$middleware" = "ZEROMQ" ]] || [[ "$middleware" = "NANO" ]]; then
        gnome-terminal -e "bash -c './responses_out Client1 ipc:///tmp/pubsub1.ipc Server2 ipc:///tmp/pubsub2.ipc; sleep 3'" &
    else
        gnome-terminal -e "bash -c './responses_out Client1 tcp://localhost:1883 Server2 tcp://localhost:1883; sleep 3'" &
    fi
fi