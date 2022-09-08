struct THusk
{
	OBJECTSTRUCT object;
	VEHICLE_MASK vehicle_mask;
};


ITEM *FindHuskItem( UID uid );
void CreateVehicleHusk( VEHICLE *pVehicle );
void FreeVehicleHusks( void );
void DestroyVehicleHusk( THusk *pHusk );
void CleanUpDeadHusks( void );
void HuskMessageReceive(ARMY_MESSAGE *pArmyMsg);
void HuskDamageMessageSend( THusk *pHusk, int damagetodo, int damagetype, SPOINT &damageloc );