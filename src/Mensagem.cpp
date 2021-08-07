#include <iostream>
#include "Mensagem.h"
#include "usuario.h"

using namespace std;

string Mensagem::getData_hora(){
    return dataHora;
}

void Mensagem::setData_hora(string data_e_hora){
    dataHora = data_e_hora;
}

int Mensagem::getEnviadaPor(){
    return enviadaPor;
}

void Mensagem::setEnviadaPor(int id_que_enviou){
    enviadaPor = id_que_enviou;
}

string Mensagem::getConteudo(){
    return conteudo;
}

void Mensagem::setConteudo(string conteudo_mensagem){
    conteudo = conteudo_mensagem;
}



