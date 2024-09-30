#include "bitreader.h"

#include <stdio.h>
#include <stdlib.h>

struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
    FILE *underlying_stream = fopen(filename, "r");

    if (underlying_stream == 0)
        return NULL;

    BitReader *buf = malloc(sizeof(BitReader));
    buf->underlying_stream = underlying_stream;
    buf->bit_position = 8;

    return buf;
}

void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
    }
    *pbuf = NULL;
}

uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        int x = fgetc(buf->underlying_stream);
        if (x == EOF) {
            fprintf(stderr, "cannot read file");
            return 1;
        }

        buf->byte = (uint8_t) x;
        buf->bit_position = 0;
    }

    uint8_t bit = (buf->byte >> buf->bit_position) & 1;
    buf->bit_position += 1;

    return bit;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0;

    for (int i = 0; i < 8; i++) {
        uint8_t bit = bit_read_bit(buf);
        byte |= (bit << i);
    }

    return byte;
}

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t byte = 0;

    for (int i = 0; i < 16; i++) {
        uint8_t bit = bit_read_bit(buf);
        byte |= (bit << i);
    }

    return byte;
}

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t byte = 0;

    for (int i = 0; i < 32; i++) {
        uint8_t bit = bit_read_bit(buf);
        byte |= (uint32_t) (bit << i);
    }

    return byte;
}
