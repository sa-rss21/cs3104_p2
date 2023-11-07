/*
 * mkbootimg/bin2h.c
 *
 * Copyright (C) 2020 bzt (bztsrc@gitlab)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This file is part of the BOOTBOOT Protocol package.
 * @brief Small utility to convert binary to C header, because MacOSX does not support ld -b binary!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "zlib.c"

int main(int argc, char **argv)
{
    FILE *f, *c, *h;
    unsigned long int size, len;
    unsigned char *buff = NULL, *buff2 = NULL;
    char *fn, name[255];
    int i, file;

    if(argc < 2){
        printf("bin2h <bin file> [bin file2...]\r\n");
        exit(1);
    }

    c = fopen("data.c", "w"); if(!c) { fprintf(stderr, "bin2h: unable to open data.c\r\n"); return 1; }
    h = fopen("data.h", "w"); if(!h) { fprintf(stderr, "bin2h: unable to open data.h\r\n"); return 1; }
    fprintf(c, "/* generated by bin2h, do not edit */\n\n");
    fprintf(h, "/* generated by bin2h, do not edit */\n\n");
    for(file = 1; file < argc; file++){
        size = 0;
        f = fopen(argv[file],"rb");
        if(f) {
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            fseek(f, 0, SEEK_SET);
            buff = (unsigned char*)malloc(size);
            if(!buff) {
                fprintf(stderr, "bin2h: memory allocation error\r\n");
                exit(2);
            }
            fread(buff, 1, size, f);
            fclose(f);
            fn = strrchr(argv[file], '/');
            if(!fn) fn = strrchr(argv[file], '\\');
            if(!fn) fn = argv[file]; else fn++;
            for(i = 0; fn[i]; i++)
                name[i] = fn[i] == '.' || fn[i] <= ' ' ? '_' : fn[i];
            name[i] = 0;
            if(size > 512) {
                len = compressBound(size);
                buff2 = (unsigned char*)malloc(len);
                if(!buff2) {
                    fprintf(stderr, "bin2h: memory allocation error\r\n");
                    exit(2);
                }
                compress2(buff2, &len, buff, size, 9);
                free(buff); buff = buff2;
            } else len = size;
            fprintf(h, "#define sizeof_%s %ld\nextern unsigned char binary_%s[%ld];\n", name, size, name, len);
            fprintf(c, "unsigned char binary_%s[%ld] = { ", name, len);
            for(i = 0; i < len; i++)
                fprintf(c,"%s%d", i?",":"", buff[i]);
            fprintf(c," };\n");
            free(buff);
            buff = NULL;
        } else
            fprintf(stderr, "bin2h: unable to open input file: %s\r\n", argv[file]);
    }
    fclose(h);
    fclose(c);
}
