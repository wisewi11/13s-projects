#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc > 2) {
        return 1; // return non 0 for error, more than one argument supplied
    } else if (argc == 2 || argc == 1) {
        // open file handler from file name
        int fd = 0; // 0 is the address of stdin
        if (argc == 2) {
            fd = open(argv[1], O_RDONLY);
        }

        if (fd < 0) {
            return 1; // return non 0 for error, invalid file name or permission
        }

        uint8_t readBuffer[16];
        int readBufferOffset = 0;
        int readBufferRemaining = 0;

        unsigned char writeBuffer[16];
        int writeBufferOffset = 0;
        int writeRowOffset = 0;
        int counter = 0;

        while (1) {
            // read file content into read buffer
            if (readBufferRemaining == 0 && counter > -1) {
                ssize_t rc = read(fd, readBuffer, sizeof(readBuffer));
                if (rc == 0) {
                    break; // stop reading until EOF
                }

                readBufferRemaining = (int) rc;
                readBufferOffset = 0;
            }

            // extract character and iterate read buffer
            unsigned char c = (unsigned char) readBuffer[readBufferOffset];

            readBufferOffset += 1;
            readBufferRemaining -= 1;

            counter += 1;

            // save character into write buffer, output if full
            if (writeBufferOffset == 16) {
                // print row header
                printf("%08x: ", writeRowOffset);

                // print pairs of hex
                for (int i = 0; i < 16; i++) {
                    printf("%02x", writeBuffer[i]);
                    if (i % 2 != 0) {
                        printf(" ");
                    }
                }

                // separator
                printf(" ");

                // print character sequence
                for (int i = 0; i < 16; i++) {
                    unsigned char c = writeBuffer[i];
                    if (c < 32 || c > 126) { // replace any invalid character with a dot
                        c = '.';
                    }

                    printf("%c", c);
                }

                printf("\n");

                writeRowOffset += 16;
                writeBufferOffset = 0;
            }

            writeBuffer[writeBufferOffset] = c;
            writeBufferOffset += 1;
        }

        if (writeRowOffset > 0 || writeBufferOffset > 0) {
            printf("%08x: ", writeRowOffset);

            for (int i = 0; i < writeBufferOffset; i++) {
                printf("%02x", writeBuffer[i]);
                if (i % 2 != 0) {
                    printf(" ");
                }
            }

            for (int i = 0; i < 16 - writeBufferOffset; i++) {
                if (i % 2 == 0) {
                    printf("   ");
                } else {
                    printf("  ");
                }
            }

            printf(" ");

            for (int i = 0; i < writeBufferOffset; i++) {
                unsigned char c = writeBuffer[i];
                if (c < 32 || c > 126) {
                    c = '.';
                }

                printf("%c", c);
            }

            printf("\n");
        }

        close(fd);
    }

    return 0;
}
