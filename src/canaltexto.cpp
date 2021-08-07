#include <iostream>
#include "canaltexto.h"
#include "Mensagem.h"
#include "usuario.h"
#include "sistema.h"

using namespace std;

string CanalTexto::getNomeCanal(){
    return nome;
}

void CanalTexto::setNomeCanal(string nome_canal){
    nome = nome_canal;
}

void CanalTexto::verificarMensagens(string data_hora, int id_remetente, string conteudo_da_mensagem){

    Mensagem obj;

    obj.setData_hora(data_hora);
    obj.setEnviadaPor(id_remetente);
    obj.setConteudo(conteudo_da_mensagem);
    mensagens.push_back(obj);

    cout << "Data: " << obj.getData_hora() << endl;
    cout << "Pessoa: " << obj.getEnviadaPor() << endl;
    cout << "Mensagem: " << obj.getConteudo() << endl;

    /*for(auto itr = mensagens.begin(); itr != mensagens.end(); itr++ ){
        cout << "Data: " << itr->getData_hora() << endl;
        cout << "Pessoa: " << itr->getEnviadaPor() << endl;
        cout << "Mensagem: " << itr->getConteudo() << endl;
    }*/    
}

