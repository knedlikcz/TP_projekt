
#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <string>
#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace QuickSDL {
	class Graphics {

	public:


		const int SCREEN_WIDTH = 1024;
		const int SCREEN_HEIGHT = 896;
		const char* WINDOW_TITLE = "Galaga";

	private:
		static Graphics* sInstance;
		static bool sInitialized;

		SDL_Window* mWindow;

		SDL_Renderer* mRenderer;

	public:
		static Graphics* Instance();
		static void Release();
		static bool Initialized();

		SDL_Texture* LoadTexture(std::string path);

		SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

		void ClearBackBuffer();

		void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void DrawLine(float startX, float startY, float endX, float endY);

		void Render();

	private:

		Graphics();
		~Graphics();

		bool Init();
	};
}
#endif
