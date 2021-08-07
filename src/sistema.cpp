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

/*! 
 * @brief Função na qual cria usuário. 
 *
 * @param email é uma string onde está armazenado o email correspondente ao usuário.
 * @param senha é uma string onde está armazenada a senha correspondente ao usuário.
 * @param nome é uma string onde está armazenado o nome correspondente ao usuário.
 *
 * @return retorna a mensagem que o usuário foi criado ou que já existe (a depender da situação).
 */

Usuario st_nome;
std::map< int, std::pair<std::string, std::string> >::iterator iterator_nome;

string Sistema::create_user (const string email, const string senha, const string nome) {
    
  st_nome.email = email;
  
  int tam, aux = 0;
  tam = usuarios.size();

  if(tam == 0){//ele é o 1º usuario a ser criado
    st_nome.id = 1;
    st_nome.email = email;
    st_nome.senha = senha;
    st_nome.nome = nome;

    usuarios.push_back(st_nome);
    email_validos.push_back(st_nome.email);
    tam = usuarios.size();
    return "\nUsuário criado\n";

  } else if (tam >= 1){
    
    for(int i = 0; i < tam; i++){//descobre se o usuário existe
      if( email_validos[i] == st_nome.email ){
        aux++;
      }
    }

    if(aux > 0){
      return "Usuário já existe!\n";
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
  return "Usuário criado\n";
}

/*! 
 * @brief Função que o usuário faz login no sistema. 
 *
 * @param email é uma string onde está armazenado o email correspondente ao usuário.
 * @param senha é uma string onde está armazenada a senha correspondente ao usuário.
 *
 * @return retorna se a senha ou usuário sé inválidos ou mostra quem fez login no sistema.
 */
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

/*! 
 * @brief Função que disconecta o usuário do sistema. 
 *
 * @param id é o número que corresponde a cada usuário, quando digitado aqui, faz logout do usuário.
 *
 * @return retorna se o usuário fi desconectado ou se ele nem se conectou.
 */
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
          completar2 += (*ptr).email;
          usuariosLogados.erase(id);
          return completar2;
        }
      } 
    }
  }

  return "Não está conectado.";
}

/*! 
 * @brief Função na qual cria um servidor. 
 *
 * @param id número que identifica cada usuário no sistema
 * @param nome é uma string onde está armazenado o nome correspondente ao usuário.
 *
 * @return retorna se o servidor foi criado ou se o servidor já existe ou não retorna nada caso não possa criar.
 */
string Sistema::create_server(int id, const string nome) {

  Servidor proprio_servidor;
  proprio_servidor.setNome_servidor(nome);
  proprio_servidor.setID(id);
  int tam = servidores.size();
  int aux = 0;

  if(usuariosLogados.find(id) != usuariosLogados.end()){ //verifica se o usuário está logado.
    if(tam == 0 && id > 0){
    servidores.push_back(proprio_servidor);
    return "Servidor criado.";
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
    return "Servidor criado.";
    }
  } else {
    return "Você não está logado(a), portanto não pode criar servidores.";
  }

  return "";
}

/*! 
 * @brief Função na qual muda a descrição do servidor. 
 *
 * @param id número que identifica cada usuário no sistema.
 * @param nome é uma string que corresponde ao nome do servidor.
 * @param descricao string na qual está a descrição digitada pelo usuário
 *
 * @return retorna se a descrição do servidor foi modificada com sucesso ou retorna a mensagem que o usuário só pode modificar se ele for o dono.
 */
string Sistema::set_server_desc(int id, const string nome, const string descricao) {

  Servidor verificar_descricao;
  verificar_descricao.setDescricao(descricao);
  //Servidor verificar_desc(descricao);

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

/*! 
 * @brief Função na qual seta código de convite para o servidor. 
 *
 * @param id número que identifica cada usuário no sistema.
 * @param nome é uma string que corresponde ao nome do servidor.
 * @param codigo é a string onde está o código de comvite do servidor
 *
 * @return retorna mensagem caso o código de convite foi modificado, ou removido, ou o usuário não pode modificar um código de um servidor que nçao é dono, ou se o servidor não existe
 */
string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {

  Servidor codigo_de_convite;
  codigo_de_convite.setCodigoConvite(codigo);
  //Servidor convite(codigo);
  //Servidor convite(id, nome, codigo);
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
            return "Código de convite do servidor '" + nome + "' modificado.";
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

/*! 
 * @brief Função que lista todos os servidores corresponde ao usuário. 
 *
 * @param id número que identifica cada usuário no sistema.
 *
 * @return retorna nada pois a apresentação dos servidores se concentra na linha 264.
 */
string Sistema::list_servers(int id) {

  cout << endl;
  for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
    cout << ((*itr).getNome_servidor()) << endl;
  }
  return "";
}

/*! 
 * @brief Função que remove um servidor
 *
 * @param id número que identifica cada usuário no sistema.
 * @param nome é uma string que corresponde ao nome do servidor.
 *
 * @return se o usuário for dono do servidor, remove o servidor, se o usuário não for dono do servidor e tentar remover, não remove, se o servidor não for encontrado, retorna que não foi encontrado o servidor.
 */
string Sistema::remove_server(int id, const string nome) {

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      if(itr->getNome_servidor() == nome){
        if(itr->getID() == id){ 
          servidores.erase(itr);
          return "Servidor removido.";
        } else {
          return "Você não é dono(a) do servidor, portanto não pode removê-lo.";
        }
      }
    } 
    return "Servidor não encontrado.";
  } else {
    return "Você não está logado.";
  }

  return "";
}

string Sistema::enter_server(int id, const string nome, const string codigo) { 

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      if(itr->getNome_servidor() == nome){
        if(itr->getID() == id){
          itr->adicionarParticipantes(id);
          iterator_nome = usuariosLogados.find(id);
          iterator_nome->second.first = itr->getNome_servidor();
          itr->testarParticipantes(nome);
          return "Entrou no servidor com sucesso.";
        } else if(itr->getCodigoConvite() != codigo && codigo == ""){
            return "Servidor requer código de acesso.";
        } else if(itr->getCodigoConvite() == codigo){
            itr->adicionarParticipantes(id);
            iterator_nome = usuariosLogados.find(id);
            iterator_nome->second.first = itr->getNome_servidor();
            itr->testarParticipantes(nome);
            return "Entrou no servidor com sucesso.";
          } else {
            return "Código de acesso errado.";
          }
      }
    }
  }

  //FOR USADO PARA SABERMOS QUAL SERVIDOR O USUÁRIO ESTÁ VISUALIZANDO
  /*for(auto ptr = usuariosLogados.begin(); ptr != usuariosLogados.end(); ptr++){
    if(usuariosLogados.find(id) != usuariosLogados.end()){
      cout << "IDs: " << ptr->first;
      cout << " Nomes: " << ptr->second.first << endl;
    }
  }*/
  return "";
}

string Sistema::leave_server(int id, const string nome) {

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      if(itr->getNome_servidor() == nome){
        if(itr->verificarParticipante(id)){
          itr->excluirParticipante(id); 
          iterator_nome = usuariosLogados.find(id);
          //iterator_nome->second.first = " "; 
          itr->testarParticipantes(nome);
          cout << "Saindo do servidor " + nome << endl;
          //return "Saindo do servidor '" + nome + "'.";
        } else{
          return "Você não está em qualquer servidor.";
        }        
      } 
    }
  } else{
    cout << "Você não está logado.";
  }

  //FOR USADO PARA SABERMOS QUAL SERVIDOR O USUÁRIO ESTÁ VISUALIZANDO
  /*for(auto ptr = usuariosLogados.begin(); ptr != usuariosLogados.end(); ptr++){
    if(usuariosLogados.find(id) != usuariosLogados.end()){
      cout << "IDs: " << ptr->first;
      cout << " Nomes: " << ptr->second.first << endl;
    }
  }*/

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
    return "Você não está logado.";
  }

  return "";
}

string Sistema::list_channels(int id) {

  string servidor_visualizado;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto itr2 = usuariosLogados.find(id);
    servidor_visualizado = itr2->second.first;

    for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
      if((*ptr).getNome_servidor() == servidor_visualizado){
        cout << "Servidor: " << servidor_visualizado << endl; //feito para testes
        ptr->mostrarCanais();
      }
    }
  } else{
      return "Você não está logado.";
  }

  return "";
}

string Sistema::create_channel(int id, const string nome) {

  string servidores_visualizado;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto itr2 = usuariosLogados.find(id);
    servidores_visualizado = itr2->second.first; //pegamos o nome do servidor do usuário logado

  
    if(servidores_visualizado == " "){
      return "Servidor não encontrado.";
    }

    auto it = find_if(servidores.begin(), servidores.end(), [servidores_visualizado](Servidor servidor){
      if(servidor.getNome_servidor() == servidores_visualizado){
        return true;
      } else{
        return false;
      }
    });

    if(it != servidores.end()){ //se o iterator não for igual ao final, ele achou um servidor, do contrario, não achou
      if(it->criarCanais(nome)){
        return "Canal de texto '" + nome + "' criado.";
      } else {
        return "Canal de texto '" + nome + "' já existe.";
      }
    }
  } else{
    return "Você não está logado.";
  }

  return "";
}

string Sistema::enter_channel(int id, const string nome) {

  string servidor_visualizado;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto itr2 = usuariosLogados.find(id);
    servidor_visualizado = itr2->second.first; //pegamos o nome do servidor do usuário logado

    for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
      if((*ptr).getNome_servidor() == servidor_visualizado){
        cout << "Servidor: " << servidor_visualizado << endl; //feito para testes
        if(ptr->verificarCanais(nome)){
          itr2->second.second = nome;
          return "Entrou no canal '" + nome + "'.";
        } else{
          return "Canal '" + nome + "' não existe.";
        }
      }
    }
  } else {
    return "Você não está logado.";
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
          //cout << "Servidor a verificar canal: " << servidor_visualizado << endl;
          //cout  << "Canal a sair: " << canal << endl;
          iter->second.second = "";
          canal2 = iter->second.second;
          return "Saindo do canal '" + canal + "'.";
          //cout << "Canal que saiu: " << canal2 << endl;
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
  int pessoa;

  time(&timer);
  horarioLocal = localtime(&timer);

  int dia = horarioLocal->tm_mday, mes = horarioLocal->tm_mon + 1, ano = horarioLocal->tm_year + 1900, hora = horarioLocal->tm_hour, min = horarioLocal->tm_min;

  std::string data_completa = "<" + std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(ano) + "-" + std::to_string(hora) + ":" + std::to_string(min) + ">";

  cout << "Data completa: " << data_completa << endl;

  auto iter = usuariosLogados.find(id);
  pessoa = iter->first;
  canal = iter->second.second;
  servidor_visualizado = iter->second.first;


  for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
    if((*itr).getNome_servidor() == servidor_visualizado){
      if(itr->verificarCanais(canal)){
        itr->percorrerCanais(data_completa, id, mensagem, canal);
      }
    }
  }

  return "";
}

string Sistema::list_messages(int id) {
  return "list_messages NÃO IMPLEMENTADO";
}


/* IMPLEMENTAR MÉTODOS PARA OS COMANDOS RESTANTES */
