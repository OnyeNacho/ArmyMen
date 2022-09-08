//========================================================================
//	FILE:			$Workfile: USA.h $
//
//	DESCRIPTION:	USA language specific text.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Sunday, July 27, 1997
//
//	REVISION:		$Header: /ArmyMen/src/USA.h 53    4/06/98 3:20p Nrobinso $
//
//========================================================================
//                 COPYRIGHT(C)1996,1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//
//	Messages come in several forms:
//		1) Mission Objective Message - a single stream describing the mission
//			objective to the use.
//		2) Squad Message - action messages from the units sent to HQ. These
//			messages are comprised of:
//				<unit Id> <action> <foe> [<sector>]
//
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/USA.h $
//  
//  53    4/06/98 3:20p Nrobinso
//  encode cheats
//  
//  52    4/06/98 2:59p Nrobinso
//  move cheats text into usa.h
//  
//  50    3/29/98 3:16p Nrobinso
//  remove unused data
//  
//  49    3/27/98 10:52a Dmaynard
//  Added Checksumming of AiDefault.aii files in Map Checking
//  
//  48    3/26/98 6:27p Bwilcox
//  moving a text to usa.h, deleting unused UNIT_BLOCK stuff
//  
//  47    3/24/98 1:35p Nrobinso
//  go to voice over intead of text for aagun and blocked paratroopers
//  
//  46    3/23/98 11:37a Nrobinso
//  remove disconnect button
//  
//  45    3/18/98 2:32a Nrobinso
//  on/off text buttons gone
//  
//  44    3/18/98 12:51a Nrobinso
//  remove Studio 3DO from copyright notices
//  
//  43    3/17/98 11:27a Aburgess
//  removed unsed references
//  
//  42    3/15/98 7:15p Nrobinso
//  add play again
//  
//  41    3/13/98 11:41a Nrobinso
//  remove unused text for stats state
//  
//  40    3/12/98 1:19p Aburgess
//  modifications made to support override of "Abort Mission" with "End
//  Boot Camp"
//  
//  39    3/09/98 9:40a Aburgess
//  added ABOUT ARMYMEN and COPYRIGHT text
//  
//  38    3/07/98 10:48p Nrobinso
//  add dones button text
//  
//  37    3/04/98 3:45p Nrobinso
//  change resert button names on custom key screen
//  
//  36    3/03/98 10:58a Bwilcox
//  imrproving statistics titles
//  
//  35    3/02/98 10:32a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  34    2/26/98 12:33p Nrobinso
//  no cd text
//  
//  33    2/25/98 1:01p Aburgess
//  changed text references to Default keycodes to "Typical" and
//  "alternative"
//  
//  32    2/25/98 10:35a Aburgess
//  removed unused audio references
//  
//  31    2/18/98 6:39p Aburgess
//  new reset joystick ocnfiguration button text
//  
//  30    2/17/98 8:52a Aburgess
//  new BOOT CAMP text reference
//  
//  29    2/16/98 6:27p Nrobinso
//  joystick configuration support
//  
//  28    2/12/98 4:18p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  27    2/11/98 10:46a Nrobinso
//  Convoy is actually named Truck
//  
//  26    2/06/98 3:26p Nrobinso
//  add Mission Won
//  
//  25    2/06/98 7:20a Aburgess
//  modifications made to support the CUSTOM configuration screen
//  
//  24    2/05/98 3:29p Nrobinso
//  stat text
//  
//  23    2/04/98 12:27p Nrobinso
//  surviving units is now surviving troops
//  
//  22    2/01/98 4:31p Aburgess
//  modifications made to support new ART and maps files
//  
//  21    1/19/98 7:47p Aburgess
//  configuration screen modifications
//  
//  20    1/14/98 2:16p Aburgess
//  modifications made to support GAME_PLAY Options screens
//  
//  19    1/06/98 10:03a Aburgess
//  added Disconnect button and reqorked session logic for MultiPlyaer mode
// 
//  $Nokeywords:$
//
///========================================================================

#ifndef __USA_H__
#define __USA_H__

#ifndef __MSG_H__
#include "Msg.h"
#endif
#ifndef __SND_H__
#include "Snd.h"
#endif
#ifndef __STREAMS_H__
#include "Streams.h"
#endif
#ifndef __VOICES_H__
#include "Voices.h"
#endif

///========================================================================
//		CAMPAIGN STRINGS
///========================================================================

///========================================================================
//		UNIT STRINGS
///========================================================================

MSG_BLOCK	MsgVehicleNames[] =
{
	{ SND_NULL_SND_ID, "No Vehicle"		},
	{ SND_NULL_SND_ID, "Jeep"		},
	{ SND_NULL_SND_ID, "Tank"		},
	{ SND_NULL_SND_ID, "HalfTrack"	},
	{ SND_NULL_SND_ID, "Truck"		},
	{ SND_NULL_SND_ID, "Sarge"		},

	// do not place anything below this line
	{ SND_NULL_SND_ID, "\0" }
};

MSG_BLOCK	MsgObjectNames[ MAX_OBJECTS ] =
{
	{ SND_NULL_SND_ID, "Rock"			},
	{ SND_NULL_SND_ID, "Bush"			},
	{ SND_NULL_SND_ID, "Tree"			},
	{ SND_NULL_SND_ID, "Big Tree"		},
	{ SND_NULL_SND_ID, "Fallen Tree"	},

	{ SND_NULL_SND_ID, "Fence"			},
	{ SND_NULL_SND_ID, "Wall"			},
	{ SND_NULL_SND_ID, "Bridge"			},
	{ SND_NULL_SND_ID, "Foot Bridge"	},
	{ SND_NULL_SND_ID, "Explosive"		},

	{ SND_NULL_SND_ID, "Gun Turret"		},
	{ SND_NULL_SND_ID, "AA Gun"			},
	{ SND_NULL_SND_ID, "Base"			},
	{ SND_NULL_SND_ID, "Auxbase"		},
	{ SND_NULL_SND_ID, "Air Strip"		},

	{ SND_NULL_SND_ID, "Heli Pad"		},
	{ SND_NULL_SND_ID, "Prison Camp"	},
	{ SND_NULL_SND_ID, "Building"		},
	{ SND_NULL_SND_ID, "PillBox"		},
	{ SND_NULL_SND_ID, "Power Plant"	},

	{ SND_NULL_SND_ID, "Fence Gate"		},
	{ SND_NULL_SND_ID, "Wall Gate"		},
	{ SND_NULL_SND_ID, "Radar Building"	},
	{ SND_NULL_SND_ID, "Miscellaneous"	},
	{ SND_NULL_SND_ID, "Overpass"		},
	{ SND_NULL_SND_ID, "Special Itme"		}
};

///------------------------------------------------------------------------
//			MISCELLANEOUS GLOBAL File Name

char	AIfileName[]				 = "AiDefault.aai";
char	ObjHeadderName[]             = "obj_header.txt";

///------------------------------------------------------------------------
///------------------------------------------------------------------------
//			MISCELLANEOUS STRINGS
///------------------------------------------------------------------------

char	OK_TextBtn[]              = "OK";
char	CANCEL_TextBtn[]          = "CANCEL";
char	NEXT_TextBtn[]            = "NEXT";
char	BACK_TextBtn[]            = "BACK";
char	FINISH_TextBtn[]          = "FINISH";
char	DELETE_TextBtn[]          = "DELETE";
char	MORE_TextBtn[]            = "MORE";
char	APPLY_TextBtn[]           = "APPLY";

char	YES_TextBtn[]             = "YES";
char	NO_TextBtn[]              = "NO";
char	CONTINUE_TextBtn[]        = "CONTINUE";
char	PlayAgain_TextBtn[]       = "Play Again?";

char	BOOTCAMP_TextBtn[]        = "Boot Camp";
char	ONEPLAYER_TextBtn[]       = "One Player";
char	MULTIPLAYER_TextBtn[]     = "Multi-Player";
char	OPTIONS_TextBtn[]         = "Options";
char	QUIT_TextBtn[]            = "Quit";

char	NEWPLAYER_TextBtn[]       = "New Player";

char	CONTROLS_TextBtn[]        = "Controls";
char	AUDIO_TextBtn[]           = "Audio";
char	ABORTMISSION_TextBtn[]    = "Abort Mission";
char	ABOUT_TextBtn[]           = "About Armymen";

char	START_TextBtn[]           = "START";
char	EXIT_TextBtn[]            = "EXIT";

char*	GameStartTitle_Text       = "Game Start";
char*	OnePlayerTitle_Text       = "Player vs. Computer";
char*	CallSignTitle_Text        = "Player Callsign";
char*	CampaignSelectTitle_Text  = "Campaign Select";
char*	OptionsTitle_Text         = "Game Options";
char*	ControlsTitle_Text        = "Control Options";
char*	AudioTitle_Text           = "Audio Options";
char*	SfxTitle_Text             = "SFX Volume";
char*	MusicTitle_Text           = "Music Volume";
char*	VoiceTitle_Text           = "Voice Volume";

char	KEYPAD_TextBtn[]          = "Typical Configuration";
char	KEYBOARD_TextBtn[]        = "Alternative Configuration";
char	CUSTOM_TextBtn[]          = "Custom Configuration";
char	JOYSTICK_TextBtn[]        = "Joystick Configuration";
char	RESTOREkb_TextBtn[]       = "Typical Config";
char	RESTOREkp_TextBtn[]       = "Alternate Config";
char	RESTOREjoy_TextBtn[]      = "Reset to Defaults";

char*	MissionFailedTitle_Text   = "MISSION FAILED";
char*	AnyKeyTitle_Text          = "ANY KEY TO CONTINUE";

char*	MissionCompleteTitle_Text = "MISSION COMPLETE";
char*	MissionWonTitle_Text      = "MISSION WON";

char*	SargeColumnTitle_Text     = "Sarge Actions";
char*	GameColumnTitle_Text      = "Basic Game Actions";
char*	JoystickColumnTitle_Text  = "Joystick Buttons";

char*	RotateRightTitle_Text     = "Rotate Right";
char*	RotateLeftTitle_Text      = "Rotate Left";
char*	RunForwardTitle_Text      = "Run Forward";
char*	WalkForwardTitle_Text     = "Walk Forward";
char*	WalkBackwardTitle_Text    = "Walk Backward";
char*	TurretRightTitle_Text     = "Turret Right";
char*	TurretLeftTitle_Text      = "Turret Left";
char*	FireTitle_Text            = "Fire";
char*	StopBrakeTitle_Text       = "Stop/Brake";
char*	SlowTitle_Text            = "Slow";
char*	MainWeaponTitle_Text      = "Main Weapon";
char*	HeavyWeaponTitle_Text     = "Heavy Weapon";
char*	SpecialItemTitle_Text     = "Special Item";
char*	DiveTitle_Text            = "Dive";
char*	RollLeftTitle_Text        = "Roll Left";
char*	RollRightTitle_Text       = "Roll Right";
char*	RaisePositionTitle_Text   = "Raise Position";
char*	LowerPositionTitle_Text   = "Lower Position";

char*	StandTitle_Text           = "Stand";
char*	KneelTitle_Text           = "Kneel";
char*	ProneTitle_Text           = "Prone";
char*	EnterVehicleTitle_Text    = "Enter Vehicle";
char*	DropItemTitle_Text        = "Drop Item";
char*	FollowTitle_Text          = "Follow";
char*	AttackTitle_Text          = "Attack";
char*	DefendTitle_Text          = "Defend";
char*	AirStrikeTitle_Text       = "Air Strike";
char*	AirDropTitle_Text         = "Air Drop";
char*	ReconTitle_Text           = "Recon";
char*	FastAttackTitle_Text      = "Fast Attack";
char*	FastDefendTitle_Text      = "Fast Defend";
char*	SendTitle_Text            = "Send";
char*	UnitScrollTitle_Text      = "Unit Scroll";
char*	EndBootCamp_Text          = "End Boot Camp";

char*	NoCD_Text = "Army Men CD is not in the drive\n";

char cheat1[] = "Tvddvnc"; // Succumb
char cheat2[] = "Usjvnqi"; // Triumph
char cheat3[] = "Pnojtdjfou"; // Omniscient
char cheat4[] = "Qzspnbodfs"; // Pyromancer
char cheat5[] = "Bfspcbmmjtujdt"; // Aeroballistics
char cheat6[] = "Jowvmofsbcmf"; // Invulnerable
char cheat7[] = "Qbsbmztjt"; // Paralysis
char cheat8[] = "Ufmfljofujd"; // Telekinetic
char cheat9[] = "Qmfuipsb"; // Plethora
char cheat10[] = "Pddvmubujpo"; // Occultation
char cheat11[] = "Lbivob"; // Kahuna

//-------------------------------------------------------------------------

char*	Copyright0_Text           = "Army Men";
char*	Copyright1_Text           = "3DO, Army Men, and the 3DO and ";
char*	Copyright2_Text           = "Army Men logos are trademarks and/or ";
char*	Copyright3_Text           = "registered trademarks of the 3DO Company ";
char*	Copyright4_Text           = "Copyright 1998 The 3DO Company ";
char*	Copyright5_Text           = "All rights reserved.";
char*	smoky_text				  = "Only you can prevent forest fires.";

#endif
///========================================================================
//									EOF
///========================================================================
