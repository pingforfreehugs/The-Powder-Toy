BoringPowder
=============
A mod with improvements for the STKM.

### DTEC element setting
 - Stickmen no longer set their element to any valid element they bump into.
 - Stickmen instead will set their element whenever they collide with DTEC, to the DTEC's CTYPE.
 - Stickmen will also copy the TMP value of DTEC.

### TMP properties
 - You can give stickmen special properties by altering their TMP property. To get the combination of flags you want, simply add up their numbers and set the stickman's TMP to the sum.
> -=- Ammo -=-
This setting makes stickmen use a limited supply of ammo when firing. Ammo is represented by TMP2 and is capped at 300. Replenish ammo by absorbing it through your head, or by touching DTEC.
+1: Enable limited ammo supply.
> -=- Igniter Particles -=-
These mutually-exclusive settings turn 20% of fired particles into "igniter" particles. Particularly useful for shooting flammable stuff.  
+2: Igniter particles are FIRE.  
+4: Igniter particles are LAVA.  
+6: Igniter particles are burning BCOL.  
> -=- Heat Immunity -=-
These mutually-exclusive settings make stickmen more resistant to damage from hot particles.  
+8: Increases the temperature needed to take damage by 300C.  
+16: Complete immunity to heat damage.  
> -=- Miscellaneous Immunities -=-
These settings make stickmen immune to damage from specific damage sources. These properties are NOT mutually-exclusive; they can be used together.
+24: Immunity to damage from cold things.
+48: Immunity to damage from toxic elements and from SPRK.
+96: Immunity to damage from high pressure.
> -=- Invincibility -=-
This setting locks a stickman's life at 100%. They can still be killed by things like the erase tool and VOID.
+192: Invincibility.


### FOAM element
 - New liquid: FOAM.
 - Clumps together.
 - Hardens into its CTYPE after a short amount of time.
 - STKM can now fire solids; they will shoot foam with ctype set to the solid, it will harden some distance away.

### CROS tool
 - New tool: CROS.
 - Crosshairs for STKM; click to make them fire at the cursor!
 - Currently doesn't do anything for STK2 or FIGH.

### PROJ element
 - New elemnt: PROJ.
 - Projectiles. Leave a trail of embers as they fly; turn into their CTYPE when they stop moving.
 - Used for certain special STKM element setting interations.

### FIGH AI improvements
 - Fighters have a reworked AI.
 - The new AI is simple but spastic, consisting of mostly randomized inputs.
 - Fighters will also use 360 degree aim to fire directly at their target, much like STKM can with CROS.

### FTTD tool
 - New tool: FTTD.
 - Fight-To-The-Death; use on two fighters to make them fight eachother.

### Minor stuff
 - Air control: Stickmen have control of their horizontal velocity while midair.
 - Health bars: Stickmen have health bars above their heads.
 - Velocity based aiming: Spawned particles inherit three times the stickman's velocity, letting you have some degree of control over where you shoot particles.
 - Gas boost: Firing gas particles also creates wind, since otherwise they barely fly an inch forward.
 - Special FIRW interaction: Shot fireworks will be lit, and explode after a short distance.
 - Special ARAY interaction: Shoots projectiles which turn into BRAY on hit.
 - Special CRAY interaction: Shoots projectiles which turn into BOMB on hit.
 - Special DRAY interaction: "Dupe ray", shoots projectiles which duplicate whatever element they hit.
 - Special FRAY interaction: "Freeze ray", shoots very cold projectiles.
