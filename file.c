# include <stdio.h>
# include <ctype.h>
# include "string_view.h"

int main(){
    FILE* fp = fopen(__FILE__, "rb");
    char buffer[1024*1024];
    fread(buffer,1,sizeof(buffer),fp);
    String_View s = make_sv(buffer);
    int word_cnt = 0;
    while(s.length>0){
        String_View line = sv_split_by_type(&s,isspace);
        sv_trim(&line);
        if(line.length==0){
            continue;
        }
        printf("|"SvPrtFmt"|\n",SvPrtArg(line));
        word_cnt += 1;
    }
    printf("Number of words: %d\n",word_cnt);
    return 0;
}