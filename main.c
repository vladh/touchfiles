#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int const FILESIZE = 10; // bytes


void
usage()
{
    printf("touchfiles\n");
    printf("Creates a given number of files in a given directory.\n");
    printf("The file naming scheme is 8-digit hex e.g. 01c9c380.\n");
    printf("\n");
    printf("Usage:\n");
    printf("\ttouchfiles <path> <n_files>\n");
    printf("\n");
    printf("Arguments:\n");
    printf("\tpath: the path to the directory to make the files in\n");
    printf("\tn_files: number of files to create\n");
}


void
make_filename(char *str, char *dir, int i)
{
    sprintf(str, "%s/%08x.txt", dir, i);
}


void
make_file(char *name)
{
    FILE *fp = fopen(name, "w");
    if (!fp) {
        printf("Could not open %s\n", name);
        exit(-1);
    }
    fseek(fp, FILESIZE - 1, SEEK_SET);
    fputc('\0', fp);
    fclose(fp);
}


int
main(int argc, char **argv)
{
    char filename[512];

    if (argc != 3) {
        usage();
        exit(1);
    }

    uint64_t n_files = strtol(argv[1], (char **)NULL, 10);
    char *dir = argv[2];
    printf("Creating %ld files in %s\n", n_files, dir);

    if (n_files == 0) {
        printf("You asked to create 0 files, did you specify the arguments correctly?\n");
    }

    for (uint64_t i = 0; i < n_files; i++) {
        make_filename(filename, dir, i);
        make_file(filename);
        if (i % 100000 == 0 && i != 0) {
            printf("Creating file number %ld\n", i);
        }
    }
}
