#!/bin/bash

# echo 'No updates at this time'
echo 'Creating a backup zip in ../p1-complete-backup.zip'
make zip > /dev/null
mv --backup=numbered p1-complete.zip ../p1-complete-backup.zip

# echo 'Removing provided files that will be updated'
# for f in data Makefile test_rcv_makeup.org; do
#     rm -rf $f
# done

echo 'Retrieving and unpacking new versions of provided files'
rm -rf data/   # special case to remove the crummy data directory
wget https://www.cs.umd.edu/~profk/216/p1-update.zip
unzip -qq -o p1-update.zip
rm -f p1-update.zip

echo 'Project Update Complete'
