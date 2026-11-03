#!/bin/bash

# Define cleanup handler
cleanup() {
  echo -e "\nCaught Ctrl+C. Terminating ROS 2 nodes..."
  
  # Terminate the publisher and subscriber using their saved PIDs
  kill $PUB_PID $SUB_PID 2>/dev/null
  
  # Wait for processes to fully exit
  wait $PUB_PID $SUB_PID 2>/dev/null
  
  echo "All processes cleaned up. Exiting."
  exit 0
}

# Trap SIGINT (Ctrl+C) and SIGTERM
trap 'cleanup' SIGINT SIGTERM

# Launch the publisher node in the background and capture its PID
ros2 run ros2_fundamentals_examples py_minimal_publisher.py &
PUB_PID=$!

sleep 1

# Launch the subscriber node in the background and capture its PID
ros2 run ros2_fundamentals_examples py_minimal_subscriber.py &
SUB_PID=$!

# Keep the script running and waiting for background jobs to finish
# This allows the trap to successfully catch Ctrl+C
wait