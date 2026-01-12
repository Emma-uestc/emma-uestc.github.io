// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input) == 1)
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
# 2. filter-less  
## 问题背景  
图片是RGB三原色构成的，本题就是通过控制RGB三个通道的值来实现滤镜效果。  
我们先看下课程提供的文件。 我们可以看到有四个文件，其中bmp.h是头文件，filter.c是主函数，helpers.c和helpers.h是辅助函数。
```Shell
cd filter-less/
filter-less/ $ ls -l
total 24
-rw-r--r-- 1 ubuntu ubuntu 1632 Dec 31  2021 bmp.h
-rw-r--r-- 1 ubuntu ubuntu 3437 Dec 31  2021 filter.c
-rw-r--r-- 1 ubuntu ubuntu  458 Dec 31  2021 helpers.c
-rw-r--r-- 1 ubuntu ubuntu  394 Dec 31  2021 helpers.h
drwxr-xr-x 2 ubuntu ubuntu 4096 Dec 31  2021 images/
-rw-r--r-- 1 ubuntu ubuntu  215 Jun 18  2022 Makefile
```  
## 位图  
BMP除了包含图片数据外，还包含一些元数据，如图片高度、宽度等。  
这些元数据存储在图片文件的头部(header)中。  
头文件中定义了`BITMAPFILEHEADER`和`BITMAPINFOHEADER`两个结构体，分别表示位图文件头和位图信息头。   
## 代码  
课程提供了必要的头文件和代码框架，我们只要实现filter函数即可。  
* `bmp.h`  
该文件定义了我们上面提到的两个header, `BITMAPINFOHEADER` 和 `BITMAPFILEHEADER`  
* `filter.c`  
该文件是filter-less 题目的主文件，课程已经帮我们首先了整个图片filter 的流程，我们需要做的就是完成