class BloodVomit : EffectParticle
{
	void BloodVomit()
	{
		SetParticleID(ParticleList.BLOODVOMIT2);
	}
	override void Event_OnStarted()
	{
		// Uncomment this to spawn fake decal of vomit on ground.

		if (m_ParentObject)
		{
			vector Ppos = m_ParentObject.GetPosition();

			Particle p = Particle.Play(ParticleList.BLOODVOMITSPLASH, Ppos);

		}

	}
}