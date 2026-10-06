#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef struct {
    uint32_t = H;
    uint32_t = W;


    uint8_t = *A1;
    uint8_t = *B1;
    uint8_t = *C1;

}InputData;

int main(int argc, char *argv[]){
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
        fprintf(stderr, "Error: failed to create output file '%s'\n");
        return 1;
     }



    return 0;
}