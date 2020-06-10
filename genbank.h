#ifndef GENBANK_H_INCLUDED
#define GENBANK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 1000
#define MAXWORD 100

typedef struct CDS{
    char locus_tag[MAXWORD];//基因名
    char protein_id[MAXWORD];

    char *translation;//蛋白序列

    char left[MAXWORD] ;
    char right[MAXWORD];

    int end;//5表示5'部分，3表示3'部分，0表示既不是5‘也不是3’

    int flag_complement;//0表示正常，1表示在互补链上。

} CDS;

int countCDS (FILE *fp);
int strcmpr(char *s, char *t);
void read_CDS(CDS cdsdata[], char *filename, int *CDS_lines);
void read_translation (FILE * fp,int count,CDS *cdsdata,char *line);


#endif // GENBANK_H_INCLUDED
