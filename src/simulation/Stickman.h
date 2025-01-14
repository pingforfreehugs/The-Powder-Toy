#ifndef STICKMAN_H_
#define STICKMAN_H_

#define MAX_FIGHTERS 100
struct playerst
{
	char comm;           //command cell
	char pcomm;          //previous command
	int elem;            //element power
	float legs[16];      //legs' positions
	float accs[8];       //accelerations
	char spwn;           //if stick man was spawned
	unsigned int frames; //frames since last particle spawn - used when spawning LIGH
	bool rocketBoots;
	bool fan;
	int spawnID;         //id of the SPWN particle that spawns it
	int swaptmp; // hacky solution to FIGH tmp usage conflict
	int swaptmp2; // hacky solution to FIGH tmp2 usage conflict
	int pain; // used to let health bars flash yellow when hurt
	bool aim; // whether to shoot at the cursor next frame or not
	float aimx; // x component of where to aim
	float aimy; // y component of where to aim
	bool aiaimed;
	unsigned char aitarget; // id of the fighter to fight if a fighter is set to fight a fighter
	bool aifttd; // whether to fight a fighter or not
};

#endif
