# Army Men [1998] Source Code & Tools

These files contain the source code to the first Army Men game released in 1998 by The 3DO Company. They also contain the level, scenario, animation editor along with some of the uncompressed 2D art assets.

Originally discovered by:
- _Z3N_

Special Thanks:
- Trapexit
- The 3DO Company
- Army Men fans

## Autonomous AI spectator mode

The current `main` source includes an AI takeover prototype that controls the local player's army and pans the spectator camera. On Windows, double-click [`INSTALL_AI_TAKEOVER.cmd`](INSTALL_AI_TAKEOVER.cmd) from a checkout of `main` to build, back up the existing executable, install, and launch. **The original 1998 NMAKE project requires a compatible legacy MSVC/DirectX development environment.** If a required tool is missing or compilation fails, the installer stops without replacing the original executable.

See [`docs/AI_TAKEOVER.md`](docs/AI_TAKEOVER.md) for supported behaviours, limitations, and the manual test checklist. This code is a prototype and has not been verified by a full Windows build or gameplay test.
