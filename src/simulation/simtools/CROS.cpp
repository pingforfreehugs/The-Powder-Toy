#include "simulation/ToolCommon.h"

#include "common/tpt-rand.h"
#include <cmath>

static int perform(Simulation * sim, Particle * cpart, int x, int y, int brushX, int brushY, float strength);

void SimTool::Tool_CROS()
{
	Identifier = "DEFAULT_TOOL_CROS";
	Name = "CROS";
	Colour = PIXPACK(0xFF0000);
	Description = "Makes STKM shoot at it.";
	Perform = &perform;
}

static int perform(Simulation * sim, Particle * cpart, int x, int y, int brushX, int brushY, float strength)
{
	if (x == brushX && y == brushY && sim->player.spwn)
	{
		int xoff = brushX - (int)sim->player.legs[2];
		int yoff = brushY - (int)sim->player.legs[3];
		float aimdist = sqrt(xoff*xoff + yoff*yoff);
		if (aimdist > 0)
		{
			sim->player.aim = true;
			sim->player.aimx = xoff/aimdist;
			sim->player.aimy = yoff/aimdist;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}
