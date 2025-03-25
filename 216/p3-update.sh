#!/bin/bash

# echo 'No updates at this time'
echo 'Creating a backup zip in ../p3-complete-backup.zip'
make zip > /dev/null
mv --backup=numbered p3-complete.zip ../p3-complete-backup.zip

echo 'Retrieving zip of updated provided files'
wget -q https://www.cs.umd.edu/~profk/216/p3-update.zip

echo 'Unpacking updated versions of provided files'
unzip -qq -o p3-update.zip
rm -f p3-update.zip

echo 'Project Update Complete'
