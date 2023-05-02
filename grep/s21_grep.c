#include "grep.h"

// void grep_i(char *argv[], int, opt);
// void grep_c(char *argv[], int, opt);
// void grep_n(char *argv[], int, opt);
// void grep_v(char *argv[], int, opt);
// void grep_l(char *argv[], int, opt);
// void grep_h(char *argv[], int, int);

int main(int argc, char *argv[]) {
    size_t buf_size = 0;
    opt grep = {0, 0, 0, 0, 0, 0, 0, 0, 0, ""};
    grep_main(argc, argv, &grep, &buf_size);
    if (buf_size != 0) free(grep.pattern);
    return 0;
}

// find pattern all | case-independent search
// void grep_i(char *argv[], int number_of_file, opt grep) {
//     regex_t myre;
//     FILE *file = fopen(argv[number_of_file], "r");
//     int err;
//     size_t text_size = 0;
//     char *text = NULL;
//     ssize_t read;
//     regmatch_t pmatch;
//     char err_msg[MAX_ERR_LENGTH];
//     if (grep.flag_otputs == 0 && grep.count_files > 1) grep.flag_otputs = 1;
//     if (file == NULL) {
//         if (grep.flag_file_error_ouput == 0) printf("%s : No such file or directory\n",
//         argv[number_of_file]); return;
//     }
//     if ((err = regcomp(&myre, grep.pattern, regist)) != 0) {
//         regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
//         printf("Error analyzing regular expression '%s': %s.\n", grep.pattern, err_msg);
//         regfree(&myre);
//         return;
//     }
//     while ((read = getline(&text, &text_size, file)) != -1) {
//         if ((err = regexec(&myre, text, 1, &pmatch, 0)) == 0) {
//             if (grep.flag_substr == 1) {
//                 char *p = getsubstr(text, &pmatch);
//                 strcat(p, "\n");
//                 print(grep.flag_otputs, p, number_of_file, argv, 0);
//                 char *str = NULL;
//                 str = text;
//                 str += pmatch.rm_eo;
//                 while (pmatch.rm_eo != -1 && (err = regexec(&myre, str, 1, &pmatch, 0)) == 0) {
//                     p = getsubstr(str, &pmatch);
//                     strcat(p, "\n");
//                     print(grep.flag_otputs, p, number_of_file, argv, 0);
//                     str += pmatch.rm_eo;
//                 }
//             } else {
//                 print(grep.flag_otputs, text, number_of_file, argv, 0);
//             }
//         }
//     }
//     if (text) free(text);
//     fclose(file);
//     regfree(&myre);
// }

// find count of matching the pattern
// void grep_c(char *argv[], int number_of_file, opt grep) {
//     regex_t myre;
//     FILE *file = fopen(argv[number_of_file], "r");
//     int err;
//     size_t text_size = 0;
//     char *text = NULL;
//     ssize_t read;
//     size_t number_of_coincidence = 0;
//     char err_msg[MAX_ERR_LENGTH];
//     regmatch_t pmatch;
//     if (grep.flag_otputs == 0 && grep.count_files > 1) grep.flag_otputs = 1;
//     if (file == NULL) {
//         if (grep.flag_file_error_ouput == 0) printf("%s : No such file or directory\n",
//         argv[number_of_file]); return;
//     }
//     if ((err = regcomp(&myre, grep.pattern, 0)) != 0) {
//         regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
//         printf("Error analyzing regular expression '%s': %s.\n", grep.pattern, err_msg);
//         regfree(&myre);
//         return;
//     }
//     while ((read = getline(&text, &text_size, file)) != -1) {
//         if ((err = regexec(&myre, text, 1, &pmatch, 0)) == 0) {
//             number_of_coincidence++;
//         }
//     }
//     char str[MAX_LENGTH];
//     snprintf(str, sizeof str, "%zu", number_of_coincidence);
//     strcat(str, "\n");
//     print(grep.flag_otputs, str, number_of_file, argv, 0);
//     if (text) free(text);
//     fclose(file);
//     regfree(&myre);
// }

// find pattern all and print number of line
// void grep_n(char *argv[], int number_of_file, opt grep) {
//     regex_t myre;
//     FILE *file = fopen(argv[number_of_file], "r");
//     int err;
//     size_t text_size = 0;
//     char *text = NULL;
//     ssize_t read;
//     size_t number_of_line = 1;
//     char err_msg[MAX_ERR_LENGTH];
//     regmatch_t pmatch;
//     grep.flag_otputs = 1;
//     if (file == NULL) {
//         if (grep.flag_file_error_ouput == 0) printf("%s : No such file or directory\n",
//         argv[number_of_file]); return;
//     }
//     if ((err = regcomp(&myre, grep.pattern, 0)) != 0) {
//         regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
//         printf("Error analyzing regular expression '%s': %s.\n", grep.pattern, err_msg);
//         regfree(&myre);
//         return;
//     }
//     while ((read = getline(&text, &text_size, file)) != -1) {
//         if ((err = regexec(&myre, text, 1, &pmatch, 0)) == 0) {
//             if (grep.flag_substr == 1) {
//                 char *p = getsubstr(text, &pmatch);
//                 strcat(p, "\n");
//                 print(grep.flag_otputs, p, number_of_file, argv, number_of_line,grep);
//                 char *str = NULL;
//                 str = text;
//                 str += pmatch.rm_eo;
//                 while (pmatch.rm_eo != -1 && (err = regexec(&myre, str, 1, &pmatch, 0)) == 0) {
//                     p = getsubstr(str, &pmatch);
//                     strcat(p, "\n");
//                     print(grep.flag_otputs, p, number_of_file, argv, number_of_line,grep);
//                     str += pmatch.rm_eo;
//                 }
//             } else {
//                 print(grep.flag_otputs, text, number_of_file, argv, number_of_line,grep);
//             }
//         }
//         number_of_line++;
//     }
//     if (text) free(text);
//     fclose(file);
//     regfree(&myre);
// }

// find unpattern all
// void grep_v(char *argv[], int number_of_file, opt grep) {
//     regex_t myre;
//     FILE *file = fopen(argv[number_of_file], "r");
//     int err;
//     size_t text_size = 0;
//     char *text = NULL;
//     ssize_t read;
//     regmatch_t pmatch;
//     char err_msg[MAX_ERR_LENGTH];
//     if (grep.flag_otputs == 0 && grep.count_files > 1) grep.flag_otputs = 1;
//     if (file == NULL) {
//         if (grep.flag_file_error_ouput == 0) printf("%s : No such file or directory\n",
//         argv[number_of_file]); return;
//     }
//     if ((err = regcomp(&myre, grep.pattern, 0)) != 0) {
//         regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
//         printf("Error analyzing regular expression '%s': %s.\n", grep.pattern, err_msg);
//         regfree(&myre);
//         return;
//     }
//     while ((read = getline(&text, &text_size, file)) != -1) {
//         if ((err = regexec(&myre, text, 1, &pmatch, 0)) == REG_NOMATCH) {
//             if (grep.flag_substr == 1) {
//                 char *p = getsubstr(text, &pmatch);
//                 strcat(p, "\n");
//                 print(grep.flag_otputs, p, number_of_file, argv, 0,grep);
//                 char *str = NULL;
//                 str = text;
//                 str += pmatch.rm_eo;
//                 while (pmatch.rm_eo != -1 && (err = regexec(&myre, str, 1, &pmatch, 0)) == 0) {
//                     p = getsubstr(str, &pmatch);
//                     strcat(p, "\n");
//                     print(grep.flag_otputs, p, number_of_file, argv, 0,grep);
//                     str += pmatch.rm_eo;
//                 }
//             } else {
//                 print(grep.flag_otputs, text, number_of_file, argv, 0,grep);
//             }
//         }
//     }
//     if (text) free(text);
//     fclose(file);
//     regfree(&myre);
// }

// void grep_l(char *argv[], int number_of_file, opt grep) {
//     regex_t myre;
//     FILE *file = fopen(argv[number_of_file], "r");
//     int err;
//     size_t text_size = 0;
//     char *text = NULL;
//     ssize_t read;
//     int bool_ = 0;
//     char err_msg[MAX_ERR_LENGTH];
//     grep.flag_otputs = 2;
//     if (file == NULL) {
//         if (grep.flag_file_error_ouput == 0) printf("%s : No such file or directory\n",
//         argv[number_of_file]); return;
//     }
//     if ((err = regcomp(&myre, grep.pattern, 0)) != 0) {
//         regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
//         printf("Error analyzing regular expression '%s': %s.\n", grep.pattern, err_msg);
//         regfree(&myre);
//         return;
//     }
//     while ((read = getline(&text, &text_size, file)) != -1) {
//         if ((err = regexec(&myre, text, 0, NULL, 0)) == 0) {
//             bool_ = 1;
//         }
//     }
//     if (bool_ == 1) print(grep.flag_otputs, argv[number_of_file], 0, argv, 0,grep);
//     if (text) free(text);
//     fclose(file);
//     regfree(&myre);
// }

// void grep_h(char *argv[], int number_of_file, int argc) {
//     regex_t myre;
//     FILE *file = fopen(argv[number_of_file], "r");
//     int err;
//     size_t text_size = 0;
//     char *text = NULL;
//     ssize_t read;
//     char err_msg[MAX_ERR_LENGTH];
//     if (file == NULL) {
//         printf("%s : No such file or directory\n", argv[number_of_file]);
//         return;
//     }
//     if ((err = regcomp(&myre, argv[2], 0)) != 0) {
//         regerror(err, &myre, err_msg, MAX_ERR_LENGTH);
//         printf("Error analyzing regular expression '%s': %s.\n", argv[2], err_msg);
//         regfree(&myre);
//         return;
//     }
//     while ((read = getline(&text, &text_size, file)) != -1) {
//         if ((err = regexec(&myre, text, 0, NULL, 0)) == 0) {
//             if (argc >= 3) printf("%s", text);
//         }
//     }
//     if (text) free(text);
//     fclose(file);
//     regfree(&myre);
// }
void Multiple_File_Handler(char *argv[], void (*func)(char **, int, opt), int optind, int argc, opt grep) {
    while (optind < argc) {
        func(argv, optind, grep);
        optind++;
    }
}