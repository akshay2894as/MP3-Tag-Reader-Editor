#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "view.h"
#include "edit.h"

char *get_frame_id(char *option)
{
    if(strcmp(option, "-t") == 0)
        return "TIT2";

    else if(strcmp(option, "-A") == 0)
        return "TPE1";

    else if(strcmp(option, "-a") == 0)
        return "TALB";

    else if(strcmp(option, "-y") == 0)
        return "TYER";

    else if(strcmp(option, "-m") == 0)
        return "TCON";

    else if(strcmp(option, "-c") == 0)
        return "COMM";

    return NULL;
}
void display_help(void)
{
    printf("---------------------------------------------------------\n");
    printf("          MP3 TAG READER AND EDITOR FOR ID3v2\n");
    printf("---------------------------------------------------------\n\n");

    printf("VIEW TAGS:\n");
    printf("  ./a.out -r <mp3_file>\n\n");

    printf("Example:\n");
    printf("  ./a.out -r sample.mp3\n\n");

    printf("EDIT TAGS:\n");
    printf("  ./a.out -e <option> <new_value> <mp3_file>\n\n");

    printf("Available Edit Options:\n");
    printf("-------------------------------------------------\n");
    printf(" Option      Tag ID      Description\n");
    printf("-------------------------------------------------\n");
    printf("   -t        TIT2        Title\n");
    printf("   -A        TPE1        Artist\n");
    printf("   -a        TALB        Album\n");
    printf("   -y        TYER        Year\n");
    printf("   -m        TCON        Music\n");
    printf("   -c        COMM        Comment\n");
    printf("-------------------------------------------------\n\n");
}

int main(int argc, char *argv[])
{  
    if(strcmp(argv[1], "-h") == 0){
    display_help();
    return 0;
    }    
    FILE *fp;

    if(strcmp(argv[1], "-r")==0)
    { 
        fp = fopen(argv[2], "rb");
        if(fp==NULL){
            printf("Unable to open file\n");
            return 1;
        }
        view_tags(fp);
        fclose(fp);   
    }
    else if(strcmp(argv[1],"-e")==0)
    {   char *frame_id;
        frame_id = get_frame_id(argv[2]);

        if(frame_id==NULL){
            printf("Invalid edit option\n");
            return 1;
        }

        fp = fopen(argv[4], "rb");

    if(fp == NULL)
    {printf("Unable to open file\n");
    return 1;
    }
   

    edit_tag(fp,frame_id, argv[3]);
    }

    
    return 0;
}