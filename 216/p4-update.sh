#!/bin/bash

# echo 'No updates at this time'
echo 'Creating a backup zip in ../p4-complete-backup.zip'
make zip > /dev/null
mv --backup=numbered p4-complete.zip ../p4-complete-backup.zip

# echo 'Removing provided files that will be updated'
# for f in data Makefile test_rcv_makeup.org; do
#     rm -rf $f
# done

echo 'Retrieving zip of updated provided files'
# rm -rf data/   # special case to remove the crummy data directory
wget -q https://www.cs.umd.edu/~profk/216/p4-update.zip

echo 'Unpacking updated versions of provided files'
unzip -qq -o p4-update.zip
rm -f p4-update.zip

echo 'Project Update Complete'
