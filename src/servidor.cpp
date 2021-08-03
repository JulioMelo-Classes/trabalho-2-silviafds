#include <iostream>
#include <vector>
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

void Servidor::excluirParticipante(int id){

    int cont = 0;

    for(auto itr = participantesIDs.begin(); itr != participantesIDs.end(); itr++){
        if((*itr) == id){
            participantesIDs.erase(participantesIDs.begin()+cont);
            break;
        }
        cont += 1;            
    }
}

void Servidor::testarParticipantes(string name){
    int tam = participantesIDs.size();
    cout << "Tamanho de participantes " << name << ": " << tam << endl;
}

bool Servidor::verificarParticipante(int id){
    for(auto itr = participantesIDs.begin(); itr != participantesIDs.end(); itr++){
        if((*itr) == id){
            return true;
        }else{
            return false;
        }
    }
}
