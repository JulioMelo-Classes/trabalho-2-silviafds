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
 * @brief Método implementado para criar um(a) usuário(a). 
 *
 * @param email atributo do tipo string que armazena o e-mail correspondente ao/à usuário(a).
 * @param senha atributo do tipo string que armazena a senha correspondente ao/à usuário(a).
 * @param nome atributo do tipo string que armazena o nome correspondente ao/à usuário(a).
 *
 * @return uma string contendo uma mensagem de erro caso o(a) usuário(a) já tenha sido criado(a) ou "Usuário(a) criado(a)."
 */

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

/*! 
 * @brief Método implementado para realizar o login de um(a) usuário(a) no sistema. 
 *
 * @param email atributo do tipo string que armazena o e-mail correspondente ao/à usuário(a).
 * @param senha atributo do tipo string que armazena a senha correspondente ao/à usuário(a).
 *
 * @return uma string contendo a mensagem de erro: "Senha ou usuário inválidos." caso seja necessário e, caso não, retorna "Logado como <email>".
 * 
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
 * @brief Método implementado para desconectar um(a) usuário específico do sistema. 
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 *
 * @return uma string contendo uma mensagem de erro para caso o(a) usuário(a) não esteja conectado(a) ou "Desconectando usuário <email>" caso esteja conectado(a). 
 *
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
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * @param nome atributo do tipo string que armazena o nome correspondente ao servidor a ser criado.
 *
 * @return uma string contendo uma mensagem de erro caso já exista um servidor com esse nome ou o(a) usuário(a) não esteja logado(a) e uma string contendo "Servidor <nome> criado." caso não haja nenhum erro.
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

/*! 
 * @brief método implementado para modificar a descrição do servidor passado como parâmetro. 
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * @param nome atributo do tipo string que armazena o nome do servidor.
 * @param descricao atributo do tipo string que armazena a nova descrição dada pelo(a) usuário(a).
 *
 * @return string contendo uma mensagem de erro caso o servidor passado como parâmetro não exista, uma mensagem de erro caso o(a) usuário(a) não esteja logado(a), uma mensagem de erro caso o id passado como parâmetro não seja dono(a) do servidor e "Descrição do servidor <nome> modificada!" caso não haja nenhum erro.
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
 * @brief método implementado para modificar o código de convite de um servidor específico. 
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * @param nome atributo do tipo string que armazena o nome correspondente ao servidor que a pessoa quer alterar o código.
 * @param codigo atributo do tipo string que armazena o código de convite a ser alterado.
 *
 * @return "Código de convite do servidor <nome> modificado com sucesso" caso não haja erros e, caso haja, serão retornadas strings contendo mensagens de erro caso o(a) usuário(a) não esteja logado(a), caso o(a) usuário(a) não seja o(a) dono(a), caso o código seja removido, e caso o servidor não exista.
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

/*! 
 * @brief método que lista todos os servidores que estão cadastrados no sistema.
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 *
 * @return uma string vazia ou uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
 */
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

/*! 
 * @brief Função que remove um servidor
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * @param nome atributo do tipo string que armazena o nome  correspondente ao servidor.
 *
 * @return "Servidor <nome> removido com sucesso." todas as validações sejam cumpridas; caso contrário, serão retornadas mensagens de erro se o(a) usuário(a) não for dono(a) do servidor, bem como se não estiver logado(a) e caso o servidor não seja encontrado.
 */
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

/*! 
 * @brief método que faz com que o(a) usuário(a) entre em um servidor.
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * @param nome atributo do tipo string que armazena o nome correspondente ao servidor.
 * @param codigo atributo do tipo string que armazena o código de convite para entrar no sistema.
 *
 * @return "Entrou no servidor <nome> com sucesso" caso todas as validações sejam cumpridas; ou mensagens de erro para caso o(a) usuário(a) não forneça o código de acesso, caso o código de acesso fornecido estiver incorreto e caso o(a) usuário(a) não esteja logado(a).
 */
string Sistema::enter_server(int id, const string nome, const string codigo) { 

  std::map< int, std::pair<std::string, std::string> >::iterator iterator_nome;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      if(itr->getNome_servidor() == nome){
        if(itr->getID() == id){
          itr->adicionarParticipantes(id);
          iterator_nome = usuariosLogados.find(id);
          iterator_nome->second.first = itr->getNome_servidor();
          itr->testarParticipantes(nome);
          return "Entrou no servidor '" + nome + "' com sucesso.";
        } else if(itr->getCodigoConvite() != codigo && codigo == ""){
            return "Servidor requer código de acesso.";
        } else if(itr->getCodigoConvite() == codigo){
            itr->adicionarParticipantes(id);
            iterator_nome = usuariosLogados.find(id);
            iterator_nome->second.first = itr->getNome_servidor();
            itr->testarParticipantes(nome);
            return "Entrou no servidor '" + nome + "' com sucesso.";
          } else {
            return "Código de acesso errado.";
          }
      }
    }
  } else{
    return "Você não está logado(a).";
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

/*! 
 * @brief método que faz com que o(a) usuário(a) saia de um servidor em que esteja conectado(a).
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * @param nome atributo do tipo string que armazena o nome correspondente ao servidor.
 *
 * @return "Saindo do servidor <nome>." caso todas as validações sejam cumpridas; ou mensagens de erro para caso o(a) usuário(a) não esteja logado(a) ou tampouco conectado(a) a algum servidor.
 */
string Sistema::leave_server(int id, const string nome) {

  std::map< int, std::pair<std::string, std::string> >::iterator iterator_nome;

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
    cout << "Você não está logado(a).";
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

/*! 
 * @brief método que lista os participantes que estão presentes no servidor que o(a) usuário(a) passado como parâmetro - através do id - está visualizando.
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 *
 * @return uma string vazia caso todas as validações sejam cumpridas e uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
 */
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

/*! 
 * @brief método que lista os canais do servidor que o usuário pertencente àquele id está visualizando.
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * 
 * @return uma string vazia caso todas as validações sejam cumpridas e uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
 */
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
      return "Você não está logado(a).";
  }

  return "";
}

/*! 
 * @brief método que cria um canal no servidor em que o(a) usuário(a) está visualizando.
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * @param nome atributo do tipo string que armazena o nome correspondente ao canal a ser criado.
 *
 * @return "Canal <nome> criado." caso todas as validações sejam cumpridas e mensagens de erro caso o(a) usuário(a) não esteja logado(a), caso um canal de texto com o nome passado já exista ou caso o(a) usuário(a) não esteja visualizando nenhum servidor.
 */
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
    return "Você não está logado(a).";
  }

  return "";
}

/*! 
 * @brief método que faz com que o(a) usuário(a), correspondente ao id, entre em um canal específico.
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * @param nome atributo do tipo string que armazena o nome correspondente ao canal que o(a) usuário(a) irá entrar.
 *
 * @return "Entrou no canal <nome>" caso todas as validações sejam cumpridas ou mensagens de erro caso o canal não exista ou o(a) usuário(a) não esteja logado(a).
 */
string Sistema::enter_channel(int id, const string nome) {

  string servidor_visualizado;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto itr2 = usuariosLogados.find(id);
    servidor_visualizado = itr2->second.first; //pegamos o nome do servidor do usuário logado

    for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
      if((*ptr).getNome_servidor() == servidor_visualizado){
        //cout << "Servidor: " << servidor_visualizado << endl; //feito para testes
        if(ptr->verificarCanais(nome)){
          itr2->second.second = nome;
          return "Entrou no canal '" + nome + "'.";
        } else{
          return "Canal '" + nome + "' não existe.";
        }
      }
    }
  } else {
    return "Você não está logado(a).";
  }
  return "";
}

// VERIFICAR ESSE MÉTODO

/*! 
 * @brief método que faz com que o(a) usuário(a) passado como parâmetro seja retirado do canal que está visualizando.
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 *
 * @return "Saindo do canal <nome>" caso todas as validações sejam cumpridas ou mensagens de erro caso o(a) usuário(a) não esteja visualizando o canal ou não esteja logado(a).
 */
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

/*! 
 * @brief método que envia uma mensagem para o canal que o(a) usuário(a) passado(a) como parâmetro está visualizando.
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 * @param mensagem atributo do tipo string que armazena a mensagem a ser enviada ao canal.
 *
 * @return uma string vazia caso todas as validações sejam cumpridas e uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
 */
string Sistema::send_message(int id, const string mensagem) {

  time_t timer;
  struct tm *horarioLocal;
  string canal, servidor_visualizado;

  time(&timer);
  horarioLocal = localtime(&timer);

  int dia = horarioLocal->tm_mday, mes = horarioLocal->tm_mon + 1, ano = horarioLocal->tm_year + 1900, hora = horarioLocal->tm_hour, min = horarioLocal->tm_min;

  std::string data_completa = " <" + std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(ano) + " - " + std::to_string(hora) + ":" + std::to_string(min) + ">";

  //cout << "Data completa: " << data_completa << endl;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto iter = usuariosLogados.find(id);
    canal = iter->second.second;
    servidor_visualizado = iter->second.first;
  
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
      //if((*itr).getNome_servidor() == servidor_visualizado){
        //if(itr->verificarCanais(canal)){
          itr->percorrerCanais(data_completa, id, mensagem, canal);
        //}
      //}
    }
  } else{
    return "Você não está logado(a).";
  }

  return "";
}

/*! 
 * @brief método que lista todas as mensagens do canal que o(a) usuário(a) passado(a) como parâmetro está visualizando.
 *
 * @param id atributo do tipo int que armazena o id correspondente ao/à usuário(a).
 *
 * @return uma string vazia caso todas as validações sejam cumpridas e uma mensagem de erro caso o(a) usuário(a) não esteja logado(a).
 */
string Sistema::list_messages(int id) {

  string canal_visualizado, servidor_visualizado, nome_usuario;
  int id_usuario;

  if(usuariosLogados.find(id) != usuariosLogados.end()){
    auto iter = usuariosLogados.find(id);
    id_usuario = iter->first;
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