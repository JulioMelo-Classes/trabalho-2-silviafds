#include <iostream>
#include <vector>
#include <algorithm>
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

bool Servidor::verificarParticipante(int id){
    for(auto itr = participantesIDs.begin(); itr != participantesIDs.end(); itr++){
        if((*itr) == id){
            return true;
        }
    }
}

void Servidor::mostrarParticipantes(vector<Usuario>& usuarios){
    for(auto itr = usuarios.begin(); itr != usuarios.end(); itr++){
        for(auto ptr = participantesIDs.begin(); ptr != participantesIDs.end(); ptr++){
            if(itr->id == (*ptr)){
                cout << itr->nome << endl;
            }
        }
    }
}

bool Servidor::criarCanais(string nome_do_canal){

    auto iter = find_if(canaisTexto.begin(), canaisTexto.end(), [nome_do_canal](CanalTexto objeto){
        if(objeto.getNomeCanal() == nome_do_canal){
            return true;
        } else{
            return false;
        } });    
 
    if(iter != canaisTexto.end()){//encontrou um objeto já existente
        return false; 
    } else{        
        CanalTexto obj;
        obj.setNomeCanal(nome_do_canal);
        canaisTexto.push_back(obj);
        //iter = canaisTexto.end()-1;
        return true;
    }   
}

void Servidor::mostrarCanais(){
    for(auto itr = canaisTexto.begin(); itr != canaisTexto.end(); itr++){
        cout << itr->getNomeCanal()<< endl;
    }
}

bool Servidor::verificarCanais(string nome_entrar_canal){

    auto iter = find_if(canaisTexto.begin(), canaisTexto.end(), [nome_entrar_canal](CanalTexto obj){
        if(obj.getNomeCanal() == nome_entrar_canal){
            return true; 
        } else{
            return false; 
        }
    });

    if(iter != canaisTexto.end()){
        return true;
    } else{
        return false;
    }
}

void Servidor::percorrerCanais(string data_hora, int id_remetente, string conteudo_da_mensagem, string canal_n){
    for(auto itr = canaisTexto.begin(); itr != canaisTexto.end(); itr++){
        if((*itr).getNomeCanal() == canal_n){
            itr->enviarMensagens(data_hora, id_remetente, conteudo_da_mensagem);
        }
    }
}

void Servidor::listarMensagensCanais(vector<Usuario>& usuarios, string canal, int id){

    for(auto itr = canaisTexto.begin(); itr != canaisTexto.end(); itr++){
        itr->listarMensagens(usuarios);
    }
}
