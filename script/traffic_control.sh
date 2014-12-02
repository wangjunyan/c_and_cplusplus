#!/bin/bash
#
#  kbit: Kilobits per second
#  mbit: Megabits per second
#

# Name of the traffic control command.
TC=/system/bin/tc

# The network interface we're planning on limiting bandwidth.
IF=wlan0

# Download limit
DNLD=32kbit

# Upload limit
UPLD=32kbit

# IP address of the machine we are controlling
IP=172.16.0.14

# Filter options for limiting the intended interface.
U32="$TC filter add dev $IF protocol ip parent 1:0 prio 1 u32"

start() {
    $TC qdisc add dev $IF root handle 1: htb default 30
    $TC class add dev $IF parent 1: classid 1:1 htb rate $DNLD
    $TC class add dev $IF parent 1: classid 1:2 htb rate $UPLD
    $U32 match ip dst $IP/32 flowid 1:1
    $U32 match ip src $IP/32 flowid 1:2
}

stop() {
    $TC qdisc del dev $IF root
}

show() {
    $TC -s qdisc ls dev $IF
}

case "$1" in

  start)
    IF=$2
    IP=$3
    DNLD=$4
    UPLD=$5
    echo -n "Starting bandwidth shaping: "
    start
    echo "done"
    ;;

  stop)
    IF=$2
    echo -n "Stopping bandwidth shaping: "
    stop
    echo "done"
    ;;

  show)
    IF=$2
    echo "Bandwidth shaping status for $IF:"
    show
    echo ""
    ;;

  *)

    pwd=$(pwd)
    echo "Usage: tc.bash {start|stop|restart|show}"
    ;;

esac

exit 0
