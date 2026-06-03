#include <stdio.h>
#include <string.h>
#include "view.h"

int get_size(char *size_buf)
{
    int size;

    size = ((unsigned char)size_buf[0] << 24) |
           ((unsigned char)size_buf[1] << 16) |
           ((unsigned char)size_buf[2] << 8)  |
           ((unsigned char)size_buf[3]);

    return size;
}

void view_tags(FILE *fp)
{
    char tag[5];
    char size_buf[4];

    int size;

    char data[1000];

    printf("---------------------------------------------------------\n");
    printf("        MP3 Tag Reader and Editor for ID3v2\n");
    printf("---------------------------------------------------------\n\n");

    
    fseek(fp, 10, SEEK_SET);

   
    for(int i = 0; i < 6; i++)
    {
        
        fread(tag, 4, 1, fp);
        tag[4] = '\0';

        
        fread(size_buf, 4, 1, fp);

        size = get_size(size_buf);

        
        fseek(fp, 3, SEEK_CUR);

        
        fread(data, size - 1, 1, fp);

        data[size - 1] = '\0';

        
        if(strcmp(tag, "TIT2") == 0)
        {
            printf("%-10s : %s\n", "Title", data);
        }
        else if(strcmp(tag, "TPE1") == 0)
        {
            printf("%-10s : %s\n", "Artist", data);
        }
        else if(strcmp(tag, "TALB") == 0)
        {
            printf("%-10s : %s\n", "Album", data);
        }
        else if(strcmp(tag, "TYER") == 0)
        {
            printf("%-10s : %s\n", "Year", data);
        }
        else if(strcmp(tag, "TCON") == 0)
        {
            printf("%-10s : %s\n", "Music", data);
        }
        else if(strcmp(tag, "COMM") == 0)
        {
            printf("%-10s : %s\n", "Composer", data);
        }
    }

    printf("\n---------------------------------------------------------\n");
}