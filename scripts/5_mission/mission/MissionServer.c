modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		Print("[ZenVirus] OnInit");

		// Load config & check for static microscopes
		GetZenVirusConfig();
		if (GetGame().IsDedicatedServer())
		{
			if (GetZenVirusConfig().StaticMicroscopes.Count() > 0)
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SpawnStaticMicroscopes, 5000, false);
		}
	}

	void SpawnStaticMicroscopes()
	{
		Print("[ZenVirus] Microscope Count = " + GetZenVirusConfig().StaticMicroscopes.Count());

		for (int i = 0; i < GetZenVirusConfig().StaticMicroscopes.Count(); i++)
		{
			ZenMicroscope microscopeConfig = GetZenVirusConfig().StaticMicroscopes.Get(i);

			if (microscopeConfig.Location != "0 0 0")
			{
				// Check for an existing microscope
				bool foundExistingMicroscope = false;
				array<Object> objectsNearSpawn = new array<Object>;
				GetGame().GetObjectsAtPosition(microscopeConfig.Location, 0.1, objectsNearSpawn, null);

				// Scan objects
				for (int x = 0; x < objectsNearSpawn.Count(); x++)
				{
					Object obj = objectsNearSpawn.Get(x);
					if (obj && obj.GetType() == "Zen_Virus_Cure_Microscope_Static")
					{
						Print("[ZenVirus] Found existing Microscope @ " + obj.GetPosition());
						foundExistingMicroscope = true;
						break;
					}
				}

				if (!foundExistingMicroscope)
				{
					// Spawn a new microscope
					Object microscope = GetGame().CreateObjectEx("Zen_Virus_Cure_Microscope_Static", microscopeConfig.Location, ECE_PLACE_ON_SURFACE);
					microscope.SetOrientation(microscopeConfig.Orientation);
					Print("[ZenVirus] Spawned new Microscope @ " + microscope.GetPosition());
				}
			}
		}
	}
}