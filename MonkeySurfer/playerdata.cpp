#include "playerdata.h"

PlayerData::PlayerData(int id) : m_id(id), m_Position(Coordonnee{ 0,0 }), m_IsReady(false)
{

}

PlayerData::~PlayerData()
{

}

int PlayerData::GetId()
{
    return m_id;
}

Coordonnee PlayerData::GetPosition() const
{
    return m_Position;
}

void PlayerData::SetId(int id)
{
    m_id = id;
}

void PlayerData::SetIsReady(bool isReady)
{
    m_IsReady = isReady;
}

bool PlayerData::GetReadyState()
{
    return m_IsReady;
}

void PlayerData::SetPosition(Coordonnee position)
{
    m_Position = position;
}