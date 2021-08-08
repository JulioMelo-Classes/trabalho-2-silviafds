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

void CanalTexto::enviarMensagens(string data_hora, int id_remetente, string conteudo_da_mensagem){

    Mensagem atributos_de_mensagens;

    atributos_de_mensagens.setData_hora(data_hora);
    atributos_de_mensagens.setEnviadaPor(id_remetente);
    atributos_de_mensagens.setConteudo(conteudo_da_mensagem);
    mensagens.push_back(atributos_de_mensagens);

    /*int tam = mensagens.size();

    cout << "Data: " << atributos_de_mensagens.getData_hora() << endl;
    cout << "Pessoa: " << atributos_de_mensagens.getEnviadaPor() << endl;
    cout << "Mensagem: " << atributos_de_mensagens.getConteudo() << endl;
    cout << "tam mensagens " << tam << endl;*/
}

void CanalTexto::listarMensagens(string nome_usuario){

    int tam = mensagens.size();

    for(auto itr = mensagens.begin(); itr != mensagens.end(); itr++){
        if(itr->getConteudo() != ""){
            cout << nome_usuario << itr->getData_hora() << ": " <<  itr->getConteudo() << endl;
            //cout << "MENSAGEM: " << itr->getConteudo() << endl;            
        } else {
            cout << "Sem mensagens para exibir." << endl;
        }
    }
}
