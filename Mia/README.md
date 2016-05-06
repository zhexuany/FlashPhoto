MIA application
==================
MIA support two mode. One is GUI mode which is very similar with `FlashPhoto`, but much simpler.
In addition, `MIA` support commnad line mode. You can type `./Mia -h` to know the usage of `Mia's` 
command line mode. For Mia's command line mode, input and output file or directory must be specified except `help` option.
For a user, `-i` or `-input`are two equivalent options for input file or directory. Similarly, `-o` or `-output` are 
two equivalent options for output file or directory. For other command line options, please refer the following usage of `MIA`.
```
Usage: MIA [options]
Allowed options:
  -h [ -help ]         print help message
  -i [ -input ] arg    Specified input file/directory path
  -o [ -output ] arg   Specified output file/directory path
  -e [ -edgedetect ]   Detect edge of a picture
  -c [ -compare ]      Compare two pictures. 1 means identical, 0 means
                        different
  -sharpen arg         Sharpen a picture or directory
  -t [ -thresh ] arg   Threshold an image by <float> value
  -q [ -quantize ] arg Quantize an image by <integer> value.
  -b [ -blur ] arg     Blur an image by <float> value
  -saturate arg        Saturate an image by <float> value
  -m [ -multrgb ] arg  Multiply an image by <r>,<g>,<b> value.
```
