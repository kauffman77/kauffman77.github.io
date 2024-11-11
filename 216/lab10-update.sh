#!/bin/bash

url=https://www.cs.umd.edu/~profk/216/lab10-update.zip

rm -f Makefile test_newer_file.org test_redirect_child.org
wget $url
unzip lab10-update.zip
rm -f lab10-update.zip
echo LAB UPDATED
