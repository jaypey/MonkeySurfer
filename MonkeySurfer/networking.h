#ifndef NETWORKING_H__
#define NETWORKING_H__
#include <enet/enet.h>
#include <map>
#include <string>
#include "playerdata.h"

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
	bool IsGameStarted();
	void SendLocalReady();
	void SendLocalPosition(Coordonnee c);
	int GetJoueurCount();
	int GetReadyPlayerCount();
	std::map<int, PlayerData*> GetJoueurs();
private:
	int _idJoueur;
	int _readyPlayerCount;
	ENetHost* _client;
	ENetAddress _address;
	ENetPeer* _host;
	std::map<int, PlayerData*> _joueurs;
	bool _gameStarted;
};
#endif // !NETWORKING_H__
