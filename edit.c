#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "view.h"
#include "edit.h"

void edit_tag(FILE *src, char *tag_name, char *new_data)
{
    char tag[5];
    char size_buf[4];
    char flag[2];
    int size;

    FILE *temp = fopen("temp.mp3", "wb");

    if(temp == NULL)
    {
        printf("Unable to create temp file\n");
        return;
    }

    /* Copy ID3 header */
    char header[10];

    fread(header, 1, 10, src);
    fwrite(header, 1, 10, temp);

    printf("header copied\n");

    for(int i = 0; i < 6; i++)
    {
        fread(tag, 1, 4, src);
        tag[4] = '\0';

        fread(size_buf, 1, 4, src);

        size = get_size(size_buf);

        fread(flag, 1, 2, src);

        if(strcmp(tag, tag_name) == 0)
        {
            int new_size = strlen(new_data) + 1;

            char be_size[4];

            be_size[0] = (new_size >> 24) & 0xFF;
            be_size[1] = (new_size >> 16) & 0xFF;
            be_size[2] = (new_size >> 8) & 0xFF;
            be_size[3] = new_size & 0xFF;

            fwrite(tag, 1, 4, temp);
            fwrite(be_size, 1, 4, temp);
            fwrite(flag, 1, 2, temp);


            fputc(0, temp);

            fwrite(new_data, 1, strlen(new_data), temp);

            
            fseek(src, size, SEEK_CUR);
            char ch;

            while(fread(&ch, 1, 1, src))
            {
                fwrite(&ch, 1, 1, temp);
            }

            break;
        }
        else
        {
            fwrite(tag, 1, 4, temp);
            fwrite(size_buf, 1, 4, temp);
            fwrite(flag, 1, 2, temp);

            char *buffer = malloc(size);

            fread(buffer, 1, size, src);
            fwrite(buffer, 1, size, temp);

            free(buffer);
        }
    }

    fclose(src);
    fclose(temp);

    remove("sample.mp3");
    rename("temp.mp3", "sample.mp3");

    printf("Tag updated successfully\n");
}