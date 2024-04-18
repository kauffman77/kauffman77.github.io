#!/bin/bash

echo Making a safety zip
make zip
mv p4-complete.zip ../safety-p4-complete.zip

echo Moving old file versions to .backup/
mkdir -p .backup
mv --backup=numbered Makefile test_* testy data data34 .backup 

echo Downloading new files
rm -f p4-update.zip
wget https://www.cs.umd.edu/~profk/216/p4-update.zip
unzip p4-update.zip
rm -f p4-update.zip

echo Project Updated
