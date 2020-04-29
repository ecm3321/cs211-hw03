#include "libvc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This definition is private to this file; code in all other files
// can only handle pointers to it: values of type `struct vote_count*`
// (a/k/a `vote_count_t`), not values of type `struct vote_count`. Only
// code in this file sees this definition, so only code in this file can
// work with `struct vote_count`s directly.
struct vote_count
{
    char*  candidate;
    size_t count;
};

// A vote_count_t will be a pointer to a `malloc`ed array of
// MAX_CANDIDATES `struct vote_count`s, with the following invariant:
//
//  - Some prefix of `candidate` fields are distinct, OWNED, `malloc`ed
//  strings, and the remaining `candidate` fields are NULL.
//
//  - When a `candidate` field is NULL the value of the corresponding
//  `count` does not mean anything, but when the `candidate` is non-NULL
//  then the `count` must be a properly initialized count.

/*
 * Q: Where are header comments for the following functions?
 * A: libvc.h
 */

// Returns a pointer to the first element of 'vc' whose 'candidate' matches     
// 'name', or NULL if there is no such element.                                 
static struct vote_count* vc_find_name (vote_count_t vc, const char * name)
{
    size_t i = 0;
    while (i < MAX_CANDIDATES && vc[i].candidate != NULL){
        if(strcmp(vc[i].candidate, name) == 1 ){
            return &vc[i];
        }
        i = i + 1;
    }
    return NULL;
}

//Returns a pointer to the first element of 'vc' whose 'candidate' is NULL,     
// or NULL if 'vc' is full.                                                     
static struct vote_count* vc_find_empty(vote_count_t vc)
{
    size_t i = 0;
    while (i < MAX_CANDIDATES){
        if(vc[i].candidate == NULL){
            return &vc[i];
        }
        i = i + 1;
    }
    return NULL;
}

// Clones a string onto the heap, printing a message to stderr and exiting with
// code 1 if malloc() fails.                                                    
//static char* strdup_or_else(const char* src)                                  
//{                                                                             
//}    

vote_count_t vc_create(void)
{
    sizze_t i = 0;
    vote_count_t result = malloc(MAX_CANDIDATES * sizeof(struct vote_count));
    while (result[i].candidate != NULL && i < MAX_CANDIDATES) {
        result[i].candidate = NULL;
        i = i + 1;
        return result;
    }
    return NULL;
}

void vc_destroy(vote_count_t vc)
{
    size_t i = 0;
    while (i < MAX_CANDIDATES && vc[i].candidate != NULL) {
        free(vc->candidate);
	vc = vc	+ 1;
        i = i + 1;
    }
}

size_t* vc_update(vote_count_t vc, const char *name)
{
    //
   vote_count match_element= vc_find_name(vc, name); //should i have the *?
    
    if( match_element != NULL) //should it be *name? or *match_element, am i supposed to use *?
    {
        return ptr_to_element -> count;
    }
    else{
        vote_count next= vc_find_empty(vc);
        struct vote_count new_element= {name, 0};
        *next= new_element;
        return next -> count;
    }
 
    //
    return NULL;
}


size_t vc_lookup(vote_count_t vc, const char* name)
{
    //
    // TODO: replace with your code:
    //
    return 0;
}

size_t vc_total(vote_count_t vc)
{
    //
    // TODO: replace with your code:
    //
    return 0;
}

const char* vc_max(vote_count_t vc)
{
    //
    // TODO: replace with your code:
    //
    return NULL;
}

const char* vc_min(vote_count_t vc)
{
    //
    // TODO: replace with your code:
    //
    return NULL;
}

void vc_print(vote_count_t vc)
{
    //
    // TODO: your code here
    //
}
