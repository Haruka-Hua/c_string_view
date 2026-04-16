# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# define SvPrtArg(sv) (int)(sv).length, (sv).data
# define SvPrtFmt "%.*s"

typedef struct {
    const char *data;
    size_t length;
} String_View;

String_View make_sv(const char * data){
    String_View s = (String_View){
        .data = data,
        .length = strlen(data),
    };
    return s;
}

void sv_chop_right(String_View* sv, size_t count){
    if(sv->length < count){
        count = sv->length;
    }
    sv->length -= count;
}

void sv_chop_left(String_View* sv, size_t count){
    if(sv->length < count){
        count = sv->length;
    }
    sv->data += count;
    sv->length -= count;
}

void sv_trim_left(String_View* sv){
    while (sv->length>0 && isspace(sv->data[0])){
        sv_chop_left(sv,1);
    }
}

void sv_trim_right(String_View* sv){
    while (sv->length>0 && isspace(sv->data[sv->length-1])){
        sv_chop_right(sv,1);
    }
}

void sv_trim(String_View* sv){
    sv_trim_left(sv);
    sv_trim_right(sv);
}

String_View sv_split_by_delim(String_View* sv, char delim){
    size_t delim_pos = 0;
    while (delim_pos<sv->length && sv->data[delim_pos]!=delim){
        delim_pos += 1;
    }
    if(delim_pos < sv->length){
        String_View res = (String_View){
            .data = sv->data,
            .length = delim_pos,
        };
        sv_chop_left(sv,delim_pos+1);
        return res;
    }
    else{
        String_View  res = *sv;
        sv_chop_left(sv,sv->length);
        return res;
    }
}

/*
Split a string view by a type of delimiters.
*/
String_View sv_split_by_type(String_View *sv, int (*type)(int c)){
    size_t delim_pos = 0;
    while (delim_pos<sv->length && !type(sv->data[delim_pos])){
        delim_pos += 1;
    }
    if(delim_pos < sv->length){
        String_View res = (String_View){
            .data =  sv->data,
            .length = delim_pos,
        };
        sv_chop_left(sv,delim_pos+1);
        return res;
    } else {
        String_View res = *sv;
        sv_chop_left(sv,sv->length);
        return res;
    }
}

char *sv_to_string(String_View *sv){
    char *s = (char*)malloc(sv->length+1);
    memcpy(s,sv->data,sv->length);
    s[sv->length] = '\0';
    return s;
}

/*
Return substring in range [start,end).
Return an empty String_View if pair (start, end) is invalid.
*/
String_View sv_substr(String_View *sv, size_t start, size_t end){
    if (end > sv->length){
        end = sv->length;
    }
    if (start > end){
        start = end;
    }
    String_View res = (String_View){
        .data = sv->data + start,
        .length = end-start,
    };
    return res;
}

/* 
Return prefix with length length.
If length < length of the String_View, then return the whole String_View.
*/
String_View sv_prefix(String_View *sv, size_t length){
    if (length > sv->length){
        length = sv->length;
    }
    String_View res = (String_View){
        .data = sv->data,
        .length = length,
    };
    return res;
}

/* 
Return suffix with length length.
If length < length of the String_View, then return the whole String_View.
*/
String_View sv_suffix(String_View *sv, size_t start){
    if(start > sv->length){
        start = sv->length;
    }
    String_View res = (String_View){
        .data = sv->data + start,
        .length = sv->length - start,
    };
    return res;
}

int sv_starts_with(const String_View *sv, const String_View *prefix){
    if(sv->length < prefix->length)
        return 0;
    int x =  memcmp(sv->data, prefix->data, prefix->length)==0;
    return x;
}

int sv_ends_with(const String_View *sv, const String_View *suffix){
    if(sv->length < suffix->length)
        return 0;
    return memcmp(sv->data, suffix->data, suffix->length)==0;
}

int sv_contains(const String_View *sv, const String_View *sub){
    if(sv->length < sub->length)
        return 0;
    int start_pos = 0;
    while(start_pos + sub->length <= sv->length){
        if(memcmp(sv->data+start_pos, sub->data, sub->length)==0)
            return 1;
        start_pos++;       
    }
    return 0;
}

int sv_is_empty(String_View *sv){
    return sv->length == 0;
}

int sv_eq(const String_View *sv1, const String_View *sv2){
    if(sv1->length != sv2->length)
        return 0;
    return memcmp(sv1->data, sv2->data, sv1->length)==0;
}

size_t sv_length(String_View *sv){
    return sv->length;
}

void print_sv(const String_View* sv){
    printf(SvPrtFmt,SvPrtArg(*sv));
}
