/*
 * Copyright (C) 2006-2010 - Frictional Games
 *
 * This file is part of Penumbra Overture.
 *
 * Penumbra Overture is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Penumbra Overture is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Penumbra Overture.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GAME_PLAYER_STATES_H
#define GAME_PLAYER_STATES_H

#include "ButtonHandler.h"
#include "GameMessageHandler.h"
#include "GameItemType.h"
#include "GameObject.h"
#include "Inventory.h"
#include "Notebook.h"
#include "NumericalPanel.h"
#include "DeathMenu.h"
#include "PlayerHands.h"

//////////////////////////////////////////////////////////////////////////
// BASE STATE
//////////////////////////////////////////////////////////////////////////

class iPlayerState
{
public:
	ePlayerState mType;
	ePlayerState mPreviuosState;

	iPlayerState(cInit *apInit,cPlayer *apPlayer,ePlayerState aType)
	{
		mpInit = apInit;

        mpPlayer = apPlayer;
		mType = aType;

		mPreviuosState = ePlayerState_LastEnum;
	}

	virtual ~iPlayerState(){}

	//-------------------------------------

	void InitState(iPlayerState* apPrevState)
	{
		if(apPrevState){
			apPrevState->LeaveState(this);
		}

		EnterState(apPrevState);
		mPreviuosState = apPrevState->mType;
	}

	//-------------------------------------
	
	/** Can be called each update from cPlayer->Update() */
	virtual void OnUpdate(float afTimeStep){}
	virtual void OnPostSceneDraw(){}
	virtual void OnDraw(){}

	/** When "Interact" input became triggered */
	virtual void OnStartInteract(){}
	/** When "Interact" input was triggered now stopped */
	virtual void OnStopInteract(){}

	/** When "Examine" input became triggered */
	virtual void OnStartExamine(){}
	/** When "Examine" input was triggered now stopped */
	virtual void OnStopExamine(){}

	virtual void OnStartHolster(){}

	virtual bool OnJump(){ return true;}

	/** When "Run" input became triggered */
	virtual void OnStartRun(){}
	/** When "Run" input was triggered, now stopped */
	virtual void OnStopRun(){}

	/** When "Crouch" input became triggered */
	virtual void OnStartCrouch(){}
	/** When "Crouch" input was triggered, now stopped */
	virtual void OnStopCrouch(){}

	/** When "InteractMode" became triggered */
	virtual void OnStartInteractMode(){}

	virtual bool OnStartInventory(){return true;}

	virtual bool OnStartInventoryShortCut(int alNum){ return true;}

	virtual bool OnMoveForwards(float afMul, float afTimeStep){return true;}
	virtual bool OnMoveSideways(float afMul, float afTimeStep){return true;}

	virtual bool OnAddYaw(float afVal){ return true;}
	virtual bool OnAddPitch(float afVal){return true;}

	virtual void EnterState(iPlayerState* apPrevState){}
	virtual void LeaveState(iPlayerState* apNextState){}

	//-------------------------------------

protected:
	cInit *mpInit;
	cPlayer* mpPlayer;

};

#endif // GAME_PLAYER_STATES_H
