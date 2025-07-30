#pragma once
#include <d3d11.h>
#include <dxgi.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

class Render {
private:
	HWND overlayWindow;
	WNDCLASSEX overlayClass;

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	ID3D11RenderTargetView* renderTargetView;
	IDXGISwapChain* swapChain;

	bool creatDevice();
	bool createWindow(cstr WindowName);
	bool createImGui();

	void destroyDevice();
	void destroyWindow();
	void destroyImGui();
public:
	Render() = default;
	~Render();

	bool shouldRun = true;
	bool shouldShow = true;

	void setupOverlay(cstr windownName);

	void startRender();
	void renderMenu();
	void endRender();
};
