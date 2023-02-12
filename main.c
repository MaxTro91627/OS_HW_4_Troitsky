#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

const int buf_size = 4096;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Wrong args!");
        exit(-1);
    }

    int fd;
    char* buf = (char*)malloc((buf_size + 1) * sizeof(char));
    ssize_t reading;
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        printf("Cant open reading file\n");
        exit(-1);
    }
    reading = read(fd, buf, buf_size);
    buf[reading] = '\0';
    if (close(fd) < 0) {
        printf("Cant close reading file\n");
    }
    if ((fd = open(argv[2], O_WRONLY | O_CREAT)) < 0) {
        printf("Cant open writing file\n");
        exit(-1);
    }
    int size = write(fd, buf, reading);
    if (size != reading) {
        printf("Cant write all string\n");
        exit(-1);
    }
    if (close(fd) < 0) {
        printf("Cant close writing file\n");
    }
    free(buf);
    return 0;
}