# Full AI Takeover + Intelligent Spectator Camera (prototype)

This feature branch turns the **local player's faction** into an AI-run army as soon as a mission starts. The human player watches the fight through an automatic, smoothly panning camera rather than issuing orders.

## Install on Windows

1. Clone or download branch `feature/ai-autoplay-spectator-camera` from `MattKoRn/ArmyMen`.
2. In a Windows environment containing **NMAKE**, **cl.exe**, and the original game's compatible legacy VC++ / DirectX SDK dependencies, double-click **`INSTALL_AI_TAKEOVER.cmd`** at the repository root.
3. The script builds `src/Armymen.mak` in Release configuration, backs up `src/RunTime/Armymen.exe` (if present), installs the patched executable, and launches the game.
4. If compilation fails or the toolchain is unavailable, the script stops without replacing the original executable. Do not use the checked-in binary as evidence the patch is already compiled; that binary predates these changes.

The script only `git pull --ff-only` when already on this feature branch. It does not force-reset your local changes. You can restore the previous executable from `Armymen.exe.before-ai-takeover`.

## Features and integration points

- **Immediate handover:** `BeginMission` calls `AutoAIStartMission`. Player units, available vehicles and Sarge switch to the original game's NPC/script AI control.
- **Continuous autonomous planning:** `AICommander` calls `AutoAIThink` approximately every 4 seconds; the existing unit AI keeps responsibility for individual trooper firing, pathing and formation.
- **Adaptive tactics:** local threats are prioritised; weakened squads fall back to the commander; healthy forces advance toward a shared target or scout the map centre. Capture-the-flag matches pursue a known opposing flag location.
- **Vehicle/commander control:** the existing Sarge and vehicle AI receives destination and attack/defend orders.
- **Controlled reserves:** in multiplayer, already-prepared units/vehicles with valid mission deployment coordinates can enter play, at most one every 20 seconds. Single-player scripted reinforcement events are preserved.
- **Automatic camera:** `UI_ProcessScreen` gives the spectator camera control of the viewport. The camera looks for ongoing squad combat, moving vehicles and Sarge, holds an interesting subject before switching, and pans using the game's existing scroll helper.
- **Input isolation:** during active gameplay, the AI spectator gets only the Escape/menu key and mouse command handlers refuse unit orders. Mission/setup menus remain available.

## Architecture and limitations

This is a first playable **source-level prototype**, not a tested standalone mod, binary patch, or rewritten game AI. The repository is the *Army Men (1998)* source code, not a base-building RTS. It has mission-specified reserves and air-support resources but does **not** provide a general economy, buildings-to-construct, harvesting, research or unit factory gameplay loop. Therefore “all production/resources” currently means the AI operates available forces and mission-prepared reserves—not an invented construction/economy system.

The strategic AI shares enemy knowledge through `ItemVisible` rather than inspecting the entire map. Without visible targets or flag objectives it scouts the map centre. The director uses existing routing; unreachable goals may fail. Scripted single-player objectives and mission completion should be regression-tested; scripted arrival-event orders should take precedence. Local-multiplayer authority, networking, camera visibility/fog, and bootcamp/campaign edge cases require playtesting before considering all modes production-ready.

## Manual test checklist

- [ ] Build patched EXE using the historical VC++ toolchain.
- [ ] Start a new single-player mission and confirm Sarge and all starting squads move without keyboard or mouse input.
- [ ] Verify mouse clicks and combat keys do not issue orders while Escape opens the pause/menu screen.
- [ ] Observe camera staying on an engagement, following moving units, and panning smoothly when focus changes.
- [ ] Confirm a weakened squad regroups; other squads continue advancing.
- [ ] Confirm targets outside the army's visible range aren't directly chased.
- [ ] Confirm scripted mission objectives and victory/failure conditions still fire.
- [ ] Test capture-the-flag, a hosted multiplayer session, and a remote client; inspect AI ownership and synchronization.
- [ ] Confirm prepared reserves deploy only at legal assigned points and resource counts are not fabricated.
- [ ] Check save/restore and transition into a second mission; verify AI state resets correctly.

## Files changed

`src/AutoAITakeover.inc` contains the AI director and camera; it is included from `src/aix.cpp` because the legacy NMAKE project lists every object explicitly. `src/Aix.h`, `src/GameFlow.cpp`, `src/ui.cpp`, and `src/Unit.cpp` provide the integration hooks and input isolation. `INSTALL_AI_TAKEOVER.cmd` performs build/install/launch where the historical tools are available.
