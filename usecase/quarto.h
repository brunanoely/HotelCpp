#ifndef QUARTO_H
#define QUARTO_H

using namespace std;

#include <set>
#include <vector>
#include <string>

class Quarto {
private:
    int numero;
    int quant_hospedes;
    float valor_diaria;

    static set<int> quartosUsados;   
    static vector<Quarto> quartos;   

public:
    
    Quarto();

    int getNumero() const;
    void setNumero(int numero);
    int getHospedes() const;
    void setHospedes(int quant_hospedes);
    float getDiarias() const;
    void setDiarias(float valor_diaria);

    void cadastrarQuarto(); 
    void exibir() const;    

    static void carregarQuartos(); 
    static void salvarQuartos();  
    static bool procurarQuartoDisponivel(int quant_hospedes, int& numeroQuarto); 
};

#endif
