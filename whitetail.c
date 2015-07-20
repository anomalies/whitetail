/*
 * whitetail - trim trailing whitespace from the input lines
 * Andrew Watts - 2015 <andrew@andrewwatts.info>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WT_MAX_LINE_SIZE 8096

static int wt_trim_whitespace(char *const line, const char *match_set);
static int wt_try_match_set(char input, const char *match_set);

static char line_buffer[WT_MAX_LINE_SIZE];

int main(int argc, char **argv) {
    unsigned int line_number;
    const char *match_set = " \t";

    if (argc >= 2) {
        if (argc > 2 || strcmp(argv[1], "-s") != 0) {
            printf("Usage: %s <-s>\n\tDefault (no options): removes trailing spaces and tabs from the input stream.\n\t-s: only remove trailing spaces.\n", argv[0]);
            return -1;
        }

        match_set = " ";
    }

    for (line_number = 1; fgets(line_buffer, sizeof(line_buffer), stdin) != NULL; ++line_number) {
        if (wt_trim_whitespace(line_buffer, match_set) != 0) {
            fprintf(stderr, "Error: unable to trim line %u as it exceeds maximum line length %u\n",
                    line_number,
                    WT_MAX_LINE_SIZE
            );

            return -1;
        }
    }

    return 0;
}

static int wt_trim_whitespace(char *const line, const char *match_set) {
    char *last_whitespace = line;
    char *scan;

    for (scan = line; *scan != '\n'; ++scan) {
        char c = *scan;

        if (c == '\0') {
            if ((scan - line) == WT_MAX_LINE_SIZE)
                return -1;

            last_whitespace[0] = '\0';
            fputs(line, stdout);
            return 0;
        }

        if (wt_try_match_set(c, match_set) == 0) {
            continue;
        }

        last_whitespace = scan + 1;
    }

    last_whitespace[0] = '\n';
    last_whitespace[1] = '\0';

    fputs(line, stdout);
    return 0;
}

static int wt_try_match_set(char input, const char *match_set) {
    for(; *match_set != '\0'; ++match_set) {
        if (input == *match_set) {
            return 0;
        }
    }

    return 1;
}
