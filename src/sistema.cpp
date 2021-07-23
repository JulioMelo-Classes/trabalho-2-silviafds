#include "usuario.h"
#include "sistema.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>
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

    tam = usuarios.size();
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

      tam = usuarios.size();
    }

  }
  return "\nUsuário criado\n";
}
  
string Sistema::login(const string email, const string senha) {
  
  int aux = 0;
  string completar("Logado como ");
  completar += email;
  
  for(auto ptr = usuarios.begin(); ptr != usuarios.end(); ptr++){
    if(email.compare((*ptr).email) == 0 && senha.compare((*ptr).senha) == 0){
      aux++;
      usuariosLogados.insert({(*ptr).id, {" " , " "}});
    }
  } 

  /*for(auto itr = usuariosLogados.begin(); itr != usuariosLogados.end(); itr++){
    cout << "quem fez login foi o id: " << itr->first << "\n";
  } */  

  if(aux > 0){
    return completar;
  } 

  return "\nSenha ou usuário inválidos!\n";

}

string Sistema::disconnect(int id) {
  Usuario avisoemail;
  string completar2("Desconectando usuário ");
  int x = 0, y = 0, chave;
  chave = id;
  x = usuariosLogados.size();//descobre tamanho do map
                            //se o map for 0 é porque ninguém fez login
                            //se o map for maior que 0 é pq pessoas fizeram login

  if(x == 0){//quando não existe pessoas logadas
    return "Não está conectado.";
  }else{//existem pessoas logadas

    if(usuariosLogados.find(id) != usuariosLogados.end()) {
      for(auto ptr = usuarios.begin(); ptr != usuarios.end(); ptr++){
        if((*ptr).id == chave){
          cout << (*ptr).email << endl;
          completar2 += (*ptr).email;
          usuariosLogados.erase(id);
          return completar2;
        }
      } 
    }
  }

  return "Não está conectado.";
}

string Sistema::create_server(int id, const string nome) {

  Servidor nome_do_servidor(id, nome);
  int tam = servidores.size();
  int aux = 0;
  
  //cout << "ID que está criando: " << nome_do_servidor.getID() << endl;
  //cout << "Nome do servidor: " << nome_do_servidor.getNome_servidor() << endl;

  if (tam == 0){
    servidores.push_back(nome_do_servidor);
    return "Servidor criado.";
  } else{
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){  
      if(nome.compare((*itr).getNome_servidor()) == 0){
        return "Servidor com esse nome já existe.";
      }
    }
  }

  servidores.push_back(nome_do_servidor);

  return "Servidor criado.";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {

  Servidor informacoes(id, nome);
  Servidor verificar_desc(descricao);
  string completar3("Descrição do servidor '");
  string completar4("' modificada!");
  string completar5("Servidor '");
  string completar6("' não existe!");

  for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
    if((*itr).getNome_servidor() == nome){
      if((*itr).getID() == id){
        verificar_desc.getDescricao();
        completar3 += (*itr).getNome_servidor();
        completar3 += completar4;
        cout << "Descrição: " << verificar_desc.getDescricao();
        return completar3;
      }
      else{
        return "Você não pode alterar a descrição de um servidor que não foi criado por você!";
      }
    }
  }   

  completar5 += nome;
  completar5 += completar6;

  return completar5;
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {

  Servidor convite(id, nome, codigo);
  string completar7("Código de convite do servidor '");
  string completar8("' modificado!");
  string completar9("' removido!");

  int tam = codigo.length();

  for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
    if((*ptr).getNome_servidor() == nome){
      if((*ptr).getID() == id){
        if (tam == 0){
          completar7 += nome;
          completar7 += completar9;
          return completar7;
        } else {        
          convite.getCodigo();
          completar7 += nome;
          completar7 += completar8;
          return completar7;
        }
      } else {
          return "Você não pode alterar a descrição de um servidor que não foi criado por você!";
      }
    }
  }
  return "Servidor não existe.";
}

string Sistema::list_servers(int id) {

  Servidor lista_servidores(id);
  string completar10("\n");

  cout << "SERVIDORES:";
  cout << endl;
  for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
    if((*itr).getID2() == id){
      cout << ((*itr).getNome_servidor()) << endl;
    }
  }
  return "\n";
}

string Sistema::remove_server(int id, const string nome) {

  Servidor remover(id, nome);
  string aux_nome;
  string completar11("Você não é dono(a) do servidor '");
  string completar12("' .");
  string completar13("Servidor '");
  string completar14("' não encontrado.");

  for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
    if(((*ptr).getID()) == id){
      if(((*ptr).getNome_servidor() == nome)){
        aux_nome = ((*ptr).getNome_servidor());
        cout << "Servidor '" << aux_nome << "' removido." << endl;
        servidores.erase(ptr);

      } else {
        completar13 += nome;
        completar13 += completar14;
        return completar13;
      }
    } else {
      completar11 += nome;
      completar11 += completar12;
      return completar11;
    }
  }

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
