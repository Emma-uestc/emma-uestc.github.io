#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// define a new type for uint8_t
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Check if the number of arguments is valid
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // open the raw file (binary read mode)
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open the file!\n");
        return 1;
    }

    // define key variables
    FILE *output = NULL; // output file
    BYTE buffer[512]; // A buffer array with 512B
    char filename[8]; // using store image with the name like "000.jpg" + '\0'
    int counter = 0; // the number of images

    while (fread(buffer, sizeof(BYTE), 512, input) == 512)
    {
        // Check the JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
        && (buffer[3] & 0xf0) == 0xe0) // 第四个字节使用位运算检查，高四位是否是1110，即0xe
        {
            if (output != NULL)
            {
                // Close it if it is writint an image
                fclose(output);
            }
            // Generate a new image
            sprintf(filename, "%03i.jpg", counter);
            output = fopen(filename, "wb");
            if (output == NULL)
            {
                fclose(input);
                printf("Could not create file.\n");
                return 1;
            }
            counter++;
        }
        if (output != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, output);
        }
    }
    // Close all files
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(input);
    return 0;
}
