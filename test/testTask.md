The basic requirement is that `make all` can all all the tests. If test fail, then print
error message. 

Test each interactive tools in `FlashPhotoApp` to make sure it producers an expected
result when the brush is moved along a pre-defined path.

Test each filter tool in `FlashPhotoApp` to make sure it produces the expected output
for some known test input image.

Test the command line options for Mia to make sure a varitey of command line options 
are hanldes correctly, including bad user input.

At least one test cases is written via Makefile

key point for testing => fake user input.

calling the tool's `applyToCanvas` methods repeatlly according to some pattern of
movement. After calling, `FlashPhotoApp` will produce a modified PixelBuffer. We can 
save it and compare it with pre-saved image.

In total, we have 
    FlashPhotoApp:
        Interactive tool:
            Blur
            Stamp
            Pen
            Highlighter
            Crayon
            WaterColor
            ImageHandler
            CalligraphyPen
            FillTool
            SprayCan
            Eraser
        Filter tool:
            Blur
            Motion Blur
            Sharpen
            Threshold
            Saturate
            Edgedetect 
            Quantize
            Special

For all tool, we need save the modifeed buffer and check with pre-saved pictures. 
A lot of work.


          

        
