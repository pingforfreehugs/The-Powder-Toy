#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_FOAM()
{
	Identifier = "DEFAULT_PT_FOAM";
	Name = "FOAM";
	Colour = PIXPACK(0xD0D0D0);
	MenuVisible = 1;
	MenuSection = SC_LIQUID;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 5;

	DefaultProperties.temp = R_TEMP - 2.0f + 273.15f;
	HeatConduct = 29;
	Description = "Foam. Hardens into its CTYPE after some time.";

	Properties = TYPE_LIQUID|PROP_LIFE_DEC|PROP_NEUTPASS;

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
	if (parts[i].ctype <= 0)
	{
		parts[i].life = 100;
	}
	else
	{
		if (parts[i].life == 0)
		{
			sim->create_part(i,x,y,parts[i].ctype);
			return 1;
		}
	}
	if (parts[i].life < 15)
	{
		float slow = (parts[i].life + 4) / 20.0f;
		parts[i].vx = parts[i].vx * slow;
		parts[i].vy = parts[i].vy * slow;
	}
	int rx, ry, r, rt;
	if (parts[i].life < 20)
		for (rx=-2; rx<3; rx++)
			for (ry=-2; ry<3; ry++)
				if (BOUNDS_CHECK && (rx || ry))
				{
					r = pmap[y+ry][x+rx];
					if (!r)
						continue;
					rt = TYP(r);
					if (rt == parts[i].ctype)
					{
						parts[i].vx += rx/3.0f;
						parts[i].vy += ry/3.0f;
					}
					else if (rt == PT_FOAM) // sqrt(parts[i].vx*parts[i].vx + parts[i].vy*parts[i].vy) < 2
					{
						parts[i].vx += rx/10.0f;
						parts[i].vy += ry/10.0f;
						parts[ID(r)].vx -= rx/10.0f;
						parts[ID(r)].vy -= ry/10.0f;
					}
				}
	
	return 0;
}