#include <iostream>
#include "servidor.h"
using namespace std;

int Servidor::getID(){
    return usuarioDonold;
}

void Servidor::setID(int id){
    usuarioDonold = id;
}

string Servidor::getNome_servidor(){
    return nome;
}

void Servidor::setNome_servidor(string nome_servidor){
    nome = nome_servidor;
}

string Servidor::getDescricao(){
    return descricao;
}

void Servidor::setDescricao(string descricao_servidor){
    descricao = descricao_servidor;
}

string Servidor::getCodigoConvite(){
    return codigoConvite;
}

void Servidor::setCodigoConvite(string codigo_convite){
    codigoConvite = codigo_convite;
}

void Servidor::adicionarParticipantes(int id){
    participantesIDs.push_back(id);
}

void Servidor::testarParticipantes(int id){
    cout << "HEY" << endl;
    int tam = participantesIDs.size();
    cout << "Tamanho de participantes: " << tam << endl;
    /*for (int i = 0; i < 4; i++) {
        cout << "HELLO";
    }*/
    /*for(auto itr = participantesIDs.begin(); itr != participantesIDs.end(); itr++){
        cout << "HELLO" << endl;
        //cout << "Participantes: " << (*itr) << endl;
    }*/
}
