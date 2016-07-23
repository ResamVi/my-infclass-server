#include "roundstatistics.h"

void CRoundStatistics::CPlayer::OnScoreEvent(int EventType, int Class)
{
	int Points = 0;
	switch(EventType)
	{
		case SCOREEVENT_HUMAN_SURVIVE:
			Points = 50;
			break;
		case SCOREEVENT_HUMAN_SUICIDE:
			Points = -10;
			break;
		case SCOREEVENT_INFECTION:
			Points = 30;
			break;
		case SCOREEVENT_KILL_INFECTED:
			Points = 10;
			break;
		case SCOREEVENT_KILL_WITCH:
			Points = 50;
			break;
		case SCOREEVENT_HELP_FREEZE:
			Points = 10;
			break;
		case SCOREEVENT_HELP_HOOK_BARRIER:
			Points = 10;
			break;
	}
	
	m_Score += Points;
	
	switch(Class)
	{
		case PLAYERCLASS_ENGINEER:
			m_EngineerScore += Points;
			break;
		case PLAYERCLASS_SOLDIER:
			m_SoldierScore += Points;
			break;
		case PLAYERCLASS_SCIENTIST:
			m_ScientistScore += Points;
			break;
		case PLAYERCLASS_MEDIC:
			m_MedicScore += Points;
			break;
		case PLAYERCLASS_NINJA:
			m_NinjaScore += Points;
			break;
		case PLAYERCLASS_MERCENARY:
			m_MercenaryScore += Points;
			break;
		case PLAYERCLASS_SNIPER:
			m_SniperScore += Points;
			break;
		case PLAYERCLASS_SMOKER:
			m_SmokerScore += Points;
			break;
		case PLAYERCLASS_HUNTER:
			m_HunterScore += Points;
			break;
		case PLAYERCLASS_BOOMER:
			m_BoomerScore += Points;
			break;
		case PLAYERCLASS_GHOST:
			m_GhostScore += Points;
			break;
		case PLAYERCLASS_SPIDER:
			m_SpiderScore += Points;
			break;
		case PLAYERCLASS_UNDEAD:
			m_UndeadScore += Points;
			break;
		case PLAYERCLASS_WITCH:
			m_WitchScore += Points;
			break;
	}
}

void CRoundStatistics::ResetPlayer(int ClientID)
{
	if(ClientID >= 0 && ClientID < MAX_CLIENTS)
		m_aPlayers[ClientID].Reset();
}

void CRoundStatistics::OnScoreEvent(int ClientID, int EventType, int Class)
{
	if(ClientID >= 0 && ClientID < MAX_CLIENTS)
		m_aPlayers[ClientID].OnScoreEvent(EventType, Class);
}

CRoundStatistics::CPlayer* CRoundStatistics::PlayerStatistics(int ClientID)
{
	if(ClientID >= 0 && ClientID < MAX_CLIENTS)
		return &m_aPlayers[ClientID];
	else return 0;
}


int CRoundStatistics::PlayerScore(int ClientID)
{
	if(ClientID >= 0 && ClientID < MAX_CLIENTS)
		return m_aPlayers[ClientID].m_Score/10;
	else return 0;
}

void CRoundStatistics::UpdatePlayer(int ClientID, bool IsSpectator)
{
	if(ClientID >= 0 && ClientID < MAX_CLIENTS)
		m_aPlayers[ClientID].m_WasSpectator = IsSpectator || m_aPlayers[ClientID].m_WasSpectator;
}
	
void CRoundStatistics::UpdateNumberOfPlayers(int Num)
{
	if(m_NumPlayersMin > Num)
		m_NumPlayersMin = Num;
	
	if(m_NumPlayersMax < Num)
		m_NumPlayersMax = Num;
}
	
bool CRoundStatistics::IsValidePlayer(int ClientID)
{
	if(ClientID >= 0 && ClientID < MAX_CLIENTS)
		return !m_aPlayers[ClientID].m_WasSpectator;
	else
		return false;
}
	
bool CRoundStatistics::IsValideRound()
{
	return m_NumPlayersMin >= 6;
}