/*#define x_DEBUG 1*/

           
static int nblocks;
static int blockIds[1000];
static int blockRoute[1000];

static int GRIDMAX;
static int x_limit; /* x limit */
static int y_limit; /* y limit */
#define MAXCOORD 1023
#define LARGESTOBJECT 2000     /* tiles in largest object */
#define OBJECTTYPE(x) ((((unsigned char) x) >> 4) & 0x0f)
#define SPEED(x) (x & 0x0f)

int NextDeazil(int depth,int dir);
static int xsafe,ysafe,blockedx,blockedy,norient; /* for walking */
static char buf[70];

/* assume max coord is 9 bits 0...1023 */
#define LEFTBIT 0x80000000
#define RIGHTBIT 0x40000000
#define UNCHECKED(y) (y & (LEFTBIT | RIGHTBIT))
#define ENCODEI(y) (((long)y) << 9)
#define ENCODEJ(x) ((long)x)
#define DECODEI(y) ((((long)y) >> 9) & 0x01ff)
#define DECODEJ(x) (((long)x) & 0x01ff)
#define LEVEL(x) ((x) >> 20) /* level is 11 bits */
#define ENCODELEVEL(x) ((x) << 20) /* level is 11 bits */
#define ADJUST(x,l)  (((x) & 0x000fffff) | ((l) << 20))
#define INDEX(y,x,xsize) (((y) * (xsize)) + (x))

typedef struct Doorway {
    long endleft;
    long endright;
    int id1;
    int id2;
} ANSWERS;

static int currentObject;		/* objects 1-4 are the 4 edge pseudoobjects */
static int ndoors;
static int spreadIndex;

unsigned long *objectLocations;				/* where are there objects */
unsigned char* idData;								/* xref of object id */
unsigned char* moveData;
unsigned long *influence;					/* who sees what map */
unsigned long *spread;
#define BLOCKED(xto,yto) (SPEED(moveData[INDEX(yto,xto,x_limit)]) >= 15)
#define IS_BLOCKED(index) (SPEED(moveData[index]) >= 15)

void InitDoors(void){

    int i;
    for (i = 0; i < GRIDMAX; ++i) idData[i] = 0;  /* objects not there */
    currentObject = 5;
    ndoors = -1;
}

int FindObject(int id,int i,int j,int type,int size){
/* find an object recursively */
    int index = INDEX(i,j,x_limit);
    int movement = moveData[index];

    if (!IS_BLOCKED(index)) return size;	 	/* no object here */
    if (idData[index] != 0) return size;	/* object already marked */
    /* if water and mountain both impassable, want different objects for them*/
    /*notsametype*/
//    if (type != -1 && OBJECTTYPE(movement) != type) return size;
	type = OBJECTTYPE(movement);
    idData[index] = id;				/* mark this object  */
    ++size;
    
    /* look in each of 8 directions for more of same*/
    if ((i+1) < y_limit) size = FindObject(id,i+1,j,type,size);
    if ((i-1) >= 0) size = FindObject(id,i-1,j,type,size);
    if ((j+1) < x_limit) size= FindObject(id,i,j+1,type,size);
    if ((j-1) >= 0) size= FindObject(id,i,j-1,type,size);

    if ((i+1) < y_limit && (j-1) >= 0) size = FindObject(id,i+1,j-1,type,size);
    if ((i+1) < y_limit && (j+1) < x_limit) size = FindObject(id,i+1,j+1,type,size);
    if ((i-1) >= 0 && (j-1) >= 0) size = FindObject(id,i-1,j-1,type,size);
    if ((i-1) >= 0 && (j+1) < x_limit) size = FindObject(id,i-1,j+1,type,size);

    return size;							/* did some object */
}

void WalkObject(int id,int i,int j){
/* walk an object recursively */

    int index = INDEX(i,j,x_limit); long val;
    if (idData[index] != id) return;	
    if (influence[index] != 0xffffffff) return; /* been here already */

    val = ENCODEI(i) | ENCODEJ(j);
    influence[index] = val;				/* base 0 influence */
    spread[++spreadIndex] = val;				/* added member */

    /* look in each of 8 directions for more of same*/
    if ((i+1) < y_limit) WalkObject(id,i+1,j);
    if ((i-1) >= 0) WalkObject(id,i-1,j);
    if ((j+1) < x_limit) WalkObject(id,i,j+1);
    if ((j-1) >= 0) WalkObject(id,i,j-1);

    if ((i-1) >= 0 && (j-1) >= 0) WalkObject(id,i-1,j-1);
    if ((i-1) >= 0 && (j+1) < x_limit) WalkObject(id,i-1,j+1);
    if ((i+1) < y_limit && (j-1) >= 0) WalkObject(id,i+1,j-1);
    if ((i+1) < y_limit && (j+1) < x_limit) WalkObject(id,i+1,j+1);
}

void ComputeObjects(){

    int i,j,size;

    /* walk the grid and create objects */
    for (i = 0; i < y_limit; ++i){
        for (j = 0; j < x_limit; ++j){
            if (size = FindObject(currentObject,i,j,-1,0)){/* object created*/
                objectLocations[currentObject] = ENCODEI(i) | ENCODEJ(j);
                ++currentObject;	/* allocate new object */
            }
        }
    }
    /* when done, currentObject is on next unallocated object */
}

static void AddDoor(int id1,int id2,int current,int from,
    ANSWERS* results, int max,int a,int b){

    int i,last = ndoors,x,y;  
    /* is it already here */
    if (last > max) last = max;
    for (i = 0; i <= ndoors; ++i){ /* is it already in this list? */
        if (results[i].id1 == id1 && results[i].id2 == id2) return;
    }
    
    if (++ndoors >= max) return; /* cannot add more */

    a = DECODEI(current);
    b = DECODEJ(current);
    x = DECODEI(from);
    y = DECODEJ(from);
    
    results[ndoors].endleft = current;
    results[ndoors].endright = from;
    results[ndoors].id1 = id1;
    results[ndoors].id2 = id2;
}

static void HitWall(int id1,int a,int b,unsigned long val,
    ANSWERS* results,int max){

    unsigned long from = influence[INDEX(a,b,x_limit)];

    int pt =  ENCODEI(a) | ENCODEJ(b);
    int id2 = idData[INDEX(DECODEI(from),DECODEJ(from),x_limit)];

    AddDoor(id1,id2,pt,from,results,max,a,b);
}

void DoSpread(int a,int b,unsigned long val,ANSWERS* results,int max){

    int pt = INDEX(a,b,x_limit);
    unsigned l = LEVEL(val) + 1;
    unsigned long current = influence[pt];
    unsigned long from = influence[INDEX(DECODEI(val),DECODEJ(val),x_limit)];

    if (LEVEL(current) > l){ /* found a worse place */
        influence[pt] = ADJUST(from,l);
        spread[++spreadIndex] = ENCODELEVEL(l) | ENCODEI(a) | ENCODEJ(b);
    }
    else{ /* hit another group at better or equal */
        int id1 = idData[INDEX(DECODEI(current),DECODEJ(current),x_limit)];
        int id2 = idData[INDEX(DECODEI(from),DECODEJ(from),x_limit)];
        int tmp; long ltmp;
        if (id1 == id2) return; /* from same group */
        /* is this first time? */
        if (id1 > id2){ /* cannonical order */
            ltmp = current;
            current = from;
            from = ltmp;
            tmp = id1;
            id1 = id2;
            id2 = tmp;
        }

        AddDoor(id1,id2,current,from,results,max,a,b);
    }            
}

int ComputeInfluence(ANSWERS* results,int max){

    int i,a,b; unsigned long val;

    /* initialize influence map */
    for (i = 0; i < GRIDMAX; ++i) influence[i] = 0xffffffff; /* max high */

    /* for all objects, sytoe them on the base list */
    /* skip the 4 edge pseudoobjects */
    spreadIndex = 0;
    for (i = 5; i < currentObject; ++i){
        /* get points of the current object */
        WalkObject(i,DECODEI(objectLocations[i]),DECODEJ(objectLocations[i]));
    }

    /* now all base points have been copied into spread */
    for (i = 1; i <= spreadIndex; ++i){
        val = spread[i];
        a = DECODEI(val);
        b = DECODEJ(val);

        /* try to spread to the 8 neighbors */
        if ((a+1) < y_limit) DoSpread(a+1,b,val,results,max);
        else HitWall(1,a,b,val,results,max);/* hit edge1 */

        if ((a-1) >= 0) DoSpread(a-1,b,val,results,max);
        else HitWall(3,a,b,val,results,max);/* hit edge2 */

        if ((b+1) < x_limit)  DoSpread(a,b+1,val,results,max);
        else HitWall(2,a,b,val,results,max); /* hit edge3 */

        if ((b-1) >= 0) DoSpread(a,b-1,val,results,max);
        else HitWall(4,a,b,val,results,max); /* hit edge4 */

        /* handle diagonals also */
        if ((a+1) < y_limit && (b+1) < x_limit) DoSpread(a+1,b+1,val,results,max);
        if ((a+1) < y_limit && (b-1) >= 0) DoSpread(a+1,b-1,val,results,max);
        if ((a-1) >= 0 && (b+1) < x_limit) DoSpread(a-1,b+1,val,results,max);
        if ((a-1) >= 0 && (b-1) >= 0) DoSpread(a-1,b-1,val,results,max);
    }

    return ndoors; /* number of doors sytoed */
}

int GetDoors(int start, int m, int n,
            char * data,
            char *dataC2,
            long *dataL1,
            long *dataL2,
            long *dataL3,
            ANSWERS* results,int max){

    int i,j; int a,b,x,y,diffx,diffy; int a1,b1,x1,y1;
    moveData = (unsigned char*) data;
    idData = (unsigned char*) dataC2;
    influence = (unsigned long *) dataL1;
    spread = (unsigned long *) dataL2;
    objectLocations = (unsigned long *) dataL3;
    GRIDMAX  = m * n; /* m rows of n columns */
    x_limit = n;
    y_limit = m;	
    
    InitDoors();
    ComputeObjects();
    ndoors = ComputeInfluence(results,max);

    /* remove multiple doors from same pt to contiguous objects */
    /* remove doors on objects adjacent to each other */
    for (i = ndoors; i >= 0; --i){
        a = DECODEI(results[i].endleft);
        b = DECODEJ(results[i].endleft);
        x = DECODEI(results[i].endright);
        y = DECODEJ(results[i].endright);
        for (j = i-1; j >= 0; --j){
            a1 = DECODEI(results[j].endleft);
            b1 = DECODEJ(results[j].endleft);
            x1 = DECODEI(results[j].endright);
            y1 = DECODEJ(results[j].endright);
            if (a1 == a && b1 == b);
            else if (x1 == a && y1 == b);
            else if (a1 == x && b1 == y);
            else if (x1 == x && y1 == y);
            else continue;
            /* does it go to same object */
            break;
        }
        if (j < 0) continue; /* no common point */

        if (TRUE){ /* just remove this door */
            results[i].endleft = results[ndoors-1].endleft;
            results[i].endright = results[ndoors-1].endright;
            results[i].id1 = results[ndoors-1].id1;
            results[i].id2 = results[ndoors-1].id2;
            --ndoors;
        }
    }



    /* remove doors on objects adjacent to each other */
    for (i = ndoors; i >= 0; --i){
        a = DECODEI(results[i].endleft);
        b = DECODEJ(results[i].endleft);
        x = DECODEI(results[i].endright);
        y = DECODEJ(results[i].endright);
        diffx = a-x;
        diffy = b-y;
        if (diffx < 0) diffx = -diffx;
        if (diffy < 0) diffy = -diffy;
        /* if door is tight, ignore it */
        if ((diffx + diffy) <= 1){ /* contiguous */
            results[i].endleft = results[ndoors-1].endleft;
            results[i].endright = results[ndoors-1].endright;
            results[i].id1 = results[ndoors-1].id1;
            results[i].id2 = results[ndoors-1].id2;
            --ndoors;
        }
    }
    return ndoors;
}


int FindLine(int yfrom,int xfrom,int yto,int xto,unsigned long * pts){

    int n = 0;
    int cd = (xto - xfrom);
    int rd = (yto - yfrom);
    int c = (cd >= 0) ? cd : -cd;	/* abs value */
    int r = (rd >= 0) ? rd : -rd;   /* abs value */
    pts[n++] = ENCODEI(yfrom) | ENCODEJ(xfrom);
    while (xfrom != xto || yfrom != yto){
        if (xfrom > xto) --xfrom;
        else if (xfrom < xto) ++xfrom;
        if (yfrom > yto) --yfrom;
        else if (yfrom < yto) ++yfrom;
        pts[n++] = ENCODEI(yfrom) | ENCODEJ(xfrom);
    }
    return n;
}

short int xdata[] = /* x */
    {0,  1,1,1,0,-1,-1,-1, 0,1,1,1,0,-1,-1,-1, 0,1,1,1,0,-1,-1,-1,
            0,1,1,1,0,-1,-1,-1};
short int ydata[] = /* y */
    {-1,-1,0,1,1, 1,0,-1, -1,-1,0,1,1,1,0,-1,  -1,-1,0,1,1,1,0,-1,
            -1,-1,0,1,1,1,0,-1};

int cross (int ptx,int pty,int fromx,int fromy,int tox,int toy){
/* compute the x product of line and point. > 0 means right < 0 means left*/

	return -(((tox - ptx) * (fromy - pty)) - ((fromx - ptx) *  (toy - pty)));}

unsigned long distance(int fromx,int fromy, int tox,int toy){

    unsigned long distance;
    distance = (tox - fromx) * (tox - fromx);
    distance += (toy - fromy) * (toy - fromy);
    return distance;
}

unsigned long ReRoute(int y,int x,int oldr,int oldc,
    int xfrom,int yfrom,int xto,int yto,int dir,int otherx,int othery){
// x,y are blocked  oldr,oldc are good just before block
// line goes from...to    

    int bestx = -1,besty = 0,bestval,val,limit = 0;
    bestval = (dir > 0) ? 0 : 31000;

    blockedx = x;
    blockedy = y;
    xsafe = oldc;
    ysafe = oldr;
    
    int cd = xsafe - blockedx; /* x */
    int rd = ysafe - blockedy; /* y */
    /* find our place on the ring */
    for (norient = 8; norient <= 16; ++norient) 
        if (xdata[norient] == cd && ydata[norient] == rd) break;
        
    int stop = 0;
    while (1){
        if (!NextDeazil(0,-dir)){
            val = cross(blockedx,blockedy,xfrom,yfrom,xto,yto);
            if (dir > 0 && val > 0) return 0xffffffff;
            if (dir < 0 && val < 0) return 0xffffffff;
            break;
        }
        if (xsafe == xto && ysafe == yto){
            break; /* back at entry */
        }
        if (++limit >= 10000){
            break; /* took too long */
        }
        if (besty == oldr && bestx == oldc){
            break;
        }
        val = cross(xsafe,ysafe,xfrom,yfrom,xto,yto);
        if (xsafe == otherx && ysafe == othery){
            break;
        }

        // if we reach our starting loc
        if (xsafe == xfrom && ysafe == yfrom && limit > 8){
            bestx = -1;
            bestval = (dir > 0) ? 0 : 31000;
            continue;
        }
        if (dir > 0){
            if (val > bestval){
                bestval = val;
                bestx = xsafe;
                besty = ysafe;
            }
        }
        else{
            if (val < bestval){
                bestval = val;
                bestx = xsafe;
                besty = ysafe;
            }
        }
    }

    if (bestx == -1){
        return 0xffffffff;
    }

    return ENCODEJ(bestx) | ENCODEI(besty);
}    


void Adjust(unsigned long* from,int at,unsigned long* to){
    /* is travel ok along this unit */

    int changed = 0;
	unsigned long hold[10000];
    int n,i,yfrom,xfrom,yto,xto;

    xfrom = DECODEJ(from[at-1]);
    yfrom = DECODEI(from[at-1]);
    xto = DECODEJ(from[at]);
    yto = DECODEI(from[at]);

    n = FindLine(yfrom,xfrom,yto,xto,hold); /* get the points of line */
    for (i = 1; i < n; ++i){ /* see if no movement blocks on one way */
        if (idData[INDEX(DECODEI(hold[i]),DECODEJ(hold[i]),x_limit)] != 0)
            break; /* this line blocked */
    }
    if (i < n){ /* way 1 was blocked, try way 2 */
        unsigned long hold1[10000]; int i;
        n = FindLine(yto,xto,yfrom,xfrom,hold1); /* get the points of line */
        for (i = 0; i < n; ++i) hold[n-i-1] = hold1[i];
    }

    int xd = DECODEJ(hold[1])-DECODEJ(hold[0]);
    int yd = DECODEI(hold[1])-DECODEI(hold[0]);
    for (i = 1; i < n; ++i){
        int xd1 = DECODEJ(hold[i])-DECODEJ(hold[i-1]);
        int yd1 = DECODEI(hold[i])-DECODEI(hold[i-1]);
        if (xd1 != xd || yd1 != yd){
            xd = xd1;
            yd = yd1;
            to[++to[0]] = hold[i];
        }
    }
}

int FreeLine(unsigned long* from,int at,unsigned long* to,unsigned long maxn){
    /* is travel ok along this unit */

    int changed = 0;
    int n,i,x,y,index,oldy,oldx;   unsigned long hold[10000];
    int yfrom,xfrom,yto,xto;

    if (from[0] > maxn){
        from[at] &= -1L ^ (LEFTBIT | RIGHTBIT);
        to[0] = 0; /* cannot pass */
        from[0] = 0; /* cannot pass */
        return 0; /* no change allowed, too complex */
    }
    xfrom = DECODEJ(from[at-1]);
    yfrom = DECODEI(from[at-1]);
    xto = DECODEJ(from[at]);
    yto = DECODEI(from[at]);

    n = FindLine(yfrom,xfrom,yto,xto,hold); /* get the points of line */
    for (i = 1; i < n; ++i){ /* see if no movement blocks on one way */
        if (idData[INDEX(DECODEI(hold[i]),DECODEJ(hold[i]),x_limit)] != 0)
            break; /* this line blocked */
    }
    if (i < n){ /* way 1 was blocked, try way 2 */
        unsigned long hold1[10000]; int i;
        n = FindLine(yto,xto,yfrom,xfrom,hold1); /* get the points of line */
        for (i = 0; i < n; ++i) hold[n-i-1] = hold1[i];
    }

    oldy = yfrom;
    oldx = xfrom;
    for (i = 1; i < n; ++i){ /* see if no movement blocks */
        x = DECODEJ(hold[i]);
        y = DECODEI(hold[i]);
        index = INDEX(y,x,x_limit);
        if (idData[index] != 0){ /* blocked, insert reroute */
            // find last block on line from reverse 
           int id = idData[index];  // search for this object
           int j,ax,by,index1;
           for (j = n-1; j >= 1; --j){ /* see if no movement blocks */
               ax = DECODEJ(hold[j]);
               by = DECODEI(hold[j]);
               index1 = INDEX(by,ax,x_limit);
               if (idData[index1] == id){
                   break; /* last break on line */
               }
           }
           ax = DECODEJ(hold[j+1]);
           by = DECODEI(hold[j+1]);
           /* find current direction around object */
           for (j = 1; j <= nblocks; ++j){
               if (id == blockIds[j]) break;
           }
           int limit = (j <= nblocks) ? blockRoute[j] : 0;
           unsigned long ans,ans1;
           // go right
           if (limit & 1) ans = 0xffffffff;
           else{
               ans = ReRoute(y,x,oldy,oldx,xfrom,yfrom,xto,yto,1,ax,by);
           }
           // go left
           if (limit & 2) ans1 = 0xffffffff;
           else{
               ans1 = ReRoute(y,x,oldy,oldx,xfrom,yfrom,xto,yto,-1,ax,by);
           }
           if (ans != 0xffffffff && ans1 != 0xffffffff){
                /* could go either way */
                int x =DECODEJ(ans), y = DECODEI(ans),val,val1; 
                val = cross(x,y,xfrom,yfrom,xto,yto);
                x = DECODEJ(ans1);
                y = DECODEI(ans1); 
                val1 = -cross(x,y,xfrom,yfrom,xto,yto);
                if (val > val1){
                    ans = ans1; /* choose least deviation */
                    ans |= LEFTBIT;
                    if (!limit){
                        blockIds[++nblocks] = id;
                        blockRoute[nblocks] = 1; // left
                    }
                }
                else{
                    x = DECODEJ(ans);
                    y = DECODEI(ans); 
                    ans |= RIGHTBIT;
                    if (!limit){
                        blockIds[++nblocks] = id;
                        blockRoute[nblocks] = 2; // right
                    }
                }
            }
            else if (ans != 0xffffffff){ /* must go right */
                x = DECODEJ(ans);
                y = DECODEI(ans); 
                ans |= RIGHTBIT;
                if (!limit){
                    blockIds[++nblocks] = id;
                    blockRoute[nblocks] = 2; // right
                }
            }
            else if (ans1 != 0xffffffff){ /* must go left */
                x = DECODEJ(ans1);
                y = DECODEI(ans1); 
                ans = ans1 | LEFTBIT;
                if (!limit){
                    blockIds[++nblocks] = id;
                    blockRoute[nblocks] = 1; // left
                }
            }
            else if (ans == 0xffffffff){/* cant go at all */
                from[at] &= -1L ^ (LEFTBIT | RIGHTBIT);

                #ifdef JUNK
                // FAIL 
                from[0] = 0;
                to[0] = 0;
                return 0;
                #endif
                from[0] = at; /* cannot pass */
                return 1; /* no way found */
            }

            to[++to[0]] = ans;
            from[at] |= LEFTBIT | RIGHTBIT;	/* will need to recheck reroute*/
            return 1;
        }
        else {
        }
        oldx = x;
        oldy = y;
    }    

    from[at] &= -1L ^ (LEFTBIT | RIGHTBIT); /* did it ok */
    return changed;
}
    
int GetRoute(int yfrom, int xfrom, int yto, int xto,
    unsigned long * data, UINT max){

    unsigned long routing[20000],routing1[20000];    
	unsigned long n,i,check;
    unsigned long *from,*to,*temp;
    /* cannot possibly get between the two points-- one is blocked */
    if (BLOCKED(xfrom,yfrom)) return 0;
    if (BLOCKED(xto,yto)) return 0;
    from = routing;
    to = routing1;
    /* the simple route */
    from[1] = ENCODEI(yfrom) | ENCODEJ(xfrom);
    from[2] = ENCODEI(yto) | ENCODEJ(xto) | LEFTBIT | RIGHTBIT;
    from[0] = 2;
    nblocks = 0;
    check = 1;
    while (check){ /* check routes until fully expanded */
		check = 0;
        to[0] = 1;
        to[1] = from[1];			 /* xfer to */
        for (i = 2; i <= from[0]; ++i){
            if (!check && (from[i] & (LEFTBIT | RIGHTBIT))){
                if (FreeLine(from,(int)i,to,max)) check = 1;
            }
            to[++to[0]] = from[i];			 /* xfer to */
        }

        /* switch and try again */
        temp = from;
        from = to;
        to = temp;
    }    

    /* final validation adjustment on visible bends */
    to[0] = 1;    
    to[1] = from[1];
    for (i = 2; i <= from[0]; ++i){
        Adjust(from,i,to);
        to[++to[0]] = from[i];			 /* xfer to */
        if (to[0] >= (max-2)){ /* overflow routes */
            to[++to[0]] = from[from[0]];	 /* xfer final */
            break;
        }
    }

    n         = 0;
	i         = ENCODEI(yfrom) | ENCODEJ(xfrom);
	data[n++] = i;
    for (i = 1; i <= to[0]; ++i){
        int x = DECODEJ(to[i]);
        int y = DECODEI(to[i]);         
        sprintf(buf,"\r\n Final %d.%d  %d",x,y,i);
        data[n++] = to[i];
    }
 	i         = ENCODEI(yto) | ENCODEJ(xto);
	data[n++] = i;
    return n; 			/* number of paths of points */
}

int NextDeazil(int depth,int dir){/*walk on object at its perimeter clockwise*/
/* norient points from blocked to non-block spot */

    int index;
    if (depth > 5) return 0;
    norient += dir;
    { /* keep going til hit object again */
        xsafe  = blockedx + xdata[norient];
        ysafe  = blockedy + ydata[norient];
        if (xsafe < 0 || xsafe >= x_limit) return 0; /* cannot go here */
        if (ysafe < 0 || ysafe >= y_limit) return 0; /* cannot go here */
        index = INDEX(ysafe,xsafe,x_limit);

        if (IS_BLOCKED(index)){ /* try again */
            blockedx = xsafe;
            blockedy = ysafe;
            norient -= dir << 1;
            if (norient & 1) norient -= dir;
            norient = (norient & 0x0007) + 16; /* smooth middle */

            /* start in middle cycle */

            return NextDeazil(depth+1,dir);
        }
        /* 360 loop failed to find another object pt */
        if (norient > 31){
            return 0;
        }
    }

    return 1; /* found another */
}
