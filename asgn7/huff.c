#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    uint32_t fileSize = 0;
    int byte = fgetc(fin);

    for (uint32_t i = 0; i < 256; i++)
        histogram[i] = 0;

    histogram[0xFF]++;
    histogram[0x00]++;

    while (byte != EOF) {
        histogram[byte]++;
        byte = fgetc(fin);
        fileSize++;
    }

    return fileSize;
}

Node *create_tree(uint32_t *histogram, uint16_t *numLeaves) {
    PriorityQueue *pq = pq_create();
    uint16_t lc = 0;

    for (uint32_t i = 0; i < 256; i++) {
        if (histogram[i] > 0) {
            Node *node = node_create((uint8_t) i, histogram[i]);
            enqueue(pq, node);

            lc++;
        }
    }

    *numLeaves = lc;

    while (!pq_size_is_1(pq)) {
        Node *left = dequeue(pq);
        Node *right = dequeue(pq);
        Node *parent_node = node_create(0, left->weight + right->weight);
        parent_node->left = left;
        parent_node->right = right;
        enqueue(pq, parent_node);
        lc++;
    }

    Node *last_node = dequeue(pq);
    pq_free(&pq);

    return last_node;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left != NULL || node->right != NULL) {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t fileSize, uint16_t numLeaves,
    Node *code_tree, Code *code_table) {

    fseek(fin, 0, SEEK_SET);

    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, fileSize);
    bit_write_uint16(outbuf, numLeaves);
    huff_write_tree(outbuf, code_tree);

    while (1) {
        int b = fgetc(fin);
        if (b == EOF)
            break;

        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;

        for (int i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
    }
}

int main(int argc, char **argv) {
    int opt;
    char *finName = NULL;
    char *foutName = NULL;
    bool needHelp = false;

    while ((opt = getopt(argc, argv, "o:i:h")) != -1) {
        switch (opt) {
        case 'i': finName = optarg; break;
        case 'h': needHelp = true; break;
        case 'o': foutName = optarg; break;
        }
    }

    if (needHelp) {
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile\n");
        printf("       huff -h\n");

        return 0;
    }

    FILE *fin;

    if (finName == NULL) {
        printf("huff:  -i option is required\n");
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile\n");
        printf("       huff -h\n");

        return 0;
    }

    fin = fopen(finName, "r");
    if (!fin) {
        printf("huff:  error reading input file %s\n", finName);
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile\n");
        printf("       huff -h\n");

        return 1;
    }

    if (!foutName) {
        printf("huff:  -o option is required\n");
        printf("Usage: huff -i infile -o outfile\n");
        printf("       huff -v -i infile -o outfile\n");
        printf("       huff -h\n");

        fclose(fin);
        return 0;
    }

    BitWriter *bit_writer = bit_write_open(foutName);
    if (!bit_writer) {
        fprintf(stderr, "cannot write file");
        fclose(fin);
        return 1;
    }

    uint32_t histogram[256];
    uint16_t numLeaves;

    uint32_t fileSize = fill_histogram(fin, histogram);
    Node *code_tree = create_tree(histogram, &numLeaves);

    Code code_table[256];
    fill_code_table(code_table, code_tree, 0, 0);

    huff_compress_file(bit_writer, fin, fileSize, numLeaves, code_tree, code_table);

    bit_write_close(&bit_writer);

    fclose(fin);

    node_free(&code_tree);

    return 0;
}
