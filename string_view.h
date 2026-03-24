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

char *sv_to_string(String_View *sv){
    char *s = (char*)malloc(sv->length+1);
    memcpy(s,sv->data,sv->length);
    s[sv->length] = '\0';
    return s;
}