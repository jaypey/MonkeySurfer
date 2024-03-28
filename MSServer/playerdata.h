#ifndef PLAYERDATA_H__
#define PLAYERDATA_H__

#include "coordonnee.h"

class PlayerData
{
private:
    int m_id;
    bool m_IsReady;
    Coordonnee m_Position;
public:
    PlayerData(int id);
    ~PlayerData();

    void SetId(int id);
    void SetIsReady(bool isReady);
    bool GetReadyState();
    int GetId();
    void SetPosition(Coordonnee position);
    Coordonnee GetPosition() const;
};

#endif