//
// Created by Zoe Roux on 5/24/21.
//

#include <Wal.hpp>
#include <iostream>
#include "Runner.hpp"
#include "Models/GameState.hpp"

namespace BBM
{
	void updateState(WAL::Wal &engine, GameState &state)
	{
		// You can change the scene here or update the game state based on entities values.

		// If you want to keep a scene loaded but not running, store it in the state.loadedScenes.
		//      If you don't need the scene anymore, remember to remove it from the loadedScene array.
	}

	int run()
	{
		WAL::Wal wal;

		try {
			wal.run<GameState>(updateState);
			return 0;
		} catch (const std::exception &ex) {
			std::cerr << ex.what() << std::endl;
			return 1;
		}
	}
}