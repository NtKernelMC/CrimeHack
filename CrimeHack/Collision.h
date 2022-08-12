#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
BYTE col_prologue[6] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
bool _nocolVehicles = true;
bool _nocolPeds = true;
bool _nocolObjects = true;
typedef struct _VECTOR
{
#pragma pack( 1 )
	float	X, Y, Z;
} VECTOR, * PVECTOR;
typedef struct _MATRIX4X4
{
#pragma pack( 1 )
	VECTOR	right;
	DWORD	flags;
	VECTOR	up;
	float	pad_u;
	VECTOR	at; // front
	float	pad_a;
	VECTOR	pos;
	float	pad_p;
} MATRIX4X4, * PMATRIX4X4;
// object_base is now unioned with a CEntity pointer where applicable
struct object_base
{
#pragma pack( 1 )
	void* vtbl;	// 0

	// this is now in CEntity
	//	CPlaceableSAInterface	Placeable;	// 4
	// but the following variables exist for compatability till we remove object_base completely
	float					coords[3];			// 4
	union
	{
		// is MTA right?
		float			m_heading;				// 16

		// and are we wrong?
		void* m_CMatrixPre;			// 16, a part of CPlaceable
		float* preMatrix;				// 16, a part of CPlaceable
		MATRIX4X4* preMatrixStruct;		// 16, a part of CPlaceable
	};
	union
	{
		void* m_CMatrix;				// 20
		float* matrix;				// 20
		MATRIX4X4* matrixStruct;			// 20
	};

	void* m_pRwObject;				// 24

	/********** BEGIN CFLAGS **************/
	unsigned long	bUsesCollision : 1;			// does entity use collision
	unsigned long	bCollisionProcessed : 1;	// has object been processed by a ProcessEntityCollision function
	unsigned long	bIsStatic : 1;			// is entity static
	unsigned long	bHasContacted : 1;		// has entity processed some contact forces
	unsigned long	bIsStuck : 1;			// is entity stuck
	unsigned long	bIsInSafePosition : 1;	// is entity in a collision free safe position
	unsigned long	bWasPostponed : 1;		// was entity control processing postponed
	unsigned long	bIsVisible : 1;			//is the entity visible
	unsigned long	bIsBIGBuilding : 1;		// Set if this entity is a big building
	unsigned long	bRenderDamaged : 1;		// use damaged LOD models for objects with applicable damage
	unsigned long	bStreamingDontDelete : 1;	// Dont let the streaming remove this
	unsigned long	bRemoveFromWorld : 1;		// remove this entity next time it should be processed
	unsigned long	bHasHitWall : 1;			// has collided with a building (changes subsequent collisions)
	unsigned long	bImBeingRendered : 1;		// don't delete me because I'm being rendered
	unsigned long	bDrawLast : 1;			// draw object last
	unsigned long	bDistanceFade : 1;		// Fade entity because it is far away
	unsigned long	bDontCastShadowsOn : 1; // Dont cast shadows on this object
	unsigned long	bOffscreen : 1;			// offscreen flag. This can only be trusted when it is set to true
	unsigned long	bIsStaticWaitingForCollision : 1;	// this is used by script created entities - they are static until the collision is loaded below them
	unsigned long	bDontStream : 1;			// tell the streaming not to stream me
	unsigned long	bUnderwater : 1;			// this object is underwater change drawing order
	unsigned long	bHasPreRenderEffects : 1;	// Object has a prerender effects attached to it
	unsigned long	bIsTempBuilding : 1;		// whether or not the building is temporary (i.e. can be created and deleted more than once)
	unsigned long	bDontUpdateHierarchy : 1;	// Don't update the aniamtion hierarchy this frame
	unsigned long	bHasRoadsignText : 1;		// entity is roadsign and has some 2deffect text stuff to be rendered
	unsigned long	bDisplayedSuperLowLOD : 1;
	unsigned long	bIsProcObject : 1;			// set object has been generate by procedural object generator
	unsigned long	bBackfaceCulled : 1;		// has backface culling on
	unsigned long	bLightObject : 1;			// light object with directional lights
	unsigned long	bUnimportantStream : 1;		// set that this object is unimportant, if streaming is having problems
	unsigned long	bTunnel : 1;			// Is this model part of a tunnel
	unsigned long	bTunnelTransition : 1;	// This model should be rendered from within and outside of the tunnel

	/********** END CFLAGS **************/
	uint8_t			wSeedColFlags;			// 32
	uint8_t			wSeedVisibleFlags;		// 33
	uint16_t		model_alt_id;			// 34 - model index
	uint8_t			__unknown_36[4];		// 36 - collision related (objects only?)

	//CReferences *pReferences; //36
	uint32_t* m_pLastRenderedLink;	// 40 CLink<CEntity*>* m_pLastRenderedLink;
	uint16_t		timer;			// 44
	uint8_t			m_iplIndex;		// 46 used to define which IPL file object is in
	uint8_t			interior_id;	// 47
	uint8_t			__unknown_48[6];		// 48

	//********* BEGIN CEntityInfo **********//
	uint8_t			nType : 3;				// 54 what type is the entity (2 == Vehicle)
	uint8_t			nStatus : 5;			// 54 control status

	// 55 alignment
	//********* END CEntityInfo **********//
	uint8_t			__unknown_56[8];		// 56
	uint8_t			quantumPhysics;			// 64 // this really needs to be figured out cos it's probably a bit field
	uint8_t			nImmunities;			// 65
	uint8_t			__unknown_66;			// 66
};
bool CollisionCheck(object_base* obj1, object_base* obj2)
{
	return (obj2->nType == 3 || obj2->nType == 2) &&
		((obj1->nType == 2 && _nocolVehicles) ||
			(obj1->nType == 3 && _nocolPeds) ||
			(obj1->nType == 4 && _nocolObjects));
}
void __declspec (naked) HOOK_PlayerCollision(void)
{
	static object_base* _obj1, * _obj2;
	static DWORD RETURN_ovrwr = 0x54CEFC, RETURN_process = 0x0054BCF4, RETURN_noProcessing = 0x54CF8D;
	__asm
	{
		jz hk_PlCol_process
		jmp RETURN_ovrwr
	}
hk_PlCol_process:
	__asm
	{
		pushad
		mov _obj2, esi
		mov _obj1, edi
	}
	if (!ColHack) goto hk_PlCol_processCol;
	if (_obj1 == nullptr || _obj2 == nullptr) goto hk_PlCol_noCol;
	if (CollisionCheck(_obj1, _obj2)) goto hk_PlCol_noCol;
hk_PlCol_processCol:
	__asm popad
	__asm jmp RETURN_process
	hk_PlCol_noCol :
	__asm popad
	__asm jmp RETURN_noProcessing
}