#include "grep.h"
char *getsubstr(char *s, regmatch_t *pmatch) {
    static char buf[MAX_LENGTH] = {0};
    memset(buf, 0, sizeof(buf));
    memcpy(buf, s + pmatch->rm_so, pmatch->rm_eo - pmatch->rm_so);
    return buf;
}

void print(int a, char *text, int number_of_file, char *argv[], size_t number_of_line, opt grep) {
    switch (a) {
        case 0: {
            grep.count_files > 1 ? printf("\x1b[35m%s\x1b[0m:%s", argv[number_of_file], text)
                                 : printf("%s", text);
            break;
        }
        case 1: {
            grep.count_files > 1 ? printf("\x1b[35m%s\x1b[0m:\x1b[32m%ld\x1b[0m\x1b[34m:\x1b[0m%s",
                                          argv[number_of_file], number_of_line, text)
                                 : printf("\x1b[32m%ld\x1b[0m\x1b[34m:\x1b[0m%s", number_of_line, text);
            break;
        }
        case 3: {
            printf("\x1b[35m%s\x1b[0m\n", argv[number_of_file]);
            break;
        }
        case 2: {
            grep.count_files > 1
                ? printf("\x1b[35m%s\x1b[0m:%ld\n", argv[number_of_file], grep.number_of_coincidence)
                : printf("%ld\n", grep.number_of_coincidence);
            break;
        }
        default:
            break;
    }
}

void grep_e(char *argv[], int number_of_file, opt grep) {
    regex_t myre;
    FILE *file = fopen(argv[number_of_file], "r");
    int err;
    size_t text_size = 0;
    char *text = NULL;
    ssize_t read;
    size_t number_of_line = 1;
    char err_msg[MAX_ERR_LENGTH];
    regmatch_t pmatch;
    int bool_;
    if (file == NULL) {
        if (grep.flag_file_error_ouput == 0) printf("%s : No such file or directory\n", argv[number_of_file]);
        return;
    }
    if ((err = regcomp(&myre, grep.pattern, grep.reg == 0 ? 0 : regist)) != 0) {
        regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
        printf("Error analyzing regular expression '%s': %s.\n", grep.pattern, err_msg);
        regfree(&myre);
        return;
    }
    while ((read = getline(&text, &text_size, file)) != -1) {
        if ((err = regexec(&myre, text, 1, &pmatch, 0)) == (grep.invert == 1 ? coincidence : 0)) {
            grep.number_of_coincidence++;
            bool_ = 1;
            if (grep.flag_substr == 1) {
                char *p = getsubstr(text, &pmatch);
                strcat(p, "\n");
                if (grep.flag_otputs < 2)
                    print(grep.flag_otputs, p, number_of_file, argv, number_of_line, grep);
                char *str = NULL;
                str = text;
                str += pmatch.rm_eo;
                while (pmatch.rm_eo != -1 && (err = regexec(&myre, str, 1, &pmatch, 0)) == 0) {
                    p = getsubstr(str, &pmatch);
                    strcat(p, "\n");
                    if (grep.flag_otputs < 2)
                        print(grep.flag_otputs, p, number_of_file, argv, number_of_line, grep);
                    str += pmatch.rm_eo;
                }
            } else {
                if (grep.flag_otputs < 2)
                    print(grep.flag_otputs, text, number_of_file, argv, number_of_line, grep);
            }
        }
        number_of_line++;
    }
    switch (grep.flag_otputs) {
        case 2: {
            print(grep.flag_otputs, text, number_of_file, argv, number_of_line, grep);
            break;
        };
        case 3: {
            if (bool_ == 1) print(grep.flag_otputs, text, number_of_file, argv, number_of_line, grep);
            break;
        }
    }
    if (text) free(text);
    fclose(file);
    regfree(&myre);
}

void grep_main(int argc, char *argv[], opt *grep, size_t *buf_size) {
    char ch;
    const struct option long_options[] = {{NULL, required_argument, NULL, 'e'},
                                          {NULL, required_argument, NULL, 'i'},
                                          {NULL, required_argument, NULL, 'v'},
                                          {NULL, required_argument, NULL, 'l'},
                                          {NULL, 0, NULL, 0}};

    const char *short_options = "e:i::v::c::n::h::s::f:o::l::";
    while ((ch = getopt_long(argc, argv, short_options, long_options, NULL)) !=
           -1) {      /* getopt() iterates over argv[] */
        switch (ch) { /* what getopt() returned */

            case 'e':
                (grep->patter_position) = optind;
                while (argv[optind] != NULL && strstr("-e", argv[optind]) != NULL) {
                    optind += 2;
                }
                grep->pattern = argv[grep->patter_position - 1];
                if (grep->count_files == 0) grep->count_files = argc - optind;
                Multiple_File_Handler(argv, grep_e, optind, argc, *grep);
                optind = grep->patter_position;
                break;
            case 'i':
                grep->reg = 1;
                if (strstr("-e-i-v-c-n-h-s-f-o-l", argv[optind]) == NULL) {
                    if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind];
                    if (grep->count_files == 0) grep->count_files = argc - optind - 1;
                    Multiple_File_Handler(argv, grep_e, optind + 1, argc, *grep);
                }
                break;
            case 'v':
                grep->invert = 1;
                if (strstr("-e-i-v-c-n-h-s-f-o-l", argv[optind]) == NULL) {
                    if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind];
                    if (grep->count_files == 0) grep->count_files = argc - optind - 1;
                    Multiple_File_Handler(argv, grep_e, optind + 1, argc, *grep);
                }
                break;
            case 'c':
                if (grep->flag_otputs < 3) grep->flag_otputs = 2;
                if (strstr("-e-i-v-c-n-h-s-f-o-l", argv[optind]) == NULL) {
                    if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind];
                    if (grep->count_files == 0) grep->count_files = argc - optind - 1;
                    Multiple_File_Handler(argv, grep_e, optind + 1, argc, *grep);
                }
                // if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind - 1];
                // grep->count_files = argc - optind;
                // Multiple_File_Handler(argv, grep_c, optind, argc, grep);
                break;
            case 'n':
                if (grep->flag_otputs < 2) grep->flag_otputs = 1;
                if (strstr("-e-i-v-c-n-h-s-f-o-l", argv[optind]) == NULL) {
                    if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind];
                    if (grep->count_files == 0) grep->count_files = argc - optind - 1;
                    Multiple_File_Handler(argv, grep_e, optind + 1, argc, *grep);
                }
                // if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind - 1];
                // grep->count_files = argc - optind;
                // Multiple_File_Handler(argv, grep_n, optind, argc, grep);
                break;
            case 'l':
                grep->flag_otputs = 3;
                if (strstr("-e-i-v-c-n-h-s-f-o-l", argv[optind]) == NULL) {
                    if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind];
                    if (grep->count_files == 0) grep->count_files = argc - optind - 1;
                    Multiple_File_Handler(argv, grep_e, optind + 1, argc, *grep);
                }
                break;
            case 'h':
                grep->count_files = 1;
                if (strstr("-e-i-v-c-n-h-s-f-o-l", argv[optind]) == NULL) {
                    if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind];
                    // grep->count_files = argc - optind - 1;
                    Multiple_File_Handler(argv, grep_e, optind + 1, argc, *grep);
                }
                break;
            case 's':
                grep->flag_file_error_ouput = 1;
                if (strstr("-e-i-v-c-n-h-s-f-o-l", argv[optind]) == NULL) {
                    if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind];
                    if (grep->count_files == 0) grep->count_files = argc - optind - 1;
                    Multiple_File_Handler(argv, grep_e, optind + 1, argc, *grep);
                }
                break;
            case 'f':
                if (strstr("-e-i-v-c-n-h-s-f-o-l", argv[optind]) == NULL) {
                    if (strcmp(grep->pattern, "") == 0) {
                        FILE *fp = fopen(argv[optind - 1], "r");
                        if (fp == NULL) {
                            printf("%s : No such file or directory\n", argv[optind - 1]);
                        } else {
                            getline(&grep->pattern, buf_size, fp);
                            fclose(fp);
                            if (grep->count_files == 0) grep->count_files = argc - optind;
                            Multiple_File_Handler(argv, grep_e, optind, argc, *grep);
                        }
                    }

                } else {
                    FILE *fp = fopen(argv[optind - 1], "r");
                    if (fp == NULL) {
                        printf("%s : No such file or directory\n", argv[optind - 1]);
                    } else {
                        getline(&grep->pattern, buf_size, fp);
                    }
                    fclose(fp);
                }
                break;
            case 'o':
                grep->flag_substr = 1;
                if (strstr("-e-i-v-c-n-h-s-f-o-l", argv[optind]) == NULL) {
                    if (strcmp(grep->pattern, "") == 0) grep->pattern = argv[optind];
                    grep->count_files = argc - optind - 1;
                    printf("%s\n", argv[optind + 1]);
                    Multiple_File_Handler(argv, grep_e, optind + 1, argc, *grep);
                }
                break;

            default:
                printf("Usage:\n%s [-o] [i] [-v] [-c] [-l] [-n] [-h] [-s] [-f file] [-o]\n", argv[0]);
        }
    }
}