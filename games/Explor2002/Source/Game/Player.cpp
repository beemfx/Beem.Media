#include "player.h"

CPlayerObject::CPlayerObject(int x, int y, Direction face){
	m_nFace=face;
	m_nXLoc=x;
	m_nYLoc=y;
}

CPlayerObject::~CPlayerObject(){
}

BOOL CPlayerObject::Move(MoveType Move, int movedst){
	switch(Move){
		case FORWARD:{
			switch(m_nFace){
				case NORTH:m_nYLoc-=movedst;break;
				case SOUTH:m_nYLoc+=movedst;break;
				case EAST:m_nXLoc+=movedst;break;
				case WEST:m_nXLoc-=movedst;break;
				default:return FALSE;
			}
			}break;
		case BACKWARD:{
			switch(m_nFace){
				case NORTH:m_nYLoc+=movedst;break;
				case SOUTH:m_nYLoc-=movedst;break;
				case EAST:m_nXLoc-=movedst;break;
				case WEST:m_nXLoc+=movedst;break;
				default:return FALSE;
			}
			}break;
		case STRAFE_LEFT:{
			switch(m_nFace){
				case NORTH:m_nXLoc-=movedst;break;
				case SOUTH:m_nXLoc+=movedst;break;
				case EAST:m_nYLoc-=movedst;break;
				case WEST:m_nYLoc+=movedst;break;
				default:return FALSE;
			}
			}break;
		case STRAFE_RIGHT:{
			switch(m_nFace){
				case NORTH:m_nXLoc+=movedst;break;
				case SOUTH:m_nXLoc-=movedst;break;
				case EAST:m_nYLoc+=movedst;break;
				case WEST:m_nYLoc-=movedst;break;
				default:return FALSE;
			}
			}break;
		default:return FALSE;
	}
	return TRUE;
}

void CPlayerObject::SetFace(Direction NewFace){
	m_nFace=NewFace;
}

void CPlayerObject::SetLocation(int x, int y){
	m_nXLoc=x;
	m_nYLoc=y;
}
BOOL CPlayerObject::CopyTFront(USHORT src[TFRONT_SIZE]){
	for(int i=0;i<TFRONT_SIZE;i++)
		m_aTFront[i]=src[i];
	return TRUE;
}

BOOL CPlayerObject::Turn(TurnType Turn){
	switch(Turn){
		case LEFT:{
			switch(m_nFace){
				case NORTH:m_nFace=WEST;break;
				case EAST:m_nFace=NORTH;break;
				case SOUTH:m_nFace=EAST;break;
				case WEST:m_nFace=SOUTH;break;
				default:return FALSE;
			}
			}break;
		case RIGHT:{
			switch(m_nFace){
				case NORTH:m_nFace=EAST;break;
				case EAST:m_nFace=SOUTH;break;
				case SOUTH:m_nFace=WEST;break;
				case WEST:m_nFace=NORTH;break;
				default:return FALSE;
			}
			}break;
		default:return FALSE;
	}
	return TRUE;
}

int CPlayerObject::GetXLoc(){
	return m_nXLoc;
}
int CPlayerObject::GetYLoc(){
	return m_nYLoc;
}

Direction CPlayerObject::GetFace(){
	return m_nFace;
}