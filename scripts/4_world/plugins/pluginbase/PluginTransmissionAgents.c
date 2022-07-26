modded class PluginTransmissionAgents extends PluginBase
{
	void PluginTransmissionAgents()
	{
		m_AgentList.Insert(VirusAgents.VIRUS, new ZombieVirusAgent);
	}
};