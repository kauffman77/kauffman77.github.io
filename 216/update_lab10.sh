#!/bin/bash

url=https://www.cs.umd.edu/~profk/216

rm -f Makefile test_newer_file.org test_redirect_child.org
wget $url/Makefile
wget $url/test_newer_file.org
wget $url/test_redirect_child.org

echo LAB UPDATED
