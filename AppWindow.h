#pragma once

#include <memory>
#include <SDL.h>

class AppWindow
{
public:
	AppWindow(SDL_Point windowSize);
	virtual ~AppWindow();
	
	void Show();
	virtual void Render();
	virtual void RenderGui();
	virtual void ProcessEvent(const SDL_Event& e);
	
	SDL_Renderer* GetRenderer() { return _renderer; }
	SDL_Point GetWindowSize() { return _windowSize; }
	
	unsigned GetFps() { return _fps; }
	void SetFps(unsigned fps) { _fps = fps; }
	
	void Close() { _showing = false; }
	
	void SetClearColor(SDL_Color color) { _clearColor = color; }
	
	
private:
	SDL_Point _windowSize;
	SDL_Window* _window{};
	SDL_Renderer* _renderer{};
	SDL_Color _clearColor;
	
	bool _showing = false;
	unsigned _fps = 60;
	Uint64 _frameTime;
	
	void BeginGuiFrame();
	void EndGuiFrame();
	void Present();
	void Clear();
	void HandleEvents();
};
