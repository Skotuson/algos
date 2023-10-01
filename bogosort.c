#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITERS 13
#define MAX_SIZE  100
#define MAX_VALUE 1500

#define CURSOR_RETURN "\033[G"
#define HIDE_CURSOR   "\033[?25l"
#define SHOW_CURSOR   "\033[?25h"
#define CLEAR_LINE    "\033[K"
#define DEF_CLR       "\033[0m"
#define CYAN_CLR      "\033[0;36m"
#define BMAG_CLR      "\033[0;95m"

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

size_t bogo ( int * a, size_t n, int print ) {
    srand ( time ( NULL ) );
    size_t iter = 1;
    if ( print )
        printf ( "%s", HIDE_CURSOR );
    while ( ! is_increasing ( a, n ) ) {
        if ( print ) {
            printf ( "Bogosort Iterations: %zd", iter );
            printf ( "%s", CURSOR_RETURN );
        }

        iter++;
        shuffle ( a, n );
    }

    if ( print ) {
        printf ( "%s", CLEAR_LINE );
        printf ( "%s", SHOW_CURSOR );
    }
    return iter - 1;
}

void sort_random ( size_t n, size_t max ) {
    int * a = random_arr ( n, max );
    printf ( "=======================\n" );
    clock_t start, end;
    size_t iter;

    start = clock ( );
    iter = bogo ( a, n, 0 );
    end = clock ( );
    printf ( "n = %zd\n", n );
    print ( a, n );
    printf ( "%s", CYAN_CLR );
    printf ( "Elapsed Time: %lf\n", ( ( double ) ( end - start ) ) / CLOCKS_PER_SEC );
    printf ( "%s", BMAG_CLR );
    printf ( "Bogosort ran %zd times\n", iter );
    printf ( "%s", DEF_CLR );
    free ( a );
}

int main ( void ) {
    srand ( time ( NULL ) );
    clock_t start, end;
    #ifdef __RANDOM_RUN__
    start = clock ( );
    for ( size_t i = 0; i < MAX_ITERS; i++ )
        sort_random ( i + 1, rand ( ) % MAX_VALUE );
    end = clock ( );

    printf ( "[ALL] Elapsed time: %lf\n", ( ( double ) ( end - start ) ) / CLOCKS_PER_SEC );
    #endif

    #ifndef __RANDOM_RUN__
    start = clock ( );
    sort_random ( 15, 100 );
    end = clock ( );
    #endif

    return 0;
}