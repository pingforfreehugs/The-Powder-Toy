#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_PROJ()
{
	Identifier = "DEFAULT_PT_PROJ";
	Name = "PROJ";
	Colour = PIXPACK(0x999999);
	MenuVisible = 1;
	MenuSection = SC_SPECIAL;
	Enabled = 1;

	Advection = 0.2f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.99f;
	Collision = 0.0f;
	Gravity = 0.2f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 30;

	DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	DefaultProperties.life = 3;
	HeatConduct = 0;
	Description = "Projectile. Turns into its CTYPE when it stops moving.";

	Properties = TYPE_PART|PROP_LIFE_DEC ; 

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	int dist = sqrt(parts[i].vx*parts[i].vx + parts[i].vy*parts[i].vy);
	if (dist < 2 && parts[i].life == 0)
	{
		if (parts[i].ctype == PT_DRAY)
		{
			sim->create_part(i,x,y,PT_EXOT);
			parts[i].life = 9999;
			parts[i].tmp = 9999;
		}
		else
			sim->create_part(i,x,y,parts[i].ctype);
		return 1;
	}
	int re;
	if (parts[i].life < 3)
		for (re=dist/3; re<dist; re+=1)
		{
			int embx = x - parts[i].vx*(re)/dist;
			int emby = y - parts[i].vy*(re)/dist;
			int r = pmap[emby][embx];
			if (!r)
			{
				int emb = sim->create_part(-1,embx,emby,PT_EMBR);
				if (emb<0)
					continue;
				parts[emb].ctype = sim->elements[parts[i].ctype].Colour;
				parts[emb].life = 5;
				parts[emb].vx = parts[i].vx/2;
				parts[emb].vy = parts[i].vy/2;
				parts[emb].temp = sim->elements[parts[i].ctype].DefaultProperties.temp;
			}
		}
	return 0;
}
