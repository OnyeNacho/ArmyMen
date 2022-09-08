//========================================================================
//	FILE:			$Workfile: MsgText.h $
//
//	DESCRIPTION:	Army Unit Message Text data
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, September 17, 1996
//
//	REVISION:		$Header: /ArmyMen/src/MsgText.h 4     12/09/97 12:12p Phu $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited
//                      All rights reserved
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/MsgText.h $
//  
//  4     12/09/97 12:12p Phu
//  
//  3     10/22/97 10:56a Bwilcox
//  nsize removed from common,
//  boat changed to convoy throughout (including aai files)
//  
//  1     7/03/97 5:18p Nrobinso
//  
//  5     5/12/97 11:14p Dbunch
//  
//  4     5/12/97 12:00p Dbunch
//  
//  3     10/02/96 11:30a Aburgess
//  removed duplicated string
//  
//  2     9/26/96 11:59a Aburgess
//  redefinition of MSG strings
//  
//  1     9/19/96 2:18p Aburgess
//  MSG text strings (i.e. "reporting in", "under attack", etc.)
//  
// 
//  $Nokeywords:$
//========================================================================

#ifndef __MSGTEXT_H__
#define __MSGTEXT_H__

///========================================================================
//							DEFINES
///========================================================================

#define	NullMessage						MSG_AUDIO_BASE			- MSG_AUDIO_BASE
#define	Group1BazookaBattleM1			BazookaConditionRed		- MSG_AUDIO_BASE
#define	Group1BazookaBattleM2			BazookaRedAlert			- MSG_AUDIO_BASE
#define	Group1BazookaBattleM3		    BazookaBattleReport		- MSG_AUDIO_BASE
#define	Group1BazookaObservationM1		BazookaObservationReport - MSG_AUDIO_BASE
#define	Group1BazookaStatusM1		    BazookaStatusReport		- MSG_AUDIO_BASE
#define	Group2BazookaTigerLong			BazookaTigerSquad		- MSG_AUDIO_BASE
#define	Group2BazookaPantherLong		BazookaPantherSquad		- MSG_AUDIO_BASE
#define	Group2BazookaScorpionLong		BazookaScorpionSquad	- MSG_AUDIO_BASE
#define	Group2BazookaCoyoteLong		    BazookaCoyoteSquad		- MSG_AUDIO_BASE
#define	Group2BazookaCobraLong			BazookaCobraSquad		- MSG_AUDIO_BASE
#define	Group2BazookaHornetLong			BazookaHornetSquad		- MSG_AUDIO_BASE
#define	Group2BazookaGrizzleLong		BazookaGrizzleSquad		- MSG_AUDIO_BASE
#define	Group2BazookaWolfLong	     	BazookaWolfSquad		- MSG_AUDIO_BASE
#define	Group2BazookaLionLong			BazookaLionSquad		- MSG_AUDIO_BASE
#define	Group2BazookaViperLong			BazookaViperSquad		- MSG_AUDIO_BASE
#define	Group3BazookaP09M1				BazookaAllQuiet			- MSG_AUDIO_BASE
#define	Group3BazookaP10M1				BazookaAttackReturn		- MSG_AUDIO_BASE
#define	Group3BazookaP12M1				BazookaNoTargets		- MSG_AUDIO_BASE
#define	Group3BazookaP14M1				BazookaUnitSpotted		- MSG_AUDIO_BASE
#define	Group3BazookaP15M1				BazookaVehicleSpotted	- MSG_AUDIO_BASE
#define	Group3BazookaP15M2				BazookaVehicleSpottedPress - MSG_AUDIO_BASE
#define	Group3BazookaP16M1				BazookaStructureSpotted - MSG_AUDIO_BASE
#define	Group3BazookaP17M1				BazookaDestroyedTarget	- MSG_AUDIO_BASE
#define	Group3BazookaP18M1				BazookaAttacking		- MSG_AUDIO_BASE
#define	Group3BazookaP19M1				BazookaUnderFire		- MSG_AUDIO_BASE
#define	Group3BazookaP20M1				BazookaUnderHeaveyFire	- MSG_AUDIO_BASE
#define	Group3BazookaP20M2				BazookaUnderHeaveyFirePress - MSG_AUDIO_BASE

#define	Group1FlamerBattleM1			FlamerConditionRed		- MSG_AUDIO_BASE
#define	Group1FlamerBattleM2			FlamerRedAlert			- MSG_AUDIO_BASE
#define	Group1FlamerBattleM3		    FlamerBattleReport		- MSG_AUDIO_BASE
#define	Group1FlamerObservationM1		FlamerObservationReport - MSG_AUDIO_BASE
#define	Group1FlamerStatusM1		    FlamerStatusReport		- MSG_AUDIO_BASE

#define Group2Flamer452					Flamer452 - MSG_AUDIO_BASE
#define Group2Flamer454					Flamer454- MSG_AUDIO_BASE
#define Group2Flamer456					Flamer456- MSG_AUDIO_BASE
#define Group2Flamer458					Flamer458 - MSG_AUDIO_BASE
#define Group2Flamer462					Flamer462- MSG_AUDIO_BASE
#define Group2Flamer464					Flamer464- MSG_AUDIO_BASE
#define Group2Flamer466					Flamer466- MSG_AUDIO_BASE
#define Group2Flamer468					Flamer468- MSG_AUDIO_BASE
#define Group2Flamer472					Flamer472- MSG_AUDIO_BASE
#define Group2Flamer474					Flamer474- MSG_AUDIO_BASE
#define Group2Flamer476					Flamer476- MSG_AUDIO_BASE
#define Group2Flamer478					Flamer478- MSG_AUDIO_BASE
#define Group2Flamer482					Flamer482- MSG_AUDIO_BASE
#define Group2Flamer484					Flamer484- MSG_AUDIO_BASE
#define Group2Flamer486					Flamer486- MSG_AUDIO_BASE
#define Group2Flamer488					Flamer488- MSG_AUDIO_BASE
#define Group2Flamer492					Flamer492- MSG_AUDIO_BASE
#define Group2Flamer494					Flamer494- MSG_AUDIO_BASE
#define Group2Flamer496					Flamer496- MSG_AUDIO_BASE
#define Group2Flamer498					Flamer498- MSG_AUDIO_BASE

#define	Group3FlamerP09M1				FlamerAllQuiet			- MSG_AUDIO_BASE
#define	Group3FlamerP10M1				FlamerAttackReturn		- MSG_AUDIO_BASE
#define	Group3FlamerP12M1				FlamerNoTargets		- MSG_AUDIO_BASE
#define	Group3FlamerP14M1				FlamerUnitSpotted		- MSG_AUDIO_BASE
#define	Group3FlamerP15M1				FlamerVehicleSpotted	- MSG_AUDIO_BASE
#define	Group3FlamerP15M2				FlamerVehicleSpottedPress - MSG_AUDIO_BASE
#define	Group3FlamerP16M1				FlamerStructureSpotted - MSG_AUDIO_BASE
#define	Group3FlamerP17M1				FlamerDestroyedTarget	- MSG_AUDIO_BASE
#define	Group3FlamerP18M1				FlamerAttacking		- MSG_AUDIO_BASE
#define	Group3FlamerP19M1				FlamerUnderFire		- MSG_AUDIO_BASE
#define	Group3FlamerP20M1				FlamerUnderHeaveyFire	- MSG_AUDIO_BASE
#define	Group3FlamerP20M2				FlamerUnderHeaveyFirePress - MSG_AUDIO_BASE

#define	Group1GrenadeBattleM1			GrenadeConditionRed		- MSG_AUDIO_BASE
#define	Group1GrenadeBattleM2			GrenadeRedAlert			- MSG_AUDIO_BASE
#define	Group1GrenadeBattleM3		    GrenadeBattleReport		- MSG_AUDIO_BASE
#define	Group1GrenadeObservationM1		GrenadeObservationReport - MSG_AUDIO_BASE
#define	Group1GrenadeStatusM1		    GrenadeStatusReport		- MSG_AUDIO_BASE

#define Group2Grenade121					Grenade121 - MSG_AUDIO_BASE
#define Group2Grenade123					Grenade123- MSG_AUDIO_BASE
#define Group2Grenade125					Grenade125- MSG_AUDIO_BASE
#define Group2Grenade127					Grenade127 - MSG_AUDIO_BASE
#define Group2Grenade129					Grenade129- MSG_AUDIO_BASE
#define Group2Grenade131					Grenade131- MSG_AUDIO_BASE
#define Group2Grenade133					Grenade133- MSG_AUDIO_BASE
#define Group2Grenade135					Grenade135- MSG_AUDIO_BASE
#define Group2Grenade137					Grenade137- MSG_AUDIO_BASE
#define Group2Grenade139					Grenade139- MSG_AUDIO_BASE
#define Group2Grenade141					Grenade141- MSG_AUDIO_BASE
#define Group2Grenade143					Grenade143- MSG_AUDIO_BASE
#define Group2Grenade145					Grenade145- MSG_AUDIO_BASE
#define Group2Grenade147					Grenade147- MSG_AUDIO_BASE
#define Group2Grenade149					Grenade149- MSG_AUDIO_BASE
#define Group2Grenade151					Grenade151- MSG_AUDIO_BASE
#define Group2Grenade153					Grenade153- MSG_AUDIO_BASE
#define Group2Grenade155					Grenade155- MSG_AUDIO_BASE
#define Group2Grenade157					Grenade157- MSG_AUDIO_BASE
#define Group2Grenade159					Grenade159- MSG_AUDIO_BASE

#define	Group3GrenadeP09M1				GrenadeAllQuiet			- MSG_AUDIO_BASE
#define	Group3GrenadeP10M1				GrenadeAttackReturn		- MSG_AUDIO_BASE
#define	Group3GrenadeP12M1				GrenadeNoTargets		- MSG_AUDIO_BASE
#define	Group3GrenadeP14M1				GrenadeUnitSpotted		- MSG_AUDIO_BASE
#define	Group3GrenadeP15M1				GrenadeVehicleSpotted	- MSG_AUDIO_BASE
#define	Group3GrenadeP15M2				GrenadeVehicleSpottedPress - MSG_AUDIO_BASE
#define	Group3GrenadeP16M1				GrenadeStructureSpotted - MSG_AUDIO_BASE
#define	Group3GrenadeP17M1				GrenadeDestroyedTarget	- MSG_AUDIO_BASE
#define	Group3GrenadeP18M1				GrenadeAttacking		- MSG_AUDIO_BASE
#define	Group3GrenadeP19M1				GrenadeUnderFire		- MSG_AUDIO_BASE
#define	Group3GrenadeP20M1				GrenadeUnderHeaveyFire	- MSG_AUDIO_BASE
#define	Group3GrenadeP20M2				GrenadeUnderHeaveyFirePress - MSG_AUDIO_BASE

#define	MSG_MAX_MSGS					256

#define	MSG_MAX_PIECES					6

///========================================================================
//							LOOKUP TABLES
///========================================================================

// A message request consists of a list of MSGIDs for each part of a unit message.
// At this time there are up 6 parts to a message. These parts are:
//           GROUP1		Unit Message Rating
//           GROUP2     Unit Identification
//           GROUP3		Unit minor Identification
//           GROUP4     Unit Reporting in
//           GROUP5     Unit Situation
//           GROUP6     Optional structure and enemy references
//

// Lookup with situation ID [message number(0-11)][random(0-1)]
#define MSG_MAX_TYPES			7
#define	MSG_GROUP1_MAX			12
#define	MSG_GROUP1_RANDOM_MAX	2
 
ULONG	MessageGroup1[MSG_MAX_TYPES][ MSG_GROUP1_MAX ][ MSG_GROUP1_RANDOM_MAX ] =
{
  { 
	{ Group1GrenadeStatusM1,     Group1GrenadeStatusM1      },	//p09
	{ Group1GrenadeStatusM1,     Group1GrenadeStatusM1      },	//p10
	{ Group1GrenadeStatusM1,     Group1GrenadeStatusM1      },	//p11
	{ Group1GrenadeStatusM1,     Group1GrenadeStatusM1      },	//p12
	{ Group1GrenadeStatusM1,     Group1GrenadeStatusM1      },	//p13
	{ Group1GrenadeObservationM1, Group1GrenadeObservationM1  },	//p14
	{ Group1GrenadeObservationM1, Group1GrenadeObservationM1  },	//p15
	{ Group1GrenadeObservationM1, Group1GrenadeObservationM1  },	//p16
	{ Group1GrenadeBattleM3,    Group1GrenadeBattleM3     },	//p17
	{ Group1GrenadeBattleM3,    Group1GrenadeBattleM3     },	//p18
	{ Group1GrenadeBattleM1,    Group1GrenadeBattleM2     },	//p19
	{ Group1GrenadeBattleM1,    Group1GrenadeBattleM2     }		//p20
  },
  { 
	{ Group1FlamerStatusM1,     Group1FlamerStatusM1      },	//p09
	{ Group1FlamerStatusM1,     Group1FlamerStatusM1      },	//p10
	{ Group1FlamerStatusM1,     Group1FlamerStatusM1      },	//p11
	{ Group1FlamerStatusM1,     Group1FlamerStatusM1      },	//p12
	{ Group1FlamerStatusM1,     Group1FlamerStatusM1      },	//p13
	{ Group1FlamerObservationM1, Group1FlamerObservationM1  },	//p14
	{ Group1FlamerObservationM1, Group1FlamerObservationM1  },	//p15
	{ Group1FlamerObservationM1, Group1FlamerObservationM1  },	//p16
	{ Group1FlamerBattleM3,    Group1FlamerBattleM3     },	//p17
	{ Group1FlamerBattleM3,    Group1FlamerBattleM3     },	//p18
	{ Group1FlamerBattleM1,    Group1FlamerBattleM2     },	//p19
	{ Group1FlamerBattleM1,    Group1FlamerBattleM2     }		//p20
  },
  { 
	{ Group1BazookaStatusM1,     Group1BazookaStatusM1      },	//p09
	{ Group1BazookaStatusM1,     Group1BazookaStatusM1      },	//p10
	{ Group1BazookaStatusM1,     Group1BazookaStatusM1      },	//p11
	{ Group1BazookaStatusM1,     Group1BazookaStatusM1      },	//p12
	{ Group1BazookaStatusM1,     Group1BazookaStatusM1      },	//p13
	{ Group1BazookaObservationM1, Group1BazookaObservationM1  },	//p14
	{ Group1BazookaObservationM1, Group1BazookaObservationM1  },	//p15
	{ Group1BazookaObservationM1, Group1BazookaObservationM1  },	//p16
	{ Group1BazookaBattleM3,    Group1BazookaBattleM3     },	//p17
	{ Group1BazookaBattleM3,    Group1BazookaBattleM3     },	//p18
	{ Group1BazookaBattleM1,    Group1BazookaBattleM2     },	//p19
	{ Group1BazookaBattleM1,    Group1BazookaBattleM2     }		//p20
  },
  { 
	{ NullMessage,		NullMessage      },	//p09
	{ NullMessage,		NullMessage      },	//p10
	{ NullMessage,		NullMessage      },	//p11
	{ NullMessage,		NullMessage      },	//p12
	{ NullMessage,		NullMessage      },	//p13
	{ NullMessage,		NullMessage  },	//p14
	{ NullMessage,		NullMessage  },	//p15
	{ NullMessage,		NullMessage  },	//p16
	{ NullMessage,		NullMessage     },	//p17
	{ NullMessage,		NullMessage     },	//p18
	{ NullMessage,		NullMessage     },	//p19
	{ NullMessage,		NullMessage     }		//p20
  },
  { 
	{ NullMessage,		NullMessage      },	//p09
	{ NullMessage,		NullMessage      },	//p10
	{ NullMessage,		NullMessage      },	//p11
	{ NullMessage,		NullMessage      },	//p12
	{ NullMessage,		NullMessage      },	//p13
	{ NullMessage,		NullMessage  },	//p14
	{ NullMessage,		NullMessage  },	//p15
	{ NullMessage,		NullMessage  },	//p16
	{ NullMessage,		NullMessage     },	//p17
	{ NullMessage,		NullMessage     },	//p18
	{ NullMessage,		NullMessage     },	//p19
	{ NullMessage,		NullMessage     }		//p20
  },
  { 
	{ NullMessage,		NullMessage      },	//p09
	{ NullMessage,		NullMessage      },	//p10
	{ NullMessage,		NullMessage      },	//p11
	{ NullMessage,		NullMessage      },	//p12
	{ NullMessage,		NullMessage      },	//p13
	{ NullMessage,		NullMessage  },	//p14
	{ NullMessage,		NullMessage  },	//p15
	{ NullMessage,		NullMessage  },	//p16
	{ NullMessage,		NullMessage     },	//p17
	{ NullMessage,		NullMessage     },	//p18
	{ NullMessage,		NullMessage     },	//p19
	{ NullMessage,		NullMessage     }		//p20
  },
  { 
	{ NullMessage,		NullMessage      },	//p09
	{ NullMessage,		NullMessage      },	//p10
	{ NullMessage,		NullMessage      },	//p11
	{ NullMessage,		NullMessage      },	//p12
	{ NullMessage,		NullMessage      },	//p13
	{ NullMessage,		NullMessage  },	//p14
	{ NullMessage,		NullMessage  },	//p15
	{ NullMessage,		NullMessage  },	//p16
	{ NullMessage,		NullMessage     },	//p17
	{ NullMessage,		NullMessage     },	//p18
	{ NullMessage,		NullMessage     },	//p19
	{ NullMessage,		NullMessage     }		//p20
  }
  };

// Lookup with unit number [(0-77)][random(0-1)]
#define	MSG_GROUP2_MAX			78
#define	MSG_GROUP2_RANDOM_MAX	2
 
ULONG	MessageGroup2[ MSG_GROUP2_MAX ][ MSG_GROUP2_RANDOM_MAX ] =
{
	{ Group2Grenade121,  Group2Grenade121  },
 	{ Group2Grenade123,  Group2Grenade123  },
	{ Group2Grenade125,  Group2Grenade125  },
	{ Group2Grenade127,  Group2Grenade127  },
	{ Group2Grenade129,  Group2Grenade129  },
	{ Group2Grenade131,  Group2Grenade131  },
 	{ Group2Grenade133,  Group2Grenade133  },
	{ Group2Grenade135,  Group2Grenade135  },
	{ Group2Grenade137,  Group2Grenade137  },
	{ Group2Grenade139,  Group2Grenade139  },
	{ Group2Grenade141,  Group2Grenade141  },
 	{ Group2Grenade143,  Group2Grenade143  },
	{ Group2Grenade145,  Group2Grenade145  },
	{ Group2Grenade147,  Group2Grenade147  },
	{ Group2Grenade149,  Group2Grenade149  },
	{ Group2Grenade151,  Group2Grenade151  },
 	{ Group2Grenade153,  Group2Grenade153  },
	{ Group2Grenade155,  Group2Grenade155  },
	{ Group2Grenade157,  Group2Grenade127  },
	{ Group2Grenade159,  Group2Grenade159  },

	{ Group2Flamer452,  Group2Flamer452  },
 	{ Group2Flamer454,  Group2Flamer454  },
	{ Group2Flamer456,  Group2Flamer456  },
	{ Group2Flamer458,  Group2Flamer458  },
	{ Group2Flamer462,  Group2Flamer462  },
 	{ Group2Flamer464,  Group2Flamer464  },
	{ Group2Flamer466,  Group2Flamer466  },
	{ Group2Flamer468,  Group2Flamer458  },
	{ Group2Flamer472,  Group2Flamer472  },
 	{ Group2Flamer474,  Group2Flamer474  },
	{ Group2Flamer476,  Group2Flamer476  },
	{ Group2Flamer478,  Group2Flamer478  },
	{ Group2Flamer482,  Group2Flamer482  },
 	{ Group2Flamer484,  Group2Flamer484  },
	{ Group2Flamer486,  Group2Flamer486  },
	{ Group2Flamer488,  Group2Flamer458  },
	{ Group2Flamer492,  Group2Flamer492  },
 	{ Group2Flamer494,  Group2Flamer494  },
	{ Group2Flamer496,  Group2Flamer496  },
	{ Group2Flamer498,  Group2Flamer498  },

	{ Group2BazookaTigerLong,	Group2BazookaTigerLong },
	{ Group2BazookaPantherLong,	Group2BazookaPantherLong },
	{ Group2BazookaScorpionLong,Group2BazookaScorpionLong },
	{ Group2BazookaCoyoteLong,	Group2BazookaCoyoteLong },
	{ Group2BazookaCobraLong,	Group2BazookaCobraLong },
	{ Group2BazookaHornetLong,	Group2BazookaHornetLong },
	{ Group2BazookaGrizzleLong, Group2BazookaGrizzleLong },
	{ Group2BazookaWolfLong,	Group2BazookaWolfLong },
	{ Group2BazookaLionLong,	Group2BazookaLionLong },
	{ Group2BazookaViperLong,	Group2BazookaViperLong },

	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	 NullMessage },

	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },

	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },

	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	NullMessage },
	{ NullMessage,	 NullMessage }
};

	
// Lookup with unit situation number [(0-11)][priority(0-4)]
#define	MSG_GROUP5_PRIORITY_MAX	12
#define	MSG_GROUP5_RANDOM_MAX	5
 
ULONG	MessageGroup3[MSG_MAX_TYPES][ MSG_GROUP5_PRIORITY_MAX ][ MSG_GROUP5_RANDOM_MAX ] =
{
  {
	{ Group3GrenadeP09M1, Group3GrenadeP09M1, Group3GrenadeP09M1, Group3GrenadeP09M1, Group3GrenadeP09M1 },
	{ Group3GrenadeP10M1, Group3GrenadeP10M1, Group3GrenadeP10M1, Group3GrenadeP10M1, Group3GrenadeP10M1 },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ Group3GrenadeP12M1, Group3GrenadeP12M1, Group3GrenadeP12M1, Group3GrenadeP12M1, Group3GrenadeP12M1 },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ Group3GrenadeP15M1, Group3GrenadeP15M1, Group3GrenadeP15M1, Group3GrenadeP15M1, Group3GrenadeP15M2 },
	{ Group3GrenadeP16M1, Group3GrenadeP16M1, Group3GrenadeP16M1, Group3GrenadeP16M1, Group3GrenadeP16M1 },
	{ Group3GrenadeP17M1, Group3GrenadeP17M1, Group3GrenadeP17M1, Group3GrenadeP17M1, Group3GrenadeP17M1 } ,
	{ Group3GrenadeP18M1, Group3GrenadeP18M1, Group3GrenadeP18M1, Group3GrenadeP18M1, Group3GrenadeP18M1 },
	{ Group3GrenadeP19M1, Group3GrenadeP19M1, Group3GrenadeP19M1, Group3GrenadeP19M1, Group3GrenadeP19M1 },
	{ Group3GrenadeP20M1, Group3GrenadeP20M1, Group3GrenadeP20M1, Group3GrenadeP20M1, Group3GrenadeP20M2 }
  },
  {
	{ Group3FlamerP09M1, Group3FlamerP09M1, Group3FlamerP09M1, Group3FlamerP09M1, Group3FlamerP09M1 },
	{ Group3FlamerP10M1, Group3FlamerP10M1, Group3FlamerP10M1, Group3FlamerP10M1, Group3FlamerP10M1 },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ Group3FlamerP12M1, Group3FlamerP12M1, Group3FlamerP12M1, Group3FlamerP12M1, Group3FlamerP12M1 },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ Group3FlamerP15M1, Group3FlamerP15M1, Group3FlamerP15M1, Group3FlamerP15M1, Group3FlamerP15M2 },
	{ Group3FlamerP16M1, Group3FlamerP16M1, Group3FlamerP16M1, Group3FlamerP16M1, Group3FlamerP16M1 },
	{ Group3FlamerP17M1, Group3FlamerP17M1, Group3FlamerP17M1, Group3FlamerP17M1, Group3FlamerP17M1 } ,
	{ Group3FlamerP18M1, Group3FlamerP18M1, Group3FlamerP18M1, Group3FlamerP18M1, Group3FlamerP18M1 },
	{ Group3FlamerP19M1, Group3FlamerP19M1, Group3FlamerP19M1, Group3FlamerP19M1, Group3FlamerP19M1 },
	{ Group3FlamerP20M1, Group3FlamerP20M1, Group3FlamerP20M1, Group3FlamerP20M1, Group3FlamerP20M2 }
  },
  {
	{ Group3BazookaP09M1, Group3BazookaP09M1, Group3BazookaP09M1, Group3BazookaP09M1, Group3BazookaP09M1 },
	{ Group3BazookaP10M1, Group3BazookaP10M1, Group3BazookaP10M1, Group3BazookaP10M1, Group3BazookaP10M1 },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ Group3BazookaP12M1, Group3BazookaP12M1, Group3BazookaP12M1, Group3BazookaP12M1, Group3BazookaP12M1 },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ Group3BazookaP15M1, Group3BazookaP15M1, Group3BazookaP15M1, Group3BazookaP15M1, Group3BazookaP15M2 },
	{ Group3BazookaP16M1, Group3BazookaP16M1, Group3BazookaP16M1, Group3BazookaP16M1, Group3BazookaP16M1 },
	{ Group3BazookaP17M1, Group3BazookaP17M1, Group3BazookaP17M1, Group3BazookaP17M1, Group3BazookaP17M1 } ,
	{ Group3BazookaP18M1, Group3BazookaP18M1, Group3BazookaP18M1, Group3BazookaP18M1, Group3BazookaP18M1 },
	{ Group3BazookaP19M1, Group3BazookaP19M1, Group3BazookaP19M1, Group3BazookaP19M1, Group3BazookaP19M1 },
	{ Group3BazookaP20M1, Group3BazookaP20M1, Group3BazookaP20M1, Group3BazookaP20M1, Group3BazookaP20M2 }
  },
  {
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage } ,
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage }
  },
  {
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage } ,
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage }
  },
  {
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage } ,
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage }
  },
  {
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage } ,
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage },
	{ NullMessage, NullMessage, NullMessage, NullMessage, NullMessage }
  }
};
// Lookup with target [(0-11)][priority(0-4)]
#define	MSG_GROUP6_MAX			23
 
ULONG	MessageGroup6[ MSG_GROUP6_MAX ] =
{
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage,
	NullMessage
};

// Here's all the message strings
char*	Messages[ MSG_MAX_MSGS ] =
{
/*000*/	"",
/*001*/	"Condition Red:",
/*002*/	"Red Alert!:",
/*003*/	"Battle report :",
/*004*/	"Observation report :",
/*005*/	"Status report :",
/*006*/	"This is the hundred and twenty first",
/*007*/	"The hundred and twenty first",
/*008*/	"This is the hundred and twenty third",
/*009*/	"This is the one twenty third",
/*010*/	"This is the hundred and twenty fifth",
/*011*/	"This is the one twenty fifth",
/*012*/	"This is the hundred and twenty seventh",
/*013*/	"This is the one twenty seventh",
/*014*/	"This is the hundred and twenty ninth",
/*015*/	"This is the one twenty ninth",
/*016*/	"This is the hundred and thirty first",
/*017*/	"This is the one thirty first",
/*018*/	"This is the hundred and thirty third",
/*019*/	"This is the one thirty third",
/*020*/	"This is the hundred and thirty fifth",
/*021*/	"This is the one thirty fifth",
/*022*/	"This is the hundred and thirty seventh",
/*023*/	"This is the one thirty seventh",
/*024*/	"This is the hundred and thirty ninth",
/*025*/	"This is the one thirty ninth",
/*026*/	"This is the hundred and fourty first",
/*027*/	"This is the one fourty first",
/*028*/	"This is the hundred and fourty third",
/*029*/	"This is the one fourty third",
/*030*/	"This is the hundred and fourty fifth",
/*031*/	"This is the one fourty fifth",
/*032*/	"This is the hundred and fourty seventh",
/*033*/	"This is the one fourty seventh",
/*034*/	"This is the hundred and fourty ninth",
/*035*/	"This is the one fourty ninth",
/*036*/	"This is the hundred and fifty first",
/*037*/	"This is the one fifty first",
/*038*/	"This is the hundred and fifty third",
/*039*/	"This is the one fifty third",
/*040*/	"This is the hundred and fifty fifth",
/*041*/	"This is the one fifty fifth",
/*042*/	"This is the hundred and fifty seventh",
/*043*/	"This is the one fifty seventh", 
/*044*/	"This is the hundred and fifty ninth",
/*045*/	"This is the one fifty ninth",
/*046*/	"This is the four hundred and fifty second",
/*047*/	"This is the four fifty second",
/*048*/	"This is the four hundred and fifty fourth",
/*049*/	"This is the four fifty fourth",
/*050*/	"This is the four hundred and fifty sixth",
/*051*/	"This is the four fifty sixth",
/*052*/	"This is the four hundred and fifty eighth",
/*053*/	"This is the four fifty eighth",
/*054*/	"This is the four hundred and sixty second",
/*055*/	"This is the four sixty second",
/*056*/	"This is the four hundred and sixty fourth",
/*057*/	"This is the four sixty fourth",
/*058*/	"This is the four hundred and sixty sixth",
/*059*/	"This is the four sixty sixth",
/*060*/	"This is the four hundred and sixty eighth",
/*061*/	"This is the four sixty eighth",
/*062*/	"This is the four hundred and seventy second",
/*063*/	"This is the four seventy second",
/*064*/	"This is the four hundred and seventy fourth",
/*065*/	"This is the four seventy fourth",
/*066*/	"This is the four hundred and seventy sixth",
/*067*/	"This is the four seventy sixth",
/*068*/	"This is the four hundred and seventy eighth",
/*069*/	"This is the four seventy eighth",
/*070*/	"This is the four hundred and eighty second",
/*071*/	"This is the four eighty second",
/*072*/	"This is the four hundred and eighty fourth",
/*073*/	"This is the four eighty fourth",
/*074*/	"This is the four hundred and eighty sixth",
/*075*/	"This is the four eighty sixth",
/*076*/	"This is the four hundred and eighty eighth",
/*077*/	"This is the four eighty eighth",
/*078*/	"This is the four hundred and ninty second",
/*079*/	"This is the four ninty second",
/*080*/	"This is the four hundred and ninty fourth",
/*081*/	"This is the four ninty fourth",
/*082*/	"This is the four hundred and ninty sixth",
/*083*/	"This is the four ninty sixth",
/*084*/	"This is the four hundred and ninty eighth",
/*085*/	"This is the four ninty eighth",
/*086*/	"This is tiger squad",
/*087*/	"Tiger squad",
/*088*/	"This is panther squad",
/*089*/	"This is the panthers",
/*090*/	"This is scorpion squad",
/*091*/	"This is the scorpions",
/*092*/	"This is coyote squad",
/*093*/	"This is the coyotes",
/*094*/	"This is cobra squad",
/*095*/	"This is the cobras",
/*096*/	"This is hornet squad",
/*097*/	"This is the hornets",
/*098*/	"This is grizzly squad",
/*099*/	"This is the grizzlys",
/*100*/	"This is wolf squad",
/*101*/	"This is the wolfs",
/*102*/	"This is lion squad",
/*103*/	"This is the lions",
/*104*/	"This is viper squad",
/*105*/	"This is the vipers",
/*106*/	"First engineering corp.    ",
/*107*/	"First corp.    ",
/*108*/	"Second engineering corp.    ",
/*109*/	"Second corp.    ",
/*110*/	"Third engineering corp.    ",
/*111*/	"Third corp.    ",
/*112*/	"fourth engineering corp.    ",
/*113*/	"fourth corp.    ",
/*114*/	"Fifth engineering corp.    ",
/*115*/	"Fifth corp.    ",
/*116*/	"Sixth engineering corp.    ",
/*117*/	"Sixth corp.    ",
/*118*/	"This is Alpha Battery",
/*119*/	"This is Alpha",
/*120*/	"This is Bravo Battery",
/*121*/	"This is Bravo",
/*122*/	"This is Charlie Battery",
/*123*/	"This is Charlie",
/*124*/	"This is Delta Battery",
/*125*/	"This is Delta",
/*126*/	"This is Echo Battery",
/*127*/	"This is Echo",
/*128*/	"This is Fox-trot Battery",
/*129*/	"This is Fox-trot",
/*130*/	"This is Indigo Battery",
/*131*/	"This is Indigo",
/*132*/	"This is Tango Battery",
/*133*/	"This is Tango",
/*134*/	"This is Zulu Battery",
/*135*/	"This is Zulu",
/*136*/	"This is eagle air defense",
/*137*/	"Eagle air defense",		
/*138*/	"This is falcon air defense",
/*139*/	"Falcon air defense",
/*140*/	"This is vulture air defense",
/*141*/	"Vulture air defense",
/*142*/	"This is condor air defense",
/*143*/	"Condor air defense",
/*144*/	"This is crane air defense",
/*145*/	"Crane air defense",
/*146*/	"This is raven air defense",
/*147*/	"Raven air defense",
/*148*/	"This is crow air defense",
/*149*/	"Crow air defense",
/*150*/	"This is thunderbird air defense",
/*151*/	"Thunderbirds air defense",
/*152*/	"This is phoenix air defense",
/*153*/	"Phoenix air defense",
/*154*/	"infantry",
/*155*/	"light infantry",
/*156*/	"heavy infantry",
/*157*/	"Reporting",
/*158*/	"Reporting in",
/*159*/	"we are under heavy attack.",
/*160*/	"we are under heavy enemy fire.",
/*161*/	"we are under fire.",
/*162*/	"we are under heavy attack from enemy ",					// <type>
/*163*/	"we are under heavy fire from enemy ",						// <type>
/*164*/	"we are under attack.",
/*165*/	"we are under enemy fire.",
/*166*/	"we are under attack from enemy ",							// <type>
/*167*/	"we are under fire from enemy ",							// <type>
/*168*/	"we are engaging the enemy.",
/*169*/	"we have reached our target, commencing attack.",
/*170*/	"we have destroyed our target.",
/*171*/	"we have destroyed the enemy ",								// <target type>
/*172*/	"we have destroyed our target, moving on to new target.",
/*173*/	"we have destroyed out target, seeking out new target.",
/*174*/	"enemy structure spotted in our area.",
/*175*/	"recon of area reveals enemy ",								// <enemy structure>
/*176*/	"enemy vehicle spotted in our area.",
/*177*/	"enemy unit spotted in our area.",
/*178*/	"support needed in our area.",
/*179*/ "support needed to engage enemy.",
/*180*/	"no targets available in our area.",
/*181*/	"structure repaired, moving on.",	
/*182*/	"moving on , finished repairs on ",							// <structure>
/*183*/	"structure repaired.",
/*184*/	"finished repairs on ",										// <structure>
/*185*/ "returning to base.",
/*186*/ "taken sever casualties, returning to base.",
/*187*/ "no new activity in our area.",
/*188*/ "all quiet in our area.",
/*189*/ "available for support if needed.",
/*190*/	"light infantry",
/*191*/	"heavy infantry",
/*192*/	"commandos",
/*193*/	"engineers",
/*194*/	"artillery",
/*195*/	"anti-air battery",
/*196*/	"main base",
/*197*/	"fuel depot",
/*198*/	"radar outpost",
/*199*/	"power plant",
/*200*/	"prison camp",
/*201*/	"gun turret",
/*202*/	"ack-ack gun",
/*203*/	"pill box",
/*204*/	"building",
/*205*/	"extra base",
/*206*/	"jeep",
/*207*/	"tank",
/*208*/	"command helicopter",
/*209*/	"attack helicopter",
/*210*/	"halftrack",
/*211*/	"convoy",
/*212*/	"super soldier"
};
	
#endif	__MSGTEXT_H__

///========================================================================
//							EOF
///========================================================================
