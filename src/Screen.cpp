//========================================================================
//	FILE:			$Workfile: Screen.cpp $
//
//	DESCRIPTION:	ArmyMen Full Screen UI processing.
//
//	AUTHOR:			Andrew J Burgess
//
//	CREATED:		Sunday, October 19, 1997
//
//	REVISION:		$Header: /ArmyMen/src/Screen.cpp 317   4/18/98 12:55p Dmaynard $
//
//========================================================================
//                 COPYRIGHT(C)1997 The 3DO Company
//      Unathorized reproduction, adaptation, distribution,
//      performance or display of this computer program or
//      the associated audiovisual work is strictly prohibited.
//                      All rights reserved.
///========================================================================
//  History
//
//  $Log: /ArmyMen/src/Screen.cpp $
//  
//  317   4/18/98 12:55p Dmaynard
//  Made Players name Blue on the map selection screen when they have not
//  yet hit continue after playing completing the previous multi-player
//  game.
//  
//  316   4/17/98 5:50a Dmaynard
//  Added calls to Force ReadRules call when starting a new game
//  
//  315   4/17/98 3:55a Dmaynard
//  Changed ScrnUpdateRules to always call ReadRules
//  
//  314   4/17/98 3:40a Dmaynard
//  Added back calls to ScrnUpdateRule in ScrnUpdateHost and
//  ScrnUpdateRemote  these are needed again since script file names are
//  getting cleared after a game.
//  
//  313   4/17/98 3:09a Dmaynard
//  Added code so that the remote player's name turns gray on the map
//  selection screen if we haven't heard from him in more than 1.25 seconds
//  
//  312   4/17/98 2:40a Dmaynard
//  Defensive Coding to prevent DPlay race conditions
//  
//  311   4/16/98 4:50p Dmaynard
//  No longer null's gpGame->mapName in SCRNOnMultiPLayer
//  was a problem because rulname was be saved but not mapname.
//  
//  310   4/16/98 11:58a Aburgess
//  initialize Scrn rule file index
//  
//  309   4/16/98 11:38a Aburgess
//  avoid destruction of playername
//  
//  308   4/15/98 3:48p Dmaynard
//  Clean-up old players who left during last game Whenever we see a new
//  player joining.
//  
//  307   4/15/98 3:26p Dmaynard
//  Better Cleaning Up of Players who left during the last game in
//  ScrnInitHost
//  
//  306   4/15/98 10:43a Aburgess
//  modification to correctly restore the state of the MultiStartOK button
//  based on having a map selected. Previously selected maps no longer
//  CLICK avoiding the transmission of extra player messages. No the have
//  map flag is set directly since we are now gauranteed to have a map.
//  
//  305   4/14/98 9:32p Dmaynard
//  Added Call to ScrnReportMapError in ScrnUpdateRemoteMap
//  
//  304   4/14/98 3:42p Dmaynard
//  Added safety check in ScrnMapUpdateRemote to not try and validate maps
//  if we haven't heard from the host yet
//  
//  303   4/14/98 3:21a Aburgess
//  remove initial Sendplayer msg call
//  
//  302   4/14/98 3:05a Aburgess
//  initialized local variable
//  
//  301   4/14/98 2:53a Aburgess
//  forcing proper date in checkin
//  
//  300   4/15/98 2:50a Aburgess
//  modified Bad Map notifications to init and Map selection.  Also reduced
//  number of sendplayermsg calls during scrolling of campaign selection
//  area in MULTIPLAYER
//  
//  299   4/14/98 10:08p Aburgess
//  corrected campaign list redraw failure (MultiPlayer)
//  
//  298   4/13/98 2:20p Nrobinso
//  fix sound skipping in mission win/lose
//  
//  297   4/10/98 11:46a Nrobinso
//  fix cursor left behind glitch
//  
//  296   4/09/98 12:31p Nrobinso
//  fix the cursor left behind in dialogs; make sure we are seeing the gdi
//  surface for dialogs
//  
//  295   4/08/98 11:25p Nrobinso
//  fix keyboard save
//  
//  294   4/08/98 8:06p Nrobinso
//  use briefs path
//  
//  293   4/08/98 12:18p Nrobinso
//  remove duplicate code
//  
//  292   4/06/98 10:54p Dmaynard
//  When screen in maximixed ScrnInit code is called and GetFocus still
//  doesn't return our window handle.   We have to Init the screens anyway.
//  
//  291   4/06/98 2:14p Nrobinso
//  separate returining for options and from recall mission
//  
//  290   4/06/98 12:40p Nrobinso
//  remove unused
//  
//  289   4/06/98 11:56a Dmaynard
//  Restore from Alt-Tab now calls proper ScrnInit routines.
//  
//  288   4/06/98 11:03a Dmaynard
//  Alt-Tab fix
//  
//  287   4/06/98 11:01a Dmaynard
//  Fix for alt-tab. 
//  
//  286   4/04/98 8:39p Dmaynard
//  Changed the way Screen functions decide if a player is in the game.
//  Fixes bugs for players exiting and rejoining during map select.
//  
//  285   4/03/98 6:04p Aburgess
//  modifications made to correct Joystick Configuration BACK/RESTORE bugs
//  
//  283   4/03/98 4:18p Aburgess
//  modifications to fix next mission bug
//  
//  282   4/02/98 11:39p Aburgess
//  modifications to support NEXT playable mission
//  
//  281   4/02/98 7:05p Nrobinso
//  fix mp name width problem
//  
//  280   4/02/98 3:21p Phu
//  typecast to avoid warnings
//  
//  279   4/01/98 1:17p Aburgess
//  yet another fix to the New Player double-click bug
//  
//  278   4/01/98 12:25p Aburgess
//  error using == rather than !=
//  
//  277   4/01/98 11:02a Aburgess
//  properly handle "New Player" callsign cases. Turn Cursor on and off for
//  credits video, disable update of host and remote when not in focus.
//  
//  276   3/31/98 5:55p Aburgess
//  copy sarge directional keys to setup keys for mp
//  
//  275   3/31/98 3:53p Nrobinso
//  fix cursor problem
//  
//  274   3/31/98 2:59p Dmaynard
//  Andy's changes for when to send PlayerMsg   (New Map selected)
//  
//  273   3/29/98 5:34p Nrobinso
//  setup cheats
//  
//  272   3/29/98 1:57p Nrobinso
//  remove unused
//  
//  271   3/29/98 1:03p Nrobinso
//  fix mission briefing no coming up
//  
//  270   3/27/98 5:20p Nrobinso
//  turn off cheats when choose anything in options menu
//  
//  269   3/27/98 4:49p Nrobinso
//  switch to cheats override in options menu
//  
//  268   3/27/98 3:36p Aburgess
//  attempt to override 0 length titles
//  
//  267   3/27/98 2:38p Dmaynard
//  Changed Abort Mission to Quit Game if we launched by a lobby.
//  
//  266   3/27/98 10:52a Dmaynard
//  Added Checksumming of AiDefault.aii files in Map Checking
//  
//  265   3/26/98 8:24p Nrobinso
//  fix firing when clicking thru in game screens; add MP music
//  
//  264   3/26/98 1:37p Dmaynard
//  Added Checksumming of all Script files listed in the rule file
//  
//  263   3/26/98 12:08p Nrobinso
//  have last mission in a scenario automatically go on to the next mission
//  
//  262   3/26/98 10:18a Nrobinso
//  set all saved game operations to the save game folder
//  
//  261   3/26/98 10:07a Nrobinso
//  rearrange initstats code so we don't change the directory out from
//  under it
//  
//  260   3/26/98 9:22a Nrobinso
//  set the flags for moving on to next scenario and campaign if won
//  
//  259   3/25/98 8:12p Nrobinso
//  remove unused; return to mission selection if you are out of missions
//  
//  258   3/25/98 7:36p Nrobinso
//  fix paths for mission end bitmaps
//  
//  257   3/25/98 7:27p Nrobinso
//  fix path for loading win/lose bitmaps
//  
//  256   3/25/98 6:56p Nrobinso
//  remove unsued
//  
//  255   3/25/98 6:26p Nrobinso
//  have multiple mission voice overs
//  
//  254   3/25/98 4:08p Aburgess
//  removed extra screen BKG assignments
//  
//  253   3/25/98 3:46p Nrobinso
//  remove unused; turn off the mission music during the mission briefing
//  
//  252   3/25/98 3:26p Aburgess
//  added CopyBackToFront to APPLY. Second clicks on "NEW PLAYERS" causes
//  edit rather than NEXT
//  
//  251   3/23/98 6:41p Nrobinso
//  don't check for movie coming out os stats -- it's already been done
//  
//  250   3/23/98 4:47p Aburgess
//  fixed chat receive colors in MP
//  
//  249   3/23/98 4:07p Aburgess
//  modified onplayback
//  
//  248   3/23/98 1:57p Nrobinso
//  
//  247   3/23/98 1:03p Nrobinso
//  fix typo
//  
//  246   3/23/98 12:19p Aburgess
//  updating handling of music processing.
//  
//  245   3/23/98 11:37a Nrobinso
//  remove disconnect button; comment out yes sir on exiting mp
//  
//  244   3/22/98 11:57p Nrobinso
//  don't eliminate a config button just beause it is undefined
//  
//  243   98/03/20 16:51 Dmaynard
//  Added protection in UpdateRemote in case a message from the host comes
//  in before we have initialized screen states.
//  
//  242   3/20/98 4:09p Dmaynard
//  Exit From Map Screen if Started by Lobby will now exit game.
//  
//  241   3/20/98 3:36p Dmaynard
//  Better State Changes for Lobby Start-up
//  
//  240   3/20/98 11:53a Aburgess
//  modifications made to correct VOICE and MUSIC cut offs. It apprears
//  that ALL Music and Voice streams need to be run with LOOP on.
//  
//  239   3/20/98 11:01a Dmaynard
//  Added code to make command line option -Rule: work properly. You can
//  now specify a rule file from the command line (needed for lobby starts)
//  
//  238   3/20/98 2:08a Nrobinso
//  fix problem with coming back from mp as the wrong color
//  
//  237   3/20/98 12:06a Nrobinso
//  clear mouse buttons when not used by sarge
//  
//  236   3/19/98 7:48p Nrobinso
//  fix delay/cursor problems coming out of options menu
//  
//  235   3/19/98 3:16p Nrobinso
//  deal with NULL key config description
//  
//  234   3/19/98 2:17p Aburgess
//  modifications made to correct audio deletions
//  
//  233   3/19/98 2:41p Nrobinso
//  turn the cursor off before clearing all surfaces
//  
//  232   3/19/98 1:25p Aburgess
//  attempt to fix player colors
//  
//  231   3/19/98 1:48p Nrobinso
//  turn off vehicle sfx if do options
//  
//  230   3/18/98 3:08p Aburgess
//  fix chat colors
//  
//  229   3/18/98 2:45p Aburgess
//  MP map list now scrolls down to last possible map
//  
//  228   3/18/98 3:03p Nrobinso
//  switch to mp screen buttons coming from the root Screens
//  
//  227   3/18/98 2:22p Aburgess
//  modifications to stop and delete audio test sounds
//  
//  226   3/18/98 1:25p Aburgess
//  corrected scrn transition bug
//  
//  225   3/18/98 11:49a Aburgess
//  removed unnecessary SCRN setstate (NULL) call, added stream
//  stop/quiet/noisy/play processing
//  
//  224   3/18/98 9:37a Dmaynard
//  Added UnPause LOCAl to Abort Mission
//  
//  223   3/18/98 2:30a Nrobinso
//  audio options defulat to the on/off flag stored in game, not whether
//  audio is actually on
//  
//  222   3/18/98 12:51a Nrobinso
//  cleanup registry access
//  
//  221   3/17/98 4:42p Dmaynard
//  Added PAUSE_MAPLOAD instead of piggy-backing on the normal PAUSE_LOCAL
//  flags.
//  
//  220   3/17/98 3:09p Aburgess
//  correction of player name entry processing
//  
//  219   3/17/98 11:19a Aburgess
//  correction of player callsign UI processing. Changes to make
//  Key/Joystick name change to clicked color during config change
//  
//  218   3/16/98 3:52p Nrobinso
//  turn off the cursor when click on the continue button
//  
//  217   3/16/98 1:03p Nrobinso
//  turn off traces
//  
//  216   3/16/98 1:56a Nrobinso
//  remove unused
//  
//  215   3/16/98 12:28a Nrobinso
//  pull cd checking and map error checking out to centralized routines;
//  check for no save file
//  
//  214   3/14/98 4:44p Nrobinso
//  fix double click, back while editing and nameless palyers
//  
//  213   3/13/98 12:15p Dmaynard
//  Bug Fixes for JoinSession Dialog  on TCP/IP case.
//  
//  212   3/13/98 12:08p Nrobinso
//  fix state change between missions
//  
//  211   3/13/98 11:40a Nrobinso
//  simplify stats state
//  
//  210   3/13/98 10:54a Dmaynard
//  Adjusted latency time to color mapping
//  
//  209   3/13/98 10:39a Dmaynard
//  Added Windows Timer Messages to repaint Player names so that their
//  colors can reflect latency to that player. Green==low yellow==medium
//  red== high.
//  
//  208   3/12/98 4:09p Aburgess
//  changed to stop all audio
//  
//  207   3/12/98 2:10p Aburgess
//  modifications made to support multiplayer campaign music and to restart
//  music on exit of game play options screen
//  
//  206   3/12/98 1:19p Aburgess
//  modifications made to support override of "Abort Mission" with "End
//  Boot Camp"
//  
//  205   3/12/98 11:39a Aburgess
//  corrected screen redraw/flashing problems
//  
//  204   3/12/98 10:20a Aburgess
//  removed setting of screen map reference index to 0 at init. Retains
//  last used index.
//  
//  203   3/12/98 9:32a Aburgess
//  when using APPLY button, screens will now return to the options screen
//  
//  202   3/11/98 3:20p Aburgess
//  modifications to support non-overwriting key bindings
//  
//  201   3/11/98 1:47p Nrobinso
//  remove ending LF on rule file lines
//  
//  200   3/11/98 11:26a Aburgess
//  modifications made to support new colorization of menus based on player
//  army color
//  
//  199   98-03-11 11:06 Dmaynard
//  
//  198   3/11/98 9:48a Dmaynard
//  Setting Player's Name Foreground color depending on latency to that
//  player
//  
//  197   3/11/98 12:57a Nrobinso
//  only turn off cursor when needed
//  
//  196   3/10/98 11:22p Nrobinso
//  turn cursor off at beginning of draw
//  
//  195   3/10/98 7:24p Nrobinso
//  read multiple scripts from rule file
//  
//  194   3/09/98 12:05p Aburgess
//  initialization of Audio volume slider bars
//  
//  193   3/09/98 11:28a Nrobinso
//  remove mission statement state; assure no compare stats if running off
//  cd
//  
//  192   3/09/98 10:42a Aburgess
//  ABOUT screens and other modifications
//  
//  191   3/09/98 9:06a Nrobinso
//  more fixes to cursor
//  
//  190   3/08/98 9:46p Nrobinso
//  working on getting cursor to always show where it needs to
//  
//  189   3/08/98 9:06p Nrobinso
//  enabled windows cursor at beginning of every screen state; simplified
//  some termiantors
//  
//  188   3/08/98 8:15p Nrobinso
//  collapse termiantion routines; diable joystick option if you don't have
//  one attached
//  
//  187   3/07/98 10:44p Nrobinso
//  change the check for CD-ROM and use an error dialog
//  
//  186   3/06/98 5:21p Aburgess
//  modification of audio options screen
//  
//  185   3/05/98 4:57p Aburgess
//  modifications made to support WIN/LOSE and end of scenario only
//  
//  184   3/05/98 2:47p Aburgess
//  added reading of joystick in Non-Gameplay mode
//  
//  183   3/03/98 5:20p Dmaynard
//  Changes for Lobby Startup,  Setting GameState and UI properly when
//  launched froma lobby.
//  
//  182   3/03/98 1:59p Phu
//  esc handling for setup state
//  
//  181   3/03/98 9:45a Aburgess
//  map name remains selected during scrolling in Host Map Select screen
//  
//  180   3/03/98 9:18a Aburgess
//  re-implemented MISSION LOSe FMVs
//  
//  179   3/02/98 12:14p Aburgess
//  modifications made to support the ESC key in both non-gameplay and
//  gameplay modes.
//  
//  178   3/02/98 10:31a Aburgess
//  modifications made to correct SFX delete problems and audio ON/OFF
//  tracking.
//  
//  177   3/01/98 11:16p Nrobinso
//  check for a screen when forceing updates
//  
//  176   2/27/98 12:54p Nrobinso
//  turn on title music
//  
//  175   2/26/98 3:42p Aburgess
//  corrected non-selected map button in Multiplayer Host Screen on
//  re-entry
//  
//  174   2/26/98 2:43p Nrobinso
//  put cd-rom check on a run time flag
//  
//  173   2/26/98 2:26p Aburgess
//  modifiations made to properly process the ESC key in mission recall and
//  map screens
//  
//  172   2/26/98 10:19a Aburgess
//  removed SCREENBTN memory leak
//  
//  171   2/25/98 5:39p Nrobinso
//  remove a bunch of commented out code
//  
//  170   2/25/98 2:52p Aburgess
//  modifications to improve AUDIO options interface. Still needs work.
//  
//  169   2/25/98 1:35p Aburgess
//  modification of audio control screen
//  
//  168   2/25/98 1:14p Nrobinso
//  change debug include to commands include
//  
//  167   2/25/98 11:47a Aburgess
//  modifications made to correct user configuration bugs
//  
//  166   2/24/98 11:06a Aburgess
//  modifications made to fixed the no audio on continues bug. Also added
//  access of fixed keycodes for display in default keycode screens
//  
//  165   2/23/98 2:59p Dmaynard
//  Bug Fix for case when one player left the game during the previous
//  round and we are now back in the map selection screen getting ready for
//  a new game.  We have to remove the remnants of the departed player.
//  
//  164   2/21/98 5:48p Nrobinso
//  turn off title music
//  
//  163   2/20/98 4:30p Aburgess
//  modifications made to reduce amount of work necessary to set up a
//  multiplayer mission select screen (host or remote).
//  
//  162   2/19/98 5:27p Dmaynard
//  Re-open session between games.
//  
//  161   2/19/98 3:54p Dmaynard
//  Added code in ScrnInitHost to re-open Session in between games.
//  
//  160   98/02/19 15:43 Dmaynard
//  modifications made to properly set m_ArmyGotMap for MultiStartOK
//  setting
//  
//  159   2/19/98 3:15p Aburgess
//  initialization of haveMap at host init
//  
//  158   2/19/98 3:04p Aburgess
//  correction to merge problem. Update of SCRNmultiStartOK via new MapMsg
//  system
//  
//  157   2/19/98 2:57p Aburgess
//  modifications made to support BAD Map detection in remote players.
//  Added checks for BootCamp game play mode.
//  
//  156   2/19/98 2:22p Dmaynard
//  Added bool parameter to calls to SendPlayerMessage  indicating whether
//  or not the map has changed.
//  
//  155   2/19/98 11:10a Dmaynard
//  Testing removing the call that sets a button color to the CLICKED
//  state.  Trying to fix a bug that results in a setcolor infinite message
//  loop between host and remote.
//  
//  154   2/18/98 6:35p Aburgess
//  modifications made to support Joystick and Custom configurations.
//  Corrected BACKSPACE in edit keys. Added Double-Click, and Name-Return
//  advance to next mission. Corrected multiple Callsign select bug.
//  Corrected configuration offset problem.
//  
//  153   2/17/98 7:51p Nrobinso
//  switch to audio play calls
//  
//  152   2/17/98 6:23p Dmaynard
//  Added Msg Summary output TRACE's after each game is finished.
//  94% of messages are Unit Update Messages.
//  
//  151   2/17/98 10:14a Nrobinso
//  display all commands in joystick table
//  
//  150   2/17/98 9:31a Aburgess
//  corrected access to joystick button names
//  
//  149   2/17/98 9:02a Aburgess
//  modifications made to support User Configuration
//  
//  148   2/16/98 6:28p Nrobinso
//  joystick configuration support
//  
//  147   2/16/98 3:26p Dmaynard
//  Fixes for playing multiple multi-player games.  Have to resync and wait
//  until everybody is back in the map selection screen until we can start
//  another game.  Also changed it so that host remembers the last map
//  selected and come up with that as the default when you re-enter the map
//  selection screen from the continue button on the Mission Won/Loss
//  screen.
//  
//  146   2/16/98 12:24p Dmaynard
//  Fixed bug which was smashing remote's mapname
//  
//  145   2/16/98 11:02a Nrobinso
//  remove annoying trace
//  
//  144   2/16/98 10:10a Nrobinso
//  send more info if bad map
//  
//  143   2/16/98 9:29a Nrobinso
//  make checksum unsigned longs
//  
//  142   2/16/98 12:11a Dmaynard
//  Bug Fixes for playing second multi-player game in a session
//  
//  141   2/13/98 4:00p Nrobinso
//  
//  140   2/13/98 10:06a Aburgess
//  modifications made to further support keyboard configurations. Support
//  of Audio slider bar. implementation of all known buttons
//  
//  139   2/12/98 4:17p Aburgess
//  modifications made to support Custom User Input Configuration
//  
//  138   2/12/98 12:54p Nrobinso
//  new sounds
//  
//  137   2/12/98 11:46a Dmaynard
//  switched order of setGameState  THEN setScrnState  because SetGameState
//  has side effects, namely it calls SetScrnState.
//  
//  136   2/11/98 7:48p Nrobinso
//  disconnect on abort; remove multiplayer replay; return multiplayer top
//  map select screen
//  
//  135   2/10/98 5:57p Dmaynard
//  Added LOCAL UNPAUSE and RemoteUnPause to ScrnPlayBack routine to
//  unpause when user hits back on Options menu.
//  
//  134   2/10/98 1:12p Nrobinso
//  remove old TRACE
//  
//  133   2/09/98 7:23p Nrobinso
//  crop mutiplayer sarge name
//  
//  132   2/09/98 1:54p Aburgess
//  modifications made to support IN GAME screens, Cursor control, and
//  Rules presentation
//  
//  131   2/08/98 3:27p Nrobinso
//  oops -- removed .AMM concat in mission selection
//  
//  130   2/07/98 6:07p Nrobinso
//  multiple maps may share a rule file for multiplayer; remote display bug
//  remains
//  
//  129   2/07/98 1:50p Nrobinso
//  make mission/map buttons into UI functions
//  
//  128   2/06/98 11:02a Nrobinso
//  add cd-rom check; patch quit button bug (hScreenBtn is a bad pointer)
//  
//  127   2/06/98 8:45a Aburgess
//  modifications made to translate keycodes
//  
//  126   2/06/98 7:20a Aburgess
//  modifications made to support the CUSTOM configuration screen
//  
//  125   2/05/98 3:26p Nrobinso
//  add real stats
//  
//  124   2/05/98 9:49a Aburgess
//  modifications made to support the OPTIONS screens (config, abort
//  mission and audio) during game play mode.
//  
//  123   2/04/98 5:56p Nrobinso
//  cleanup stat screen construction
//  
//  122   2/04/98 1:45p Nrobinso
//  update stats before displaying; multiplayer stats are of player, not
//  winner
//  
//  121   2/03/98 4:48p Aburgess
//  repaired Remote Load background display, reduced Multiplayer chat max
//  number of lines to 2 rather than 4. Ignore NULL map references.
//  
//  120   2/03/98 4:02p Nrobinso
//  comment out unused local
//  
//  119   2/03/98 3:15p Nrobinso
//  duplicate save call removed
//  
//  118   2/03/98 2:40p Aburgess
//  modifications made to correct music stream failures
//  
//  117   2/02/98 5:01p Aburgess
//  re-enabled audio at end of stats
//  
//  116   2/02/98 3:52p Aburgess
//  added a disconnect in OnNoPlayAgain if in multiplayer mode
//  
//  115   2/02/98 1:01p Aburgess
//  modifications made to support new mission briefing references through
//  campaign.cpn
//  
//  114   2/02/98 11:49a Aburgess
//  activated multiplayer load screen via .RUL reference. Closed the
//  distance between lines in the RULES screen.
//  
//  113   2/02/98 11:09a Aburgess
//  modification to campaign select in multiplayer
//  
//  112   2/02/98 10:51a Aburgess
//  removed repeated calls to multimap select. Removed stuck campaign list
//  selection
//  
//  111   2/02/98 10:06a Aburgess
//  
//  110   2/02/98 9:00a Nrobinso
//  add extension to map name instead of reading it fromcampaign file;
//  improve error checking by looking for map existance; improve mp map
//  selection error checking
//  
//  109   2/01/98 8:30p Nrobinso
//  add failed multiplayer screen
//  
//  108   2/01/98 4:31p Aburgess
//  modifications made to support new ART and maps files
//  
//	...
//
//  1     10/27/97 10:25a Aburgess
//  FullScreen UI Screen interface
//  
//  
//  $Nokeywords:$
//========================================================================
//========================================================================

// Includes
#include "stdafx.h"
#include "comm.h"
#include "Armymen.h"
#include "MainFrm.h"
#include "GameFlow.h"
#include "map.h"
#include "gameproc.h"
#include "Dialog.h"
#include "Audio.h"
#include "Ai.h"
#include "ui.h"
#include "comm.h"
#include "miscfile.h"
#include "bmptext.h"
#include "States.h"
#include "Screen.h"
#include "Screen.dat"
#include "Stats.h"
#include "input.h"
#include "Commands.h"
#include "commands.h"
#include "Movie.h"
#include "fileio.h"
#include "debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef enum
{
	RULE_FILE_OK = 0,
	RULE_FILE_BAD,
	RULE_FILE_NOEXIST
} RULES_ERROR;


//================================================================
//			GLOBAL variables
//================================================================
extern BOOL		AUDIOsfxOn;
extern BOOL		AUDIOmusicOn;
extern BOOL		AUDIOvoiceOn;
extern char*	KeysText[];
extern CONFIG	UIcurrentConfig;
extern char*	NoCD_Text;
extern SBTN_SCRN_COLORS*	ArmyInterfaceColors[ LAST_COLOR_ARMY+1 ];
extern char*				ArmyInterfacePaths[ LAST_COLOR_ARMY+1 ];
extern SOBJIMAGEDEF			missionOverImage;	// string is filled in
extern char*	EndBootCamp_Text;
extern char		NEWPLAYER_TextBtn[];
extern int		NEWPLAYER_BtnSize;

#ifndef FINAL
	BOOL no_cd_ok = TRUE;
#endif

//================================================================
//			GLOBAL prototypes
//================================================================
extern void				DrawCursor();
extern void				StopAudioData();
extern unsigned char	SBtnPlayerColor( SHORT nPlayerIndex );
extern void				MissionVisible(MISSIONREF* pMission);
extern void				MissionNextVisible(MISSIONREF* pMission);

//================================================================
//			LOCAL variables
//================================================================
HSCREEN			SCRNfullScreen;
CAMPAIGNREF*	SCRNcampaign;

char*	default_name = "default";
char*	SCRNnullStateName = "SCRN_NULL_STATE";
char*	SCRNstateName[SCRN_LAST_STATE+1] =
{
//	"SCRN_NULL_STATE",
	"SCRN_TITLE_STATE",				// Title Screen state
	"SCRN_GAME_START_STATE",		// One or Multi Player, Options, Quit
	"SCRN_SELECT_CAMPAIGN_STATE",	// One Player campaign selection
	"SCRN_SELECT_CALLSIGN_STATE",	// One Player player name selection
	"SCRN_SELECT_MISSION_STATE",	// One Player mission selection

	"SCRN_MULTI_HOST_STATE",		// Multi Player HOST campaign selection
	"SCRN_MULTI_REMOTE_STATE",		// Multi Player REMOTE campaign selection

	"SCRN_OPTIONS_STATE",			// Armymen options selection
	"SCRN_CONTROLS_STATE",			// User control configuration
	"SCRN_AUDIO_STATE",				// audio configuration
	"SCRN_ABOUT_STATE",				// About Armymen configuration
	"SCRN_PLAY_OPTIONS_STATE",		// Armymen game play options selection
	"SCRN_PLAY_CONTROLS_STATE",		// User control configuration
	"SCRN_PLAY_AUDIO_STATE",		// audio configuration
	"SCRN_PLAY_ABOUT_STATE",		// About Armymen configuration

	"SCRN_QUIT_STATE",				// Army quit

	"SCRN_STATS_STATE",				// Army statistics

	"SCRN_KEYPAD_STATE",			// User Keypad configuration
	"SCRN_KEYBOARD_STATE",			// User KeyBoard configuration
	"SCRN_CUSTOM_STATE",			// User Custom configuration
	"SCRN_JOYSTICK_STATE",			// User Joystick configuration

	// NOTHING BELOW THIS LINE
	"SCRN_LAST_STATE"				// screen last state marker
};

#define		SCRN_MAX_RULES_LENGTH	256

char*		SCRNruleFiles[ SCRN_MAX_RULE_FILES ];
int			SCRNruleIndex;
int			SCRNruleFileIndex = 0;
char		SCRNloadMap[SCRN_MAX_NAME_LEN+1];
char		SCRNrules[SCRN_MAX_RULES_LENGTH+1];
char		SCRNrulesTitle[64];
CHAT		SCRNchat;

ULONG		SCRNsfxSnd          = SND_NULL_SND_ID;
BOOL		SCRNsfxPlayToggle   = FALSE;
ULONG		SCRNmusicSnd        = SND_NULL_SND_ID;
BOOL		SCRNmusicPlayToggle = FALSE;
ULONG		SCRNvoiceSnd        = SND_NULL_SND_ID;
BOOL		SCRNvoicePlayToggle = FALSE;

COLORREF	PlayerColorTable[ LAST_COLOR_ARMY ] = { RGB_GREEN, RGB_LT_TAN, RGB_LT_BLUE, RGB_LT_GRAY };
COLORREF	PlayerBtnColorTable[ LAST_COLOR_ARMY ] = { SBTN_LT_GREEN, SBTN_LT_TAN, SBTN_LT_BLUE, SBTN_LT_GREY };

static	DWORD	SCRNtimerStart   = 0;
static	BOOL	SCRNtimerTrigger = FALSE;
static	BOOL	SCRNmultiStartOK = FALSE;

//================================================================
//			LOCAL prototypes
//================================================================
BOOL			ScrnSetReference( HSCREEN hScreen, char* pScreenRef );
SBOX*			ScrnDisplayBkg( HSCREEN hScreen );
void			ScrnLoadDef( HSCREEN hScreen, SCREENDEF* pScreenDef );
BOOL			ScrnInsertScreenObj( HSCREEN hScreen, HSCREENOBJ hScreenObj );
void			ScrnForceUpdate( void );

void			ScrnInitCampaigns( HSCREEN hScreen );
void			ScrnInitMoreCampaigns( HSCREEN hScreen );
LONG			ScrnSelectCampaign( HSCREENBTN hScreenBtn );
LONG			ScrnSelectMission( HSCREENBTN hScreenBtn );
void			ScrnInitMissions( HSCREEN hScreen );
void			ScrnLoadStatValue( HSCREENOBJ hScreenObj, int nValue );

LONG			ScrnWhatIsNext( void );

LONG			ScrnOnPlayerNameDelete( HSCREENBTN hScreenBtn );
void			ScrnColorButtonUpdate( HSCREEN hScreen );
void			ScrnLEDUpdate( HSCREEN hScreen );
void			ScrnPlayerNamesUpdate( HSCREEN hScreen );
void			ScrnMapUpdateHost( HSCREEN hScreen );
int				ScrnMapUpdateRemote( HSCREEN hScreen );
void			ScrnReleaseRules( void );
void			ScrnDisplayChatReceive( HSCREEN hScreen );
void			ScrnUpdateRules( BOOL ForceReadRules );
void			ScrnDisplayRules( HSCREEN hScreen );
BOOL			ScrnMultiPlayerSpclUpdate( HSCREEN hScreen );
void			ScrnMultiPlayerDisplay( HSCREEN hScreen );
int				ScrnVerifyMap( SOBJIMAGEDEF* pMapImage );
void			ScrnReceiveChatMessage(char *message);
BOOL			ChatHandleKey(UINT character);  //returns true if the character was used
int				MessageFormat(RECT* pRect, char *message, int nMaxLength, COLORREF nColor, int nFontID );

void CALLBACK	ScrnTick( void );
void			ScrnLoadJoystickConfiguration( HSCREEN hScreen, CONFIG eConfigType, BOOL bUseOffset );
void			ScrnLoadSargeKeycode( HSCREENOBJ hScreenObj, CONFIG eConfigType, int nKeyIndex );
void			ScrnLoadGameKeycode( HSCREENOBJ hScreenObj, CONFIG eConfigType, int nKeyIndex );
LONG			ScrnOnConfigBack( HSCREENBTN hScreenBtn );
LONG			ScrnOnJoystickConfigBack( HSCREENBTN hScreenBtn );
char*			ScrnFindSargeDesc( BYTE nKeyCode, CONFIG eConfigType );
char*			ScrnFindGameDesc( BYTE nKeyCode, CONFIG eConfigType );

int				ScrnReportMapError( int error );
BOOL			ReadRules(const char *FileName);
void			CopyBaseFileName( char *dest, const char *src);
void			RemoveLF(char *str);
void			ScrnVerifyUpdate( void );
LONG			ScrnOnPlayerNameNext( HSCREENBTN hScreenBtn );

void			ScrnDump( void );
void			ScrnSetMusic( SCRN_STATE eScrnState );

extern void VehicleSoundOff();
extern			char	AIfileName[];

//================================================================
//			FULL SCREEN Routines
//================================================================

//========================================================================
//	Function:		ScrnInit()
//
//	Description:
//		Initalize the Full Screen UI processing.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

BOOL	ScrnInit( void )
{
	SCRNloadMap[0]    = '\0';
	SCRNrules[0]      = '\0';
	SCRNrulesTitle[0] = '\0';

	SObjInit();

	return( FALSE );
}

//========================================================================
//	Function:		ScrnExit()
//
//	Description:
//		terminate and clear the Full Screen UI processing.
//
//	Input:			none
//
//	Ouput:			none
//
//========================================================================

void	ScrnExit( void )
{
	// release any rules data
	ScrnReleaseRules( );

	// delete any residual screen
	if ( SCRNfullScreen )
	{
		// delete any residual Objects and Buttons
		SObjExit();

		free((void*)SCRNfullScreen);
		SCRNfullScreen = NULL;
	}

	// free up any specially created buttons
	SBtnSpclFree();
}

//========================================================================
//	Function:		ScrnSetState()
//
//	Description:
//		set a new screen state.
//
//	Input:			eNewState		new screen state
//
//	Ouput:			none
//
//========================================================================

void	ScrnSetState( SCRN_STATE eNewState )
{
	SCRN_STATE	eCurrentState = SCRN_NULL_STATE;

	// call the termination callback for the current state
	if ( SCRNfullScreen )
	{
		eCurrentState = SCRNfullScreen->eState;

		if ( SCRNstateTable[ eCurrentState ].pTerminateCallback )
			SCRNstateTable[ eCurrentState ].pTerminateCallback( &SCRNfullScreen );
		if ( SCRNfullScreen )
			SCRNfullScreen->ePrevState = eCurrentState;
	}

#ifdef AUDIO_DBG
	TRACE( "Scrn State (Prev) = %s (New) = %s\n",
		ScrnGetStateName(eCurrentState), ScrnGetStateName(eNewState) );
#endif

	// now initialized the new state
	if ( eNewState != SCRN_NULL_STATE )
	{
		if ( SCRNstateTable[ eNewState ].pInitCallback )
			SCRNstateTable[ eNewState ].pInitCallback( &SCRNfullScreen );
	}

	if ( SCRNfullScreen )
		SCRNfullScreen->eState = eNewState;
}

//========================================================================
//	Function:		ScrnGetState()
//
//	Description:
//		retrieve the current screen state.
//
//	Input:			none
//
//	Ouput:			eState			current screen state
//
//========================================================================

SCRN_STATE	ScrnGetState( void )
{
	SCRN_STATE	eState = SCRN_TITLE_STATE;
	if ( SCRNfullScreen )
		eState = SCRNfullScreen->eState;

	return( eState );
}

//========================================================================
//	Function:		ScrnCreate()
//
//	Description:
//		Create an instance of a UI Full Screen.
//
//	Input:			pPoint			Upper Lefthand coordinate of the Screen to
//										be created.
//					bAttributes		Attributes to be applied to this new Screen.
//
//	Ouput:			SCRNfullScreen	handle to new screen object,
//										NULL otherwise
//
//========================================================================

HSCREEN		ScrnCreate( SPOINT* pPoint, USHORT bAttributes )
{
	SCREEN*				pScreen     = NULL;

	// first malloc a screen
	pScreen = (SCREEN*)malloc( sizeof ( SCREEN ) );
	if ( pScreen == NULL )
	{
		// error malloc failed
		TRACE( "ScrnCreate(): malloc failure [%s : %d]\n", __FILE__, __LINE__ );
		goto exit;
	}
#ifdef SBTN_DEBUG
TRACE( "ScrnCreate: MALLOC (%08x)\n", pScreen );
#endif
	ZeroMemory( (void*)pScreen, sizeof( SCREEN ) );

	// initialize the buttons status structure elements
	pScreen->bAttributes = bAttributes;
	ScrnSetPosition( pScreen, pPoint );
	pScreen->bUpdate     = TRUE;
	SCRNfullScreen       = pScreen;

exit:
	return( SCRNfullScreen );
}

//========================================================================
//	Function:		ScrnDelete()
//
//	Description:
//		Delete a UI Full Screen instance.
//
//	Input:			hScreen			handle to screen to be deleted
//
//	Ouput:			none
//
//========================================================================

BOOL		ScrnDelete( HSCREEN hScreen )
{
	int			nObject;
	BOOL		bError = TRUE;

	if ( !hScreen ) return( FALSE );

#ifdef SBTN_DEBUG
	TRACE( "ScrnDelete( %08x ):\n", hScreen );
	SBtnDumpAll();
#endif

	// now remove all the screen objects
	for( nObject=0; nObject<hScreen->nNumberObjs; ++nObject )
	{
		bError = SObjDelete( hScreen->pScreenObjs[ nObject ] );
		if ( bError )
			goto exit;
		else
			hScreen->pScreenObjs[ nObject ] = NULL;
	}

	// now free the screen object
#ifdef SBTN_DEBUG
TRACE( "ScrnDelete:     FREE (%08x)\n", hScreen );
#endif
	free( hScreen );

	bError = FALSE;
exit:
	return( bError );
}

//========================================================================
//				SCREEN ACCESS ROUTINES
//========================================================================

BOOL	ScrnSetAttributes( HSCREEN hScreen, USHORT bAttributes )
{
	if ( !hScreen ) return( TRUE );

	if ( bAttributes )
		hScreen->bAttributes |= bAttributes;
	else
		hScreen->bAttributes = SCRN_CLEAR;

	return( FALSE );	// no error
}

USHORT	ScrnGetAttributes( HSCREEN hScreen )
{
	if ( !hScreen ) return( 0 );

	return( hScreen->bAttributes );
}

BOOL	ScrnHaveAttributes( HSCREEN hScreen, USHORT bAttributesMask )
{
	BOOL	bHaveThem = FALSE;

	if ( !hScreen ) return( bHaveThem );

	if ( bAttributesMask )
	{
		if ( (hScreen->bAttributes & bAttributesMask) == bAttributesMask )
			bHaveThem = TRUE;
	}
	else
	if ( hScreen->bAttributes == SCRN_CLEAR )	// bAttributesMask = 0 = SCRN_CLEAR
		bHaveThem = TRUE;

	return( bHaveThem );
}

BOOL	ScrnSetBGColor( HSCREEN hScreen, SCRN_COLOR eColor )
{
	BOOL	bError = TRUE;

	if ( !hScreen ) return( bError );

	hScreen->eBGColor = eColor;
	bError            = FALSE;

	return( bError );
}

SCRN_COLOR	ScrnGetBGColor( HSCREEN hScreen )
{
	if ( !hScreen ) return( (SCRN_COLOR)0 );

	return( hScreen->eBGColor );
}

BOOL	ScrnSetBkg( HSCREEN hScreen, SCREENDEF* pScreenDef )
{
	BOOL	bError = TRUE;

	if ( !hScreen ) return( bError );
	ASSERT ( ((hScreen->bAttributes & SCRN_BKG_TYPE) == SCRN_BKG_TYPE) );

	bError = ScrnSetReference( hScreen, pScreenDef->bkgRef );

	return( bError );
}

SPRITE*	ScrnGetBkg( HSCREEN hScreen )
{
	if ( !hScreen ) return( NULL );

	return( hScreen->pBkgSprite );
}

BOOL	ScrnSetArea( HSCREEN hScreen, SCREENDEF* pScreenDef )
{
	if ( !hScreen ) return( TRUE );
	ASSERT ( ((hScreen->bAttributes & SCRN_AREA_TYPE) == SCRN_AREA_TYPE) );

	hScreen->BkgBox.x  = pScreenDef->bkgBox.x;
	hScreen->BkgBox.y  = pScreenDef->bkgBox.y;
	hScreen->BkgBox.cx = pScreenDef->bkgBox.cx;
	hScreen->BkgBox.cy = pScreenDef->bkgBox.cy;

#ifdef	SCREEN_DEBUG
TRACE( "ScrnSetArea (%s)edit: BkgBox (%d,%d,%d,%d )\n",
		hScreen->BkgBox.x,    hScreen->BkgBox.y,
		hScreen->BkgBox.cx,   hScreen->BkgBox.cy
	 );
#endif

	return( FALSE );
}

SBOX*	ScrnGetArea( HSCREEN hScreen )
{
	if ( !hScreen ) return( NULL );

	return( &(hScreen->BkgBox) );
}

BOOL	ScrnSetPosition( HSCREEN hScreen, SPOINT* pPosition )
{
	if ( !hScreen ) return( TRUE );
	if ( !pPosition ) return( TRUE );

	hScreen->position.x   = pPosition->x;
	hScreen->position.y   = pPosition->y;

	return( FALSE );	// no error
}

SPOINT*	ScrnGetPosition( HSCREEN hScreen )
{
	if ( !hScreen ) return( NULL );

	return( &(hScreen->position) );
}

//========================================================================
//					SCREEN UTILITY ROUTINES
//========================================================================

BOOL	ScrnSetReference( HSCREEN hScreen, char* pScreenRef )
{
	SBOX*	pBox;
	char*	pReference;
	int		len = 0;
	BOOL	bError = TRUE;

	if ( !hScreen ) return( bError );
	ASSERT( ((hScreen->bAttributes & SCRN_BKG_TYPE) == SCRN_BKG_TYPE) );

	// NOTE: the user sends in a NULL pScreenRef when they want to use
	// the currently active BKG. Simple acquire the BKG box size from
	// the sprite in this case.
	pReference = hScreen->BkgRef;
	pBox       = &(hScreen->BkgBox);
	if ( !pScreenRef )	// asked to use exiting screen BKG
	{
		// acquire the BKG sprite and area
		hScreen->pBkgSprite = BackgroundSize( pBox );
		if ( !(hScreen->pBkgSprite) )
		{
			// error: failed to acquire bkg size
			TRACE( "ERROR: failed to acquire Bkg size [%s : %d]\n",
					__FILE__, __LINE__ );
			goto exit;
		}
	}
	else
	{
		// free up any exisiting sprite
		if ( pReference && *pReference )
		{
			FreeBackground();
			*pReference = '\0';
		}

		len = strlen( pScreenRef );
		if ( len > SCRN_MAX_TEXT_LEN )
			len = SCRN_MAX_TEXT_LEN;
		if ( len )
			strcpy(pReference, pScreenRef);
		pReference[len] = '\0';

		// now load the background
		hScreen->pBkgSprite = LoadBackground( pReference, TRUE );
		if ( hScreen->pBkgSprite )
		{
			// acquire the area for this bkg
			if ( SpriteBox( hScreen->pBkgSprite, pBox ) )
			{
				// error: failed to acquire bkg size
				TRACE( "ERROR: failed to acquire Bkg size [%s : %d]\n",
						__FILE__, __LINE__ );
				goto exit;
			}
		}
	}

	bError           = FALSE;
	hScreen->bUpdate = TRUE;

exit:
	return( bError );	// no error
}

void	ScrnReload( void )
{
	if ( SCRNfullScreen )
		ScrnDisplay( SCRNfullScreen );
}

LONG	ScrnDisplay( HSCREEN hScreen )
{
	SBOX*				pBox;
	HSCREENOBJ			hScreenObj;
	int					nObject;
	BOOL				bUpdate = FALSE;

	if ( !hScreen ) return( bUpdate );

	// start by displaying the background and get the box for this object
	pBox = ScrnDisplayBkg( hScreen );

	// if this is a multiplayer game, check for special updates
	if ( (ScrnGetState() == SCRN_MULTI_HOST_STATE) || (ScrnGetState() == SCRN_MULTI_REMOTE_STATE) )
	{
		if ( ScrnMultiPlayerSpclUpdate( hScreen ) )
			bUpdate = TRUE;
	}

	// now display all the screen objects in this screen
	for( nObject=0; nObject<hScreen->nNumberObjs; ++nObject )
	{
		hScreenObj = hScreen->pScreenObjs[ nObject ];
		if ( hScreenObj )
			SObjDisplay( hScreenObj );
	}

	// if this is a multiplayer game, check for special updates
	if ( (ScrnGetState() == SCRN_MULTI_HOST_STATE) || (ScrnGetState() == SCRN_MULTI_REMOTE_STATE) )
	{
		if ( bUpdate )
			ScrnMultiPlayerDisplay( hScreen );
	}

	if (!hScreen->dialog)
		CursorOn();

	// clear the button update flag: button updated
	hScreen->bUpdate = FALSE;

	if (bAudioRecall) 
		MsgMissionEnd(gpGame->winner, gpGame->GameType == GAMETYPE_ONEPLAYER);
	bAudioRecall = FALSE;

	return( 0 );
}

LONG	ScrnUpdate( HSCREEN hScreen )
{
	HSCREENOBJ	hScreenObj;
	int			nObject;
	BOOL		bStateChange;

	if ( !hScreen ) return( 0 );

	// check to see if we can start the mulitplayer game
	if ( ScrnGetState() == SCRN_MULTI_HOST_STATE )
		SCRNmultiStartOK = gpComm->EverybodyHasMap();

	// now display all the screen objects in this screen
	nObject      = 0;
	bStateChange = FALSE;
	while ( !bStateChange && (nObject<hScreen->nNumberObjs) )
	{
		hScreenObj = hScreen->pScreenObjs[ nObject ];
		if ( hScreenObj )
			bStateChange = SObjUpdate( hScreenObj );
		++nObject;
	}

	return( 0 );
}

BOOL	ScrnInEditMode( void )
{
	int			nNumObjects;
	int			nObject;
	HSCREEN		hScreen;
	HSCREENOBJ	hScreenObj;
	BOOL		bInEditMode = FALSE;

	hScreen = SCRNfullScreen;
	if ( hScreen )
	{
		nNumObjects = hScreen->nNumberObjs;
		nObject     = 0;
		bInEditMode = FALSE;
		while ( !bInEditMode && (nObject<nNumObjects) )
		{
			hScreenObj  = hScreen->pScreenObjs[ nObject ];
			bInEditMode = SObjInEditMode( hScreenObj );
			++nObject;
		}
	}

	return( bInEditMode );
}

BOOL	ScrnTerminateEditMode( HSCREENBTN hNextBtn )
{
	SCRN_STATE	eScrnState;
	HSCREENBTN	hScreenBtn;
	BOOL		bDone = FALSE;
	int			len;
	int			nIndex;

	// retrieve the current screen state and clicked button
	eScrnState = ScrnGetState();
	hScreenBtn = SBtnGetCurrentClicked();
	if ( !hScreenBtn )
		return( bDone );

	switch ( eScrnState )
	{
	case SCRN_SELECT_CALLSIGN_STATE:	// One Player player name selection
		if ( ScrnInEditMode() )
		{
			// make sure the name string isn't NULL
			bDone = TRUE;
			len = strlen( hScreenBtn->pText ) - 1;	// minus 1 for the underscore

			// strip the underscore cursor
			if ( hScreenBtn->pText[len] == '_' )
				hScreenBtn->pText[len] = '\0';
			else
				++len;

			if ( len <= 0 )
			{
#if 1
				bDone = TRUE;
				strcpy( hScreenBtn->pText, NEWPLAYER_TextBtn );

				// turn off the user key input processing
				SBtnTurnOffKeys( hScreenBtn );

				// set the button to FOCUSED state
				if ( SBTNcurrentClicked )
					SBTNcurrentClicked->eScreenBtnState = BUTTON_FOCUSED;
//					SBtnSetState( SBTNcurrentClicked, BUTTON_FOCUSED );
				SBTNcurrentClicked = NULL;

				return( bDone );
#else
				bDone = TRUE;
				strcpy( hScreenBtn->pText, NEWPLAYER_TextBtn );
				strcat( hScreenBtn->pText, "_" );
				hScreenBtn->bUpdate = TRUE;
				return( bDone );
#endif
			}
			else
			if ( strncmp( hScreenBtn->pText, NEWPLAYER_TextBtn, NEWPLAYER_BtnSize ) == 0 )
			{
				bDone = TRUE;

				// turn off the user key input processing
				SBtnTurnOffKeys( hScreenBtn );

				// set the button to FOCUSED state
				if ( SBTNcurrentClicked )
					SBtnSetState( SBTNcurrentClicked, BUTTON_FOCUSED );
				SBTNcurrentClicked = NULL;

				return( bDone );
			}
			else	// verify that this new name doesn't already exist
			if ( StatsHaveName( hScreenBtn->pText ) )
			{
				bDone = FALSE;
				strcpy( hScreenBtn->pText, "Exists_" );
				hScreenBtn->bUpdate = TRUE;
			}
			else
			{
				bDone = TRUE;

				// turn off the user key input processing
				SBtnTurnOffKeys( hScreenBtn );
			}
		}
		else
		{
			if ( hNextBtn )
				bDone = TRUE;
		}

		if ( hNextBtn )
		{
			if ( (hNextBtn->pClickedCallback == ScrnPlayerName) || (hNextBtn->pClickedCallback == ScrnOnPlayerNameDelete) || (hNextBtn->pClickedCallback == ScrnOnBack) )
				bDone = FALSE;
		}

		if ( bDone || !hNextBtn )
		{
			// copy the current player name into the permanent set
			nIndex = hScreenBtn->dwData;
			StatSetPlayerNameIndex( nIndex );
			strcpy( STATcurrentName, hScreenBtn->pText );
			strcpy( STATplayerNames[ nIndex ], STATcurrentName );
			StatUpdate( nIndex, STAT_UPDATE_PLAYER_NAME, TRUE );

			if ( hScreenBtn->pEditCallback )
				hScreenBtn->pEditCallback( hScreenBtn );

			// turn off the user key input processing
			SBtnTurnOffKeys( hScreenBtn );

			hScreenBtn->hPrevClicked = hScreenBtn;

			ScrnOnPlayerNameNext( hScreenBtn );

			ScrnForceUpdate();
		}
		else
			bDone = FALSE;
		break;

	case SCRN_MULTI_HOST_STATE:			// Multi Player HOST campaign selection
	case SCRN_MULTI_REMOTE_STATE:		// Multi Player REMOTE campaign selection
		if ( ScrnInEditMode() )
		{
			// terminate chat mode
			SBtnChatTurnOffKeys( hScreenBtn );
			ScrnForceUpdate();

			bDone = TRUE;
		}
		break;
	case SCRN_CUSTOM_STATE:				// User Custom configuration
	case SCRN_JOYSTICK_STATE:			// User Joystick configuration
		if ( ScrnInEditMode() )
		{
			// terminate chat mode
			SBtnKeycodeTurnOffKeys( hScreenBtn );
			ScrnForceUpdate();

			bDone = TRUE;
		}
		break;
	}
	return( bDone );
}

SBOX*	ScrnDisplayBkg( HSCREEN hScreen )
{
	SCRN_COLOR	bkgColor;
	COLORREF	rgbColor;
	RECT		Rect;
	char*		pScreenRef;
	SPRITE*		pScreenBkg;
	SBOX*		pBox = NULL;

	if ( !hScreen ) return( pBox );

	// get the display box for this screen
	pBox = &(hScreen->BkgBox);
	if ((hScreen->bAttributes & SCRN_BKG_TYPE) == SCRN_BKG_TYPE)
	{
		// acquire the image data
		if ( hScreen->bUpdate )
		{
			pScreenRef = hScreen->BkgRef;
			pScreenBkg = hScreen->pBkgSprite;

			// create the object rectangle
			Rect.left   = pBox->x;
			Rect.top    = pBox->y;
			Rect.right  = Rect.left + pBox->cx;
			Rect.bottom = Rect.top + pBox->cy;

			CursorOff(&Rect);

			// draw the image
			DisplaySpriteFront( pScreenBkg, Rect.left, Rect.top );
		}
	}
	else
	if ((hScreen->bAttributes & SCRN_BKG_TYPE) != SCRN_BKG_TYPE)
	{
		if ( hScreen->bUpdate && ((hScreen->bAttributes & SCRN_TRANSPARENT) != SCRN_TRANSPARENT) )
		{
			// create the object rectangle
			Rect.left   = pBox->x;
			Rect.top    = pBox->y;
			Rect.right  = Rect.left + pBox->cx;
			Rect.bottom = Rect.top + pBox->cy;

			// now acquire the rectangle color
			bkgColor    = hScreen->eBGColor;
			if ( bkgColor != SBTN_TRANSPARENT )
			{
				CursorOff(&Rect);

				rgbColor = SBTNcolorTable[bkgColor];

				// draw the rectangle (opaque, translucent, or transparent)
				FillRectFront( &Rect, rgbColor );	// filled rectangle
			}
		}
	}
	else
		pBox = NULL;

	// return the box
	return( pBox );
}

BOOL	ScrnUpdateCheck( HSCREEN hScreen )
{
	if ( !hScreen ) return( FALSE );

	return( hScreen->bUpdate );
}

void	ScrnLoadDef( HSCREEN hScreen, SCREENDEF* pScreenDef )
{
	SCREENOBJDEF*	pScreenObjDef;
	HSCREENOBJ		hScreenObj;
	SBOX			parentBox;
	int				nObject;

	// set up the screen area
	if ( (hScreen->bAttributes & SCRN_BKG_TYPE) == SCRN_BKG_TYPE )
		ScrnSetBkg( hScreen, pScreenDef );
	else
	if ( (hScreen->bAttributes & SCRN_AREA_TYPE) == SCRN_AREA_TYPE )
		ScrnSetArea( hScreen, pScreenDef );

	for( nObject=0; nObject<pScreenDef->nNumberObjs; ++nObject )
	{
		pScreenObjDef = pScreenDef->pScreenObjDefs[ nObject ];

		parentBox.x   = hScreen->BkgBox.x + hScreen->position.x;
		parentBox.y   = hScreen->BkgBox.y + hScreen->position.y;
		parentBox.cx  = hScreen->BkgBox.cx;
		parentBox.cy  = hScreen->BkgBox.cy;

		hScreenObj    = SObjCreate( &(pScreenObjDef->position),
									pScreenObjDef->bAttributes,
									&(parentBox) );
		ASSERT( hScreenObj );
		SObjLoadDef( hScreenObj, pScreenObjDef );
		ScrnInsertScreenObj( hScreen, hScreenObj );
	}

	hScreen->bUpdate = TRUE;
}

BOOL	ScrnInsertScreenObj( HSCREEN hScreen, HSCREENOBJ hScreenObj )
{
	BOOL	bError = TRUE;		// assume an error

	if ( !hScreen ) return( bError );
	if ( !hScreenObj ) return( bError );

	// make sure we aren't full already
	if ( (hScreen->nNumberObjs) >= SCRN_MAX_OBJS )
	{
		TRACE( "ERROR: max screenObj limit (SCRN_MAX_OBJS=%d) exceeded\n",
				SCRN_MAX_OBJS );
		ASSERT(0);
	}

	// insert the object
	hScreen->pScreenObjs[ hScreen->nNumberObjs ] = hScreenObj;
	++(hScreen->nNumberObjs);

	// make sure this screen and this object get displayed
	hScreen->bUpdate    = TRUE;
	hScreenObj->bUpdate = TRUE;

	// we were successful
	bError = FALSE;

	return( bError );
}

void MapError(CString filename, HSCREENBTN hScreenBtn)	{
	CString		error;

	gameQuiet();
	error = "ERROR: ";
	error += filename;
	error += " does not exist\n";
	pMainFrame->OnErrorDialog2(error, FALSE);
	SBtnSetState(hScreenBtn, BUTTON_NULL);
	ScrnForceUpdate();
	gameNoisy();
}


BOOL CD_OK(HSCREENBTN hScreenBtn)	{
	BOOL done = FALSE;

#ifndef FINAL
	if (!no_cd_ok)
#endif
	{
		gameQuiet();
		while (!done)	{
			if (gPaths.LocateCdromDrive() != LCD_NO_ERROR )	{
				if (pMainFrame->OnErrorDialog(NoCD_Text, FALSE) != 0)	{
					done = TRUE;
					SBtnSetState(hScreenBtn, BUTTON_NULL);
					ScrnForceUpdate();
					gameNoisy();
					return FALSE;
				}
			}
			else
				done = TRUE;
		}
		gameNoisy();
	}
	return TRUE;
}

//================================================================
//					GAME START SCREEN FUNCTIONS
//================================================================

LONG	ScrnOnBootCamp( HSCREENBTN hScreenBtn )
{
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	char			buffer[64];

	if (!CD_OK(hScreenBtn))
		return( SBTN_STATE_CHANGE );

	// turn off the title music
	TitleMusic( TRUE );

	// load in the BootCamp campaign data
	SetPath(CAMPAIGN_PATH);
	AiCampaignLoad( "BootCamp.cpn" );

	// indicate that we are in a ONE PLAYER type of game
	gpGame->GameType    = GAMETYPE_ONEPLAYER;

	// set the global indexcies and references
	g_MissionIndex  = 0;
	g_ScenarioIndex = 0;
	g_CampaignIndex = 0;

	SCRNcampaign       = g_Campaigns[ g_CampaignIndex ];
	gpGame->CampaignID = SCRNcampaign->nCampaignID;
	pScenario          = &(SCRNcampaign->pScenarios[ g_ScenarioIndex ]);
	gpGame->ScenarioID = pScenario->nScenarioID;
	pMission           = &(pScenario->pMissions[ g_MissionIndex ]);
	gpGame->MissionID  = pMission->nMissionID;

	gpGame->newMission = TRUE;
	gpGame->BootCamp   = TRUE;

	// now acquire the Boot Camp Map
	strcpy(buffer, pMission->pFileName);
	strcat( buffer, ".AMM" );
	gpGame->MapName = buffer;

	SetPath(MAP_PATH);
	if (FileExist(gpGame->MapName))	{

		// clear the SCREEN state
		ScrnSetState( SCRN_NULL_STATE );

		// clear the front buffer
		EraseVisibleSurface();

		// now go wait for others to join
		pMainFrame->StartGame();	// start the game
	}
	else	{
		MapError(gpGame->MapName, hScreenBtn);
	}

	return( SBTN_STATE_CHANGE );
}


LONG	ScrnOnOnePlayer( HSCREENBTN hScreenBtn )
{
	if (!CD_OK(hScreenBtn))
		return( SBTN_STATE_CHANGE );

	// disable any further clicks of this button
	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// setup to enter the player name (callsign)
	ScrnSetState( SCRN_SELECT_CALLSIGN_STATE );

	// indicate that we are in a ONE PLAYER type of game
	gpGame->GameType    = GAMETYPE_ONEPLAYER;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnMultiPlayer( HSCREENBTN hScreenBtn )
{
	int	result = IDCANCEL;

	// force the current map name to be NULL
	// gpGame->MapName = "\0";

	SCRNfullScreen->dialog = TRUE;
	pMainFrame->PauseFlip();

	// make sure we're connected
	audioDisable();	// disable all audio
	if ( gpComm->IsConnected() == FALSE )
		result = pMainFrame->OnServiceProviderDialog();
	else
	if ( gpComm->IsInSession() == FALSE )
		result = pMainFrame->OnGameSetupDialog();
	else
		result = ID_NEXT;
	audioEnable( pMainFrame->m_hWnd );		// start up audio again

	SCRNfullScreen->dialog = FALSE;
	pMainFrame->UnPauseFlip();

	if ( result == ID_NEXT )
	{
		if ( gpComm->m_bHost )
		{
			// host a battle
			gpGame->GameType = GAMETYPE_HOST_MULTIPLAYER;
			ScrnSetState( SCRN_MULTI_HOST_STATE );
		}
		else
		{
			// join a battle
			gpGame->GameType = GAMETYPE_REMOTE_MULTIPLAYER;
			ScrnSetState( SCRN_MULTI_REMOTE_STATE );
		}
	}
	else
	{
		// decided not to play
		ScrnSetState( SCRN_TITLE_STATE );
	}

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnOptions( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_OPTIONS_STATE );

	return( SBTN_STATE_CHANGE );
}

void	Scrn_KDn_Options( UINT nChar, UINT nFlags )
{
	if( gpGame->GetSubState() == PLAY_SETUP_SUB_STATE )
	{
		if( UI_CurMode == UIMODE_PLACINGITEM )
		{
			UI_PutItemBackInTray();
			return;
		}
	}

	if ( ScrnOptionsVisible() )
	{
		// unpause this screen and notify others
		gpGame->UnPauseGame( PAUSE_LOCAL );
		if ( gpGame->GameType != GAMETYPE_ONEPLAYER )
			SendGamePause(FALSE, PAUSE_LOCAL);

		ScrnOnPlayBack( (HSCREENBTN)NULL);
	}
	else
	{
		ScrnSetState( SCRN_PLAY_OPTIONS_STATE );

		pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
		pMainFrame->SetUIOverride(KeyOverride_CHEATS);
		pMainFrame->PausePageFlip();

		ClearCheat();

		// now copy the back buffer into the front to restore
		// the last played background
		DDCopyBackToFront();

		// set the local and remote pause
		gpGame->PauseGame( PAUSE_LOCAL );
		if ( gpGame->GameType != GAMETYPE_ONEPLAYER )
			SendGamePause(TRUE, PAUSE_LOCAL);

		VehicleSoundOff();
		ShowTheCursor( TRUE );
	}
}


LONG	ScrnOnQuit( HSCREENBTN hScreenBtn )
{
	// turn off all audio streams and voice
	StopAllStreams();

	// clear the current screen state
	ScrnSetState( SCRN_NULL_STATE );

	// disable user-interface...
	pMainFrame->SetUI(NULL);									
	pMainFrame->SetUIOverride(NULL);
	pMainFrame->UnPausePageFlip();

	// clear the surfaces
	EraseSurfaces();

	// send off the close message
	pMainFrame->PostMessage(WM_CLOSE, 0, 0);

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnBack( HSCREENBTN hScreenBtn )
{
	SCRN_STATE	eScrnState;

	// turn off all audio streams and voice
	StopAudioData();
	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		// now copy the back buffer into the front to restore
		// the last played background
		DDCopyBackToFront();
	}

#if 0
	eScrnState = ScrnGetState();
	if ( eScrnState != SCRN_NULL_STATE )
		TRACE( "ScrnOnBack() from %s to: \n", SCRNstateName[ eScrnState ] );
	else
		TRACE( "ScrnOnBack() from SCRN_NULL_STATE to: \n" );
#endif

	// apply the new screen state
	eScrnState = (SCRN_STATE)(hScreenBtn->dwData);
	ScrnSetState( eScrnState );
	ScrnSetMusic( eScrnState );

#if 0
	if ( eScrnState != SCRN_NULL_STATE )
		TRACE( "%s\n", SCRNstateName[ eScrnState ] );
	else
		TRACE( "SCRN_NULL_STATE\n" );
#endif


	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnConfigBack( HSCREENBTN hScreenBtn )
{
	SCRN_STATE	eScrnState;

	// reset the key bindings, we've effectively issued a CANCEL
	eScrnState = ScrnGetState();
	if ( eScrnState == SCRN_CUSTOM_STATE)
		LoadKeyBindings( CONFIG_CUSTOM );

	// make sure we restore the background
	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		// now copy the back buffer into the front to restore
		// the last played background
		DDCopyBackToFront();
	}

	// apply the new screen state
	eScrnState = (SCRN_STATE)(hScreenBtn->dwData);
	ScrnSetState( eScrnState );
	ScrnSetMusic( eScrnState );

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnJoystickConfigBack( HSCREENBTN hScreenBtn )
{
	SCRN_STATE	eScrnState;

	// reset the key bindings, we've effectively issued a CANCEL
	LoadKeyBindings( CONFIG_JOYSTICK );

	// make sure we restore the background
	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		// now copy the back buffer into the front to restore
		// the last played background
		DDCopyBackToFront();
	}

	// apply the new screen state
	eScrnState = (SCRN_STATE)(hScreenBtn->dwData);
	ScrnSetState( eScrnState );
	ScrnSetMusic( eScrnState );

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnPlayBack( HSCREENBTN hScreenBtn )
{
	ShowTheCursor(FALSE);

	// now copy the back buffer into the front to restore
	// the last played background
	DDCopyBackToFront();
    gpGame->UnPauseGame(PAUSE_LOCAL);
 	if ( gpGame->GameType != GAMETYPE_ONEPLAYER )
			SendGamePause(FALSE, PAUSE_LOCAL);

	// apply the new screen state
	if (hScreenBtn)
		ScrnSetState( (SCRN_STATE)(hScreenBtn->dwData) );

	// disable user-interface...
	if( gpGame->GetSubState() == PLAY_SETUP_SUB_STATE )
		pMainFrame->SetUI(&UI_GAME_SETUP_STATE);
	else
		pMainFrame->SetUI(&UI_GAME_PLAY_STATE);
	pMainFrame->SetUIOverride(NULL);
	pMainFrame->UnPausePageFlip();

	MissionMusic( FALSE );

	gpGame->nPauseDelay = GetTickCount() + 100;
	MouseDown0 = FALSE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnApply( HSCREENBTN hScreenBtn )
{
	SCRN_STATE	eScrnState;


	ShowTheCursor( FALSE );

	// now copy the back buffer into the front to restore
	// the last played background
	DDCopyBackToFront();

	// get the current screen state to decide the proper
	// processor
	eScrnState = ScrnGetState();
	switch( eScrnState )
	{
	case SCRN_KEYPAD_STATE:		// User Keypad configuration
		SelectKeyBindings( CONFIG_DEFAULT1 );
		break;
	case SCRN_KEYBOARD_STATE:	// User KeyBoard configuration
		SelectKeyBindings( CONFIG_DEFAULT2 );
		break;
	case SCRN_CUSTOM_STATE:		// User Custom configuration
		SaveKeyBindings( CONFIG_CUSTOM );
		SelectKeyBindings( CONFIG_CUSTOM );
		break;
	default:
		return( SBTN_STATE_CHANGE );
	}

	CopyKeyBindingsToSetup();

	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		ScrnSetState( SCRN_PLAY_OPTIONS_STATE );
		gameNoisy();	// turn on all the audio
	}
	else
		ScrnSetState( SCRN_OPTIONS_STATE );

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnRestoreKB( HSCREENBTN hScreenBtn )
{
	RestoreDefaultBindings( CONFIG_DEFAULT1 );
	ScrnForceUpdate();
	SBtnSetState( hScreenBtn, BUTTON_NULL );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnRestoreKP( HSCREENBTN hScreenBtn )
{
	RestoreDefaultBindings( CONFIG_DEFAULT2 );
	ScrnForceUpdate();
	SBtnSetState( hScreenBtn, BUTTON_NULL );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnRestoreJoystick( HSCREENBTN hScreenBtn )
{
	RestoreDefaultBindings( CONFIG_JOYSTICK );
	ScrnForceUpdate();
	SBtnSetState( hScreenBtn, BUTTON_NULL );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnCancel( HSCREENBTN hScreenBtn )
{
	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		// turn on all the audio
		gameNoisy();
		ScrnSetState( SCRN_NULL_STATE );
	}
	else
	{
		ScrnSetState( SCRN_TITLE_STATE );
		gpGame->SetSubState(NULL_SUB_STATE);
		gpGame->SetState( GAME_TITLE_SCREEN_STATE );
	}

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnJoystickApply( HSCREENBTN hScreenBtn )
{
	SaveKeyBindings( CONFIG_JOYSTICK );		// save off these keycodes
	LoadKeyBindings( CONFIG_JOYSTICK );

	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		ScrnSetState( SCRN_PLAY_OPTIONS_STATE );
		gameNoisy();	// turn on all the audio
	}
	else
		ScrnSetState( SCRN_OPTIONS_STATE );

	return( SBTN_STATE_CHANGE );
}

//================================================================
//					STATE FUNCTIONS
//================================================================

void	ScrnDoDisplay( void )
{
	SCRN_STATE	eCurrentState;

	if ( !SCRNfullScreen ) return;

	// now verify the updateability of the screen
//	ScrnVerifyUpdate();

	// call the termination callback for the current state
	eCurrentState = SCRNfullScreen->eState;
	if ( SCRNstateTable[ eCurrentState ].pDisplayCallback )
		SCRNstateTable[ eCurrentState ].pDisplayCallback( SCRNfullScreen );

	DrawCursor();
}

void	ScrnDoActions( void )
{
	SCRN_STATE	eCurrentState;

	if ( !SCRNfullScreen ) return;

	// call the termination callback for the current state
	eCurrentState = SCRNfullScreen->eState;
	if ( SCRNstateTable[ eCurrentState ].pUpdateCallback )
		SCRNstateTable[ eCurrentState ].pUpdateCallback( SCRNfullScreen );
}

void	ScrnTerminate( SCRN_STATE eState )
{
	// call the termination callback for the current state
	if ( SCRNstateTable[ eState ].pTerminateCallback )
		SCRNstateTable[ eState ].pTerminateCallback( &SCRNfullScreen );
}

LONG	ScrnNOOP( HSCREEN* hScreen )
{
	return( 0 );
}

void	ScrnForceUpdate( void )
{
	int			nObject;
	HSCREENOBJ	hScreenObj;
	HSCREEN     hScreen = SCRNfullScreen;

	if ( hScreen )
	{
		for( nObject=0; nObject<hScreen->nNumberObjs; ++nObject )
		{
			hScreenObj = hScreen->pScreenObjs[ nObject ];
			SObjForceUpdate( hScreenObj );
		}
		hScreen->bUpdate = TRUE;
	}
}

//----------------------------------------------------------------
//		SCREEN	TITLE SCREEN STATE CALLBACKS
//----------------------------------------------------------------

LONG	ScrnInitTitleScreen( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef  = &SCRNtitleScreen;

	gpGame->BootCamp = FALSE;

	// build an screen
	SetPath( SCREEN_PATH );

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	pNewScreen->bUpdate = TRUE;

	*hScreen = pNewScreen;

	SCRNtimerStart = GetTickCount();

	// start the ArmyMen Theme music
	TitleMusic( FALSE );

	ShowTheCursor(TRUE);
	return( 0 );
}

LONG	ScrnTitleUpdate( HSCREEN hScreen )
{
	if ( SCRNtimerStart && ((gpGame->dwSysTime - SCRNtimerStart) > FIVE_SECONDS) )
	{
//		TRACE("Title Screen advancing to Start State...\n" );
		SCRNtimerStart = 0;
		if (gpComm->m_bStartedByLobby)
		{
			// host or join a battle
			gpGame->SetSubState(NULL_SUB_STATE);
			if ( gpComm->m_bHost )
			{
				// host a battle
				gpGame->GameType = GAMETYPE_HOST_MULTIPLAYER;
				ScrnSetState( SCRN_MULTI_HOST_STATE );
			}
			else
			{
				// join a battle
				gpGame->GameType = GAMETYPE_REMOTE_MULTIPLAYER;
				ScrnSetState( SCRN_MULTI_REMOTE_STATE );
			}
		}  else	 ScrnSetState( SCRN_GAME_START_STATE );
	}

	return(0);
}

LONG	ScrnTerminateTitleScreen( HSCREEN* hScreen )
{
	if ( SCRNtimerStart )
		SCRNtimerStart = 0;

	ScrnTerminateScreen( hScreen );
	return 0;
}

//----------------------------------------------------------------
//		SCREEN	PLAYER NAME STATE CALLBACKS
//----------------------------------------------------------------
LONG	ScrnInitPlayerName( HSCREEN* hScreen )
{
	int				nPlayerIndex;
	HSCREEN			pNewScreen;
	HSCREENOBJ		hScreenObj;
	HSCREENBTN		hScreenBtn;
	SCREENDEF*		pScreenDef  = &SCRNplayerNameScreen;

	// build an screen
	SetPath( SCREEN_PATH );

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	// now read from the registry and update any player names
	for( nPlayerIndex=0; nPlayerIndex<SCRN_PLAYER_NAMES; ++nPlayerIndex )
		StatUpdate( nPlayerIndex, STAT_UPDATE_PLAYER_NAME, FALSE );

	// copy the player names into the various buttons
	hScreenObj = pNewScreen->pScreenObjs[0];
	for( nPlayerIndex=0; nPlayerIndex<SCRN_PLAYER_NAMES; ++nPlayerIndex )
	{
		hScreenBtn = hScreenObj->hScreenBtns[ nPlayerIndex ];
		SBtnSetText( hScreenBtn, STATplayerNames[ nPlayerIndex ] );
	}

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor( TRUE );
	return ( 0 );
}

LONG	ScrnOnPlayerNameDelete( HSCREENBTN hScreenBtn )
{
	int			nIndex;
	HSCREENBTN	hPrevBtn;

	// was there a previous clicked button
	if ( hScreenBtn->hPrevClicked )
	{
		hPrevBtn = hScreenBtn->hPrevClicked;
		if ( (hPrevBtn->bAttributes & SBTN_EDIT_TYPE) == SBTN_EDIT_TYPE )
		{
			ScrnDeletePlayerFiles( hPrevBtn->pText );
			strcpy( hPrevBtn->pText, NEWPLAYER_TextBtn );
			strcpy( STATcurrentName, hPrevBtn->pText );
			nIndex = hPrevBtn->dwData;
			strcpy( STATplayerNames[ nIndex ], STATcurrentName );
			StatUpdate( nIndex, STAT_UPDATE_PLAYER_NAME, TRUE );
		}
		SBtnSetState( hPrevBtn, BUTTON_NULL );
		hScreenBtn->hPrevClicked = NULL;
		ScrnForceUpdate();
	}
	SBtnSetState( hScreenBtn, BUTTON_NULL );

	return( 0 );
}

LONG	ScrnOnPlayerNameNext( HSCREENBTN hScreenBtn )
{
	int			nIndex;
	HSCREENBTN	hPrevBtn;

	if ( hScreenBtn->hPrevClicked )
	{
		hPrevBtn = hScreenBtn->hPrevClicked;

		// copy the current player name into the permanent set
		nIndex = StatGetPlayerNameIndex();
		strcpy( STATplayerNames[ nIndex ], STATcurrentName );
		StatUpdate( hScreenBtn->dwData, STAT_UPDATE_PLAYER_NAME, TRUE );
		SBtnSetState( hScreenBtn, BUTTON_NULL );
		ScrnSetState( SCRN_SELECT_CAMPAIGN_STATE );
	}
	else
		SBtnSetState( hScreenBtn, BUTTON_NULL );

	return( SBTN_STATE_CHANGE );
}

//----------------------------------------------------------------
//		SCREEN	SELECT CAMPAIGN STATE CALLBACKS
//----------------------------------------------------------------
LONG	ScrnInitSelectCampaign( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;

#ifdef SBTN_DEBUG
	TRACE( "ScrnInitSelectCampaign( %08x )\n", hScreen );
#endif

	// build an screen
	SetPath( SCREEN_PATH );

	// treat this as a fresh application
	gpGame->HavePlayed = FALSE;

	if ( g_NumberCampaigns && (g_CampaignIndex+4 < g_NumberCampaigns) )
	{
		pScreenDef = &SCRNselectCampaignMoreScreen;
		pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );

		ScrnLoadDef( pNewScreen, pScreenDef );
		ScrnInitMoreCampaigns( pNewScreen );
	}
	else
	{
		pScreenDef = &SCRNselectCampaignScreen;
		pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );

		ScrnLoadDef( pNewScreen, pScreenDef );
		ScrnInitCampaigns( pNewScreen );
	}

	pNewScreen->bUpdate = TRUE;

	*hScreen   = pNewScreen;
	ASSERT( pNewScreen );

	ShowTheCursor(TRUE);
	return ( 0 );
}

LONG	ScrnTerminateSelectCampaign( HSCREEN* hScreen )
{
	// release any residual campaign data
	SObjReleaseCampaignData( );

	// turn off the ArmyMen theme music
	StopAllStreams();

	// clear the screen
	ScrnTerminateScreen( hScreen );
	return( 0 );
}

LONG	ScrnOnCampaignMore( HSCREENBTN hScreenBtn )
{
	int	nNextCampaignIndex = g_CampaignIndex+4;
	// get the current Campaign Index and see which
	// type of campaign Select screen to display
	g_MissionIndex = 0;
	if ( nNextCampaignIndex+4 < g_NumberCampaigns )
	{
		g_CampaignIndex = nNextCampaignIndex;
		ScrnInitMoreCampaigns( SCRNfullScreen );
	}
	else
	{
		ScrnTerminateSelectCampaign( &SCRNfullScreen );
		g_CampaignIndex = nNextCampaignIndex;
		ScrnInitSelectCampaign( &SCRNfullScreen );
	}
	return( 0 );
}

void	ScrnInitCampaigns( HSCREEN hScreen )
{
	int				nButton;
	int				nCampaign;
	HSCREENBTN		hScreenBtn;
	HSCREENOBJ		hScreenObj;

#ifdef SBTN_DEBUG
	TRACE( "ScrnInitCampaigns( %08x )\n", hScreen );
#endif

	// build a screen
	SetPath( SCREEN_PATH );

	// acquire the screenobject
	hScreenObj = hScreen->pScreenObjs[0];

	// now acquire and fill in the campaign names
	nButton = SObjCampaignInit( hScreenObj );

	// set the attributes for all the empyt screen buttons
	for( nCampaign=nButton; nCampaign<g_NumberCampaigns; ++nCampaign )
	{
		hScreenBtn = hScreenObj->hScreenBtns[ nCampaign ];
		SBtnSetAttributes( hScreenBtn, SBTN_INVISIBLE );
		hScreenBtn->bUpdate = TRUE;
	}
}

void	ScrnInitMoreCampaigns( HSCREEN hScreen )
{
	int				nButton;
	int				nCampaign;
	CAMPAIGNREF*	pCampaign;
	HSCREENBTN		hScreenBtn;
	HSCREENOBJ		hScreenObj;
	SCREENDEF*		pScreenDef  = &SCRNselectCampaignScreen;

#ifdef SBTN_DEBUG
	TRACE( "ScrnInitMoreCampaigns( %08x )\n", hScreen );
#endif

	// build a screen
	SetPath( SCREEN_PATH );

	// acquire the screenobject
	hScreenObj = hScreen->pScreenObjs[0];

	// for each button, acquire a campaign name
	nButton = 0;
	for( nCampaign=g_CampaignIndex; nCampaign<g_NumberCampaigns; ++nCampaign )
	{
		// get the text string for this campaign
		pCampaign = g_Campaigns[ nCampaign ];
		if ( pCampaign )
		{
			hScreenBtn = hScreenObj->hScreenBtns[ nButton ];
			SBtnSetText( hScreenBtn, pCampaign->pCampaignName );
			SBtnSetData( hScreenBtn, pCampaign->nCampaignID );
			SBtnSetCallback( hScreenBtn, BUTTON_CLICKED, (LPVOID)ScrnSelectCampaign );
			hScreenBtn->bUpdate = TRUE;
			++nButton;
		}
	}

	for( nCampaign=nButton; nCampaign<g_NumberCampaigns; ++nCampaign )
	{
		hScreenBtn = hScreenObj->hScreenBtns[ nCampaign ];
		SBtnSetAttributes( hScreenBtn, SBTN_INVISIBLE );
		hScreenBtn->bUpdate = TRUE;
	}
}

LONG	ScrnSelectCampaign( HSCREENBTN hScreenBtn )
{
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
#ifdef SBTN_DEBUG
	TRACE( "ScrnSelectCampaign( %08x )\n", hScreenBtn );
#endif

	// get the campaign ID out of the button data
	g_MissionIndex     = 0;
	g_ScenarioIndex    = 0;
	g_CampaignIndex    = AiCampaignIndex( hScreenBtn->dwData );
	SCRNcampaign       = g_Campaigns[ g_CampaignIndex ];
	gpGame->CampaignID = SCRNcampaign->nCampaignID;
	pScenario          = &(SCRNcampaign->pScenarios[ g_ScenarioIndex ]);
	gpGame->ScenarioID = pScenario->nScenarioID;
	pMission           = &(pScenario->pMissions[ g_MissionIndex ]);
	gpGame->MissionID  = pMission->nMissionID;

	// save for later updates
	ArmySetNextAdvance( g_CampaignIndex, g_ScenarioIndex, g_MissionIndex );

	// now we have the pointer to the particular campaign
	// we need to expand into missions
	ScrnSetState( SCRN_SELECT_MISSION_STATE );

	return( SBTN_STATE_CHANGE );
}

//----------------------------------------------------------------
//		SCREEN	SELECT MISSION STATE CALLBACKS
//----------------------------------------------------------------
LONG	ScrnInitSelectMission( HSCREEN* hScreen )
{
	CAMPAIGNREF*	pCampaign;
	int				nIndex;
	int				nScenarios;
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;

	// turn off any streaming music
	gameQuiet();
	StopAllStreams();

	// apply the proper access to mission and scenarios
#ifdef VISIBILITY_DEBUG
	TRACE( "ScrnInitSelectMission( %d:%d, %d%d %d%d )\n",
		g_CampaignIndex, gpGame->CampaignID, g_ScenarioIndex,
		gpGame->ScenarioID, g_MissionIndex, gpGame->MissionID );
	AiDumpVisibility();
#endif

	ArmyCampaignFindNextAdvance();

	// first determine the number of scenarios in this screen
	nScenarios = g_NumberScenarios - ((g_ScenarioIndex>>2)<<2);
	if ( nScenarios > 4 )
		nScenarios = 4;
	switch( nScenarios )
	{
	case 1:
//		pScreenDef = &SCRNselectMission1Screen;
//		break;
	case 2:
//		pScreenDef = &SCRNselectMission2Screen;
//		break;
	case 3:
//		pScreenDef = &SCRNselectMission3Screen;
//		break;
	case 4:
		pScreenDef = &SCRNselectMission4Screen;
		break;
	default:
		ASSERT(0);
		break;
	}

	// build an screen
	SetPath( SCREEN_PATH );

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	// apply the campaign specific BKG
	nIndex    = AiCampaignIndex( gpGame->CampaignID );
	pCampaign = g_Campaigns[ nIndex ];
	if ( ScrnSetReference( pNewScreen, pCampaign->pCampaignBkg ) )
	{
		// report an error
		TRACE("ERROR: failed to set Mission Select BKG [%s:%d]\n", __FILE__, __LINE__ );
		return( -1 );
	}

	// initialize mission selections
	ScrnInitMissions( pNewScreen );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	// now turn on the campaign music
	gameNoisy();
	PlayStream( pCampaign->nCampaignMusicID, (SND_MUSIC_FLAG|SND_LOOP_FLAG), FALSE );

	ShowTheCursor( TRUE );
	return ( 0 );
}

LONG	ScrnTerminateSelectMission( HSCREEN* hScreen )
{
	CAMPAIGNREF*	pCampaign;
	int				nIndex;

	nIndex    = AiCampaignIndex( gpGame->CampaignID );
	pCampaign = g_Campaigns[ nIndex ];
	StopStream( pCampaign->nCampaignMusicID );

	//clear the screen
	ScrnTerminateScreen( hScreen );
	return 0;
}

LONG	ScrnOnScenarioMore( HSCREENBTN hScreenBtn )
{
	g_ScenarioIndex += 4;
	ScrnTerminateSelectMission( &SCRNfullScreen );
	ScrnInitSelectCampaign( &SCRNfullScreen );

	return( 0 );
}

void	ScrnInitMissions( HSCREEN hScreen )
{
	int				nObject;
	int				nScenario;
	int				nScenarioObjs;
	HSCREENOBJ		hScreenObj;

	// build a screen

	// NOTE: if there are more than SCRN_MAX_SCENARIOS
	// the last object is a MORE button. The
	// others each defines a scenario and its
	// mission list.

	nScenarioObjs = hScreen->nNumberObjs;
	if ( nScenarioObjs > SCRN_MAX_SCENARIOS )
		nScenarioObjs = SCRN_MAX_SCENARIOS;

	// now fill in the scenario/mission info
	nScenario = ((g_ScenarioIndex>>2)<<2);
	for( nObject=0; nObject<SCRN_MAX_SCENARIOS; ++nObject, ++nScenario )
	{
		// acquire the screenobject
		hScreenObj = hScreen->pScreenObjs[ nScenario ];

		// now acquire and fill in the Scenario and Mission names
		SObjScenarioInit( hScreenObj, &(SCRNcampaign->pScenarios[ nScenario ]) );
	}
}

LONG	ScrnSelectMission( HSCREENBTN hScreenBtn )
{
	CAMPAIGNREF*	pCampaign;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	char			buffer[64];

	// get the campaign filename out of the button data
	gpGame->MissionID  = (0x0000FFFF & hScreenBtn->dwData);
	gpGame->ScenarioID = ((0xFFFF0000 & hScreenBtn->dwData)>>16);
	gpGame->newMission = TRUE;

	pCampaign          = g_Campaigns[ g_CampaignIndex ];
	g_ScenarioIndex    = AiScenarioIndex( pCampaign, gpGame->ScenarioID );
	pScenario          = &(pCampaign->pScenarios[ g_ScenarioIndex ]);
	g_MissionIndex     = AiMissionIndex( pScenario, gpGame->MissionID );
	pMission           = &(pScenario->pMissions[ g_MissionIndex ]);


// NEED TO check for saved game file, too
	if ( g_MissionIndex > 0 )	{
		if (!HaveSavedMission(StatGetPlayerNameIndex(), gpGame->MissionID - 1))	{
			MapError("Save file", hScreenBtn);
			return( SBTN_STATE_CHANGE );
		}
	}

	strcpy(buffer, pMission->pFileName);
	strcat( buffer, ".AMM" );
	gpGame->MapName = buffer;

	SetPath(MAP_PATH);
	if (FileExist(gpGame->MapName))	{

		// clear the SCREEN state
		ScrnSetState( SCRN_NULL_STATE );

		// clear the front buffer
		EraseVisibleSurface();

		// now go wait for others to join
		pMainFrame->StartGame();	// start the game
	}
	else	{
		MapError(gpGame->MapName, hScreenBtn);
	}

	return( SBTN_STATE_CHANGE );
}

//----------------------------------------------------------------
//		SCREEN	GAME START STATE CALLBACKS
//----------------------------------------------------------------

LONG	ScrnInitGameStart( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef  = &SCRNstartScreen;

	// build an screen
	SetPath( SCREEN_PATH );

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor( TRUE );
	return ( 0 );
}

LONG	ScrnPlayerName( HSCREENBTN hScreenBtn )
{
#if 0
	// disable any further clicks of this button
	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;
#endif

	return( 0 );
}

//----------------------------------------------------------------
//		SCREEN	OPTIONS STATE CALLBACKS
//----------------------------------------------------------------
LONG	ScrnInitOptions( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef  = &SCRNoptionsScreen;

	// start by erasing the backgrounds
	EraseSurfaces();

	// build an screen
	SetPath( SCREEN_PATH );

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor( TRUE );
	return ( 0 );
}

LONG	ScrnAudioScreen( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	HSCREENOBJ		hScreenObj;
	HSCREENBTN		hScreenBtn;
	HSCREENBTN		hBarBtn;
	SCREENDEF*		pScreenDef;
	SPOINT*			pPosition;
	LONG			nVolume;
	BOOL			bFlags;

	// build an screen
	SetPath( SCREEN_PATH );

	// turn off all the audio
	audioDisable();

	pScreenDef  = &SCRNaudioScreen;

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	// turn on the audio and start 3 looping effects
	audioEnable(pMainFrame->m_hWnd);

	if ( SFXenabled )
	{
		bFlags = (SND_SFX_FLAG|SND_LOOP_FLAG);
		SCRNsfxSnd = audioCreateSnd( AUDIOsfxID, TANK_FULL_LOOP, 0, bFlags );
		if ( SCRNsfxSnd == SND_NULL_SND_ID )
		{
			// report an error
			TRACE("ERROR: failed to create SFX sound [%s:%d]\n", __FILE__, __LINE__ );
			return( 0 );
		}
		audioStoreSnd( TANK_FULL_LOOP, SCRNsfxSnd, bFlags );
		SCRNsfxPlayToggle = FALSE;
	}

	// get the SFX state and set the buttons appropriately
	hScreenObj = pNewScreen->pScreenObjs[SFX_ON_OFF_OBJECT];
	if ( gpGame->Sfx == FALSE)
	{
		hScreenBtn = hScreenObj->hScreenBtns[OFF_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	else
	{
		hScreenBtn = hScreenObj->hScreenBtns[ON_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	hScreenObj = pNewScreen->pScreenObjs[SFX_VOLUME_OBJECT];
	hBarBtn    = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];
	nVolume    = audioGetMasterVolume( SND_SFX_FLAG );
	pPosition  = SBtnGetPosition( hBarBtn );
	pPosition->x = (short)(pPosition->x - (100 - nVolume));
	SBtnSetPosition( hBarBtn, pPosition );

	if ( STRMenabled )
	{
		bFlags       = (SND_MUSIC_FLAG|SND_LOOP_FLAG);
		SCRNmusicSnd = strmCreateStream( AUDIOstreamID, TITLE_MUSIC, 0, bFlags );
		if ( SCRNmusicSnd == SND_NULL_SND_ID )
		{
			// report an error
			TRACE("ERROR: failed to create MUSIC stream [%s:%d]\n", __FILE__, __LINE__ );
			return( 0 );
		}
		audioStoreSnd( TITLE_MUSIC, SCRNmusicSnd, bFlags );
		SCRNmusicPlayToggle = FALSE;
	}

	// get the MUSIC state and set the buttons appropriately
	hScreenObj = pNewScreen->pScreenObjs[MUSIC_ON_OFF_OBJECT];
	if ( gpGame->Music == FALSE)
	{
		hScreenBtn = hScreenObj->hScreenBtns[OFF_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	else
	{
		hScreenBtn = hScreenObj->hScreenBtns[ON_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	hScreenObj = pNewScreen->pScreenObjs[MUSIC_VOLUME_OBJECT];
	hBarBtn    = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];
	nVolume    = audioGetMasterVolume( SND_MUSIC_FLAG );
	pPosition  = SBtnGetPosition( hBarBtn );
	pPosition->x = (short)(pPosition->x - (100 - nVolume));
	SBtnSetPosition( hBarBtn, pPosition );

	if ( VOICEenabled )
	{
		bFlags       = (SND_VOICE_FLAG|SND_LOOP_FLAG);
		SCRNvoiceSnd = voiceCreateStream( AUDIOvoiceID, PINNED_DOWN, 0, bFlags );
		if ( SCRNvoiceSnd == SND_NULL_SND_ID )
		{
			// report an error
			TRACE("ERROR: failed to create VOICE stream [%s:%d]\n", __FILE__, __LINE__ );
			return( 0 );
		}
		audioStoreSnd( PINNED_DOWN, SCRNvoiceSnd, bFlags );
		SCRNvoicePlayToggle = FALSE;
	}

	// get the VOICE state and set the buttons appropriately
	hScreenObj = pNewScreen->pScreenObjs[VOICE_ON_OFF_OBJECT];
	if ( gpGame->Voice == FALSE)
	{
		hScreenBtn = hScreenObj->hScreenBtns[OFF_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	else
	{
		hScreenBtn = hScreenObj->hScreenBtns[ON_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	hScreenObj = pNewScreen->pScreenObjs[VOICE_VOLUME_OBJECT];
	hBarBtn    = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];
	nVolume    = audioGetMasterVolume( SND_VOICE_FLAG );
	pPosition  = SBtnGetPosition( hBarBtn );
	pPosition->x = (short)(pPosition->x - (100 - nVolume));
	SBtnSetPosition( hBarBtn, pPosition );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor( TRUE );
	return ( 0 );
}

LONG	ScrnTerminateAudioScreen( HSCREEN* hScreen )
{
	audioStopAll();
	AudioSetReg();

	ScrnTerminateScreen( hScreen );
	return 0;
}

LONG	ScrnAboutScreen( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;

	// build an screen
	SetPath( SCREEN_PATH );

	pScreenDef = &SCRNemptyScreen;
	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	// turn off all the audio
	gameQuiet();

	// disable the windows cursor
	ShowTheCursor( FALSE );

	// set the movie state and start the smacker video
	MovieSetState( MOVIE_CREDITS_STATE );
	MovieInitCredits();

	return ( 0 );
}

LONG	ScrnTerminateAboutScreen( HSCREEN* hScreen )
{
	ScrnTerminateScreen( hScreen );

	// enable the windows cursor
	ShowTheCursor( TRUE );

	gameNoisy();
	return( 0 );
}

LONG	ScrnOnControlsOption( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_CONTROLS_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnAboutOption( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_ABOUT_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnKeypadConfig( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_KEYPAD_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnKeyBoardConfig( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_KEYBOARD_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnCustomConfig( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_CUSTOM_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnJoystickConfig( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_JOYSTICK_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnAudioOption( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_AUDIO_STATE );
	return( SBTN_STATE_CHANGE );
}

//----------------------------------------------------------------
//		SCREEN	PLAY OPTIONS STATE CALLBACKS
//----------------------------------------------------------------
LONG	ScrnInitPlayOptions( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	HSCREENOBJ		hScreenObj;
	HSCREENBTN		hScreenBtn;
	SCREENDEF*		pScreenDef  = &SCRNoptions2Screen;

	// build an screen
	SetPath( SCREEN_PATH );

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	// look to see if we need to override "Abort Mission" button with
	// a "Exit Boot Camp" button
	if (gpGame->BootCamp)
	{
		hScreenObj = pNewScreen->pScreenObjs[ ABORT_OBJECT ];
		if( hScreenObj )
		{
			hScreenBtn = hScreenObj->hScreenBtns[ ABORT_BUTTON ];
			if ( hScreenBtn )
				SBtnSetText( hScreenBtn, EndBootCamp_Text );
		}
	}

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor(TRUE);
	return ( 0 );
}

LONG	ScrnControlsScreen( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;
	SCREENOBJ*		hScreenObj;
	SCREENBTN*		hButton;

	// build an screen
	SetPath( SCREEN_PATH );

	if ( gpGame->GetState() == GAME_PLAY_STATE )
		pScreenDef  = &SCRNcontrols2Screen;
	else
		pScreenDef  = &SCRNcontrolsScreen;

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	// get the controls object to set joystick availability and currently selected UI
	hScreenObj = pNewScreen->pScreenObjs[ CONTROLS_OBJECT ];

	// if no joystick attached, inactivate option
	if (!JoystickActive())	{
		// Display the current player
		SCREENBTN* hButton = hScreenObj->hScreenBtns[ JOYSTICK_OBJECT ];

		SBtnSetAttributes( hButton, SBTN_DISABLED );
		hScreenObj->bUpdate = TRUE;
	}

	// now look to see what configuration we're currently using
	hButton = hScreenObj->hScreenBtns[ UIcurrentConfig ];
	SBtnSetState( hButton, BUTTON_FOCUSED );

	ShowTheCursor(TRUE);
	return ( 0 );
}

LONG	ScrnTerminateScreen( HSCREEN* hScreen )
{
	if ( hScreen )
	{
		ScrnDelete( *hScreen );
		*hScreen = NULL;
	}

	ShowTheCursor(FALSE);
	return( 0 );
}


LONG	ScrnPlayAudioScreen( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;
	HSCREENOBJ		hScreenObj;
	HSCREENBTN		hScreenBtn;
	HSCREENBTN		hBarBtn;
	SPOINT*			pPosition;
	LONG			nVolume;
	BOOL			bFlags;

	// build an screen
	SetPath( SCREEN_PATH );

	gameQuiet();
	audioStopAll();
	gameNoisy();

	pScreenDef = &SCRNaudio2Screen;
	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	// turn on the audio and start 3 looping effects
	audioEnable(pMainFrame->m_hWnd);

	if ( SFXenabled )
	{
		bFlags = (SND_SFX_FLAG|SND_LOOP_FLAG);
		SCRNsfxSnd = audioCreateSnd( AUDIOsfxID, TANK_FULL_LOOP, 0, bFlags );
		if ( SCRNsfxSnd == SND_NULL_SND_ID )
		{
			// report an error
			TRACE("ERROR: failed to create SFX sound [%s:%d]\n", __FILE__, __LINE__ );
			return( 0 );
		}
		audioStoreSnd( TANK_FULL_LOOP, SCRNsfxSnd, bFlags );
		SCRNsfxPlayToggle = FALSE;
	}

	// get the SFX state and set the buttons appropriately
	hScreenObj = pNewScreen->pScreenObjs[SFX_ON_OFF_OBJECT];
	if ( audioSfxGetOn() == FALSE)
	{
		hScreenBtn = hScreenObj->hScreenBtns[OFF_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	else
	{
		hScreenBtn = hScreenObj->hScreenBtns[ON_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	hScreenObj = pNewScreen->pScreenObjs[SFX_VOLUME_OBJECT];
	hBarBtn    = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];
	nVolume    = audioGetMasterVolume( SND_SFX_FLAG );
	pPosition  = SBtnGetPosition( hBarBtn );
	pPosition->x = (short)(pPosition->x - (100 - nVolume));
	SBtnSetPosition( hBarBtn, pPosition );

	if ( STRMenabled )
	{
		bFlags       = (SND_MUSIC_FLAG|SND_LOOP_FLAG);
		SCRNmusicSnd = strmCreateStream( AUDIOstreamID, TITLE_MUSIC, 0, bFlags );
		if ( SCRNmusicSnd == SND_NULL_SND_ID )
		{
			// report an error
			TRACE("ERROR: failed to create MUSIC stream [%s:%d]\n", __FILE__, __LINE__ );
			return( 0 );
		}
		audioStoreSnd( TITLE_MUSIC, SCRNmusicSnd, bFlags );
		SCRNmusicPlayToggle = FALSE;
	}

	// get the MUSIC state and set the buttons appropriately
	hScreenObj = pNewScreen->pScreenObjs[MUSIC_ON_OFF_OBJECT];
	if ( audioMusicGetOn() == FALSE)
	{
		hScreenBtn = hScreenObj->hScreenBtns[OFF_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	else
	{
		hScreenBtn = hScreenObj->hScreenBtns[ON_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	hScreenObj = pNewScreen->pScreenObjs[MUSIC_VOLUME_OBJECT];
	hBarBtn    = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];
	nVolume    = audioGetMasterVolume( SND_MUSIC_FLAG );
	pPosition  = SBtnGetPosition( hBarBtn );
	pPosition->x = (short)(pPosition->x - (100 - nVolume));
	SBtnSetPosition( hBarBtn, pPosition );

	if ( VOICEenabled )
	{
		bFlags       = (SND_VOICE_FLAG|SND_LOOP_FLAG);
		SCRNvoiceSnd = voiceCreateStream( AUDIOvoiceID, PINNED_DOWN, 0, bFlags );
		if ( SCRNvoiceSnd == SND_NULL_SND_ID )
		{
			// report an error
			TRACE("ERROR: failed to create VOICE stream [%s:%d]\n", __FILE__, __LINE__ );
			return( 0 );
		}
		audioStoreSnd( PINNED_DOWN, SCRNvoiceSnd, bFlags );
		SCRNvoicePlayToggle = FALSE;
	}

	// get the VOICE state and set the buttons appropriately
	hScreenObj = pNewScreen->pScreenObjs[VOICE_ON_OFF_OBJECT];
	if ( audioVoiceGetOn() == FALSE)
	{
		hScreenBtn = hScreenObj->hScreenBtns[OFF_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	else
	{
		hScreenBtn = hScreenObj->hScreenBtns[ON_OBJECT];
		SBtnSetState( hScreenBtn, BUTTON_CLICKED );
	}
	hScreenObj = pNewScreen->pScreenObjs[VOICE_VOLUME_OBJECT];
	hBarBtn    = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];
	nVolume    = audioGetMasterVolume( SND_VOICE_FLAG );
	pPosition  = SBtnGetPosition( hBarBtn );
	pPosition->x = (short)(pPosition->x - (100 - nVolume));
	SBtnSetPosition( hBarBtn, pPosition );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor(TRUE);
	return ( 0 );
}


LONG	ScrnPlayAboutScreen( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;

	// build an screen
	SetPath( SCREEN_PATH );

	pScreenDef = &SCRNemptyScreen;
	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	// turn off all the audio
	gameQuiet();

	// disable the windows cursor
	ShowTheCursor( FALSE );

	pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
	pMainFrame->SetUIOverride(KeyOverride_GAME_STAT_SCREEN_STATE);
	pMainFrame->PausePageFlip();

	// set the movie state and start the smacker video
	MovieSetState( MOVIE_CREDITS_STATE );
	MovieInitCredits();

	return ( 0 );
}

LONG	ScrnTerminatePlayAboutScreen( HSCREEN* hScreen )
{
	ScrnTerminateScreen( hScreen );

	// clear the surfaces as we're about to change the palette
	EraseSurfaces();

	// force creation of the gameplay terrain palette
	ForceLoadIdentityPalette(the_map.terrain_name);

	// enable the windows cursor
	ShowTheCursor( TRUE );

	// turn on the audio
	gameNoisy();

	// reset the UI to appropriate game play sub state
	if( gpGame->GetSubState() == PLAY_SETUP_SUB_STATE )
		pMainFrame->SetUI(&UI_GAME_SETUP_STATE);
	else
		pMainFrame->SetUI(&UI_GAME_PLAY_STATE);	
	pMainFrame->SetUIOverride(NULL);

	// once again start page flipping
	pMainFrame->UnPausePageFlip();
	return( 0 );
}

LONG	ScrnOnControls2Option( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_PLAY_CONTROLS_STATE );
	pMainFrame->SetUIOverride(NULL);
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnAudio2Option( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_PLAY_AUDIO_STATE );
	pMainFrame->SetUIOverride(NULL);
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnAbortMission( HSCREENBTN hScreenBtn )
{
	// quiet the game and turn off all the audio
	audioStopAll();

	// clear the screen
	ShowTheCursor(FALSE);
	EraseSurfaces();
	gpGame->UnPauseGame( PAUSE_LOCAL );
	if( gpGame->GameType != GAMETYPE_ONEPLAYER )
	{
		SendGamePause(FALSE, PAUSE_LOCAL);
		gpComm->Disconnect();
	}

	// now reset the screen and game states to GAME START
	pMainFrame->SetUIOverride(NULL);
	ScrnSetState( SCRN_NULL_STATE );
	gpGame->SetSubState(NULL_SUB_STATE);
	gpGame->SetState( GAME_TITLE_SCREEN_STATE );
	ScrnSetState( SCRN_GAME_START_STATE );
	if (gpComm->m_bStartedByLobby) return (ScrnOnQuit(hScreenBtn));

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnAbout2Option( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_PLAY_ABOUT_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnKeypad2Config( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_KEYPAD_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnKeyBoard2Config( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_KEYBOARD_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnCustom2Config( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_CUSTOM_STATE );
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnJoystick2Config( HSCREENBTN hScreenBtn )
{
	ScrnSetState( SCRN_JOYSTICK_STATE );
	return( SBTN_STATE_CHANGE );
}

//----------------------------------------------------------------
//		SCREEN	AUDIO CALLBACKS
//----------------------------------------------------------------
LONG	ScrnOnSfxOnOption( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;

	// turn on the sfx
	gpGame->Sfx = TRUE;
	audioSfxOn();

	// no locate the OFF button and change it to NULL state
	hScreenObj          = SCRNfullScreen->pScreenObjs[SFX_ON_OFF_OBJECT];
	hScreenObj->bUpdate = TRUE;
	hBtn                = hScreenObj->hScreenBtns[OFF_OBJECT];
	SBtnSetState( hBtn, BUTTON_NULL );
	hBtn->bUpdate       = TRUE;

	// disable any further clicks of this button
	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnSfxOffOption( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;

	// turn off the sfx
	gpGame->Sfx = FALSE;
	audioSfxOff();

	// no locate the ON button and change it to NULL state
	hScreenObj          = SCRNfullScreen->pScreenObjs[SFX_ON_OFF_OBJECT];
	hScreenObj->bUpdate = TRUE;
	hBtn                = hScreenObj->hScreenBtns[ON_OBJECT];
	SBtnSetState( hBtn, BUTTON_NULL );
	hBtn->bUpdate       = TRUE;

	// disable any further clicks of this button
	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnMusicOnOption( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;

	// turn on the Music
	gpGame->Music = TRUE;
	audioMusicOn();

	// no locate the OFF button and change it to NULL state
	hScreenObj          = SCRNfullScreen->pScreenObjs[MUSIC_ON_OFF_OBJECT];
	hScreenObj->bUpdate = TRUE;
	hBtn                = hScreenObj->hScreenBtns[OFF_OBJECT];
	SBtnSetState( hBtn, BUTTON_NULL );
	hBtn->bUpdate       = TRUE;

	// disable any further clicks of this button
	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnMusicOffOption( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;

	// turn off the Music
	gpGame->Music = FALSE;
	audioMusicOff();

	// no locate the ON button and change it to NULL state
	hScreenObj          = SCRNfullScreen->pScreenObjs[MUSIC_ON_OFF_OBJECT];
	hScreenObj->bUpdate = TRUE;
	hBtn                = hScreenObj->hScreenBtns[ON_OBJECT];
	SBtnSetState( hBtn, BUTTON_NULL );
	hBtn->bUpdate       = TRUE;

	// disable any further clicks of this button
	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnVoiceOnOption( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;

	// turn on the Voice
	gpGame->Voice = TRUE;
	audioVoiceOn();

	// no locate the OFF button and change it to NULL state
	hScreenObj          = SCRNfullScreen->pScreenObjs[VOICE_ON_OFF_OBJECT];
	hScreenObj->bUpdate = TRUE;
	hBtn                = hScreenObj->hScreenBtns[OFF_OBJECT];
	SBtnSetState( hBtn, BUTTON_NULL );
	hBtn->bUpdate       = TRUE;

	// disable any further clicks of this button
	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnVoiceOffOption( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;

	// turn off the Voice
	gpGame->Voice = FALSE;
	audioVoiceOff();

	// no locate the ON button and change it to NULL state
	hScreenObj          = SCRNfullScreen->pScreenObjs[VOICE_ON_OFF_OBJECT];
	hScreenObj->bUpdate = TRUE;
	hBtn                = hScreenObj->hScreenBtns[ON_OBJECT];
	SBtnSetState( hBtn, BUTTON_NULL );
	hBtn->bUpdate       = TRUE;

	// disable any further clicks of this button
	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnSfxVolumeDn( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBarBtn;
	short		nVolume;
	SPOINT*		pPosition;

	// now update the volume scroll bar
	hScreenObj   = SCRNfullScreen->pScreenObjs[SFX_VOLUME_OBJECT];
	hBarBtn      = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];

	// start by acquiring the current volume
	nVolume   = (short)audioGetMasterVolume( SND_SFX_FLAG );
	pPosition = SBtnGetPosition( hBarBtn );

	// now decrease the volume by 10%
	if ( (nVolume-10) <= 0 )
	{
		pPosition->x -= nVolume;
		nVolume       = 0;
	}
	else
	{
		pPosition->x -= 10;
		nVolume      -= 10;
	}

	// set this new volume
	audioSetMasterVolume( SND_SFX_FLAG, (LONG)nVolume );
	SBtnSetPosition( hBarBtn, pPosition );
	SObjForceUpdate( hScreenObj );

	// allows multiple CLICKs
	SBtnSetState( hScreenBtn, BUTTON_NULL );

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnSfxVolumeUp( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBarBtn;
	short		nVolume;
	SPOINT*		pPosition;

	// now update the volume scroll bar
	hScreenObj   = SCRNfullScreen->pScreenObjs[SFX_VOLUME_OBJECT];
	hBarBtn      = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];

	// start by acquiring the current volume
	nVolume   = (short)audioGetMasterVolume( SND_SFX_FLAG );
	pPosition = SBtnGetPosition( hBarBtn );

	// now increase the volume by 10%
	if ( (nVolume+10) > 100 )
	{
		pPosition->x += (100 - nVolume);
		nVolume       = 100;
	}
	else
	{
		pPosition->x += 10;
		nVolume      += 10;
	}

	// set this new volume
	audioSetMasterVolume( SND_SFX_FLAG, (LONG)nVolume );
	SBtnSetPosition( hBarBtn, pPosition );
	SObjForceUpdate( hScreenObj );

	// allows multiple CLICKs
	SBtnSetState( hScreenBtn, BUTTON_NULL );

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnMusicVolumeDn( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBarBtn;
	short		nVolume;
	SPOINT*		pPosition;

	// now update the volume scroll bar
	hScreenObj   = SCRNfullScreen->pScreenObjs[MUSIC_VOLUME_OBJECT];
	hBarBtn      = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];

	// start by acquiring the current volume
	nVolume   = (short)audioGetMasterVolume( SND_MUSIC_FLAG );
	pPosition = SBtnGetPosition( hBarBtn );

	// now decrease the volume by 10%
	if ( (nVolume-10) <= 0 )
	{
		pPosition->x -= nVolume;
		nVolume       = 0;
	}
	else
	{
		pPosition->x -= 10;
		nVolume      -= 10;
	}

	// set this new volume
	audioSetMasterVolume( SND_MUSIC_FLAG, (LONG)nVolume );
	SBtnSetPosition( hBarBtn, pPosition );
	SObjForceUpdate( hScreenObj );

	// allows multiple CLICKs
	SBtnSetState( hScreenBtn, BUTTON_NULL );

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnMusicVolumeUp( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBarBtn;
	short		nVolume;
	SPOINT*		pPosition;

	// now update the volume scroll bar
	hScreenObj   = SCRNfullScreen->pScreenObjs[MUSIC_VOLUME_OBJECT];
	hBarBtn      = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];

	// start by acquiring the current volume
	nVolume   = (short)audioGetMasterVolume( SND_MUSIC_FLAG );
	pPosition = SBtnGetPosition( hBarBtn );

	// now increase the volume by 10%
	if ( (nVolume+10) > 100 )
	{
		pPosition->x += (100 - nVolume);
		nVolume       = 100;
	}
	else
	{
		pPosition->x += 10;
		nVolume      += 10;
	}

	// set this new volume
	audioSetMasterVolume( SND_MUSIC_FLAG, (LONG)nVolume );
	SBtnSetPosition( hBarBtn, pPosition );
	SObjForceUpdate( hScreenObj );

	// allows multiple CLICKs
	SBtnSetState( hScreenBtn, BUTTON_NULL );

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnVoiceVolumeDn( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBarBtn;
	short		nVolume;
	SPOINT*		pPosition;

	// now update the volume scroll bar
	hScreenObj   = SCRNfullScreen->pScreenObjs[VOICE_VOLUME_OBJECT];
	hBarBtn      = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];

	// start by acquiring the current volume
	nVolume   = (short)audioGetMasterVolume( SND_VOICE_FLAG );
	pPosition = SBtnGetPosition( hBarBtn );

	// now decrease the volume by 10%
	if ( (nVolume-10) <= 0 )
	{
		pPosition->x -= nVolume;
		nVolume       = 0;
	}
	else
	{
		pPosition->x -= 10;
		nVolume      -= 10;
	}

	// set this new volume
	audioSetMasterVolume( SND_VOICE_FLAG, (LONG)nVolume );
	SBtnSetPosition( hBarBtn, pPosition );
	SObjForceUpdate( hScreenObj );

	// allows multiple CLICKs
	SBtnSetState( hScreenBtn, BUTTON_NULL );

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnVoiceVolumeUp( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBarBtn;
	short		nVolume;
	SPOINT*		pPosition;

	// now update the volume scroll bar
	hScreenObj   = SCRNfullScreen->pScreenObjs[VOICE_VOLUME_OBJECT];
	hBarBtn      = hScreenObj->hScreenBtns[SLIDER_BAR_BUTTON];

	// start by acquiring the current volume
	nVolume   = (short)audioGetMasterVolume( SND_VOICE_FLAG );
	pPosition = SBtnGetPosition( hBarBtn );

	// now increase the volume by 10%
	if ( (nVolume+10) > 100 )
	{
		pPosition->x += (100 - nVolume);
		nVolume       = 100;
	}
	else
	{
		pPosition->x += 10;
		nVolume      += 10;
	}

	// set this new volume
	audioSetMasterVolume( SND_VOICE_FLAG, (LONG)nVolume );
	SBtnSetPosition( hBarBtn, pPosition );
	SObjForceUpdate( hScreenObj );

	// allows multiple CLICKs
	SBtnSetState( hScreenBtn, BUTTON_NULL );

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnSfxPlaySnd( HSCREENBTN hScreenBtn )
{
	// turn off the music if it exists
	if ( SCRNsfxSnd != SND_NULL_SND_ID )
	{
		if ( SCRNsfxPlayToggle )
		{
			sfxStopSnd( SCRNsfxSnd );
			SCRNsfxPlayToggle = FALSE;
		}
		else
		{
			sfxStopSnd( SCRNsfxSnd );
			sfxPlaySnd( SCRNsfxSnd );
			SCRNsfxPlayToggle = TRUE;

			// dont forget to disable the other audio players
			if ( SCRNmusicSnd != SND_NULL_SND_ID )
			{
				strmStopSnd( SCRNmusicSnd );
				SCRNmusicPlayToggle = FALSE;
			}
			if ( SCRNvoiceSnd != SND_NULL_SND_ID )
			{
				voiceStopSnd( SCRNvoiceSnd );
				SCRNvoicePlayToggle = FALSE;
			}
		}

		// allows multiple CLICKs
		SBtnSetState( hScreenBtn, BUTTON_NULL );

		// force an update of this button
		hScreenBtn->bUpdate = TRUE;
	}
	else
	{
		// report an error
		TRACE("ERROR: failed to create SFX sound loop [%s:%d]\n", __FILE__, __LINE__ );
	}
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnMusicPlaySnd( HSCREENBTN hScreenBtn )
{
	// turn off the music if it exists
	if ( SCRNmusicSnd != SND_NULL_SND_ID )
	{
		if ( SCRNmusicPlayToggle )
		{
			strmStopSnd( SCRNmusicSnd );
			SCRNmusicPlayToggle = FALSE;
		}
		else
		{
			strmStopSnd( SCRNmusicSnd );
			strmCueSnd( SCRNmusicSnd );
			strmPlaySnd( SCRNmusicSnd );
			SCRNmusicPlayToggle = TRUE;

			// dont forget to disable the other audio players
			if ( SCRNsfxSnd != SND_NULL_SND_ID )
			{
				sfxStopSnd( SCRNsfxSnd );
				SCRNsfxPlayToggle = FALSE;
			}
			if ( SCRNvoiceSnd != SND_NULL_SND_ID )
			{
				voiceStopSnd( SCRNvoiceSnd );
				SCRNvoicePlayToggle = FALSE;
			}
		}

		// allows multiple CLICKs
		SBtnSetState( hScreenBtn, BUTTON_NULL );

		// force an update of this button
		hScreenBtn->bUpdate = TRUE;
	}
	else
	{
		// report an error
		TRACE("ERROR: failed to create MUSIC stream [%s:%d]\n", __FILE__, __LINE__ );
	}
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnVoicePlaySnd( HSCREENBTN hScreenBtn )
{
	// turn off the voice if it exists
	if ( SCRNvoiceSnd != SND_NULL_SND_ID )
	{
		if ( SCRNvoicePlayToggle )
		{
			voiceStopSnd( SCRNvoiceSnd );
			SCRNvoicePlayToggle = FALSE;
		}
		else
		{
			voiceStopSnd( SCRNvoiceSnd );
			voiceCueSnd( SCRNvoiceSnd );
			voicePlaySnd( SCRNvoiceSnd );
			SCRNvoicePlayToggle = TRUE;

			// dont forget to disable the other audio players
			if ( SCRNsfxSnd != SND_NULL_SND_ID )
			{
				sfxStopSnd( SCRNsfxSnd );
				SCRNsfxPlayToggle = FALSE;
			}
			if ( SCRNmusicSnd != SND_NULL_SND_ID )
			{
				strmStopSnd( SCRNmusicSnd );
				SCRNmusicPlayToggle = FALSE;
			}
		}

		// allows multiple CLICKs
		SBtnSetState( hScreenBtn, BUTTON_NULL );

		// force an update of this button
		hScreenBtn->bUpdate = TRUE;
	}
	else
	{
		// report an error
		TRACE("ERROR: failed to create VOICE stream [%s:%d]\n", __FILE__, __LINE__ );
	}

	return( SBTN_STATE_CHANGE );
}

//----------------------------------------------------------------
//		SCREEN	CONTINUE CALLBACK
//----------------------------------------------------------------

LONG	ScrnOnContinue( HSCREENBTN hScreenBtn )
{
	if ( gpGame->GetSubState() == STAT_SUB_STATE )
		ScrnOnContinueStats();

	return( SBTN_STATE_CHANGE );
}

//----------------------------------------------------------------
//		SCREEN	PLAYER LOSE MISSION STATE CALLBACKS
//----------------------------------------------------------------

LONG	ScrnOnYesPlayAgain( HSCREENBTN hScreenBtn )
{
	int				nPlayerNameIndex;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;

	StopAllStreams();

	// save the missions completed data
 	if (gpGame->GameType == GAMETYPE_ONEPLAYER)
	{
		pScenario          = GetScenario();
		pMission           = GetMission();
		pMission->bVisible = STAT_NEXT_FLAG;

		nPlayerNameIndex = StatGetPlayerNameIndex();
		StatSaveNext( nPlayerNameIndex, gpGame->CampaignID, gpGame->MissionID, TRUE );
	}

	// clear the screen state and put up a title screen background
	ScrnSetState( SCRN_NULL_STATE );
	gpGame->newMission = TRUE;

	pMainFrame->StartGame();	// start the game

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnNoPlayAgain( HSCREENBTN hScreenBtn )
{
	int				nPlayerNameIndex;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;

	// clear the YEAH/BOO stream
	StopAllStreams();

	// clear the bootcamp flag
	gpGame->BootCamp = FALSE;

	// save the missions completed data
 	if (gpGame->GameType == GAMETYPE_ONEPLAYER)
	{
		pScenario          = GetScenario();
		pMission           = GetMission();
		pMission->bVisible = STAT_NEXT_FLAG;

		nPlayerNameIndex = StatGetPlayerNameIndex();
		StatSaveNext( nPlayerNameIndex, gpGame->CampaignID, gpGame->MissionID, TRUE );
	}

	// if we were a loser we need to play an FMV (Failed Mission Video)
	if ( gpGame->winner == FALSE )	// "You Lose"
	{
		// prepare to go on
 		switch(gpGame->GameType)	
		{
		case GAMETYPE_ONEPLAYER:
			ScrnSetState( SCRN_NULL_STATE );

			// need to return the player to the mission select screen
			gpGame->SetState( GAME_TITLE_SCREEN_STATE );
			ScrnSetState( SCRN_SELECT_MISSION_STATE );
			break;
		case GAMETYPE_HOST_MULTIPLAYER:
			gpGame->SetState( GAME_TITLE_SCREEN_STATE );
			DumpMessageCounts();
			ClearMessageCounts();
			ScrnSetState( SCRN_MULTI_HOST_STATE );
			break;
		case GAMETYPE_REMOTE_MULTIPLAYER:
			gpGame->SetState( GAME_TITLE_SCREEN_STATE );
			DumpMessageCounts();
			ClearMessageCounts();
			ScrnSetState( SCRN_MULTI_REMOTE_STATE );
			break;
		}
	}
	else
	{
		// need to return the player to the mission select screen
		ScrnSetState( SCRN_GAME_START_STATE );
		gpGame->SetSubState(NULL_SUB_STATE);
		gpGame->SetState( GAME_TITLE_SCREEN_STATE );
	}

	return( SBTN_STATE_CHANGE );
}


//----------------------------------------------------------------
//		SCREEN	STATS STATE CALLBACKS
//----------------------------------------------------------------
extern int	GetSargeHealthPercentage();

void SetMissionOverBitmap(BOOL winner, BOOL one_player)	{
	char *terrain_base;
	char *base;
	char *type;
	char basename[32];
	char filename[64];

	if (winner)
		type = "Win";
	else if (!GetSargeHealthPercentage())
		type = "Die";
	else
		type = "Lose";

	terrain_base = the_map.terrain_name;
	if (one_player)	{
		if (gpGame->cdBoot && !winner)
			base = terrain_base;
		else	{
			base = basename;
			sprintf( basename, "%s_%d", the_map.map_name, g_MissionIndex+1 );
		}
	}
	else	{
		base = basename;
		sprintf( basename, "%sMP", terrain_base );
	}

	strcpy(filename, base);
	strcat(filename, type);
	strcat(filename, ".bmp");

	if (!FileExist(filename))	{
		strcpy(filename, terrain_base);
		strcat(filename, type);
		strcat(filename, ".bmp");
	}

	strcpy(missionOverImage.bkgRef, filename);
}


LONG	ScrnInitStats( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	STATS*			pMissionStats = NULL;
	SCREENDEF*		pScreenDef;
	BOOL			bYesNo = TRUE;
	int				nPlayerNameIndex;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;

	// initialize the mission completed screen
	bYesNo     = FALSE;
	pScreenDef = &SCRNmissionCompleteScreen;

	// see if we need to override based on oneplayer
	if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
	{
		pScenario = GetScenario();
		pMission = GetMission();
		MissionVisible(pMission);
		nPlayerNameIndex = StatGetPlayerNameIndex();

		// did we win or lose
		if ( !gpGame->winner && !gpGame->cdBoot)
			pScreenDef  = &SCRNmissionFailedScreen;
		else
		if ( gpGame->winner /* && !gpGame->cdBoot */ )
		{
			// copy the current player name into the permanent set
			strcpy( STATplayerNames[ nPlayerNameIndex ], STATcurrentName );
			StatUpdate( STAT_CURRENT_PLAYER_INDEX, STAT_UPDATE_PLAYER_STATS, FALSE );

			// now do an auto save
			StatSave( nPlayerNameIndex, gpGame->MissionID );
		}
	}

	SetPath(BRIEFS_PATH);
	SetMissionOverBitmap(gpGame->winner, gpGame->GameType == GAMETYPE_ONEPLAYER);

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	*hScreen           = pNewScreen;
	pNewScreen->eState = SCRN_STATS_STATE;
	ScrnLoadDef( pNewScreen, pScreenDef );

	// now set up the YES-NO response flag
	if ( bYesNo )
		pNewScreen->bAttributes |= SCRN_ISYESNO;

	pNewScreen->bUpdate = TRUE;

//	MsgMissionEnd(gpGame->winner, gpGame->GameType == GAMETYPE_ONEPLAYER);
	bAudioRecall = TRUE;

	ShowTheCursor(TRUE);
	return( 0 );
 }

LONG	ScrnTerminateStats( HSCREEN* hScreen )
{
	ScrnTerminateScreen( hScreen );
	return( SBTN_STATE_CHANGE );
}


void	ScrnOnContinueStats( void )
{
	int				nPlayerNameIndex;
	SCENARIOREF*	pScenario;
	MISSIONREF*		pMission;
	BOOL			bNextMission = FALSE;

	ShowTheCursor( FALSE );

	// take care of the audio
	StopAllStreams();

	// clear the current substate and prepare for a new one
	gpGame->SetSubState(NULL_SUB_STATE);

	// restore any audio
	audioEnable( pMainFrame->m_hWnd );


 	switch(gpGame->GameType)	
	{
		case GAMETYPE_HOST_MULTIPLAYER:
			gpGame->SetState( GAME_TITLE_SCREEN_STATE );
			DumpMessageCounts();
			ClearMessageCounts();
			ScrnSetState( SCRN_MULTI_HOST_STATE );
			return;
		case GAMETYPE_REMOTE_MULTIPLAYER:
			gpGame->SetState( GAME_TITLE_SCREEN_STATE );
			DumpMessageCounts();
			ClearMessageCounts();
			ScrnSetState( SCRN_MULTI_REMOTE_STATE );
			return;
	}


	// update the current mission completed visibility
	pScenario = GetScenario();
	pMission = GetMission();
	MissionVisible(pMission);

	// did we win or lose
	if ( gpGame->winner == FALSE )	// "You Lose"
	{
		nPlayerNameIndex = StatGetPlayerNameIndex();
		StatSaveNext( nPlayerNameIndex, gpGame->CampaignID, gpGame->MissionID, TRUE );

		// need to return the player to the mission select screen
		ScrnSetState( SCRN_NULL_STATE );
		gpGame->SetState( GAME_TITLE_SCREEN_STATE );
		ScrnSetState( SCRN_SELECT_MISSION_STATE );
	}
	else							// "You WIN"
		ScrnWhatIsNext();	// check to see if we are at the end of a mission or scenario

	MouseDown0 = FALSE;
}

//----------------------------------------------------------------
//		SCREEN	LOSE STATE CALLBACKS
//----------------------------------------------------------------

LONG	ScrnOnQuitStats( HSCREENBTN hScreenBtn )
{
	pMainFrame->PostMessage(WM_CLOSE, 0, 0);
	SBtnSetState( hScreenBtn, BUTTON_NULL );

	return( SBTN_STATE_CHANGE );
}

//----------------------------------------------------------------
//		SCREEN	SUB STATE CALLBACKS
//----------------------------------------------------------------

void ScrnStatInitSubstate( void )
{
	pMainFrame->SetUI(&UI_STAT_SCREEN_STATE);
	pMainFrame->SetUIOverride(KeyOverride_GAME_STAT_SCREEN_STATE);
	pMainFrame->PausePageFlip();

	ScrnSetState( SCRN_STATS_STATE );

	ShowTheCursor( TRUE );
}

void ScrnStatEndSubstate( void )
{
	// release any residual screen data
	if ( SCRNfullScreen )
	{
		ScrnDelete( SCRNfullScreen );
		SCRNfullScreen = NULL;
	}

	// now copy the back buffer into the front to restore
	// the last played background
	DDCopyBackToFront();

	// release any residual campaign data
	SObjReleaseCampaignData( );

	if( gpGame->GetSubState() == PLAY_SETUP_SUB_STATE )
		pMainFrame->SetUI(&UI_GAME_SETUP_STATE);
	else
		pMainFrame->SetUI(&UI_GAME_PLAY_STATE);									// disable user-interface...
	pMainFrame->SetUIOverride(NULL);
	pMainFrame->UnPausePageFlip();

	// restart the audio
	audioEnable( pMainFrame->m_hWnd );
}


void ScrnOptionsInitSubstate( void )
{
	// now copy the back buffer into the front to restore
	// the last played background
	DDCopyBackToFront();

	// set up the UI for this screen
	pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
	pMainFrame->SetUIOverride(KeyOverride_GAME_TITLE_SCREEN_STATE);
	pMainFrame->PausePageFlip();

	ScrnSetState( SCRN_PLAY_OPTIONS_STATE );

	ShowTheCursor( TRUE );
}

void ScrnOptionsEndSubstate( void )
{
	// release any residual screen data
	if ( SCRNfullScreen )
	{
		ScrnDelete( SCRNfullScreen );
		SCRNfullScreen = NULL;
	}
}

LONG	ScrnKeypadInitState( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;

	// build an screen
	SetPath( SCREEN_PATH );

	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		pScreenDef  = &SCRNKeypad2Screen;

		// now copy the back buffer into the front to restore
		// the last played background
		DDCopyBackToFront();
	}
	else
		pScreenDef  = &SCRNKeypadScreen;

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	// now go load up the configuration data
	ScrnLoadConfiguration( pNewScreen, CONFIG_DEFAULT1, TRUE );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor( TRUE );
	return(0);
}

LONG	ScrnKeyboardInitState( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;

	// build an screen
	SetPath( SCREEN_PATH );

	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		pScreenDef  = &SCRNKeyboard2Screen;

		// now copy the back buffer into the front to restore
		// the last played background
		DDCopyBackToFront();
	}
	else
		pScreenDef  = &SCRNKeyboardScreen;

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	// now go load up the configuration data
	ScrnLoadConfiguration( pNewScreen, CONFIG_DEFAULT2, TRUE );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor( TRUE );
	return ( 0 );
}

LONG	ScrnCustomInitState( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;

	// build an screen
	SetPath( SCREEN_PATH );

	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		pScreenDef  = &SCRNCustom2Screen;

		// now copy the back buffer into the front to restore
		// the last played background
		DDCopyBackToFront();
	}
	else
		pScreenDef  = &SCRNCustomScreen;

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	// now go load up the configuration data
	ScrnLoadConfiguration( pNewScreen, CONFIG_CUSTOM, TRUE );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor( TRUE );
	return(0);
}

void	ScrnLoadConfiguration( HSCREEN hScreen, CONFIG eConfigType, BOOL bUseOffset )
{
	HSCREENOBJ			hScreenObj;
	int					nObject;
	int					nOffsetIndex;
	short				nOffset;
	int					nKeyIndex;
	SPOINT				spOffset;

	nKeyIndex    = 0;
	nObject      = SARGE_KEY_START_INDEX;
	nOffsetIndex = 0;
	spOffset.x   = 0;
	while( SargeKeyDescs[nKeyIndex].dispatcher != NULL )
	{
		// see if there is a dispatcher routine for this keycode
		hScreenObj = hScreen->pScreenObjs[ nObject ];
		if ( hScreenObj )
		{
			// calculate the offset
			nOffset    = KEYOFFSET * nOffsetIndex;
			spOffset.y = nOffset;

			ScrnLoadSargeKeycode( hScreenObj, eConfigType, nKeyIndex );

			// offset the Object
			if ( bUseOffset )
				SObjApplyOffset( hScreenObj, &spOffset, APPLY_AS_IS );

			++nOffsetIndex;
			++nObject;
		}
		++nKeyIndex;
	}

	nKeyIndex    = 0;
	nObject      = GAME_KEY_START_INDEX;
	nOffsetIndex = 0;
	spOffset.x   = 0;
	while( GamePlayKeyDescs[nKeyIndex].dispatcher != NULL )
	{
		hScreenObj = hScreen->pScreenObjs[ nObject ];
		if ( hScreenObj )
		{
			ScrnLoadGameKeycode( hScreenObj, eConfigType, nKeyIndex );

			// calculate the offset
			nOffset    = KEYOFFSET * nOffsetIndex;
			spOffset.y = nOffset;

			// offset the Object
			if ( bUseOffset )
				SObjApplyOffset( hScreenObj, &spOffset, APPLY_AS_IS );

			++nOffsetIndex;
			++nObject;
		}
		++nKeyIndex;
	}
}

void	ScrnLoadJoystickConfiguration( HSCREEN hScreen, CONFIG eConfigType, BOOL bUseOffset )
{
	HSCREENOBJ			hScreenObj;
	int					nObject;
	int					nOffsetIndex;
	short				nOffset;
	int					nKeyIndex;
	SPOINT				spOffset;

	nKeyIndex    = 0;
	nObject      = JOYSTICK_BUTTON_START_INDEX;
	nOffsetIndex = 0;
	spOffset.x   = 0;
	while( JoystickDescs[nKeyIndex].dispatcher != NULL )
	{
		// see if there is a dispatcher routine for this keycode
		hScreenObj = hScreen->pScreenObjs[ nObject ];
		if ( hScreenObj )
		{
			// calculate the offset
			nOffset    = KEYOFFSET * nOffsetIndex;
			spOffset.y = nOffset;

			ScrnLoadSargeKeycode( hScreenObj, eConfigType, nKeyIndex );

			// offset the Object
			if ( bUseOffset )
				SObjApplyOffset( hScreenObj, &spOffset, APPLY_AS_IS );

			++nOffsetIndex;
			++nObject;
		}
		++nKeyIndex;
	}

}

#define	CUSTOM_KEY_INDEX	1
#define	FIXED_KEY_INDEX		0

void	ScrnLoadSargeKeycode( HSCREENOBJ hScreenObj, CONFIG eConfigType, int nKeyIndex )
{
	HSCREENBTN			hScreenBtn;
	HSCREENBTN			hFixedScreenBtn = NULL;
	BYTE				cKey;
	BYTE				cFixedKey = 0;
	char*				pDescription=NULL;
	DWORD				dwData;							// button user data

	hScreenBtn		= hScreenObj->hScreenBtns[ CUSTOM_KEY_INDEX ];
	hFixedScreenBtn = hScreenObj->hScreenBtns[ FIXED_KEY_INDEX ];
	switch( eConfigType )
	{
	case CONFIG_DEFAULT1:
		cKey      = SargeKeyDescs[nKeyIndex].DefaultKey1;
		cFixedKey = SargeKeyDescs[nKeyIndex].FixedKey;
		pDescription = SargeKeyDescs[nKeyIndex].desc;
		break;
	case CONFIG_DEFAULT2:
		cKey      = SargeKeyDescs[nKeyIndex].DefaultKey2;
		cFixedKey = SargeKeyDescs[nKeyIndex].FixedKey;
		pDescription = SargeKeyDescs[nKeyIndex].desc;
		break;
	case CONFIG_CUSTOM:
		cKey      = SargeKeyDescs[nKeyIndex].CustomKey;
		cFixedKey = SargeKeyDescs[nKeyIndex].FixedKey;
		pDescription = SargeKeyDescs[nKeyIndex].desc;
		break;
	case CONFIG_JOYSTICK:
		cKey         = JoystickDescs[nKeyIndex].CustomKey;
		pDescription = JoystickDescs[nKeyIndex].desc;
		break;

	default:
		return;
	}
	if ( pDescription && (*pDescription != '\0') )
		SObjSetTitle( hScreenObj, pDescription );

	if ( eConfigType == CONFIG_JOYSTICK )
		pDescription = GetJoystickButtonStr( cKey );
	else
		pDescription = SBtnKeycodeName(cKey);

	if ( pDescription )
	{
		dwData = nKeyIndex;
		SBtnSetData( hScreenBtn, dwData );
		SBtnSetText( hScreenBtn, pDescription );
	}

	if ( cFixedKey && (eConfigType != CONFIG_JOYSTICK) )
	{
		pDescription = KeysText[ cFixedKey ];

		if ( pDescription )
			SBtnSetText( hFixedScreenBtn, pDescription );

		SBtnClearAttributes( hFixedScreenBtn, SBTN_INVISIBLE );
		hFixedScreenBtn->bUpdate = TRUE;
	}

	// now make this object and button visible
	SObjClearAttributes( hScreenObj, SOBJ_INVISIBLE );
	hScreenObj->bUpdate = TRUE;
	SBtnClearAttributes( hScreenBtn, SBTN_INVISIBLE );
	hScreenBtn->bUpdate = TRUE;
}

void	ScrnLoadGameKeycode( HSCREENOBJ hScreenObj, CONFIG eConfigType, int nKeyIndex )
{
	HSCREENBTN			hScreenBtn;
	HSCREENBTN			hFixedScreenBtn = NULL;
	BYTE				cKey;
	BYTE				cFixedKey = 0;
	char*				pDescription=NULL;
	DWORD				dwData;							// button user data

	hScreenBtn		= hScreenObj->hScreenBtns[ CUSTOM_KEY_INDEX ];
	hFixedScreenBtn = hScreenObj->hScreenBtns[ FIXED_KEY_INDEX ];
	switch( eConfigType )
	{
	case CONFIG_DEFAULT1:
		cKey = GamePlayKeyDescs[nKeyIndex].DefaultKey1;
		cFixedKey = GamePlayKeyDescs[nKeyIndex].FixedKey;
		break;
	case CONFIG_DEFAULT2:
		cKey = GamePlayKeyDescs[nKeyIndex].DefaultKey2;
		cFixedKey = GamePlayKeyDescs[nKeyIndex].FixedKey;
		break;
	case CONFIG_CUSTOM:
		cKey      = GamePlayKeyDescs[nKeyIndex].CustomKey;
		cFixedKey = GamePlayKeyDescs[nKeyIndex].FixedKey;
		break;
	case CONFIG_JOYSTICK:
		cKey      = JoystickDescs[nKeyIndex].CustomKey;
		return;
	default:
		return;
	}

	pDescription = GamePlayKeyDescs[nKeyIndex].desc;
	if ( pDescription && (*pDescription != '\0') )
		SObjSetTitle( hScreenObj, pDescription );
	else
		TRACE("This is what your're looking for!\n");

	pDescription = SBtnKeycodeName(cKey);
	if ( pDescription )
	{
		dwData = (GAME_KEY_FLAG | (DWORD)nKeyIndex );
		SBtnSetData( hScreenBtn, dwData );
		SBtnSetText( hScreenBtn, pDescription );
	}

	if ( cFixedKey )
	{
		pDescription = KeysText[ cFixedKey ];
		if ( pDescription )
			SBtnSetText( hFixedScreenBtn, pDescription );

		SBtnClearAttributes( hFixedScreenBtn, SBTN_INVISIBLE );
		hFixedScreenBtn->bUpdate = TRUE;
	}

	// now make this object and button visible
	SObjClearAttributes( hScreenObj, SOBJ_INVISIBLE );
	hScreenObj->bUpdate = TRUE;
	SBtnClearAttributes( hScreenBtn, SBTN_INVISIBLE );
	hScreenBtn->bUpdate = TRUE;
}

char*	ScrnFindSargeDesc( BYTE nKeyCode, CONFIG eConfigType )
{
	BYTE				cKeyIndex;
	BYTE				cKey;
	char*				pDescription = NULL;
	BOOL				bFound;

	cKeyIndex = 0;
	bFound    = FALSE;
	while( !bFound && SargeKeyDescs[cKeyIndex].dispatcher )
	{
		cKey = SargeKeyDescs[cKeyIndex].CustomKey;
		if (  cKey == nKeyCode )
			bFound = TRUE;
		else
			++cKeyIndex;
	}

	if (bFound)
		pDescription = SargeKeyDescs[cKeyIndex].desc;
	return( pDescription );
}

char*	ScrnFindGameDesc( BYTE nKeyCode, CONFIG eConfigType )
{
	BYTE				cKeyIndex;
	BYTE				cKey;
	char*				pDescription = NULL;
	BOOL				bFound;

	cKeyIndex = 0;
	bFound    = FALSE;
	while( !bFound && GamePlayKeyDescs[cKeyIndex].dispatcher )
	{
		cKey = GamePlayKeyDescs[cKeyIndex].CustomKey;
		if ( cKey == nKeyCode )
			bFound = TRUE;
		else
			++cKeyIndex;
	}

	if (bFound)
		pDescription = GamePlayKeyDescs[cKeyIndex].desc;

	return( pDescription );
}

LONG	ScrnJoystickInitState( HSCREEN* hScreen )
{
	HSCREEN			pNewScreen;
	SCREENDEF*		pScreenDef;

	// build an screen
	SetPath( SCREEN_PATH );

	if ( gpGame->GetState() == GAME_PLAY_STATE )
	{
		pScreenDef  = &SCRNJoystick2Screen;

		// now copy the back buffer into the front to restore
		// the last played background
		DDCopyBackToFront();
	}
	else
		pScreenDef  = &SCRNJoystickScreen;

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	ScrnLoadDef( pNewScreen, pScreenDef );

	// now go load up the configuration data
	ScrnLoadJoystickConfiguration( pNewScreen, CONFIG_JOYSTICK, TRUE );

	pNewScreen->bUpdate = TRUE;
	*hScreen            = pNewScreen;

	ShowTheCursor( TRUE );
	return(0);
}

void ScrnLoadStatValue( HSCREENOBJ hScreenObj, int nValue )
{
	char	pValue[ SCRN_VALUE_SIZE+1 ];

	// convert the value to a right justified string
	sprintf( pValue,"%5d", nValue );

	// apply this text to the object title
	SObjSetTitleFont( hScreenObj, FONT_TIMES_14 );
	SObjSetTitleBGColor( hScreenObj, SBTN_TRANSPARENT );
	SObjSetTitleFGColor( hScreenObj, SBTN_WHITE );
	SObjSetTitle( hScreenObj, pValue );
}

//========================================================================
//	Function:		ScrnDeletePlayerFiles()
//
//	Description:
//		delet all existing .ASF ( Armymen Statistics File ) file for a playerName.
//
//	Input:			pPlayerName		player name for .ASF filename construction
//
//	Ouput:			none
//
//========================================================================

void	ScrnDeletePlayerFiles( char* pPlayerName )
{
	char			ASFname[STAT_MAX_REF_LEN+1];
	HANDLE			hFileCtl;
	WIN32_FIND_DATA	fileData;
	DWORD			bFileFound = FALSE;			// assume no files

	SetPath(SAVE_PATH);
	sprintf( ASFname, "%s*.asf\0\0", pPlayerName );

#ifdef SBTN_DEBUG
	TRACE( "WARNING: deleting player (%s) and associated data files (%s)\n",
		   pPlayerName, ASFname );
#endif

	// look for the first file with this suffix
	hFileCtl = FindFirstFile( ASFname, &fileData );
	if ( hFileCtl != INVALID_HANDLE_VALUE )
		bFileFound = TRUE;

	// delete this first file and then look for others
	while ( bFileFound )
	{
#ifdef SBTN_DEBUG
		TRACE( "Deleting player ASF file (%s)\n", fileData.cFileName );
		if ( DeleteFile( fileData.cFileName ) != TRUE )
			TRACE( "WARNING: could not delete file %s\n", fileData.cFileName );
#else
		DeleteFile( fileData.cFileName );
#endif
		bFileFound = FindNextFile( hFileCtl, &fileData );
	}
	FindClose( hFileCtl );

	// now delete any STAT name references
	StatsDeleteName( pPlayerName );
}

//========================================================================
//	Function:		ScrnGetStateName()
//
//	Description:
//		retrieve the name of the screen state passed in.
//
//	Input:			eState			current screen state
//
//	Ouput:			State Name String
//
//========================================================================

char*	ScrnGetStateName( SCRN_STATE eState )
{
	if ( eState == SCRN_NULL_STATE )
		return( SCRNnullStateName );
	else
		return( SCRNstateName[ eState ] );
}

LONG	ScrnWhatIsNext( void )
{
	ASSERT(gpGame->GameType == GAMETYPE_ONEPLAYER);

	// check to see if we are at the end of a mission
	// or the end of a scenario
	if ( ArmyHaveNextMission() )	// end of mission, go on to next
	{
		// start by re-enabling the audio
		gameNoisy();

		// continuing into another mission
		gpGame->newMission = FALSE;

		// mission music off
		MissionMusic( TRUE );

		// start up the game and then execute the mission message
		if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
		{
			gpGame->SetSubState( PLAY_SUB_STATE );

			// set a delay for PAUSE
			gpGame->nPauseDelay = 2;
			gpGame->m_DelayFunc = UI_MissionRecall;
		}
		else	{
			gpGame->SetSubState( PLAY_SETUP_SUB_STATE );
		}

		if (gpGame->GetState() != GAME_PLAY_STATE)
			gpGame->SetState( GAME_PLAY_STATE );
	}
	else
	{
		ScrnSetState( SCRN_NULL_STATE );

		if ( ArmyHaveNextScenario() )	// end of scenario, go onto next
		{
			;
		}
		else if ( ArmyHaveNextCampaign() )	// end of campaign, go onto next
		{
			;
		}
		else	// player is finished the entire disk
			ASSERT(0);

		ScrnSetState( SCRN_NULL_STATE );
		gpGame->newMission = TRUE;

		MISSIONREF* pMission = GetMission();
		char buffer[32];

		strcpy(buffer, pMission->pFileName);
		strcat( buffer, ".AMM" );
		gpGame->MapName = buffer;

		pMainFrame->StartGame();	// start the game

	}

	return( SBTN_STATE_CHANGE );
}

//----------------------------------------------------------------
//		SCREEN	MULTI PLAYER CALLBACKS
//----------------------------------------------------------------

LONG	ScrnInitHost( HSCREEN* hScreen )
{
	int					i;
	int					nSlot;
	int					nColor;
	SPOINT				offset;
	SBTN_COLOR			eColor;
	HSCREEN				pNewScreen;
	HSCREENOBJ			hScreenObj;
	HSCREENBTN			hScreenBtn;
	HSCREENBTN			hClickedBtn;
	CHAT_STRUCT_RECEIVE	*chat_receive;
	SCREENDEF			*pScreenDef = &SCRNhostSelectScreen;
	LPDPSESSIONDESC2	lpSessionDesc;
	HRESULT				hr;


	// turn off all existing audio
	audioStopAll();

	if ( GetFocus() != pMainFrame->GetHwnd() ) TRACE("ScrnInitHost Entered without Focus \n");

	// cursor off
	ShowWindowsCursor( FALSE );

	// build an screen
	SetPath( SCREEN_PATH );
	SCRNmultiStartOK = FALSE;
	for( i=0;i<ARMY_LAST_ARMY;++i)
		gpComm->m_ArmyGotMap[i] = FALSE;

	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	*hScreen           = pNewScreen;
	pNewScreen->eState = SCRN_MULTI_HOST_STATE;
	ScrnLoadDef( pNewScreen, pScreenDef );

	// get the Chat Send object and change its color to that of the player
	hScreenObj = pNewScreen->pScreenObjs[CHAT_SEND_OBJECT];
	hScreenBtn = hScreenObj->hScreenBtns[ 0 ];
	nColor     = PlayerColor( ARMY_PLAYER );
	if ( nColor == ARMY_NO_COLOR )
		eColor = SBTN_WHITE;
	else
		eColor     = (SBTN_COLOR)PlayerBtnColorTable[ nColor ];
	SBtnSetFGColor( hScreenBtn, BUTTON_NULL,    eColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_FOCUSED, eColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_CLICKED, eColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_EDIT,    eColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_DISABLED,eColor );

	// now apply offsets to campaign file lists
//	SCRNruleFileIndex = 0;
	hScreenObj = pNewScreen->pScreenObjs[CAMPAIGN_LIST_OBJECT];
	nSlot = 0;
	offset.x = 0;
	offset.y = 0;
	for( nSlot=0; nSlot<hScreenObj->nNumberBtns; ++nSlot )
	{
		hScreenBtn = hScreenObj->hScreenBtns[ nSlot ];
		SBtnApplyOffset( hScreenBtn, &offset );
		offset.y += 20;

		if ( (nSlot == 0) && hScreenBtn )
			hClickedBtn = hScreenBtn;
	}

	// clear the chat information block
	chat_receive = &(SCRNchat.chatReceive);
	ZeroMemory( chat_receive, sizeof(CHAT_STRUCT_RECEIVE) );
	for (i=0;i<CHAT_MESSAGES_ONSCREEN;i++)
		chat_receive->pStrings[i]=&(chat_receive->strings[i*(CHAT_MAX_WITH_NAME+1)]);
	chat_receive->nCurrentTopString = 0;

	pMainFrame->SetUI(&UI_MPUI_SCREEN_STATE);
	pMainFrame->SetUIOverride(KeyOverride_MPUI_SCREEN_STATE);

	// tell the world
	pNewScreen->bUpdate = TRUE;
	for (i= 1; i<(int)4 ; i++) {
		if( gpComm->m_PlayerId[i] == 0xffffffff)   //  This player left the game
			gpComm->RemovePlayer(gpComm->m_PlayerId[i]);
	}

	// Open up the session again so new players can join between games
	if (gpComm->m_NumDPPlayers < 4) {
		gpComm->GetSessionDesc();
		lpSessionDesc = gpComm->m_pSDesc ;
		if(lpSessionDesc ) {
			lpSessionDesc->dwFlags &= ~( DPSESSION_JOINDISABLED | DPSESSION_NEWPLAYERSDISABLED );
			hr = gpComm->SetSessionDesc(lpSessionDesc,0);
			if ( FAILED( hr )  )   TRACE("Set Session Failed to reopen Session\n");
		}
	}
	// now do a complete update of the host data
	ScrnUpdateHost();

	// Tell everyone we are back in map Load screen;
	SendGameReadyMsg(FALSE);
//	SendPlayerMsg(TRUE);

	// Start the timer to Update the Names periodically to indicate latency
	pMainFrame->m_EventTimerID = pMainFrame->SetTimer( NameUpdateTimer, NameUpdateTime, NULL);
	return( 0 );
}

LONG	ScrnTerminateHost( HSCREEN* hScreen )
{
	if ( pMainFrame->m_EventTimerID) { pMainFrame->KillTimer ( pMainFrame->m_EventTimerID); pMainFrame->m_EventTimerID = 0;}
	ScrnTerminateScreen( hScreen );

	pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
//	pMainFrame->SetUIOverride(KeyOverride_GAME_TITLE_SCREEN_STATE);
	pMainFrame->SetUIOverride(NULL);

	gameNoisy();

	return( SBTN_STATE_CHANGE );
}

void	ScrnUpdateHost( void )
{
	if ( !SCRNfullScreen || (ScrnGetState() != SCRN_MULTI_HOST_STATE) || (GetFocus() != pMainFrame->GetHwnd()) )
//	if ( !SCRNfullScreen || (GetFocus() != pMainFrame->GetHwnd()) )
		return;
#ifdef SCRN_DEBUG
	TRACE("ScrnUpdateHost( void )\n" );
#endif

	// update all the color buttons
	ScrnColorButtonUpdate( SCRNfullScreen );

	// update all the LEDs
	ScrnLEDUpdate( SCRNfullScreen );

	// update all the player names
	ScrnPlayerNamesUpdate( SCRNfullScreen );

	// update the map choices
	ScrnMapUpdateHost( SCRNfullScreen );
}

LONG	ScrnInitRemote( HSCREEN* hScreen )
{
	int					i;
	int					nColor;
	int					error;
	CHAT_STRUCT_RECEIVE	*chat_receive;
	SBTN_COLOR			eColor;
	HSCREEN				pNewScreen;
	HSCREENOBJ			hScreenObj;
	HSCREENBTN			hScreenBtn;
	SCREENDEF			*pScreenDef = &SCRNremoteSelectScreen;

	// turn off all existing audio
	audioStopAll();
 	if ( GetFocus() != pMainFrame->GetHwnd() ) TRACE("ScrnInitRemote Entered without Focus \n");

	// build an screen
	SetPath( SCREEN_PATH );
	pNewScreen = ScrnCreate( &(pScreenDef->position), (USHORT)(pScreenDef->bAttributes) );
	ASSERT( pNewScreen );

	*hScreen           = pNewScreen;
	pNewScreen->eState = SCRN_MULTI_REMOTE_STATE;
	ScrnLoadDef( pNewScreen, pScreenDef );

	// get the Chat Send object and change its color to that of the player
	hScreenObj = pNewScreen->pScreenObjs[CHAT_SEND_OBJECT];
	hScreenBtn = hScreenObj->hScreenBtns[ 0 ];
	nColor     = PlayerColor( ARMY_PLAYER );
	if ( nColor == ARMY_NO_COLOR )
		eColor = SBTN_WHITE;
	else
		eColor     = (SBTN_COLOR)PlayerBtnColorTable[ nColor ];
	SBtnSetFGColor( hScreenBtn, BUTTON_NULL,    eColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_FOCUSED, eColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_CLICKED, eColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_DISABLED,eColor );
	SBtnSetFGColor( hScreenBtn, BUTTON_EDIT,    eColor );

	// clear the chat information block
	chat_receive = &(SCRNchat.chatReceive);
	ZeroMemory( chat_receive, sizeof(CHAT_STRUCT_RECEIVE) );
	for (i=0;i<CHAT_MESSAGES_ONSCREEN;i++)
		chat_receive->pStrings[i]=&(chat_receive->strings[i*(CHAT_MAX_WITH_NAME+1)]);
	chat_receive->nCurrentTopString = 0;

	pMainFrame->SetUI(&UI_MPUI_SCREEN_STATE);
	pMainFrame->SetUIOverride(KeyOverride_MPUI_SCREEN_STATE);

	pNewScreen->bUpdate = TRUE;
	for (i= 1; i<(int)4 ; i++) {
		if( gpComm->m_PlayerId[i] == 0xffffffff)   //  This player left the game
			gpComm->RemovePlayer(gpComm->m_PlayerId[i]);
	}

	// Tell host we are back in Map Selection Sreeen
	SendGameReadyMsg(FALSE);

	// now do a complete update of the remote data
	error = ScrnUpdateRemote();
	if ( error )
		ScrnReportMapError( error );

	ShowTheCursor( TRUE );
	// Start the timer to Update the Names periodically to indicate latency
	pMainFrame->m_EventTimerID = pMainFrame->SetTimer( NameUpdateTimer, NameUpdateTime, NULL);
	return( 0 );
}

LONG	ScrnTerminateRemote( HSCREEN* hScreen )
{
	if ( pMainFrame->m_EventTimerID) { pMainFrame->KillTimer ( pMainFrame->m_EventTimerID); pMainFrame->m_EventTimerID = 0;}
	ScrnTerminateScreen( hScreen );

	pMainFrame->SetUI(&UI_TITLE_SCREEN_STATE);
//	pMainFrame->SetUIOverride(KeyOverride_GAME_TITLE_SCREEN_STATE);
	pMainFrame->SetUIOverride(NULL);

	gameNoisy();

	return( SBTN_STATE_CHANGE );
}

int	ScrnUpdateRemote( void )
{
	int	error = 0;

	if ( !SCRNfullScreen || (ScrnGetState() != SCRN_MULTI_REMOTE_STATE) || (GetFocus() != pMainFrame->GetHwnd()) )
//	if ( !SCRNfullScreen || (GetFocus() != pMainFrame->GetHwnd())  )
		return ( error );

#ifdef SCRN_DEBUG
	TRACE("ScrnUpdateRemote( void )\n" );
#endif

	// update all the color buttons
	ScrnColorButtonUpdate( SCRNfullScreen );

	// update all the LEDs
	ScrnLEDUpdate( SCRNfullScreen );

	// update all the player names
	ScrnPlayerNamesUpdate( SCRNfullScreen );

	// update map
	error = ScrnMapUpdateRemote( SCRNfullScreen );
	
	return( error );
}

LONG	ScrnOnRequestColor( HSCREENBTN hScreenBtn )
{
	int			nObject;
	HSCREENOBJ	hObj;
	HSCREENBTN	hBtn;
	ARMY_COLOR	nColor = ARMY_NO_COLOR;

	// retrieve the color
	nColor = (ARMY_COLOR)(hScreenBtn->dwData);

	// check to see if this is our color already and the player
	// is releasing it.
	if ( nColor == PlayerColor(ARMY_PLAYER) )	// release the color
	{
#ifdef SCRN_DEBUG
	TRACE("ScrnOnRequestColor( RELEASE color %d )\n", PlayerColor(ARMY_PLAYER), nColor );
#endif
		gpComm->ReleaseColor(gpComm->m_PlayerId[0] );
	}
	else										// acquire the color
	{
#ifdef SCRN_DEBUG
	TRACE("ScrnOnRequestColor( ACQUIRE color %d )\n", PlayerColor(ARMY_PLAYER), nColor );
#endif
		gpComm->AcquireColor(gpComm->m_PlayerId[0], nColor );
	}

	// now pop up all the other color buttons
	for( nObject=GREEN_BUTTON;nObject<=GRAY_BUTTON;++nObject)
	{
		if ( nObject != nColor )
		{
			hObj = SCRNfullScreen->pScreenObjs[nObject];
			if ( hObj )
			{
				hBtn = hObj->hScreenBtns[0];
				if ( hBtn )
				{
					if ( SBtnGetState( hBtn ) != SBTN_DISABLED )
					{
#ifdef SCRN_DEBUG
	TRACE("ScrnOnRequestColor( Player color %d - non color %d ) BUTTON_NULL\n", nColor, nObject );
#endif
						SBtnSetState( hBtn, BUTTON_NULL );
					}
				}
			}
		}
	}

	// disable any further clicks of this button
	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// force an update of this button
	hScreenBtn->bUpdate = TRUE;

	// now send out a color message
	SendColorMsg( (DWORD)nColor );
	if( gpComm->m_bHost ) {
		ScrnUpdateHost();
		SendPlayerMsg(FALSE);
	}
	
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnStartMulti( HSCREENBTN hScreenBtn )
{
#ifdef	SBTN_DEBUG
	TRACE("StartMultiPlayer: communications initialized...\n");
#endif

	if ( SCRNmultiStartOK && gpComm->EverybodyInMapSelection() )
	{
		// tell the other players you are ready
		pMainFrame->PostMessage( UM_TDG_LAUNCH, 0, 0 );
		SendGameStartMsg();
		SBtnSetState( hScreenBtn, BUTTON_NULL );

		// stablize the campaign data, indirect effect on Multiplayer
		gpGame->start_game = FALSE;
		SetPath(CAMPAIGN_PATH);
		AiCampaignLoad( "campaign.cpn" );
		pMainFrame->StartGame();
	}
	else
	{
		SBtnSetState( hScreenBtn, BUTTON_NULL );
		audioPlay( BULLET_HIT_OBJECT, SND_SFX_FLAG | SND_DELETE_FLAG );
	}

	SCRNmultiStartOK = FALSE;
	
	return( SBTN_STATE_CHANGE );
}

LONG	ScrnOnExitMulti( HSCREENBTN hScreenBtn )
{
	BOOL lobbyStart = gpComm->m_bStartedByLobby;
	gpComm->Disconnect();
	ScrnSetState( SCRN_GAME_START_STATE );

	audioEnable( pMainFrame->m_hWnd );
	gpGame->GameType   = GAMETYPE_ONEPLAYER;
 	if (lobbyStart) return (ScrnOnQuit(hScreenBtn));

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnSelectMultiMap( HSCREENBTN hScreenBtn )
{
	int				nSlot;
	char			buffer[64];
	HSCREENOBJ		hScreenObject;
	HSCREENBTN		hBtn;
	SOBJIMAGEDEF	mapImage;
	static BOOL		rules_error = FALSE;
	static BOOL		map_error = FALSE;
	static BOOL		image_error = FALSE;

    if ( hScreenBtn->hPrevClicked == hScreenBtn )
		return(0);
	else
	if ( hScreenBtn->hPrevClicked )
		SBtnSetState( hScreenBtn->hPrevClicked, BUTTON_NULL );

    if ( hScreenBtn->bAttributes == SBTN_CLICK_BYPASS )
		return(0);

	ZeroMemory( &mapImage, sizeof( SOBJIMAGEDEF ) );

	// get the base file name
	SetPath( MAP_PATH );
	strcpy( buffer, hScreenBtn->pText );
	if ( *buffer == '\0' )
		return( -1 );

	gpGame->RuleName = buffer;
	gpGame->RuleName += ".RUL";

#if 0
TRACE("\nRuleName = %s\n", gpGame->RuleName );
#endif

	rules_error = ReadRules((const char *) gpGame->RuleName);
	if (rules_error == RULE_FILE_OK)
	{
		hScreenObject          = SCRNfullScreen->pScreenObjs[ RULES_OBJECT ];
		hScreenObject->bUpdate = TRUE;

		// get the map bmp reference
		CopyBaseFileName( mapImage.bkgRef, (const char *) gpGame->MapName);

		if (FileExist(gpGame->MapName))
			gpGame->MapSum = MapLoadSum(gpGame->MapName);
		else
		{
			// use the default map file for now
			strcpy( mapImage.bkgRef, default_name );
			gpGame->MapName = "\0";
		}
	}
	else	{
		strcpy( mapImage.bkgRef, default_name );
	}
	map_error = FALSE;

	// signify that we now a valid game selected
	gpComm->m_ArmyGotMap[ ARMY_PLAYER ] = TRUE;

	// get the stratmap object and change its BKG reference
	strcat( mapImage.bkgRef, "_mp.BMP" );
	hScreenObject = SCRNfullScreen->pScreenObjs[START_MAP_OBJECT];
	if ( SObjSetBkgImage( hScreenObject, &mapImage ) )
	{
		TRACE( "Stratmap file (%s) does not exist\n", mapImage.bkgRef );
		SCRNmultiStartOK = FALSE;
	}

	// get the map image information and possibly the rules
	image_error = ScrnVerifyMap( &mapImage );
#if 0
	TRACE( "ScrnSelectMultiMap(): ScrnVerifyMap( %d )\n", image_error );
#endif
	if ( image_error == MAP_OK )
		ScrnUpdateRules(TRUE);
	else
		ScrnReportMapError( image_error );

	// make ourselves the previously clicked button so that
	// we'll ignore ourselves later
	hScreenBtn->hPrevClicked = hScreenBtn;

	// time to force an update
	hScreenObject = SCRNfullScreen->pScreenObjs[CAMPAIGN_LIST_OBJECT];
	for( nSlot=0; nSlot<(hScreenObject->nNumberBtns); ++nSlot )
	{
		hBtn = hScreenObject->hScreenBtns[ nSlot ];
		if (hBtn != hScreenBtn )
		{
			hBtn->hPrevClicked = NULL;
			SBtnSetState( hBtn, BUTTON_NULL );
		}
	}

	hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;

	// now force an update of the screen
	ScrnMapUpdateHost( SCRNfullScreen );

	// send a message annoucing the map selection
	SendPlayerMsg(TRUE);

	return( SBTN_STATE_CHANGE );
}

LONG	ScrnScrollUp( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;
	TCHAR		filename[DLG_MAX_FILENAME + 1];
	int			nIndex;
	int			nSlot;

	// the first thing to do is disable this button
	// until a button up occurs
	if ( SCRNruleFileIndex )
	{
		--SCRNruleFileIndex;

		// time to force an update
		hScreenObj = SCRNfullScreen->pScreenObjs[CAMPAIGN_LIST_OBJECT];
		nIndex     = SCRNruleFileIndex;
		nSlot      = 0;
		while( (nSlot<hScreenObj->nNumberBtns) && (nIndex<SCRNruleIndex) )
		{
			hBtn               = hScreenObj->hScreenBtns[ nSlot ];
			hBtn->hPrevClicked = NULL;
			SBtnSetText( hBtn, SCRNruleFiles[ nIndex ] );

			// see if we should select this map
			strcpy( filename, SCRNruleFiles[ nIndex ]);
			strcat( filename, ".RUL" );
			if ( strcmp( filename, gpGame->RuleName) == 0 )
			{
				hBtn->eScreenBtnState = BUTTON_CLICKED;
				hBtn->bAttributes    |= SBTN_CLICK_BYPASS;
			}
			else
			{
				hBtn->eScreenBtnState = BUTTON_NULL;
				hBtn->bAttributes    &= ~SBTN_CLICK_BYPASS;
			}
			hBtn->bUpdate = TRUE;

			// update indecies
			++nIndex;
			++nSlot;
		}
		SObjForceUpdate( hScreenObj );
	}
	else
		audioPlay( BULLET_HIT_OBJECT, SND_SFX_FLAG | SND_DELETE_FLAG );

	// allows multiple CLICKs
	SBtnSetState( hScreenBtn, BUTTON_NULL );
	hScreenBtn->bUpdate = TRUE;

	// now update the vertical scroll bar
	hScreenObj = SCRNfullScreen->pScreenObjs[VERTICAL_SCROLL_OBJECT];
	SObjForceUpdate( hScreenObj );

	return( 0 );
}

LONG	ScrnScrollDn( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;
	TCHAR		filename[DLG_MAX_FILENAME + 1];
	int			nIndex;
	int			nSlot;

	// now enumerate the data
	if ( SCRNruleFileIndex+4 <= SCRNruleIndex )
	{
		++SCRNruleFileIndex;

		// time to force an update
		hScreenObj = SCRNfullScreen->pScreenObjs[CAMPAIGN_LIST_OBJECT];
		nIndex     = SCRNruleFileIndex;
		nSlot      = 0;
		while( (nSlot<hScreenObj->nNumberBtns) && (nIndex<SCRNruleIndex) )
		{
			hBtn               = hScreenObj->hScreenBtns[ nSlot ];
			hBtn->hPrevClicked = NULL;
			SBtnSetText( hBtn, SCRNruleFiles[ nIndex ] );

			// see if we should select this map
			strcpy( filename, SCRNruleFiles[ nIndex ]);
			strcat( filename, ".RUL" );
			if ( strcmp( filename, gpGame->RuleName) == 0 )
			{
				hBtn->eScreenBtnState = BUTTON_CLICKED;
				hBtn->bAttributes    |= SBTN_CLICK_BYPASS;
			}
			else
			{
				hBtn->eScreenBtnState = BUTTON_NULL;
				hBtn->bAttributes    &= ~SBTN_CLICK_BYPASS;
			}
			hBtn->bUpdate = TRUE;

			// update indecies
			++nIndex;
			++nSlot;
		}
		SObjForceUpdate( hScreenObj );
	}
	else
		audioPlay( BULLET_HIT_OBJECT, SND_SFX_FLAG | SND_DELETE_FLAG );

	// allows multiple CLICKs
	SBtnSetState( hScreenBtn, BUTTON_NULL );
	hScreenBtn->bUpdate = TRUE;

	// now update the vertical scroll bar
	hScreenObj = SCRNfullScreen->pScreenObjs[VERTICAL_SCROLL_OBJECT];
	SObjForceUpdate( hScreenObj );

	return( 0 );
}

LONG	ScrnHostChat( HSCREENBTN hScreenBtn )
{
	return( 0 );
}

LONG	ScrnRemoteChat( HSCREENBTN hScreenBtn )
{
	return( 0 );
}

// update all the color buttons
void	ScrnColorButtonUpdate( HSCREEN hScreen )
{
	int			nButton;
	int			nPlayer;
	int			nColor;
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hScreenBtn;
	BOOL		bFound;

#ifdef SCRN_DEBUG
	TRACE("ScrnColorButtonUpdate( HSCREEN hScreen )\n" );
#endif

	// for each color, see if a player owns it
	nColor = ARMY_GREEN; 
	for( nButton=GREEN_BUTTON; nButton<=GRAY_BUTTON; ++nButton )
	{
		bFound     = FALSE;
		nPlayer    = 0;
		hScreenObj = hScreen->pScreenObjs[ nButton ];
		hScreenBtn = hScreenObj->hScreenBtns[0];
		while( !bFound && (nPlayer<=ARMY_PLAYER_4) )
		{
			if ( (gpComm->m_PlayerId[nPlayer] != 0) && (gpComm->m_PlayerId[nPlayer]  != 0xffffffff)  )
			{
				if ( (PlayerColor( (ARMY_TYPE)nPlayer ) == nColor) && (nPlayer!=ARMY_PLAYER) )
				{
#ifdef SCRN_DEBUG
	TRACE("ScrnColorButtonUpdate( Player %d: color %d ) BUTTON_NULL\n", nPlayer, nColor );
#endif

					// SBtnSetState( hScreenBtn, BUTTON_DISABLED );
					SBtnSetState( hScreenBtn, BUTTON_NULL );
					bFound = TRUE;
				}
				else
				if ( (PlayerColor( (ARMY_TYPE)nPlayer ) == nColor) && (nPlayer==ARMY_PLAYER) )
				{
					if ( SBtnGetState( hScreenBtn ) != BUTTON_CLICKED )
					{
#ifdef SCRN_DEBUG
	TRACE("ScrnColorButtonUpdate( Player %d: color %d ) BUTTON_CLICKED\n", nPlayer, nColor );
#endif

//						SBtnSetState( hScreenBtn, BUTTON_CLICKED );
//						hScreenBtn->bAttributes |= SBTN_CLICK_BYPASS;
					}
					bFound = TRUE;
				}
				else
					++nPlayer;
			}
			else
				++nPlayer;
		}

		// if not found, color is available
		if ( !bFound )
		{
#ifdef SCRN_DEBUG
	TRACE("ScrnColorButtonUpdate( unclaimed ) BUTTON_NULL\n", nPlayer, nColor );
#endif
			SBtnSetState( hScreenBtn, BUTTON_NULL );
		}

		hScreenBtn->bUpdate = TRUE;

		// try the next color
		++nColor;
	}
}

char*	SCRNledColors[LAST_COLOR_ARMY+1] =
{
	"green_selected.bmp",
	"tan_selected.bmp",
	"blue_selected.bmp",
	"grey_selected.bmp",
	"none_selected.bmp"
};

// update all the LEDs
void	ScrnLEDUpdate( HSCREEN hScreen )
{
	int	nLED;
	int	nPlayer;
	int	nColor;
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hScreenBtn;

	SetPath( SCREEN_PATH );
	nLED =PLAYER0_LED;
	for( nPlayer=ARMY_PLAYER; nPlayer<=ARMY_PLAYER_4; ++nPlayer )
	{
		hScreenObj = hScreen->pScreenObjs[ nLED ];
		hScreenBtn = hScreenObj->hScreenBtns[0];
		if ( (gpComm->m_PlayerId[nPlayer] != 0) && (gpComm->m_PlayerId[nPlayer]  != 0xffffffff) )
		{
			nColor = PlayerColor( (ARMY_TYPE)nPlayer );
			if ( nColor == ARMY_NO_COLOR )
				SBtnSetIcon( hScreenBtn, BUTTON_NULL, SCRNledColors[ LAST_COLOR_ARMY ] );
			else
				SBtnSetIcon( hScreenBtn, BUTTON_NULL, SCRNledColors[nColor] );
		}
		else
			SBtnSetIcon( hScreenBtn, BUTTON_NULL, SCRNledColors[ LAST_COLOR_ARMY ] );

		hScreenBtn->bUpdate = TRUE;

		// check the next LED
		++nLED;
	}
}

#define NAME_WIDTH 50

void CropPlayerName(char *pname, HSCREENOBJ hScreenObj)	{
	int	len = strlen(pname);
	int width = TextWidth(pname, hScreenObj->title.titleFontID);

	if ( width && hScreenObj->bkgArea.bkgBox.cx )	{
		while (len && (width > hScreenObj->bkgArea.bkgBox.cx) )	{
			len--;
			pname[len] = 0;
			width      = TextWidth(pname, hScreenObj->title.titleFontID);
		}
	}
#if 1
	else
	{
		TRACE( "CropPlayerName: width = %d   hScreenObj->bkgArea.bkgBox.cx = %d\n",
			width, hScreenObj->bkgArea.bkgBox.cx );
	}
#endif
}

//   Static GetLatencyColor

static SBTN_COLOR GetLatencyColor(DPID id) {
	SBTN_COLOR eColor;
	DWORD latency,now;
	LPFLOWQ flow;
	latency = AveLatencyID(id);
	eColor = SBTN_GREEN;
	if ( id == gpComm->m_DPId) return eColor;  // I'm OK 
	if (latency >  750 ) eColor = SBTN_YELLOW;
	if (latency >  1000 ) eColor = SBTN_DK_RED;
	if (latency >  1250 ) eColor = SBTN_RED;	
	flow = FindFlowQ(id) ;
	if (flow) {
		now = GetTickCount();
		if ((now - flow->timeReceived) > 1250 ) eColor = SBTN_LT_GREY;
	}
	if ( gpComm->m_ArmyReady[gpComm->GetIndexFromID(id)])  eColor = SBTN_LT_BLUE;
	return eColor;
}

void ScrnRedoPlayerNames ( ) {

if ( (GetFocus() != pMainFrame->GetHwnd()) )  return;
if ((ScrnGetState() != SCRN_MULTI_HOST_STATE) && (ScrnGetState() != SCRN_MULTI_REMOTE_STATE )) return;
if (SCRNfullScreen) ScrnPlayerNamesUpdate( SCRNfullScreen );
}


// update all the player names
void	ScrnPlayerNamesUpdate( HSCREEN hScreen )
{
	int			nObject;
	int			nPlayer;
	char*		pTitle;
	HSCREENOBJ	hScreenObj;
   	SBTN_COLOR	latencyColor;
	char		pPlayerName[SBTN_MAX_TEXT_LEN+1];

	nObject = PLAYER0_OBJECT;
	for( nPlayer=ARMY_PLAYER; nPlayer<=ARMY_PLAYER_4; ++nPlayer )
	{
		hScreenObj = hScreen->pScreenObjs[ nObject ];
		if ( hScreenObj )
		{
			if ( (gpComm->m_PlayerId[nPlayer] != 0) && (gpComm->m_PlayerId[nPlayer]  != 0xffffffff)  )
			{
				strncpy( pPlayerName,gpComm->m_PlayerName[nPlayer],SBTN_MAX_TEXT_LEN);
				CropPlayerName(pPlayerName, hScreenObj);
				latencyColor = GetLatencyColor(gpComm->m_PlayerId[nPlayer]);
				SObjSetTitleFGColor( hScreenObj, latencyColor );
				SObjSetTitle( hScreenObj, pPlayerName );
				hScreenObj->bUpdate = TRUE;
			}
			else
			{
				// if there's a title string clear it
				pTitle = SObjGetTitle( hScreenObj );
				if ( *pTitle )
				{
					*pTitle = '\0';
					hScreenObj->bUpdate = TRUE;
				}
			}
		}

		// check the next Object
		++nObject;
	}
}

// update the map choices
void	ScrnMapUpdateHost( HSCREEN hScreen )
{
	SOBJIMAGEDEF	mapImage;
	HSCREENOBJ		hScreenObject;
	HSCREENBTN		hScreenBtn;
	TCHAR			filename[DLG_MAX_FILENAME + 1];
	HANDLE			hFileCtl;
	WIN32_FIND_DATA	fileData;
	int				nIndex;
	int				nSlot;
	int				len;
	int				error;
	char*			pFileName;
	DWORD			bFileFound = FALSE;			// assume no files

	// clear the existing list
	ScrnReleaseRules( );

	// look to see which type of list to build
	filename[0] = '\0';
	strcat( filename, "*.RUL\0\0" );

	// look for the first file with this suffix
	SetPath( MAP_PATH );
	hFileCtl = FindFirstFile( filename, &fileData );
	if ( hFileCtl != INVALID_HANDLE_VALUE )
		bFileFound = TRUE;

	// store this first file into the list box and then look for
	// others
	while ( bFileFound && (SCRNruleIndex<SCRN_MAX_RULE_FILES) )
	{
		len = strlen( fileData.cFileName );
		if ( len-4 )
		{
			len -= 4;	// strip off .rul suffix
			pFileName = (char*)malloc( len+1 );
			if ( !pFileName )
				return;
			ZeroMemory( pFileName, len );
			strncpy( pFileName, fileData.cFileName, len );
			pFileName[ len ] = '\0';
			SCRNruleFiles[ SCRNruleIndex ] = pFileName;
			++SCRNruleIndex;
		}
		bFileFound = FindNextFile( hFileCtl, &fileData );
	}
	FindClose( hFileCtl );

	// now enumerate the data
	nIndex            = 0;
	// SCRNruleFileIndex = 0;	  // This is global already initialized
	bFileFound        = FALSE;
	hScreenObject     = hScreen->pScreenObjs[CAMPAIGN_LIST_OBJECT];
	while(  (nIndex<SCRNruleIndex) )
	{
			// see if we should select this map
			strcpy( filename, SCRNruleFiles[ nIndex ]);
			strcat( filename, ".RUL" );
			if ( strcmp( filename, gpGame->RuleName) == 0 )
			{
				bFileFound                  = TRUE;
				if (nIndex < SCRNruleFileIndex) SCRNruleFileIndex = nIndex;
				if (nIndex >= (SCRNruleFileIndex+hScreenObject->nNumberBtns)) SCRNruleFileIndex = nIndex;
				if (SCRNruleFileIndex > (SCRNruleIndex-hScreenObject->nNumberBtns)) SCRNruleFileIndex = (SCRNruleIndex-hScreenObject->nNumberBtns);
				break;
			}

		// update indecies
		++nIndex;
	}
	hScreenObject->bUpdate = TRUE;

	// now see if we need to re-highlight the currently selected map
	nSlot         = 0;
	nIndex        = SCRNruleFileIndex;
	bFileFound    = FALSE;
	while( (nSlot<hScreenObject->nNumberBtns) &&  (nIndex<SCRNruleIndex) )
	{
		hScreenBtn = hScreenObject->hScreenBtns[ nSlot ];
		if ( hScreenBtn )
		{
			SBtnSetText( hScreenBtn, SCRNruleFiles[ nIndex ] );

			// see if we should select this map
			strcpy( filename, SCRNruleFiles[ nIndex ]);
			strcat( filename, ".RUL" );
			if ( strcmp( filename, gpGame->RuleName) == 0 )
			{
				hScreenBtn->eScreenBtnState = BUTTON_CLICKED;
				hScreenBtn->bAttributes    |= SBTN_CLICK_BYPASS;
				bFileFound                  = TRUE;
			}
			else
			{
				hScreenBtn->eScreenBtnState = BUTTON_NULL;
				hScreenBtn->bAttributes    &= ~SBTN_CLICK_BYPASS;
			}
			hScreenBtn->bUpdate = TRUE;
		}

		// update indecies
		++nIndex;
		++nSlot;
	}
	if ( !bFileFound )
	{
		// choose the first file in the list as a default
		hScreenBtn                  = hScreenObject->hScreenBtns[ 0 ];
		hScreenBtn->eScreenBtnState = BUTTON_CLICKED;
	}

	// signify that we now a valid game selected
	gpComm->m_ArmyGotMap[ ARMY_PLAYER ] = TRUE;

	// get the map image information
	error = ScrnVerifyMap( &mapImage );
//	if ( error )
//		ScrnReportMapError( image_error );

	// get the stratmap object and change its BKG reference
	hScreenObject = hScreen->pScreenObjs[START_MAP_OBJECT];
	SObjSetBkgImage( hScreenObject, &mapImage );
	hScreenObject->bUpdate = TRUE;

	// now update the rules
	if ( error == MAP_OK )
		ScrnUpdateRules(FALSE);
}

void BadMap(int error, const char *mapName)	{
	char *str;
	char tempbuffer[128];
	char err_str[64];

	// send message to host
	SendMapMsg( error , DPID_ALLPLAYERS);

	//append the proper color header
//	tempbuffer[0]=PlayerColor(ARMY_PLAYER) + 1;
//	tempbuffer[0]=SBtnPlayerColor( PlayerColor(ARMY_PLAYER) );
	tempbuffer[0]=gpComm->GetArmyIndex(ARMY_PLAYER)+1;

	// now insert the players Name
	strcpy(tempbuffer+1, gpComm->m_PlayerName[ARMY_PLAYER]);
	strcat(tempbuffer+1, ": ");

	// send chat message
	// TBD: get string from usa.h
	switch (error)	{
		case MAP_BAD_CHECKSUM:
			str = "Remote Map %s is Damaged";
			break;
		case MAP_BAD_RULECHECKSUM:
			str = "Remote Map %s has Damaged Script Files";
			break;
		case MAP_NO_MAP:
			str = "Remote Map %s is Missing";
			break;
	}
	sprintf(err_str, str, mapName);

	strcat(tempbuffer+1, err_str);

	// pass the string to proper update mechanism
	ScrnReceiveChatMessage(tempbuffer);

	// finally, send the chat message out to all
	// the other players
	SendChatMessage( tempbuffer );	// broadcast to all players

	// TBD: rules checksum error
}

void GoodMap(const char *mapName)	{
	// send message to host
	SendMapMsg( MAP_OK , DPID_ALLPLAYERS);

	// TBD: rules checksum error
}

// update the map image
int	ScrnMapUpdateRemote( HSCREEN hScreen )
{
	SOBJIMAGEDEF	mapImage;
	HSCREENOBJ		hScreenObject;
	int				error;

	// get the map image information
	if ( !gpComm->m_HostID) return (MAP_OK); // haven't heard from host yet
	ScrnUpdateRules(FALSE);
	error = ScrnVerifyMap( &mapImage );
	if (error != MAP_OK) ScrnReportMapError(error);
#if 0
	TRACE( "ScrnMapUpdateRemote(): ScrnVerifyMap( %d )\n", error );
#endif

	// get the stratmap object and change its BKG reference
	hScreenObject = hScreen->pScreenObjs[START_MAP_OBJECT];
	SObjSetBkgImage( hScreenObject, &mapImage );
	hScreenObject->bUpdate = TRUE;

	hScreenObject = hScreen->pScreenObjs[ RULES_OBJECT ];
	hScreenObject->bUpdate = TRUE;

#if 0
	hScreenObject = hScreen->pScreenObjs[ RULES_OBJECT ];
	hScreenObject->bUpdate = TRUE;
#endif

	// now update the rules
	if ( error == MAP_OK )
		ScrnUpdateRules(FALSE);

	return( error );
}

// update the map image
int	ScrnVerifyMap( SOBJIMAGEDEF* pMapImage )
{
	int				len;
	char			buffer[128];
	unsigned long	sum   = 0;
	int				error = MAP_OK;
	static char		bad_map[] = "default_mp.bmp";

	ZeroMemory( pMapImage, sizeof( SOBJIMAGEDEF ) );

	SetPath( MAP_PATH );
	if ( *(gpGame->MapName) ) {
		if (FileExist(gpGame->MapName))	{
			sum = MapLoadSum(gpGame->MapName);
			if (sum != gpGame->MapSum)
				error = MAP_BAD_CHECKSUM;
		}
		else
			error = MAP_NO_MAP;
	}
	else
		error = MAP_NULL;
	if (error == MAP_OK) {
		if(!gpComm->m_bHost) 
			if(gpGame->HostRuleSum != gpGame->RuleSum) error = MAP_BAD_RULECHECKSUM;
	}


	switch (error)	{
		case MAP_OK:
			strcpy( buffer, gpGame->MapName );
			if ( *buffer == '\0' )
				return( error );
			len = strlen( buffer );
			len -= 4;		// strip off suffix and '.'
			buffer[len] = '\0';
			strcpy( pMapImage->bkgRef, buffer );
			strcat( pMapImage->bkgRef, "_mp.BMP" );
			GoodMap((LPCTSTR) gpGame->MapName);
//			SCRNmultiStartOK = TRUE;
			break;
		case MAP_BAD_CHECKSUM:
			strcpy( pMapImage->bkgRef, bad_map );
			break;
		case MAP_BAD_RULECHECKSUM:
			break;
		case MAP_NO_MAP:
			strcpy( pMapImage->bkgRef, bad_map );
			break;
		case MAP_NULL:
			strcpy( pMapImage->bkgRef, bad_map );
			break;
	}
	return( error );
}

// update the map image
int	ScrnReportMapError( int error )
{
	switch (error)	{
		case MAP_BAD_CHECKSUM:
			TRACE("Bad checksum in Remote Map (%s)\n", gpGame->MapName);
			BadMap(error, (LPCTSTR) gpGame->RuleName);
			break;
		case MAP_BAD_RULECHECKSUM:
			TRACE("Bad checksum in Scripts for Remote Map (%s)\n", gpGame->MapName);
			BadMap(error, (LPCTSTR) gpGame->RuleName);
			break;
		case MAP_NO_MAP:
			TRACE("ERROR:Remote Map not found (%s)\n", gpGame->MapName);
			BadMap(error, (LPCTSTR) gpGame->RuleName);
			break;
	}
	return( error );
}

void	ScrnDisplayChatReceive( HSCREEN hScreen )
{
	CHAT_STRUCT_RECEIVE *pChatObject;
	HSCREENOBJ			hScreenObj;
	HSCREENBTN			hScreenBtn;
	SBOX*				pObjectBox;
	SBOX				boxText;
	COLORREF			rgbTextColor;
	RECT				Rect;
	char*				pString;
	char				buffer[CHAT_MAX_WITH_NAME+1];
	int					i;
	int					nNumLines = 0;

	// get the chat button
	hScreenBtn = SBtnGetCurrentClicked();

	// setup the chat data
	pChatObject = &(SCRNchat.chatReceive);
//	for (i=0;i<pChatObject->nCurrentTopString;i++)
//		pChatObject->pStrings[i]=&(pChatObject->strings[i*(CHAT_MAX_WITH_NAME+1)]);

	// get the screen text box for chat receive
	hScreenObj = hScreen->pScreenObjs[CHAT_RECEIVE_OBJECT];
	if ( !hScreenObj )
		return;

	// now write out the string into the chat receive area
	pObjectBox = SObjGetBkgArea( hScreenObj );
	if ( !pObjectBox )
		return;

	// convert the area to a rect and erase the chat screen
	Rect.left   = hScreenObj->ParentBox.x + hScreenObj->position.x + pObjectBox->x;
	Rect.top    = hScreenObj->ParentBox.y + hScreenObj->position.y + pObjectBox->y;
	Rect.right  = Rect.left + pObjectBox->cx;
	Rect.bottom = Rect.top + pObjectBox->cy;

	CursorOff(&Rect);

	// draw the rectangle
	FillRectFront( &Rect, RGB_BLACK );	// filled rectangle

	// now figure out the text offsets
	buffer[0] = 'M';
	buffer[1] = '\0';
	if ( TextBox( buffer, &boxText, FONT_TIMES_14 ) )
	{
		boxText.cx = 10;
		boxText.cy = 14;
	}

	// now display the lines of text
	for (i=0;i<pChatObject->nCurrentTopString;i++)
	{
		pString = pChatObject->pStrings[i];
		if ( *pString )
		{
			// check to see if there is a color designator
			if ((*pString>0) && (*pString<32))
			{
				rgbTextColor = PlayerColorTable[(*pString-1)];
				++pString;
			}

			// copy the message into a buffer
			memcpy( buffer, pString, CHAT_MAX_WITH_NAME );
			buffer[ CHAT_MAX_WITH_NAME ] = 0;
			nNumLines = MessageFormat( &Rect, pString, CHAT_MAX_WITH_NAME, rgbTextColor, FONT_TIMES_14 );

			// adjust the rectangle for the new text
			Rect.top += (nNumLines * boxText.cy);
		}
	}
}

void	ScrnUpdateRules( BOOL ForceReadRules )
{
	int		len;
	int		nNumLines = 0;

	// get to the data directory and open the data file
	SetPath( MAP_PATH );
	len = strlen( gpGame->RuleName );
	len -= 4;			// strip off the .RUL
	if ( len > 0 )
	{
		// check to see if the rules file name has changed
		if ( ForceReadRules || strncmp( SCRNrulesTitle, gpGame->RuleName, len ) != 0 )
		{
			strncpy( SCRNrulesTitle, gpGame->RuleName, len );
			SCRNrulesTitle[ len ] = 0;

			if (ReadRules(gpGame->RuleName) != RULE_FILE_OK)	{
				// bad rules
				SCRNrules[0] = '\0';
			}
		}
	}
}

void	ScrnDisplayRules( HSCREEN hScreen )
{
	HSCREENOBJ			hScreenObj;
	SBOX*				pObjectBox;
	RECT				Rect;
	char				buffer[SCRN_MAX_RULES_LENGTH+1];
	int					len;
	int					nNumLines = 0;

	// get to the data directory and open the data file
	SetPath( MAP_PATH );
	len = strlen( SCRNrulesTitle );
	if ( len  )
	{
		// first output the rules title
		hScreenObj = hScreen->pScreenObjs[ RULESTITLE_OBJECT ];

		// write out the string into the rules title area
		pObjectBox = SObjGetBkgArea( hScreenObj );
		if ( !pObjectBox )
			return;

		// convert the area to a rect and erase the rules screen
		Rect.left   = hScreenObj->ParentBox.x + hScreenObj->position.x + pObjectBox->x + 4;
		Rect.top    = hScreenObj->ParentBox.y + hScreenObj->position.y + pObjectBox->y;
		Rect.right  = Rect.left + pObjectBox->cx - 4;
		Rect.bottom = Rect.top + pObjectBox->cy;

		CursorOff(&Rect);

		// draw the rectangle
		FillRectFront( &Rect, RGB_BLACK );	// filled rectangle

		// build the rules title
		memcpy( buffer, SCRNrulesTitle, len );
		buffer[ len ] = 0;
		nNumLines = MessageFormat( &Rect, buffer, len, RGB_WHITE, FONT_TIMES_14 );
	}

	// now output the actual rules
	hScreenObj = hScreen->pScreenObjs[ RULES_OBJECT ];

	// write out the string into the rules area
	pObjectBox = SObjGetBkgArea( hScreenObj );
	if ( !pObjectBox )
		return;

	// convert the area to a rect and erase the rules screen
	Rect.left   = hScreenObj->ParentBox.x + hScreenObj->position.x + pObjectBox->x + 4;
	Rect.top    = hScreenObj->ParentBox.y + hScreenObj->position.y + pObjectBox->y;
	Rect.right  = Rect.left + pObjectBox->cx - 4;
	Rect.bottom = Rect.top + pObjectBox->cy;

	CursorOff(&Rect);

	// draw the rectangle
	FillRectFront( &Rect, RGB_BLACK );	// filled rectangle

	// read in the rules data
	len = strlen( SCRNrules );
	if ( len > 0 )
	{
		if ( len > (SCRN_MAX_RULES_LENGTH - 1) )
			len = (SCRN_MAX_RULES_LENGTH - 1);

		// copy the message into a buffer
		memcpy( buffer, SCRNrules, len );
		buffer[ len ] = 0;
		nNumLines = MessageFormat( &Rect, buffer, len, RGB_WHITE, FONT_TIMES_14 );
	}
}

BOOL	ScrnMultiPlayerSpclUpdate( HSCREEN hScreen )
{
	HSCREENOBJ	hScreenObj;
	BOOL		bUpdate		= FALSE;

	// take care of the special objects in this
	// screen: chat and rules

	hScreenObj = hScreen->pScreenObjs[ RULES_OBJECT ];
	if ( hScreenObj->bUpdate )
		bUpdate = TRUE;
	hScreenObj->bUpdate = FALSE;

	hScreenObj = hScreen->pScreenObjs[ CHAT_RECEIVE_OBJECT ];
	if ( hScreenObj->bUpdate )
		bUpdate = TRUE;
	hScreenObj->bUpdate = FALSE;
	
	return( bUpdate );
}

void	ScrnMultiPlayerDisplay( HSCREEN hScreen )
{
	ScrnDisplayChatReceive( hScreen );
	ScrnDisplayRules( hScreen );
}

void	ScrnReleaseRules( void )
{
	int	nIndex;

	for( nIndex=0; nIndex<SCRNruleIndex; ++nIndex )
	{
		if ( SCRNruleFiles[ nIndex ] )
		{
			free( SCRNruleFiles[ nIndex ] );
			SCRNruleFiles[ nIndex ] = NULL;
		}
	}
	SCRNruleIndex = 0;
}


void ScrnReceiveChatMessage(char *message)
{
	HSCREENOBJ				hScreenObj;
	CHAT_STRUCT_RECEIVE*	chat_receive;
	char*					targetstring;
	char*					tptr;
	char*					mptr;
	int						i,len;

	if (!SCRNfullScreen)
		return;

	len = strlen(message+1);
	if (len>CHAT_MAX_WITH_NAME-1)
	{
//		TRACE("WARNING: SCREEN chat message received that was just too damn long, truncating\n");
		len = CHAT_MAX_WITH_NAME-1;
	}

	chat_receive = &(SCRNchat.chatReceive);
	if ( chat_receive->nCurrentTopString >= CHAT_MAX_MESSAGES )
	{
		// scroll the messages up
		for (i=0;i<CHAT_MAX_MESSAGES-1;i++)
			strcpy( chat_receive->pStrings[i], chat_receive->pStrings[i+1] );
	}
	else
		++(chat_receive->nCurrentTopString);

	targetstring  = chat_receive->pStrings[chat_receive->nCurrentTopString-1];
	if ( targetstring )
	{
		ZeroMemory(targetstring, (CHAT_MAX_WITH_NAME+1)*sizeof(char));
		mptr = message;
		tptr = targetstring;
		if ((message[0]>0) && (message[0]<32))
		{
			targetstring[0] = message[0];
			++tptr;
			++mptr;

			// now insert the message
			strncpy(tptr, mptr, len);
			*(targetstring+len+1) = '\0';
		}
		else
		{
			++len;

			// now insert the message
			strncpy(tptr, mptr, len);
			*(targetstring+len) = '\0';
		}

//		chat_receive->nCurrentTopString=(chat_receive->nCurrentTopString+1)%CHAT_MAX_MESSAGES;

//		for (i=0;i<CHAT_MAX_MESSAGES;i++)
//			chat_receive->pStrings[i]=&chat_receive->strings[(CHAT_MAX_WITH_NAME+1)*((i+chat_receive->nCurrentTopString)%CHAT_MAX_MESSAGES)];

		chat_receive->bUpdate = TRUE;

		hScreenObj          = SCRNfullScreen->pScreenObjs[ CHAT_RECEIVE_OBJECT ];
		hScreenObj->bUpdate = TRUE;
	}
}

int MessageFormat(RECT* pRect, char *message, int nMaxLength, COLORREF nColor, int nFontID )
{
	char*	messageBuffer;
	char*	pNextChar;
	char	nEndOfWord;
	SBOX	textBox;
	SPOINT	screenPos;
	BOOL	bEndOfLine;
	BOOL	bDone;
	int		nNextChar;
	LONG	xMaxLen;
	int		nNumLines = 0;

	if (!pRect || !message)
		return(nNumLines);

	// malloc up a message buffer
	messageBuffer = (char*)malloc( nMaxLength+16 );		// buffer space for formatting
	if ( !messageBuffer )
	{
		TRACE( "ERROR: failed to malloc message buffer of size %d [%s:%d]\n",
			nMaxLength+1, __FILE__, __LINE__ );
		return(nNumLines);
	}

	// initialize the screen position of the text
	screenPos.x = (short)pRect->left;
	screenPos.y = (short)pRect->top;
	xMaxLen     = pRect->right - pRect->left;

	TextSetColors( nColor, RGB_TRANSPARENT );

	// now start outputing the message
	bDone     = FALSE;
	pNextChar = message;
	while ( !bDone )
	{
		nEndOfWord = -1;
		nNextChar  = 0;
		bEndOfLine = FALSE;
		// copy text into the buffer until you get a word break or EOL
		while ( !bEndOfLine )
		{
			messageBuffer[ nNextChar ]   = *pNextChar;
			messageBuffer[ nNextChar+1 ] = '\0';
#ifdef SCREEN_DEBUG
TRACE( "messageBuffer (%s)\n", messageBuffer );
#endif
			switch( *pNextChar )
			{
			case ' ':	// remember this End Of Word location
			case '\n':	// remember this End Of Word location
				// check to see if the current line will still fit
				// into the display window
				textBox.x  = 0;
				textBox.y  = 0;
				if ( TextBox( messageBuffer, &textBox, nFontID ) )
				{
					// error: failed to acquire text box size
					TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
							__FILE__, __LINE__ );
					return(0);
				}
				if ( textBox.cx > xMaxLen )
				{
					// back up to the last whole word
					if ( nEndOfWord < 0 )
						ASSERT(0);
					else
					{
						pNextChar -= (nNextChar-nEndOfWord);
						nNextChar  = nEndOfWord+1;
						messageBuffer[ nEndOfWord ] = '\0';
					}

					// now output this string to the window
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								messageBuffer, nFontID, NULL );
//					TRACE("%s\n", messageBuffer);

					// advance the position
//					screenPos.y += textBox.cy + 8;
					screenPos.y += textBox.cy + 2;
					bEndOfLine = TRUE;
					++nNumLines;
				}
				else
				{
					messageBuffer[ nNextChar ] = ' ';
					nEndOfWord                 = nNextChar;
					++nNextChar;
					++pNextChar;
					messageBuffer[ nNextChar ] = '\0';
				}
				break;
			case '\0':	// remember this End Of Word location
				// check to see if the current line will still fit
				// into the display window
				messageBuffer[ nNextChar ] = '\0';
				textBox.x  = 0;
				textBox.y  = 0;
				if ( TextBox( messageBuffer, &textBox, nFontID ) )
				{
					// error: failed to acquire text box size
					TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
							__FILE__, __LINE__ );
					return(0);
				}
				if ( textBox.cx > xMaxLen )
				{
					// back up to the last whole word
					messageBuffer[ nEndOfWord ] = '\0';

					pNextChar -= (nNextChar-nEndOfWord);
					nNextChar  = nEndOfWord+1;
					messageBuffer[ nEndOfWord ] = '\0';

					// now output this string to the window
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								messageBuffer, nFontID, NULL );
//					TRACE("%s\n", messageBuffer);
					++nNumLines;

					// advance the position
					screenPos.y += textBox.cy + 2;

					// now output this remainder of the string
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								&(messageBuffer[nNextChar]), nFontID, NULL );
//					TRACE("%s\n", &(messageBuffer[nNextChar]));
					// advance the position
					screenPos.y += textBox.cy + 2;
					++nNumLines;
				}
				else
				{
//					nEndOfWord = nNextChar;
					nEndOfWord = 0;
					++nNextChar;
					++pNextChar;
					messageBuffer[ nNextChar ] = '\0';

					// now output this string to the window
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								messageBuffer, nFontID, NULL );
//					TRACE("%s\n", messageBuffer);
					// advance the position
					screenPos.y += textBox.cy + 2;
					++nNumLines;
				}
				bEndOfLine = TRUE;
				bDone      = TRUE;
				break;
			default:
				if ( nNextChar >= nMaxLength )
				{
					// back up to the last whole word
					if ( nEndOfWord != -1 )
					{
						messageBuffer[ nEndOfWord ] = '\0';

						// back up the source pointer
						pNextChar -= (nNextChar-nEndOfWord);
						nNextChar  = nEndOfWord+1;
						messageBuffer[ nNextChar ] = *pNextChar;
						++nNextChar;
						messageBuffer[ nNextChar ] = '\0';
					}
					else
					{
						// back up until the string fits
						nEndOfWord = 0;
						while ( nNextChar && !nEndOfWord )
						{
							--nNextChar;
							if ( nNextChar )
							{
								--pNextChar;
								messageBuffer[ nNextChar ] = '\0';
								if ( TextBox( messageBuffer, &textBox, nFontID ) )
								{
									// error: failed to acquire text box size
									TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
											__FILE__, __LINE__ );
									return(0);
								}
								if ( textBox.cx < xMaxLen )
								{
									// good enough
									nEndOfWord = nNextChar;
								}
							}
						}
					}

					if ( TextBox( messageBuffer, &textBox, FONT_CARGO_20 ) )
					{
						// error: failed to acquire text box size
						TRACE( "ERROR: failed to acquire text box size [%s : %d]\n",
								__FILE__, __LINE__ );
						return(0);
					}

					// now output this string to the window
					TextWrite(	pFrontBuffer,
								screenPos.x + rcWindowScreen.left,
								screenPos.y + rcWindowScreen.top,
								messageBuffer, nFontID, NULL );
//					TRACE("%s\n", messageBuffer);

					// advance the position
					screenPos.y += textBox.cy + 2;
					bEndOfLine   = TRUE;
					++nNumLines;
				}
				else
				{
					// go on to the next character
					++nNextChar;
					++pNextChar;
					messageBuffer[ nNextChar ] = '\0';
				}
				break;
			}
		}
	}

	// free the message buffer
	if ( messageBuffer )
		free(messageBuffer);

	return( nNumLines );
}

void	ScrnClearFocus( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;
	int			nIndex;
	int			nMaxBtns;

	// set other buttons in this object to NULL state
	hScreenObj = SCRNfullScreen->pScreenObjs[0];
	nMaxBtns   = hScreenObj->nNumberBtns;
	for( nIndex=0; nIndex<nMaxBtns; ++nIndex )
	{
		hBtn = hScreenObj->hScreenBtns[ nIndex ];
		if ( hBtn )
		{
			if ( hBtn != hScreenBtn )
				SBtnSetState( hBtn, BUTTON_NULL );
		}
	}
}

void	ScrnClearClicked( HSCREENBTN hScreenBtn )
{
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hBtn;
	int			nIndex;
	int			nMaxBtns;

	// set other buttons in this object to NULL state
	hScreenObj = SCRNfullScreen->pScreenObjs[0];
	nMaxBtns   = hScreenObj->nNumberBtns;
	for( nIndex=0; nIndex<nMaxBtns; ++nIndex )
	{
		hBtn = hScreenObj->hScreenBtns[ nIndex ];
		if ( hBtn )
		{
			if ( hBtn != hScreenBtn )
				SBtnSetState( hBtn, BUTTON_NULL );
		}
	}
}

void CALLBACK	ScrnTick( void )
{
	if ( SCRNtimerStart && ((gpGame->dwSysTime - SCRNtimerStart) > FIVE_SECONDS) )
	{
		SCRNtimerStart = 0;
		SCRNtimerTrigger = TRUE;
	}
}

HSCREENBTN	ScrnGetChatBtn( void )
{
	HSCREENOBJ	hScreenObj;

	hScreenObj = SCRNfullScreen->pScreenObjs[CHAT_SEND_OBJECT];
	return( hScreenObj->hScreenBtns[0] );
}

void	ScrnInitChat( UINT key )
{
	HSCREENBTN	hScreenBtn;

	hScreenBtn = ScrnGetChatBtn();
	memset(hScreenBtn->pText, '\0', SBTN_MAX_TEXT_LEN);
	SBtnChatTurnOnKeys( hScreenBtn );
	hScreenBtn->eScreenBtnState = BUTTON_EDIT;
	hScreenBtn->bUpdate         = TRUE;
	SBTNcurrentClicked          = hScreenBtn;
	if ( SBTNcurrentFocus )
	{
		if ( SBTNcurrentFocus != hScreenBtn )
			SBtnSetState( SBTNcurrentFocus, BUTTON_NULL );
		SBTNcurrentFocus = NULL;
	}

	audioPlay( BUTTONSPRINGIN, SND_SFX_FLAG | SND_DELETE_FLAG );
	SBtnExecuteCallback( hScreenBtn, BUTTON_EDIT );
}

void	ScrnDisplayLoading( void )
{
	char*			pBkgImage;
	CAMPAIGNREF*	pCampaign;

	// clear the surfaces and go to the screens directory
	EraseSurfaces();
  	SetPath( SCREEN_PATH );

	// no acquire the loading BMP from the CAMPAIGN table
	if ( gpGame->GameType == GAMETYPE_ONEPLAYER )
	{
		pCampaign = g_Campaigns[ g_CampaignIndex ];
		if ( !pCampaign )
			pBkgImage = "Title_legal.bmp";
		else
			pBkgImage = pCampaign->pLoadBkg;
		if ( !pBkgImage )
			pBkgImage = "Title_legal.bmp";
	}
	else
	{
		pBkgImage = SCRNloadMap;
		if ( *pBkgImage == '\0' )
			pBkgImage = "Title_legal.bmp";
	}

	LoadBackground( pBkgImage, TRUE );
}

BOOL	ScrnOptionsVisible( void )
{
	ULONG	nGameState;
	BOOL	bAnswer = FALSE;

	// get the current screen state and see if it is
	// one that should be active during game play
	nGameState = ScrnGetState();

	switch( nGameState )
	{
	case SCRN_OPTIONS_STATE:			// Armymen options selection
	case SCRN_CONTROLS_STATE:			// User control configuration
	case SCRN_AUDIO_STATE:				// audio configuration
	case SCRN_PLAY_OPTIONS_STATE:		// Armymen options selection during game play
	case SCRN_PLAY_CONTROLS_STATE:		// User control configuration
	case SCRN_PLAY_AUDIO_STATE:			// audio configuration
	case SCRN_STATS_STATE:				// Army statistics
	case SCRN_KEYPAD_STATE:				// User Keypad configuration
	case SCRN_KEYBOARD_STATE:			// User KeyBoard configuration
	case SCRN_CUSTOM_STATE:				// User Custom configuration
	case SCRN_JOYSTICK_STATE:			// User Joystick configuration
		bAnswer = TRUE;
		break;
	default:
		break;
	}
	return( bAnswer );
}


BOOL ReadRules(const char *FileName)
{
	FILE*	pFilePtr;
	BOOL	rulesErr = RULE_FILE_BAD;
	char	script[SCRN_MAX_NAME_LEN+1];
	char	name[SCRN_MAX_NAME_LEN+1];
	char	terrainname[SCRN_MAX_NAME_LEN+1];
	gpGame->RuleSum = 0;
	SCRNrules[0] = '\0';
   
	SetPath( MAP_PATH );

	if (FileName[0] == '\0')
		return RULE_FILE_NOEXIST;

	// read in the rules data
	if ( (pFilePtr = (FILE*)fopen( FileName, "r" )) == NULL )
	{
		rulesErr = RULE_FILE_NOEXIST;
	}
	else
	{
		// read in a line of data from the file
		if ( fgets( SCRNrules, SCRN_MAX_RULES_LENGTH, pFilePtr ) != NULL )
		{
			RemoveLF(SCRNrules);
			if ( fgets( name, SCRN_MAX_NAME_LEN, pFilePtr ) != NULL )
			{
			RemoveLF(name);
			if (gpGame->GameType == GAMETYPE_HOST_MULTIPLAYER)
				gpGame->MapName = name;

 				if ( fgets( terrainname, SCRIPT_NAME_SIZE, pFilePtr ) != NULL )
				{
					RemoveLF(terrainname);
					rulesErr = RULE_FILE_OK;
					SetPath(NULL);
 					gpGame->RuleSum ^= FileXSum(AIfileName);
					SetPath(terrainname);
 					gpGame->RuleSum ^= FileXSum(AIfileName);
   					SetPath( MAP_PATH );
					if ( fgets( SCRNloadMap, SCRN_MAX_NAME_LEN, pFilePtr ) != NULL )
					{
						RemoveLF(SCRNloadMap);

						if ( fgets( brieffilename, SCRIPT_NAME_SIZE, pFilePtr ) != NULL )
						{
							RemoveLF(brieffilename);

							script[0]    = '\0';
							int i = 0;
							while ( fgets( script, SCRN_MAX_NAME_LEN, pFilePtr ) != NULL )
							{
								RemoveLF(script);
								SetScriptName(script, i);
								gpGame->RuleSum ^= ScriptFileXSum(script);
								i++;
								script[0]    = '\0';
							}
						}
					}
				}
			}
		}
		if (gpComm->m_bHost) gpGame->HostRuleSum = gpGame->RuleSum;
		fclose( pFilePtr );
	}


#if 0
TRACE("Rules  = %s\n", SCRNrules );
TRACE("Map    = %s\n", gpGame->MapName );
TRACE("Load   = %s\n", SCRNloadMap );
TRACE("Brief  = %s\n", brieffilename );
#endif

	return rulesErr;
}

SCREENDEF*	ScrnBuildKeysDef( CONFIG nScreenType )
{
	return(NULL);
}

void	ScrnLoadSargeKeys( HSCREEN hScreen, int nObjectIndex )
{
}

void	ScrnLoadGameKeys( HSCREEN hScreen, int nObjectIndex )
{
}

void	CopyBaseFileName( char *dest, const char *src)	{
	char *dot;

	strcpy(dest, src);
	dot = strchr(dest, '.');
	*dot = '\0';
}

void	RemoveLF(char *str)	{
	int len = strlen(str) - 1;
	if (str[len] == 0xA)
		str[len] = '\0';
}


void	ScrnDump( void )
{
	HSCREEN		hScreen;
	HSCREENOBJ	hScreenObj;
	int			nIndex;
	int			nMaxObjs;

	// Dump Screen Info
	hScreen = SCRNfullScreen;
	if ( hScreen )
	{
		// dump the attributes
		TRACE( "    Attributes:            " );
		if ( hScreen->bAttributes                       == SCRN_CLEAR )
			TRACE( "SCRN_CLEAR " );
		if ( (hScreen->bAttributes & SCRN_BKG_TYPE)     == SCRN_BKG_TYPE )
			TRACE( "SCRN_BKG_TYPE " );
		if ( (hScreen->bAttributes & SCRN_AREA_TYPE)    == SCRN_AREA_TYPE )
			TRACE( "SCRN_AREA_TYPE " );
		if ( (hScreen->bAttributes & SCRN_TRANSPARENT)  == SCRN_TRANSPARENT )
			TRACE( "SCRN_TRANSPARENT " );
		if ( (hScreen->bAttributes & SCRN_ISYESNO)      == SCRN_ISYESNO )
			TRACE( "SCRN_ISYESNO " );
		TRACE( "\n" );

		// display the screen current state
#if 0
		TRACE( "    Screen Current State:  %d\n", hScreen->eState );
#else
		TRACE( "    Screen Current State:  " );
		if ( hScreen->eState == BUTTON_NULL )
			TRACE( "BUTTON_NULL " );
		if ( hScreen->eState == BUTTON_FOCUSED )
			TRACE( "BUTTON_FOCUSED " );
		if ( hScreen->eState == BUTTON_CLICKED )
			TRACE( "BUTTON_CLICKED " );
		if ( hScreen->eState == BUTTON_EDIT )
			TRACE( "BUTTON_EDIT " );
		if ( hScreen->eState == BUTTON_DISABLED )
			TRACE( "BUTTON_DISABLED " );
		TRACE( "\n" );
#endif

		// display the screen previous state
#if 0
		TRACE( "    Screen Previous State:  %d\n", hScreen->ePrevState );
#else
		TRACE( "    Screen Previous State: " );
		if ( hScreen->ePrevState == BUTTON_NULL )
			TRACE( "BUTTON_NULL " );
		if ( hScreen->ePrevState == BUTTON_FOCUSED )
			TRACE( "BUTTON_FOCUSED " );
		if ( hScreen->ePrevState == BUTTON_CLICKED )
			TRACE( "BUTTON_CLICKED " );
		if ( hScreen->ePrevState == BUTTON_EDIT )
			TRACE( "BUTTON_EDIT " );
		if ( hScreen->ePrevState == BUTTON_DISABLED )
			TRACE( "BUTTON_DISABLED " );
		TRACE( "\n" );
#endif

		// BG color
		TRACE( "    BG Color:              %s\n", SBtnColorName( hScreen->eBGColor ) );

		// does it need an update
		TRACE( "    Screen Update:         %s\n", ((hScreen->bUpdate) ? "TRUE" : "FALSE") );

		// display the position, text, references, and Resource IDs
		TRACE( "    Screen Position:       (%d,%d)\n", hScreen->position.x, hScreen->position.y );
		TRACE( "    Screen Image Ref:      [%s]\n", hScreen->BkgRef );
		TRACE( "    Bkg Box:               (x:%d,y:%d,w:%d,h:%d)\n",
				hScreen->BkgBox.x,  hScreen->BkgBox.y,
				hScreen->BkgBox.cx, hScreen->BkgBox.cy );

		// Dump the Object info
		TRACE( "    # Objects:             %d\n", hScreen->nNumberObjs );
		nMaxObjs = hScreen->nNumberObjs;
		for( nIndex=0; nIndex<nMaxObjs; ++nIndex )
		{
			TRACE( "                   Object #%d\n", nIndex );
			hScreenObj = SCRNfullScreen->pScreenObjs[nIndex];
			if ( hScreenObj )
				SObjDump( hScreenObj );
		}
	}

}

void	ScrnVerifyUpdate( void )
{
	HSCREEN		hScreen;
	HSCREENOBJ	hScreenObj;
	HSCREENBTN	hScreenBtn;
	int			nObjIndex;
	int			nBtnIndex;
	int			nMaxBtns;
	int			nMaxObjs;
	BOOL		bUpdate;

	hScreen = SCRNfullScreen;
	if ( hScreen )
	{
		nObjIndex = 0;
		nMaxObjs  = hScreen->nNumberObjs;
		bUpdate   = hScreen->bUpdate;
		while ( !bUpdate && (nObjIndex<nMaxObjs) )
		{
			hScreenObj = SCRNfullScreen->pScreenObjs[nObjIndex];
		    nBtnIndex  = 0;
			bUpdate    = hScreenObj->bUpdate;
			nMaxBtns   = hScreenObj->nNumberBtns;
			while( !bUpdate && (nBtnIndex<nMaxBtns) )
			{
				hScreenBtn = hScreenObj->hScreenBtns[ nBtnIndex ];
				bUpdate    = hScreenBtn->bUpdate;
				++nBtnIndex;
			}
			++nObjIndex;
		}

		hScreen->bUpdate = bUpdate;
	}
}

void ScrnSetMusic( SCRN_STATE eScrnState )
{
	switch( eScrnState )
	{
	case SCRN_NULL_STATE:
	case SCRN_TITLE_STATE:				// Title Screen state
	case SCRN_GAME_START_STATE:			// One or Multi Player, Options, Quit
		break;

	case SCRN_SELECT_CAMPAIGN_STATE:	// One Player campaign selection
		MissionMusic( TRUE );			// stop any mission music playing
		CampaignMusic( FALSE );			// start the campaign music
		break;

	case SCRN_SELECT_CALLSIGN_STATE:	// One Player player name selection
		CampaignMusic( TRUE );			// start the campaign music
		TitleMusic( FALSE );			// start the title music
		break;
	case SCRN_SELECT_MISSION_STATE:		// One Player mission selection
	case SCRN_MULTI_HOST_STATE:			// Multi Player HOST campaign selection
	case SCRN_MULTI_REMOTE_STATE:		// Multi Player HOST campaign selection
		break;

	case SCRN_OPTIONS_STATE:			// Armymen options selection
		TitleMusic( FALSE );			// start the title music
		break;

	case SCRN_CONTROLS_STATE:			// User control configuration
		break;		
	case SCRN_AUDIO_STATE:				// audio configuration
		TitleMusic( FALSE );			// start the title music
		break;		

	case SCRN_ABOUT_STATE:				// About Armymen configuration
	case SCRN_QUIT_STATE:				// Army quit
	case SCRN_STATS_STATE:				// Army statistics
		break;

	case SCRN_KEYPAD_STATE:				// User Keypad configuration
	case SCRN_KEYBOARD_STATE:			// User KeyBoard configuration
	case SCRN_CUSTOM_STATE:				// User Custom configuration
	case SCRN_JOYSTICK_STATE:			// User Joystick configuration
		break;
	}
}

//========================================================================
//							EOF
//========================================================================
