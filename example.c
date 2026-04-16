// example.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isspace, isdigit, etc.
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

    // --- Example 4: Splitting by Delimiter ---
    printf("--- Example 4: Splitting by Delimiter ---\n");
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
    printf("\n");

    // --- Example 6: Substring Functions ---
    printf("--- Example 6: Substring Functions ---\n");
    char subtext[] = "Hello, World!";
    String_View sub_sv = make_sv(subtext);

    printf("Original: " SvPrtFmt "\n", SvPrtArg(sub_sv));

    // Using sv_substr
    String_View sub1 = sv_substr(&sub_sv, 7, 12); // "World"
    printf("sv_substr(7, 12): " SvPrtFmt "\n", SvPrtArg(sub1));

    // Using sv_prefix
    String_View sub2 = sv_prefix(&sub_sv, 5); // "Hello"
    printf("sv_prefix(5): " SvPrtFmt "\n", SvPrtArg(sub2));

    // Using sv_suffix
    String_View sub3 = sv_suffix(&sub_sv, 7); // "World!"
    printf("sv_suffix(7): " SvPrtFmt "\n\n", SvPrtArg(sub3));

    // --- Example 7: Splitting by Type ---
    printf("--- Example 7: Splitting by Type ---\n");
    char mixed_text[] = "word1 123 word2 456 word3";
    String_View type_split_sv = make_sv(mixed_text);
    
    printf("Splitting by isspace (words): " SvPrtFmt "\n", SvPrtArg(type_split_sv));
    while (type_split_sv.length > 0) {
        String_View part = sv_split_by_type(&type_split_sv, isspace);
        printf("Part: [" SvPrtFmt "]\n", SvPrtArg(part));
    }
    printf("\n");

    // Reset the view for another example
    type_split_sv = make_sv(mixed_text);
    printf("Splitting by isdigit (non-digits): " SvPrtFmt "\n", SvPrtArg(type_split_sv));
    while (type_split_sv.length > 0) {
        String_View part = sv_split_by_type(&type_split_sv, isdigit);
        printf("Non-digit part: [" SvPrtFmt "]\n", SvPrtArg(part));
    }


    // --- Example 8: sv_starts_with & sv_ends_with ---
    printf("--- Example 8: sv_starts_with & sv_ends_with ---\n");
    String_View hello_sv = make_sv("hello world");
    String_View prefix_sv = make_sv("hello");
    String_View suffix_sv = make_sv("world");
    printf("Starts with 'hello': %s\n", sv_starts_with(&hello_sv, &prefix_sv) == 1 ? "YES" : "NO");
    printf("Ends with 'world': %s\n", sv_ends_with(&hello_sv, &suffix_sv) == 1 ? "YES" : "NO");
    printf("\n");

    // --- Example 9: sv_contains ---
    printf("--- Example 9: sv_contains ---\n");
    String_View contain_sv = make_sv("abcdefg");
    String_View sub_sv_1 = make_sv("cde");
    printf("Contains 'cde': %s\n", sv_contains(&contain_sv, &sub_sv_1) ? "YES" : "NO");
    String_View not_sub_sv = make_sv("xyz");
    printf("Contains 'xyz': %s\n", sv_contains(&contain_sv, &not_sub_sv) ? "YES" : "NO");
    printf("\n");

    // --- Example 10: sv_eq ---
    printf("--- Example 10: sv_eq ---\n");
    String_View eq1 = make_sv("abc");
    String_View eq2 = make_sv("abc");
    String_View eq3 = make_sv("abcd");
    printf("'abc' == 'abc': %s\n", sv_eq(&eq1, &eq2) ? "YES" : "NO");
    printf("'abc' == 'abcd': %s\n", sv_eq(&eq1, &eq3) ? "YES" : "NO");
    printf("\n");

    // --- Example 11: sv_is_empty & sv_length ---
    printf("--- Example 11: sv_is_empty & sv_length ---\n");
    String_View empty_sv = make_sv("");
    printf("Is empty: %s\n", sv_is_empty(&empty_sv) ? "YES" : "NO");
    printf("Length of 'hello world': %zu\n", sv_length(&hello_sv));
    printf("\n");

    return 0;
}