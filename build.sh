#!/bin/bash
rm -rf bin
mkdir bin
cmake -B bin -S .
cd bin
make
