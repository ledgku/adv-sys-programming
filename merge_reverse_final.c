/********************************************************
*   Kookmin University
*   Advanced System Programming
*   
*   Assignment 1
*   Computer Science 20093319 DongkyuLee
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FILE_MAX_SIZE (1024*1024*100)
#define DELIM "\n"

char *strrev(char *str);

int main(int argc, char *argv[])
{
    int file1, file2;
    FILE *fout;
    long line1 = 0, line2 = 0, lineout = 0;
    struct timeval before, after;
    int duration;
    int ret = 1;
    char *str1, *token1, *saveptr1;
    char *str2, *token2, *saveptr2;
    char *buf_file1 = 0, *buf_file2 = 0;
    struct stat file1_stat, file2_stat;

    if (argc != 4) 
    {
        fprintf(stderr, "usage: %s file1 file2 fout\n", argv[0]);
        goto leave0;
    }
 
    if ((file1 = open(argv[1], O_RDONLY)) < 0) 
    {
        perror(argv[1]);
        goto leave0;
    }

    if ((file2 = open(argv[2], O_RDONLY)) < 0) 
    {
        perror(argv[2]);
        goto leave1;
    }

    if ((fout = fopen(argv[3], "wt")) == NULL) 
    {
        perror(argv[3]);
        goto leave2;
    }

    if (fstat(file1, &file1_stat) < 0)
    {
        fprintf(stderr, "error: an error occurred while reading the information in the file1\n");
        goto leave3;
    }

    if (fstat(file2, &file2_stat) < 0)
    {
        fprintf(stderr, "error: an error occurred while reading the information in the file2\n");
        goto leave3;
    }

    if (file1_stat.st_size > FILE_MAX_SIZE) 
    {
        fprintf(stderr, "error: %s size is greater than %d bytes\n", argv[1], FILE_MAX_SIZE);
	goto leave3;
    }

    if (file2_stat.st_size > FILE_MAX_SIZE) 
    {
        fprintf(stderr, "error: %s size is greater than %d bytes\n", argv[2], FILE_MAX_SIZE);
	goto leave3;
    }
   
    gettimeofday(&before, NULL);

    if ((buf_file1 = (char *) malloc(file1_stat.st_size)) == NULL)
    {
        fprintf(stderr, "error: an error occurred while allocating memory of file1's buffer (%u bytes)", (unsigned int)file1_stat.st_size);
        goto leave3;    	
    }

    if ((buf_file2 = (char *) malloc(file1_stat.st_size)) == NULL)
    {
        fprintf(stderr, "error: an error occurred while allocating memory of file2's buffer (%u bytes)", (unsigned int)file2_stat.st_size);
        goto leave4;
    }

    if (read(file1, buf_file1, malloc_usable_size(buf_file1)) < 1)
    {
        fprintf(stderr, "error: an error occured while reading the contents of the file1 into the buffer");
        goto leave5;
    }

    if (read(file2, buf_file2, malloc_usable_size(buf_file2)) < 1)
    {
        fprintf(stderr, "error: an error occured while reading the contents of the file2 into the buffer");
        goto leave5;
    }

    setvbuf(fout, NULL, _IOFBF, BUFSIZ);

    for (str1=buf_file1, str2=buf_file2; ;str1=NULL, str2=NULL)
    {
        token1 = strtok_r(str1, DELIM, &saveptr1);
        token2 = strtok_r(str2, DELIM, &saveptr2);
        
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

    lineout = line1 + line2;

    duration = (after.tv_sec - before.tv_sec) * 1000000 + (after.tv_usec - before.tv_usec);
    printf("Processing time = %d.%06d sec\n", duration / 1000000, duration % 1000000);
    printf("File1 = %ld, File2= %ld, Total = %ld Lines\n", line1, line2, lineout);
    ret = 0;

leave5:
    free(buf_file2);
leave4:
    free(buf_file1);
leave3:
    fclose(fout);
leave2:
    close(file2);
leave1:
    close(file1);
leave0:
    return ret; 
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
