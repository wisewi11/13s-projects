#define MAX_LINE_LENGTH 1024

#include "hash.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {

    int fd = 0;

    uint8_t read_buff[16];
    int read_buff_offset = 0;
    int read_buff_remaining = 0;
    int number_unique_lines = 0;
    char current_line[MAX_LINE_LENGTH] = { 0 };
    int current_line_offset = 0;

    Hashtable *h = hash_create();

    while (1) {

        if (read_buff_remaining == 0) {
            ssize_t rc = read(fd, read_buff, sizeof(read_buff));
            if (rc == 0) {
                break;
            }

            read_buff_remaining = (int) rc;
            read_buff_offset = 0;
        }

        char c = (char) read_buff[read_buff_offset];
        read_buff_remaining -= 1;
        read_buff_offset += 1;

        if (c == '\n') {

            int *hash_result = hash_get(h, current_line);
            if (hash_result == NULL) {
                hash_put(h, current_line, 0);

                number_unique_lines += 1;
            }

            memset(current_line, 0, sizeof(current_line));
            current_line_offset = 0;
        } else if (current_line_offset < MAX_LINE_LENGTH) {
            current_line[current_line_offset] = c;
            current_line_offset += 1;
        }
    }

    printf("%d\n", number_unique_lines);

    hash_destroy(&h);
    close(fd);
}
