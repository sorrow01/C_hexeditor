#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned char byte;
    struct list *next;

}list;

list *head=NULL;

int load(char *str)
{
    list *new,*prev=NULL;
    unsigned char c;
    FILE *file;
    
    file=fopen(str,"rb");
    if (file==NULL) return -1;
    
    c=fgetc(file);

    if (head==NULL)
    {
        head=(list*)malloc(sizeof(list));
        head->byte=c;
        head->next=NULL;
        prev=head;
    }

    if (feof(file)) return 1;

    while (1)
    {
        c=fgetc(file);

        new=(list*)malloc(sizeof(list));
        new->byte=c;
        new->next=NULL;
        prev->next=new;
        prev=new;

        if (feof(file)) return 1;
    }
}

int hexshow()
{
    if (head==NULL) return -1;
    list *temp=head;
    int i=0;

    printf("\tOffset\t00   01   02   03      04   05   06   07      08   09   0A   0B      0C   0D   0E   0F\n\n\n");

    while(temp->next!=NULL)
    {
        if (i==0)
        {
            printf("\t      \t");
        }
        
        temp->byte <= 0xF ? printf("0%x   ",temp->byte) : printf("%x   ",temp->byte);

        temp=temp->next;
        i++;
        if (i==4 || i==8 || i==12 ) printf("   ");
        if (i==16)
        {
            printf("\n\n");
            i=0;
        }

    }
    printf("\n");
    if (temp==NULL) return 1;
}


int main (void)
{
    char filename[100];

    printf("Filename : ");
    scanf("%s",filename);

    if (load(filename)==-1)
    {
        printf("Error, cannot open the file (Check the filename...)");
        return -1;
    }

    if  ( hexshow() == -1 )
    {
        printf("Problem loading from memory...");
        return -1;
    }

    getchar();
    return 1;
}
