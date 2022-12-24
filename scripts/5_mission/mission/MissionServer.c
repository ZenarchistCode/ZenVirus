modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		Print("[ZenVirus] OnInit");
		
		// Load config & check for static microscopes
		if (GetZenVirusConfig().StaticMicroscopes.Count() > 0)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SpawnStaticMicroscopes, 10000, false);
		}
	}

	void SpawnStaticMicroscopes()
	{
		for (int i = 0; i < GetZenVirusConfig().StaticMicroscopes.Count(); i++)
		{
			ZenMicroscope microscopeConfig = GetZenVirusConfig().StaticMicroscopes.Get(i);

			if (microscopeConfig.Location != "0 0 0")
			{
				// Check for an existing microscope
				bool foundExistingMicroscope = false;
				array<Object> objectsNearSpawn = new array<Object>;
				GetGame().GetObjectsAtPosition(microscopeConfig.Location, 0.1, objectsNearSpawn, null);
				Object obj;
				for (i = 0; i < objectsNearSpawn.Count(); i++)
				{
					obj = objectsNearSpawn.Get(i);
					if (obj && obj.GetType() == "Zen_Virus_Cure_Microscope_Static")
						foundExistingMicroscope = true;
				}

				if (!foundExistingMicroscope)
				{
					// Spawn a new microscope
					EntityAI microscope = EntityAI.Cast(SpawnMicroscope(microscopeConfig.Location, microscopeConfig.Orientation));
				}
			}
		}
	}

	// Spawn an object and apply appropriate flags/physics updates
	static Object SpawnMicroscope(vector position, vector orientation, float scale = 1.0)
	{
		Object obj = GetGame().CreateObjectEx("Zen_Virus_Cure_Microscope_Static", position, ECE_SETUP | ECE_UPDATEPATHGRAPH | ECE_CREATEPHYSICS);
		if (!obj)
		{
			Error("Failed to create object Zen_Virus_Cure_Microscope_Static");
			return NULL;
		}

		obj.SetPosition(position);
		obj.SetOrientation(orientation);
		obj.SetScale(scale);
		obj.Update();
		obj.SetAffectPathgraph(true, false);

		if (obj.CanAffectPathgraph())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
		}

		return obj;
	}
}