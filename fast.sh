#!/bin/bash

nevent=500000
for RunNumber in 99 109; do
 # for Ele_field in 203 204 205; do
        ./bin/Darwin-clang/musrSim ${RunNumber}.mac &> ${RunNumber}.log &
        sleep 0.5
        echo "Run ${RunNumber} submitted successfully! ${nevent} events will be generated!" 
done
