#pragma once
#include <Cheats/Players.h>

inline void espLoop() {
	while (true) {
		for (RBX::Player& player : g_PlayerList) {
			if (player.getAddress() == g_LocalPlayer.getAddress()) {
				continue;
			}

		RBX:RBX::ModelInstance character = player.getModelInstance();
			if (!character.getAddress()) {
				continue;
			}

			character.findFirstChild("Head");
		}

		sleep_ms(1);
	}
}
