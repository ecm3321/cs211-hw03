#include "../src/libvc.h"
#include <lib211.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static void test_create_destroy(void)
{
    vc_destroy(vc_create());
}


static void test_2_candidates(void)
{
    size_t* cp;//what is cp?
    vote_count_t vc = vc_create();
    assert(vc);

    CHECK_POINTER( vc_max(vc), NULL );//what is check pointer?
    CHECK_POINTER( vc_min(vc), NULL );
    CHECK_SIZE( vc_lookup(vc, "alice"), 0 );
    CHECK_SIZE( vc_lookup(vc, "bob"), 0 );
    CHECK_SIZE( vc_total(vc), 0 );


    cp = vc_update(vc, "alice");//what is going on here?
    CHECK( cp );//checking that cp is not null
    ++*cp;
    CHECK_STRING( vc_max(vc), "alice" );
    CHECK_STRING( vc_min(vc), "alice" );
    CHECK_SIZE( vc_lookup(vc, "alice"), 1 );
    CHECK_SIZE( vc_lookup(vc, "bob"), 0 );

    CHECK_SIZE( vc_total(vc), 1 );

    cp = vc_update(vc, "bob");
    CHECK( cp );
    ++*cp;
    CHECK_STRING( vc_max(vc), "alice" );//max tie
    CHECK_STRING( vc_min(vc), "bob" );//min tie

    cp = vc_update(vc, "alice");
    CHECK( cp );
    ++*cp;
    CHECK_STRING( vc_max(vc), "alice" );
    CHECK_STRING( vc_min(vc), "bob" );
    CHECK_SIZE( vc_lookup(vc, "alice"), 2 );
    CHECK_SIZE( vc_lookup(vc, "bob"), 1 );
    CHECK_SIZE( vc_total(vc), 3 );

    cp = vc_update(vc, "bob");//here down not working
    CHECK( cp );
    ++*cp;
    cp = vc_update(vc, "bob");
    CHECK( cp );
    ++*cp;
    cp = vc_update(vc, "alice");
    CHECK( cp );
    ++*cp;
    CHECK_STRING( vc_max(vc), "alice" );
    CHECK_STRING( vc_min(vc), "bob" );
    //CHECK_SIZE( vc_lookup(vc, "alice"), 3 );//checking if tie
    //CHECK_SIZE( vc_lookup(vc, "bob"), 3 );


    //vc_destroy(vc);
    //vc = NULL;
    vc_destroy(vc);
}



//
static void test_max_candidates(void)
{
    size_t* cp;
    vote_count_t vc = vc_create();
    assert(vc);

    size_t i = 0;

    const char* array[26] = {"a","b","c","d","e","f","g","h","i","j","k",
                             "l","m","n","o","p","q","r","s","t","u","v",
                             "w","x","y","z"};
    while (i < 26){
        cp = vc_update(vc, array[i]);
        if(i >= MAX_CANDIDATES){
            CHECK( !cp );
            break;
        } else {
            CHECK( cp );
            ++*cp;
            i = i + 1;
        }
    }
    CHECK_SIZE( vc_total(vc), MAX_CANDIDATES);

    vc_destroy(vc);
}
//

int main(void)
{
    test_create_destroy();
    test_2_candidates();
}
