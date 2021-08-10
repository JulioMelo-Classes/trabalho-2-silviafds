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

}

void CanalTexto::listarMensagens(vector<Usuario>& usuarios){

    int tam = mensagens.size();

    if(tam == 0){
        cout << "Sem mensagens para exibir." << endl;
    }else{
        for(auto itr = mensagens.begin(); itr != mensagens.end(); itr++){
            for (auto ptr = usuarios.begin(); ptr != usuarios.end(); ptr++){
                if(ptr->id == itr->getEnviadaPor()){
                    //if(itr->getConteudo() != ""){
                        cout << ptr->nome << itr->getData_hora() << ": " <<  itr->getConteudo() << endl;
                    //}
                }
            }
        }
    }
}
