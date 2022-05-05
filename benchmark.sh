#! /bin/bash


for((i=0;i<6000;i++))
do
    nohup telnet 127.0.0.1 8010 &
    echo $i
done