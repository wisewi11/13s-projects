#include "bitwriter.h"

#include <stdio.h>
#include <stdlib.h>

struct BitWriter {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    FILE *underlying_stream = fopen(filename, "w");

    if (underlying_stream == 0)
        return NULL;

    BitWriter *buf = malloc(sizeof(BitWriter));
    buf->byte = 0;
    buf->bit_position = 0;

    buf->underlying_stream = underlying_stream;
    return buf;
}

void bit_write_close(BitWriter **pbuf) {
    if (*pbuf != NULL) {
        if ((*pbuf)->bit_position > 0) {
            fputc((*pbuf)->byte, (*pbuf)->underlying_stream);
        }

        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
    }
    *pbuf = NULL;
}

void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if (buf->bit_position > 7) {
        fputc(buf->byte, buf->underlying_stream);
        buf->bit_position = 0;
        buf->byte = 0;
    }

    if (bit & 1)
        buf->byte |= (bit & 1) << buf->bit_position;
    buf->bit_position += 1;
}

void bit_write_uint8(BitWriter *buf, uint8_t x) {
    for (int i = 0; i < 8; i++)
        bit_write_bit(buf, x >> i);
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i < 16; i++)
        bit_write_bit(buf, (uint8_t) (x >> i));
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i < 32; i++)
        bit_write_bit(buf, (uint8_t) (x >> i));
}
