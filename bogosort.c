#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITERS 25
#define MAX_SIZE  100
#define MAX_VALUE 1500

#define CURSOR_RETURN "\033[G"
#define HIDE_CURSOR   "\033[?25l"
#define SHOW_CURSOR   "\033[?25h"


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

void bogo ( int * a, size_t n ) {
    srand ( time ( NULL ) );
    size_t iter = 0;
    printf ( "%s", HIDE_CURSOR );
    while ( ! is_increasing ( a, n ) ) {
        printf ( "Iterations: %zd", iter );
        shuffle ( a, n );
        iter++;
        printf ( "%s", CURSOR_RETURN );
    }
    printf ( "%s", SHOW_CURSOR );
}

void sort_random ( size_t n, size_t max ) {
    int * a = random_arr ( n, max );
    printf ( "Before sorting:\n" );
    print ( a, n );

    clock_t start, end;
    
    start = clock ( );
    bogo ( a, n );
    end = clock ( );
    printf ( "After sorting:\n" );
    print ( a, n );

    printf ( "One sort time: %lf\n", ( ( double ) ( end - start ) ) / CLOCKS_PER_SEC );

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

    printf ( "Time elapsed: %lf\n", ( ( double ) ( end - start ) ) / CLOCKS_PER_SEC );
    #endif

    #ifndef __RANDOM_RUN__
    start = clock ( );
    sort_random ( 15, 100 );
    end = clock ( );
    #endif

    return 0;
}