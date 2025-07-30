#pragma once
#include <SDK/Offsets.h>
#include <SDK/Classes/DataModel/Player.h>

inline RBX::Instance g_LocalPlayer;
inline std::vector<RBX::Player> g_PlayerList;

void updatePlayers() {
	RBX::Instance playersService = dataModel->findFirstChild("Players");

	while (true) {
		g_LocalPlayer = RBX::Instance(Comms->read<u64>(playersService.getAddress() + Offsets::LocalPlayer));

		for (RBX::Instance& player : playersService.getChildren()) {
			if (!player.getAddress()) {
				continue;
			}

			g_PlayerList.push_back(RBX::Player(player.getAddress()));
		}

		sleep_ms(100);

		g_PlayerList.clear();
	}
}
