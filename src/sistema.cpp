#include "usuario.h"
#include "sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
  Usuario a, st_email, st_senha, st_nome;
  st_nome.nome = nome;
  st_email.email = email;
  st_senha.senha = senha;
  a.id;
  a.id = 1;


  int tam, result, tam_email, aux = 0;
  tam = usuarios.size();

  if(tam == 0){//ele é o 1º usuario a ser criado
    result = 1;

    usuarios.push_back(st_nome);
    usuarios.push_back(st_email);
    usuarios.push_back(st_senha);
    
    tam = 3;

    id_usuario.push_back(1);
    email_validos.push_back(st_email.email);

    return "\nUsuário criado!\n";

  }else if(tam >= 3){
    tam_email = email_validos.size();

    for(int i = 0; i < tam_email; i++){//descobre se o usuário existe
      if(email_validos[i] == st_email.email){
        aux++;
      }
    }
   
    if(aux > 0){
      return "\nUsuário já existe\n";
    }else{
      email_validos.push_back(st_email.email);//preenche no vector o novo email valido p/ futuras comparações
      usuarios.push_back(st_nome);//vector do tipo usuario preenchendo com informações de usuarios criados
      usuarios.push_back(st_email);
      usuarios.push_back(st_senha);
      tam = usuarios.size();
      result = tam/3;
      id_usuario.push_back(result);
      return "\nUsuário criado\n";
    }
  }

 /* cout << "\ntamanho: " << tam << "\n";
  cout << "\nvalor de result: " << result << endl;*/
  //cout << "\nO id: " << a.id << "\n";
 /* cout << "nome usuario: " << st_nome.nome << "\n";
  cout << "email usuario: " << st_email.email << "\n";
  cout << "senha usuario: " << st_senha.senha << "\n";*/
  //cout << "\nO create-user não está implementado ainda\n";
  return "create_user NÃO IMPLEMENTADO";
}

string Sistema::login(const string email, const string senha) {
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
