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
echo ./Mia -i brainstack/mrbrain-8bit023.png -o output/mrbrain-8bit023.png -c
./Mia -i brainstack/mrbrain-8bit023.png -o output/mrbrain-8bit023.png -c
echo EXPECTED 0

echo -e "\n"
echo TEST compare flag
echo COPY file first
echo cp brainstack/mrbrain-8bit024.png output/mrbrain-8bit023.png
cp brainstack/mrbrain-8bit024.png output/mrbrain-8bit023.png
sleep 1
echo ./Mia -i brainstack/mrbrain-8bit024.png -o output/mrbrain-8bit023.png -c
./Mia -i brainstack/mrbrain-8bit024.png -o output/mrbrain-8bit023.png -c
echo EXPECTED 1

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

echo -e "\n"
echo TEST all flags with directory
echo ./Mia -i brainstack -o output -m 0.1 0.1 0.1 -sharpen 5 -t 5.0 -e -saturate 5.0 -q 8 -b 5.0
./Mia -i brainstack -o output -m 0.1 0.1 0.1 -sharpen 5 -t 5.0 -e -saturate 5.0 -q 8 -b 5.0

echo -e "\n"
echo TEST all flags with a file
echo ./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -m 0.1 0.1 0.1 -sharpen 5 -t 5.0 -e -saturate 5.0 -q 8 -b 5.0
./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -m 0.1 0.1 0.1 -sharpen 5 -t 5.0 -e -saturate 5.0 -q 8 -b 5.0

echo DELETE output directory
echo rm -rf output
rm -rf output

echo -e "\n"
echo START to test bad user input
echo -e "\n"
sleep 3

echo -e "\n"
echo input file does existed
echo ./Mia -i dedede -o output
./Mia -i dedede -o output


echo -e "\n"
echo SHARPEN flag can only accpet int but type float
echo ./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -sharpen 5.0
./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -sharpen 5.0

echo -e "\n"
echo QUAT flag can only accpet int but type flaot
echo ./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -q 8.0
./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -q 8.0


echo -e "\n"
echo compare flag need two image file both existed
echo ./Mia -i brainstack/mrbrain-8bit023.png -o output/100.png -c
./Mia -i brainstack/mrbrain-8bit023.png -o output/100.png -c


sleep 2
echo -e "\n"
echo compare flag specified. Other flag does not work
echo copy file first
echo ./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png
./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png
sleep 1
echo ./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -c -e
./Mia -i brainstack/mrbrain-8bit023.png -o output/1.png -c -e
echo EXPECTED 1


sleep 2
echo -e "\n"
echo test without input or output path
echo ./Mie -e
./Mie -e
echo ./Mia -i brainstack
./Mia -i brainstack
echo ./Mia -o output
./Mia -o output

echo -e "\n"
echo END of test case.






