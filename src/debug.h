#ifndef FINAL
	extern void ShowDebugInfo( void );
	extern void test_troop_update();
#else
	#define ShowDebugInfo()
	#define test_troop_update()
#endif