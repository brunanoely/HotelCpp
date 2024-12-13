#include "cliente.h"
#include <string.h>
#include <iostream>
#include <limits>
#include <filesystem>
#include "repository/repository.h"

set<int> Cliente::codigosUsados;
vector<Cliente> Cliente::clientes;

Cliente::Cliente() : codigo(0), telefone(0) {
    memset(nome, 0, sizeof(nome));
    memset(endereco, 0, sizeof(endereco));
}

int Cliente::getCodigo() const { return codigo; }
void Cliente::setCodigo(int codigo) { this->codigo = codigo; }

const char* Cliente::getNome() const {
    return nome;
}
void Cliente::setNome(const string& n) {
    strncpy(nome, n.c_str(), sizeof(nome) - 1);
    nome[sizeof(nome) - 1] = '\0';
}

const char* Cliente::getEndereco() const {
    return endereco;
}
void Cliente::setEndereco(const string& e) {
    strncpy(endereco, e.c_str(), sizeof(endereco) - 1);
    endereco[sizeof(endereco) - 1] = '\0';
}

int Cliente::getTelefone() const { return telefone; }
void Cliente::setTelefone(int telefone) { this->telefone = telefone; }

void Cliente::cadastrarCliente() {
    verificarDiretorio(); 

    cout << "Digite o código do cliente: ";
    cin >> codigo;

    if (codigosUsados.count(codigo) > 0) {
        cout << "Código já existe, escolha outro." << endl;
        return;
    }

    codigosUsados.insert(codigo);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Digite o nome do cliente: ";
    cin.getline(nome, sizeof(nome));

    cout << "Digite o endereço do cliente: ";
    cin.getline(endereco, sizeof(endereco));

    cout << "Digite o telefone: ";
    cin >> telefone;

    ifstream arquivoLeitura(REPOSITORIO + "clientes.dat", ios::binary);
    Cliente clienteExistente;
    while (arquivoLeitura.read(reinterpret_cast<char*>(&clienteExistente), sizeof(Cliente))) {
        if (clienteExistente.codigo == codigo) {
            cout << "Erro: Cliente com esse código já existe no arquivo!" << endl;
            arquivoLeitura.close();
            return;
        }
    }
    arquivoLeitura.close();

    ofstream arquivo(REPOSITORIO + "clientes.dat", ios::binary | ios::app);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo para gravação!" << endl;
        return;
    }

    arquivo.write(reinterpret_cast<const char*>(this), sizeof(Cliente));
    arquivo.close();

    cout << "Cliente cadastrado com sucesso!" << endl;
}

void Cliente::pesquisarPorCodigo() {
    verificarDiretorio(); 

    int codigoPesquisa;
    cout << "Digite o código do cliente para pesquisa: ";
    cin >> codigoPesquisa;

    ifstream arquivo(REPOSITORIO + "clientes.dat", ios::binary);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo clientes.dat!" << endl;
        return;
    }

    Cliente cliente;
    bool clienteEncontrado = false;

    while (arquivo.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        if (cliente.getCodigo() == codigoPesquisa) {
            cliente.exibir();
            clienteEncontrado = true;
            break;
        }
    }

    if (!clienteEncontrado) {
        cout << "Cliente com código " << codigoPesquisa << " não encontrado." << endl;
    }

    arquivo.close();
}

void Cliente::carregarClientes() {
    verificarDiretorio(); 

    ifstream arquivo(REPOSITORIO + "clientes.dat", ios::binary);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo de clientes para leitura." << endl;
        return;
    }

    clientes.clear();
    codigosUsados.clear();

    Cliente c;
    while (arquivo.read(reinterpret_cast<char*>(&c), sizeof(Cliente))) {
        clientes.push_back(c);
        codigosUsados.insert(c.getCodigo());
    }

    arquivo.close();
    cout << "Clientes carregados com sucesso!" << endl;
}

void Cliente::listarCliente() {
    verificarDiretorio();

    ifstream arquivo(REPOSITORIO + "clientes.dat", ios::binary);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo clientes.dat!" << endl;
        return;
    }

    Cliente cliente;
    while (arquivo.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))) {
        cliente.exibir();
    }

    arquivo.close();
}

void Cliente::salvarClientes() {
    verificarDiretorio(); 

    ofstream arquivo(REPOSITORIO + "clientes.dat", ios::binary | ios::trunc);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo para salvar.\n";
        return;
    }

    for (const Cliente& c : clientes) {
        arquivo.write(reinterpret_cast<const char*>(&c), sizeof(Cliente));
    }
    arquivo.close();
}

void Cliente::exibir() const {
    cout << "Código: " << codigo << endl;
    cout << "Nome: " << nome << endl;
    cout << "Endereço: " << endereco << endl;
    cout << "Telefone: " << telefone << endl;
}