#ifndef GENBANK_H_INCLUDED
#define GENBANK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 1000
#define MAXWORD 100

typedef struct CDS{
    char locus_tag[MAXWORD];//������
    char protein_id[MAXWORD];

    char *translation;//��������

    char left[MAXWORD] ;
    char right[MAXWORD];

    int end;//5��ʾ5'���֣�3��ʾ3'���֣�0��ʾ�Ȳ���5��Ҳ����3��

    int flag_complement;//0��ʾ������1��ʾ�ڻ������ϡ�

} CDS;

int countCDS (FILE *fp);
int strcmpr(char *s, char *t);
void read_CDS(CDS cdsdata[], char *filename, int *CDS_lines);
void read_translation (FILE * fp,int count,CDS *cdsdata,char *line);


#endif // GENBANK_H_INCLUDED
