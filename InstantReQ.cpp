#include "InstantReQ.h"
#include "Windows.h"
#include <sstream>
#include "InputHandler.h"
BAKKESMOD_PLUGIN(InstantReQ, "Instant ReQueue", "1.0", PLUGINTYPE_FREEPLAY)

class InputHandler input;
//bool atMenu = false;

int randBetween(int low, int high) {
	return rand() % ((high - low) + 1) + low;
}

void InstantReQ::onLoad()
{
	cvarManager->registerCvar(enabledCvarName, "1", "Determines whether the InstantReQ plugin is enabled or disabled.").addOnValueChanged(std::bind(&InstantReQ::pluginEnabledChanged, this));
	cvarManager->registerCvar(delayCvarName, "0", "Wait X amount of seconds before exiting");
	hookMatchEnded();
}

void InstantReQ::onUnload()
{
}

void InstantReQ::pressKey(KEY key, int numDone, int numTarget) const {
	input.pressKey(key);
	std::stringstream logBuffer;
	logBuffer << "Pressed " << key;
	cvarManager->log(logBuffer.str());
	numDone++;
	if (numDone < numTarget)
		gameWrapper->SetTimeout(std::bind(&InstantReQ::pressKey, this, key, numDone, numTarget), 0.25f);
}

void InstantReQ::reQueue() const
{
	if (!gameWrapper->IsInGame()/* && !gameWrapper->IsInOnlineGame() && !gameWrapper->IsInCustomTraining()
	&& !gameWrapper->IsInFreeplay() && !gameWrapper->IsInReplay()
	&& !gameWrapper->IsSpectatingInOnlineGame()*/) {
		gameWrapper->SetTimeout(std::bind(&InstantReQ::pressKey, this, ESC, 0, 5), 0.5f);
		gameWrapper->SetTimeout(std::bind(&InstantReQ::pressKey, this, SPACE, 0, 3), 2.5f);
	} else {
		gameWrapper->SetTimeout(std::bind(&InstantReQ::reQueue, this), 1);
	}
	

	/*
	int x = randBetween(45, 340);
	int y = randBetween(550, 580);

	std::stringstream logBuffer;

	logBuffer = input.leftClick2(x, y);  // PLAY
	cvarManager->log(logBuffer.str());
	Sleep(100);

	logBuffer = input.leftClick2(randBetween(45, 345), randBetween(470, 495)); // PLAY ONLINE
	cvarManager->log(logBuffer.str());
	Sleep(100);

	logBuffer = input.leftClick2(randBetween(1165, 1490), randBetween(1490, 805)); // FIND MATCH
	cvarManager->log(logBuffer.str());
	Sleep(100);
	*/

	/*
	//POINT pos;
	//GetCursorPos(&pos);
	
	//logBuffer << "Clicked " << x << ", " << y;
	
	//Sleep(1000);
	
	*/
}

void InstantReQ::exitGame() const
{
	cvarManager->executeCommand("unreal_command disconnect");
	//gameWrapper->SetTimeout(std::bind(&InstantReQ::reQueue, this), 5);
	reQueue();
}

void InstantReQ::pluginEnabledChanged()
{
	const bool enabled = cvarManager->getCvar(enabledCvarName).getBoolValue();

	if (enabled)
	{
		if (!hooked)
		{
			hookMatchEnded();
		}
	}
	else
	{
		if (hooked)
		{
			unhookMatchEnded();
		}
	}
}

void InstantReQ::delayCheck()
{
	float exitDelayTime = cvarManager->getCvar(delayCvarName).getFloatValue();
	gameWrapper->SetTimeout(std::bind(&InstantReQ::exitGame, this), exitDelayTime);
}

void InstantReQ::hookMatchEnded()
{
	gameWrapper->HookEvent(matchEndedEvent, std::bind(&InstantReQ::delayCheck, this));
	hooked = true;
	logHookType("Hooked");
}

void InstantReQ::unhookMatchEnded()
{
	gameWrapper->UnhookEvent(matchEndedEvent);
	hooked = false;
	logHookType("Unhooked");
}

void InstantReQ::logHookType(const char *const hookType) const
{
	std::stringstream logBuffer;
	logBuffer << hookType << " match ended event.";
	cvarManager->log(logBuffer.str());
}
