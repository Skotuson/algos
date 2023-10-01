#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int is_increasing ( int * a, size_t n )  {
    for ( size_t i = 1; i < n; i++ )
        if ( a[i - 1] > a[i]  ) return 0;
    return 1;
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
        swap ( a[i], a[rand() % n] );
}

void bogo ( int * a, size_t n ) {
    srand ( time ( NULL ) );
    while ( ! is_increasing ( a, n ) )
        shuffle ( a, n );
}

int main ( void ) {
    
    return 0;
}