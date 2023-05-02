#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPT_NUM 10 /* a, b, c and x (h is not relevant here) */
#define MAX_ERR_LENGTH 80
#define MAX_LENGTH 256
#define regist REG_EXTENDED | REG_ICASE
#define coincidence REG_NOMATCH

typedef struct grep_options {
    int flag_file_error_ouput;
    int flag_file_input;
    int flag_otputs;  // 0 -- 1 file, 2 -- several files, 3 -- no outputs with several files
    int count_files;
    int flag_substr;
    int reg;
    size_t number_of_coincidence;
    int invert;
    int patter_position;
    char *pattern;
} opt;

void print(int a, char *text, int number_of_file, char *argv[], size_t number_of_line, opt);
void Multiple_File_Handler(char *argv[], void (*func)(char **, int, opt), int, int, opt);
void grep_e(char *argv[], int, opt);
char *getsubstr(char *s, regmatch_t *pmatch);
void grep_main(int argc, char *argv[], opt *grep, size_t *buf_size);