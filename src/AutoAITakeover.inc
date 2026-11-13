// ArmyMen AI Takeover: included by aix.cpp so the original VC4.2 makefile
// needs no additional .obj entry. All strategic decisions execute only for
// the local player's faction; other armies retain their existing AI/scripts.
#ifndef ARMYMEN_AUTO_AI_TAKEOVER_INC
#define ARMYMEN_AUTO_AI_TAKEOVER_INC

extern void MapLookTowardsPoint(int x, int y);

static DWORD autoAIPlanTime = 0;
static DWORD autoAIReserveTime = 0;
static DWORD autoAICameraTime = 0;
static ITEM* autoAICameraItem = NULL;

// The target finder respects the existing visibility system: the AI does
// not receive omniscient knowledge of hidden enemy positions.
static void AutoAIConsiderEnemy(ITEM* candidate, SPOINT from,
                                ITEM** best, int* bestDistance)
{
    int distance;
    if (!candidate || !candidate->tile || candidate->nStrength <= 0)
        return;
    if (!ItemVisible(ARMY_PLAYER, candidate))
        return;
    distance = GetDistance(&from, &candidate->position);
    if (distance < *bestDistance)
    {
        *bestDistance = distance;
        *best = candidate;
    }
}

static ITEM* AutoAINearestEnemy(SPOINT from)
{
    ITEM* best = NULL;
    int bestDistance = 0x7fffffff;
    int army, i;
    LEGION* legion;
    UNIT* unit;
    VEHICLE* vehicle;
    SARGE* sarge;

    FOR_EACH_ARMY(army)
    {
        if (army == ARMY_PLAYER || !Armies[army].Status ||
            Armies[ARMY_PLAYER].bAlliances[army])
            continue;
        legion = ArmyGetLegion(army);
        if (!legion) continue;
        FOR_EACH_UNIT(legion, unit)
        {
            if (!UNIT_IN_OPEN(unit)) continue;
            AutoAIConsiderEnemy((ITEM*)unit, from, &best, &bestDistance);
        }
        FOR_EACH_VEHICLE(legion, i)
        {
            vehicle = legion->pLegionVehicles[i];
            if (vehicle && VEHICLE_ON_MAP(vehicle))
                AutoAIConsiderEnemy((ITEM*)vehicle, from, &best, &bestDistance);
        }
        sarge = SargePointer(army);
        if (sarge)
            AutoAIConsiderEnemy((ITEM*)sarge, from, &best, &bestDistance);
    }
    return best;
}

static SPOINT AutoAIRallyPoint()
{
    SPOINT point;
    SARGE* sarge = SargePointer(ARMY_PLAYER);
    LEGION* legion = ArmyGetLegion(ARMY_PLAYER);
    UNIT* unit;

    if (sarge && sarge->common.tile && sarge->common.nStrength > 0)
        return sarge->common.position;

    if (legion)
    {
        FOR_EACH_UNIT(legion, unit)
        {
            if (UNIT_IN_OPEN(unit) && unit->common.nStrength > 0)
                return unit->common.position;
        }
    }
    point.x = (short)((the_map.boundrect.left + the_map.boundrect.right) / 2);
    point.y = (short)((the_map.boundrect.top + the_map.boundrect.bottom) / 2);
    return point;
}

static SPOINT AutoAIStrategicObjective(SPOINT rally)
{
    int i, color;
    ITEM* target = AutoAINearestEnemy(rally);
    SPOINT goal;
    int bestDistance = 0x7fffffff;

    if (target)
        return target->position;

    // In capture-the-flag games, scout toward an opposing known flag.
    if (gpGame->CaptureFlag)
    {
        color = gpComm->ColorFromIndex(ARMY_PLAYER);
        for (i = 0; i < 4; ++i)
        {
            int distance;
            if (i == color || !flags[i] || !flags[i]->common.tile)
                continue;
            distance = GetDistance(&rally, &flags[i]->common.position);
            if (distance < bestDistance)
            {
                bestDistance = distance;
                goal = flags[i]->common.position;
            }
        }
        if (bestDistance != 0x7fffffff)
            return goal;
    }

    // Without sighting or an explicit map objective, scout the map centre.
    // Unit routing then finds a reachable position rather than wallhacking.
    goal.x = (short)((the_map.boundrect.left + the_map.boundrect.right) / 2);
    goal.y = (short)((the_map.boundrect.top + the_map.boundrect.bottom) / 2);
    return goal;
}

// Only release already existing reserves with a mission-supplied valid
// deployment point. This does not invent resources or create free units.
static void AutoAIReleaseReadyReserve(DWORD now)
{
    LEGION* legion;
    UNIT* unit;
    VEHICLE* vehicle;
    int i;

    if (gpGame->GameType == GAMETYPE_ONEPLAYER)
        return; // preserve single-player scripted reinforcement events
    if (autoAIReserveTime && now - autoAIReserveTime < 20000)
        return;
    autoAIReserveTime = now;

    legion = ArmyGetLegion(ARMY_PLAYER);
    if (!legion) return;
    FOR_EACH_UNIT(legion, unit)
    {
        if (!UNIT_IN_HQ(unit) || unit->paratrooper ||
            unit->deployPosition.x < 5 || unit->deployPosition.y < 5 ||
            !unit->pTroops || !unit->pTroops[0])
            continue;
        ScriptDeploy(ITEM_UID(unit), ATTACKFIRE, NULL, 0);
        ScriptAIControl(ITEM_UID(unit));
        return; // stagger reinforcements to avoid map congestion
    }
    FOR_EACH_VEHICLE(legion, i)
    {
        vehicle = legion->pLegionVehicles[i];
        if (!vehicle || vehicle->state != VEHICLE_UNDEPLOYED ||
            vehicle->deployPosition.x < 5 || vehicle->deployPosition.y < 5)
            continue;
        ScriptDeploy(ITEM_UID(vehicle), ATTACKFIRE, NULL, 0);
        ScriptAIControl(ITEM_UID(vehicle));
        return;
    }
}

void AutoAIStartMission(void)
{
    LEGION* legion;
    UNIT* unit;
    VEHICLE* vehicle;
    SARGE* sarge;
    int i;

    autoAIPlanTime = 0;
    autoAIReserveTime = 0;
    autoAICameraTime = 0;
    autoAICameraItem = NULL;
    if (!Armies[ARMY_PLAYER].Status)
        return;

    legion = ArmyGetLegion(ARMY_PLAYER);
    if (!legion) return;

    FOR_EACH_UNIT(legion, unit)
    {
        if (!UNIT_ALIVE(unit)) continue;
        unit->aiSetup = TRUE;
        ScriptAIControl(ITEM_UID(unit));
    }
    FOR_EACH_VEHICLE(legion, i)
    {
        vehicle = legion->pLegionVehicles[i];
        if (vehicle && vehicle->common.nStrength > 0)
            ScriptAIControl(ITEM_UID(vehicle));
    }
    sarge = SargePointer(ARMY_PLAYER);
    if (sarge && sarge->common.tile && sarge->common.nStrength > 0)
        ScriptAIControl(ITEM_UID(sarge));
}

// Adaptive planner: the engine's per-trooper targeting/formation AI remains
// in charge of actual fighting. This layer supplies higher-level orders.
void AutoAIThink(void)
{
    DWORD now;
    LEGION* legion;
    UNIT* unit;
    VEHICLE* vehicle;
    SARGE* sarge;
    ITEM* target;
    SPOINT rally, objective, goal;
    int i, ready = 0, threats = 0;

    if (gpGame->GetSubState() != PLAY_SUB_STATE ||
        !Armies[ARMY_PLAYER].Status)
        return;
    now = gpGame->dwAnimTime;
    if (autoAIPlanTime && now - autoAIPlanTime < 4000)
        return;
    autoAIPlanTime = now;

    legion = ArmyGetLegion(ARMY_PLAYER);
    if (!legion) return;
    sarge = SargePointer(ARMY_PLAYER);
    rally = AutoAIRallyPoint();
    objective = AutoAIStrategicObjective(rally);

    FOR_EACH_UNIT(legion, unit)
    {
        if (UNIT_IN_OPEN(unit) && unit->common.nStrength > 0)
            ++ready;
    }
    target = AutoAINearestEnemy(rally);
    if (target) ++threats; // one visible force is enough to trigger defense
    if (sarge && sarge->common.nStrength > 0 && sarge->common.tile)
    {
        if (!sarge->npc) ScriptAIControl(ITEM_UID(sarge));
        goal = objective;
        // Do not erase mission scripts' pending arrival-event triggers.
        if (sarge->arrivalEvent != 0 &&
            sarge->arrivalEvent != EVENT_NUM_UNDEFINED)
            goal = sarge->aiGoal;
        if (ready < 2 && target)
            goal = rally; // preserve the commander if the army is depleted
        if (goal.x > 0 &&
            (!sarge->aiGoal.x ||
             GetDistance(&sarge->aiGoal, &goal) > 100))
            ScriptOrder(ITEM_UID(sarge), UNIT_ATTACK, ATTACKFIRE,
                        DEFENDFIRE, FALSE, &goal, 0,
                        EVENT_NUM_UNDEFINED, 0);
    }

    FOR_EACH_UNIT(legion, unit)
    {
        ITEM* localEnemy;
        int distance;
        if (!UNIT_ALIVE(unit)) continue;
        if (!unit->npc) ScriptAIControl(ITEM_UID(unit));
        if (!UNIT_IN_OPEN(unit) || unit->common.nStrength <= 0)
            continue;
        // Scenario scripts can own mission-critical travel/arrival events.
        if (unit->arrivalEvent != 0 &&
            unit->arrivalEvent != EVENT_NUM_UNDEFINED)
            continue;
        localEnemy = AutoAINearestEnemy(unit->common.position);
        distance = localEnemy ?
            GetDistance(&unit->common.position, &localEnemy->position) :
            0x7fffffff;

        if (unit->common.nMaxStrength > 0 &&
            unit->common.nStrength * 3 < unit->common.nMaxStrength &&
            (distance > 256 || ready <= 2))
        {
            // A badly weakened squad regroups around its commander.
            goal = rally;
        }
        else if (localEnemy && distance < 480)
        {
            // Local opportunistic attacks override the global objective.
            goal = localEnemy->position;
        }
        else if (ready < 2 && threats)
            goal = rally;
        else
            goal = objective;

        // Offset groups by tile to reduce clustering at a single waypoint.
        i = (int)(unit - legion->pUnitList);
        if (!localEnemy || distance >= 160)
        {
            goal.x = (short)(goal.x + ((i % 3) - 1) * 24);
            goal.y = (short)(goal.y + (((i / 3) % 3) - 1) * 24);
        }
        ClipNum(&goal.x, the_map.boundrect.left + 16,
                the_map.boundrect.right - 17);
        ClipNum(&goal.y, the_map.boundrect.top + 16,
                the_map.boundrect.bottom - 17);
        if (goal.x <= 0 || UNIT_IN_VEHICLE(unit))
            continue;
        if (unit->focusLocation.x &&
            GetDistance(&unit->focusLocation, &goal) < 96)
            continue;
        ScriptOrder(ITEM_UID(unit), UNIT_ATTACK,
                    (localEnemy ? ATTACKFIRE : DEFENDFIRE),
                    DEFENDFIRE, FALSE, &goal, 0,
                    EVENT_NUM_UNDEFINED, 0);
    }

    FOR_EACH_VEHICLE(legion, i)
    {
        vehicle = legion->pLegionVehicles[i];
        if (!vehicle || !VEHICLE_ON_MAP(vehicle) ||
            vehicle->common.nStrength <= 0) continue;
        if (!vehicle->npc) ScriptAIControl(ITEM_UID(vehicle));
        if (vehicle->arrivalEvent != 0 &&
            vehicle->arrivalEvent != EVENT_NUM_UNDEFINED)
            continue;
        target = AutoAINearestEnemy(vehicle->common.position);
        goal = target ? target->position : objective;
        if (goal.x <= 0) continue;
        if (vehicle->aiGoal.x &&
            GetDistance(&vehicle->aiGoal, &goal) < 128) continue;
        ScriptOrder(ITEM_UID(vehicle), UNIT_ATTACK, ATTACKFIRE,
                    DEFENDFIRE, FALSE, &goal, 0,
                    EVENT_NUM_UNDEFINED, 0);
    }
    AutoAIReleaseReadyReserve(now);
}

static int AutoAICameraScore(ITEM* item, int bonus)
{
    if (!item || !item->tile || item->nStrength <= 0)
        return -1;
    if (item->nMaxStrength > 0 &&
        item->nStrength * 2 < item->nMaxStrength)
        bonus += 35;
    if (item == autoAICameraItem)
        bonus += 40; // prevent constant, distracting camera cuts
    return bonus;
}

// All camera decisions are local visual state; no game/network commands.
void AutoAICamera(void)
{
    DWORD now;
    LEGION* legion;
    SARGE* sarge;
    UNIT* unit;
    VEHICLE* vehicle;
    ITEM* best = NULL;
    int bestScore = -1;
    int score, i;

    if (gpGame->GetSubState() != PLAY_SUB_STATE ||
        !Armies[ARMY_PLAYER].Status)
        return;
    now = gpGame->dwAnimTime;
    legion = ArmyGetLegion(ARMY_PLAYER);
    if (!legion) return;

    if (!autoAICameraItem || !autoAICameraItem->tile ||
        autoAICameraItem->nStrength <= 0 ||
        now - autoAICameraTime >= 6000)
    {
        sarge = SargePointer(ARMY_PLAYER);
        if (sarge)
        {
            score = AutoAICameraScore((ITEM*)sarge, 80);
            if (score > bestScore) { best = (ITEM*)sarge; bestScore = score; }
        }
        FOR_EACH_UNIT(legion, unit)
        {
            if (!UNIT_IN_OPEN(unit)) continue;
            score = AutoAICameraScore((ITEM*)unit,
                     UNIT_ENGAGED(unit) ? 210 :
                     UNIT_MOVING(unit) ? 95 : 30);
            if (score > bestScore) { best = (ITEM*)unit; bestScore = score; }
        }
        FOR_EACH_VEHICLE(legion, i)
        {
            vehicle = legion->pLegionVehicles[i];
            if (!vehicle || !VEHICLE_ON_MAP(vehicle)) continue;
            score = AutoAICameraScore((ITEM*)vehicle,
                     vehicle->full_velocity ? 115 : 35);
            if (score > bestScore) { best = (ITEM*)vehicle; bestScore = score; }
        }
        autoAICameraItem = best;
        autoAICameraTime = now;
    }
    if (autoAICameraItem && autoAICameraItem->tile &&
        autoAICameraItem->nStrength > 0)
        MapLookTowardsPoint(autoAICameraItem->position.x,
                            autoAICameraItem->position.y);
}

#endif // ARMYMEN_AUTO_AI_TAKEOVER_INC
