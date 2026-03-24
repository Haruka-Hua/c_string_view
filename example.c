// example.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_view.h"

int main() {
    // --- Example 1: Basic Creation and Printing ---
    printf("--- Example 1: Basic Creation and Printing ---\n");
    char text[] = "Hello, World!";
    String_View sv = make_sv(text);

    printf("Original string: %s\n", text);
    printf("String_View content: " SvPrtFmt "\n", SvPrtArg(sv));
    printf("Length: %zu\n\n", sv.length);

    // --- Example 2: Trimming ---
    printf("--- Example 2: Trimming ---\n");
    char text_with_spaces[] = "  \t  Trim me   \n";
    String_View trim_sv = make_sv(text_with_spaces);
    printf("Before trim: '" SvPrtFmt "'\n", SvPrtArg(trim_sv));

    sv_trim(&trim_sv);
    printf("After trim:  '" SvPrtFmt "'\n\n", SvPrtArg(trim_sv));

    // --- Example 3: Chopping ---
    printf("--- Example 3: Chopping ---\n");
    char text_to_chop[] = "abcdef";
    String_View chop_sv = make_sv(text_to_chop);
    printf("Initial: " SvPrtFmt "\n", SvPrtArg(chop_sv));

    sv_chop_left(&chop_sv, 2);
    printf("Chop left 2: " SvPrtFmt "\n", SvPrtArg(chop_sv));

    sv_chop_right(&chop_sv, 1);
    printf("Chop right 1: " SvPrtFmt "\n\n", SvPrtArg(chop_sv));

    // --- Example 4: Splitting ---
    printf("--- Example 4: Splitting ---\n");
    char csv_line[] = "apple,banana,cherry,end";
    String_View split_sv = make_sv(csv_line);
    String_View token;

    printf("Splitting the line: " SvPrtFmt "\n", SvPrtArg(split_sv));
    while (split_sv.length > 0) { // Keep going until the view is empty
        token = sv_split_by_delim(&split_sv, ',');
        printf("Token: [" SvPrtFmt "]\n", SvPrtArg(token));
    }
    printf("\n");

    // --- Example 5: Converting back to C-string ---
    printf("--- Example 5: Converting back to C-string ---\n");
    char temp_str[] = "temporary";
    String_View cstr_sv = make_sv(temp_str);

    // Chop it to demonstrate we're only converting a part of the original buffer
    sv_chop_right(&cstr_sv, 4); // Now it should be "temp"
    
    char * extracted_cstr = sv_to_string(&cstr_sv);
    if (extracted_cstr != NULL) {
        printf("Extracted C-string: '%s'\n", extracted_cstr);
        free(extracted_cstr); // Don't forget to free the allocated memory!
    } else {
        printf("Failed to allocate memory for C-string.\n");
    }

    return 0;
}