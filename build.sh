#!/bin/bash

# use first cmd line arg for setting the configuration
config=$1

if [ "$config" == "" ]; then
	config="debug"
fi

# generate Makefile
premake5 gmake2

time make config=$config -r -j`nproc`
