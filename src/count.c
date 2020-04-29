#include "libvc.h"
#include <lib211.h>
#include <stdio.h>

#define OOM_MESSAGE     "%s: out of memory\n"
#define DROP_MESSAGE    "%s: vote dropped: %s\n"
#define FINAL_MESSAGE   "%s: %zu vote(s) dropped\n"

int main(int argc, char* argv[])
{
size_t i = 0;
    size_t drop = 0;
    vote_count_t list = vc_create();
    if (list == NULL) {
        fprintf(stderr, OOM_MESSAGE, argv[0]);
        return 1;
    }

    const char* line;
    while ((line = read_line()) != NULL){
        size_t* cntpntr =  vc_update(list, line);
        if (i >= MAX_CANDIDATES || cntpntr == NULL){
            drop = drop + 1;
            fprintf(stderr, DROP_MESSAGE, argv[0], line);
            return 2;
        } else {
            *cntpntr = *cntpntr + 1;
        }
        free(line);
        i = i + 1;
    }
        vc_print(list);
        vc_destroy(list);
        if (i >= MAX_CANDIDATES){
            fprintf(stderr, FINAL_MESSAGE, argv[0], drop);
            return 2;
        }
}

