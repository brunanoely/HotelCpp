#ifndef ESTADIA_H
#define ESTADIA_H

#include <string>
#include <set>
#include <fstream>
#include <vector>
#include "quarto.h"  
#include "cliente.h"  
#include "funcionario.h"  

class Estadia {
private:
    int codigo;
    int data_entrada;
    int data_saida;
    int quant_diarias;
    int codigo_cliente;
    int numero_quarto;
    int codigo_funcionario;
    float valor_diaria;

    static vector<Estadia> estadias;

public:

    Estadia();  

    int getCodigo() const;
    void setCodigo(int codigo);
    int getDataEntrada() const;
    void setDataEntrada(int data_entrada);
    int getDataSaida() const;
    void setDataSaida(int data_saida);
    int getQuantDiarias() const;
    void setQuantDiarias(int quant_diarias);
    int getCodigoCliente() const;
    void setCodigoCliente(int codigo_cliente);
    int getNumeroQuarto() const;
    void setNumeroQuarto(int numero_quarto);
    int getCodigoFuncionario() const;
    void setCodigoFuncionario(int codigo_funcionario);
    float getValorTotal() const;
    void setValorTotal(float valor_total);

    static int calcularDiarias(int data_entrada, int data_saida);
    void cadastrarEstadia();
    void exibir() const;
    void mostrarEstadiasPorCliente(); 
    void baixarValorPago();
    float calcularValorTotal() const;
    float obterValorDaria(int numeroQuarto);
    void calcularValorArrecadadoPorMes();

    static void salvarEstadias();
    static bool validarCliente(int codigoCliente); 
    static bool validarFuncionario(int codigoFuncionario);
};

#endif
