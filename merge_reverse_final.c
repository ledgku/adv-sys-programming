/********************************************************
*  ÍKookmin University
*   Advanced System Programming
*   
*   Assignment 1
*   Computer Science 20093319 DongkyuLee
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>

#define FILE_MAX_SIZE (1024*1024*100)

size_t fsize(const char* fname);
char *strrev(char *str);

int main(int argc, char *argv[])
{
    FILE *file1, *file2, *fout;
    long line1 = 0, line2 = 0, lineout = 0;
    struct timeval before, after;
    int duration;
    int ret = 1;
    char *str1, *token1, *saveptr1;
    char *str2, *token2, *saveptr2;
    unsigned char *buf_file1 = 0, *buf_file2 = 0;
    size_t file1_size, file2_size;

    if (argc != 4) {
        fprintf(stderr, "usage: %s file1 file2 fout\n", argv[0]);
        goto leave0;
    }

    if ((file1_size = fsize(argv[1])) > FILE_MAX_SIZE) {
        fprintf(stderr, "error: %s size is greater than %d bytes\n", argv[1], FILE_MAX_SIZE);
	goto leave0;
    }
    if ((file2_size = fsize(argv[2])) > FILE_MAX_SIZE) {
        fprintf(stderr, "error: %s size is greater than %d bytes\n", argv[2], FILE_MAX_SIZE);
	goto leave0;
    }
    if ((file1 = fopen(argv[1], "rt")) == NULL) {
        perror(argv[1]);
        goto leave0;
    }
    if ((file2 = fopen(argv[2], "rt")) == NULL) {
        perror(argv[2]);
        goto leave1;
    }
    if ((fout = fopen(argv[3], "wt")) == NULL) {
        perror(argv[3]);
        goto leave2;
    }

    gettimeofday(&before, NULL);

    buf_file1 = (char *) malloc(file1_size);
    buf_file2 = (char *) malloc(file2_size);

    if (fread(buf_file1, 1, file1_size, file1) < 1)
    {
        goto leave2;
    }

    if (fread(buf_file2, 1, file2_size, file2) < 1)
    {
        goto leave2;
    }

    for (str1=buf_file1, str2=buf_file2; ;str1=NULL, str2=NULL)
    {
        token1 = strtok_r(str1, "\n", &saveptr1);
        token2 = strtok_r(str2, "\n", &saveptr2);
        
        if (token1 != NULL)
        {
            fprintf(fout, "%s\n", strrev(token1));
            ++line1;
        }
        if (token2 != NULL)
        {
            fprintf(fout, "%s\n", strrev(token2));
            ++line2;
            continue;
        }
        if (token1 == NULL && token2 == NULL)
        {
            break;
        }
    }

    gettimeofday(&after, NULL);

    free(buf_file1);
    free(buf_file2);

    lineout = line1 + line2;

    duration = (after.tv_sec - before.tv_sec) * 1000000 + (after.tv_usec - before.tv_usec);
    printf("Processing time = %d.%06d sec\n", duration / 1000000, duration % 1000000);
    printf("File1 = %ld, File2= %ld, Total = %ld Lines\n", line1, line2, lineout);
    ret = 0;

leave3:
    fclose(fout);
leave2:
    fclose(file2);
leave1:
    fclose(file1);
leave0:
    return ret; 
}

/* return filesize(byte) */
size_t fsize(const char* fname)
{
    struct stat st;
    stat(fname, &st);
    return st.st_size;
}

/* Reverse string function */
/* return reversed string */
char *strrev(char *str)
{
    char *p1, *p2;

    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}
