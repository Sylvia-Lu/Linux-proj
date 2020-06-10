main : main.c libgenbank.so libfasta.so fasta.h main.c
	gcc main.c -o main
test :
	./main
clean :
	rm main 
