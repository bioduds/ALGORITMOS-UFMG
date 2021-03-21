/***********************************************************
** Disciplina: Algoritmos I 
** Título: Trabalho Prático II - As viagens de João da Silva
** Autor: Eduardo Capanema
** Contato: eduardocapanema@ufmg.br
** Matrícula: 2020041515
/***********************************************************

/** PACOTES E INCLUSÕES **/
#include <iostream> 
#include <vector> 
using namespace std;

 
/************* FUNÇÃO MAIN *************/
int main() {
    // LEITURA
    int n, d, t; // qtd escalas, qtd maxima de escalas com descontos cum. no int. T e tempo máximo p/ aplicação
    cin >> n >> d >> t;

    // check limits
    if( n<1 || n>10000 || d<2 || d>100 || t<1 || t>1000 ) {
        printf( "Favor checar os limites de entrada\n" );
        return 0;
    }
    
    vector<int> qtd;
    for( int i=0; i<d; i++ ) { // percorre qtd escalas
        int q;
        cin >> q;
        qtd.push_back( q );
    }

    vector< vector<int> > tempos;
    for( int j=0; j<n; j++ ) {
        vector<int> t_gasto;
        int a, b;
        cin >> a >> b;
        t_gasto.push_back( a );
        t_gasto.push_back( b );
        tempos.push_back( t_gasto );
    }

    for( int i=0; i<n; i++ ) {
        int pago = 0;
        int time = 0;

        for( int j=0; j<d && time<t && i+j<=n; j++ ) {
            printf( "Que que tem isso\n" );
        }
    }

    // Visualizar leitura
    // printf( "n, d, t_max: %d %d %d\n", n, d, t );
    // printf( "QUANTS: " );
    // for( int i=0; i<qtd.size(); i++ ) {
    //     printf( " %d", qtd[i] );
    // }
    // printf( "\n" );
    // for( int i=0; i<tempos.size(); i++ ) {
    //     printf( " %d - %d\n", tempos[i][0], tempos[i][1] );
    // }

	return 0; // finalizamos nossa implementação
}
