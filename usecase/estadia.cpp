#include <iostream>
#include <fstream>
#include <filesystem>
#include "repository.h"
#include "estadia.h"
#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"

using namespace std;

vector<Estadia> Estadia::estadias;

Estadia::Estadia() {
    codigo = 0;
    data_entrada = 0;
    data_saida = 0;
    quant_diarias = 0;
    codigo_cliente = 0;
    numero_quarto = 0;
    codigo_funcionario = 0;
    valor_diaria = 0.0f;
}

int calcularDiarias(int dataEntrada, int dataSaida) {
    int diaEntrada = dataEntrada % 100;
    int mesEntrada = (dataEntrada / 100) % 100;
    int anoEntrada = dataEntrada / 10000;

    int diaSaida = dataSaida % 100;
    int mesSaida = (dataSaida / 100) % 100;
    int anoSaida = dataSaida / 10000;

    int diasEntrada = anoEntrada * 365 + mesEntrada * 30 + diaEntrada;
    int diasSaida = anoSaida * 365 + mesSaida * 30 + diaSaida;

    return diasSaida - diasEntrada;
}

float obterValorDiaria(int numeroQuarto) {
    verificarDiretorio();
    ifstream arquivo(REPOSITORIO + "quartos.dat", ios::binary);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo de quartos.\n";
        return 0;
    }

    Quarto quarto;
    while (arquivo.read(reinterpret_cast<char*>(&quarto), sizeof(Quarto))) {
        if (quarto.getNumero() == numeroQuarto) {
            arquivo.close();
            return quarto.getDiarias();
        }
    }

    arquivo.close();
    return 0;
}

void Estadia::cadastrarEstadia() {
    verificarDiretorio();
    int codigoCliente, codigoFuncionario, quantidadeHospedes, dataEntrada, dataSaida;
    int numeroQuarto, codigoEstadia;

    cout << "Digite o código da estadia: ";
    cin >> codigoEstadia;

    cout << "Digite o código do cliente: ";
    cin >> codigoCliente;

    if (!validarCliente(codigoCliente)) {
        cout << "Cliente inválido.\n";
        return;
    }

    cout << "Digite o código do funcionário: ";
    cin >> codigoFuncionario;

    if (!validarFuncionario(codigoFuncionario)) {
        cout << "Funcionário inválido.\n";
        return;
    }

    cout << "Digite a quantidade de hóspedes: ";
    cin >> quantidadeHospedes;

    if (!Quarto::procurarQuartoDisponivel(quantidadeHospedes, numeroQuarto)) {
        cout << "Não há quartos disponíveis para " << quantidadeHospedes << " hóspedes.\n";
        return;
    }

    cout << "Quarto selecionado: " << numeroQuarto << endl;

    cout << "Digite a data de entrada (AAAAMMDD): ";
    cin >> dataEntrada;

    cout << "Digite a data de saída (AAAAMMDD): ";
    cin >> dataSaida;

    data_entrada = dataEntrada;
    data_saida = dataSaida;
    codigo_cliente = codigoCliente;
    numero_quarto = numeroQuarto;
    codigo_funcionario = codigoFuncionario;
    quant_diarias = calcularDiarias(dataEntrada, dataSaida);
    valor_diaria = obterValorDiaria(numeroQuarto);
    codigo = codigoEstadia;

    estadias.push_back(*this);
    salvarEstadias();

    cout << "Estadia cadastrada com sucesso no quarto " << numeroQuarto << ".\n";
}

void Estadia::salvarEstadias() {
    verificarDiretorio();
    ofstream arquivo(REPOSITORIO + "estadias.dat", ios::binary | ios::trunc);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo para salvar.\n";
        return;
    }

    for (const Estadia& e : estadias) {
        arquivo.write(reinterpret_cast<const char*>(&e), sizeof(Estadia));
    }
    arquivo.close();
}

bool Estadia::validarCliente(int codigoCliente) {
    verificarDiretorio();
    ifstream arquivo(REPOSITORIO + "clientes.dat", ios::binary);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo de clientes.\n";
        return false;
    }

    Cliente cliente;
    while (arquivo.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        if (cliente.getCodigo() == codigoCliente) {
            arquivo.close();
            return true;
        }
    }

    arquivo.close();
    cout << "Cliente com código " << codigoCliente << " não encontrado.\n";
    return false;
}

bool Estadia::validarFuncionario(int codigoFuncionario) {
    verificarDiretorio();
    ifstream arquivo(REPOSITORIO + "funcionarios.dat", ios::binary);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo de funcionários.\n";
        return false;
    }

    Funcionario funcionario;
    while (arquivo.read(reinterpret_cast<char*>(&funcionario), sizeof(Funcionario))) {
        if (funcionario.getCodigo() == codigoFuncionario) {
            arquivo.close();
            return true;
        }
    }

    arquivo.close();
    cout << "Funcionário com código " << codigoFuncionario << " não encontrado.\n";
    return false;
}

void Estadia::mostrarEstadiasPorCliente() {
    verificarDiretorio();
    int codigoPesquisa;

    cout << "Digite o código do cliente para pesquisa: ";
    cin >> codigoPesquisa;

    ifstream arquivoEstadias(REPOSITORIO + "estadias.dat", ios::binary);
    if (!arquivoEstadias) {
        cout << "Erro ao abrir o arquivo de estadias.\n";
        return;
    }

    Estadia estadia;
    bool encontrouEstadias = false;

    while (arquivoEstadias.read(reinterpret_cast<char*>(&estadia), sizeof(Estadia))) {
        if (estadia.codigo_cliente == codigoPesquisa) {
            cout << "\nEstadia encontrada:" << endl;
            cout << "Código da Estadia: " << estadia.codigo << endl;
            cout << "Número do Quarto: " << estadia.numero_quarto << endl;
            cout << "Data de Entrada: " << estadia.data_entrada << endl;
            cout << "Data de Saída: " << estadia.data_saida << endl;
            cout << "Quantidade de Diárias: " << estadia.quant_diarias << endl;
            cout << "Valor Total: R$ " << estadia.valor_diaria * estadia.quant_diarias << endl;
            encontrouEstadias = true;
        }
    }

    arquivoEstadias.close();

    if (!encontrouEstadias) {
        cout << "Nenhuma estadia encontrada para o cliente com código " << codigoPesquisa << ".\n";
    }
}

int Estadia::calcularDiarias(int dataEntrada, int dataSaida) {
    int diaEntrada = dataEntrada % 100;
    int mesEntrada = (dataEntrada / 100) % 100;
    int anoEntrada = dataEntrada / 10000;

    int diaSaida = dataSaida % 100;
    int mesSaida = (dataSaida / 100) % 100;
    int anoSaida = dataSaida / 10000;

    int diasEntrada = anoEntrada * 365 + mesEntrada * 30 + diaEntrada;
    int diasSaida = anoSaida * 365 + mesSaida * 30 + diaSaida;

    return diasSaida - diasEntrada;
}
float Estadia::calcularValorTotal() const {
    return valor_diaria * quant_diarias;
}

void Estadia::baixarValorPago() {

    verificarDiretorio();

    int codigoEstadia;
    cout << "Digite o código da estadia: ";
    cin >> codigoEstadia;

    fstream arquivo(REPOSITORIO + "estadias.dat", ios::in | ios::out | ios::binary);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de estadias.\n";
        return;
    }

    Estadia estadia;
    bool estadiaEncontrada = false;

    while (arquivo.read(reinterpret_cast<char*>(&estadia), sizeof(Estadia))) {
        if (estadia.codigo == codigoEstadia) {
            estadiaEncontrada = true;

            cout << "Valor total a ser pago: R$ " << estadia.calcularValorTotal() << endl;

            cout << "Digite o valor pago: ";
            float valorPago;
            cin >> valorPago;

            estadia.valor_diaria = valorPago / estadia.quant_diarias;
            arquivo.seekp(-static_cast<int>(sizeof(Estadia)), ios::cur);
            arquivo.write(reinterpret_cast<const char*>(&estadia), sizeof(Estadia));
            cout << "Estadia atualizada com sucesso!\n";
            break;
        }
    }

        if (!estadiaEncontrada) {
        cout << "Estadia com código " << codigoEstadia << " não encontrada.\n";
    }

    arquivo.close();
}


void Estadia::calcularValorArrecadadoPorMes() {

    verificarDiretorio();
    int mesDesejado, anoDesejado;
    cout << "Digite o mês (MM): ";
    cin >> mesDesejado;
    cout << "Digite o ano (AAAA): ";
    cin >> anoDesejado;

    ifstream arquivo(REPOSITORIO + "estadias.dat", ios::binary);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de estadias.\n";
        return;
    }

    Estadia estadia;
    float valorTotal = 0.0;

    while (arquivo.read(reinterpret_cast<char*>(&estadia), sizeof(Estadia))) {
        int mesEntrada = estadia.data_entrada / 100 % 100; // Extrai mês da data
        int anoEntrada = estadia.data_entrada / 10000;     // Extrai ano da data

        if (mesEntrada == mesDesejado && anoEntrada == anoDesejado) {
            valorTotal += estadia.calcularValorTotal();
        }
    }

    cout << "Valor total arrecadado no mês " << mesDesejado << "/" << anoDesejado << ": R$ " << valorTotal << endl;

    arquivo.close();
}

