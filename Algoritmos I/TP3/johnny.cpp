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
#include <bits/stdc++.h> 
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
    vector<int> _td;
    int a, b;
    cin >> a >> b;
    _td.push_back( 0 );
    _td.push_back( 0 );
    td.push_back( _td );

    vector<double> custos;
    for( int s=0; s<d; s++ ) {
        int span = 0;
        double custo = 0.0f;
        double desconto = 0.0f;
        int c = 0;
        for( int i=0; i<=n; i++ ) {
            if( i>=s ) {
                if( span < t ) {
                    desconto += ( double )qtd[c+1]/100;
                    custo += ( td[i][1] * ( 1 - desconto ) );
                    span += td[i][0];
                } else if( span >= t ) {
                    desconto = 0.0f;
                    custo += ( td[i][1] * ( 1 - desconto ) );
                    span = 0;
                    c=0;
                }
                c++;
            } else {
                custo += ( td[i][1] * ( 1 - desconto ) );
            }
        }
        custos.push_back( custo );
    }

    // Verificando o custo
    sort( custos.begin(), custos.end() );
    cout << custos[0] << setprecision(2) << endl;

	return 0; // finalizamos nossa implementação
}
