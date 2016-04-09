// spells.EXS ExplorSCRIPT for monsters.
// This is not the completed spell script it is only an example of what one might look
// like

// lighting is a damage doing spell it does 50 to 60 damage on up to 3 enemies at a time
// is does air damage so if victim is resistant to air propability of it having effect
// is decreased.

lightning
{
   type=damage
   damage=50 to 60
   numattackable=3
   typedamage=air
}

// Enchant is a water spell that effects statistics.  It drains the accuracy for the
// remainder of the battle.  One resistant to water damage is likely to dodge this

enchant
{
   type=effectstats
   numattackable=1
   effect=tempaccdrain
   typedamage=water
}