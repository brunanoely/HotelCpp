#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <string.h>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

class Funcionario {
private:
    int codigo;
    char nome[50];
    char telefone[20];
    char cargo[30];
    float salario;

    static set<int> codigosUsados;           
    static vector<Funcionario> funcionarios; 

public:

    Funcionario();

    int getCodigo() const;
    void setCodigo(int codigo);
    const char* getNome() const;
    void setNome(const std::string&);
    const char* getTelefone() const;
    void setTelefone(const std::string&);
    const char* getCargo() const;
    void setCargo(const std::string&);
    float getSalario() const;
    void setSalario(float salario);


    void cadastrarFuncionario();
    void exibir() const;

   
    static void pesquisarPorCodigo();
    static void carregarFuncionarios();
    static void salvarFuncionarios();
};

#endif
