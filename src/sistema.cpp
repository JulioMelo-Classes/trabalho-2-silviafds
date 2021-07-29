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

/*! 
 * @brief Função na qual cria usuário. 
 *
 * @param email é uma string onde está armazenado o email correspondente ao usuário.
 * @param senha é uma string onde está armazenada a senha correspondente ao usuário.
 * @param nome é uma string onde está armazenado o nome correspondente ao usuário.
 *
 * @return retorna a mensagem que o usuário foi criado ou que já existe (a depender da situação).
 */
 /*
 A1.2 ok
 */
string Sistema::create_user (const string email, const string senha, const string nome) {
  Usuario st_nome;
  
  st_nome.email = email;
  
  int tam, tam_email, aux = 0;
  tam = usuarios.size();

  //realmente não precisa tratar esse usuário diferente... 
  if(tam == 0){//ele é o 1º usuario a ser criado
    st_nome.id = 1;
    st_nome.email = email;
    st_nome.senha = senha;
    st_nome.nome = nome;

    usuarios.push_back(st_nome);
    email_validos.push_back(st_nome.email);
    /*cout << "\nTESNTANDO O PRIMEIO USUARIO SENDO CRIADO\n";
    cout << "\ntamanho dentro da func: " << tam << endl;*/
    tam = usuarios.size();
    return "\nUsuário criado\n";

  } else if (tam >= 1){
    
    for(int i = 0; i < usuarios.size(); i++){//descobre se o usuário existe
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

 /*
 A1.3 ok
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
 /*
 A2.1 ok
 */
string Sistema::disconnect(int id) {
  Usuario avisoemail;
  string completar2("Desconectando usuário ");
  int x = 0, y = 0, chave;
  chave = id;
  x = usuariosLogados.size();//descobre tamanho do map
                            //se o map for 0 é porque ninguém fez login
                            //se o map for maior que 0 é pq pessoas fizeram login

  //não é necessário, fazendo o bloco do else toda vez vc ainda tem o mesmo resultado!
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
 /*
 A2.2 70%
 - Faltou testar se o usuário está logado
 */
string Sistema::create_server(int id, const string nome) {

  Servidor nome_do_servidor(id, nome);
  int tam = servidores.size();
  int aux = 0;
  
  /*cout << "ID que está criando: " << nome_do_servidor.getID() << endl;
  cout << "Nome do servidor: " << nome_do_servidor.getNome_servidor() << endl;*/

  if(tam == 0 && id > 0){
    servidores.push_back(nome_do_servidor);
    return "Servidor criado";
  } else {
    for(auto itr = servidores.begin(); itr != servidores.end(); itr++){  
      if(nome.compare((*itr).getNome_servidor()) == 0){
        aux++;
        return "Servidor com esse nome já existe.";
      }
    }
  }
  if(aux == 0 && id > 0){
    servidores.push_back(nome_do_servidor);
    return "Servidor criado";
  }

  return "";//mudei aqui
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
 /*
 A2.3 70%
 - Faltou tester se o usuário está logado
 */
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
        return completar3;
      }else{
        return "Você não pode alterar a descrição de um servidor que não foi criado por você!";
      }
    }
  }   

  return "Você não pode alterar a descrição de um servidor que não foi criado por você!";
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
 /*
 A2.4 70%
 - Faltou testar se está logado
 */
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
          return "Você não pode alterar o código de um servidor que não foi criado por você!";
      }
    }
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
 /*
 A2.5 ok
 - vc não verificou se o usuário está logado, mas nesse caso não é mesmo necessário
 - Veja que esse comando deve listar todos os servidores do sistema e não apenas os que o usuário é dono!
 */
string Sistema::list_servers(int id) {

  Servidor lista_servidores(id);
  string completar10("\n");

  //cout << "SERVIDORES:";
  cout << endl;
  for(auto itr = servidores.begin(); itr != servidores.end(); itr++){
    if((*itr).getID2() == id){
      cout << ((*itr).getNome_servidor()) << endl;
    }
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

 /*
 A2.6 70%
 - Faltou verificar se o usuário está logado!
 - Não vou tirar pontos por isso, mas faltou atualizar a tabela usuarios logados de acordo com a remoção do servidor
 */
string Sistema::remove_server(int id, const string nome) {

  Servidor remover(id, nome);
  string aux_nome;
  string completar11("Você não é dono(a) do servidor '");
  string completar12("' .");
  string completar13("Servidor '");
  string completar14("' não encontrado.");
  string completar15("' removido");

  for(auto ptr = servidores.begin(); ptr != servidores.end(); ptr++){
    if(((*ptr).getID()) == id){
      if(((*ptr).getNome_servidor() == nome)){
        aux_nome = ((*ptr).getNome_servidor());
        servidores.erase(ptr);
        completar13 += aux_nome;
        completar13 += completar15;
        return completar13;
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
  completar13 += nome;
  completar13 += completar14;
  return completar13;
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
