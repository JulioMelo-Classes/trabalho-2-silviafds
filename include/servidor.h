#ifndef SERVIDOR_H
#define SERVIDOR_H
#include <vector>
#include <string>
#include "canaltexto.h"
using namespace std;

/*
CP1 classe servidor 70%
tirei pontos pois vcs não dividiram em .cpp e .h
*/
class Servidor{
	private:
		int usuarioDonold;//id do usuário que criou o servidor
		string nome;
		string descricao;
		string codigoConvite;
		vector<CanalTexto> canaisTexto; //não pode ter get e set
		vector<int> participantesIDs; //não pode ter get e set

	public:
		Servidor(int id, string nome_servidor){
			usuarioDonold = id;
			nome = nome_servidor;				
		}

		int getID(){
			return usuarioDonold;
		}

		string getNome_servidor(){
			return nome;
		}
		
		Servidor(string desc){
			descricao = desc;
		}

		string getDescricao(){
			return descricao;
		}

		Servidor(int id, string nome_server, string codigo){
			usuarioDonold = id;
			nome = nome_server;
			codigoConvite = codigo;
		}

		string getCodigo(){
			return codigoConvite;
		}

		Servidor(int id){
			usuarioDonold = id;
		}

		int getID2(){
			return usuarioDonold;
		}

};

#endif
