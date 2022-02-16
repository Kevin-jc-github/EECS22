

# design names
DESIGN = PhotoLab PhotoLabTest

#libs
LIBS   = libFilter.a

CC     = gcc
DEBUG  = -DDEBUG -g
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall -lm
AR     = ar rc
RANLIB = ranlib

IMAGES = bw.ppm edge.ppm shuffle.ppm brightness.ppm hmirror.ppm hue.ppm bigresize.ppm smallresize.ppm rotate.ppm rotater.ppm saturate.ppm hflip.ppm

all: PhotoLab PhotoLabTest

Test.o: Test.c Test.h
	$(CC) $(CFLAGS) Test.c -o Test.o

Test_DEBUG.o: Test.c Test.h
	$(CC) $(CFLAGS) $(DEBUG) Test.c -o Test_DEBUG.o


Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o


FileIO.o: FileIO.h FileIO.c Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o


DIPs.o: DIPs.h DIPs.c Constants.h
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o


Advanced.o: Advanced.h Advanced.c Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o


PhotoLab.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) PhotoLab.c -o PhotoLab.o


PhotoLabTest.o: PhotoLab.c DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab.c -o PhotoLabTest.o




libFilter.a: DIPs.o Advanced.o
	$(AR) libFilter.a Advanced.o DIPs.o
	$(RANLIB) libFilter.a



PhotoLab: PhotoLab.o FileIO.o Image.o Test.o libFilter.a
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o Image.o Test.o -L. -lFilter -o PhotoLab


PhotoLabTest: PhotoLabTest.o FileIO.o Image.o Test_DEBUG.o libFilter.a
	$(CC) $(LFLAGS) PhotoLabTest.o FileIO.o Image.o Test_DEBUG.o -L. -lFilter -o PhotoLabTest

	
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)