#include "usuario.h"
#include "sistema.h"
#include "servidor.h"
#include "canaltexto.h"
#include "Mensagem.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <time.h>
#include <ctime>
using namespace std;

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
    
  Usuario objCentral;

  objCentral.email = email;
  
  int tam, aux = 0;
  tam = usuarios.size();

  if(tam == 0){//ele é o 1º usuario a ser criado
    objCentral.id = 1;
    objCentral.email = email;
    objCentral.senha = senha;
    objCentral.nome = nome;

    usuarios.push_back(objCentral);
    email_validos.push_back(objCentral.email);
    tam = usuarios.size();
    return "\nUsuário criado\n";

  } else if (tam >= 1){
    
    for(int i = 0; i < tam; i++){//descobre se o usuário existe
      if( email_validos[i] == objCentral.email ){
        aux++;
      }
    }

    if(aux > 0){
      return "Usuário já existe!\n";
    }else{
      objCentral.id = tam + 1;
      objCentral.email = email;
      objCentral.senha = senha;
      objCentral.nome = nome;
      usuarios.push_back(objCentral);
      email_validos.push_back(objCentral.email);

      tam = usuarios.size();
    }

  }
  return "Usuário criado\n";
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
  x = usuariosLogados.size();

  if(x == 0){//quando não existe pessoas logadas
    return "Não está conectado.";
  }else{//existem pessoas logadas

    if(usuariosLogados.find(id) != usuariosLogados.end()) {
      for(auto ptr = usuarios.begin(); ptr != usuarios.end(); ptr++){
        if((*ptr).id == chave){
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

  Servidor proprio_servidor;
  proprio_servidor.setNome_servidor(nome);
  proprio_servidor.setID(id);
  int tam = servidores.size();
  int aux = 0;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    if(tam == 0 && id > 0){
    servidores.push_back(proprio_servidor);
    return "Servidor '" + nome + "' criado.";
    } else {
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
        if(nome == (*itr).getNome_servidor()){
        aux++;
        return "Servidor com esse nome já existe.";
        }
      }
    }
    if(aux == 0 && id > 0){
    servidores.push_back(proprio_servidor);
    return "Servidor '" + nome + "' criado.";
    }
  } else {
    return "Você não está logado(a), portanto não pode criar servidores.";
  }

  return "";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {

  Servidor verificar_descricao;
  verificar_descricao.setDescricao(descricao);

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      if(itr->getNome_servidor() == nome){ 
        if(itr->getID() == id){
          verificar_descricao.setDescricao(descricao);
          return "Descrição do servidor '" + nome + "' modificada!";
        }else{
          return "Você não pode alterar a descrição de um servidor que não foi criado por você.";
        }
      } 
    }  

    return "Servidor '" + nome + "' não existe.";

  } else {
    return "Você não está logado(a), portanto não pode alterar nenhuma descrição.";
  }
  return "";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {

  Servidor codigo_de_convite;
  codigo_de_convite.setCodigoConvite(codigo);
  int tam = codigo.length();

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
      if(ptr->getNome_servidor() == nome){
        if(ptr->getID() == id){
          if (tam == 0){
            return "Código de convite do servidor '" + nome + "' removido.";
          } else {        
            ptr->setCodigoConvite(codigo); // OK
            cout << "Código de convite: "<< ptr->getCodigoConvite() << endl;
            return "Código de convite do servidor '" + nome + "' modificado com sucesso.";
          }
        } else {
            return "Você não pode alterar o código de um servidor que você não é o(a) dono(a).";
        }
      }
    }
  } else {
    return "Você não está logado(a), portanto não pode modificar códigos de convite.";
  }
  return "Servidor não existe.";
}

string Sistema::list_servers(int id) {

  cout << endl;
  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      cout << ((*itr).getNome_servidor()) << endl;
    }
  } else{
    return "Você não está logado(a).";
  }
  return "";
}

string Sistema::remove_server(int id, const string nome) {

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      if(itr->getNome_servidor() == nome){
        if(itr->getID() == id){ 
          servidores.erase(itr);
          return "Servidor '" + nome + "' removido com sucesso.";
        } else {
          return "Você não é dono(a) do servidor, portanto não pode removê-lo.";
        }
      }
    } 
    return "Servidor não encontrado.";
  } else {
    return "Você não está logado(a).";
  }

  return "";
}

string Sistema::enter_server(int id, const string nome, const string codigo) { 

  std::map< int, std::pair<std::string, std::string> >::iterator iterator_nome;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      if(itr->getNome_servidor() == nome){
        if(itr->getID() == id){
          itr->adicionarParticipantes(id);
          iterator_nome = usuariosLogados.find(id);
          iterator_nome->second.first = itr->getNome_servidor();
          return "Entrou no servidor '" + nome + "' com sucesso.";
        } else if(itr->getCodigoConvite() != codigo && codigo == ""){
            return "Servidor requer código de acesso.";
        } else if(itr->getCodigoConvite() == codigo){
            itr->adicionarParticipantes(id);
            iterator_nome = usuariosLogados.find(id);
            iterator_nome->second.first = itr->getNome_servidor();
            return "Entrou no servidor '" + nome + "' com sucesso.";
          } else {
            return "Código de acesso errado.";
          }
      }
    }
  } else{
    return "Você não está logado(a).";
  }
  return "";
}

string Sistema::leave_server(int id, const string nome) {

  std::map< int, std::pair<std::string, std::string> >::iterator iterator_nome;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      if(itr->getNome_servidor() == nome){
        if(itr->verificarParticipante(id)){
          itr->excluirParticipante(id); 
          iterator_nome = usuariosLogados.find(id);
          return "Saindo do servidor '" + nome + "'.";
        } else{
          return "Você não está em qualquer servidor.";
        }        
      } 
    }
  } else{
    cout << "Você não está logado(a).";
  }

  return "";
}

string Sistema::list_participants(int id) {

  string servidor_visualizado;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = usuariosLogados.begin(); itr != usuariosLogados.end(); itr++){
      if(itr->first == id){
        servidor_visualizado = itr->second.first;
        break;
      }
    }

    for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
      if((*ptr).getNome_servidor() == servidor_visualizado){
        ptr->mostrarParticipantes(usuarios);           
      }
    }
  } else {
    return "Você não está logado(a).";
  }

  return "";
}

string Sistema::list_channels(int id) {

  string servidor_visualizado;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto itr2 = usuariosLogados.find(id);
    servidor_visualizado = itr2->second.first;

    if(servidor_visualizado == " "){
      return "Você não tem canais para serem listados.";
    }

    for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
      if((*ptr).getNome_servidor() == servidor_visualizado){
        //cout << "Servidor: " << servidor_visualizado << endl; //feito para testes
        ptr->mostrarCanais();
      }
    }
  } else{
      return "Você não está logado(a).";
  }

  return "";
}

string Sistema::create_channel(int id, const string nome) {

  string servidor_visualizado;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto itr2 = usuariosLogados.find(id);
    servidor_visualizado = itr2->second.first; 


    auto it = find_if(servidores.begin(), servidores.end(), [servidor_visualizado](Servidor servidor){
      if(servidor.getNome_servidor() == servidor_visualizado){
        return true;
      } else{
        return false;
      }
    });

    if(it != servidores.end()){ 
      if(it->criarCanais(nome)){
        return "Canal de texto '" + nome + "' criado.";
      } else {
        return "Canal de texto '" + nome + "' já existe.";
      }
    }
  } else{
    return "Você não está logado(a).";
  }

  return "";
}

string Sistema::enter_channel(int id, const string nome) {

  string servidor_visualizado;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto itr2 = usuariosLogados.find(id);
    servidor_visualizado = itr2->second.first;

    for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
      if((*ptr).getNome_servidor() == servidor_visualizado){
        if(ptr->verificarCanais(nome)){
          itr2->second.second = nome;
          return "Entrou no canal '" + nome + "'.";
        } else{
          return "Canal '" + nome + "' não existe no servidor em que você está.";
        }
      }
    }
  } else {
    return "Você não está logado(a).";
  }
  return "";
}

string Sistema::leave_channel(int id) {

  string servidor_visualizado, canal, canal2;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto iter = usuariosLogados.find(id);
    servidor_visualizado = iter->second.first;
    canal = iter->second.second;

    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      if((*itr).getNome_servidor() == servidor_visualizado){
        if(iter->second.second == ""){
          return "Você não está visualizando este canal.";
        }else{
          iter->second.second = "";
          canal2 = iter->second.second;
          return "Saindo do canal '" + canal + "'.";
        }
      }
    }
  } else{
      return "Você não está logado(a).";
  }
  return "";
}

string Sistema::send_message(int id, const string mensagem) {

  time_t timer;
  struct tm *horarioLocal;
  string canal, servidor_visualizado;

  time(&timer);
  horarioLocal = localtime(&timer);

  int dia = horarioLocal->tm_mday, mes = horarioLocal->tm_mon + 1, ano = horarioLocal->tm_year + 1900, hora = horarioLocal->tm_hour, min = horarioLocal->tm_min;

  std::string data_completa = " <" + std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(ano) + " - " + std::to_string(hora) + ":" + std::to_string(min) + ">";

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto iter = usuariosLogados.find(id);
    canal = iter->second.second;
    servidor_visualizado = iter->second.first;
  
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      itr->percorrerCanais(data_completa, id, mensagem, canal);
    }
  } else{
    return "Você não está logado(a).";
  }

  return "";
}

string Sistema::list_messages(int id) {

  string canal_visualizado, servidor_visualizado, nome_usuario;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto iter = usuariosLogados.find(id);
    canal_visualizado = iter->second.second;
    servidor_visualizado = iter->second.first;

    for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
      if((*ptr).getNome_servidor() == servidor_visualizado){
        ptr->listarMensagensCanais(usuarios, canal_visualizado, id);
      }
    }

  } else {
    return "Você não está logado(a).";
  }

  return "";
}