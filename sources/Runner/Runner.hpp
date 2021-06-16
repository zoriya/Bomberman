//
// Created by Zoe Roux on 5/24/21.
//

#pragma once
#include "Models/GameState.hpp"
#include "Wal.hpp"

namespace BBM
{
	class Runner {
		public:

		//! @brief the width of the map
		static int mapWidth;
		//! @brief the height of the map
		static int mapHeight;

		static int addedPlayer;

		//! @brief store current scenes informations
		static GameState gameState;
		//! @brief Start the game and run a Bomberman.
		//! @return 0 on success, another value on error.
		static int run();

		//! @brief Update current scene (loading related data) according to state
		//! @param engine: Wal ECS
		//! @param state current game state
		static void updateState(WAL::Wal &engine, GameState &state);
		
		//! @brief Add required systems to wal
		static void addSystems(WAL::Wal &wal);

		//! @brief init all raylib-related data & context
		static void enableRaylib(WAL::Wal &wal);

		static void addMenuControl(WAL::Scene &scene);

		//! @brief load all data related to title screen
		static std::shared_ptr<WAL::Scene> loadTitleScreenScene();

		//! @brief load all data related to main menu screen
		static std::shared_ptr<WAL::Scene> loadMainMenuScene();

		//! @brief load all data related to pause menu screen
		static std::shared_ptr<WAL::Scene> loadPauseMenuScene();

		//! @brief load all data related to settings screen
		static std::shared_ptr<WAL::Scene> loadSettingsMenuScene();

		//! @brief load all data related to game screen
		static std::shared_ptr<WAL::Scene> loadGameScene();

		//! @brief load all data related to credit screen
		static std::shared_ptr<WAL::Scene> loadCreditScene();

		//! @brief load all data related to lobby screen
		static std::shared_ptr<WAL::Scene> loadLobbyScene();

		//! @brief load all data related to resume lobby screen
		static std::shared_ptr<WAL::Scene> loadResumeLobbyScene();

		//! @brief Create a player (without any controllable) and add it to the scene.
		//! @param scene The scene where to player should reside.
		//! @return A reference to the created player.
		static WAL::Entity &createPlayer(WAL::Scene &scene);

		//! @brief load all data related to splash screen
		static std::shared_ptr<WAL::Scene> loadSplashScreenScene();

		//! @brief loads all scenes in the game state
		static void loadScenes();
	};
}