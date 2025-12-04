#include <stdio.h>
#include <fcntl.h>    // open
#include <unistd.h>   // read, write, close
#include <stdlib.h>   // exit
#include <errno.h>    // errno

#define BUFFER_SIZE 1024

int main() {
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open source file for reading
    src_fd = open("result.txt", O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open destination file for writing (create if not exist, truncate if exists)
    dest_fd = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    // Read from source and write to destination
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read < 0) {
        perror("Error reading from source file");
    }

    // Close both files
    close(src_fd);
    close(dest_fd);

    printf("File copied successfully from result.txt to copyresult.txt\n");
    return 0;
}
