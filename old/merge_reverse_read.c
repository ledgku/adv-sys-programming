#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>

int readaline_and_reverse_out(int fin, int fout);
char *strrev(char *str);

int main(int argc, char *argv[])
{
    int file1, file2, fout;
    int eof1 = 0, eof2 = 0;
    long line1 = 0, line2 = 0, lineout = 0;
    struct timeval before, after;
    int duration;
    int ret = 1;

    if (argc != 4) {
        fprintf(stderr, "usage: %s file1 file2 fout\n", argv[0]);
        goto leave0;
    }
    if ((file1 = open(argv[1], O_RDONLY)) == -1) {
        perror(argv[1]);
        goto leave0;
    }
    if ((file2 = open(argv[2], O_RDONLY)) == -1) {
        perror(argv[2]);
        goto leave1;
    }
    if ((fout = open(argv[3], O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1) {
        perror(argv[3]);
        goto leave2;
    }

    gettimeofday(&before, NULL);
    do {
        if (!eof1) {
            if (!readaline_and_reverse_out(file1, fout)) {
                line1++; lineout++;
            } else
                eof1 = 1;
        }
        if (!eof2) {
            if (!readaline_and_reverse_out(file2, fout)) {
                line2++; lineout++;
            } else
                eof2 = 1;
        }
    } while (!eof1 || !eof2);
    gettimeofday(&after, NULL);

    duration = (after.tv_sec - before.tv_sec) * 1000000 + (after.tv_usec - before.tv_usec);
    printf("Processing time = %d.%06d sec\n", duration / 1000000, duration % 1000000);
    printf("File1 = %ld, File2= %ld, Total = %ld Lines\n", line1, line2, lineout);
    ret = 0;

leave3:
    close(fout);
leave2:
    close(file2);
leave1:
    close(file1);
leave0:
    return ret; 
}

/* return 1 if fin meets end of file */
int readaline_and_reverse_out(int fin, int fout)
{    
    int ch, count = 0;
    char tempStr[81];
    char *rev;

    do {
        if (read(fin, &ch, 1) < 1) {
            if (!count)
                return 1;
            else {
                tempStr[count] = 0x0a;
                break;
            }
        }
        tempStr[count] = ch;
        count++;
    } while (ch != 0x0a);
    
    tempStr[count] = '\0';

    rev = strrev(tempStr);
    write(fout, rev, count);

    return 0;
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
