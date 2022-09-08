`//========================================================================
//	FILE:			$Workfile: Unit.cpp $
//
//	DESCRIPTION:	Army Unit processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Tuesday, August 13, 1996
//
//	REVISION:		$Header: /ArmyMen/src/Unit.cpp 566   4/17/98 8:34p Bwilcox $
//
//========================================================================
//                 COPYRIGHT(C)1996 The 3DO Company
//      Unauthorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//	
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Unit.cpp $
//  
//  566   4/17/98 8:34p Bwilcox
//  explosives now get TRIGGER_DESTROYED when they blow up
//  
//  565   4/17/98 7:11a Bwilcox
//  imrpoved trace messages
//  
//  564   4/16/98 5:05p Bwilcox
//  omit script warnings on repeated orders for playcycle == 0
//  
//  563   4/16/98 4:42p Bwilcox
//  script warning if order something twice in one frame
//  
//  562   4/16/98 12:56p Bwilcox
//  fix undeploy to set deadposition.
//  
//  561   4/15/98 3:17p Bwilcox
//  reduce routeplan costs by randomly deciding to update or not and
//  not tracking vehicles so closely
//  
//  560   4/15/98 12:03p Bwilcox
//  
//  559   4/15/98 11:59a Bwilcox
//  indenting normal traces and fixing setusercontrol setaicontrol
//  
//  558   4/13/98 10:48p Bwilcox
//  ai order failures delay 3 seconds before reporting now
//  
//  557   4/13/98 2:52p Bwilcox
//  
//  556   4/13/98 2:30p Bwilcox
//  
//  555   4/13/98 12:34p Bwilcox
//  warnings about no route if scriptdebug is on forSCRIPTORDER
//  
//  554   4/13/98 11:42a Bwilcox
//  place wont for ammoless weapons and sarge owned things
//  
//  553   4/13/98 12:52a Bwilcox
//  fixing vehicle control problem on event arriveal
//  
//  552   4/12/98 9:58p Bwilcox
//  fix vehicle deploy mode
//  
//  551   4/12/98 3:55p Bwilcox
//  
//  550   4/10/98 3:27p Bwilcox
//  mp ai controls only setup forces and vehicles
//  
//  549   4/10/98 11:25a Bwilcox
//  
//  548   4/10/98 1:12a Bwilcox
//  keeping deadposition as unique data
//  
//  547   4/09/98 9:57p Dmaynard
//  Added ItemSpecialUpdatePosition for cases where items enter and leave
//  the universe.
//  
//  546   4/09/98 8:47p Bwilcox
//  attemp to get pad status correct
//  
//  545   4/09/98 1:04p Bwilcox
//  for carried objects, return their scriptlocation as that of the carryer
//  
//  544   4/09/98 12:32p Phu
//  some scripted explosions don't sound
//  
//  543   4/09/98 12:07p Bwilcox
//  issargeuntrafficable varies if sarge is npc. new arg added
//  
//  542   4/09/98 10:41a Bwilcox
//  script location uses centerpos for flags
//  
//  541   4/08/98 8:29p Phu
//  change damage done by some scripted explosions
//  
//  540   4/08/98 12:50p Bwilcox
//  router reset for vehicles/sarge on order
//  
//  539   4/08/98 12:02p Bwilcox
//  unit unable to go to dest triggers event
//  
//  538   4/07/98 4:44p Bwilcox
//  dont trigger vis events on dead things
//  
//  537   4/07/98 11:42a Bwilcox
//  immobie foe for assets too
//  
//  536   4/07/98 6:19a Bwilcox
//  dead items cant see
//  
//  535   4/06/98 9:45p Bwilcox
//  remove tad primary and validation stuff
//  
//  534   4/06/98 2:03p Nrobinso
//  troopers won't enter a dead vehicle
//  
//  533   4/05/98 1:47p Bwilcox
//  add error recovery from assert in unit.cpp
//  
//  532   4/03/98 8:58p Bwilcox
//  clean up vehicle movement layer code
//  
//  530   4/02/98 10:35p Nrobinso
//  fix typo
//  
//  529   4/02/98 8:38p Bwilcox
//  fixed excess ack of orders
//  
//  528   4/02/98 6:29p Phu
//  typecast to avoid warnings
//  
//  527   4/02/98 2:46p Nrobinso
//  cleanup object triggers
//  
//  526   4/02/98 11:51a Bwilcox
//  fixing mp scriptally and deally
//  
//  525   4/01/98 4:10p Bwilcox
//  
//  524   3/31/98 2:39p Bwilcox
//  better script debug
//  
//  523   3/31/98 2:19p Bwilcox
//  armywide follow available
//  
//  522   3/30/98 10:11p Nrobinso
//  switch to animtime, which allows for pauses
//  
//  521   3/30/98 7:10p Bwilcox
//  allow resurrection of all local forces, not just green
//  
//  520   3/30/98 6:19p Bwilcox
//  sarge being ordered with rest of army
//  
//  519   3/30/98 5:49p Bwilcox
//  sarge ai activation and ordering goto
//  
//  518   3/30/98 2:49p Bwilcox
//  
//  517   3/30/98 1:16p Bwilcox
//  vehicles ai state reset at start of mission
//  
//  516   3/30/98 12:58p Phu
//  break! dammit
//  
//  515   3/30/98 11:49a Bwilcox
//  notify accepts a oneplayer message,
//  script order accepts an army
//  
//  514   3/30/98 10:27a Dmaynard
//  Enable Vehicle Fire in One plyaer/Multi-player games.
//  
//  513   3/29/98 11:52p Bwilcox
//  allow reject of deploy if badly formed
//  
//  511   3/28/98 7:14a Bwilcox
//  multiplayer-mode easter egg. Enjoy. Best Regards, The AI Guru
//  
//  510   3/27/98 8:38p Nrobinso
//  no sound when sarge is healed by script
//  
//  509   3/27/98 7:32p Bwilcox
//  
//  508   3/27/98 5:41p Phu
//  fix whereitem location in script place object
//  
//  507   3/27/98 1:04p Phu
//  explode at hotspot of item
//  
//  506   3/27/98 8:37a Bwilcox
//  trooper formation/unit follow point change
//  
//  505   3/26/98 8:47p Bwilcox
//  only assets with tads can see
//  
//  504   3/26/98 7:33a Bwilcox
//  removeobject does local drop of item if carried
//  
//  503   3/26/98 6:42a Bwilcox
//  blowitem added to header, added when weapon is unplaced
//  
//  502   3/25/98 6:59p Bwilcox
//  
//  501   3/25/98 5:58p Bwilcox
//  event trigger is better
//  
//  500   3/25/98 6:24p Phu
//  call armycollectflag
//  
//  499   3/25/98 5:18p Bwilcox
//  script notify for mp capture data
//  
//  498   3/25/98 10:16a Bwilcox
//  removeobjects only if active
//  
//  497   3/24/98 5:45p Nrobinso
//  switch to the untrafficable error only showing up in debug versions
//  
//  496   3/24/98 12:07p Bwilcox
//  immediate orders get acked but no "arrive" message
//  
//  495   3/24/98 11:58a Phu
//  deploy objects at hotspot
//  
//  494   3/24/98 12:10p Nrobinso
//  remove unused
//  
//  493   3/24/98 9:11a Bwilcox
//  units follow to different places
//  
//  492   3/23/98 6:26p Bwilcox
//  FOLLOW UNITS GO TO DIFFERENT PLACES
//  
//  491   3/22/98 10:43p Nrobinso
//  get rid of bwalk.axs
//  
//  490   3/22/98 9:03p Bwilcox
//  various script protections in case army not deployed
//  
//  489   3/22/98 7:31p Dmaynard
//  Changed ScriptPlaceObject to TRACE instead of Assert if it doesn't find
//  the request object.   The assert was triggered on ALL capture the flag
//  games with less than 4 players.  Script tries to place all four flags.
//  
//  488   3/22/98 3:58p Nrobinso
//  fix null sarge pointer
//  
//  487   3/22/98 3:17p Phu
//  changes w/Bruce to stop crashing in FOR_EACH_ARMY macros
//  
//  486   3/22/98 2:52p Nrobinso
//  heal sarge by script makes sound
//  
//  485   3/22/98 1:20p Bwilcox
//  
//  484   3/21/98 8:16p Dmaynard
//  Making UnitFind survive trying to find a unit in an army than has left
//  the game.
//  
//  483   3/21/98 8:02p Dmaynard
//  Made UnitFind return NULL instead of asserting  on failure.  Fixes a
//  Bug in Desert2 Multiplayer when a player leaves during startup and the
//  script tries to control his units.
//  
//  482   98-03-21 18:05 Dmaynard
//  Go back to Full AI processing per frame.  Partial can cause missing
//  victims on fire operations.
//  
//  481   3/20/98 2:04p Bwilcox
//  evadefire now always evades, never fights
//  
//  480   3/19/98 7:28p Phu
//  bump up scripted explode damage
//  
//  479   3/18/98 9:47p Bwilcox
//  
//  478   3/18/98 7:31p Bwilcox
//  fixed a follow crash when target of follow is destroyed
//  
//  477   3/17/98 10:46p Bwilcox
//  fix order carryover problem between units
//  
//  476   3/17/98 6:09p Bwilcox
//  proper null checking around aiitemfind calls
//  
//  475   3/17/98 5:28p Phu
//  don't select npc units when moving to next unit
//  
//  474   3/16/98 10:55a Bwilcox
//  ai major updates for units only 15times a second
//  
//  473   3/13/98 2:44p Bwilcox
//  scriptremoveobject checks for being sarge weapon
//  remove object message now allows other than mines
//  
//  472   3/12/98 7:35p Bwilcox
//  scriptrecharge
//  
//  471   3/12/98 5:50p Bwilcox
//  
//  470   3/12/98 5:22p Bwilcox
//  air fixes
//  
//  469   98-03-09 10:57 Dmaynard
//  units can engage in follow if was avoiding vehicle
//  
//  468   3/08/98 1:04a Nrobinso
//  only load anims for unit types that exist in the map
//  
//  467   3/06/98 4:14p Phu
//  loading bar
//  
//  466   3/05/98 12:10p Bwilcox
//  evade now limits distance it bothers to evade
//  
//  465   3/04/98 4:56p Bwilcox
//  scriptremove should only remove if on the map
//  
//  464   3/02/98 8:01p Phu
//  don't allow tab, command/scroll if no units to select
//  
//  463   3/02/98 2:41p Bwilcox
//  less frequent chase planning
//  
//  462   3/02/98 2:01p Bwilcox
//  removing dead code tied to npc sarges (a concept discarded)
//  
//  461   3/01/98 10:33a Bwilcox
//  airstrikes go against tan costs
//  
//  460   2/28/98 7:08p Bwilcox
//  multiple units exiting vehicle do it to separate tiles
//  
//  459   2/27/98 10:05p Bwilcox
//  fixing unitinitaial deploy for vehicles
//  
//  458   2/27/98 7:06p Nrobinso
//  unit deploy takes a vehicle pointer
//  
//  457   2/27/98 1:21p Bwilcox
//  cleaning up the air, supporting script airdrops for foes,e tc
//  
//  456   2/26/98 4:39p Awerner
//  added script support for AIRDROP command
//  
//  since this may be the last time I ever check a file into the armyman
//  project, and since I've tried to make a tradition of adding glib little
//  observations and suchlike to my checkin notices, I'd just like to take
//  this moment to say, and I'm getting all choked up here, I love you
//  guys! (sniffle)
//  
//  455   2/26/98 1:16p Bwilcox
//  improvingvehicle control routings
//  
//  454   2/26/98 12:24p Bwilcox
//  unit new code redudant with aibtank when bug fixed
//  
//  453   2/26/98 11:48a Bwilcox
//  moved code from wrong place to right place
//  
//  452   2/26/98 10:50a Bwilcox
//  improved vehicle router
//  
//  451   2/25/98 8:50p Nrobinso
//  clear vehicle pointer
//  
//  450   2/25/98 5:40p Nrobinso
//  put in avatar checking code
//  
//  449   2/25/98 4:45p Bwilcox
//  trigger arrival events at end of unit processing
//  
//  448   2/25/98 3:07p Nrobinso
//  bad assert
//  
//  447   2/25/98 2:49p Nrobinso
//  check for good deployment data
//  
//  446   2/25/98 1:10p Bwilcox
//  changes to vehicle/trooper interactions
//  
//  445   2/24/98 6:01p Bwilcox
//  retrirger deaths of vehicles and objects on startup of next mssions.
//  
//  444   2/23/98 1:42p Bwilcox
//  fixed vehicles running over troops contained within
//  
//  443   2/20/98 2:34p Bwilcox
//  trigger then event on entering npc vehicle with unit
//  
//  442   2/20/98 1:19p Nrobinso
//  fix up sounds
//  
//  441   2/20/98 12:00p Aburgess
//  corrected null pointer problem in pVehicle assignment
//  
//  440   2/20/98 11:01a Bwilcox
//  units can now follow and jump into an npc vehicle
//  
//  439   2/18/98 12:22p Bwilcox
//  tadbeing hit now called. removed useless formation code. removed attack
//  wander code
//  
//  438   2/17/98 3:18p Nrobinso
//  assets have infinite ammo
//  
//  437   2/17/98 1:42p Nrobinso
//  script visible back in
//  
//  436   2/16/98 9:25p Nrobinso
//  script display bmp
//  
//  435   2/16/98 4:16p Nrobinso
//  change showbmp to take a filename
//  
//  434   2/15/98 12:12p Bwilcox
//  removedscript visible and invisible. added scriptbmp
//  
//  433   2/14/98 1:48p Bwilcox
//  units stay mad for 10 seconds
//  
//  432   2/13/98 11:13a Phu
//  
//  431   2/12/98 12:25p Bwilcox
//  
//  430   2/10/98 12:21p Bwilcox
//  warns you if you give follow order to other than a unit
//  
//  429   2/07/98 2:16p Phu
//  have the script drop items at the hotspot of objects instead of the
//  position
//  
//  428   2/06/98 2:20p Bwilcox
//  vehiclebehavior trace added
//  
//  427   2/06/98 11:24a Bwilcox
//  vehicle resurrects in same facing as deploy
//  
//  426   2/05/98 12:35p Phu
//  flaming plastic
//  
//  425   2/05/98 8:22a Bwilcox
//  immobilefoe supported for testing
//  
//  424   2/03/98 9:15p Bwilcox
//  fixed assetfire bug, and eventsactive
//  
//  423   2/03/98 5:20p Bwilcox
//  eventsvalidate check
//  
//  422   2/03/98 11:31a Nrobinso
//  get prone first, where we're getting a diffuculty
//  
//  421   2/03/98 11:22a Bwilcox
//  
//  420   2/03/98 10:54a Bwilcox
//  
//  419   2/03/98 10:37a Bwilcox
//  sargedrop on deleting army
//  
//  418   2/02/98 4:25p Bwilcox
//  nits in vehicles fix. deploy when sareg exit vehicle
//  
//  417   2/02/98 4:06p Bwilcox
//  
//  416   2/02/98 3:22p Bwilcox
//  
//  415   2/02/98 1:54p Bwilcox
//  
//  414   2/02/98 12:35p Bwilcox
//  
//  413   2/01/98 5:45p Nrobinso
//  remove TESTPATH
//  
//  412   1/30/98 4:29p Bwilcox
//  fixing tab ring cycle
//  
//  411   1/30/98 2:19p Bwilcox
//  
//  410   1/30/98 12:43p Nrobinso
//  call checkanimfree to finish cleanup of trooper anims
//  
//  409   1/29/98 5:50p Bwilcox
//  unit names system changed
//  
//  408   1/29/98 3:16p Nrobinso
//  separate miner and sweeper
//  
//  407   1/29/98 12:33p Bwilcox
//  moved invis from trooper to unit
//  
//  406   1/29/98 11:22a Bwilcox
//  script explode now takes optional type of explosion
//  
//  405   1/28/98 8:59p Bwilcox
//  
//  404   1/28/98 8:20p Bwilcox
//  Script visible and invisible for units
//  
//  403   1/28/98 7:21p Bwilcox
//  removing traces
//  
//  402   1/28/98 1:01p Bwilcox
//  fixed drop bug for sarge in armydelete
//  
//  401   1/27/98 2:48p Bwilcox
//  fixed a unitprivatedata bug
//  
//  400   1/27/98 2:42p Phu
//  allow release build
//  
//  399   1/27/98 2:37p Bwilcox
//  puff away dead forces
//  
//  398   1/27/98 1:06p Bwilcox
//  finishing armydelete adjustments for multiplayer
//  
//  397   1/27/98 11:35a Bwilcox
//  ScriptUndeploy of army
//  
//  396   1/27/98 11:24a Bwilcox
//  aix dead code removal. spawned ArmiesDelete from ArmyDelete
//  
//  395   1/27/98 7:54a Bwilcox
//  fixed unit safe delpoyt of vehicle
//  
//  394   1/27/98 7:48a Bwilcox
//  units going usercontrolled become default selected
//  
//  393   1/26/98 4:36p Bwilcox
//  enter/exit vehicle code keeps troopers from being hit
//  
//  392   1/26/98 2:26p Bwilcox
//  CHANGED unit ATTACK BEHAVIOR
//  
//  391   1/26/98 1:58p Bwilcox
//  router fixing to center of tile
//  
//  390   1/25/98 5:26a Bwilcox
//  troopers can be ordered slow
//  
//  389   1/25/98 4:55a Bwilcox
//  paracount added for aai files
//  
//  388   1/23/98 4:53p Dmaynard
//  Fixed bug I had introduced into UnitSafeDeploy
//  
//  387   1/23/98 4:02p Dmaynard
//  Added TRACE for Illegal Deployment.  Looking for a bug where a
//  paratrooper never got deployed on remote machine.
//  
//  386   1/22/98 6:44p Nrobinso
//  use SetPath
//  
//  385   98/01/22 18:32 Dmaynard
//  
//  384   98/01/22 18:13 Dmaynard
//  
//  383   1/22/98 3:28p Bwilcox
//  sarge and units will move if deployed where some object is already
//  
//  382   1/21/98 1:44p Phu
//  fix paratrooper initialization
//  
//  381   1/21/98 11:02a Phu
//  prevent assets from firing during game setup substate
//  
//  380   1/21/98 10:59a Phu
//  bypass target acquisition for units during setup sub-state
//  
//  379   1/20/98 4:46p Nrobinso
//  fix scripted air strikes
//  
//  378   1/20/98 12:42p Bwilcox
//  removed calls to myuntrafficable ujit
//  
//  377   1/20/98 11:36a Bwilcox
//  implemented vehicleundeploy
//  
//  376   1/20/98 10:26a Awerner
//  fixed an incorrect comment
//  
//  375   1/19/98 3:24p Awerner
//  Added ALLY and UNALLY, MAKESTRATEGIC and MAKENONSTRATEGIC, and changed
//  get_ and drop_ to take specific item names
//  
//  374   1/18/98 12:50a Nrobinso
//  remove some validation code
//  
//  373   1/17/98 8:06a Bwilcox
//  
//  372   1/17/98 8:03a Bwilcox
//  
//  371   1/17/98 7:54a Bwilcox
//  
//  370   1/17/98 7:44a Bwilcox
//  fixed attack.defense radius bug
//  
//  369   1/17/98 7:38a Bwilcox
//  added follow_radius, and follow_engaged radius and fixed a
//  defend-radius bug
//  
//  368   1/15/98 12:57p Bwilcox
//  scriptfollow order extended to optional then clause
//  
//  367   1/15/98 9:35a Bwilcox
//  tile line optimizations
//  
//  366   1/14/98 4:29p Bwilcox
//  replaced cansee/canshoot coding
//  
//  365   1/14/98 9:47a Nrobinso
//  change UnitsValidateAnims to chck the command lists directly
//  
//  364   1/14/98 8:25a Bwilcox
//  fix to trooper routing system
//  
//  363   1/13/98 1:03p Nrobinso
//  validate all units anims
//  
//  362   1/13/98 12:35p Bwilcox
//  visoff events added
//  
//  361   1/13/98 10:33a Bwilcox
//  units exit vehicles nearby
//  
//  360   1/13/98 9:30a Bwilcox
//  
//  359   1/13/98 9:26a Bwilcox
//  
//  358   1/13/98 9:10a Bwilcox
//  fixed unitcloserwhere router data owner bug
//  
//  357   1/13/98 8:49a Bwilcox
//  fixing goal fix of vehcile
//  
//  356   1/13/98 7:59a Bwilcox
//  put validation on the debug menu bar
//  
//  355   1/12/98 7:15p Bwilcox
//  visibility tmp added to common, and moved itemsees army from
//  sarge/vehicle to unit.cpp
//  
//  354   1/12/98 6:00p Bwilcox
//  fixed armiesregenerate death messages
//  
//  353   1/08/98 8:34p Nrobinso
//  ifdef defbug out the unit dump routine
//  
//  352   1/08/98 2:15p Bwilcox
//  attack paramaters and trooper slide parameters added to defaults file
//  
//  351   1/07/98 12:24p Bwilcox
//  fix script deploy to use unit facing.
//  Make ScriptAlly work
//  
//  350   1/06/98 3:25p Awerner
//  added in script ALLY command
//  
//  349   1/02/98 2:12p Bwilcox
//  distance tests moved into canshoot
//  
//  348   1/02/98 12:53p Bwilcox
//  canshoot now takes a weapon arg
//  
//  347   1/02/98 12:30p Bwilcox
//  
//  346   1/02/98 11:22a Bwilcox
//  fixing asset fire some
//  
//	...
//  
//  $Nokeywords:$
///========================================================================


// Includes
#include "stdafx.h"

#include "Army.h"
#include "aix.h"
#include "unit.h"
#include "Tad.h"
#include "UnitText.h"
#include "sargemsg.h"
#include "miscfile.h"
#include "Ai.h"
#include "Map.h"
#include "Animfile.h"
#include "UnitMsg.h"
#include "trooper.h"
#include "aiaccess.h"
#include "object.h"
#include "comm.h"
#include "item.h"
#include "gameFlow.h"
#include "newdoor.h"
#include "aibtank.h"
#include "avatar.h"
#include "weapon.h"
#include "vehicle.h"
#include "pad.h"
#include "event.h"
#include "sarge.h"
#include "air.h"
#include "Damage.h"
#include "aix.h"
#include "explosions.h"
#include "vehiclemsg.h"
#include "comm.h"
#include "sounds.h"
#include "ui.h"
#include "audio.h"
#ifdef VALIDATE
char validate = 1; // perform validation?
#else
char validate = 0; // perform validation?
#endif
extern char immobileFoe;

static long lastAIUpdated = 0;

char scriptDebug = 0;
int PARACOUNT = 4;
extern char vehicleBehavior;
BOOL VehicleEnterable(VEHICLE* pVehicle);        
extern UNIT* curselectedunit;
int unitdie = 0;

char unitBehavior = 0;

UNIT* testunit = NULL;

extern char aiPlayers;	// 1 = armyplayer 2 = computer // 3 = both

///========================================================================
//							LOCAL VARIABLES
///========================================================================

static	BOOL		UNITloaded;

static SPOINT deployOffsets[9] = // offsets to deploy test
{ 
    {0,0}, // leader
    {32,0},{-32,0},	// one on each side of him
    {0,32},{0,-32}, // one above and below him
    {32,32},{32, -32},
    {-32,32},{-32, -32}
};

#define STILLMAD 10000		// how long before we forget we were attacked 10sec
#define MAX_ANIM_FILES 10
int DEFENSE_RADIUS = 7;
int ATTACK_RADIUS = 12;
int ATTACK_TILES = 10;	// how far will I go from center to hunt

// private data bits
#define UNIT_PRIVATE_TROOPER_MARK  0x40
#define UNIT_PRIVATE_BEEN		   0x01
//#define UNIT_PRIVATE_LOS		   0x02
#define UNIT_PRIVATE_HERE_NOW	   0x80
#define UNIT_PRIVATE_PROPOGATED	   0x20

static CSpriteCatalog *AnimFiles[ARMY_LAST_TROOPER][MAX_ANIM_FILES];

int manDied = 0;

static char *troop_anim_names[MAX_ANIM_FILES] =
{
	"Prone.AXS",	"Kneel.AXS",
	"Squash.AXS",	"Walk.AXS",
    "Shoot.AXS",	"Run.AXS",
	"Fall_Dive.AXS","PSDeath.AXS",
	"KSDeath.AXS",	"Melt.AXS"
};

#define MELT_INDEX (MAX_ANIM_FILES-1)

static ITEM* currentItemProp;

///========================================================================
//							LOCAL PROTOTYPES
///========================================================================
static void UnitDeployTroopers(UNIT* pUnit, SPOINT position,int facing);
static void UnitDoEvent(UNIT* pUnit);
static void	UnitFullOrders( UNIT* pUnit,

                            UNIT_ORDER orders,
                            SPOINT where, ITEM* pItem,
                            SPEED eSpeed,
                            BEHAVIOR pre,BEHAVIOR post,
                            int arriveEvent,int eventtype);
static void UnitsFinishTroopers();
static SPOINT NoConflictWhere(UNIT* pUnit, SPOINT where);   
static void UnitsUpdateDeath();
static void UnitFreeTad(UNIT* pUnit);
static SPOINT UnitDeploySpot(UNIT *pUnit,SPOINT position);
static void UnitValidateUnit(UNIT* pUnit);
static void UnitHandleTarget(UNIT* pUnit, ITEM* pTarget);
static void	UnitDelete( UNIT* pUnit );
static BOOL UnitSpriteLoad( void );
static void UnitApplyDefault(ARMY_TYPE eArmy, UNIT* pUnit,UNIT_TYPE eUnitType);
static void UnitSelectNames(ARMY_TYPE eArmy,UNIT_TYPE eUnitTYpe);
static void UnitCreate( ARMY_TYPE eArmy, int eUnitType, UNIT* pUnit);
static void UnitUpdatePosition( UNIT* pUnit );
static void UnitCreate( ARMY_TYPE eArmy, int eUnitType, UNIT* pUnit);
static void UnitApplyDefault(ARMY_TYPE eArmy,UNIT* pUnit, UNIT_TYPE eUnitType);
static void UnitTrooperApplyDefault(UNIT* pUnit,int n);
SPOINT VehicleRear(VEHICLE* pVehicle);
static BOOL UnitEngaged(UNIT* pUnit);
static void UnitsUpdateModes();
static SPOINT UnitAttackDestination(UNIT* pUnit);
static SPOINT UnitDefendDestination(UNIT* pUnit);
static void UnitsUpdateDestinations();
static void UnitsUpdateTargets();
static void UnitUpdateDestination(UNIT* pUnit);
static void UnitsUpdateMovement();
static void UnitsSeeAllUnits();
static void UnitsValidateAnims();

static unsigned char* privateMap = NULL;

// when sarge is 5 or more tiles away, run to him, unless we are engaged
int FOLLOW_RADIUS	= 5;
// when sarge is 12 or more tiles away, run to him even if engaged
int FOLLOW_ENGAGED_RADIUS	= 12;

UNIT* eunit = NULL;		// debugging

///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - startup routines
///*****************************************************************
///*****************************************************************

void ArmyDelete(int eArmy,int showIt);

///========================================================================
//	Function:		UnitLoad
//	Description:	Load in the Army Unit sprites. Return True if Fail.
///========================================================================

BOOL	UnitLoad( void )
{
	// check to see if we've already been loaded
	if ( UNITloaded ) return FALSE;

	// load the necessary sprites
	if ( UnitSpriteLoad() )  return TRUE;  		// return if fail

	// signify that the graphics have been loaded
	UNITloaded = TRUE;

	return FALSE;
}

///========================================================================
//	Function:		UnitTrooperCreate
//	Description:	Create a units troopers
///========================================================================
void UnitTrooperCreate(UNIT* pUnit,int n)
{
    // fill in the trooper data
    pUnit->initialTroops = n;
    UnitTrooperApplyDefault( pUnit,n);

	ASSERT( pUnit->nLastTroop >= 0 );
}

///========================================================================
//	Function:		UnitCreateAll
//	Description:	creates all units of a type for a legion
///========================================================================

void UnitCreateAll( ARMY_TYPE eArmy, int eUnitType, UNIT* pUnit, int nNumberOfUnits)
{
    int n;
	LEGION* pLegion = ArmyGetLegion(eArmy);
	// if we are playing and have no private unit data, acquire some for ai
	if (!pLegion->pUnitPrivateData && Armies[eArmy].Status)
	{
        int n = the_map.height * the_map.width;
		pLegion->pUnitPrivateData = (unsigned char*) malloc(n);
		if (!pLegion->pUnitPrivateData) TRACE("FAILED TO MALLOC PRIVATE DATA\n");
        else ZeroMemory((void*)pLegion->pUnitPrivateData, n);
	}

	int		nUnit;
    if (nNumberOfUnits == 0) return;  				// nothing to do
    
	// walk through the units outfitting them
    n = 0;
	for( nUnit=0; nUnit<nNumberOfUnits; ++nUnit )
	{
      pUnit->nCompID  = ++n; // unit name
      UnitCreate(eArmy,eUnitType,pUnit);
      ++pUnit;
    }
}


///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES -  enter a unit into game routines
///*****************************************************************
///*****************************************************************

void	UnitDeployPosition( UNIT* pUnit, SPOINT *pPos, short facing)
{
	pUnit->deployPosition = *pPos;
	pUnit->deployFacing = facing;
}

///========================================================================
//	Function:		UnitDeployTroopers
///========================================================================
static void UnitDeployTroopers(UNIT* pUnit, SPOINT goal,int facing)
{      
	// Deploy the troopers within this unit to different tiles
    TROOPER* pTrooper;
    int i;
    SPOINT deployPosition;
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
        deployPosition = UnitDeploySpot(pUnit,goal);
		TrooperDeploy( pTrooper, deployPosition, facing );
	}

    // it can see itself
    ItemUpdateSeen((ITEM*)pUnit,(ITEM*)pUnit);

}
      
///========================================================================
//	Function:		ParaSafeDeploy
//	Description:	Find an unblocked place to put para unit
///========================================================================
long ParaSafeDeploy(IPOINT index)
{
    if (UntrafficableUnit(index))	return 0; 
    SPOINT point;
    point = CenterPointFromTile(index);
    ITEM* pItemList;
    pItemList = GetObjectsMaskPoint(&point);
    if (pItemList != NULL) 
		return 0;  // dont want this

    // this is as good as any place
    return index;
}

///========================================================================
//	Function:		UnitSafeDeploy
//	Description:	Find an unblocked place to put unit
///========================================================================
long UnitSafeDeploy(IPOINT index)
{
    if (UntrafficableUnit(index))	return 0; 
    SPOINT point;
    point.x = IPOINT_X(index) << 4;
    point.y = IPOINT_Y(index) << 4;
    ITEM* pItemList = GetObjectsIntersectPoint(&point);
    while (pItemList != NULL)  {
		if (ITEM_TYPE(pItemList) == ARMY_VEHICLE)	return 0;  // nothing there please
		pItemList = pItemList->next;
	}

    // this is as good as any place
    return index;
}

///========================================================================
//	Function:		UnitInitialDeploy
//	Description:	deploy a unit.
//      This is called AFTER deploy animation is run.
// 		Result is Unit has full legal existence.
///========================================================================

void UnitInitialDeploy(UNIT *pUnit, SPOINT pPos, short facing, BEHAVIOR atmode, VEHICLE *pVehicle)	{

    IPOINT tile = ENCODE_IPOINT(pPos.x,pPos.y);
    if (ITEM_ARMY(pUnit) != ARMY_PLAYER && gpGame->GameType == GAMETYPE_ONEPLAYER)
        pUnit->npc = 1;

    if (!UnitSafeDeploy(tile) && !pVehicle)
    {
      ErrorDebug("!*!*! %s deployed illegally at %d.%d (%d.%d)\n",ItemDBName(pUnit),
          pPos.x,pPos.y,pPos.x>>4,pPos.y>>4);
      tile = (IPOINT)ItemFanOut((ITEM*)pUnit,tile,100,UnitSafeDeploy);
      if (!tile) {
		TRACE("!*!* %s failed to deploy \n", ItemDBName(pUnit));
		return;
	  }
	  pPos.x = IPOINT_X(tile) << 4;
	  pPos.y = IPOINT_Y(tile) << 4;
      TRACE("!*!*! %s relocatd to %d.%d\n",ItemDBName(pUnit),
              pPos.x,pPos.y);
    }   

      // leave off CR so line merges with order assigned to unit
      else 
      {	
          TRACE("    %s deploying %d troopers to %d.%d \n",ItemDBName(pUnit),
			pUnit->troops,pPos.x,pPos.y);
      }

    // Deploying a unit involves giving it an order in future
    pUnit->mode = UNIT_STILL;			// now active on world

	// Deploy the troopers within this unit to different tiles
    // before updateing position or fog breaks
    UnitDeployTroopers(pUnit,pPos,facing);

	// set starting location of unit, PAD,FOG
    ItemSpecialUpdatePosition((ITEM*)pUnit,&pPos);

	// create the tad for this unit
    ASSERT(!pUnit->common.pTad);
	TadCreateObject(ITEM_ARMY(pUnit), (int)ARMY_UNIT,(ITEM*)pUnit,TAD_SMART);

    pUnit->routeData.owner = ITEM_UID(pUnit);
      
    AIRouter(OFF_THE_MAP,&pUnit->routeData,UNIT_ROUTE,OFF_THE_MAP,0);	// clear router

	// Deploying a unit involves giving it an order in future
	UnitFullOrders(pUnit,UNIT_DEFEND,pPos,NULL,FAST_SPEED,
          atmode,atmode,EVENT_NUM_UNDEFINED,0);
	pUnit->focusArrived = TRUE;  // it is already there now

    // if we have no unit selected and this is our unit deploying, select it
    if (!curselectedunit && ITEM_ARMY(pUnit) == ARMY_PLAYER)
		if( !(pUnit->npc) )
			curselectedunit = pUnit;

    // unit belongs in vehicle
    if (pVehicle)
    {
      UnitEnterVehicle(pUnit,pVehicle);
    }
}


///========================================================================
//	Function:		UnitDeploy
//	Description:	deploy a unit.
//      This is called AFTER deploy animation is run.
// 		Result is Unit has full legal existence.
///========================================================================

void UnitDeploy(UNIT *pUnit, SPOINT *pPos, short facing,BEHAVIOR atmode)
{
    UnitInitialDeploy(pUnit,*pPos,facing,atmode);
    UnitDeployMessageSend(pUnit);
}

///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - change operating behavior of a unit
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		UnitMissionInit
//	Description:	a new mission is starting
///========================================================================
void UnitMissionInit()
{

      // clear out man died this mission
      manDied = 0;
      UNIT* pUnit;
      int eArmy,i;
	  VEHICLE* pVehicle;
	  SARGE* pSarge;
      FOR_EACH_ARMY(eArmy)
      {
          if (Armies[eArmy].Status == 0) continue; // not playing
          LEGION* pLegion = ArmyGetLegion(eArmy);
		  pSarge = SargePointer(eArmy);
		  pSarge->aiGoal = OFF_THE_MAP;
		  pSarge->delayFailed = 0;
		  pSarge->arrivalEvent = EVENT_NUM_UNDEFINED;

		  // clear out each unit, particularly ai
          FOR_EACH_UNIT(pLegion,pUnit)
          {
              // clear out last reported sighting
              pUnit->lastSitrep = NULL;
              // clear out merged unit command
              pUnit->mergedWith = 0;
              // clear out pending send event- should have none
              pUnit->sendYourEvent = 0;
              // clear out invisible
              pUnit->beInvisible = 0;
              // clear out old destination
              pUnit->destination = pUnit->common.position;
              pUnit->nHitWhen = 0;
              pUnit->pTarget = NULL;
 			pUnit->delayFailed = 0;
             pUnit->arrivalEvent = EVENT_NUM_UNDEFINED;
			// LEAVE pVehicle state alone- he can stay
          }
		  FOR_EACH_VEHICLE(pLegion,i)
		  {
			pVehicle = pLegion->pLegionVehicles[i];
			pVehicle->aiGoal = OFF_THE_MAP;
			pVehicle->delayFailed = 0;
			pVehicle->arrivalEvent = EVENT_NUM_UNDEFINED;
			pVehicle->imode = DEFENDFIRE;
			pVehicle->atmode = DEFENDFIRE;
		  }
	  }

      lastAIUpdated = 0;
      
}


///========================================================================
//	Function:		UnitGiveOrders
//	Description:	USER UI interpreted order a unit
///========================================================================

static void	UnitGiveOrders( UNIT* pUnit,
                    UNIT_ORDER orders,
                    SPOINT where, ITEM* pItem,
                    SPEED eSpeed)
{
      // decline if no unit or dead unit
      if (!pUnit || !UNIT_ALIVE(pUnit)) return;      
      // decline if unit not deployed on map
      if (!UNIT_ON_MAP(pUnit)) return;    
	  

      // convert follow into follow your sarge
      if (orders == UNIT_FOLLOW)
      {
		// if unit is already following, change to defend order in place
//		  if (pUnit->order == UNIT_FOLLOW)
//		  {
//			pItem = NULL;
//			where = pUnit->common.position;
//			orders = UNIT_DEFEND;
//		  }
		  // OTHERWISE carry out the follow request
//		  else
		  {
			pItem = (ITEM*) SargePointer(ITEM_ARMY(pUnit));
			where = OFF_THE_MAP;
		  }
      }

      eSpeed = FAST_SPEED;		// units always go fast.

      // if object-based order given, decide if object should remain an object
      // or become a location
      if (pItem)
      {
          if (scriptDebug)
          {
              TRACE( "    %s object order given\n",ItemDBName(pUnit));
          }

        // if item is on untrafficable space, convert to a location request
        // that can be adjusted later
        if (UntrafficableUnit(pItem->tile) && ITEM_TYPE(pItem) != ARMY_SARGE)
        {
			where = pItem->position;
		}
  	}	

    
    BEHAVIOR post,pre;
    switch(orders)			//pre-poststation behavior
    {
      case UNIT_ATTACK: pre = post = ATTACKFIRE; break;
      case UNIT_DEFEND: pre = post = DEFENDFIRE; break;
      case UNIT_FOLLOW: pre = post = DEFENDFIRE; break;
      default: post = DEFENDFIRE; pre = DEFENDFIRE; break;
    }

    // give reinterpreted full order
    UnitFullOrders(pUnit, orders, where, pItem, eSpeed, pre, post,
                  EVENT_NUM_UNDEFINED,0);
}

///========================================================================
//	Function:		UnitOrders
//	Description:	USER UI to give order to controllable units 
///========================================================================

void UnitOrders( UNIT* pOrderUnit,
                    UNIT_ORDER orders,
                    SPOINT pt, ITEM* pItem,
                    SPEED eSpeed)
{
      int eArmy = ITEM_ARMY(pOrderUnit);
      LEGION* pLegion = ArmyGetLegion(eArmy);
	  UNIT* pUnit;

		if (pt.x == 0 || SameSPoint(pOrderUnit->common.position,pt))
			SitRep(ARMY_ORDERACK,(ITEM*)pOrderUnit);
		else 
			SitRep(ARMY_GOTOACK,(ITEM*)pOrderUnit);


      // if multiplayer, control only the selected unit
      // if bootcamp do the same
      if (!(gpGame->GameType == GAMETYPE_ONEPLAYER) || gpGame->BootCamp)
      {
          UnitGiveOrders(pOrderUnit,orders,pt,pItem,eSpeed);
      }

      // if single player, control all not-npc units
      else {
          FOR_EACH_UNIT(pLegion,pUnit)	      
          {
              // ignore npc, dead, or undeployed units
              if (pUnit->npc) continue;
              if (!UNIT_ALIVE(pUnit)) continue;
              if (UNIT_IN_HQ(pUnit)) continue;
      
              UnitGiveOrders(pUnit,orders,pt,pItem,eSpeed);
          }
      }
}

///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - simulation update routines
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		ItemSeesArmy
//	Description:	mark units of army that this item sees
///========================================================================

static void ItemSeesArmy(ITEM* pItem,ARMY_TYPE eFoeArmy)
{
	 if (pItem->tile == 0) return;
	 if (pItem->nStrength == 0) return;

      LEGION* pFoeLegion = ArmyGetLegion(eFoeArmy);
      VEHICLE* pVehicle;
      int i;
      SARGE* pSarge;
      UNIT*	pFoeUnit;
      FOR_EACH_UNIT(pFoeLegion,pFoeUnit)
      {
         if (!UNIT_ON_MAP(pFoeUnit)) continue; 		// not around to be seen
         if (pFoeUnit->pVehicle) continue;
         ItemUpdateSeen(pItem,(ITEM*)pFoeUnit);
      }

      pSarge = SargePointer(eFoeArmy); 
      if (!pSarge->pVehicle) ItemUpdateSeen(pItem,(ITEM*)pSarge);

      for (i=0; i < pFoeLegion->nNumberOfVehicles; ++i)
      {
          pVehicle = pFoeLegion->pLegionVehicles[i];
          if (!pVehicle->common.tile) continue; // not on map
          ItemUpdateSeen(pItem,(ITEM*)pVehicle);      
      }

	  for( i = 0; i < pFoeLegion->nAssets; i++ )
	  {
		  OBJECTSTRUCT *pObject;

		  pObject = pFoeLegion->AssetList[i];
		  ItemUpdateSeen( pItem, (ITEM *)pObject );
	  }
}
#ifdef JUNK
static void UnitMinorUpdate()
{
    // By now, all units have currentTarget in tad that can be gotten,
    // and know whether or not they are locked onto that target.
    UnitValidateTad();					// prove tad is sound now.

    UnitsFinishTroopers();

    // by now all units have fought, so those that have lost all their
    // troopers must die. We dont want them dying earlier or that might
    // confuse tad. The system must expect to handle units with no troopers,
    // during the frame.
    // also handles units climbing onto vehicles

	UnitsUpdateDeath();
    // By now, all troopers have completed their movement.

    UnitValidateTad();						// prove tad is sound now.

}
#endif
///========================================================================
//	Function:		UnitUpdate
//	Description:	make all units do the right thing
///========================================================================

void UnitUpdate() 
{
//	long diff;

    // only do major update 15 times a second
 //   diff = gpGame->dwAnimTime - lastAIUpdated;
 //   if (diff < 75)
 //   {
 //     UnitMinorUpdate();
 //     return;
 //   }
    lastAIUpdated = gpGame->dwAnimTime;

	if( gpGame->game_substate != PLAY_SETUP_SUB_STATE )
		UnitsUpdateTargets();			// Find who units want to fight.
    // By now, all units have currentTarget in tad that can be gotten,
    // and know whether or not they are locked onto that target.
    UnitValidateTad();					// prove tad is sound now.

    UnitsUpdateModes();					// still or moving or engaged
    // By now, all units know whether they are still, moving or engaged.
   
    UnitsUpdateDestinations();			// Where will each move to.
    // By now, all units have a waypoint to head toward. 

    UnitsUpdateMovement();				// Go move all troopers.
    // by now all units have fought, so those that have lost all their
    // troopers must die. We dont want them dying earlier or that might
    // confuse tad. The system must expect to handle units with no troopers,
    // during the frame.
    // also handles units climbing onto vehicles

	UnitsUpdateDeath();
    // By now, all troopers have completed their movement.
    UnitsSeeAllUnits();						// compute who now sees whom

    UnitValidateTad();						// prove tad is sound now.

}


///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - exit a unit from game routines
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		UnitKill
//	Description:	all troopers have died, kill this unit.
///========================================================================

void	UnitKill( UNIT* pUnit )
{
      LEGION*		pLegion;
      pUnit->mode = UNIT_DEAD;

	  TRACE("    %s died\n",ItemDBName(pUnit));

      // each trooper has already died and influence removed.
      pUnit->deadPosition = pUnit->common.position;
   // set location to heaven/hell, off map, PAD,TAD,FOG
      ItemSpecialUpdatePosition((ITEM*)pUnit,&OFF_THE_MAP);

      DiedItemTriggerEvents((ITEM *)pUnit); // might cause unit to resurrect!

      pUnit->pVehicle = NULL;

      // if you kill the selected unit, try to find another
      if (pUnit == curselectedunit)
      {
          curselectedunit = NULL;

          pLegion = ArmyGetLegion(ITEM_ARMY(pUnit));
          FOR_EACH_UNIT(pLegion,pUnit)
          {
              if (!UNIT_ON_MAP(pUnit)) continue;
			  if( pUnit->npc ) continue;
              curselectedunit = pUnit;
              break;
          }
      }
}

///========================================================================
//	Function:		UnitUndeploy
//	Description:	remove unit from play (not same as Pickup into vehicle)
//		Result is unit off the world immediately
///========================================================================

void UnitUndeploy(UNIT *pUnit)	{

	pUnit->mode = UNIT_IN_HQ;		// now in limbo reserve
 
      if (scriptDebug)
      {
          TRACE("    %s undeployed\n",ItemDBName);
      }  

       pUnit->pVehicle = NULL;

   // remove the tad from the world
	if (pUnit->common.pTad)
	{
        UnitValidateTad(); // just test the hell out of the links
  		TadDeleteObject((TAD*)pUnit->common.pTad);	
		pUnit->common.pTad = NULL;
        UnitValidateTad(); // just test the hell out of the links
	}

    // need to pickup all troopers
    TROOPER* pTrooper;
    int i;
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
        TrooperPickup(pTrooper);
    }

    // update location, PAD,FOG
	ItemSpecialUpdatePosition((ITEM*)pUnit, &OFF_THE_MAP);
}

///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - wind-down routines
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		UnitDisband
//	Description:	releases all units of a legion
///========================================================================

void UnitDisband(LEGION* pLegion)
{
    UNIT* pUnit;
    // release tracking data for units of this legion
    if (pLegion->pUnitPrivateData) 
    {
      free(pLegion->pUnitPrivateData);
      pLegion->pUnitPrivateData = NULL;
    }

    FOR_EACH_UNIT(pLegion,pUnit)
			UnitDelete( pUnit );
}

///========================================================================
//	Function:		UnitFree
//	Description:	Release the Army Unit sprites.
///========================================================================

void	UnitFree( void )
{
	int eType;

	// check to see if we've in fact been loaded
	if (UNITloaded) 
	{

		FOR_EACH_TROOPER_TYPE(eType)
		{
			for (int i=0; i<MAX_ANIM_FILES; i++)	
			{
				FreeAnimImport(AnimFiles[eType][i]);
				AnimFiles[eType][i] = NULL;
			}

			if (TrooperCommands[eType])
				CheckAnimFree(TrooperCommands[eType] );
		}
		UNITloaded = FALSE;
	}
}


///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - debug routines 
///*****************************************************************
///*****************************************************************


///========================================================================
//	Function:		StartUnit
//	Description:	Debugging for tad. enable units tad
///========================================================================

void	StartUnit()
{
}

///========================================================================
//	Function:		StopUnit
//	Description:	Debugging for tad. disable units tad
///========================================================================

void	StopUnit()
{
}


///========================================================================
//	Function:		UnitDumpAll
//	Description:	show states of all troopers
///========================================================================
#ifdef _DEBUG
void	UnitDumpAll(int eArmy)
{
      int i;
      LEGION* pLegion = ArmyGetLegion(eArmy);
      UNIT* pUnit;
      TROOPER* pTrooper;
      SARGE* pSarge;
      pSarge = SargePointer(eArmy);
      TRACE("%s hp=%d ammo=%d act=%s @%d.%d ( %d)\n",
              ItemDBName(pSarge),
              pSarge->common.nStrength,
              pSarge->common.pWeapon->nAmmo,              
              AvatarActionDBName(pSarge->action),
              pSarge->common.position.x,
              pSarge->common.position.y,
              pSarge->common.tile);
      FOR_EACH_UNIT(pLegion,pUnit)
      {
          if (!UNIT_ON_MAP(pUnit)) continue;
          TRACE("%s status\n",ItemDBName(pUnit));
          FOR_EACH_TROOPER(pUnit,pTrooper,i)
          {
              TRACE("    %s %s hp=%d act=%s @%d.%d ( %d)\n",
                      ItemDBName(pTrooper),
                      TrooperName(ITEM_CLASS(pTrooper)),
                      pTrooper->common.nStrength,
                      AvatarActionDBName(pTrooper->action),
                      pTrooper->common.position.x,
                      pTrooper->common.position.y,
                      pTrooper->common.tile);

          }
      }
}
#endif

///========================================================================
//	Function:		UnitsValidateLocations
//	Description:	prove tile holds no units (during map object adding)
///========================================================================
      
void UnitsValidateLocations(IPOINT tile)
{
    int			eArmy;
	LEGION*		pLegion;
    UNIT* 		pUnit;
    TROOPER*    pTrooper;
    int			i;

	FOR_EACH_DEPLOYED_ARMY(eArmy)      
    {
      pLegion = ArmyGetLegion(eArmy);
      FOR_EACH_UNIT(pLegion,pUnit)
      {
          if (!UNIT_ON_MAP(pUnit)) continue;
          FOR_EACH_TROOPER(pUnit,pTrooper,i)
          {
              if (!TROOPER_ALIVE(pTrooper)) continue;
              ASSERT(pTrooper->common.tile != tile);
          }
          
      }
    }
}

///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - information about a specific unit
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		UnitTroopCount
//	Description:	return number of LIVING troopers of this unit
///========================================================================

int UnitTroopCount(UNIT* pUnit)
{ // return number of troopers left (alive or dying) in this unit
  // ones that died completely have already been erased.
     return pUnit->nLastTroop + 1;
}

///========================================================================
//	Function:		UnitFiringRange
//	Description:	how far does the best trooper shoot of this unit
///========================================================================

long	UnitFiringRange( UNIT* pUnit )
{	// find firing range of best trooper firing range
	long	nFiringRange = 0;
	long	nTroopRange;
    int 	i;
	TROOPER*	pTrooper;

	// ask each trooper for its distance and choose the largest
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
	{
		nTroopRange = AiObjectFiringRange( (ITEM*) pTrooper );
		if ( nTroopRange > nFiringRange ) nFiringRange = nTroopRange;
	}

	return( nFiringRange );
}

///========================================================================
//	Function:		UnitMinFiringRange
//	Description:	how near does the best trooper shoot of this unit
///========================================================================

static long	UnitMinFiringRange( UNIT* pUnit )
{
	long	nFiringRange = 0;
	long	nMinFiringRange = 0;
	long	nTroopRange;
	TROOPER*	pTrooper;
    int 	i;

	// ask each trooper for its distance and choose the largest
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
	{
		nTroopRange = AiObjectFiringRange( (ITEM*) pTrooper );
		if ( nTroopRange > nFiringRange )
        {
              nFiringRange = nTroopRange;
              nMinFiringRange = WeaponMinRange(pTrooper->common.pWeapon->eWeapon);
        }
	}

	return( nMinFiringRange );
}

///========================================================================
//	Function:		UnitFindClosestTrooper
//	Description:	find the trooper closest to the point
///========================================================================

TROOPER* UnitFindClosestTrooper(UNIT* pUnit,SPOINT* point)
{
     TROOPER* pTrooper;
     TROOPER* bestTrooper = NULL;
     int i;
     long d,bestD = 1000000;
     FOR_EACH_TROOPER(pUnit,pTrooper,i)
     {
         if (!TROOPER_HEALTHY(pTrooper)) continue; // he is dead
         d = GetDistance(point,&(pTrooper->common.position));
         if (d < bestD){
             bestD = d;
             bestTrooper = pTrooper;
         }
     }

     return bestTrooper;
}


///========================================================================
//	Function:		UnitGetTrooperStatus
//	Description:	return health of trooper in a unit
///========================================================================
HEALTH UnitGetTrooperStatus(UNIT* pUnit, int nTrooper)
{
      TROOPER* pTrooper;
      int i;

	  if (!pUnit)
		  return STATUS_DEAD;

      FOR_EACH_TROOPER(pUnit,pTrooper,i)
      {
          // not the correct trooper
          if ((pTrooper->common.nUniqueID & 0x07) != nTrooper) continue;
          // dead but not removed is dead
          if (pTrooper->common.nStrength == 0) return STATUS_DEAD;
          // 25% or less is dying
          if (pTrooper->common.nStrength <= (pTrooper->common.nMaxStrength >> 2)) return STATUS_DYING;
          // 50% or less is weak
          if (pTrooper->common.nStrength <= (pTrooper->common.nMaxStrength >> 1)) return STATUS_WEAK;
          // > 50% is strong
          return STATUS_STRONG;
      }
      // dead or never there is dead
      return STATUS_DEAD;
}

///*****************************************************************
///*****************************************************************
//	EXTERNALLY VISIBLE ROUTINES - information about multiple units or find unit
///*****************************************************************
///*****************************************************************

///========================================================================
//	Function:		UnitFind()
//	Description:	locate the Unit of this UID
///========================================================================

UNIT*	UnitFind( LONG nUniqueID )
{
	UNIT*		pUnit;
	LEGION*		pLegion;
	int eArmy;
	eArmy = EXTRACT_ARMY(nUniqueID);
	if (Armies[eArmy].Status == 0) return NULL; // army not there

	// now decode the unique ID
	ASSERT (OBJTYPE(nUniqueID) == ARMY_UNIT );
	pLegion = ArmyGetLegion(eArmy);
	if( !pLegion->pUnitList ) return NULL;
	pUnit = pLegion->pUnitList + SUB2TYPE(nUniqueID);
    if (!(ITEM_INDEX(pUnit) == SUB2TYPE(nUniqueID))) return NULL;
	return pUnit;
}

///========================================================================
//	Function:		UnitsInHQ
//	Description:	Get list of units of this type still in HQ
///========================================================================

int		UnitsInHQ( ARMY_TYPE eArmy, UNIT_TYPE eUnitType, UID* pUIDs )
{
	LEGION*		pLegion = ArmyGetLegion(eArmy);
	UNIT*		pUnit;
	int			nUnitsInReserve = 0;

    FOR_EACH_UNIT_OF_TYPE(pLegion,eUnitType,pUnit)
    {
        if (!UNIT_IN_HQ(pUnit)) continue;
        if (pUnit->paratrooper) continue; // ignore airdrop units
        
        *pUIDs = ITEM_UID(pUnit);
        ++nUnitsInReserve;
        ++pUIDs;
    }

	// let the caller know how many names were found
	return( nUnitsInReserve );
}


///========================================================================
//	Function:		ParatroopersInHQ
//	Description:	Get list of paraunits still in HQ
///========================================================================

int		ParatroopersInHQ( ARMY_TYPE eArmy, UID* pUIDs )
{
	LEGION*		pLegion = ArmyGetLegion(eArmy);
	UNIT*		pUnit;
	int			nUnitsInReserve = 0;

    FOR_EACH_UNIT_OF_TYPE(pLegion,ARMY_RIFLE_MEN,pUnit)
    {
        if (!UNIT_IN_HQ(pUnit)) continue;
        if (!pUnit->paratrooper) continue; // only airdrop units
        
        *pUIDs = ITEM_UID(pUnit);
        ++nUnitsInReserve;
        ++pUIDs;
    }

	// let the caller know how many names were found
	return( nUnitsInReserve );
}


///========================================================================
//	Function:		UnitNextInHQ
//	Description:	find the next free unit for deployment
///========================================================================

UNIT*	UnitNextInHQ( ARMY_TYPE eArmy, int eUnitType )
{ // next unit yet to create

	LEGION*		pLegion = ArmyGetLegion(eArmy);
	UNIT*		pUnit;

    FOR_EACH_UNIT_OF_TYPE(pLegion,eUnitType,pUnit)
    {
        if (!UNIT_IN_HQ(pUnit)) continue;
        if (pUnit->paratrooper) continue;  // cannot access airdrop 
      
        // already earmarked for deployment
        if (pUnit->deployPosition.x) continue;
		pUnit->deployPosition.x = 1;
        return pUnit;
    }

    return NULL;
}

///========================================================================
//	Function:		ParatrooperNextInHQ
//	Description:	find the next free paratrooper for deployment
///========================================================================

UNIT*	ParatrooperNextInHQ( ARMY_TYPE eArmy )
{ // next paraunit yet to deploy

	LEGION*		pLegion = ArmyGetLegion(eArmy);
	UNIT*		pUnit;

    FOR_EACH_UNIT_OF_TYPE(pLegion,ARMY_RIFLE_MEN,pUnit)
    {
        if (!UNIT_IN_HQ(pUnit)) continue;
        if (!pUnit->paratrooper) continue;  // must be para

      if (scriptDebug)
      {
        TRACE("    releasing paratrooper %s\n",ItemDBName(pUnit));
      }

        // this guy is ready to deploy
        return pUnit; 
    }

    return NULL;
}


///========================================================================
//	Function:		UnitAvailable
//	Description:	return the number of units created for army
//					or the number of units created of a specific type
///========================================================================

int	UnitAvailable( int eArmy, int eType )
{
	LEGION*		pLegion = ArmyGetLegion( (ARMY_TYPE)eArmy );
	int			nCount = 0;

	// get the units from the legion
    if ( !eType )
        nCount = pLegion->nTotalUnits;
    else
        nCount = pLegion->pLastUnit[eType] - pLegion->pUnits[eType];

	// report the count
	return( nCount );
}


///========================================================================
//	Function:		UnitGetNextFunctional
//	Description:given a unit or null, return the next alive unit to command
///========================================================================

UNIT*	UnitGetNextFunctional(UNIT* pOldUnit)
{
	UNIT*		pUnit;
	LEGION*		pLegion = ArmyGetLegion(ARMY_PLAYER);
    FOR_EACH_UNIT(pLegion,pUnit)
    {
      // ignore units earlier in the list
      if (pUnit <= pOldUnit) continue;
      if (!UNIT_ON_MAP(pUnit) && !UNIT_IN_VEHICLE(pUnit)) continue;
      if (pUnit->npc) continue; // ignore npc units 
      return pUnit;
    }

    // now return the 1st available unit (cyclic loop)
    FOR_EACH_UNIT(pLegion,pUnit)
    {
      if (!UNIT_ON_MAP(pUnit) && !UNIT_IN_VEHICLE(pUnit)) continue;
      if (pUnit->npc) continue; // ignore npc units 
      return pUnit;
    }

	return NULL;
}

///========================================================================
//	Function:		UnitGetNextTarget
//	Description:	given a unit/sarge or null, return the next visible target
//					across all foe armies. Look at sarge and units.
//					Item is currently seen this turn. no stale visibility.
///========================================================================

ITEM*	UnitGetNextTarget(ITEM* pItem )
{
    ITEM*		pOriginalItem = pItem;
    int			eBaseArmy = ARMY_PLAYER_2;
    int			eArmy;
	LEGION*		pLegion;
    UNIT* 		pUnit;
    SARGE*		pSarge;
 
	if (pItem)
		eBaseArmy = ITEM_ARMY(pItem);

	FOR_EACH_DEPLOYED_ARMY(eArmy)
    {
	  if (eArmy == ARMY_PLAYER) continue;

      if (eArmy < eBaseArmy) continue; 		// already did these armies
      pLegion = ArmyGetLegion(eArmy);

      // starting a new army
      if (eArmy != eBaseArmy)
      {
          pSarge = SargePointer(eArmy);
		  if ((void*)pSarge<=(void*)pOriginalItem)
			if (ITEM_SEEN_THIS_TURN(pSarge,ARMY_PLAYER)) return (ITEM*) pSarge;

   		  // cant see sarge, so continue with units of this army
          eBaseArmy = eArmy;
      }


      // currently hunting in this army. Sarge is 1st, so next must be units
      if (eArmy == eBaseArmy)
      {
          FOR_EACH_UNIT(pLegion,pUnit)
          {
 			  if ((ITEM*)pUnit<=pOriginalItem) continue;
              if (!UNIT_IN_OPEN(pUnit)) continue;
              if (!ITEM_SEEN_THIS_TURN(pUnit,ARMY_PLAYER)) continue;
             return (ITEM*) pUnit;
          }
      }
    }

   // we didnt find it. If we saw all, give up
   if (pOriginalItem == NULL) return NULL;

   // otherwise recurse once to scan the whole list from the start
   return UnitGetNextTarget(NULL);
}



///*****************************************************************
///*****************************************************************
//	INTERNAL ROUTINES not visible to outside
///*****************************************************************
///*****************************************************************

static long UnitOutOfVehicle(IPOINT at) // find a trafficable place to exit
{
    int eArmy;
    eArmy = ITEM_ARMY(fanoutItem);
    LEGION* pLegion;
    UNIT* pUnit;
    int i;
    TROOPER* pTrooper;
    SPOINT x;
    x = CenterPointFromTile(at);
    if (UntrafficableUnit(at)) return 0;

    // dont deploy where a unit/trooper of ours already is
    pLegion = ArmyGetLegion(eArmy);
    FOR_EACH_UNIT(pLegion,pUnit)
    {
	  if (!UNIT_ON_MAP(pUnit)) continue;
      if (pUnit->common.tile == at) return 0;
      FOR_EACH_TROOPER(pUnit,pTrooper,i)
      {
          if (pTrooper->common.tile == at) return 0;
      }
    }
    return at;
}

///========================================================================
//	Function:		UnitFullOrders
//	Description:	Fully detail unit behavior
///========================================================================

static void	UnitFullOrders( UNIT* pUnit,
                            UNIT_ORDER orders,
                            SPOINT where, ITEM* pItem,
                            SPEED eSpeed,
                            BEHAVIOR pre,BEHAVIOR post,
                            int arriveEvent,int eventtype)
{
      // decline if no unit or dead unit
      if (!pUnit || !UNIT_ALIVE(pUnit)) return;  
	  pUnit->sendYourEvent = 0;

      // decline if unit not deployed on map
      if (!UNIT_ON_MAP(pUnit)) return;    
	  
      
      // decline if in moving vehicle
      if (UNIT_IN_VEHICLE(pUnit) && pUnit->pVehicle->full_velocity)
      {
          if (scriptDebug)
          {
              TRACE("Unit refusing order while in moving vehicle\n");
          }
          return;
      }

	  SARGE* pSarge;
	  pSarge = SargePointer(ITEM_ARMY(pUnit));

	  // decline a follow order if sarge in vehcile and unit in same vehicle
	  if (orders == UNIT_FOLLOW && pUnit->pVehicle && pSarge && pSarge->pVehicle == pUnit->pVehicle) {
		  TRACE("Unit refused to follow sarge when both in vehicle\n");
		  return;
	  }

      // if unit in vehicle, update its position so route planner works
      if (UNIT_IN_VEHICLE(pUnit)) 
	  {
			ItemSpecialUpdatePosition((ITEM*)pUnit,&(pUnit->pVehicle->common.position));
	  }


      TAD* pTad = (TAD*) ((pItem) ? pItem->pTad : NULL);

      // maybe he clicked on illegal location or cant get to item point...
      // so reinterpret his click to get closest legal point
      if (where.x)
          where = ItemClosestWhere((ITEM*)pUnit,where); // get a legal where
      // dont go where other units are going tilewise, find a near point
      if (where.x)
          where = NoConflictWhere(pUnit,where);

      if (scriptDebug)
      {
          if (!pItem)
          {
              TRACE( "    %s %s %d.%d (%d.%d) from %d.%d -  %s during %s after\n",
              ItemDBName(pUnit), UnitOrderText[orders],
              where.x,where.y,
              where.x >> 4,where.y >> 4,
			  pUnit->common.position.x,pUnit->common.position.y,
              UnitModeText[pre],UnitModeText[post]);
          }
          else
          {
              char label[200];
              sprintf(label,"%s",ItemDBName(pItem));
              TRACE( "    %s %s %s - %s during %s after\n",
                  ItemDBName(pUnit), label,UnitOrderText[orders],
                  UnitModeText[pre],UnitModeText[post]);
          }
      }
 
    // assign the new orders
    pUnit->order = orders;
    pUnit->focusSpeed = eSpeed;
	pUnit->delayFailed = 0;

    // behaviors on way and after arrive
    pUnit->prestationBehavior = pre;
    pUnit->poststationBehavior = post;

    // define the location/focus
    pUnit->focusTile = ENCODE_IPOINT(where.x,where.y);
    // center the where
    if (where.x)
    {
      where = CenterPointFromTile(pUnit->focusTile);
    }
    pUnit->focusLocation = where;
	pUnit->focusItem = pItem;

    pUnit->arrivalEvent = arriveEvent;
    pUnit->eventtype = eventtype;
      
    // clear formation/router data
    pUnit->focusArrived = FALSE;
    pUnit->destination = OFF_THE_MAP;
    pUnit->routeData.destination = OFF_THE_MAP;

    // leave vehicle if inside one
    if (UNIT_IN_VEHICLE(pUnit))
    {
      UnitExitVehicle(pUnit,OFF_THE_MAP,0);
    }

    // if ordered in place, we arrive NOW (but say nothing)
    if (pUnit->common.tile == pUnit->focusTile)
    {
      pUnit->focusArrived = TRUE;
      pUnit->sendYourEvent = TRUE;
    }
}

///========================================================================
//	Function:		UnitDeploySpot
//	Description:	Find an available spot for a trooper to deploy
//					Try to disperse the troopers one to a tile.
///========================================================================

static SPOINT UnitDeploySpot(UNIT *pUnit,SPOINT position)
{

      int i;
      TROOPER* pTrooper;
      BOOL bOK;
      IPOINT tile;
	  SPOINT newPosition;
      for (int n = 0; n <= 8; ++n)
      {	      
          bOK = TRUE;
          newPosition.x = position.x + deployOffsets[n].x;
          newPosition.y = position.y + deployOffsets[n].y;

          tile = ENCODE_IPOINT(newPosition.x,newPosition.y);
          if (UntrafficableUnit(tile))  continue;
      
          FOR_EACH_TROOPER(pUnit,pTrooper,i)
          {
              if (tile != pTrooper->common.tile) continue;

              // already have one here
              bOK = FALSE;
              break;
          }
          if (bOK) return newPosition;
      }

      return position; // if all else fails, do it here
}


///========================================================================
//	Function:		UnitSpriteLoad
//	Description:	Load into sprites all graphics associated with UNITs.
///========================================================================

static BOOL	UnitSpriteLoad( void )
{
	BOOL	error = TRUE;		// assume failure
	char	pathname[32];
	char	filename[32];
	int eType;
	int flags;
	int		loadcount;
	int		eArmy;
	int		total;

	// load each of the unit types
	sprintf(pathname, "%s/Units/", the_map.terrain_name);
	SetPath(pathname);
	loadcount = 0;

    FOR_EACH_TROOPER_TYPE(eType)
	{
		total = 0;
		FOR_EACH_ARMY(eArmy)
			total += Armies[eArmy].Reserves.nUnitsAvail[eType];
		total += Armies[ARMY_PLAYER].nSargeTypesAvail[eType];

		if (!total)
			continue;	// don't load data if no units of that type

		if (TrooperCommands[eType])	{
//			TRACE("Loading %s files\n",TrooperName(eType));
			for (int i=0; i<MAX_ANIM_FILES; i++)	{
				sprintf(filename, "%s/%s", TrooperName(eType), troop_anim_names[i]);
				flags = BM_NOTRANSLATE;
				CSpriteCatalog *pCat = AnimImport(filename, flags);
				if (pCat)	{
					ProcessAnim(pCat, TrooperCommands[eType]);
					AnimFiles[eType][i] = pCat;
				}
				MissionLoading( 3600 + 95 * loadcount, 20000 );
				loadcount++;
			}
			CheckAnim(TrooperCommands[eType], TrooperName(eType), TrooperCommands[ARMY_RIFLE_MEN]);
		}
	}

	// if we made it here we were successful
	error = FALSE;

	return( error );
}

      
///========================================================================
//	Function:		UnitCreate
//	Description:	Create a unit with all its default data and troopers.
//		Result is a complete undeployed unit.
///========================================================================

static void UnitCreate( ARMY_TYPE eArmy, int eUnitType, UNIT* pUnit)
{

    // fill in the unit data
    UnitApplyDefault( eArmy, pUnit, (UNIT_TYPE)eUnitType);

	pUnit->common.seen[ARMY_PLAYER] = -1;
	pUnit->common.seen[ARMY_PLAYER_2] = -1;
	pUnit->common.seen[ARMY_PLAYER_3] = -1;
	pUnit->common.seen[ARMY_PLAYER_4] = -1;
}

///========================================================================
//	Function:		UnitApplyDefault
//	Description:	Apply the default settings to a unit.
///========================================================================

static void	UnitApplyDefault(ARMY_TYPE eArmy, UNIT* pUnit, UNIT_TYPE eUnitType)
{
    LEGION*		pLegion = &Armies[ eArmy ].Legion;
	int 		nID;
    
	// access the AIinfo data for a unit of this type
    nID 		 			 = pUnit - pLegion->pUnitList;	// offset into list
    ItemSetUID(pUnit,eArmy,ARMY_UNIT,eUnitType,nID);

	// now initialize the direction (facing)

    pUnit->common.facing     = DIRECTION_UP;
    pUnit->common.oldFacing     = DIRECTION_UP;
    pUnit->mode = UNIT_IN_HQ; 			// pick an inactive state
    pUnit->order = UNIT_NO_ORDER;
    pUnit->focusItem = NULL;
    pUnit->focusLocation = OFF_THE_MAP;
    pUnit->focusTile = 0;
	pUnit->paratrooper = FALSE;

    pUnit->common.tile = 0;
     pUnit->common.position.x = 0;
    pUnit->common.position.y = 0;
}

///========================================================================
//	Function:		UnitTrooperApplyDefault
//	Description:	Create troopers of a unit
///========================================================================

static void UnitTrooperApplyDefault(UNIT* pUnit,int n)
{
// create the troopers- space is allocated in bulk for all of them
    UNIT_TYPE	eUnitType 	= (UNIT_TYPE) ITEM_CLASS(pUnit);
	AI_UTBL*	pUnitTable 	= &(AIinfo.unitTables[eUnitType]);
    int			nTroopers 	= pUnitTable->nTroops;
    ARMY_TYPE 	eArmy 		= ITEM_ARMY(pUnit);
    int			nID 		= 0;
    AI_MAKEUP*	makeUp 		= &AIinfo.unitTables[eUnitType].makeup;
    AI_COMP*    comp	    = &AIinfo.unitTables[eUnitType].comp;
    TROOPER*	pTrooper;
    int			choice;
    int 		i;
    TROOPER_TYPE	eTrooperType;

    if (n) nTroopers = n;			// map data override on default
    ASSERT ( nTroopers );
    
    pUnit->common.nStrength = 0;	// total hp of unit
    pUnit->common.nMaxStrength = 0;	// total max hp of unit
    pUnit->troops = 0;
    pUnit->nLastTroop =  - 1;       // index of last one (no troopers)
    pUnit->nLeader = 0;				// leader starts as 1st trooper

    // now create the troops
    for (i = 0; i < nTroopers; ++i)
    {
       pTrooper = (TROOPER*) malloc(sizeof(TROOPER)); 
       if ( pTrooper == NULL )
       {
          TRACE("ERROR: Cant allocate TROOP space.\n");
       }

        // pick the trooper type. ALL UNITs of a type are composed equally
        choice  = comp->composition[nID];
        if (choice )
            eTrooperType = (TROOPER_TYPE)makeUp->eSecondary;
        else
            eTrooperType = (TROOPER_TYPE)makeUp->ePrimary;

        TrooperCreate(pUnit, pTrooper, eTrooperType);
        ++nID;
    }
}

///========================================================================
//	Function:		UnitUpdatePosition
//	Description:	Update unit position based on a lead trooper or vehicle
///========================================================================

static void	UnitUpdatePosition( UNIT* pUnit )
{
	TROOPER*	pLeader;
      
    // if in vehicle, update from vehicle 
    if (UNIT_IN_VEHICLE(pUnit))
    {
		ItemUpdatePosition((ITEM*)pUnit,&(pUnit->pVehicle->common.position));
        return;
    }

	// apply the leaders data to the unit. He IS the unit.
    pLeader = THE_LEADER(pUnit);
	if (pLeader)
	{
		ItemUpdatePosition((ITEM*)pUnit,&pLeader->common.position);
		pUnit->common.facing = pLeader->common.facing;
	}
}

///========================================================================
//	Function:		UnitDelete
//	Description:	Delete a Unit.
///========================================================================

static void	UnitDelete( UNIT* pUnit )
{
	TROOPER*	pTrooper;
    int i;

	ASSERT(pUnit);

	ItemFreeLabel((ITEM *)pUnit);

	FOR_EACH_TROOPER(pUnit,pTrooper,i)
	{
      if (!pTrooper)
		  continue;
      TrooperDelete( pTrooper );
      free(pTrooper);
      pUnit->pTroops[i] = NULL;
	}
    pUnit->nLastTroop = -1;			  // now has no troops

    UnitFreeTad(pUnit);
}

///========================================================================
//	Function:		UnitFreeTad
//	Description:	Release unit from tad control
///========================================================================

static void UnitFreeTad(UNIT* pUnit)
{
    if (pUnit->common.pTad)
	{
        UnitValidateTad(); // just test the hell out of the links
		TadDeleteObject((TAD*)pUnit->common.pTad);
		pUnit->common.pTad = NULL;
        UnitValidateTad(); // just test the hell out of the links
	}
}

///========================================================================
//	Function:		UnitEngaged
//	Description:	is unit engaged with target
///========================================================================

static BOOL UnitEngaged(UNIT* pUnit) // is it engaged with a target
{
      int foeRange,frndRange;
      long d;
      ITEM* pFoeItem = pUnit->pTarget;
      BOOL engaged = FALSE;

      // if have no target, are not engaged
      if (!pFoeItem)
      {
          engaged = FALSE;
          goto exit;
      }
      
      // if not at goal yet...
      if (IS_PRESTATION(pUnit))
      {
          // pay no attention to targets if ignoring fire
          if (pUnit->prestationBehavior == IGNOREFIRE)
          {
              engaged = FALSE;
              goto exit;
          }              
          // if RETURNFIRE mode, engage only if being shot at
          if (pUnit->prestationBehavior == RETURNFIRE &&
              (DWORD)(pUnit->nHitWhen+STILLMAD) < gpGame->dwAnimTime)
          {
              engaged = FALSE;
              goto exit;
          }
      }
      // at goal
      else
      {
          // pay no attention to targets
          if (pUnit->poststationBehavior == IGNOREFIRE)
          {
              engaged = FALSE;
              goto exit;
          }


          // if RETURNFIRE mode, engage only if being shot at
          if (pUnit->poststationBehavior == RETURNFIRE &&
              (DWORD)(pUnit->nHitWhen+STILLMAD) < gpGame->dwAnimTime)
          {
              engaged = FALSE;
              goto exit;
          }

      }

      // if unit is to follow sarge and is too far away, dont fight, run.
      if (pUnit->order == UNIT_FOLLOW)
      {
          // a unit on follow reverts to defend if target gone
          if (pUnit->focusItem == NULL)
          {
              engaged = FALSE;
      
              pUnit->sendYourEvent = TRUE;

              if (pUnit->order == UNIT_FOLLOW)
                  UnitFullOrders(pUnit,UNIT_DEFEND,pUnit->common.position,
                      NULL,FAST_SPEED, DEFENDFIRE,pUnit->poststationBehavior,
                      EVENT_NUM_UNDEFINED,0);

              engaged = FALSE;

              goto exit;
          }

          d = TileDistance(pUnit->common.tile,pUnit->focusItem->tile);
          // when in battle, dont rush after sarge until he is far away
		  // unless trooper was avoiding vehicle
		  if (THE_LEADER(pUnit)->override == AVOID_VEHICLE);
          else if ((pUnit->mode == UNIT_ENGAGED && d > FOLLOW_ENGAGED_RADIUS)
              || (pUnit->mode != UNIT_ENGAGED && d > FOLLOW_RADIUS))
          {
              engaged = FALSE;
              goto exit;
          }
      }

      // how far from target
      d =	GetDistance(&(pUnit->common.position),&(pFoeItem->position));

      // if in his firing range of us, we must fight or get slaughtered
      foeRange = AiObjectFiringRange(pFoeItem);
      frndRange = UnitFiringRange(pUnit);

      // we will evade
      if (IS_PRESTATION(pUnit) && pUnit->prestationBehavior == EVADEFIRE)
	  {
          engaged = FALSE;
          goto exit;
      }              
      if (!IS_PRESTATION(pUnit) && pUnit->poststationBehavior == EVADEFIRE)
      {
          engaged = FALSE;
          goto exit;
      }


      // if we are in range of it, we must attack since he can hit us...
      if (d <= (foeRange+64))
      {
          engaged = TRUE;
      }

      // if we are in our range of him, we can attack and should
      else if (d <= (frndRange + 16))
      {
          engaged = TRUE;
      }
      // otherwise we are not engaged
      else
      {
          engaged =  FALSE;
      }

exit:
      if (scriptDebug)
      {
          if (pUnit->mode == UNIT_ENGAGED && !engaged && unitBehavior)
              TRACE("    %s disengaging\n",ItemDBName(pUnit));
          if (pUnit->mode != UNIT_ENGAGED && engaged && unitBehavior)
          TRACE("    %s engaging\n",ItemDBName(pUnit));
      }

      return engaged;
      
}

///========================================================================
//	Function:		UnitsUpdateModes
//	Description:	decide unit mode for each as engaged or moving
///========================================================================

static void UnitsUpdateModes() // change mode of each unit
{
    UNIT_MODE mode;
    UNIT* pUnit;
    int eArmy;
    LEGION* pLegion;
    FOR_EACH_LOCAL_ARMY(eArmy)
    {       
      pLegion = ArmyGetLegion(eArmy);
      FOR_EACH_UNIT(pLegion,pUnit)
      {
        if (!UNIT_ON_MAP(pUnit)) continue; // dead or not deployed
        if (pUnit->mode == UNIT_DYING) continue; // cannot stop dying
        
        if (UNIT_IN_VEHICLE(pUnit))
              mode = UNIT_IN_VEHICLE;

        // An active unit is either "still", "moving", or "engaged".
        // To be engaged, it must be in some range of a target.

        else if (UnitEngaged(pUnit))
			mode = UNIT_ENGAGED;	// close enough
        else mode = UNIT_MOVING;							// not fighting

        pUnit->mode = mode;
      }
   }
}

///========================================================================
//	Function:		UnitAttackDestination
//	Description:	wander around the attack area
///========================================================================

static SPOINT UnitAttackDestination(UNIT* pUnit) // decide where unit should go
{
    // if we havent gotten to our focus, go there first
    if (pUnit->focusArrived == FALSE)
      return pUnit->focusLocation;

    //  we have a target within control range, attack him
    if (pUnit->pTarget)
	{
        long d = TileDistance(pUnit->pTarget->tile,
			ENCODE_IPOINT(pUnit->focusLocation.x,pUnit->focusLocation.y));
        if (d <= ATTACK_RADIUS) return pUnit->pTarget->position;
    }

    // default return to focus
    return pUnit->focusLocation;
}

///========================================================================
//	Function:		UnitDefendDestination
//	Description:	Selection location for defending unit to goto
///========================================================================

static SPOINT UnitDefendDestination(UNIT* pUnit) // decide where unit should go
{
    // if we havent gotten to our focus, go there first
    if (pUnit->focusArrived == FALSE)
      return pUnit->focusLocation;

    //  we have a target within control range of our defense point, attack him
    if (pUnit->pTarget)
	{
        long d = TileDistance(pUnit->pTarget->tile,
			ENCODE_IPOINT(pUnit->focusLocation.x,pUnit->focusLocation.y));
        if (d <= DEFENSE_RADIUS) return pUnit->pTarget->position;
   }

    // default return to focus
    return pUnit->focusLocation;
}


///========================================================================
//	Function:		ValidGoal
//	Description:	find a location of item that is or was legal
///========================================================================

SPOINT ValidGoal(ITEM* pItem)
{
      SPOINT goal;
      if (!pItem) return OFF_THE_MAP;

      goal = pItem->position;

      // if untrafficable, maybe it was a vehicle sitting still.

      // go find a nearby legal point
      if (UntrafficableUnit(ENCODE_IPOINT(goal.x,goal.y)))
      {
          IPOINT tile;
          tile = (IPOINT)ItemFanOut((ITEM*)pItem,pItem->tile,10,UnitSafeDeploy);
          goal = CenterPointFromTile(tile);
      }

      return goal;
}

UNIT* vlUnit;
SPOINT ValidUnitGoal(ITEM* pItem)
{
      SPOINT goal;
      if (!pItem) return OFF_THE_MAP;

	  // dont land exactly on it (esp. for sarge being followed)
      goal = pItem->position;
	  int offset;
	  offset = pItem->tile & 0x03;
	  switch(offset)
	  {
		case 0: goal.x += 32; break;
		case 1: goal.y += 32; break;
		case 2: goal.x -= 32; break;
		default: goal.y -= 32;
	  }

      // if untrafficable, maybe it was a vehicle sitting still.

      // go find a nearby legal point
      if (UntrafficableUnit(ENCODE_IPOINT(goal.x,goal.y)))
      {
          IPOINT tile;
          tile = (IPOINT)ItemFanOut((ITEM*)pItem,pItem->tile,10,UnitSafeDeploy);
          goal = CenterPointFromTile(tile);
      }


      return goal;
}
      
///========================================================================
//	Function:		EvadeTarget
//	Description:	go away from someone
///========================================================================
static IPOINT farTile;
static int bestDist;      
static IPOINT avoidTile;
      
static long UnitEvadeFind(IPOINT at)
{
      int d;
      
      // cant go here
      if (UntrafficableUnit(at)) return 0;
      
      // not a more distant place
      d = TileDistance(at,farTile);
      if (d < bestDist) return 0;

      // this is better
      bestDist = d;
      avoidTile = at;
	  return 0;
}

static SPOINT EvadeTarget(UNIT* pUnit)
{
      SPOINT goal;
      // object died, change to defend where you are
      // or lost visibility, switch to attack or defend where you are
      if (pUnit->pTarget->nStrength == 0 ||
          !ItemVisible(ITEM_ARMY(pUnit),pUnit->pTarget))
      {
          if (scriptDebug)
          {
              TRACE("    %s lost evade, staying put\n",ItemDBName(pUnit));
          }
          return OFF_THE_MAP;
      }

      int d;
      // too far away to bother evading
      d = GetDistance(&(pUnit->pTarget->position),&pUnit->common.position);
      if (d > 190) return OFF_THE_MAP;

      // find farthest away from him that is good
      farTile = pUnit->pTarget->tile;
      avoidTile = pUnit->common.tile;
      bestDist = TileDistance(farTile,avoidTile);
      ItemFanOut((ITEM*)pUnit,pUnit->common.tile,10,UnitEvadeFind);
      goal = CenterPointFromTile(avoidTile);
      return goal;
}

///========================================================================
//	Function:		ChaseTarget
//	Description:	go after someone
///========================================================================

static SPOINT ChaseTarget(UNIT* pUnit)
{
	  SPOINT destination,fix;
      int oldd,d;
	  vlUnit = pUnit;
	  destination = ValidUnitGoal(pUnit->focusItem);  // where I want to go
      oldd = GetDistance(&pUnit->focusLocation,&destination); // old vs current
      // see if we collide with existing forces of ours
	  if (destination.x)
	  {
          fix = NoConflictWhere(vlUnit,destination);
		  if (!SameSPoint(fix,destination)) 
		  {
				oldd = 1000; // force us to go to new location
				destination = fix;
		  }
	  }

      // if destination changes  enough tiles from our prior destination
      // then recalculate to  new one
	  BOOL reset=FALSE;
	   if (!pUnit->focusLocation.x ) reset = TRUE;
	  else if (ITEM_TYPE(pUnit->focusItem) == ARMY_VEHICLE && pUnit->order == UNIT_FOLLOW)
	  {
		  // dont track our vehicles so closely
		  // randonly decide to match to spread out unit work
		  if (oldd  > (24 * 16)) reset = ((rand() & 0x0f) == 1 );
	  }
 	  else  if (oldd > (8*16) ) reset = ((rand() & 0x0f) == 1 );

	  if (reset)
	  {
		  pUnit->focusLocation = destination;
          pUnit->focusTile = ENCODE_IPOINT(destination.x,destination.y);
	  }

      // if we are within 4 tiles of final actual goal against an enemy
      // rest and just shoot
      d = GetDistance(&destination,&pUnit->common.position);
      if (d <= 63 && ITEM_ARMY(pUnit) != ITEM_ARMY(pUnit->focusItem)) 
		  return pUnit->common.position;


      // so this is where we are going now
      destination = pUnit->focusLocation;

      // object died, change to defend where you are
      // or lost visibility, switch to attack or defend where you are
      if (pUnit->focusItem->nStrength == 0 ||
          !ItemVisible(ITEM_ARMY(pUnit),pUnit->focusItem))
      {
          if (scriptDebug)
          {
              TRACE("    %s lost chase, staying put\n",ItemDBName(pUnit));
          }
          // a unit on attack reverts to attack going to new location
          pUnit->focusItem = NULL;
          pUnit->focusArrived = FALSE;
          destination = OFF_THE_MAP;

          // a unit on follow reverts to specified atmode (defend is default)
          if (pUnit->order == UNIT_FOLLOW)
          {
              pUnit->sendYourEvent = TRUE;

              if (pUnit->order == UNIT_FOLLOW)
                  UnitFullOrders(pUnit,UNIT_DEFEND,pUnit->common.position,
                      NULL,FAST_SPEED, DEFENDFIRE,pUnit->poststationBehavior,
                      EVENT_NUM_UNDEFINED,0);
          }
      }

      return destination;
}

///========================================================================
//	Function:		UnitDoEvent
//	Description:	Process completion event if any
///========================================================================

static void UnitDoEvent(UNIT* pUnit) // non-zero return is abort
 {
      int event = pUnit->arrivalEvent;
      // notify just once
      pUnit->arrivalEvent = EVENT_NUM_UNDEFINED;

      // send event notification
      if (event == -3) // auto control on
      {
          --pUnit->npc;
		  if( (!curselectedunit) && (pUnit->npc == 0) )
			curselectedunit = UnitGetNextFunctional( NULL );
      }
      else if (event != EVENT_NUM_UNDEFINED)
      {
          EventTrigger((EVENT_TYPE)pUnit->eventtype,event,
                      ITEM_UID(pUnit),0,0);
      }
  }

///========================================================================
//	Function:		UnitUpdateDestination
//	Description:	Selection location to goto for this unit
///========================================================================

static void UnitUpdateDestination(UNIT* pUnit)
{
      SPOINT destination;
      ITEM* focusItem = pUnit->focusItem;

      // consider prestation routing (never arrived on station)
      if (!pUnit->focusArrived)
      {	
          if (pUnit->prestationBehavior == EVADEFIRE && pUnit->pTarget)
          {
              destination = EvadeTarget(pUnit);
              if (destination.x) goto exit;
          }      

          // if we have a lockedon target, go to it
          if (pUnit->focusItem)
          {
              destination = ChaseTarget(pUnit);
          }
      
          // if we have a pre-station location to handle...
          else if (pUnit->focusLocation.x)
          {
              destination =  pUnit->focusLocation;
      
              // if we have just arrived
              if (pUnit->common.tile  == pUnit->focusTile)
              {
                  if (scriptDebug)
                  {
                      TRACE("    %s arrives at station\n",ItemDBName(pUnit));
                  }
                  if (pUnit->npc == 0 && ITEM_ARMY(pUnit) == ARMY_PLAYER) 
					  SitRep(ARMY_REACHED,(ITEM*)pUnit);
                  pUnit->focusArrived = TRUE;
                  pUnit->sendYourEvent = TRUE;
              }        
          }
      } // end of prestation behavior

      // now handle post-station behavior
      if (pUnit->focusArrived)
      {
          if (pUnit->order ==  UNIT_FOLLOW)
          {
              pUnit->focusArrived = FALSE;
              pUnit->mode = UNIT_STILL;
          }

          switch (pUnit->poststationBehavior)
          {
            case EVADEFIRE:
                // go after focus target
                if (pUnit->pTarget) 
				{
					destination = EvadeTarget(pUnit);
				}
                else
                  {
                      pUnit->mode = UNIT_STILL;
                      destination = UnitDefendDestination(pUnit);
                  }
                break;
            case ATTACKFIRE: // we may chase something
                // go after focus target
                if (pUnit->focusItem) 
				{
					destination = ChaseTarget(pUnit);
				}
                // otherwise patrol area
                else destination = UnitAttackDestination(pUnit);

                if (SameSPoint(pUnit->common.position,destination))
                      pUnit->mode = UNIT_STILL;
                else pUnit->routeData.arrived = 0; // try again to get there
                break;

            default: 
                destination = UnitDefendDestination(pUnit);
                if (pUnit->common.tile ==
                  ENCODE_IPOINT(destination.x,destination.y))
                      pUnit->mode = UNIT_STILL;
                else pUnit->routeData.arrived = 0; // try again to get there
                break;
          }
      }

exit:
      // now do general route planning knowing our destination
	pUnit->destination = destination;
      
      // make sure we have routing data to current or new destination
    AIRouter(destination,&pUnit->routeData,
          UNIT_ROUTE|COLLAPSE,pUnit->common.position,pUnit->common.facing);
    // just arrives now? or cant plan to goal (from blocked?)
    if (!pUnit->routeData.waypoint.x) 
	{
		pUnit->mode = UNIT_STILL;
		if (!pUnit->routeData.arrived) 
		{
			// set delay notification
			if (!pUnit->delayFailed) pUnit->delayFailed = gpGame->dwSysTime + 3000;
		}
    }
}


///========================================================================
//	Function:		UnitsUpdateDestinations
//	Description:	Selection locations to goto for all units
///========================================================================

static void UnitsUpdateDestinations() // decide where units should go (MOVING)
{
    // This computes the waypoint result for the unit, using routeplanning.

    // Units that have targets will move toward them first (until engaged)
    // Otherwise they will move toward their focus, or if they
    // have reached their focus, they may wander around near it.

      UNIT* pUnit;
      int eArmy;
      LEGION* pLegion;
      FOR_EACH_LOCAL_ARMY(eArmy)
      { 
          pLegion = ArmyGetLegion(eArmy);
          FOR_EACH_UNIT(pLegion,pUnit)
          {
			// finish delayed event trigger
			if (pUnit->delayFailed && pUnit->delayFailed < gpGame->dwSysTime)
			{
				pUnit->delayFailed = 0;
				pUnit->sendYourEvent = TRUE;
			}


              if (!UNIT_IN_OPEN(pUnit)) 
				  continue; 
              // if engaged, unit does nothing, troopers to all.
              if (UNIT_ENGAGED(pUnit)) 
              {
                  eunit = pUnit;	// just for debugging
				  continue;
              }

              if (UNIT_IN_VEHICLE(pUnit)) 
				  continue;
      
              UnitUpdateDestination(pUnit);
          }
      }
}

///========================================================================
//	Function:		UnitHandleTarget
//	Description:	decide how to label current state with target
///========================================================================

static void UnitHandleTarget(UNIT* pUnit, ITEM* pTarget)
{
      pUnit->pTarget = pTarget;

      // tell user we are seeing him
      if (pUnit->lastSitrep != pTarget && pUnit->npc == 0 && ITEM_ARMY(pUnit) == ARMY_PLAYER)
      {
          pUnit->lastSitrep = pTarget;
          SitRep(ARMY_APPROACH,(ITEM*)pUnit);
      }

      // if on station in attack mode, go after him
      if (IS_POSTSTATION(pUnit) && pUnit->poststationBehavior == ATTACKFIRE)
      {
          pUnit->focusItem = pTarget;		// success
      }
}


//========================================================================
//	Function:		AssetFight
//	Description:	asset decides to fire or not
///========================================================================
void AssetFight(OBJECT* pAsset){

      WEAPON* pWeapon = pAsset->common.pWeapon;
	  if( !(pAsset->common.pWeapon) )			// non-firing asset
		  return;							
      if (pAsset->common.nStrength == 0) return; // dead asset
	  if (immobileFoe) return; 
      WeaponFireUpdate(pWeapon);

      // do not fire during game-setup state
	  if( gpGame->game_substate == PLAY_SETUP_SUB_STATE )
		  return;
      // he is out of ammo 
      if (pWeapon->nAmmo == 0) return;

      // he is recycling and not ready to fire
      if (!WeaponFireTime(pWeapon)) return;
      WEAPON_TYPE eWeapon = pWeapon->eWeapon;

      // there is no one to attack
      TAD* pTad;
      ITEM* pVictim;
      pTad = TadCurrentTarget( (ITEM*)pAsset);
      pVictim = (ITEM*) ((pTad) ? pTad->pItem : NULL);
      if (!pVictim)  return;

      // he is out of range, bad los or friends in way
      BOOL bCanShoot;
      bCanShoot = CanShoot(pWeapon,(ITEM*)pAsset,pVictim->tile);

	  // if our LOS is bad, too bad
      if (bCanShoot <= 0) return;

      WeaponFireReset(pWeapon);
 //     pWeapon->nAmmo--;		// assets have infinite ammo
      AssetFireWeapon( pAsset, pVictim );
}


//========================================================================
//	Function:		UnitsUpdateTargets
//	Description:	update the unit target information.
///========================================================================
static void UnitsUpdateTargets()
{
	int			eArmy;
    UNIT		*pUnit;
    TAD			*pTad;
    ITEM		*pTarget;
    LEGION		*pLegion;
	DWORD		dwAnimTime = gpGame->dwAnimTime;

    // change target of each unit and set lockon status
    // By the time we leave here, unit should know if it has a target
    // and whether it should chase it around or not (locked on).
        
    // Have tad assign targets for all units under AI control.
    // This includes player on this machine and ai on this machine.
    // This does not include remote players.
	FOR_EACH_LOCAL_ARMY( eArmy )
    {
      TadTargetAcquisition( (ARMY_TYPE)eArmy );
    }
	TadRestore();
     
    UnitValidateTad();						// prove tad is sound now.

    // process each unit target
    FOR_EACH_LOCAL_ARMY(eArmy)
    { 
		pLegion = ArmyGetLegion(eArmy);
		FOR_EACH_UNIT(pLegion,pUnit)
		{

#ifdef DEBUG
			// BUG -- TESTING FOR MISSING AVATAR
			if (UNIT_ON_MAP(pUnit))
			{
				TROOPER		*pTrooper;
				int i;
				FOR_EACH_TROOPER(pUnit, pTrooper, i)	
				{
					ASSERT(pTrooper->pAvatar);
				}
			}
#endif

			if (!UNIT_IN_OPEN(pUnit)) continue; // not moving/engaged/still      

			pTad = TadCurrentTarget( (ITEM*)pUnit);
			pTarget = (pTad) ? pTad->pItem : NULL;

            if (!pTarget)
                  pUnit->pTarget = NULL;
            else if (pTarget->nStrength == 0)
                  pUnit->pTarget = NULL;
            else  // a good and valid target
			{
				UnitValidateTad();			// prove tad is sound now.
				UnitHandleTarget(pUnit,pTarget);
				UnitValidateTad();			// prove tad is sound now.
			}
		}

		for( int i = 0; i < pLegion->nAssets; i++ )
		{
			OBJECTSTRUCT	*pAsset;
			pAsset = pLegion->AssetList[i];
            AssetFight(pAsset);
		}
	}
}


//========================================================================
//	Function:		UnitsValidateAnims
//	Description:	validate the anims for all troopers of all units
///========================================================================
static void UnitsValidateAnims()
{
#ifdef _DEBUG
	int eType;

    FOR_EACH_TROOPER_TYPE(eType)
	{
		if (TrooperCommands[eType])	{
			ValidateCommandList(TrooperCommands[eType]);
		}
	}
#endif
}

//========================================================================
//	Function:		UnitsUpdateDeath
//	Description:	units without troopers must die &&
//					Units that are dying can no longer be focus of order
//					And Units entering vehicles done now (keeps tad clean)
///========================================================================

static void UnitsUpdateDeath() 
{
    int 		eArmy;
    LEGION* 	pLegion;
    int			i;
    BOOL		bHasLivingTrooper;
    BOOL		bVisible;
    UNIT* 		pUnit;
    TROOPER* 	pTrooper;
    SARGE*		pSarge;

    FOR_EACH_DEPLOYED_ARMY(eArmy)
    { 
      pLegion = ArmyGetLegion(eArmy);
      pSarge = SargePointer(eArmy);
      FOR_EACH_UNIT(pLegion,pUnit)
      {
          if (!UNIT_ON_MAP(pUnit)) continue;

          // if focus item is dead, drop focus item and use unit location
          if (pUnit->focusItem && pUnit->focusItem->nStrength == 0)
          {
              pUnit->focusItem = NULL;
              pUnit->focusLocation = pUnit->common.position;

              if (pUnit->order == UNIT_FOLLOW)
              {
                  pUnit->sendYourEvent = TRUE;
                  UnitFullOrders(pUnit,UNIT_DEFEND,pUnit->common.position,
                      NULL,FAST_SPEED, DEFENDFIRE,pUnit->poststationBehavior,
                      EVENT_NUM_UNDEFINED,0);
              }
          }


          bVisible = ItemUserVisible(ARMY_PLAYER, pUnit);
          bHasLivingTrooper = FALSE;

          // consider status of each trooper in unit
          FOR_EACH_TROOPER(pUnit,pTrooper,i)
            {
                  // clean up troopers who were shot to death this frame
                  if (IS_LOCAL_ITEM(pTrooper) && !TROOPER_HEALTHY(pTrooper) &&
                      pTrooper->mode != TROOPER_DYING)
                      TrooperKill(pTrooper);

                  // since one trooper is good, the unit is good and
                  // should remain in tad
                  if (TROOPER_HEALTHY(pTrooper))
                      bHasLivingTrooper = TRUE;
      
                  // if the unit is visible, all of its troopers are visible
                  // unless explicitly hiding
                  if (bVisible && pUnit->beInvisible == 0)
                      ITEM_SET_VISIBLE((ITEM *) pTrooper);
                  else
                      ITEM_SET_INVISIBLE((ITEM *) pTrooper);
            }
          
            // if unit has no living troopers, remove its tad 
            if (!bHasLivingTrooper)
            {
                  UnitFreeTad(pUnit);
				  pUnit->focusItem = NULL;
                  pUnit->focusLocation = pUnit->common.position;
                  if (pUnit->order == UNIT_FOLLOW) pUnit->order = UNIT_DEFEND;
            }

          VEHICLE* pVehicle = NULL;
		  if ( !(pUnit->focusItem) ) ;
		  else if (ITEM_TYPE(pUnit->focusItem) == ARMY_VEHICLE) pVehicle = (VEHICLE*)pUnit->focusItem;
		  else if (ITEM_TYPE(pUnit->focusItem) == ARMY_SARGE) pVehicle = pSarge->pVehicle;
          
          // clean up units whose last trooper died out completely this frame
          // units have no messages across the net to consider
          if (pUnit->nLastTroop == -1 && pUnit->mode != UNIT_DEAD)
              UnitKill(pUnit);

          // if unit follows sarge in a vehicle or follows a vehicle
          // and gets close
          // it might jump on board if it is close and vehicle is
          // stationary and some trooper is still alive
          else if (IS_LOCAL_ITEM(pUnit) &&
                   pUnit->mode != UNIT_IN_VEHICLE &&
			       pUnit->order == UNIT_FOLLOW && pVehicle &&
                   pVehicle->full_velocity == 0 &&
                   pUnit->common.nStrength)
          {
              if (!VehicleEnterable(pVehicle));
              else if (TileDistance(pVehicle->common.tile,pUnit->common.tile) < 8)
			  {
				UnitEnterVehicle(pUnit,pVehicle);
				return;
			  }
          }

         // if unit has triggered an arrival event and still exists on map
         // now you can safely launch the event (which might undeploy unit)
         if (pUnit->sendYourEvent && pUnit->common.nStrength && pUnit->common.tile)
         {
              pUnit->sendYourEvent = 0;
              UnitDoEvent(pUnit);
         }
         else pUnit->sendYourEvent = 0; // in case it had one pending and died
		}
    }
}

static void UnitsFinishTroopers()
{
    UNIT* pUnit;
    int eArmy;
    LEGION* pLegion;

    // update local and remote armies (remote data is in by now)
    FOR_EACH_DEPLOYED_ARMY(eArmy)
    {	
      pLegion = ArmyGetLegion(eArmy);
      FOR_EACH_UNIT(pLegion,pUnit)
      {
          if (!UNIT_ON_MAP(pUnit)) continue;
          if (UNIT_IN_VEHICLE(pUnit))   continue;

          // do the avatar thing from the pending command
          TroopersUpdateAvatars(pUnit);

          // The unit updates after the troopers have done theirs.
          UnitUpdatePosition(pUnit);
      }
    }
}

//========================================================================
//	Function:		UnitsUpdateMovement
//	Description:	make all units move or fight from this machine.
///========================================================================

static void UnitsUpdateMovement() 
{
    UNIT* pUnit;
    int eArmy;
    LEGION* pLegion;

	// Perform movement intentions for each LOCAL unit (set up the avatars)
	FOR_EACH_LOCAL_ARMY(eArmy)
    { 
      pLegion = ArmyGetLegion(eArmy);
      FOR_EACH_UNIT(pLegion,pUnit)
      {
        if (!UNIT_ON_MAP(pUnit)) continue;

        // guys who are invisible must remain invisible until changed
        if (pUnit->beInvisible == TRUE)
        {
          continue;
        }
        else if (immobileFoe && eArmy != ARMY_PLAYER)
        {
          SPOINT point;
          // face best target, even though not fighting
          if (pUnit->pTarget) point = pUnit->pTarget->position;
          else point = OFF_THE_MAP;
          TroopersStill(pUnit,&point); 	
        }

          // still units must face incoming attackers
        else if (UNIT_STILL(pUnit) || pUnit->mode == UNIT_DYING)
        {
          SPOINT point;
          // face best target, even though not fighting
          if (pUnit->pTarget) point = pUnit->pTarget->position;
          else point = OFF_THE_MAP;
          TroopersStill(pUnit,&point); 	
        }

        // moving units transit from place to place (setup)
        else if (UNIT_MOVING(pUnit))
        {
          SPOINT to = pUnit->routeData.waypoint;
          TroopersMove(pUnit,to); // move the leader (followers follow)
        }

        // engaged units have the troopers fight at will (move/fire setup)
        else if (UNIT_ENGAGED(pUnit))
        {
          TroopersFight(pUnit);
        }
      }
    }


    // REMOTE troopers will have sent update messages if they changed
    UnitsFinishTroopers();
}


///========================================================================
//	Function:		UnitsSeeAllUnits
//	Description:	determine who sees whom from this machine and mark them 
///========================================================================

static int EnemySees(ITEM* pItem)
{  
	int		eArmy;
	FOR_EACH_DEPLOYED_ARMY(eArmy)
    {      
      if (eArmy == ITEM_ARMY(pItem)) continue; // ignore own army
      if (ItemVisible(eArmy,pItem)) return TRUE;
    }
    return FALSE;
}

static void MarkForceSeen(){
    // this is good really only for single-player stuff

	int		eArmy,i;
	LEGION	*pLegion;
    SARGE*  pSarge;
	UNIT	*pUnit;
    VEHICLE* pVehicle;
      
	FOR_EACH_LOCAL_ARMY(eArmy)
	{
		pLegion = ArmyGetLegion(eArmy);

        // do sarge
        pSarge = SargePointer(eArmy);
        pSarge->common.seentemp = EnemySees((ITEM*)pSarge);

        // do units
		FOR_EACH_UNIT(pLegion,pUnit)
		{
          pUnit->common.seentemp = EnemySees((ITEM*)pUnit);
		}  

        // do vehicles
        FOR_EACH_VEHICLE(pLegion,i)
        {
          pVehicle = pLegion->pLegionVehicles[i];
          pVehicle->common.seentemp = EnemySees((ITEM*)pVehicle);
        }

        // do assets
		for(i = 0; i < pLegion->nAssets; i++ )
		{
			OBJECTSTRUCT *pObject;

			pObject = pLegion->AssetList[i];
            pObject->common.seentemp = EnemySees((ITEM*)pObject);
		}
	}
}

static void TriggerUnseenEvents(){
    // this is good really only for single-player stuff

	int		eArmy,i;
	LEGION	*pLegion;
    SARGE*  pSarge;
	UNIT	*pUnit;
    VEHICLE* pVehicle;
    int seentemp;
      
	FOR_EACH_LOCAL_ARMY(eArmy)
	{
		pLegion = ArmyGetLegion(eArmy);

        // do sarge
        pSarge = SargePointer(eArmy);
        seentemp = EnemySees((ITEM*)pSarge);
        if (pSarge->common.seentemp == 0 && seentemp && pSarge->common.nStrength)
              EventTrigger(EVENT_ITEMVISOFF,pSarge->common.eventNum,0,0,0);

        // do units
		FOR_EACH_UNIT(pLegion,pUnit)
		{
          seentemp = EnemySees((ITEM*)pUnit);
          if (pUnit->common.seentemp == 0 && seentemp && pUnit->common.nStrength)
              EventTrigger(EVENT_ITEMVISOFF,pUnit->common.eventNum,0,0,0);
		}  

        // do vehicles
        FOR_EACH_VEHICLE(pLegion,i)
        {
          pVehicle = pLegion->pLegionVehicles[i];
          seentemp = EnemySees((ITEM*)pVehicle);
          if (pVehicle->common.seentemp == 0 && seentemp && pVehicle->common.nStrength)
              EventTrigger(EVENT_ITEMVISOFF,pVehicle->common.eventNum,0,0,0);
		}  

        // do assets
		for(i = 0; i < pLegion->nAssets; i++ )
		{
			OBJECTSTRUCT *pObject;

			pObject = pLegion->AssetList[i];
			seentemp = EnemySees((ITEM*)pObject);
            if (pObject->common.seentemp == 0 && seentemp && pVehicle->common.nStrength)
               EventTrigger(EVENT_ITEMVISOFF,pObject->common.eventNum,0,0,0);
		}
	}
}


static void UnitsSeeAllUnits()
{
	int		eArmy,eFoeArmy,i;
	LEGION	*pLegion;
    SARGE*  pSarge;
	UNIT	*pUnit;
    VEHICLE* pVehicle;

    MarkForceSeen(); // set seen state of all forces

      
	// For each army controlled by this machine, determine who it sees
	// We dont need to know who sees us from remote machines.
	// Note that viewing is not symmetric. If you see me, I may not see you.
	FOR_EACH_LOCAL_ARMY(eArmy)
	{
 		pLegion = ArmyGetLegion(eArmy);

        // do sarge
        pSarge = SargePointer(eArmy);
        if (pSarge->common.tile)
        {
          FOR_EACH_DEPLOYED_ARMY(eFoeArmy)
          {
			  if( Armies[eFoeArmy].Status == 0 )
				  continue;
              if (eFoeArmy == eArmy) continue;
              ItemSeesArmy((ITEM*)pSarge,(ARMY_TYPE)eFoeArmy);
          }      
        }

        // do units
		FOR_EACH_UNIT(pLegion,pUnit)
		{
			if (!UNIT_ON_MAP(pUnit)) 
				continue;					// he cant see anything
			if (UNIT_IN_VEHICLE(pUnit)) 
				continue;
			FOR_EACH_DEPLOYED_ARMY(eFoeArmy)			// what does he see of each foe
			{
				if (eFoeArmy == eArmy)
					continue;				// we know us
				ItemSeesArmy((ITEM*)pUnit,(ARMY_TYPE)eFoeArmy);
			}
		}  

        // do vehicles
        FOR_EACH_VEHICLE(pLegion,i)
        {
          pVehicle = pLegion->pLegionVehicles[i];
          if (pVehicle->state != VEHICLE_DEPLOYED) continue;
          if (!pVehicle->common.tile) continue;
          FOR_EACH_DEPLOYED_ARMY(eFoeArmy)
          {
              if (eFoeArmy == eArmy) continue; // we know us
              ItemSeesArmy((ITEM*)pVehicle,(ARMY_TYPE)eFoeArmy);
          }
        }

        // do assets
		for(i = 0; i < pLegion->nAssets; i++ )
		{
			OBJECTSTRUCT *pObject;

			pObject = pLegion->AssetList[i];
			if (pObject->common.pTad == NULL) continue; // not occupied to be shot at

			FOR_EACH_DEPLOYED_ARMY(eFoeArmy)
			{
				if (eFoeArmy == eArmy)
					continue;				// we know us
				ItemSeesArmy( (ITEM *)pObject, (ARMY_TYPE)eFoeArmy );
			}
		}
	}

    TriggerUnseenEvents();
}

///========================================================================
//	Function:		ItemClosestWhere
//	Description:	Find a legal point for to walk to on way to where
///========================================================================

SPOINT ItemClosestWhere(ITEM* pItem,SPOINT to)
{
   ROUTEDATA routeData;
    routeData.owner = ITEM_UID(pItem); // set owner of this data
    routeData.destination = OFF_THE_MAP;

      // staying put
 	if (ENCODE_IPOINT(to.x,to.y) == pItem->tile) return to;
    IPOINT myLine[3000];
    if (!UntrafficableUnit(ENCODE_IPOINT(to.x,to.y))) return to;
    TileLegalLine(pItem->tile,ENCODE_IPOINT(to.x,to.y),myLine);


    int n = myLine[0];
    while (n)
    {
          to = CenterPointFromTile(myLine[n]);
          if (!UntrafficableUnit(ENCODE_IPOINT(to.x,to.y))) return to;
          --n;
      }

	  return to;
}


///========================================================================
//	Function:		UnitValidateTad
//	Description:	prove no tad now points to this unit
///========================================================================

// DEBUGGING ONLY 

void UnitValidateTad()
{
}

///========================================================================
//	Function:		UnitViewDraw
//	Description:	mark the view radius of a unit
///========================================================================
static long UnitMarkView(IPOINT at)
{
    if (CanSeeFromItem(currentItemProp,at)) return 0;
#ifndef FINAL
    if (the_map.debug_layer[at] == 'h')
        the_map.debug_layer[at] = '*'; 	// see and shoot
    else 
        the_map.debug_layer[at] = 'v';  // just see, not shoot
#endif
	return 0;
}
    
void UnitViewDraw(UNIT* pUnit)
{
    SARGE* pSarge = SargePointer(ARMY_PLAYER);
    if (!pUnit)
    {
        pUnit = (UNIT*) pSarge; // lie just for the raw common data
    }
    else
    {
        // undeployed? or dead
        if (!pUnit->common.tile) return;
    }
    currentItemProp = (ITEM*)pUnit;
    ItemFanOut((ITEM*)pUnit,pUnit->common.tile,visibilityRange,UnitMarkView);
#ifndef FINAL
	the_map.debug_layer[pUnit->common.tile] = '?'; 
    DisplayDebugLayer(RGB_YELLOW);
#endif
}

///========================================================================
//	Function:		UnitFireAllDraw
//	Description:	mark the fire ability around a unit
///========================================================================
static int xMinRange,xRange,xPartRange;
static int xSee;

static long UnitMarkFireView(IPOINT at)
{
    int n = TileDistance(currentItemProp->tile,at) << 4;
	if (n > xRange) return 0;
	if (n < xMinRange) return 0;
    if (xSee && !CanSeeFromItem(currentItemProp,at)) return 0;
#ifndef FINAL
    if (n > xPartRange)
        the_map.debug_layer[at] = '.'; 	// shooting past 70% range
    else if (the_map.debug_layer[at] == 'v')
        the_map.debug_layer[at] = '*'; 	// see and shoot
    else 
        the_map.debug_layer[at] = 'h';  // just shoot, not see
#endif
	return 0;
}
    
void UnitFireAllDraw(UNIT* pUnit)
{
    SARGE* pSarge = SargePointer(ARMY_PLAYER);
    if (!pUnit)
    {
        xRange = AiObjectFiringRange((ITEM*)pSarge);
        xPartRange = (xRange * 7) / 10;
        xMinRange = WeaponMinRange(pSarge->common.pWeapon->eWeapon);
        xSee = (pSarge->common.pWeapon->eWeapon != ARMY_GRENADE &&
                pSarge->common.pWeapon->eWeapon != ARMY_MORTAR);
        pUnit = (UNIT*) pSarge; // lie just for the raw data
    }
    else
    {
		if (!pUnit->common.tile) return;
        xRange = UnitFiringRange(pUnit);
        xPartRange = (xRange * 7) / 10;
        xMinRange = UnitMinFiringRange(pUnit);
        xSee = (THE_LEADER(pUnit)->common.pWeapon->eWeapon != ARMY_GRENADE &&
                THE_LEADER(pUnit)->common.pWeapon->eWeapon != ARMY_MORTAR);
    }
    currentItemProp = (ITEM*) pUnit;
    ItemFanOut((ITEM*)pUnit,pUnit->common.tile,xRange >> 4,UnitMarkFireView);
#ifndef FINAL
	the_map.debug_layer[pUnit->common.tile] = '?'; 
    DisplayDebugLayer(RGB_YELLOW);
#endif
}

///========================================================================
//	Function:		UnitSnakePoint
//	Description:	Find open tile nearest me behind some guy in front of me
///========================================================================

static SPOINT Tile8[] = 
{
  {0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1}
};

static SPOINT Tile24[] = 
{
  {-2,-2},{-2,-1},{-2,0},{-2,1},{-2,2},
  {-1,-2},{-1,-1},{-1,0},{-1,1},{-1,2},
  {0,-2},{0,-1},{0,1},{0,2},
  {1,-2},{1,-1},{1,0},{1,1},{1,2},
  {2,-2},{2,-1},{2,0},{2,1},{2,2}
};

static SPOINT UnitSnakePoint(SPOINT where) 
{
    IPOINT 			at, spot, maplist[1000];
    int			n = 0, index,i;
    spot = ENCODE_IPOINT(where.x,where.y);
    maplist[n] = spot;
    ASSERT(spot >= 0 && spot < gridmax);        
    privateMap[spot] |= UNIT_PRIVATE_PROPOGATED;

    // propgate outward from this point til find ok point
    for (index = 0; index <= n; ++index)
    {
        at = maplist[index];	// this tile doesnt work
        for (i = 0; i <= 7; ++i)
        {
            spot = at + Tile8[i].x + INDEX_ENCODED_Y(Tile8[i].y);
            if (privateMap[spot] & UNIT_PRIVATE_PROPOGATED) continue;
            if (UntrafficableUnit(spot)) continue;
            if (privateMap[spot] & UNIT_PRIVATE_HERE_NOW){
                ASSERT(spot >= 0 && spot < gridmax);        
                // try searching from here later
                privateMap[spot] |= UNIT_PRIVATE_PROPOGATED;
                maplist[++n] = spot;	
                continue;
            }
            // its ok to use this spot
            index = 2000;	// force end to next loop as well
            break;
        }
    }

    // clear our markers
    for (index = 0; index <= n; ++index)
    {
        ASSERT(maplist[index] >= 0 && maplist[index] < gridmax);        
         privateMap[maplist[index]] &= -1 ^ UNIT_PRIVATE_PROPOGATED;
    }
    SPOINT ans;
    ans = CenterPointFromTile(spot);
	return ans;
}

///========================================================================
//	Function:		NoConflictWhere
//	Description:	see that unit doesnt go to goal of another
///========================================================================
static long NoUnit(IPOINT tile)
{
	if (privateMap[tile] & UNIT_PRIVATE_HERE_NOW) return 0;
	if (UntrafficableUnit(tile)) return 0;
	return tile;
}

static SPOINT NoConflictWhere(UNIT* pOrderUnit,SPOINT where)
{
    IPOINT tile = ENCODE_IPOINT(where.x,where.y),spot,at,standing;
    int eArmy = ITEM_ARMY(pOrderUnit);
    LEGION* pLegion = ArmyGetLegion(eArmy);
	privateMap = pLegion->pUnitPrivateData;					// temp global
    SARGE* pSarge;
    ASSERT(privateMap);        
    int i;
    UNIT* pUnit;
    pSarge = SargePointer(eArmy);
    if (pSarge) 
        privateMap[pSarge->common.tile] |= UNIT_PRIVATE_HERE_NOW;

    // turn on markers of where units are going, or where they are now
	FOR_EACH_UNIT(pLegion,pUnit)
    {
        if (!UNIT_ON_MAP(pUnit)) continue;	
        if (UNIT_IN_VEHICLE(pUnit)) continue;
        if (pOrderUnit == pUnit) break; // ignore self. only concern earliers

        at = pUnit->focusTile;
		if (pUnit->focusItem) at = pUnit->focusItem->tile;//item being tracked
        if (!at) continue; // no place for it
            
        // mark center
        ASSERT(at > 0 && at < gridmax);
		if (at <= 0 || at >= gridmax) continue;

        privateMap[at] |= UNIT_PRIVATE_HERE_NOW;
		standing = pUnit->common.tile;
        privateMap[standing] |= UNIT_PRIVATE_HERE_NOW;

        // mark all of block as well
        for (i = 0; i <= 23; ++i)
        {
            spot = at + Tile24[i].x + INDEX_ENCODED_Y(Tile24[i].y);
            ASSERT(spot >= 0 && spot < gridmax);
            privateMap[spot] |= UNIT_PRIVATE_HERE_NOW;          
			spot = standing + Tile24[i].x + INDEX_ENCODED_Y(Tile24[i].y);
            ASSERT(spot >= 0 && spot < gridmax);
            privateMap[spot] |= UNIT_PRIVATE_HERE_NOW;

        }
    }

    // are we going to another units request
    if (privateMap[tile] & UNIT_PRIVATE_HERE_NOW)
    {
        // we need to go nearby...
        where = CenterPointFromTile((IPOINT)PropogateTrafficable(NULL,tile,10,NoUnit));
    }


    // turn off markers of where units are
	FOR_EACH_UNIT(pLegion,pUnit)
    {
        if (!UNIT_ON_MAP(pUnit)) continue;	
        if (UNIT_IN_VEHICLE(pUnit)) continue;
        if (pOrderUnit == pUnit) break; // ignore self
        at = pUnit->focusTile;
		if (pUnit->focusItem) at = pUnit->focusItem->tile;
        if (!at) continue;
        
        // unmark center
        ASSERT(at > 0 && at < gridmax);            
		if (at <= 0 || at >= gridmax) continue;
        privateMap[at] &= -1 ^ UNIT_PRIVATE_HERE_NOW;
		standing = pUnit->common.tile;
        privateMap[standing] &= -1 ^ UNIT_PRIVATE_HERE_NOW;

        // unmark all of block as well
        for (i = 0; i <= 23; ++i)
        {
            spot = at + Tile24[i].x + INDEX_ENCODED_Y(Tile24[i].y);
            ASSERT(spot >= 0 && spot < gridmax);
            privateMap[spot] &= -1 ^ UNIT_PRIVATE_HERE_NOW;
			 spot = standing + Tile24[i].x + INDEX_ENCODED_Y(Tile24[i].y);
            ASSERT(spot >= 0 && spot < gridmax);
            privateMap[spot] &= -1 ^ UNIT_PRIVATE_HERE_NOW;

        }
    }
    if (pSarge) 
            privateMap[pSarge->common.tile] &= -1 ^ UNIT_PRIVATE_HERE_NOW;
        
    return where;
}

///========================================================================
//	Function:		UnitValidateUnit
//	Description:	prove unit seems intact
///========================================================================

void UnitValidateUnit(UNIT* pUnit)
{
    TROOPER* pTrooper;
    int i;
    if (!validate) return;

    if (!UNIT_ON_MAP(pUnit)) return; // its not out there
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
        ASSERT(pTrooper->pUnit == pUnit);
        ASSERT(pTrooper->pAvatar != 0);
    }
}

///========================================================================
//	Function:		IsAIActivated
//	Description:	is item under AI script control?
///========================================================================

static BOOL IsAIActivated(ITEM* pItem)
{
    int eArmy = ITEM_ARMY(pItem);
    if (ITEM_TYPE(pItem) == ARMY_SARGE && ((SARGE*)pItem)->npc)
        return TRUE;
    if (ITEM_TYPE(pItem) == ARMY_UNIT && ((UNIT*)pItem)->npc)
        return TRUE;
    if (ITEM_TYPE(pItem) == ARMY_VEHICLE && ((VEHICLE*)pItem)->npc)
        return TRUE;

    return FALSE;
}

///========================================================================
//	Function:		UnitEnterVehicle
//	Description:	go into a vehicle
///========================================================================

void UnitEnterVehicle(UNIT* pUnit, VEHICLE* pVehicle)
{
	if (pVehicle->common.nStrength == 0)
		goto exit;

    // must wait for all troopers to become stationary before entering
    TROOPER * pTrooper;
	int i;
    FOR_EACH_TROOPER(pUnit,pTrooper,i)
    {
      if (pTrooper->mode == TROOPER_DYING) return; // must wait out death
      if (pTrooper->action == AVATAR_RUN) return; // was running
      if (pTrooper->action == AVATAR_WALK) return; // was walking
      if (pTrooper->action == AVATAR_SHUFFLE) return; // was shuffling
      if (pTrooper->action == AVATAR_FIRE) return; // was firing on the move?
    }

    TRACE("%s enters vehicle\n",ItemDBName(pUnit));

    pUnit->pVehicle = pVehicle;
    // this will cause troopers to disappear
    pUnit->mode = UNIT_IN_VEHICLE; 

    // remove targeting on unit
    UnitFreeTad(pUnit);

	// audioPlay( PICKUPSOUND, SND_SFX_FLAG );

    if (IS_LOCAL_ITEM(pUnit))
        UnitVehicleMessageSend(pUnit,pVehicle, TRUE);

    TroopersInactive(pUnit); // they go invisible

exit:
	
    // signal event done for follow script
    if (pUnit->npc)
    {
      pUnit->sendYourEvent = TRUE;
    }
}

///========================================================================
//	Function:		UnitExitVehicle
//	Description:	exit a vehicle
///========================================================================

void UnitExitVehicle(UNIT* pUnit,SPOINT position,int facing)
{
	VEHICLE* pVehicle;
	pVehicle = pUnit->pVehicle;
	ASSERT(pVehicle);

	ClearVehicleFromVehicleLayer( pVehicle ); // we dont know if it is there
	ReinsertVehicleInVehicleLayer(pVehicle,TRUE); // require vehicle have a mask 
	// when troopers get out, if it wasnt moveing it will also


    TRACE("%s exits vehicle\n",ItemDBName(pUnit));
    if (position.x == 0)
    {
      // exit at safe point to rear
       position = VehicleRear(pVehicle);
    }
	pUnit->mode = UNIT_MOVING;

    // mode is changed and unit is deployed by giving the order
    // this is called after that

	// Deploy the troopers within this unit to different tiles
    UnitDeployTroopers(pUnit,position,facing);
    
	// reinstate unit targeting
    ASSERT(!pUnit->common.pTad);
	TadCreateObject(ITEM_ARMY(pUnit), (int)ARMY_UNIT,(ITEM*)pUnit,TAD_SMART);

    // remove vehicle link
    pUnit->pVehicle = NULL;

	// audioPlay( PICKDROP, SND_SFX_FLAG );
        
    if (IS_LOCAL_ITEM(pUnit))
        UnitVehicleMessageSend(pUnit,pUnit->pVehicle, FALSE);

    TroopersActive(pUnit);
}


///*****************************************************************
///*****************************************************************
//			EXTERNALLY VISIBLE ROUTINES - script routines
///*****************************************************************
///*****************************************************************

      
///========================================================================
//	Function:		ScriptItemLocation
//	Description:	find reference position of an item
///========================================================================
static ITEM* CarriesItem(ITEM* pDropItem)
{ // this does a non-network local drop
	int eArmy;
    SARGE* pSarge;
 	FOR_EACH_ARMY(eArmy)
	{
       pSarge = SargePointer(eArmy);
	  if (!pSarge) continue;

      ITEM* pItem;
      pItem = pSarge->pWeaponItemList[1];
      if (pItem == pDropItem)
			return (ITEM*)pSarge;
      pItem = pSarge->pWeaponItemList[2];
      if (pItem == pDropItem)
  			return (ITEM*)pSarge;
 	}
	return NULL;
}

static SPOINT ScriptLocation(UID destinationItem,SPOINT* position)
{
      SPOINT where;
	  ITEM* pItem = NULL;
	  ITEM* container;

	  if (destinationItem) pItem = AiItemFind(destinationItem);
 
      if (pItem) 
      {

          // use vehicle rear and safe point
		  switch( ITEM_TYPE(pItem) )
		  {
		  case ARMY_VEHICLE:
              where = VehicleRear((VEHICLE*)pItem);
			  break;
		  case ARMY_UNIT:
		  case ARMY_TROOPER:
		  case ARMY_SARGE:
			  where = pItem->position;
			  break;
		  case ARMY_ASSET:
		  case ARMY_STRUCTURE:
		  case ARMY_OBSTACLE:
			  container = CarriesItem(pItem);
			  if (container) 
				  where = ItemCenterPos(container);
			  else 
				  where = ItemCenterPos(pItem);
			  break;
		  case ARMY_HUSK:
			  where = pItem->position;
			  break;
		  }
			// see if we can use dead spot
		  if (!where.x) where = ItemDeadPosition(pItem);

          // if it was never deployed, use its deploy location
          if (!where.x) {
			  ASSERT(where.x != 1);
			  if( ITEM_TYPE(pItem) == ARMY_UNIT )
				  where = ((UNIT*)pItem)->deployPosition;
		  }
       }
      else if (position && position->x)
      {
          where = *position;
      }
	  else where = OFF_THE_MAP;

      // move it to center of tile if on map
      if (where.x) where = CenterPoint(where);
      
      return where;
}

///========================================================================
//	Function:		OrderAll
//	Description:	give detailed order to army
///========================================================================

static void OrderAll(UID namedItem,UNIT_ORDER order,
                 BEHAVIOR inmode, BEHAVIOR arrivalMode,
                 BOOL bSlow,
                 SPOINT* position, UID destinationItem,
                 int eventNumber,int eventtype)
{
      UNIT* pUnit;
      LEGION* pLegion;
      VEHICLE* pVehicle;
      int i;
      int eArmy = 0;
      if (namedItem == UID_BLUE)
          eArmy = gpComm->IndexFromColor((ARMY_COLOR) ARMY_BLUE);
      else if (namedItem == UID_GRAY)
          eArmy = gpComm->IndexFromColor((ARMY_COLOR) ARMY_GRAY);
      else if (namedItem == UID_GREEN)
          eArmy = gpComm->IndexFromColor((ARMY_COLOR) ARMY_GREEN);
      else if (namedItem == UID_TAN)
          eArmy = gpComm->IndexFromColor((ARMY_COLOR) ARMY_TAN);
      pLegion = ArmyGetLegion(eArmy);
      FOR_EACH_UNIT(pLegion,pUnit)
      {
		  if (!pUnit->aiSetup) continue; // not under control
		ScriptOrder(ITEM_UID(pUnit),order,inmode,arrivalMode,bSlow,
                position,destinationItem,eventNumber,eventtype);
      }
      FOR_EACH_VEHICLE(pLegion,i)      
      {
          pVehicle = pLegion->pLegionVehicles[i];
          ScriptOrder(ITEM_UID(pVehicle),order,inmode,arrivalMode,TRUE,
                position,destinationItem,eventNumber,eventtype);
      }
}
///========================================================================
//	Function:		ScriptOrder
//	Description:	give detailed order to unit
///========================================================================

void ScriptOrder(UID namedItem,UNIT_ORDER order,
                 BEHAVIOR inmode, BEHAVIOR arrivalMode,
                 BOOL bSlow,
                 SPOINT* position, UID destinationItem,
                 int eventNumber,int eventtype)
{
   if (scriptDebug) TRACE("Script Order triggered\n");
 
    // if ordering army, do them all
    if (namedItem == UID_BLUE || namedItem == UID_TAN ||
        namedItem == UID_GRAY || namedItem == UID_GREEN)
    {
       OrderAll(namedItem,order,inmode,arrivalMode,bSlow,
                position,destinationItem,eventNumber,eventtype);
      return;
    }

    SPOINT where;
    SPEED eSpeed;
    UNIT* pUnit = NULL;
    VEHICLE* pVehicle = NULL;
	ITEM* pItem = NULL;
    SARGE* pSarge = NULL;
	int eArmy;
	eArmy = EXTRACT_ARMY(namedItem);
	if (Armies[eArmy].Status == 0) return; // army not there
     
    if (OBJTYPE(namedItem) == ARMY_UNIT)
    {
      pUnit = UnitFind(namedItem);
	  pItem = (ITEM*) pUnit;
      if (!pUnit) return;
      if (!IsAIActivated((ITEM*) pUnit))
      {
          if (scriptDebug)
          {
              TRACE("%s- script order refused by user-controlled unit\n",ItemDBName(pUnit));
          }
          return;
      }

      // give this order to all other units merged with him
      // and so forth, transitively to units following him..
      LEGION* pLegion = ArmyGetLegion(ITEM_ARMY(pUnit));
      UNIT* pMergeUnit;
      FOR_EACH_UNIT(pLegion,pMergeUnit)
      {
          if (pMergeUnit->mergedWith == namedItem)
                ScriptOrder(ITEM_UID(pMergeUnit),order,
                  inmode,arrivalMode,bSlow,position, destinationItem,
                  eventNumber,eventtype);
      }

      // if killed, cannot give it order to this unit
      if (!UNIT_ALIVE(pUnit)) return;
      // if not on map, cannot give it order either
      if (!UNIT_ON_MAP(pUnit)) return;
    }
    else if (OBJTYPE(namedItem) == ARMY_SARGE)
    {
      pSarge = SargeFind(namedItem);
	  pItem = (ITEM*) pSarge;
      if (!pSarge) return;
      if (!IsAIActivated((ITEM*) pSarge))
      {
          if (scriptDebug)
          {
              TRACE("%s- script order refused by user-controlled sarge\n",ItemDBName(pSarge));
          }
          return;
      }
      // dead?
      if (pSarge->common.nStrength == 0) return;
      // not on map?
      if (pSarge->common.tile == 0) return;
    }
    else if (OBJTYPE(namedItem) == ARMY_VEHICLE)
    {
      pVehicle = VehicleFind(namedItem);
  	  pItem = (ITEM*) pVehicle;
    if (!pVehicle) return;
      if (!IsAIActivated((ITEM*) pVehicle))
      {
          if (scriptDebug)
          {
              TRACE("%s- script order refused by user-controlled item\n",ItemDBName(pVehicle));
          }
          return;
      }
      // dead?
      if (pVehicle->common.nStrength == 0) return;
      // not on map?
      if (pVehicle->common.tile == 0) return;
    }

    eSpeed =  (bSlow != 0) ? NORMAL_SPEED : FAST_SPEED;

    // convert named items into their location or use location
    where = ScriptLocation(destinationItem,position);
    if (pUnit)
	{
 		// pass 0 if no event number given
		UnitFullOrders(pUnit, UNIT_DEFEND, where, NULL , eSpeed, inmode,
						 arrivalMode,eventNumber,eventtype);
	  if (pUnit->lastOrdered == playCycle && playCycle)
		  TRACE("WARNING- already ordered %s this frame\n",ItemDBName(pUnit));
	  pUnit->lastOrdered = playCycle;


 
	}
    else if (pVehicle)
    {
      if (scriptDebug || vehicleBehavior)
      {
       TRACE("    %s ordered to %d.%d\n",ItemDBName(pVehicle),
            where.x,where.y);
      }
	  if (pVehicle->lastOrdered == playCycle && playCycle)
		  TRACE("WARNING- already ordered %s this frame\n",ItemDBName(pVehicle));
	  pVehicle->lastOrdered = playCycle;
       pVehicle->aiGoal = where;
       pVehicle->imode = inmode;
       pVehicle->atmode = arrivalMode;
       pVehicle->speed = eSpeed;
       pVehicle->arrivalEvent = eventNumber;
	   pVehicle->delayFailed = 0;
       pVehicle->eventtype = eventtype;
		if (!pVehicle->controller)InitControl(pVehicle);
		(( VEHICLE_CONTROLLER*)pVehicle->controller)->routeData.destination = OFF_THE_MAP; // reset router to think of this as new
		(( VEHICLE_CONTROLLER*)pVehicle->controller)->routeData.arrived = 0; // reset router to think of this as new
  
	
	}
    else if (pSarge)
    {
      if (scriptDebug || vehicleBehavior)
      {
       TRACE("    %s ordered to %d.%d\n",ItemDBName(pSarge),
            where.x,where.y);
      }
       pSarge->aiGoal = where;
       pSarge->imode = inmode;
       pSarge->atmode = arrivalMode;
       pSarge->speed = eSpeed;
       pSarge->arrivalEvent = eventNumber;
       pSarge->eventtype = eventtype;
	   pSarge->delayFailed = 0;
  		pSarge->routeData.destination = OFF_THE_MAP; // reset router to think of this as new
		pSarge->routeData.arrived = 0; // reset router to think of this as new

    }

	if (scriptDebug && pItem) // check utility of order for possible bugs
		{
			ROUTEDATA junk;
			SPOINT waypoint;
			junk.destination = OFF_THE_MAP;
			junk.owner = ITEM_UID(pItem);
			if (ITEM_TYPE(pItem) == ARMY_VEHICLE)
				waypoint = AIRouter(where,&junk,TANK_ROUTE|COLLAPSE,pItem->position,pItem->facing);
			else 
				waypoint = AIRouter(where,&junk,UNIT_ROUTE|COLLAPSE,pItem->position,pItem->facing);
			if (waypoint.x == 0 && junk.arrived == 0)
				TRACE("WARNING- %s ordered to %d.%d but no route\n",ItemDBName(pItem),where.x,where.y);
		}
 
}


///========================================================================
//	Function:		ScriptVisible
//	Description:	affect users ability to see unit
///========================================================================

void ScriptVisible(UID namedItem,int seen)
{
	 if (scriptDebug) TRACE("Script visible triggered\n");

	int eArmy;
	eArmy = EXTRACT_ARMY(namedItem);
	if (Armies[eArmy].Status == 0) return; // army not there

    if (OBJTYPE(namedItem) == ARMY_UNIT)
    {	
      UNIT* pUnit;
      pUnit = UnitFind(namedItem);
      if (!pUnit) return;
            // dont affect vis of unit not alive and deployed
      if (!UNIT_ALIVE(pUnit)) return;
      if (UNIT_IN_HQ(pUnit)) return;
      if (!UNIT_ON_MAP(pUnit)) return;

      if (seen) TroopersActive(pUnit);
      else TroopersInactive(pUnit);
    }
    else ASSERT(0);
}

///========================================================================
//	Function:		DeployStatic
//	Description:	place all forces undeployed of this army
///========================================================================
static void DeployStatic(int eArmy)
{
      LEGION* pLegion;
      UNIT* pUnit;
      pLegion = ArmyGetLegion(eArmy);
      FOR_EACH_UNIT(pLegion,pUnit)
      {
          if (!UNIT_IN_HQ(pUnit)) continue;
          if (pUnit->paratrooper) continue;
		  if (pUnit->deployPosition.x < 5)
		  {
			TRACE("%s lacks deployability\n",ItemDBName(pUnit));
			continue;
		  }
		  pUnit->aiSetup = TRUE; // we control this.
          UnitInitialDeploy(pUnit,pUnit->deployPosition,
                            pUnit->deployFacing,ATTACKFIRE,NULL);
          ++pUnit->npc;
      }
      int i;
      VEHICLE* pVehicle;
      FOR_EACH_VEHICLE(pLegion,i)
      {
          pVehicle = pLegion->pLegionVehicles[i];
          if (pVehicle->state != VEHICLE_UNDEPLOYED) continue;
		  if (pVehicle->deployPosition.x < 5)
		  {
			TRACE("%s lacks deployability\n",ItemDBName(pVehicle));
			continue;
		  }

          VehicleInitialDeploy(pVehicle,&pVehicle->deployPosition,
                               pVehicle->deployFacing);
          pVehicle->imode = pVehicle->atmode = ATTACKFIRE;
          pVehicle->speed = NORMAL_SPEED;
          ++pVehicle->npc;
		  pVehicle->aiGoal = pVehicle->common.position;
      }
	  SARGE* pSarge;
	  pSarge = SargePointer(eArmy);
	  if (!pSarge) return;
	  ++pSarge->npc;
	  pSarge->imode = pSarge->atmode = ATTACKFIRE;
	  pSarge->aiGoal = pSarge->common.position;
 
}

///========================================================================
//	Function:		ScriptDeploy
//	Description:	place unit not on map onto map
///========================================================================

void ScriptDeploy(UID namedItem, BEHAVIOR atMode,SPOINT* position,UID locationItem)
{
	 if (scriptDebug) TRACE("Script Deploy triggered\n");

	int index;
    if (namedItem == UID_GREEN)
    {
      index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GREEN);
      DeployStatic(index);
      return;
    }
    if (namedItem == UID_TAN)
    {
      index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_TAN);
      DeployStatic(index);
      return;
    }
    if (namedItem == UID_BLUE)
    {
      index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_BLUE);
      DeployStatic(index);
      return;
    }
    if (namedItem == UID_GRAY)
    {
      index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GRAY);
      DeployStatic(index);
      return;
    }



	  SPOINT where = ScriptLocation(locationItem,position);
	  SPOINT pt;
	  int eArmy;
		eArmy = EXTRACT_ARMY(namedItem);
		if (Armies[eArmy].Status == 0) return; // army not there

	  if (where.x) 
	  {
		pt = where;
	  }
      if (OBJTYPE(namedItem) == ARMY_UNIT)
      {
          UNIT* pUnit;
          pUnit = UnitFind(namedItem);
          if (!pUnit) return;

          // if killed, cannot redeploy it
          if (!UNIT_ALIVE(pUnit)) return;
          if (pUnit->mode != UNIT_IN_HQ) return;
		  if (!where.x) {
			  pt = pUnit->deployPosition;
			  ASSERT(pt.x != 1);
		  }

          UnitInitialDeploy(pUnit,pt,pUnit->deployFacing,atMode);
      }
      if (OBJTYPE(namedItem) == ARMY_VEHICLE)      
      {
          VEHICLE* pVehicle;
          pVehicle = VehicleFind(namedItem);
          if (!pVehicle) return;

          // if dead cannot redeploy it
          if (pVehicle->state != VEHICLE_UNDEPLOYED) return;
      	  if (!where.x) pt = pVehicle->deployPosition;
      
          VehicleInitialDeploy(pVehicle,&pt, pVehicle->deployFacing);
		  pVehicle->imode = atMode;
			pVehicle->atmode = atMode;
  

      }
      if (OBJTYPE(namedItem) == ARMY_SARGE)
      {
          SARGE* pSarge;
          pSarge = SargeFind(namedItem);
          if (!pSarge) return;

		  if (!where.x) pt = pSarge->deployPosition;

          SargeInitialDeploy(pSarge,&pt,pSarge->deployFacing);
		  pSarge->imode = atMode;
			pSarge->atmode = atMode;
      }
}

///========================================================================
//	Function:		ScriptUndeploy
//	Description:	remove unit on map
///========================================================================

static void PrepareDelete(int eArmy)
{
      int aArmy;
      ITEM* pItem;
      SARGE* pSarge;
      OBJECT* pObject;

      // as host make sure all other sarges drop weapons of this army type
      if (gpComm->m_bHost && gpGame->GameType != GAMETYPE_ONEPLAYER)
      {
        FOR_EACH_DEPLOYED_ARMY(aArmy)
        {
          pSarge = SargePointer(aArmy);
          pItem = pSarge->pWeaponItemList[(SARGE_WEAPON)2];
          pObject = (OBJECTSTRUCT*) pItem;
          if (pObject && OBJECT_OWNER(pObject) == eArmy)
          {
              ItemSetLocation(pItem,&pSarge->common.position);
              SargeWantItemMessageSend(pSarge,pItem,DO_DROP,(SARGE_WEAPON)2);
              SargeDropWeapon(pSarge,pSarge->common.position,(SARGE_WEAPON)2);
          }
          pItem = pSarge->pWeaponItemList[(SARGE_WEAPON)1];
          pObject = (OBJECTSTRUCT*) pItem;
          if (pObject && OBJECT_OWNER(pObject) == eArmy)
          {
              ItemSetLocation(pItem,&pSarge->common.position);
              SargeWantItemMessageSend(pSarge,pItem,DO_DROP,(SARGE_WEAPON)1);
              SargeDropWeapon(pSarge,pSarge->common.position,(SARGE_WEAPON)1);
          }
        }
      }

      // sarge of army drops all things he posseses
      pSarge = SargePointer(eArmy);
	  if (pSarge)	{
		  SargeDropWeapon(pSarge,pSarge->common.position,(SARGE_WEAPON)2);
		  SargeDropWeapon(pSarge,pSarge->common.position,(SARGE_WEAPON)1);
	  }

      // army gets deleted
      ArmyDelete(eArmy,TRUE);
}

void ScriptRecharge(UID army,int number)
{   
	if (scriptDebug) TRACE("Script Recharge triggered\n");

      SARGE* pSarge;
      LEGION* pLegion;
      int index;
	  if (Armies[army].Status == 0) return;

      if (army == UID_GREEN)
          index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GREEN);
      else if (army == UID_TAN)
          index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_TAN);
      else if (army == UID_BLUE)
          index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_BLUE);
      else if (army == UID_GRAY)
          index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GRAY);
      else// unacceptable army
      {
          TRACE("unacceptable army\n");
          return;
      }
      
      pLegion = ArmyGetLegion(index);
      pSarge = SargePointer(index);

      // full health
      if (number == 1)
          pSarge->common.nStrength = pSarge->common.nMaxStrength;
      // full strike
      else if (number == 2)
      {
          if (pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE] < 3)
              pLegion->AirResources[ARMY_RESOURCE_AIR_STRIKE] = 3;
      }
      // full recon
      else if (number == 3)
      {
          if (pLegion->AirResources[ARMY_RESOURCE_AIR_RECON] < 3)
              pLegion->AirResources[ARMY_RESOURCE_AIR_RECON] = 3;
      }          
      else ASSERT(0);
}


void ScriptUndeploy(UID namedItem)
{
	if (scriptDebug) TRACE("Script undeploy triggered\n");

    VEHICLE* pVehicle;
    SARGE* pSarge;
    UNIT* pUnit;
    int index;
    if (namedItem == UID_GREEN)
    {
      TRACE("script Deleting green army\n");
      index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GREEN);
      PrepareDelete(index);
      return;
    }
    if (namedItem == UID_TAN)
    {
      TRACE("script Deleting tan army\n");
      index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_TAN);
      PrepareDelete(index);
      return;
    }
    if (namedItem == UID_BLUE)
    {
      TRACE("script Deleting blue army\n");
      index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_BLUE);
      PrepareDelete(index);
      return;
    }
    if (namedItem == UID_GRAY)
    {
      TRACE("script Deleting gray army\n");
      index = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GRAY);
      PrepareDelete(index);
      return;
    }

		 int eArmy;
		eArmy = EXTRACT_ARMY(namedItem);
		if (Armies[eArmy].Status == 0) return; // army not there


    if (OBJTYPE(namedItem) == ARMY_UNIT)
    {	
      pUnit = UnitFind(namedItem);
      if (!pUnit) return;
      
      // dont undeploy unit not alive and deployed
      if (!UNIT_ALIVE(pUnit)) return;
      if (UNIT_IN_HQ(pUnit)) return;
	  if (!pUnit->common.position.x) return;
      pUnit->deadPosition = pUnit->common.position;
      UnitUndeploy(pUnit);
    }
  else if (OBJTYPE(namedItem) == ARMY_SARGE)
  {
      pSarge = SargeFind(namedItem);
      if (!pSarge) return;

      // script may only deactive own army sarge.
      // used in multiplayer last game after you lose-man-standing
      if (ITEM_ARMY(pSarge) != ARMY_PLAYER) return;
      
      if (pSarge->common.nStrength == 0) return;
      if (pSarge->common.position.x == 0) return;
	  pSarge->deadPosition = pSarge->common.position;
 
      SargeUndeploy((ARMY_TYPE)EXTRACT_ARMY(namedItem));
  }
  else if (OBJTYPE(namedItem) == ARMY_VEHICLE)
  {
      pVehicle = VehicleFind(namedItem);
      if (!pVehicle) return;

      // dont undeploy unit not alive and deployed
      if (pVehicle->common.nStrength == 0) return;
      if (pVehicle->common.position.x == 0) return;
		pVehicle->deadPosition = pVehicle->common.position;
       VehicleUndeploy(pVehicle);
  }
}

///========================================================================
//	Function:		ScriptNuke
//	Description:	do a lot of damage to an item
///========================================================================
void ScriptNuke(UID namedItem)
{
	   if (scriptDebug) TRACE("Script Nuke triggered\n");

	ITEM *pItem;
	 int eArmy;
		eArmy = EXTRACT_ARMY(namedItem);
		if (eArmy != ARMY_INDEPENDENT && Armies[eArmy].Status == 0) return; // army not there

	pItem=AiItemFind(namedItem);
	
	//Because damage will communicate itself to remote machines, we only want
	//to do this if we're on the host machine
	
	if (pItem)
		if (EventsActive == 2)
			ItemDamage(pItem, 10000, DMGTYPE_OTHER, &pItem->position, 0);
}


///========================================================================
//	Function:		ScriptMerge
//	Description:	tell one unit to join another
///========================================================================

void ScriptUnitMerge(UID namedUnit,UID otherUnit)
{
	   if (scriptDebug) TRACE("Script Merge triggered\n");

    UNIT* pUnit = UnitFind(namedUnit);
    if (!pUnit) return;
    if (!IsAIActivated((ITEM*) pUnit)) return;

    UNIT* pUnitMerge = UnitFind(otherUnit);
    if (!pUnitMerge) return;

    // check unit disbanding

    // if killed, cannot be merged out of
    if (!UNIT_ALIVE(pUnitMerge)) return;
    // if not on map, cannot give it merge out of
    if (!UNIT_ON_MAP(pUnitMerge)) return;

    // merge is done into the living unit controllable by human
    pUnit->npc = 0; // now orders with other unit
	if( (!curselectedunit) )
		curselectedunit = UnitGetNextFunctional( NULL );

    // copy the data from the other current unit if it lives
    // take on his current order, and then listen for new ones also
    if (pUnitMerge && pUnitMerge->common.nStrength)
    {
      if (scriptDebug)
      {
          TRACE("   %s merges",ItemDBName(pUnit));
          TRACE("   into %s\n",ItemDBName(pUnitMerge));
      }
      pUnit->order = pUnitMerge->order;
      pUnit->focusSpeed = pUnitMerge->focusSpeed;
      pUnit->prestationBehavior = pUnitMerge->prestationBehavior;
      pUnit->poststationBehavior = pUnitMerge->poststationBehavior;
      pUnit->focusTile = pUnitMerge->focusTile;
      pUnit->focusLocation = pUnitMerge->focusLocation;
      pUnit->focusItem = pUnitMerge->focusItem;
      pUnit->arrivalEvent = EVENT_NUM_UNDEFINED;
      pUnit->eventtype = pUnitMerge->eventtype;
      pUnit->focusArrived = FALSE;
      pUnit->destination = pUnitMerge->destination;
      pUnit->routeData.destination = OFF_THE_MAP;
      pUnit->mergedWith = ITEM_UID(pUnitMerge);
    }
    // otherwise enter a follow order for this new unit unit
    else
    {
      if (scriptDebug)
      {
          TRACE("%s unable to merge\n",ItemDBName(pUnit));
      }
      UnitOrders(pUnit,UNIT_FOLLOW,OFF_THE_MAP,NULL,FAST_SPEED);
    }
}

///========================================================================
//	Function:		ScriptAtMode
//	Description:	change poststation behavior of a unit
///========================================================================

void ScriptAtMode(UID namedUnit,BEHAVIOR atMode)
{
	   if (scriptDebug) TRACE("Script AtMode triggered\n");

    UNIT* pUnit;
    pUnit = UnitFind(namedUnit);
    if (!pUnit) return;
    pUnit->poststationBehavior = atMode;
}

///========================================================================
//	Function:		ScriptUserControl
//	Description:	change to user control
///========================================================================

void ScriptUserControl(UID namedItem)
{
	   if (scriptDebug) TRACE("Script UserControl triggered\n");

    if (OBJTYPE(namedItem) == ARMY_UNIT)
    {      
      UNIT* pUnit = UnitFind(namedItem);
      if (!pUnit) return;
      if (!pUnit->npc) return;
      pUnit->npc = 0;
      // BECome selected if going to user control and on map
      if (UNIT_ON_MAP(pUnit) && pUnit->common.nStrength) curselectedunit = pUnit;
    }
    else if (OBJTYPE(namedItem) == ARMY_SARGE)
    {
      SARGE* pSarge = SargeFind(namedItem);
      if (!pSarge) return;
      if (!pSarge->npc) return;
      pSarge->npc = 0;
      TadFlags((TAD*)pSarge->common.pTad,TAD_SMART,TAD_CLEAR_IT);
	}
    else if (OBJTYPE(namedItem) == ARMY_VEHICLE)
    {
      VEHICLE* pVehicle = VehicleFind(namedItem);
      if (!pVehicle) return;
      if (!pVehicle->npc) return;
      pVehicle->npc = 0;
    }
}

///========================================================================
//	Function:		ScriptAIControl
//	Description:	change to AI control
///========================================================================

void ScriptAIControl(UID namedItem)
{
	   if (scriptDebug) TRACE("Script AIControl triggered\n");

    if (OBJTYPE(namedItem) == ARMY_UNIT)
    {      
      UNIT* pUnit = UnitFind(namedItem);
      if (!pUnit) return;
      pUnit->npc = 1;
	  if( curselectedunit == pUnit )
		curselectedunit = UnitGetNextFunctional( pUnit );
    }
    else if (OBJTYPE(namedItem) == ARMY_SARGE)
    {
      SARGE* pSarge = SargeFind(namedItem);
      if (!pSarge) return;
      // gain tad smart control
      if (pSarge->npc == 0)
          TadFlags((TAD*)pSarge->common.pTad,TAD_SMART,TAD_SET_IT);
      pSarge->npc = 1;
	}
    else if (OBJTYPE(namedItem) == ARMY_VEHICLE)
    {
      VEHICLE* pVehicle = VehicleFind(namedItem);
      if (!pVehicle) return;
      pVehicle->npc = 1;
    }
}

///========================================================================
//	Function:		ScriptHeal
//	Description:	recover hit points of remaining elements of item
///========================================================================

void ScriptHeal(UID namedItem, int percentToHeal)
{
	   if (scriptDebug) TRACE("Script Heal triggered\n");

    TROOPER* pTrooper;
    int i;

	switch(OBJTYPE(namedItem))
	{
	case ARMY_UNIT:
		{

			UNIT* pUnit = UnitFind(namedItem);
			if (!pUnit) return;

			FOR_EACH_TROOPER(pUnit,pTrooper,i)
			{
			  if (pTrooper->common.nStrength == 0) continue; // dead already
				pUnit->common.nStrength -= pTrooper->common.nStrength;
				// regenerate fully
				pTrooper->common.nStrength+=(pTrooper->common.nMaxStrength*percentToHeal/100);
				if (pTrooper->common.nStrength>pTrooper->common.nMaxStrength)
					pTrooper->common.nStrength=pTrooper->common.nMaxStrength;

				pUnit->common.nStrength += pTrooper->common.nStrength;
			}
		}
		break;

	case ARMY_SARGE:
		{
			SARGE* pSarge = SargeFind(namedItem);
      
			if (!pSarge) return;

			if (pSarge->common.nStrength)
			{
				pSarge->common.nStrength+=(pSarge->common.nMaxStrength*percentToHeal/100);
				if (pSarge->common.nStrength>pSarge->common.nMaxStrength)
					pSarge->common.nStrength=pSarge->common.nMaxStrength;
//				if (IS_LOCAL_ITEM(pSarge))
//					AudioPlayItem(HEAL_SARGE, (ITEM *)pSarge);
			}
		}
		break;
	}

}

///========================================================================
//	Function:		ScriptSetWeapon
//	Description:	change weapon on unit
///========================================================================

void ScriptSetWeapon(UID namedUnit,WEAPON_TYPE eWeapon)
{
	   if (scriptDebug) TRACE("Script SetWeapon triggered\n");

    UNIT* pUnit = UnitFind(namedUnit);
    if (!pUnit) return;
}
      

///========================================================================
//	Function:		Follow All
//	Description:	give detailed follow order to army
///========================================================================

void FollowAll(UID namedItem,UID followItem,BEHAVIOR inmode,
                  BEHAVIOR arrivalmode,
                  int eventNumber,int eventtype)
{
      UNIT* pUnit;
      LEGION* pLegion;
      VEHICLE* pVehicle;
      int i;
      int eArmy = 0;
      if (namedItem == UID_BLUE)
          eArmy = gpComm->IndexFromColor((ARMY_COLOR) ARMY_BLUE);
      else if (namedItem == UID_GRAY)
          eArmy = gpComm->IndexFromColor((ARMY_COLOR) ARMY_GRAY);
      else if (namedItem == UID_GREEN)
          eArmy = gpComm->IndexFromColor((ARMY_COLOR) ARMY_GREEN);
      else if (namedItem == UID_TAN)
          eArmy = gpComm->IndexFromColor((ARMY_COLOR) ARMY_TAN);
      pLegion = ArmyGetLegion(eArmy);
      FOR_EACH_UNIT(pLegion,pUnit)
      {
		  if (!pUnit->aiSetup) continue; // not under deploy control
		ScriptFollow(ITEM_UID(pUnit),followItem,inmode,arrivalmode,
                eventNumber,eventtype);
      }
      FOR_EACH_VEHICLE(pLegion,i)      
      {
          pVehicle = pLegion->pLegionVehicles[i];
		  pVehicle->speed = NORMAL_SPEED; // go slow to stay with units
          ScriptFollow(ITEM_UID(pVehicle),followItem,inmode,arrivalmode,
              eventNumber,eventtype);
      }
}
///========================================================================
//	Function:		ScriptFollow
//	Description:	give follow order 
///========================================================================

void ScriptFollow(UID namedItem,UID followItem,BEHAVIOR inmode,
                  BEHAVIOR arrivalmode,
                  int eventNumber,int eventtype)
{
	   if (scriptDebug) TRACE("Script Follow triggered\n");


	  // if ordering army, do them all
    if (namedItem == UID_BLUE || namedItem == UID_TAN ||
        namedItem == UID_GRAY || namedItem == UID_GREEN)
    {
       FollowAll(namedItem,followItem,inmode,arrivalmode,eventNumber,eventtype);
      return;
    }

    UNIT* pUnit;
    ITEM* pItem;
    if (OBJTYPE(namedItem) == ARMY_UNIT)
    {
      pUnit = UnitFind(namedItem);
      if (!pUnit) return;
      if (!IsAIActivated((ITEM*) pUnit))
      {
          if (scriptDebug)
          {
              TRACE("%s- script order refused by user-controlled item\n",ItemDBName(pUnit));
          }

          return;
      }
      // if killed, cannot give it order
      if (!UNIT_ALIVE(pUnit)) return;
      // if not on map, cannot give it order
      if (!UNIT_ON_MAP(pUnit)) return;
      if (UNIT_IN_VEHICLE(pUnit)) return;
      // cannot give follow order to unit in vehicle. It just enters again
    }
    else
  {
      TRACE("can only give follow to units\n");
      return;
  }
    // player unit is not npc and cannot be ordered by script
    if (EXTRACT_ARMY(namedItem) == ARMY_PLAYER && pUnit->npc == FALSE)
    {
      // UNLESS, both sides are AI controlled
      if (aiPlayers != 3) return;
    }

    pItem = AiItemFind(followItem);
    if (pItem)
	{
      UnitFullOrders(pUnit, UNIT_FOLLOW,OFF_THE_MAP, pItem , FAST_SPEED, inmode,
						 arrivalmode,eventNumber,eventtype);
	if (pUnit->lastOrdered == playCycle && playCycle)
		  TRACE("WARNING- already ordered %s this frame\n",ItemDBName(pUnit));
	  pUnit->lastOrdered = playCycle;
	}
      
}
            

///========================================================================
//	Function:		ScriptAirstrike
//	Description:	call in an airstrike
///========================================================================

void ScriptAirstrike(SPOINT* position,UID locationItem)
{
	   if (scriptDebug) TRACE("Script Airstrike triggered\n");

      SPOINT where;
      where = ScriptLocation(locationItem,position);
      DoAirSupport(AIRSUPPORT_AIRSTRIKE,where,ARMY_TAN);
}

///========================================================================
//	Function:		ScriptAirdrop
//	Description:	call in an airdrop
///========================================================================

void ScriptAirdrop(SPOINT* position,UID locationItem, ARMY_COLOR whichColor)
{
	   if (scriptDebug) TRACE("Script Airdrop triggered\n");

      SPOINT where;
      where = ScriptLocation(locationItem,position);
      DoAirSupport(AIRSUPPORT_AIRDROP,where,(int) whichColor);
}

///========================================================================
//	Function:		ScriptResurrect
//	Description:	bring a unit back to life
///========================================================================

void ScriptResurrect(UID namedItem,SPOINT* position,UID other)
{   
	if (scriptDebug) TRACE("Script Resurrect triggered\n");

      SARGE* pSarge;
      UNIT* pUnit;
      SPOINT point;
      // convert named items into their location or use location
      point = ScriptLocation(other,position);

      if (OBJTYPE(namedItem) == ARMY_UNIT)
      {	
          pUnit = UnitFind(namedItem);
          if (!pUnit) return;
		  if (!IS_LOCAL_ITEM(pUnit)) return;

          UnitCreate(ITEM_ARMY(pUnit),ITEM_CLASS(pUnit),pUnit);

          // cause LOCAL guy to recreate the unit. DO NOT SEND
          // network deploy message.
          // Event of resurrect will cause local copy to refresh and deploy
          UnitTrooperCreate(pUnit,pUnit->initialTroops);
          UnitInitialDeploy(pUnit,point,0,DEFENDFIRE);
          if (scriptDebug)
          {
              TRACE("    unit resurrected\n");
          }
      }
      else if (OBJTYPE(namedItem) == ARMY_SARGE)
      {
          pSarge = SargeFind(namedItem);
          if (!pSarge) return;
          // script may only resurrect own army sarge in multiplayer mode
          // That will tell all others you have deployed
          if (!IS_LOCAL_ITEM(pSarge)) return;

          SargeDeploy(pSarge,&point,0);
      }
      else if (OBJTYPE(namedItem) == ARMY_VEHICLE)
      {
          VEHICLE* pVehicle;
          pVehicle = VehicleFind(namedItem);
		  if (!pVehicle) return;

          // script may only resurrect own army vehicle in multiplayer mode
          // That will tell all others you have deployed
          if (!IS_LOCAL_ITEM(pVehicle)) return;

          VehicleDeploy(pVehicle,&point,pVehicle->deployFacing);
         if (scriptDebug || vehicleBehavior)
         {
              TRACE("%s resurrected\n",ItemDBName(pVehicle));
         }
      }
}

///========================================================================
//	Function:		ScriptAlly
//	Description:	make them allies. 
///========================================================================

void ScriptAlly(ARMY_COLOR army1, ARMY_COLOR army2)
{
	if (scriptDebug) TRACE("Script Ally triggered\n");
	army1 =  (ARMY_COLOR) gpComm->IndexFromColor(army1);
	army2 =  (ARMY_COLOR) gpComm->IndexFromColor(army2);

	// ally both with each other
	ArmySetAlliance((ARMY_TYPE)army1,(ARMY_TYPE)army2, TRUE);
	ArmySetAlliance((ARMY_TYPE)army2,(ARMY_TYPE)army1, TRUE);
}

///========================================================================
//	Function:		ScriptUnAlly
//	Description:	make them not allies. 
///========================================================================

void ScriptUnAlly(ARMY_COLOR army1, ARMY_COLOR army2)
{
	if (scriptDebug) TRACE("Script Unally triggered\n");
	army1 =  (ARMY_COLOR) gpComm->IndexFromColor(army1);
	army2 =  (ARMY_COLOR) gpComm->IndexFromColor(army2);

	// deally both with each other
	ArmySetAlliance((ARMY_TYPE)army1,(ARMY_TYPE)army2, FALSE);
	ArmySetAlliance((ARMY_TYPE)army2,(ARMY_TYPE)army1, FALSE);
}

///========================================================================
//	Function:		ScriptExplode
//	Description:	destroy this position or object location
///========================================================================

void ScriptExplode(SPOINT* position,UID namedItem,int type)
{
	   if (scriptDebug) TRACE("Script eXPLODE triggered\n");

    ITEM* pItem = NULL;
    SPOINT where;
	int damage;
	ULONG audioID;

    // if name is given, use its location instead
    if (namedItem) pItem = AiItemFind(namedItem);
    if (pItem)
    {
		switch(OBJTYPE(namedItem))
		{
		case ARMY_ASSET:
		case ARMY_OBSTACLE:
		case ARMY_STRUCTURE:
          OBJECT* pObj;
          pObj = (OBJECT*) pItem;
          // if object was dynamite, mark it destroyed
          if (pObj->category == EXPLOSIVES &&
              pObj->number == ARMY_EXPLOSIVE_WEAPON)
          {
              pObj->triggers |= TRIGGER_DESTROYED;
          }
  			where = pObj->cell.world_pos;
			break;
		default:
			where = pItem->position;
		}
      // if it is dead, use its old location
      if (!where.x) where = ItemDeadPosition(pItem);
		  
	  // if it was never deployed, use its deploy location
	  if (!where.x && OBJTYPE(namedItem) == ARMY_UNIT )
			where = ((UNIT*)pItem)->deployPosition;

    }
    else where = *position;

    if (type == -1) type = EXPLOSION_SMOKE_M_COMMAND;

	switch( type )
	{
	case EXPLOSION_SMOKE_S_COMMAND:
	case EXPLOSION_DIRT_SMOKE_S_COMMAND:
		audioID = SND_NULL_SND_ID;
		damage = 0;
		break;
	default:
		damage = 150;
		audioID = BIG_EXPLOSION;
		break;
	}
	DoExplosion(where.x, where.y, (COMMAND_NUMBERS)type, NULL, DMGTYPE_OTHER_EXPLOSION, 
				 damage, NULL, 0, 0, audioID );
}

static void DropIfWeapon(int eArmy,ITEM* pDropItem)
{ // this does a non-network local drop
      SARGE* pSarge;
      pSarge = SargePointer(eArmy);
	  if (!pSarge) return;

      ITEM* pItem;
      pItem = pSarge->pWeaponItemList[1];
      if (pItem == pDropItem)
      {
          SargeDoDropWeapon(pSarge,pSarge->common.position,(SARGE_WEAPON)1);
          BlowItem((ITEM*)pSarge);
      }
      pItem = pSarge->pWeaponItemList[2];
      if (pItem == pDropItem)
      {
          SargeDoDropWeapon(pSarge,pSarge->common.position,(SARGE_WEAPON)2);
          BlowItem((ITEM*)pSarge);
      }
}

static int HasWeapon(int eArmy,ITEM* pDropItem)
{ // this does a non-network local drop
      SARGE* pSarge;
      pSarge = SargePointer(eArmy);
	  if (!pSarge) return FALSE;

      ITEM* pItem;
      pItem = pSarge->pWeaponItemList[1];
      if (pItem == pDropItem) return TRUE;
      pItem = pSarge->pWeaponItemList[2];
      if (pItem == pDropItem) return TRUE;
      return FALSE;
}

void ScriptPlaceObject(UID nUid, SPOINT *position, UID whereItem)
{
	   if (scriptDebug) TRACE("Script Placeobject triggered\n");

	OBJECT *pObject;
	ITEM *pWhereItem=NULL;
	SPOINT where;
	SPOINT pos;
	int eArmy;

	if (!nUid)	return;
	pObject = (OBJECT*)AiItemFind(nUid);
	if (!pObject) 
	{
		TRACE("ScriptPlaceObject couldn't find object %x of army %d objtype %d \n",
			nUid,EXTRACT_ARMY(nUid),OBJTYPE(nUid));
		return;
	}
	
	// if weapon with no ammo, dont
	if (pObject->common.pWeapon && pObject->common.pWeapon->nAmmo == 0)
	{
		TRACE("object weapon has no ammo. declining placement\n");
		return;
	}

    FOR_EACH_DEPLOYED_ARMY(eArmy) 
	{
			 if (!HasWeapon(eArmy,(ITEM*) pObject)) continue;
			 TRACE("owned by sarge. refusing to place\n");
			 return;
	}

	switch(OBJTYPE(nUid))
	{
	case ARMY_ASSET:
	case ARMY_OBSTACLE:
	case ARMY_STRUCTURE:
 
		if (whereItem) pWhereItem = AiItemFind(whereItem);
		if (pWhereItem)
		{
			switch( OBJTYPE(whereItem) )
			{
			case ARMY_ASSET:
			case ARMY_OBSTACLE:
			case ARMY_STRUCTURE:
				where = ((OBJECTSTRUCT *)pWhereItem)->cell.world_pos;
				break;
			default:
				where = pWhereItem->position;
			}
		  // if it is dead, use its old location
		  if (!where.x) where = ItemDeadPosition(pWhereItem);

		  if (where.x)
		  {
			  pos = where;
		  }
	
		}
		else pos = *position;

		MapPlaceObject(pObject, &pos);
		break;
	}
}
void ScriptNotify(UID nUid1,UID nUid2, int which)
{
	   if (scriptDebug) TRACE("Script Notify triggered\n");

	int index1 = -1, index2 = -1;
	if (which == 2) // 2 is tell we are playing 1 player (affects ui)
	{
		  gpGame->oneplayerMode = TRUE;
		  return;
	}

	if (nUid1 == UID_GREEN)
          index1 = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GREEN);
      else if (nUid1 == UID_TAN)
          index1 = gpComm->IndexFromColor((ARMY_COLOR)ARMY_TAN);
      else if (nUid1 == UID_BLUE)
          index1 = gpComm->IndexFromColor((ARMY_COLOR)ARMY_BLUE);
      else if (nUid1 == UID_GRAY)
          index1 = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GRAY);
	if (nUid2 == UID_GREEN)
          index2 = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GREEN);
      else if (nUid2 == UID_TAN)
          index2 = gpComm->IndexFromColor((ARMY_COLOR)ARMY_TAN);
      else if (nUid2 == UID_BLUE)
          index2 = gpComm->IndexFromColor((ARMY_COLOR)ARMY_BLUE);
      else if (nUid2 == UID_GRAY)
          index2 = gpComm->IndexFromColor((ARMY_COLOR)ARMY_GRAY);
  
	  if (index1 < 0 || index2 < 0) 
	  {
		 TRACE("notify rejects index\n");
		return; // wrong stuff
	  }
	  if (which == 1)	// 1 is capture the flag notify
	  {
			ArmyCollectedFlag( index1, index2 );
	  }
}


void ScriptRemoveObject(UID nUid)
{
	   if (scriptDebug) TRACE("Script RemoveObject triggered\n");

	ITEM *pItem;
	OBJECT *pObject;
    int eArmy;

	pItem=AiItemFind(nUid);
	if (pItem && pItem->tile) // its there and on the map.
    {      
        // prove no sarge has it, for multi
        if (gpGame->GameType != GAMETYPE_ONEPLAYER)
        {
              FOR_EACH_DEPLOYED_ARMY(eArmy) DropIfWeapon(eArmy,pItem);
        }

		switch (OBJTYPE(nUid))
		{
		case ARMY_ASSET:
		case ARMY_OBSTACLE:
		case ARMY_STRUCTURE:
			pObject=(OBJECT*)pItem;
			if (pObject->cell.flags&ANIM_FLAG_ACTIVE) // is it active
  				MapRemoveObject(pObject);
			break;
		}
    }
}



///========================================================================
//	Function:		ArmiesRegenerateDeathEvents
//	Description:	on mission startup, retrigger events on dead units
///========================================================================
void ArmiesRegenerateDeathEvents()
{
      int eArmy;
      UNIT* pUnit;
      LEGION* pLegion;
      VEHICLE* pVehicle;
      int vehicle;
      FOR_EACH_DEPLOYED_ARMY(eArmy)
      {
        // we pay no attention at present to retriggering if sarge died

		pLegion = ArmyGetLegion(eArmy);
        FOR_EACH_UNIT(pLegion,pUnit)
        {
              // never assigned an event
              if (pUnit->common.eventNum == 0 ||
                  pUnit->common.eventNum == EVENT_NUM_UNDEFINED) continue;

             if (pUnit->mode == UNIT_DEAD)
                  DiedItemTriggerEvents((ITEM *)pUnit);
        }
        FOR_EACH_VEHICLE(pLegion,vehicle)
        {
              pVehicle = pLegion->pLegionVehicles[vehicle];
              if (pVehicle->state != VEHICLE_DYING) continue;
      
              // never assigned an event
              if (pVehicle->common.eventNum == 0 ||
                  pVehicle->common.eventNum == EVENT_NUM_UNDEFINED) continue;

              DiedItemTriggerEvents((ITEM *)pVehicle);      
        }

        // assets dead are handled by objects below
     }

     // now make alll objects die again that need to
     OBJECT *pObject;
     int i;
     for (i = 0; i < the_map.num_objects; i++)
     {
          pObject = &(the_map.objects[i]);

          // not dead
          if (pObject->common.nStrength != 0) continue;
		  // never could be killed
		  if (pObject->common.nMaxStrength == 0) continue;

          // never assigned an event
          if (pObject->common.eventNum == 0 ||
              pObject->common.eventNum == EVENT_NUM_UNDEFINED) continue;
      
          DiedItemTriggerEvents((ITEM *)pObject);      
     }
}


///========================================================================
//	Function:		GetTrooperOnTile
//	Description:	Given the x,y coordinates of a tile, returns a pointer to
//					the trooper who is currently there, if any
///========================================================================
TROOPER*		GetTrooperOnTile(int x, int y)
{
      int eArmy;
      LEGION* pLegion;
      UNIT* pUnit;
      TROOPER* pTrooper;
      int i;
      IPOINT tile = INDEX(x,y);
      FOR_EACH_DEPLOYED_ARMY(eArmy)
      {
          pLegion = ArmyGetLegion(eArmy);
          FOR_EACH_UNIT(pLegion,pUnit)
          {
              if (!UNIT_ON_MAP(pUnit)) continue;
              FOR_EACH_TROOPER(pUnit,pTrooper,i)
              {
                  if (pTrooper->common.tile == tile) return pTrooper;
              }
          }    
      }
	
      return NULL;
}

BOOL VehicleEnterable(VEHICLE* pVehicle)
{
    // can only enter convoy and halftrack
    return (ITEM_CLASS(pVehicle) == ARMY_CONVOY ||
        ITEM_CLASS(pVehicle) == ARMY_HALFTRACK);
}

SPOINT VehicleRear(VEHICLE* pVehicle)
{
      // try to find a rear point
      ANIM* pAnim;
      int offset;
      int direction;
      SPOINT x;

      pAnim = pVehicle->pAnimation;
      offset = pAnim->move_off.back;
      direction = pVehicle->common.facing;
      direction = NormalizeFacingAdd(direction,CIRCLE_UNITS/2);
      x.x = (short)(pAnim->world_pos.x + cos_table[direction] * offset);
      x.y = (short)(pAnim->world_pos.y + sin_table[direction] * offset);

      IPOINT out;
      out = ItemFanOut((ITEM*)pVehicle,ENCODE_IPOINT(x.x,x.y),8,UnitOutOfVehicle);
      x = CenterPointFromTile(out);
      return x;
}

void ClearAIPending()
{
	int eArmy;
	UNIT* pUnit;
	LEGION* pLegion;
	int i;
	VEHICLE* pVehicle;
	FOR_EACH_DEPLOYED_ARMY(eArmy)
	{
		pLegion = ArmyGetLegion(eArmy);
		FOR_EACH_UNIT(pLegion,pUnit)
		{
			if (!UNIT_ON_MAP(pUnit)) continue;
			if (pUnit->common.nStrength == 0) continue;
            if (pUnit->pVehicle) continue;

			// give them stationary defend orders.
			UnitFullOrders(pUnit,UNIT_DEFEND,pUnit->common.position,NULL,FAST_SPEED,
			 DEFENDFIRE,DEFENDFIRE,EVENT_NUM_UNDEFINED,0);
			pUnit->focusArrived = TRUE;  // it is already there now
		}
        for (i = 0; i < pLegion->nNumberOfVehicles; ++i)
        {
          pVehicle = pLegion->pLegionVehicles[i];
          if (pVehicle->common.tile == 0) continue;
          pVehicle->aiGoal = OFF_THE_MAP;
          pVehicle->arrivalEvent = EVENT_NUM_UNDEFINED;
          pVehicle->velocity = pVehicle->full_velocity = 0;
        }

	}
}

///========================================================================
//								EOF
///=======================================================================

