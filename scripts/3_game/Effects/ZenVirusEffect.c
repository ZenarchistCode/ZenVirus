class PPERequester_ZenVirusEffect extends PPERequester_GameplayBase
{
	protected ref array<float> m_OverlayColor;

	void ZV_SetEffectValues(float amount, float vig)
	{
		if (!IsRequesterRunning())
			Start();

		// Slowly change screen color to be more red, and add a vignette over time to give a tunnel vision effect
		autoptr array<float> m_OverlayColor = { amount * 2, 0.0, 0.0, 0.0 };
		SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_COLORIZATIONCOLOR, m_OverlayColor, PPEGlow.L_23_GLASSES, PPOperators.ADD);
		SetTargetValueFloat(PostProcessEffectType.Glow, PPEGlow.PARAM_VIGNETTE, false, vig, PPEGlow.L_25_SHOCK, PPOperators.ADD);
	}
}