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
    qtd.push_back( 0 );
    for( int i=0; i<d; i++ ) { // percorre qtd escalas
        int q;
        cin >> q;
        qtd.push_back( q );
    }

    vector< vector<int> > td;
    for( int j=0; j<n; j++ ) {
        vector<int> _td;
        int a, b;
        cin >> a >> b;
        _td.push_back( a );
        _td.push_back( b );
        td.push_back( _td );
    }

    int span = 0;
    int duracao = 0;
    float custo = 0;

    for( int i=0; i<n; i++ ) {
        duracao += td[i][0];
        printf( "Mostra o span: %d\n", span );
        // aplicar desconto
        printf( "Mostra o disconto: %f e o valor: %d\n", (float)qtd[i+1]/100, td[i][1] );
        if( span < t ) {
            custo += ( td[i][1] * ( 1 - (float)qtd[i+1]/100 ) );
            span += td[i][0];
            if( span >= t ) {
                span = 0;
                span += td[i][0];
            }
        }
    }

    printf( "Duracao: %d, Custo: %f\n", duracao, custo );

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
