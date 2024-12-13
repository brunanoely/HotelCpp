#include <iostream>
#include <string>
#include "usecase/cliente.h"
#include "usecase/funcionario.h"
#include "usecase/quarto.h"
#include "usecase/estadia.h"
#include "repository/repository.h"

using namespace std;

void verificarDiretorio();

void cleanTerminal() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void menu() {
    
    cout << "\n1. Cadastrar Cliente" << endl;
    cout << "2. Cadastrar Funcionário" << endl;
    cout << "3. Cadastrar Quarto" << endl;
    cout << "4. Cadastrar Estadia" << endl;
    cout << "5. Pesquisar Cliente por codigo" << endl;
    cout << "6. Pesquisar funcionario por codigo" << endl;
    cout << "7. Mostrar todas as estadias de um Cliente" << endl;
    cout << "8. Baixar valor pago de uma Estadia" << endl;
    cout << "9. Calcular valor arrecadado pelo Hotel em um mês" << endl;
    cout << "10. Sair\n";
    cout << "Escolha uma opção: ";
}

int main() {
    int opcao;

    do {
        menu();
        cin >> opcao;

        switch (opcao) {
            case 1: {
                cleanTerminal();
                Cliente cliente;
                cliente.cadastrarCliente();
                break;
            }
            case 2: {
                cleanTerminal();
                Funcionario funcionario;
                funcionario.cadastrarFuncionario();
                break;
            }
            case 3: {
                Quarto quarto;
                cleanTerminal();
                quarto.cadastrarQuarto();
                break;
            }
            case 4: {
                Estadia estadia;
                cleanTerminal();
                estadia.cadastrarEstadia();
                break;
            }
            case 5: {
                Cliente cliente;
                cleanTerminal();
                cliente.pesquisarPorCodigo(); 
                break;
            }
            case 6: {
                Funcionario funcionario;
                cleanTerminal();
                funcionario.pesquisarPorCodigo();
                break;
            }
            case 7: {
                Estadia estadia;
                cleanTerminal();
                estadia.mostrarEstadiasPorCliente();
                break;
            }
            case 8: {
                Estadia estadia;
                cleanTerminal();
                estadia.baixarValorPago();
                break;
            }
            case 9: {
                Estadia estadia;
                cleanTerminal();
                estadia.calcularValorArrecadadoPorMes();
                break;
            }
            case 10:
                cout << "Encerrando o sistema...\n";
                break;
            default:
                cout << "Opção inválida! Tente novamente.\n";
                break;
        }
    } while (opcao != 10);

    return 0;
}

