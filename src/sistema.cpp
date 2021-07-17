#include "usuario.h"
#include "sistema.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  Usuario st_nome;
  
  st_nome.email = email;
  
  int tam, id_result, tam_email, aux = 0;
  tam = usuarios.size();

  if(tam == 0){//ele é o 1º usuario a ser criado
    st_nome.id = 1;
    st_nome.email = email;
    st_nome.senha = senha;
    st_nome.nome = nome;

    usuarios.push_back(st_nome);
    email_validos.push_back(st_nome.email);

    /*cout << "\n";
    cout << st_nome.id << "\n";
    cout << st_nome.email << "\n";
    cout << st_nome.senha << "\n";
    cout << st_nome.nome << "\n";*/

    tam = usuarios.size();
    //cout << "Tamanho: " << tam << endl;
    return "\nUsuário criado!\n";

  } else if (tam >= 1){
    
    for(int i = 0; i < usuarios.size(); i++){//descobre se o usuário existe
      if( email_validos[i] == st_nome.email ){
        aux++;
      }
    }

    if(aux > 0){
      return "\nUsuário já existe!\n";
    }else{
      st_nome.id = tam + 1;
      st_nome.email = email;
      st_nome.senha = senha;
      st_nome.nome = nome;

      usuarios.push_back(st_nome);
      email_validos.push_back(st_nome.email);

      /*cout << st_nome.id << "\n";
      cout << st_nome.email << "\n";
      cout << st_nome.senha << "\n";
      cout << st_nome.nome << "\n";*/

      tam = usuarios.size();
      //cout << "Tamanho:: " << tam << endl;
    }

  }
  return "\nUsuário criado\n";

}
  
string Sistema::login(const string email, const string senha) {
  Usuario rec;
  string v;
  int ret;
  
  rec.email = email;
  validar_email.push_back(rec);

  cout << "Mostrar email:::: " << rec.email << endl;
  
  if((email.compare(usuarios)) == 0){
    cout << " is equal to "  << endl;
  }

  /*ret = strcmp(rec, usuarios);
  if (ret == 0){
    cout << "sao iguais";
  }*/

  int x = usuarios.size();
  cout << "tamanho: " << x << endl;

 
  /*for(int i = 0; i < x; i++){
    if(validar_email[0] == usuarios[i]){
      cout << "\nsão iguais\n";
    }
  }*/

  /*if (strcasecmp(v.c_str(), email.c_str()) == 0) {funciona usando strings
        cout << "strings: text1 and text2 match." << endl;
  }*/

  return "login NÃO IMPLEMENTADO";
}

string Sistema::disconnect(int id) {
  return "disconnect NÃO IMPLEMENTADO";
}

string Sistema::create_server(int id, const string nome) {
  return "create_server NÃO IMPLEMENTADO";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
  return "set_server_desc NÃO IMPLEMENTADO";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
  return "set_server_invite_code NÃO IMPLEMENTADO";
}

string Sistema::list_servers(int id) {
  return "list_servers NÃO IMPLEMENTADO";
}

string Sistema::remove_server(int id, const string nome) {
  return "remove_server NÃO IMPLEMENTADO";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
  return "enter_server NÃO IMPLEMENTADO";
}

string Sistema::leave_server(int id, const string nome) {
  return "leave_server NÃO IMPLEMENTADO";
}

string Sistema::list_participants(int id) {
  return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels(int id) {
  return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
  return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
  return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
  return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
  return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}




/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
