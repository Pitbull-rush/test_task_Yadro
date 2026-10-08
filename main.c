#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef struct {
    uint32_t h;
    uint32_t w;

    uint8_t *a;
    uint8_t *b;
    uint8_t *c;

    uint16_t dh;
    uint16_t dw;

    int8_t *d;
} InputData;

int main(int argc, char *argv[]){
    InputData data = {0};

     int opt;
     char *input_filename = NULL;
     char *output_filename = NULL;
     
    FILE* inputfile = NULL;
    FILE* outfile = NULL;

     opterr = 0;

     while((opt = getopt(argc, argv, "i:o:")) !=-1){
        switch(opt){
            case 'i':
                input_filename = optarg;
                break;
            case 'o':
                output_filename = optarg;
                break;
            case '?':
                if(optopt == 'i' || optopt == 'o'){
                    fprintf(stderr, "Option -%c requires a path argument\n", optopt);
                }else{
                    fprintf(stderr, "Unknown option: -%c\n", optopt);
                }
                return 10;
            default:
                return 10;
        }
     }

    if(input_filename == NULL || output_filename == NULL){
        fprintf(stderr, "Erorr. Two flags are not specified.\n");
        return 10;
     }

    inputfile = fopen(input_filename, "rb");
     if(inputfile == NULL){
        fprintf(stderr, "Failed to open input file: %s\n", input_filename);
        return 1;
     }

    outfile = fopen(output_filename, "wb");
     if(outfile == NULL){
        fprintf(stderr, "Error: failed to create output file '%s'\n", output_filename);
        return 1;
     }

    if (fread(&data.h, sizeof(data.h), 1, inputfile) != 1) {
    fprintf(stderr, "Error: failed to read H\n");
    fclose(inputfile);
    fclose(outfile);
    return 1;
    }

    if (fread(&data.w, sizeof(data.w), 1, inputfile) != 1) {
    fprintf(stderr, "Error: failed to read W\n");
    fclose(inputfile);
    return 1;
    }

    size_t count = (size_t)data.h*data.w;

    data.a = malloc(count*sizeof(*data.a));
    data.b = malloc(count*sizeof(*data.b)); 
    data.c = malloc(count*sizeof(*data.c));

    if (data.a == NULL || data.b == NULL || data.c == NULL) {
    fprintf(stderr, "Error: failed to allocate memory for matrices A, B and C\n");

    free(data.a);
    free(data.b);
    free(data.c);

    fclose(inputfile);
    return 1;
    }

    for (size_t i = 0; i < count; ++i) {
    if (fread(&data.a[i], sizeof(data.a[i]), 1, inputfile) != 1) {
        fprintf(stderr, "Error: failed to read A\n");

        free(data.a);
        free(data.b);
        free(data.c);

        fclose(inputfile);
        return 1;
    }

    if (fread(&data.b[i], sizeof(data.b[i]), 1, inputfile) != 1) {
        fprintf(stderr, "Error: failed to read B\n");

        free(data.a);
        free(data.b);
        free(data.c);

        fclose(inputfile);
        return 1;
    }

    if (fread(&data.c[i], sizeof(data.c[i]), 1, inputfile) != 1) {
        fprintf(stderr, "Error: failed to read C\n");

        free(data.a);
        free(data.b);
        free(data.c);

        fclose(inputfile);
        return 1;
    }
}


    if (fread(&data.dh, sizeof(data.dh), 1, inputfile) != 1) {
    fprintf(stderr, "Error: failed to read DH\n");

    free(data.a);
    free(data.b);
    free(data.c);

    fclose(inputfile);
    return 1;
}

if (fread(&data.dw, sizeof(data.dw), 1, inputfile) != 1) {
    fprintf(stderr, "Error: failed to read DW\n");

    free(data.a);
    free(data.b);
    free(data.c);

    fclose(inputfile);
    return 1;
}

size_t d_count = (size_t)data.dh * data.dw;

data.d = malloc(d_count * sizeof(*data.d));

if (data.d == NULL) {
    fprintf(stderr, "Error: failed to allocate memory for matrix D\n");

    free(data.a);
    free(data.b);
    free(data.c);

    fclose(inputfile);
    return 1;
}

if (fread(data.d, sizeof(*data.d), d_count, inputfile) != d_count) {
    fprintf(stderr, "Error: failed to read matrix D\n");

    free(data.a);
    free(data.b);
    free(data.c);
    free(data.d);

    fclose(inputfile);
    return 1;
}

printf("H = %u, W = %u\n",
       (unsigned int)data.h,
       (unsigned int)data.w);

printf("DH = %u, DW = %u\n",
       (unsigned int)data.dh,
       (unsigned int)data.dw);

for (size_t i = 0; i < count; ++i) {
    printf("A[%zu] = %u, B[%zu] = %u, C[%zu] = %u\n",
           i, (unsigned int)data.a[i],
           i, (unsigned int)data.b[i],
           i, (unsigned int)data.c[i]);
}

for (size_t i = 0; i < d_count; ++i) {
    printf("D[%zu] = %d\n", i, (int)data.d[i]);
}





free(data.a);
free(data.b);
free(data.c);
free(data.d);

fclose(inputfile);
fclose(outfile);

    return 0;
}