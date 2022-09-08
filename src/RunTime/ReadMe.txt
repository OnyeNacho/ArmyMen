Army Men Readme file
Version 1.0
April 17th, 1998
----------------

Multiplayer 'Boot Camp'
-----------------------
You can go to multiplayer boot camp on any of the multiplayer maps. Select "Serial 
Port" as your communication type and host a session. But don't wait for anyone to 
join you. Select a map and start. The other 3 players will be run by the computer, 
and periodically one of the armies will venture out and come looking for you.


Direct X
--------
We always let you know what version of Direct X you have installed, and ask if you 
want to install version 5.1 for your convenience. This version of the Direct X 
installer does not do partial installs well, however, so if you have damaged your 
Direct X installation (for example, by accidentally deleting some of the Direct X 
files) you may need assistance to re-install DirectX. 


Installation
------------
If some of the system files that Army Men depends on are in use by Windows when 
Army Men is installed, you will need to reboot your system before Army Men will 
work properly. We will let you know when this situation arises and prompt you to 
reboot.


Intro Movie
-----------
If you encounter problems with the openning movie sequence or simply choose not to 
view it, you can enter the command line parameter -nomovies at the end of the 
target line in the Army Men shortcut.

In order to change the shortcut in your Windows Start Menu to Army Men that doesn't play 
the movie intro, do the following:

1) In the Start Menu, choose Settings, then Taskbar.

2) Click on the Start Menu Programs tab.

3) Click on the Advanced button.

4) Double click on the Programs folder on the left side of the Explorer window, then 
click on the Army Men folder.

5) Right click on the Army Men icon on the right side of the Explorer window and select 
Properties from the menu.

6) In the Target box, add the letters -nomovies at the end of the text. So the text 
there will read:
  "C:\Program Files\The 3DO Company\Army Men\Armymen.exe" -nomovies

7) Click the "OK" button at the bottom.


Gunsight Cursor Color
---------------------
Some people have trouble seeing the red gunsight cursor over the terrain. If you 
prefer a white cursor, you can switch between the colors with the 'G' key.


Right Mouse Button
------------------
The right mouse button can either switch sarge between weapons, or move him forward. 
You can switch between these actions with the 'M' key.


Healing Troops
--------------
Just like sarge, troops can be healed in medical tents. Get them to follow you (with 
the F1 key) and lead them into the tent. After a short stay, you will all be feeling 
refreshed.


Laptop Keyboard Configuration
-----------------------------
The initial custom configuration is designed for use with a laptop. If you ever want 
to restore this custom configuration, you can delete the file "custom.cfg" in the 
Army Men folder, duplicate the file "laptop.cfg" and rename it "custom.cfg". 


ALT-TAB Key Use
---------------
On some systems, using the ALT-TAB key combination to switch between active tasks 
can cause Army Men to quit unexpectedly. It is not recommended that you use ALT-TAB 
to toggle between Army Men and other applications for this reason. If an active game 
of Army Men is minimized on your taskbar, clicking on the taskbar icon with the 
mouse pointer to restore the game will not terminate the application unexpectedly.


Multiplayer And The CD
---------------------
To join a session, you do not need a CD. But if you want to hear sounds, you should 
make sure you did a "Typical" or "Complete" Installation.


Multi-Player Via TCP/IP
----------------------
You should establish your connection to the network before starting Army Men.

If you are going to host a game you should find out the IP Address of your 
network connection. Choose Run "winipcfg"  or Run "c:\windows\system\winipcfg" from
the Start Menu and find the IP Address for your connection and write it down.
Note: Your IP Address may change each session depending upon how you are connected
to the network.

If you are joining a TCP/IP game you must know the IP Address of the hosting 
session.   

Multi-Player probably will not work through firewalls or through proxy servers.  


Multi-Player Map Selection Screen
---------------------------------
On the Map Selection Screen the color of each player name changes to indicate
the current state of the connection to that player.

	Green  	good low latency connection
	Yellow	medium latency connection
	Red	high latency connection
 
	Gray	connection temporarily suspended
	Blue	player hasn't yet hit 'Continue' to finish a previous game

The game may become unplayable with high latencies or unreliable connections.

The host checks that every player has an unmodified version the selected Map.
If any player doesn't have the map a message appears and the host will not
be able to start the game.

Playing multiplayer via the Internet is subject to a number of quirks. The amount of 
time it takes for messages to travel between computers (latency), the speed of 
people's modems and the quality of their Internet Service Providers (packet loss) 
can all have an effect on your play experience. If you are experiencing frequent 
delays, dropping from the game and skipping units due to latency, try playing maps 
with fewer units or playing with only 2 or 3 players.

Army Men displays the real time latency as a graphic bar that travels around each 
player's score box at the top of the screen.  As latency and/or packet loss 
increases this bar will turn from green to yellow to red.  If the latency is too 
large (red) Army Men will become unplayable. If the latency gets really bad, Army Men 
will give up and drop you back to the main menu. If your latency and packet loss are 
always high you may need to try a different Internet Service Provider (ISP). You can 
also try a direct modem connection to one friend to avoid Internet latencies.

A note about Online Services: There are online services such as AOL or Compuserve
that allow their users to connect to the Internet. Although these providers give you 
access to the net, you may experience excessive latency while playing a game through 
their access. If you are a subscriber to one of these services, you may find that 
Army Men's performance through these services is less than satisfactory. Our best 
suggestion to alleviate this problem is to secure an account with an ISP rather than 
an Online Service. Most ISP's will tend to provide a faster, consistent connection 
to the Internet.

Multiplayer Via Lobby Servers
-----------------------------
Lobby servers are available for matchmaking Army Men games.  See the options
installed under "C:\Program Files\Army Men\" or visit our WebSites at
			www.armymen.com 
			www.3do.com


Video Card And Other Hardware Drivers
-------------------------------------
Direct X depends on having up to date hardware drivers for your video card and other 
hardware devices, such as your mouse, sound card or network card. If you are having 
difficulty with Army Men displays (screen flickers during game play, sarge leaving 
a trail of dots) or other hardware (erratic mouse movement or choppy sound) try 
updating your drivers. The latest drivers can usually be found on the hardware 
manufacturer's web site.


