#include "genbank.h"
#include "fasta.h"

int main()
{
    char filename[100];
    printf("please input your filename(path):\n");
    scanf("%s",filename);
    FILE *fp;
    fp = fopen(filename,"r");
    printf("open\n");

    int count;
    count = countCDS(fp);//ͳ�ƹ�����CDS
    fclose(fp);
    printf("count:%d\n",count);

    int CDS_translation_lines[count];
    CDS cdsdata[count];
    read_CDS(cdsdata,filename,CDS_translation_lines);//�ѳ�translation�������Ϣ��ȡ���洢
    printf("read\n");

    int i=0;//������
    for(i=0;i<count;i++)
    {
        printf("%d.locus_tag:%s\tprotein_id:%s\tleft:%s\tright:%s\tend:%d\tflag:%d\n",i+1,cdsdata[i].locus_tag,cdsdata[i].protein_id,cdsdata[i].left,cdsdata[i].right,cdsdata[i].end,cdsdata[i].flag_complement);
    }

    for (i=0;i<count;i++)//��ȡ���洢translation
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

    writefasta(filename,cdsdata,count);

    return 0;
}
