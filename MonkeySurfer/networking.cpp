#include "networking.h"
#include <iostream>

Networking::Networking()
{
}

Networking::~Networking()
{
	ENetEvent event;

	enet_peer_disconnect(_host, 0);

	while (enet_host_service(_client, &event, 3000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			enet_packet_destroy(event.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			std::cout << "Deconnectee" << std::endl;
			break;
		}
	}
}

void Networking::Connect(std::string adresse, int port)
{
	try
	{
		if (enet_initialize() != 0)
		{
			throw("Erreur d'initialisation");
		}

		atexit(enet_deinitialize);

		_client = enet_host_create(NULL, 1, 1, 0, 0);

		if (_client == NULL)
		{
			throw("Impossible de creer le client ENet");
		}

		enet_address_set_host(&_address, adresse.c_str());
		_address.port = port;

		_host = enet_host_connect(_client, &_address, 1, 0);

		if (_host == NULL)
		{
			throw("Aucune connexion!");
		}
		ENetEvent event;
		if (enet_host_service(_client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
		{
			std::cout << "Connecte a " << adresse << ":" << std::to_string(port) << std::endl;
		}
		else {
			enet_peer_reset(_host);
			throw("Connection interrompue");
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}

int Networking::GetId()
{
	return _idJoueur;
}

void Networking::ParseData(char* data)
{
	int dataType;
	int id;
	sscanf(data, "%d|%d", &dataType, &id);

	switch (dataType)
	{
	case 1: { //Met a jour la position
		if (id != _idJoueur)
		{
			int x;
			int y;
			sscanf(data, "%*d|%*d|%dx%dy", &x, &y);
			_joueurs[id]->setPosition({ x, y });
		}
		break;
	}
	}
}

void Networking::ReceiveData()
{
	ENetEvent event;

	while (enet_host_service(_client, &event, 0) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			ParseData((char*)event.packet->data);
			enet_packet_destroy(event.packet);
			break;
		}
	}
}

int Networking::GetJoueurCount()
{
	return _joueurs.size();
}
