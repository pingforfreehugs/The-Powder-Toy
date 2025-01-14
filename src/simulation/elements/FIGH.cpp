#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static bool createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS);
static void changeType(ELEMENT_CHANGETYPE_FUNC_ARGS);
static void Free(Simulation *sim, unsigned char i);
bool Element_FIGH_CanAlloc(Simulation *sim);
int Element_FIGH_Alloc(Simulation *sim);
void Element_FIGH_NewFighter(Simulation *sim, int fighterID, int i, int elem);
int Element_STKM_graphics(GRAPHICS_FUNC_ARGS);
void Element_STKM_init_legs(Simulation * sim, playerst *playerp, int i);
int Element_STKM_run_stickman(playerst *playerp, UPDATE_FUNC_ARGS);

void Element::Element_FIGH()
{
	Identifier = "DEFAULT_PT_FIGH";
	Name = "FIGH";
	Colour = PIXPACK(0xFFE0A0);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	Advection = 0.5f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.2f;
	Loss = 1.0f;
	Collision = 0.0f;
	Gravity = 0.0f;
	NewtonianGravity = 0.0f;
	Diffusion = 0.0f;
	HotAir = 0.00f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 50;

	DefaultProperties.temp = R_TEMP + 14.6f + 273.15f;
	HeatConduct = 0;
	Description = "Fighter. Tries to kill stickmen. Note: You have to set their TMP properties with DTEC.";

	Properties = PROP_NOCTYPEDRAW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 620.0f;
	HighTemperatureTransition = PT_FIRE;

	DefaultProperties.life = 100;

	Update = &update;
	Graphics = &Element_STKM_graphics;
	CreateAllowed = &createAllowed;
	ChangeType = &changeType;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].tmp < 0 || parts[i].tmp >= MAX_FIGHTERS)
	{
		sim->kill_part(i);
		return 1;
	}
	playerst* figh = &sim->fighters[(unsigned char)parts[i].tmp];

	int tarx, tary;
	
	
	parts[i].tmp2 = 0; //0 - stay in place, 1 - seek a stick man, 2 - fight a fighter

	//Set target cords
	if (figh->aifttd && sim->fighters[(unsigned char)figh->aitarget].spwn)
	{	
		tarx = (int)sim->fighters[figh->aitarget].legs[2];
		tary = (int)sim->fighters[figh->aitarget].legs[3];
		parts[i].tmp2 = 1;
	}
	else
	{
		figh->aifttd = false;
		if (sim->player2.spwn)
		{
			if (sim->player.spwn && (pow((float)sim->player.legs[2]-x, 2) + pow((float)sim->player.legs[3]-y, 2))<=
			   (pow((float)sim->player2.legs[2]-x, 2) + pow((float)sim->player2.legs[3]-y, 2)))
			{
				tarx = (int)sim->player.legs[2];
				tary = (int)sim->player.legs[3];
			}
			else
			{
				tarx = (int)sim->player2.legs[2];
				tary = (int)sim->player2.legs[3];
			}
			parts[i].tmp2 = 1;
		}
		else if (sim->player.spwn)
		{
			tarx = (int)sim->player.legs[2];
			tary = (int)sim->player.legs[3];
			parts[i].tmp2 = 1;
		}
	}
	int offx, offy;
	float dist;
	if (parts[i].tmp2 != 0)
	{
		offx = tarx-x;
		offy = tary-y;
		dist = sqrt(offx*offx + offy*offy);
		if (dist > 100)
		{
			if (offx < -50)
			{
				figh->comm = 0x01;
			}
			else if (offx > 50)
			{
				figh->comm = 0x02;
			}
			if (offy < 50)
			{
				figh->comm = (int)figh->comm | 0x04;
			}
		}
		else
		{
			if (RNG::Ref().chance(1, 30))
				figh->comm = (int)figh->comm ^ 0x01;
			if (RNG::Ref().chance(1, 30))
				figh->comm = (int)figh->comm ^ 0x02;
			if (RNG::Ref().chance(1, 30))
				figh->comm = (int)figh->comm ^ 0x04;
		}
		if (dist > 25)
		{
			figh->aimx = (float)offx/dist;
			figh->aimy = (float)offy/dist;
		}
		if (RNG::Ref().chance(1, 30))
		{
			figh->aiaimed = !figh->aiaimed;
		}
		figh->aim = figh->aiaimed;
		
	}
	else
	{
		figh->comm = 0;
		figh->aiaimed = false;
		
	}

	figh->pcomm = figh->comm;
	
	//hacky solution for figh ai compatibility; just swap out values and put them back afterwards.
	int hackyswap;
	hackyswap = figh->swaptmp;
	figh->swaptmp = parts[i].tmp;
	parts[i].tmp = hackyswap;
	
	hackyswap = figh->swaptmp2;
	figh->swaptmp2 = parts[i].tmp2;
	parts[i].tmp2 = hackyswap;
	
	
	Element_STKM_run_stickman(figh, UPDATE_FUNC_SUBCALL_ARGS);
	
	
	hackyswap = figh->swaptmp;
	figh->swaptmp = parts[i].tmp;
	parts[i].tmp = hackyswap;
	
	hackyswap = figh->swaptmp2;
	figh->swaptmp2 = parts[i].tmp2;
	parts[i].tmp2 = hackyswap;
	
	return 0;
}

static bool createAllowed(ELEMENT_CREATE_ALLOWED_FUNC_ARGS)
{
	return Element_FIGH_CanAlloc(sim);
}

static void changeType(ELEMENT_CHANGETYPE_FUNC_ARGS)
{
	if (to == PT_FIGH)
	{
		sim->parts[i].tmp = Element_FIGH_Alloc(sim);
		if (sim->parts[i].tmp >= 0)
			Element_FIGH_NewFighter(sim, sim->parts[i].tmp, i, PT_DUST);
	}
	else
	{
		Free(sim, (unsigned char)sim->parts[i].tmp);
	}
}

bool Element_FIGH_CanAlloc(Simulation *sim)
{
	return sim->fighcount < MAX_FIGHTERS;
}

int Element_FIGH_Alloc(Simulation *sim)
{
	if (sim->fighcount >= MAX_FIGHTERS)
		return -1;
	int i = 0;
	while (i < MAX_FIGHTERS && sim->fighters[i].spwn==1)
		i++;
	if (i < MAX_FIGHTERS)
	{
		sim->fighters[i].spwn = 1;
		sim->fighters[i].elem = PT_DUST;
		sim->fighcount++;
		return i;
	}
	else return -1;
}

static void Free(Simulation *sim, unsigned char i)
{
	if (sim->fighters[i].spwn)
	{
		sim->fighters[i].spwn = 0;
		sim->fighcount--;
	}
}

void Element_FIGH_NewFighter(Simulation *sim, int fighterID, int i, int elem)
{
	Element_STKM_init_legs(sim, &sim->fighters[fighterID], i);
	if (elem > 0 && elem < PT_NUM)
		sim->fighters[fighterID].elem = elem;
	sim->fighters[fighterID].spwn = 1;
}
