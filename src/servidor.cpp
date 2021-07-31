#include "servidor.h"


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
