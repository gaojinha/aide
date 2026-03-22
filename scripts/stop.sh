#!/bin/bash

PID=$(pidof aide)
if [ -n "$PID" ]; then
    echo "Stopping aide (PID: $PID)..."
    kill $PID
    sleep 1
else
    echo "aide is not running"
fi
