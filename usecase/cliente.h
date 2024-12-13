#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

class Cliente {
private:
    int codigo;
    char nome[50];      
    char endereco[100]; 
    int telefone;

    static set<int> codigosUsados;          
    static vector<Cliente> clientes;       

public:
    
    Cliente();

    int getCodigo() const;
    void setCodigo(int codigo);
    const char* getNome() const;
    void setNome(const string& n);
    const char* getEndereco() const;
    void setEndereco(const string& e);
    int getTelefone() const;
    void setTelefone(int telefone);


    void cadastrarCliente();  
    void exibir() const;    
    void listarCliente(); 

    static void pesquisarPorCodigo();  
    static void carregarClientes();    
    static void salvarClientes();   

};

#endif
