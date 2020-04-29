#include "libvc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define OOM_MESSAGE     "%s: error: out of memory\n"

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
    if (vc[i].candidate != NULL) {
        while (i < MAX_CANDIDATES && vc[i].candidate != NULL && name != NULL){ \

            if(strcmp(name, vc[i].candidate) == 0){
                return &vc[i];
            }
            i = i + 1;
        }
    }
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
static char* strdup_or_else(const char* src)
{
    int n = strlen(src);
    char* q = malloc(sizeof(char) * n + 1);
    if (q != NULL) {
        strcpy(q, src);
        return q;
    } else {
        fprintf(stderr, OOM_MESSAGE, src);
        return NULL;
    }
}


vote_count_t vc_create(void)
{
    size_t i = 0;
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
        vc = vc + 1;
        i = i + 1;
    }
}

size_t* vc_update(vote_count_t vc, const char *name)
{
   if(vc[0].candidate != NULL){
        struct vote_count* match_element = vc_find_name(vc, name);
        if (match_element != NULL) {
            return &(match_element -> count);
        } else {
            struct vote_count* next = vc_find_empty(vc);
            struct vote_count new_element = {strdup_or_else(name), 0};
            *next = new_element;
            return &(next -> count);
        }
    }
    return NULL;
}



size_t vc_lookup(vote_count_t vc, const char* name)
{
    size_t i = 0;
    if (vc[i].candidate != NULL){
        struct vote_count* exists = vc_find_name(vc, name);
        if(exists != NULL){
            return exists -> count;
        }
    }
    return 0;
}



size_t vc_total(vote_count_t vc)
{
    size_t i = 0;
    size_t sum = 0;
    if (vc[i].candidate != NULL){
        while (i < MAX_CANDIDATES && vc[i].candidate != NULL){
            sum = sum + vc[i].count;
            i = i + 1;
        }
        return sum;
    }
    return 0;
}

const char* vc_max(vote_count_t vc)
{
size_t i = 0;
    size_t t = 0;
    size_t max = vc[i].count;
    if (vc[i].candidate != NULL){
        while (i < MAX_CANDIDATES && vc[i].candidate != NULL){
            if(vc_lookup(vc, vc[i].candidate) > max){
                max = vc_lookup(vc, vc[i].candidate);
                t = i;
            }
            i = i + 1;
        }
        return vc[t].candidate;
    }
    return NULL;
}

const char* vc_min(vote_count_t vc)
{
   size_t i = 0;
    size_t t = 0;
    size_t min = vc_lookup(vc, vc_max(vc));
    if (vc[i].candidate != NULL){
        while (i < MAX_CANDIDATES && vc[i].candidate != NULL){
            if(vc_lookup(vc, vc[i].candidate) < min
               && vc_lookup(vc, vc[i].candidate) != 0){
                min = vc_lookup(vc, vc[i].candidate);
                t = i;
            }
            i = i + 1;
        }
        if (min > 0) {
            return vc[t].candidate;
        }
    }
    return NULL;
}


void vc_print(vote_count_t vc)
{
    //
    size_t i=0;
    while(vc[i]!=NULL)
    {
        printf("%s %1f \n",vc[i].candidate, vc[1].count);
    }


