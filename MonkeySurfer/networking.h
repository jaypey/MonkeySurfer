#ifndef NETWORKING_H__
#define NETWORKING_H__
#include <enet/enet.h>
#include <map>
#include "joueur.h"
#include <string>

class Networking
{
public:
	Networking();
	~Networking();

	void Connect(std::string adresse, int port);
	int GetId();
	void SendPacket(char* data);
	void ParseData(char* data);
	void ReceiveData();
	int GetJoueurCount();
	std::map<int, Joueur*> GetJoueurs();
private:
	int _idJoueur;
	ENetHost* _client;
	ENetAddress _address;
	ENetPeer* _host;
	std::map<int, Joueur*> _joueurs;
};
#endif // !NETWORKING_H__
