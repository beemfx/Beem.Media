// monster.EXS ExplorSCRIPT for monsters.
// This is not the completed monster script it is only an example of what one might look
// like

// The goblin is a fairly weak creature it's only move is to attack
Goblin
{
   image="goblin.bmp"
   attackchance=100%
   armor=3
   accuracy=20
   health=14
   damage=3 to 10
}

// The seductress is a tougher creature.  It has a 75% chance to attack and a 25%
// chance to cast a spell.  If it casts a spell it has a 90% chance to cast lighting
// and 10% to cast enchant

Seductress
{
   image="seductress.bmp"
   attackchance=75%
   spellchance=25%
   armor=20
   accuracy=65
   health=200
   damage=20 to 100
   spells
   {
      enchant=10%
      lightning=90%
   }
}