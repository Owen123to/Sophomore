gcc -Wall -O2 -c -o avlTree.o avlTree.c
ar -rcs libavlTree.a avlTree.o
gcc avlTreemain.c libavlTree.a -o avlTreemain -I.
avlTreemain.exe