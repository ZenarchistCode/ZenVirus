modded class PlayerBase
{
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (ammo == "Arrow_Bolt_Virus")
		{
			this.InsertAgent(VirusAgents.VIRUS, 1000);
		}
	}
};