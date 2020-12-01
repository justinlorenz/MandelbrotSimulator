CC = gcc
CFLAGS = -lm -g

tests = colorPalette MandelMovie MandelFrame

Mandelbrot: ComplexNumber.o Mandelbrot.o MandelFrame.o
	$(CC) -o MandelFrame ComplexNumber.o Mandelbrot.o MandelFrame.o $(CFLAGS)

MandelMovie: ComplexNumber.o Mandelbrot.o MandelMovie.o ColorMapInput.o ColorOut.o
	$(CC) -o $@ ComplexNumber.o Mandelbrot.o MandelMovie.o ColorOut.o ColorMapInput.o $(CFLAGS)

colorPalette: ColorMapInput.o ColorOut.o colorPalette.o 
	$(CC) -o $@ ColorMapInput.o ColorOut.o colorPalette.o $(CFLAGS)

testA:	Mandelbrot
	./MandelFrame 2 1536 -0.7746806106269039 -0.1374168856037867 1e-5 100 student_output/MandelNorm.txt
	python3 verify.py testing/partA.txt student_output/MandelNorm.txt "MandelBrot: Given TestA"

testASimple:	Mandelbrot
	./MandelFrame 2 1536 5 3 5 2 student_output/MandelSimple.txt
	python3 verify.py testing/partASimple.txt student_output/MandelSimple.txt "MandelBrot: Given TestASimple"

memcheckA:	Mandelbrot
	valgrind --tool=memcheck --leak-check=full --dsymutil=yes --track-origins=yes ./MandelFrame 2 1536 -0.7746806106269039 -0.1374168856037867 1e-5 100 student_output/MandelNorm.txt

testB1Small: colorPalette
	./colorPalette defaultcolormap.txt student_output/colorpaletteP3Small.ppm student_output/colorpaletteP6Small.ppm 3 1,1,0,1,0,1,0,1,1
	python3 verify.py student_output/colorpaletteP3Small.ppm testing/B1SmallP3.ppm "colorPaletteP3: Given testB1Small"
	python3 verify.py student_output/colorpaletteP6Small.ppm testing/B1SmallP6.ppm "colorPaletteP6: Given testB1Small"

testB1Big: colorPalette
	./colorPalette defaultcolormap.txt student_output/colorpaletteP3Big.ppm student_output/colorpaletteP6Big.ppm 7 624,255,783,250,538,84,460,699,927,667,334,550,668,436,568,969,245,482,311,419,453,646,753,559,599,878,820,219,509,273,154,557,742,556,75,269,920,367,101,562,951,519,253,534,905,659,16,892,800
	python3 verify.py student_output/colorpaletteP3Big.ppm testing/B1BigP3.ppm "colorPaletteP3: Given testB1Big"
	python3 verify.py student_output/colorpaletteP6Big.ppm testing/B1BigP6.ppm "colorPaletteP6: Given testB1Big"

memcheckB1: colorPalette
	valgrind --tool=memcheck --leak-check=full --dsymutil=yes --track-origins=yes ./colorPalette defaultcolormap.txt student_output/colorpaletteP3Big.ppm student_output/colorpaletteP6Big.ppm 7 624,255,783,250,538,84,460,699,927,667,334,550,668,436,568,969,245,482,311,419,453,646,753,559,599,878,820,219,509,273,154,557,742,556,75,269,920,367,101,562,951,519,253,534,905,659,16,892,800

testB2:  MandelMovie
	cd student_output && rm -rf partB && mkdir partB && cd ../
	./MandelMovie 2 1536 -0.561397233777 -0.643059076016 2 1e-7 5 100 student_output/partB defaultcolormap.txt
	python3 verify.py testing/testB student_output/partB "MandelMovie: Given TestB2"

memcheckB2: MandelMovie
	valgrind --tool=memcheck --leak-check=full --dsymutil=yes --track-origins=yes ./MandelMovie 2 1536 -0.561397233777 -0.643059076016 2 1e-7 5 100 student_output/partB defaultcolormap.txt

testB2Small:  MandelMovie
	cd student_output && rm -rf testBSmall && mkdir testBSmall && cd ../
	./MandelMovie 2 1536 5 3 8 2 3 2 student_output/testBSmall defaultcolormap.txt
	python3 verify.py testing/testBSmall student_output/testBSmall "MandelMovie: Given TestB2Small"

memcheckB2Small: MandelMovie
	valgrind --tool=memcheck --leak-check=full --dsymutil=yes --track-origins=yes ./MandelMovie 2 1536 5 3 8 2 3 2 student_output/testBSmall defaultcolormap.txt

# BigTest:  MandelMovie
# 	printf "WARNING: This is a very big test that could take close to two hours to finish; if you want to have this run in the background try nohup make BigTest to run this in the backround and use top to check progress. Only do this if you are confident in your solution"
# 	./MandelMovie 2 1536 -0.561397233777 -0.643059076016 2 1e-7 576 400 student_output/BigTest defaultcolormap.txt
# 	python3 verify.py testing/BigTest student_output/BigTest

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf *.o $(tests)
