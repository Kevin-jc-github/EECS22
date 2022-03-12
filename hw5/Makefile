#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2022
#
# Initial author: Tim Schmidt
#  New	author: Kevin Zhu
# Makefile: Makefile for HW 5
#  Date: 	2022/03/01	
#######################################################################

all: MovieLab

######################### Generate object files #######################

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -ansi -std=c11 -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -Wall -ansi -std=c11 -c DIPs.c -o DIPs.o

Image.o: Image.c Image.h Constants.h
	gcc -Wall -ansi -std=c11 -c Image.c -o Image.o

ImageList.o: ImageList.c ImageList.h Constants.h
	gcc -Wall -ansi -std=c11 -c ImageList.c -o ImageList.o

Movie.o: Movie.c Movie.h Constants.h
	gcc -Wall -ansi -std=c11 -c Movie.c -o Movie.o

######################### Generate the executable #####################

MovieLab: FileIO.o DIPs.o Image.o ImageList.o Movie.o MovieLab.o
	gcc -Wall -ansi -std=c11 FileIO.o DIPs.o Image.o ImageList.o Movie.o MovieLab.o -o MovieLab

###############################  others  ##############################

clean:
	rm -f *.o
	rm -rf *o MovieLab