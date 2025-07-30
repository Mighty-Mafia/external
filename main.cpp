#include <SDK/Cache.h>
#include <SDK/Offsets.h>

#include <Cheats/Players.h>

auto main(i32 argc, i8** argv) -> i32 {
	printf("[+] Welcome to Donastra Cheats.\n");

	if (!Comms->is_connected()) {
		printf("[-] Failed to connect to the Driver.\n");
		sleep_ms(5000);
		exit(0);
	}

	printf("[+] Connected to the driver successfully.\n");

	printf("[+] Looking for roblox process.\n");

	while (Comms->find_process("RobloxPlayerBeta.exe") == 0) {
		sleep_ms(100);
	}

	//Comms->process_handle = Comms->v_attach(Comms->process_id);

	printf("[+] Found RobloxPlayerBeta.exe with procces ID: %d\n", Comms->process_id);

	if (Comms->find_image() == 0) {
		printf("[-] Failed to get the base address.\n ");
		sleep_ms(5000);
		exit(0);
	}

	printf("[+] Found RobloxPlayerBeta.exe with base address: 0x%llx", Comms->image_address);

	// Getting DataModel

	u64 FakeDataModel = Comms->read<u64>(Comms->image_address + Offsets::FakeDataModel);
	dataModel = std::make_unique<RBX::DataModel>(Comms->read<u64>(FakeDataModel + Offsets::RealDataModel));

	printf("DataModel -> 0x%llx\n", dataModel->getAddress());

	visualEngine = std::make_unique<RBX::VisualEngine>(Comms->read<u64>(Comms->image_address + Offsets::VisualEngine));

	printf("VisEngine -> 0x%llx\n", visualEngine->getAddress());

		render = std::make_unique<Render>();

		render->setupOverlay("Donastra Cheats");

		std::thread(updatePlayers).detach();

		while (render->shouldRun) {
			render->startRender();

			if (render->shouldShow) {
				render->renderMenu();
			}

			render->endRender();
		}
}
