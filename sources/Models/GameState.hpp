//
// Created by Zoe Roux on 5/24/21.
//


#pragma once

#include <unordered_map>
#include <Scene/Scene.hpp>


namespace BBM
{
	//! @brief A class representing the current game state. This allow one to retain information between update calls.
	class GameState
	{
		public:
		//! @brief The list of scenes available.
		enum SceneID
		{
			MainMenuScene,
			GameScene,
			SettingsScene,
			PauseMenuScene,
			LobbyScene,
			TitleScreenScene,
		};


		//! @brief The currently loaded scene
		SceneID currentScene = TitleScreenScene;

		//! @brief The next scene to load (if smae as currentScene, nothing to do)
		SceneID nextScene = TitleScreenScene;

		//! @brief The list of loaded scenes.
		std::unordered_map<SceneID, std::shared_ptr<WAL::Scene>> _loadedScenes = {};
	};
}