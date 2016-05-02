#!/usr/bin/env bash
MIA_TARGET=./Mia
MIA_PATH=../../Mia
echo -e "\n"
echo START to test MIA\'s command line mode..... First cd  to Mia directory
echo -e "\n"
echo cd $MIA_PATH;

echo -e "\n"
cd $MIA_PATH;
echo Now It is time to build Mia from source
cd $MIA_PATH;
make

echo -e "\n"
sleep 1
echo TEST help flag: -h
echo ./Mia -h
./Mia -h
echo ./Mia -help
./Mia -help

echo -e "\n"
echo TEST input and output flag
echo ./Mia -i brainstack -o output
./Mia -i brainstack -o output
rc=$?
if [[ $rc != 0 ]];
then echo ERROR on input or output flag;
fi


