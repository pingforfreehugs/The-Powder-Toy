#include "simulation/ToolCommon.h"

#include "common/tpt-rand.h"
#include <cmath>

static int perform(Simulation * sim, Particle * cpart, int x, int y, int brushX, int brushY, float strength);

void SimTool::Tool_FTTD()
{
	Identifier = "DEFAULT_TOOL_FTTD";
	Name = "FTTD";
	Colour = PIXPACK(0xA00000);
	Description = "Fight-to-the-death. Use on two fighters to make them fight eachother.";
	Perform = &perform;
}

static int perform(Simulation * sim, Particle * cpart, int x, int y, int brushX, int brushY, float strength)
{
	if (!cpart)
		return 0;
	else if (cpart->type == PT_FIGH)
	{
		playerst* figh1 = &sim->fighters[(unsigned char)cpart->tmp];
		if (!sim->fttd_selected)
		{
			sim->fttd_last_id = cpart->tmp;
			sim->fttd_selected = true;
			return 1;
		}
		else if (sim->fttd_last_id == cpart->tmp)
		{
			return 0;
		}
		else
		{
			figh1->aitarget = sim->fttd_last_id;
			figh1->aifttd = true;
			sim->fighters[sim->fttd_last_id].aitarget = cpart->tmp;
			sim->fighters[sim->fttd_last_id].aifttd = true;
			sim->fttd_selected = false;
			return 1;
		}
	}
	else
		return 0;
}
