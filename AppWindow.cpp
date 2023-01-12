#include "AppWindow.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdlrenderer.h"
#include "imgui_impl_sdl.h"

AppWindow::AppWindow(SDL_Point windowSize):
	_windowSize(windowSize),
	_clearColor(SDL_Color(10, 10, 10, 255)),
	_frameTime(1000 / 60.f)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL init falure\n";
		return;
	}

	_window = SDL_CreateWindow("Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowSize.x,
		windowSize.y,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
	if (!_window)
	{
		std::cout << "Couldn't create window\n";
		return;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (!_renderer)
	{
		SDL_DestroyWindow(_window);
		std::cout << "Couldn't create renderer\n";
		return;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(_window, _renderer);
	ImGui_ImplSDLRenderer_Init(_renderer);
}

AppWindow::~AppWindow()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

void AppWindow::Show()
{
	SDL_ShowWindow(_window);
	_showing = true;
	
	while (_showing)
	{
		Uint64 frameTime = SDL_GetTicks();
		
		HandleEvents();
		
		BeginGuiFrame();
		RenderGui();
		EndGuiFrame();

		Clear();
        Render();
		Present();
		
		frameTime = SDL_GetTicks() - frameTime;
		if (frameTime < _frameTime)
			SDL_Delay(_frameTime - frameTime);
	}
}

void AppWindow::BeginGuiFrame()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void AppWindow::EndGuiFrame()
{
	ImGui::Render();
}

void AppWindow::Present()
{
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	SDL_RenderPresent(_renderer);
}

void AppWindow::Clear()
{
	SDL_SetRenderDrawColor(_renderer,
		_clearColor.r,
		_clearColor.g,
		_clearColor.b,
		_clearColor.a);
	SDL_RenderClear(_renderer);
}

void AppWindow::Render()
{
}

void AppWindow::RenderGui()
{
	ImGui::Begin("Window");
	ImGui::End();
}

void AppWindow::HandleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
		if (e.type == SDL_QUIT)
			Close();
		else
			ProcessEvent(e);
	}
}

void AppWindow::ProcessEvent(const SDL_Event& e)
{
	
}
