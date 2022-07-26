modded class ZombieBase
{
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (ammo == "Arrow_Bolt_Virus")
			this.SetHealth(this.GetHealth() - 120);
	}
}

modded class AnimalBase
{
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (ammo == "Arrow_Bolt_Virus")
			this.SetHealth(this.GetHealth() - 120);
	}
}