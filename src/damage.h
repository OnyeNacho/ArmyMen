/////////////////////////////////////////////////////////////////////////////
// defines
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Function Prototypes
/////////////////////////////////////////////////////////////////////////////

void ObjectDamage(OBJECT *pObj, int nDamage, int eDamageType, SPOINT damageloc, int dosideeffects,UID fromUID);
BOOL ObjectIsDestroyed(OBJECT *pObj);
void ItemDamage(ITEM* pItem, int nDamage, int eDamageType, SPOINT* from,UID fromUID);
int DamageFromBehind(int nDamage, int direction, ITEM *pItem);
void DamageItemTriggerEvents(ITEM *pItem, int oldstrength, int newstrength, int maxstrength);
void DiedItemTriggerEvents(ITEM *pItem);
void Dmg_SetObjectDamage(OBJECT *pObj, AI_ITBL* pAiObjDef, int damagelevel);

