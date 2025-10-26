#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() 
{
    char username[50];
    char fileContent[50];
    char sl;

    puts(
        "                                ____ \n"
        "                       / __ \\ / ____|\n"
        " __  ___ __ __ _ _   _| |  | | (___  \n"
        " \\ \\/ / '__/ _` | | | | |  | |\\___ \\\n"
        "  >  <| | | (_| | |_| | |__| |____) |\n"
        " /_/\\_\\_|  \\__,_|\\__, |\\____/|_____/\n"
        "                  __/ |              \n"
        "                 |___/               \n"
    );
    printf("Formerly karsonOS\n");
    printf("v2.0.0a\n\n");

    printf("Do you want to sign up or log in? (s/l) ");
    scanf(" %c", &sl);

    //sign up
    if (sl == 's') { 
        FILE *file = fopen("userDetails.txt", "w");
        if (file == NULL) {
            perror("ERROR: FILE NOT FOUND");
            return 1;
        }

        printf("\nCreate a username: ");
        scanf(" %49[^\n]", username);

        fprintf(file, "%s", username);
        fclose(file);
        printf("Account created successfully.\n");
        goto login_part;
    }

login_part:  

    if (sl == 'l' || sl == 's') { 
        FILE *file = fopen("userDetails.txt", "r");
        if (file == NULL) {
            perror("ERROR: FILE NOT FOUND");
            return 1;
        }

        printf("Enter your username: ");
        scanf(" %49[^\n]", username);

        if (fgets(fileContent, sizeof(fileContent), file) == NULL) {
            printf("Error reading file.\n");
            fclose(file);
            return 1;
        }
        fclose(file);

        fileContent[strcspn(fileContent, "\n")] = '\0';

        /* check login */
        if (strcmp(username, fileContent) == 0) {

            char input[50];
            /* example commands array (NULL-terminated) */
            char *commands[] = {
                "HELP - SHOWS THIS MENU",
                "EXIT - EXITS OS",
                "LS - LISTS CONTENTS OF CURRENT FOLDER",
                NULL
            };

            char *lsROOT[] = {
                "[xrayOS.C]",
                "[userDetails.txt]",
                NULL
            };

            /* LOGIN SUCCESSFUL */
            printf("\nWelcome, %s\n", username);

cmdline:

            printf("\n~/> ");

            /* skip any leftover whitespace/newline, then read input up to newline */
            scanf(" %49[^\n]", input);

            /* normalize input to lowercase for case-insensitive comparison */
            for (char *q = input; *q; ++q) {
                *q = (char)tolower((unsigned char)*q);
            }

            if (strcmp(input, "help") == 0) {
                printf("\n!!COMMANDS!!\n");
                for (char **p = commands; *p != NULL; ++p) {
                    printf("%s\n", *p);
                }
                goto cmdline;
            }
            else if (strcmp(input, "exit") == 0) {
                exit(0);
            }
            else if (strcmp(input, "ls") == 0) {
                for (char **p = lsROOT; *p != NULL; ++p) {
                    printf("%s\n", *p);
                }
                goto cmdline;
            }
            return 0;
        }
                 else {
            printf("ERROR!");
        }
    }
}