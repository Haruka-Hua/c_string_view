# String_View

A simple and efficient C library for handling string views/slices without unnecessary memory allocation. I was inspired by this video [C 语言的字符串太糟糕了！ | Tsoding](https://www.bilibili.com/video/BV16kAjzzEck/?share_source=copy_web&vd_source=267788d5bc046ec90dbdd1a97885eeaf), and decided to try to make my own implement as a practice.

## Overview

This library provides a `String_View` struct, which is a non-owning reference to a sequence of characters. It consists of a pointer to the character data and its length. This approach allows for efficient string manipulation (like splitting or trimming) by modifying the view's pointer and length, rather than copying the underlying character array.

## Structure

- `String_View`: A struct containing:
    - `const char *data`: A pointer to the start of the character sequence.
    - `size_t length`: The number of characters in the sequence.

## Functions

- `make_sv(const char * data)`: Creates a `String_View` from a null-terminated C string.
- `sv_chop_right(String_View* sv, size_t count)`: Removes `count` characters from the end of the view. If `count` is greater than the view's length, the view becomes empty.
- `sv_chop_left(String_View* sv, size_t count)`: Removes `count` characters from the beginning of the view by advancing its internal pointer. If `count` is greater than the view's length, the view becomes empty.
- `sv_trim_left(String_View* sv)`: Removes whitespace characters from the beginning of the view.
- `sv_trim_right(String_View* sv)`: Removes whitespace characters from the end of the view.
- `sv_trim(String_View* sv)`: Removes whitespace characters from both ends of the view.
- `sv_split_by_delim(String_View* sv, char delim)`: Splits the view at the first occurrence of `delim`. Returns a new `String_View` for the part before the delimiter. The original view (`sv`) is modified to start after the delimiter. If the delimiter is not found, it returns a copy of the original view and makes the input view empty.
- `sv_to_string(String_View *sv)`: Allocates a new C string (null-terminated) containing a copy of the view's data. The caller is responsible for freeing the returned pointer with `free()`.
- `sv_substr(String_View *sv, size_t start, size_t end)`: Returns a new `String_View` representing the substring in the range `[start, end)`. Bounds are automatically clamped to the original view's length.
- `sv_prefix(String_View *sv, size_t length)`: Returns a new `String_View` containing the first `length` characters of `sv`. If `length` is greater than `sv->length`, the entire view is returned.
- `sv_suffix(String_View *sv, size_t start)`: Returns a new `String_View` starting from offset `start` to the end of `sv`. If `start` is greater than `sv->length`, an empty view is returned.
- `sv_split_by_type(String_View *sv, int (*type)(int c))`: Splits the view at the first character where the provided function `type(c)` returns true. Returns a new `String_View` for the part before the delimiter. The original view (`sv`) is modified to start after the delimiter. If no such character is found, it returns a copy of the original view and makes the input view empty.

## Macros

- `SvPrtFmt`: A format specifier string (`"%.*s"`) for use with `printf`-style functions.
- `SvPrtArg(sv)`: A macro that expands to the two arguments required by `SvPrtFmt` to print a `String_View`. Usage: `printf(SvPrtFmt, SvPrtArg(my_sv))`.