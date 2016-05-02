#!/usr/bin/env bash
MIA_TARGET=./Mia
MIA_PATH=../../Mia
echo -e "\n"
echo START to test MIA\'s command line mode..... First cd  to Mia directory
echo -e "\n"
echo cd $MIA_PATH;

sleep 1
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

sleep 1
echo -e "\n"
echo TEST edge flag
echo ./Mia -i brainstack -o output -e
./Mia -i brainstack -o output -e

echo -e "\n"
echo TEST sharpen flag
echo ./Mia -i brainstack -o output -sharpen 5
./Mia -i brainstack -o output -sharpen 5

echo -e "\n"
echo TEST thresh flag
echo ./Mia -i brainstack -o output -t 2.0
./Mia -i brainstack -o output -t 2.0


echo -e "\n"
echo TEST quantize flag
echo ./Mia -i brainstack -o output -q 8
./Mia -i brainstack -o output -q 8

echo -e "\n"
echo TEST blur  flag
echo ./Mia -i brainstack -o output -b 5.0
./Mia -i brainstack -o output -b 5.0

echo -e "\n"
echo TEST saturate flag
echo ./Mia -i brainstack -o output -saturate 5.0
./Mia -i brainstack -o output -saturate 5.0


echo -e "\n"
echo TEST multrgb flag
echo ./Mia -i brainstack -o output -m 0.1 0.1 0.1
./Mia -i brainstack -o output -m 0.1 0.1 0.1


echo -e "\n"
echo TEST compare flag
echo ./Mia -i brainstack/mrbrain-8bit023.png -o brainstack/mrbrain-8bit023.png -c
./Mia -i brainstack/mrbrain-8bit023.png -o brainstack/mrbrain-8bit023.png -c

echo -e "\n"
echo TEST compare flag
echo ./Mia -i brainstack/mrbrain-8bit023.png -o brainstack/mrbrain-8bit023.png -c
./Mia -i brainstack/mrbrain-8bit023.png -o brainstack/mrbrain-8bit024.png -c


echo -e "\n"
echo Now start to TEST combination of flags
sleep 1

echo -e "\n"
echo TEST multirgb and edge flag
echo ./Mia -i brainstack -o output -m 0.1 0.1 0.1 -e
./Mia -i brainstack -o output -m 0.1 0.1 0.1 -e


echo -e "\n"
echo  TEST multirgb and saturate flag
echo ./Mia -i brainstack -o output -m 0.1 0.1 0.1 -saturate 5.0
./Mia -i brainstack -o output -m 0.1 0.1 0.1 -saturate 5.0

echo -e "\n"
echo TEST multirgb and blur flag 
echo ./Mia -i brainstack -o output -m 0.1 0.1 0.1 -b 5.0
./Mia -i brainstack -o output -m 0.1 0.1 0.1 -b 5.0

echo -e "\n"
echo TEST multirgb and quant flag
echo ./Mia -i brainstack -o output -m 0.1 0.1 0.1 -q 8
./Mia -i brainstack -o output -m 0.1 0.1 0.1 -q 8

echo -e "\n"
echo TEST multirgb and thresh flag
echo ./Mia -i brainstack -o output -m 0.1 0.1 0.1 -t 5.0
./Mia -i brainstack -o output -m 0.1 0.1 0.1 -t 5.0


echo -e "\n"
echo TEST multirgb and sharpen flag
echo ./Mia -i brainstack -o output -m 0.1 0.1 0.1 -sharpen 5
./Mia -i brainstack -o output -m 0.1 0.1 0.1 -sharpen 5

echo TEST all flags except compare flag
echo ./Mia -i brainstack -o output -m 0.1 0.1 0.1 -sharpen 5 -t 5.0 -e -saturate 5.0 -q 8 -b 5.0
./Mia -i brainstack -o output -m 0.1 0.1 0.1 -sharpen 5 -t 5.0 -e -saturate 5.0 -q 8 -b 5.0


echo TEST all flags 
echo ./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -m 0.1 0.1 0.1 -sharpen 5 -t 5.0 -e -saturate 5.0 -q 8 -b 5.0 -c
./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -m 0.1 0.1 0.1 -sharpen 5 -t 5.0 -e -saturate 5.0 -q 8 -b 5.0 -c








echo -e "\n"
echo DELETE output directory
echo rm -rf output
rm -rf output
