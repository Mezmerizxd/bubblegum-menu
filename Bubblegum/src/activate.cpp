#include "discord_register.hpp"
#include "discord_rpc.hpp"
#include <windows.h>

namespace DRP {
	void Start() {
		DiscordEventHandlers Handler;
		memset(&Handler, 0, sizeof(Handler));
		Discord_Initialize("#######################################", &Handler, 1, NULL);
	}
	void Update() {
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.state = "Example1";
		discordPresence.details = "Example2";
		discordPresence.startTimestamp = 1507665886;
		discordPresence.largeImageText = "Example3";
		discordPresence.smallImageText = "Example4";
		Discord_UpdatePresence(&discordPresence);
	}
}