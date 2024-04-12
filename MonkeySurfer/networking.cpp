#include "networking.h"
#include <iostream>
#include <enet/enet.h>
#include "coordonnee.h"

Networking::Networking()
{
    _readyPlayerCount = 0;
    _gameStarted = false;
    _isPlayerReady = false;
}

Networking::~Networking()
{
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
        if (enet_host_service(_client, &event, 10000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
        {
            enet_host_flush(_client);
            std::cout << "Connecte a " << adresse << ":" << std::to_string(port) << std::endl;
        }
        else {
            enet_peer_reset(_host);
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

void Networking::SendLocalReady() {
    char messageData[80] = "2|";
    SendPacket(messageData);
}

void Networking::SendLocalPosition(Coordonnee c) {
    std::string msgPosition = std::to_string(c.x) + "x" + std::to_string(c.y) + "y";
    char messageData[80] = "1|";
    strcat_s(messageData, msgPosition.c_str());
    SendPacket(messageData);
}

void Networking::SendPacket(char* data)
{
    ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(_host, 0, packet);
    enet_host_flush(_client);
}

void Networking::ParseData(char* data)
{
    int dataType;
    int id;
    sscanf_s(data, "%d|%d", &dataType, &id);

    switch (dataType)
    {
    case 1: { //Met a jour la position
        if (id != _idJoueur)
        {
            int x;
            int y;
            sscanf_s(data, "%*d|%*d|%dx%dy", &x, &y);
            _mutex.lock();
            _joueurs[id]->SetPosition({ x, y });
            _mutex.unlock();
        }
        break;
    }
    case 2: {
        int nbReadyJoueur;
        sscanf_s(data, "%*d|%*d|%dx", &nbReadyJoueur);
        _mutex.lock();
        _readyPlayerCount = nbReadyJoueur;
        _mutex.unlock();
    }
    case 3: //Reception connexion autre user
    {
        if (id != _idJoueur)
        {
            _mutex.lock();
            _joueurs[id] = new PlayerData(id);
            _mutex.unlock();
            std::cout << "Nouveau joueur connect�: " << id << std::endl;
        }
        break;
    }
    case 4: //Reception id
    {
        _idJoueur = id;
        break;
    }
    case 5:
    {
        if (id != _idJoueur)
        {
            _mutex.lock();
            _joueurs.erase(id);
            _mutex.unlock();
        }

    }
    case 6:
    {
        _gameStarted = true;
    }
    }
}

void Networking::ReceiveData()
{
    while (TRUE) {
        ENetEvent event;

        while (enet_host_service(_client, &event, 100000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "Message recu: " << (char*)event.packet->data << std::endl;
                ParseData((char*)event.packet->data);
                enet_packet_destroy(event.packet);
                break;
            }
        }
    }
}

bool Networking::IsGameStarted()
{
    return _gameStarted;
}

bool Networking::IsPlayerReady()
{
    return _isPlayerReady;
}

int Networking::GetReadyPlayerCount() {
    return _readyPlayerCount;
}

std::map<int, PlayerData*> Networking::GetJoueurs()
{
    return _joueurs;
}


int Networking::GetJoueurCount()
{
    return _joueurs.size();
}

QMutex* Networking::GetMutex() {
    return &_mutex;
}