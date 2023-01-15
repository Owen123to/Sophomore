gcc -Wall -O2 -c -o dBST.o dBST.c
ar -rcs libdBST.a dBST.o
gcc BSTmain.c libdBST.a -o BSTmain -I.
BSTmain.exe