#pragma once
#pragma comment(lib, "bakkesmod.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"

class InstantReQ final : public BakkesMod::Plugin::BakkesModPlugin
{

	enum KEY {
		SPACE = 0x39,
		ESC = 0x01
	};


public:
	void onLoad() override;
	void onUnload() override;
	void pressKey(KEY key, int timesDone, int timesLeft) const;

private:
	void reQueue() const;
	void exitGame() const;
	void pluginEnabledChanged();
	void delayCheck();
	void hookMatchEnded();
	void unhookMatchEnded();
	void logHookType(const char *const hookType) const;

private:
	static constexpr const char *matchEndedEvent = "Function TAGame.GameEvent_Soccar_TA.EventMatchEnded";
	//static constexpr const char*menuLoaded = "Function TAGame.GFxData_MainMenu_TA.HandleTopMenuChange";
	static constexpr const char *menuLoadedEvent = "Function TAGame.MenuSequencer_TA.Tick";
	static constexpr const char *enabledCvarName = "instant_exit_enabled";
	static constexpr const char *delayCvarName = "instant_exit_delay";

private:
	bool hooked = false;
};