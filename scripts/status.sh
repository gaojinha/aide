#!/bin/bash

PID=$(pidof aide)
if [ -n "$PID" ]; then
    echo "aide is running (PID: $PID)"
    ps -p $PID -o pid,vsz,comm=
else
    echo "aide is not running"
fi
