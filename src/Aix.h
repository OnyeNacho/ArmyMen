//*******************************************************
//	AIX.cpp is the armymen game access to the
//	commander AI system. Route planning for units is done
//  independently of the commander via AIROUTER.cpp.     
//*******************************************************
#ifndef __AIX_H__
#define __AIX_H__ 
     
   //********************************************
   // What we export to foes (rest of armymen)
   //********************************************

// exported normally for the game
void AICommander();		 	// per think cycle of game	(play)
void AIDraw( void );		// per draw cycle of game	(play)
int	 Player2IsAI();			// is player2 ai?
int	 Player0IsAI();			// is player0 ai?

void AIControlUI();			// take control of ui 
extern int visibilityRange;		// how many tiles a LOS runs for unit

void DoFatal(char* buf);	// Bad news...hit debugger

#define MAX_FORCES 200

#endif // of __AIX_H__
