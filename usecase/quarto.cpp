#include "quarto.h"
#include "repository.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>

using namespace std;

set<int> Quarto::quartosUsados;
vector<Quarto> Quarto::quartos;

Quarto::Quarto() : numero(0), quant_hospedes(0), valor_diaria(0.0f) {}

int Quarto::getNumero() const { return numero; }
void Quarto::setNumero(int numero) { this->numero = numero; }
int Quarto::getHospedes() const { return quant_hospedes; }
void Quarto::setHospedes(int quant_hospedes) { this->quant_hospedes = quant_hospedes; }
float Quarto::getDiarias() const { return valor_diaria; }
void Quarto::setDiarias(float valor_diaria) { this->valor_diaria = valor_diaria; }

void Quarto::cadastrarQuarto() {
    verificarDiretorio(); 
    carregarQuartos();

    cout << "Digite o número do quarto: ";
    cin >> numero;

    while (quartosUsados.count(numero) > 0) {
        cout << "Número do quarto já cadastrado. Digite outro: ";
        cin >> numero;
    }

    quartosUsados.insert(numero); 

    cout << "Digite a quantidade de hóspedes: ";
    cin >> quant_hospedes;

    cout << "Digite o valor da diária: ";
    cin >> valor_diaria;

    quartos.push_back(*this);
    salvarQuartos();

    cout << "Quarto cadastrado com sucesso!" << endl;
}

void Quarto::carregarQuartos() {
    verificarDiretorio(); 

    ifstream arquivo(REPOSITORIO + "quartos.dat", ios::binary);
    if (!arquivo.is_open()) {
        return; 
    }

    quartos.clear();
    quartosUsados.clear();   

    Quarto q;
    while (arquivo.read(reinterpret_cast<char*>(&q), sizeof(Quarto))) {
        quartos.push_back(q);
        quartosUsados.insert(q.getNumero());
    }

    arquivo.close();
}

void Quarto::exibir() const {
    cout << "\nNúmero do Quarto: " << numero
         << "\nQuantidade de Hóspedes: " << quant_hospedes
         << "\nValor da Diária: " << valor_diaria << endl;
}

bool Quarto::procurarQuartoDisponivel(int quant_hospedes, int& numeroQuarto) {
    verificarDiretorio(); 

    ifstream arquivo(REPOSITORIO + "quartos.dat", ios::binary);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de quartos.\n";
        return false;
    }

    Quarto quarto;
    while (arquivo.read(reinterpret_cast<char*>(&quarto), sizeof(Quarto))) {
        
        if (quarto.getHospedes() >= quant_hospedes) {
            numeroQuarto = quarto.getNumero(); 
            arquivo.close();
            return true; 
        }
    }

    arquivo.close();
    return false; 
}

void Quarto::salvarQuartos() {
    verificarDiretorio(); 

    ofstream arquivo(REPOSITORIO + "quartos.dat", ios::binary | ios::trunc);
    if (!arquivo) {
        cerr << "Erro ao salvar os dados dos quartos no arquivo." << endl;
        return;
    }

    for (const Quarto& q : quartos) {
        arquivo.write(reinterpret_cast<const char*>(&q), sizeof(Quarto));
    }

    arquivo.close(); 
}
