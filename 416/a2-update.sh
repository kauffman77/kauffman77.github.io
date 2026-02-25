#!/bin/bash
AN=a2
CLASS=416

# echo 'No updates at this time'
echo 'Creating a backup zip in ../${AN}-complete-backup.zip'
make zip > /dev/null
mv --backup=numbered ${AN}-complete.zip ../${AN}-complete-backup.zip

echo 'Retrieving zip of updated provided files'
# rm -rf data/   # special case to remove the crummy data directory
wget -q https://www.cs.umd.edu/~profk/${CLASS}/${AN}-update.zip

echo 'Unpacking updated versions of provided files'
unzip -qq -o ${AN}-update.zip
rm -f ${AN}-update.zip

echo 'Update Complete'
