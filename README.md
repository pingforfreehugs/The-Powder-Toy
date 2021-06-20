BoringPowder
=============
A mod with improvements for the STKM.

### DTEC element setting
 - Stickmen no longer set their element to any valid element they bump into.
 - Stickmen instead will set their element whenever they collide with DTEC, to the DTEC's CTYPE.
 - Stickmen will also copy the TMP value of DTEC.

### TMP properties
 - You can give stickmen special properties by altering their TMP property. To get the combination of flags you want, simply add up their numbers and set the stickman's TMP to the sum.
#### Ammo
+1: Fired particles will come from an ammo supply represented by TMP2, instead of coming from an infinite supply. Ammo caps at 300 particles. Replenish ammo by absorbing it through your head, or by touching DTEC.
#### Igniter Particles
These mutually-exclusive settings turn 20% of fired particles into "igniter" particles. Particularly useful for shooting flammable stuff.  
+2: Igniter particles are FIRE.  
+4: Igniter particles are LAVA.  
+6: Igniter particles are burning BCOL.  
#### Heat Immunity
These settings make stickmen more resistant to damage from hot particles.  
+8: Increases the temperature needed to take damage by 300C.  
+16: Complete immunity to heat damage.  

### FOAM element
 - New liquid: FOAM.
 - Sticks to its CTYPE.
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

### Minor stuff
 - Air control: Stickmen have control of their horizontal velocity while midair.
 - Velocity based aiming: Spawned particles inherit three times the stickman's velocity, letting you have some degree of control over where you shoot particles.
 - Gas boost: Firing gas particles also creates wind, since otherwise they barely fly an inch forward.
 - Special FIRW interaction: Shot fireworks will be lit, and explode after a short distance.
 - Special ARAY interaction: Shoots projectiles which turn into BRAY on hit.
 - Special CRAY interaction: Shoots projectiles which turn into BOMB on hit.
 - Special DRAY interaction: Shoots projectiles which duplicate whatever element they hit.
