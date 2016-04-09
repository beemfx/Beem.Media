#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <windows.h>
#include "defines.h"

class CPlayerObject{
	private:
		int m_nXLoc;
		int m_nYLoc;
		Direction m_nFace;
	public:
		CPlayerObject(int x, int y, Direction face);
		~CPlayerObject();
		BOOL Move(MoveType Move, int movedst);
		BOOL Turn(TurnType Turn);
		void SetFace(Direction newFace);
		void SetLocation(int x, int y);
		BOOL CopyTFront(USHORT src[TFRONT_SIZE]);
		int GetXLoc();
		int GetYLoc();
		Direction GetFace();
		USHORT m_aTFront[TFRONT_SIZE];
};

#endif