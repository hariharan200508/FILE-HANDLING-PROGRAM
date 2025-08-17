#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
void create_file(const char *fname);
void write_file(const char *fname);
void append_file(const char *fname);
void read_file(const char *fname);
int  is_tilde_line(const char *s);
void flush_stdin(void);
int main(void) {
    char filename[260];
    int choice;

    printf("==== File Handling Program ====\n");
    printf("Enter file name to work with: ");
    if (scanf("%259s", filename) != 1) {
        fprintf(stderr, "Failed to read file name.\n");
        return 1;
    }
    flush_stdin();

    do {
        printf("\n----------- MENU -----------\n");
        printf("1. Create (empty) file\n");
        printf("2. Write (overwrite) data\n");
        printf("3. Append data\n");
        printf("4. Read & display file\n");
        printf("5. Exit\n");
        printf("----------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Exiting.\n");
            return 1;
        }
        flush_stdin();

        switch (choice) {
            case 1: create_file(filename); break;
            case 2: write_file(filename);  break;
            case 3: append_file(filename); break;
            case 4: read_file(filename);   break;
            case 5: printf("Goodbye!\n");  break;
            default: printf("Invalid option. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
void create_file(const char *fname) {
    FILE *fp = fopen(fname, "w");
    if (!fp) {
        perror("Error creating file");
        return;
    }
    printf("File '%s' created (or truncated) successfully.\n", fname);
    fclose(fp);
}

void write_file(const char *fname) {
    FILE *fp = fopen(fname, "w");
    if (!fp) {
        perror("Error opening file for writing");
        return;
    }
    printf("Enter text to WRITE (overwrite). End with a line containing only '~'\n");

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), stdin)) {
        if (is_tilde_line(line)) break;
        fputs(line, fp);
    }

    printf("Data written to '%s'.\n", fname);
    fclose(fp);
}

void append_file(const char *fname) {
    FILE *fp = fopen(fname, "a");
    if (!fp) {
        perror("Error opening file for appending");
        return;
    }
    printf("Enter text to APPEND. End with a line containing only '~'\n");

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), stdin)) {
        if (is_tilde_line(line)) break;
        fputs(line, fp);
    }

    printf("Data appended to '%s'.\n", fname);
    fclose(fp);
}

void read_file(const char *fname) {
    FILE *fp = fopen(fname, "r");
    if (!fp) {
        perror("Error opening file for reading");
        return;
    }
    printf("\n----- Contents of '%s' -----\n", fname);

    char ch;
    while ((ch = (char)fgetc(fp)) != EOF) {
        putchar(ch);
    }

    printf("\n----------- END ------------\n");
    fclose(fp);
}
int is_tilde_line(const char *s) {
    if (s[0] == '~') {
        if (s[1] == '\n' || (s[1] == '\r' && s[2] == '\n') || s[1] == '\0')
            return 1;
    }
    return 0;
}

/* eat the rest of the current line from stdin */
void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
