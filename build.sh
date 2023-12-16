#!/bin/bash

# Build the project
if g++ -o bouncing_ball main.cpp -lsfml-graphics -lsfml-window -lsfml-system; then
    # Compilation succeeded, run the executable
    ./bouncing_ball
else
    # Compilation failed, display an error message
    echo "Compilation failed. Please fix the errors before running the executable."
fi
