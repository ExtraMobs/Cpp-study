#include <iostream>
#include <time.h>
#include <string>

#define TAM 10

using namespace std;

int main()
{
    srand(time(NULL));
    int tabuleiro[TAM][TAM];
    bool ganhou;
    string tabuleiro_para_exibicao[TAM][TAM];
    string resposta;

    // Coloca as bombas no tabuleiro e escreve a exibicao padrao
    for (int y=0; y < TAM; y++){
        for (int x=0; x < TAM; x++){
            // o casting do RAND_MAX para o tipo float "(float)" é necessário pois
            // se não será retornado um inteiro e não um número flutuante.
            if (rand() / (float)RAND_MAX < 0.35){ // 0.35 = 35% de chance de ter uma bomba.
                tabuleiro[y][x] = 1;
            }else{
                tabuleiro[y][x] = 0;
            }
            tabuleiro_para_exibicao[y][x] = "#";
        }
    }


    bool jogo_ativo = true;

    while (jogo_ativo){
        for (int y=0;y<TAM;y++){
            if (y == 0){
                for(int indicador_y=0; indicador_y < TAM;indicador_y++){
                    cout << indicador_y+1 << " ";
                }
                cout << endl << endl;
            }
            for (int x=0;x<TAM;x++){
                cout << tabuleiro_para_exibicao[y][x] << " ";
            }
            // Indicador lateral da posição x
            cout << "  " << y+1;
            cout << endl;
        }

        // Coleta a coluna e linha para podermos somar as bombas
        int y,x;
        cout << endl << endl << "Escolha uma linha: ";
        cin >> resposta;
        y = std::stoi(resposta);
        y--;
        cout << endl << "Escolha uma coluna: ";
        cin >> resposta;
        x = std::stoi(resposta);
        x--;

        // Verifica se posição não contém uma bomba
        if (tabuleiro[y][x] == 1){
            ganhou = false;
            break;
        }

        // Soma as bombas das casas vizinhas
        // [x-1, y-1][x  ,y-1][x+1, y-1]  Representação das posições que ele lá.
        // [x-1, y  ][x  ,y  ][x+1, y  ]  Ele só não lê o que está fora da matriz
        // [x-1, y+1][x  ,y+1][x+1, y+1]  y é a linha e x é a coluna
        int total_bombas = 0;
        for(int sum_y=y-1; sum_y < y+2; sum_y++){
            if (sum_y > -1 && sum_y < TAM){
                for (int sum_x=x-1; sum_x < x+2; sum_x++){
                    if (sum_x > -1 && sum_y < TAM){
                        if (tabuleiro[sum_y%TAM][sum_x%TAM] == 1){
                            cout << sum_y << " " << sum_x;
                            total_bombas++;
                        }
                    }
                }
            }
        }
        tabuleiro_para_exibicao[y][x] = std::to_string(total_bombas);
        system("cls");
    }
    cout << endl;
    if (ganhou){
        cout << "Parabens, voce ganhou!!!";
    } else {
        cout << "Sinto muito, voce perdeu.";
    }

    // Exibe o tabuleiro
    cout << endl << endl;
    for (int y=0;y<TAM;y++){
        for (int x=0;x<TAM;x++){
            if (tabuleiro[y][x] == 1){
                cout << "X" << " ";
            }else{
                cout << "0" << " ";
            }
        }
        cout << endl;
    }
    system("pause > nul");
    return 0;
}
