#pragma once

#include <iostream>

#include "game_window.hpp"
#include "singleton.hpp"

class Game : public Singleton {
   public:
	static Game& GetInstance() {
		static Game instance;
		return instance;
	}

    void Init();
    void Run();
    void Stop();

    GameWindow *GetWindow() const;

    bool IsRunning() const;

   private:
	Game() {}

    GameWindow *window;
};
