#include "funcionario.h"
#include "repository.h"
#include <iostream>
#include <filesystem>

using namespace std;

set<int> Funcionario::codigosUsados;
vector<Funcionario> Funcionario::funcionarios;

Funcionario::Funcionario() : codigo(0), salario(0.0) {
    memset(nome, 0, sizeof(nome));
    memset(telefone, 0, sizeof(telefone));
    memset(cargo, 0, sizeof(cargo));
}

int Funcionario::getCodigo() const { return codigo; }
void Funcionario::setCodigo(int codigo) { this->codigo = codigo; }
const char* Funcionario::getNome() const { return nome; }

void Funcionario::setNome(const string& n) {
    strncpy(nome, n.c_str(), sizeof(nome) - 1); 
    nome[sizeof(nome) - 1] = '\0'; 
}

const char* Funcionario::getTelefone() const { return telefone; }

void Funcionario::setTelefone(const string& t) {
    strncpy(telefone, t.c_str(), sizeof(telefone) - 1);
    telefone[sizeof(telefone) - 1] = '\0';
}

const char* Funcionario::getCargo() const { return cargo; }

void Funcionario::setCargo(const string& c) {
    strncpy(cargo, c.c_str(), sizeof(cargo) - 1);
    cargo[sizeof(cargo) - 1] = '\0';
}

float Funcionario::getSalario() const { return salario; }
void Funcionario::setSalario(float salario) { this->salario = salario; }

void Funcionario::cadastrarFuncionario() {
    verificarDiretorio();

    cout << "Digite o código do funcionário: ";
    cin >> codigo;

    while (codigosUsados.count(codigo) > 0) {
        cout << "Código já existente. Digite outro código: ";
        cin >> codigo;
    }
    codigosUsados.insert(codigo);

    cin.ignore(); 

    cout << "Digite o nome do funcionário: ";
    cin.getline(nome, sizeof(nome));

    cout << "Digite o telefone do funcionário: ";
    cin.getline(telefone, sizeof(telefone));

    cout << "Digite o cargo do funcionário: ";
    cin.getline(cargo, sizeof(cargo));

    cout << "Digite o salário do funcionário: ";
    cin >> salario;

    funcionarios.push_back(*this);
    salvarFuncionarios(); 

    cout << "Funcionário cadastrado com sucesso!" << endl;
}

void Funcionario::exibir() const {
    cout << "\nCódigo: " << codigo;
    cout << "\nNome: " << nome;
    cout << "\nTelefone: " << telefone;
    cout << "\nCargo: " << cargo;
    cout << "\nSalário: R$" << salario << "\n";
}

void Funcionario::pesquisarPorCodigo() {
    verificarDiretorio();

    int codigoPesquisa;
    cout << "Digite o código do funcionário para pesquisar: ";
    cin >> codigoPesquisa;

    ifstream arquivo(REPOSITORIO + "funcionarios.dat", ios::binary); 
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    Funcionario funcionario;
    bool funcionarioEncontrado = false;

    while (arquivo.read(reinterpret_cast<char*>(&funcionario), sizeof(Funcionario))) {
        if (arquivo.gcount() != sizeof(Funcionario)) {
            cout << "Erro na leitura do arquivo!" << endl;
            break;
        }

        if (funcionario.getCodigo() == codigoPesquisa) {
            funcionario.exibir();  
            funcionarioEncontrado = true;
            break;  
        }
    }

    if (!funcionarioEncontrado) {
        cout << "Funcionário com código " << codigoPesquisa << " não encontrado.\n";
    }

    arquivo.close();
}

void Funcionario::carregarFuncionarios() {
    verificarDiretorio();

    ifstream arquivo(REPOSITORIO + "funcionarios.dat", ios::binary);
    if (!arquivo) {
        cout << "Nenhum arquivo encontrado. Inicializando lista vazia.\n";
        return;
    }

    funcionarios.clear();
    codigosUsados.clear();

    Funcionario f;
    while (arquivo.read(reinterpret_cast<char*>(&f), sizeof(Funcionario))) {
        funcionarios.push_back(f);
        codigosUsados.insert(f.getCodigo());
    }
    arquivo.close();
}

void Funcionario::salvarFuncionarios() {
    verificarDiretorio();

    ofstream arquivo(REPOSITORIO + "funcionarios.dat", ios::binary | ios::trunc);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo para salvar.\n";
        return;
    }

    for (const Funcionario& f : funcionarios) {
        arquivo.write(reinterpret_cast<const char*>(&f), sizeof(Funcionario));
    }
    arquivo.close();
}
