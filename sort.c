#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_ITERS 1000
#define MAX_SIZE  100
#define MAX_VALUE 50000

#define CURSOR_RETURN    "\033[G"
#define CURSOR_RETURN_AB "\033[F"
#define HIDE_CURSOR      "\033[?25l"
#define SHOW_CURSOR      "\033[?25h"
#define CLEAR_LINE       "\033[K"
#define DEF_CLR          "\033[0m"
#define CYAN_CLR         "\033[0;36m"
#define BMAG_CLR         "\033[0;95m"
#define BGRN_CLR         "\033[0;92m"

int is_increasing ( int * a, size_t n )  {
    for ( size_t i = 1; i < n; i++ )
        if ( a[i - 1] > a[i]  ) return 0;
    return 1;
}

int * random_arr ( size_t n, size_t max ) {
    int * r = ( int * ) malloc ( sizeof ( *r ) * n );
    for ( size_t i = 0; i < n; i++ )
        r[i] = rand ( ) % max;
    return r;
}

void print ( int * a, size_t n ) {
    printf ( "{ " );
    for ( size_t i = 0; i < n; i++ )
        printf ( "%d ", a[i] );
    printf ( "}\n" );
}

void swap ( int * a, int * b ) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shuffle ( int * a, size_t n ) {
    for ( size_t i = 0; i < n; i++ )
        swap ( &a[i], &a[rand() % n] );
}

size_t bogo ( int * a, size_t n ) {
    size_t iter = 1;
    while ( ! is_increasing ( a, n ) ) {
        iter++;
        shuffle ( a, n );
    }
    return iter - 1;
}

size_t bubble ( int * a, size_t n ) {
    size_t iter = 1;
    for ( size_t i = 0; i < n; i++ ) {
        for ( size_t j = 0; j < n - i - 1; j++ ) {
            if ( a[j] > a[j + 1] )
                swap ( &a[j], &a[j + 1] );
            iter++;
        }
    }
    return iter - 1;
}

void sort_random ( size_t n, size_t max, size_t (*sort_fnc) ( int *, size_t ) ) {
    int * a = random_arr ( n, max );
    printf ( "=======================\n" );
    clock_t start, end;
    size_t iter;

    printf ( "n = %zd\n", n );
    start = clock ( );
    iter = sort_fnc ( a, n );
    end = clock ( );
    //Sorted check
    assert ( is_increasing ( a, n ) );
    //print ( a, n );
    printf ( "%s", CYAN_CLR );
    printf ( "Elapsed Time: %lf\n", ( ( double ) ( end - start ) ) / CLOCKS_PER_SEC );
    printf ( "%s", BMAG_CLR );
    printf ( "Algorithm iterations count: %zd\n", iter );
    printf ( "%s", DEF_CLR );
    free ( a );
}

int main ( void ) {
    srand ( time ( NULL ) );
    clock_t start, end;
    #ifndef __RANDOM_RUN__
    start = clock ( );
    size_t els = 0;
    for ( size_t i = 0; i < MAX_ITERS; i++ ) {
        sort_random ( i + 1, rand ( ) % MAX_VALUE, bubble );
        els += i + 1;
    }
    end = clock ( );

    printf ( "\n%s[ALL] Elapsed time: %lf\n%s", BGRN_CLR, ( ( double ) ( end - start ) ) / CLOCKS_PER_SEC, DEF_CLR );
    printf ( "%sTotal number of elements sorted: %zd%s\n", CYAN_CLR, els, DEF_CLR );

    #endif

    #ifdef __RANDOM_RUN__
    start = clock ( );
    sort_random ( 15, 100, bogo );
    end = clock ( );
    #endif

    return 0;
}