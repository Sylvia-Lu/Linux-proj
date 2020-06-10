#include "genbank.h"

int main()
{
    char filename[100];
    printf("please input your filename(path):\n");
    scanf("%s",filename);
    FILE *fp;
    fp = fopen(filename,"r");
    printf("open\n");

    int count;
    count = countCDS(fp);//统计共多少CDS
    fclose(fp);
    printf("count:%d\n",count);

    int CDS_translation_lines[count];
    //char filename[]="D:/Program_CPP/C_program/hw/CDS_test.txt";
    CDS cdsdata[count];
    read_CDS(cdsdata,filename,CDS_translation_lines);//把除translation以外的信息提取并存储
    printf("read\n");

    int i=0;//结果检查
    for(i=0;i<count;i++)
    {
        printf("%d.locus_tag:%s\tprotein_id:%s\tleft:%s\tright:%s\tend:%d\tflag:%d\n",i+1,cdsdata[i].locus_tag,cdsdata[i].protein_id,cdsdata[i].left,cdsdata[i].right,cdsdata[i].end,cdsdata[i].flag_complement);
    }

    for (i=0;i<count;i++)//提取并存储translation
    {
        FILE *fp2;
        char line2[MAXLINE];
        fp2 = fopen(filename,"r");
        int lines = 0;
        while(fgets(line2, MAXLINE, fp2) != NULL)
        {
            //printf("%s\n",line2);
            lines++;
            if (lines == CDS_translation_lines[i])
            {
                read_translation (fp2,i+1,cdsdata,line2);
                break;
            }
        }
        fclose(fp2);
    }

    return 0;
}

int countCDS (FILE *fp)//统计一共多少个CDS要提取
{
    int len;
    char line[MAXLINE];
    int count_CDS = 0;
    while (fgets(line, MAXLINE, fp) != NULL){
        len = strlen(line);
        int i=0;
        while(isspace(line[i]))//跳过开头空格
            i++;
        if (line[i]=='C' && line[i+1]=='D' && line[i+2]=='S' && isspace(line[i+3])) //判断是否为CDS
            {
                count_CDS++;
                continue;
            }
    }

    return count_CDS;
}


void read_CDS(CDS cdsdata[], char *filename, int *CDS_lines){
    FILE *fp;
    fp = fopen(filename,"r");
    int len,CDS_line=0,nlines = 0;
    int count = 0 ;
    cdsdata[count].locus_tag[0] = '\0';//初始化结构体内的值
    cdsdata[count].protein_id[0] = '\0';
    char line[MAXLINE];
    while (fgets(line, MAXLINE, fp) != NULL){
        len = strlen(line);
        nlines++;
        int i=0;
        while(isspace(line[i]))//跳过开头空格
            i++;
        if (line[i]=='C' && line[i+1]=='D' && line[i+2]=='S' && isspace(line[i+3]))//判断是否为CDS
            {
                CDS_line = nlines;
                i+=3;

                if (strcmpr(line, "complement"))
                    cdsdata[count].flag_complement = 1;
                else cdsdata[count].flag_complement = 0;

                while(!('0'<=line[i]&&line[i]<='9')){//跳过非数字
                    if(line[i]=='<')
                        cdsdata[count].end = 5;
                    else if(line[i]=='>')
                        cdsdata[count].end = 3;
                    else cdsdata[count].end = 0;

                    i++;
                }
                int j = 0;
                while('0'<=line[i]&&line[i]<='9')
                        cdsdata[count].left[j++] = line[i++];//基因起始位置
                    cdsdata[count].left[j]='\0';
                i+=2;

                int k = 0;
                while('0'<=line[i]&&line[i]<='9')
                    cdsdata[count].right[k++] = line[i++];//基因终止位置
                cdsdata[count].right[k]='\0';

                count++;
                continue;

            }

            if(strcmpr(line,"/locus_tag=") && (nlines == CDS_line+1) )
            {
                int k=0;
                while(line[k]!='"')
                    k++;
                k++;
                int j = 0;
                while(line[k]!='"')
                    cdsdata[count-1].locus_tag[j++]=line[k++];
                cdsdata[count-1].locus_tag[j]='\0';
            }

            if(strcmpr(line,"/protein_id="))
            {
                int k=0;
                while(line[k]!='"')
                    k++;
                k++;
                int j = 0;
                while(line[k]!='"')
                    cdsdata[count-1].protein_id[j++]=line[k++];
                cdsdata[count-1].protein_id[j]='\0';

            }

            if(strcmpr(line,"/translation="))
                CDS_lines[count -1]=nlines;//把translation行号存在数组里


    }
}

int strcmpr(char *s, char *t)
{
    int flag = 0;
    if (strstr(s,t) != NULL)
        flag = 1;
    return flag;
}

void read_translation (FILE * fp,int count,CDS *cdsdata,char *line)
{
    char Line[MAXLINE];
    int right = atoi(cdsdata[count-1].right);
    int left = atoi(cdsdata[count-1].left);
    char *p,temp[right-left];
    p = malloc(right-left);
    int j=0,k = 0;
    while(line[k]!='"') //跳到序列处
        k++;
    k++;
    while(line[k] != '\0') //存储第一行
        temp[j++]=line[k++];

  while(fgets(Line, MAXLINE, fp) != NULL){
    int l = 0;
    while (isspace(Line[l]))//跳过空格
        l++;
    while (Line[l]!='\0'){
        temp[j++]=Line[l++];
        if (Line[l] == '"'){
            temp[j] = '\0';
            break;}
        }
    if (Line[l] == '"'){
        temp[j] = '\0';
        break;
        }
    }
    strcpy(p,temp);
    cdsdata[count-1].translation = p;
    printf("translation:%s\n\n",cdsdata[count-1].translation);
    free(p);
}
