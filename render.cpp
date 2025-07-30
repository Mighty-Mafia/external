#include <Render/Render.h>
#include <dwmapi.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam)) {
		return true;
	}

	switch (msg) {
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) {
			return 0;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_CLOSE:
		return 0;
	}

	return DefWindowProcA(hwnd, msg, wParam, lParam);
}

bool Render::creatDevice() {
	DXGI_SWAP_CHAIN_DESC swapChainDescription;
	ZeroMemory(&swapChainDescription, sizeof(swapChainDescription));

	swapChainDescription.BufferCount = 4;

	swapChainDescription.BufferDesc.Width = 0;
	swapChainDescription.BufferDesc.Height = 0;
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	swapChainDescription.OutputWindow = overlayWindow;

	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDescription.Windowed = 1;

	swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	swapChainDescription.SampleDesc.Count = 1;
	swapChainDescription.SampleDesc.Quality = 0;

	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	D3D_FEATURE_LEVEL featureLevel;
	D3D_FEATURE_LEVEL featureLevelList[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featureLevelList,
		2,
		D3D11_SDK_VERSION,
		&swapChainDescription,
		&swapChain,
		&device,
		&featureLevel,
		&deviceContext
	);

	if (result == DXGI_ERROR_UNSUPPORTED) {
		result = D3D11CreateDeviceAndSwapChain(
		nullptr,
			D3D_DRIVER_TYPE_WARP,
			nullptr,
			0,
			featureLevelList,
			2,
			D3D11_SDK_VERSION,
			&swapChainDescription,
			&swapChain,
			&device,
			&featureLevel,
			&deviceContext
		);
	}

	if (result != S_OK) {
		MessageBoxA(nullptr, "This software can not run on your system, you are entitled to a refund.", "Critical Problem", MB_OK | MB_ICONERROR);
	}

	ID3D11Texture2D* backBuffer{ nullptr };
	swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	if (backBuffer) {
		device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);
		backBuffer->Release();

		return true;
	}

	return false;
}

bool Render::createWindow(cstr WindowName) {
	overlayClass.cbSize = sizeof(overlayClass);
	overlayClass.style = CS_CLASSDC;
	overlayClass.lpszClassName = "Donatra Cheats";
	overlayClass.hInstance = GetModuleHandleA(0);
	overlayClass.lpfnWndProc = windowProcedure;

	RegisterClassEx(&overlayClass);

	overlayWindow = CreateWindowEx(
		WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
		overlayClass.lpszClassName,
		"Dnastra Cheats",
		WS_POPUP,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		0,
		0,
		overlayClass.hInstance,
		0
	);

	if (!overlayWindow) {
		MessageBoxA(nullptr, "Failed to create overlay window.", "Error", MB_ICONWARNING | MB_OK);
	}

	SetLayeredWindowAttributes(overlayWindow, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);

	RECT clientArea{};
	RECT windowArea{};

	GetClientRect(overlayWindow, &clientArea);
	GetWindowRect(overlayWindow, &windowArea);

	POINT diff{};
	ClientToScreen(overlayWindow, &diff);

	MARGINS margins{
		windowArea.left + (diff.x - windowArea.left),
		windowArea.top + (diff.y - windowArea.top),
		windowArea.right,
		windowArea.bottom,
	};

	DwmExtendFrameIntoClientArea(overlayWindow, &margins);

	ShowWindow(overlayWindow, SW_SHOW);
	UpdateWindow(overlayWindow);

	return true;
}

bool Render::createImGui() {
	using namespace ImGui;

	CreateContext();
	StyleColorsDark();

	if (!ImGui_ImplWin32_Init(overlayWindow)) {
		return false;
	}

	if (!ImGui_ImplDX11_Init(device, deviceContext)) {
		return false;
	}
}

void Render::destroyDevice() {
	if (device) {
		device->Release();
		deviceContext->Release();
		swapChain->Release();
		renderTargetView->Release();
	}
}

void Render::destroyWindow() {
	DestroyWindow(overlayWindow);
	UnregisterClassA(overlayClass.lpszClassName, overlayClass.hInstance);
}

void Render::destroyImGui() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
}

Render::~Render() {
	destroyImGui();
	destroyDevice();
	destroyWindow();
}

void Render::setupOverlay(cstr windowName) {
	createWindow(windowName);
	creatDevice();
	createImGui();
}

void Render::startRender() {
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		shouldShow = !shouldShow;

		if (shouldShow) {
			SetWindowLong(overlayWindow, GWL_EXSTYLE, WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT);
		} 
		else {
			SetWindowLong(overlayWindow, GWL_EXSTYLE, WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_LAYERED);

		}
	}
}

void Render::endRender() {
	ImGui::Render();

	float clearColor[4] = { 0, 0, 0, 0 };
	deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
	deviceContext->ClearRenderTargetView(renderTargetView, clearColor);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	swapChain->Present(1, 0);
}

void Render::renderMenu() {
	using namespace ImGui;

	SetNextWindowSize({500, 500});
	Begin("Donastra Cheats", &shouldRun, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
	Text("Donastra Loaded");
	End();
}
