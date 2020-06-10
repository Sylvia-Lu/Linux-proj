//writefasta.c
#include "fasta.h"
void writefasta(char *gene,char *protein_id,int flag,int flag_complement,char *translation){
	FILE *fp;

	strcat(gene,".fasta");
	if((fp = fopen(gene,"w")) == NULL){
		printf("Error:The file is not exist.");
		exit(1);
	}

	strtok(gene,".");
	fputs(">",fp);
	fputs("gene:",fp);
	fputs(gene,fp);

	if(protein_id != NULL){
		fputs("\tprotein_id:",fp);
		fputs(protein_id,fp);
	}
	if(flag != 0){
		if(flag == 3)
                fputs("\tend:3'",fp);
		if(flag == 5)
                fputs("\tend:5'",fp);
        }
	if(flag_complement == 0){
                fputs("\tnot complentmentary chain",fp);
        }
	if(flag_complement == 1){
                fputs("\tcomplementary chain:",fp);
        }

	fputs("\n",fp);
	fputs(translation,fp);

	fclose(fp);
}

//fasta.h
#ifndef __FASTA__
#define __FASTA__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writefasta(char *gene,char *protein_id,int flag,int flag_complement,char *transportation);

#endif
