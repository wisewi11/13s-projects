#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    int stackSize = 0;
    Node *stack[64];
    Node *node;

    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    assert(type1 == 'H');
    assert(type2 == 'C');

    uint32_t fileSize = bit_read_uint32(inbuf);

    uint16_t numLeaves = bit_read_uint16(inbuf);
    uint16_t numNodes = 2 * numLeaves - 1;

    for (int i = 0; i < numNodes; i++) {
        uint8_t bit = bit_read_bit(inbuf);
        if (bit) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            node = node_create(0, 0);

            stackSize -= 1;
            node->right = stack[stackSize];

            stackSize -= 1;
            node->left = stack[stackSize];
        }

        stack[stackSize] = node;
        stackSize++;
    }

    stackSize -= 1;
    Node *code_tree = stack[stackSize];
    stackSize -= 1;

    for (uint32_t i = 0; i < fileSize; i++) {
        node = code_tree;

        while (1) {
            uint8_t bit = bit_read_bit(inbuf);
            if (bit) {
                node = node->right;
            } else {
                node = node->left;
            }

            if (!(node->right))
                break;

            if (!(node->left))
                break;
        }

        fputc(node->symbol, fout);
    }

    node_free(&code_tree);
    code_tree = NULL;
}

int main(int argc, char **argv) {
    int opt;
    char *finName = NULL;
    char *foutName = NULL;
    bool needHelp = false;

    while ((opt = getopt(argc, argv, "o:i:h")) != -1) {
        switch (opt) {
        case 'i': finName = optarg; break;
        case 'o': foutName = optarg; break;
        case 'h': needHelp = true; break;
        }
    }

    if (needHelp) {
        printf("Usage: dehuff -i infile -o outfile\n");
        printf("       dehuff -v -i infile -o outfile\n");
        printf("       dehuff -h\n");
        return 0;
    }

    FILE *fout;

    if (finName == NULL) {
        printf("dehuff:  -i option is required\n");
        printf("Usage: dehuff -i infile -o outfile\n");
        printf("       dehuff -v -i infile -o outfile\n");
        printf("       dehuff -h\n");

        return 0;
    }

    if (foutName == NULL) {
        printf("dehuff:  -o option is required\n");
        printf("Usage: dehuff -i infile -o outfile\n");
        printf("       dehuff -v -i infile -o outfile\n");
        printf("       dehuff -h\n");
        return 0;
    }

    fout = fopen(foutName, "w");
    if (!fout) {
        printf("dehuff:  error reading input file %s\n", foutName);
        printf("Usage: dehuff -i infile -o outfile\n");
        printf("       dehuff -v -i infile -o outfile\n");
        printf("       dehuff -h\n");
        return 1;
    }

    BitReader *bit_reader = bit_read_open(finName);
    if (!bit_reader) {
        fprintf(stderr, "cannot read file");
        fclose(fout);
        return 1;
    }

    dehuff_decompress_file(fout, bit_reader);

    bit_read_close(&bit_reader);

    fclose(fout);

    return 0;
}
