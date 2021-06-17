//
// Created by hbenjamin on 10/06/2021.
//

#include <fstream>
#include <map>
#include <Component/Position/PositionComponent.hpp>
#include <Component/Timer/TimerComponent.hpp>
#include <Map/Map.hpp>
#include <Component/BombHolder/BombHolderComponent.hpp>
#include <sstream>
#include <Component/Keyboard/KeyboardComponent.hpp>
#include <Component/Shaders/ShaderComponent.hpp>
#include <Component/Animator/AnimatorComponent.hpp>
#include <Component/Tag/TagComponent.hpp>
#include <Component/Animation/AnimationsComponent.hpp>
#include <Component/Sound/SoundComponent.hpp>
#include <Component/Bonus/PlayerBonusComponent.hpp>
#include <Component/Music/MusicComponent.hpp>
#include <Items/Bonus.hpp>
#include <Exception/Error.hpp>
#include "ParserYaml.hpp"
#include <algorithm>
#include <Component/Levitate/LevitateComponent.hpp>
#include <Runner/Runner.hpp>
#include <cstring>
#include <sstream>
#include <Component/Gamepad/GamepadComponent.hpp>
#include <Component/Renderer/Drawable2DComponent.hpp>
#include <System/Lobby/LobbySystem.hpp>
#include <filesystem>
#include "Utils/Utils.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM {

	const std::string ParserYAML::fileName = "save";
	std::stringstream ParserYAML::_block("");
	std::stringstream ParserYAML::_bonus("");
	std::stringstream ParserYAML::_player("");
	std::vector<std::string> ParserYAML::playerName = {};
	std::vector<Vector3f> ParserYAML::playerPosition = {};
	std::vector<int> ParserYAML::playerBombCount = {};
	std::vector<float> ParserYAML::playerExplosionRange = {};
	std::vector<float> ParserYAML::playerSpeed = {};
	std::vector<std::string> ParserYAML::playerAssets = {};

	std::string ParserYAML::_getBlockType(std::string blockName)
	{
		static std::map<std::string, MapGenerator::BlockType> map {
			{"Upper Floor", MapGenerator::BlockType::UPPERFLOOR},
			{"Bumper Block", MapGenerator::BlockType::BUMPER},
			{"Breakable Block", MapGenerator::BlockType::BREAKABLE},
			{"Unbreakable Block", MapGenerator::BlockType::UNBREAKABLE},
			{"Hole Block", MapGenerator::BlockType::HOLE}
		};

		return (std::to_string(map.at(blockName)));
	}

	std::string ParserYAML::_getBonusType(std::string bonusName)
	{
		static std::map<std::string, Bonus::BonusType> map {
			{"Bonus Bomb Up", Bonus::BonusType::BOMBSTOCK},
			{"Bonus Speed Up", Bonus::BonusType::SPEEDUP},
			{"Bonus Fire Up", Bonus::BonusType::EXPLOSIONINC}
		};

		return (std::to_string(map.at(bonusName)));
	}

	void ParserYAML::_saveBonus(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto name = entity.getName();

		if (!position)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_bonus << std::endl << "  " << name << ":" << std::endl << "    ";
		_bonus << std::string("bonus_type: ") << _getBonusType(entity.getName()) << std::endl << "    ";
		_bonus << "position: [" << std::to_string(position->getX()) << "," << std::to_string(position->getY()) << "," << std::to_string(position->getZ()) << "]";
	}

	void ParserYAML::_savePlayer(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto *bombHolder = entity.tryGetComponent<BombHolderComponent>();
		auto *model = entity.tryGetComponent<Drawable3DComponent>();
		auto *controllable = entity.tryGetComponent<ControllableComponent>();
		auto name = entity.getName();

		if (!position || !bombHolder || !model || !controllable)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_player << std::endl << "  " << name << ":" << std::endl << "    ";
		_player << "texture_path: " << dynamic_cast<RAY3D::Model *>(model->drawable.get())->getTextureByMaterial(MAP_DIFFUSE).getResourcePath() << std::endl << "    ";
		_player << "max_bomb: " << std::to_string(bombHolder->maxBombCount) << std::endl << "    ";
		_player << "explosion_radius: " << std::to_string(bombHolder->explosionRadius) << std::endl << "    ";
		_player << "speed: " << std::to_string(controllable->speed) << std::endl << "    ";
		_player << "position: [" << std::to_string(position->getX()) << "," << std::to_string(position->getY()) << "," << std::to_string(position->getZ()) << "]";
	}

	void ParserYAML::_saveBlock(const WAL::Entity &entity)
	{
		auto *position = entity.tryGetComponent<PositionComponent>();
		auto name = entity.getName();

		if (!position)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_block << std::endl << "  " << name << ":" << std::endl << "    ";
		_block << std::string("block_type: ") << _getBlockType(entity.getName()) << std::endl << "    ";
		_block << "position: [" << std::to_string(position->getX()) << "," << std::to_string(position->getY()) << "," << std::to_string(position->getZ()) << "]";
	}

	void ParserYAML::save(std::shared_ptr<WAL::Scene> scene)
	{
		std::string block = std::string("save/" + fileName + "_block.yml");
		std::string player = std::string("save/" + fileName + "_player.yml");
		std::string bonus = std::string("save/" + fileName + "_bonus.yml");
		std::map<std::string, std::function<void (const WAL::Entity &)>> savingGame = {
				{"Bonus", &_saveBonus},
				{"Block", &_saveBlock},
				{"Upper Floor", &_saveBlock},
				{"Player", &_savePlayer}
		};
		std::ofstream blockFile(block);
		std::ofstream playerFile(player);
		std::ofstream bonusFile(bonus);

		_player << "players:";
		_bonus << "bonuses:";
		_block << "width: " << std::to_string(Runner::mapWidth);
		_block << std::endl << "height: " + std::to_string(Runner::mapHeight);
		_block << std::endl << "blocks:";
		for (const auto &entity : scene->getEntities()) {
			for (const auto& type : savingGame) {
				if (entity.getName().find(type.first) != std::string::npos) {
					type.second(entity);
				}
			}
		}
		blockFile << _block.str() << std::endl;
		playerFile << _player.str() << std::endl;
		bonusFile << _bonus.str() << std::endl;
		_block = std::stringstream();
		_player = std::stringstream();
		_bonus = std::stringstream();
	}

	void ParserYAML::_loadPlayer(std::shared_ptr<WAL::Scene> scene, Node &node, int countPlayer)
	{
		std::string tmpAssets = node.getProperty("texture_path");
		std::map<std::string, RAY::Color> map = {
				{"red", RED},
				{"blue", BLUE},
				{"yellow", YELLOW},
				{"green", GREEN}
		};

		playerName.push_back(node.getName());
		playerAssets.push_back(node.getProperty("texture_path"));
		playerBombCount.push_back(_parseMaxBomb(node.getProperty("max_bomb")));
		playerExplosionRange.push_back(_parseExplosionRadius(node.getProperty("explosion_radius")));
		playerSpeed.push_back(_parseSpeed(node.getProperty("speed")));
		playerPosition.push_back(_parsePosition(node.getProperty("position")));

		if ((tmpAssets.find("red.png") == std::string::npos && tmpAssets.find("blue.png") == std::string::npos &&
		tmpAssets.find("green.png") == std::string::npos && tmpAssets.find("yellow.png") == std::string::npos &&
		tmpAssets.find("ai.png") == std::string::npos) || !std::filesystem::exists(tmpAssets)) {
			throw (ParserError("Error with saved map: One asset is invalid.\n                Loading default maps..."));
		}
		auto start = tmpAssets.find_last_of("/") + 1;
		auto color = map.at(tmpAssets.substr(start, tmpAssets.length() - start - 4));
		auto resumeScene = Runner::gameState._loadedScenes[GameState::SceneID::ResumeLobbyScene];
		auto &playerTile = resumeScene->addEntity("player tile")
			.addComponent<PositionComponent>(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY2D::Rectangle>(RAY::Vector2(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3), RAY::Vector2(200, 200), color);
		auto &playerLogo = resumeScene->addEntity("player")
			.addComponent<PositionComponent>(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>(tmpAssets.replace(tmpAssets.find("textures"), 8, "icons"));
		auto &ready = resumeScene->addEntity("ready")
			.addComponent<PositionComponent>(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>();
		playerLogo.addComponent<LobbyComponent>(countPlayer, ready, playerTile);
	}

	void ParserYAML::_loadPlayers(std::shared_ptr<WAL::Scene> scene, Node &node)
	{
		int countPlayer = 0;
		auto childNode = node.getChildNodes("players")[0].getChildNodes();

		if (childNode.size() < 2)
			throw (ParserError("There isn't enough players to load this saved map."));
		for (auto child : childNode) {
			_loadPlayer(scene, child, countPlayer);
			countPlayer++;
		}
	}

	void ParserYAML::_loadBlock(std::shared_ptr<WAL::Scene> scene, Node child, MapGenerator::MapBlock &map)
	{
		Vector3f pos = _parsePosition(child.getProperty("position"));
		MapGenerator::BlockType blockType = _parseBlockType(child.getProperty("block_type"));

		if (blockType == MapGenerator::NOTHING)
			throw (ParserError("Invalid block_type field."));
		if (blockType == MapGenerator::HOLE)
			pos.y += 1.0f;
		map[std::make_tuple(pos.x, pos.y, pos.z)] = blockType;
	}

	void ParserYAML::_loadBlocks(std::shared_ptr<WAL::Scene> scene, Node &node)
	{
		MapGenerator::MapBlock map;
		int size = -1;

		if (!Utils::tryParseInteger(node.getProperty("width"), size)) {
			throw ParserError("width property must be an int");
		}
		Runner::mapWidth = size;
		if (!Utils::tryParseInteger(node.getProperty("height"), size)) {
			throw ParserError("width property must be an int");
		}
		Runner::mapHeight = size;

		for (int i = 0; i < Runner::mapWidth; i++)
			for (int j = 0; j < Runner::mapHeight; j++)
				map[std::make_tuple(i, 0, j)] = MapGenerator::NOTHING;
		auto childNode = node.getChildNodes("blocks")[0].getChildNodes();
		for (auto child : childNode)
			_loadBlock(scene, child, map);
		MapGenerator::loadMap(Runner::mapWidth, Runner::mapHeight, map, scene);
	}

	void ParserYAML::_loadBonus(std::shared_ptr<WAL::Scene> scene, Node &node)
	{
		auto &entity = scene->addEntity(node.getName());
		Vector3f pos = _parsePosition(node.getProperty("position"));
		Bonus::BonusType bonusType = _parseBonusType(node.getProperty("bonus_type"));

		if (bonusType == Bonus::NOTHING) {
			entity.scheduleDeletion();
			return;
		}
		MapGenerator::createBonus(entity, pos, bonusType);
	}

	void ParserYAML::_loadBonuses(std::shared_ptr<WAL::Scene> scene, Node &node)
	{
		auto childNode = node.getChildNodes("bonuses")[0].getChildNodes();
		for (auto child : childNode)
			_loadBonus(scene, child);
	}

	void ParserYAML::load(std::shared_ptr<WAL::Scene> gameScene)
	{
		Node blocksInfos = parseFile("save/save_block.yml");
		Node bonusesInfos = parseFile("save/save_bonus.yml");
		Node playerInfos = parseFile("save/save_player.yml");
		_loadBlocks(gameScene, blocksInfos);
		_loadBonuses(gameScene, bonusesInfos);
		_loadPlayers(gameScene, playerInfos);
	}

	Vector3f ParserYAML::_parsePosition(std::string line)
	{
		float x;
		float y;
		float z;
		std::string subStr;

		try {
			auto start = line.find("[", 0) + 1;
			subStr = line.substr(start, line.find("]", 0) - 1 - start);
			auto pos = Utils::splitStr(subStr, ',');
			if (pos.size() != 3)
				throw (ParserError("Error with saved map: Error parsing position.\n                Loading default maps..."));
			if (!Utils::tryParseFloat(pos[0], x) || !Utils::tryParseFloat(pos[1], y) || !Utils::tryParseFloat(pos[2], z))
				throw (ParserError("Error with saved map: Error parsing position.\n                Loading default maps..."));
		} catch (const std::out_of_range &err) {
			throw (ParserError("Error with saved map: Error parsing position.\n                Loading default maps..."));
		}
		return Vector3f(x, y, z);
	}

	int ParserYAML::_parseMaxBomb(std::string line)
	{
		int maxBomb = 0;

		if (line.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse max bomb.\n                Loading default maps..."));
		if (!Utils::tryParseInteger(line, maxBomb))
			throw (ParserError("Error with saved map: Couldn't parse max bomb.\n                Loading default maps..."));
		return (maxBomb);
	}

	int ParserYAML::_parseExplosionRadius(std::string line)
	{
		int explosionRadius = 0;

		if (line.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse explosion radius.\n                Loading default maps..."));
		if (!Utils::tryParseInteger(line, explosionRadius))
			throw (ParserError("Error with saved map: Couldn't parse explosion radius.\n                Loading default maps..."));
		return (explosionRadius);
	}

	float ParserYAML::_parseSpeed(std::string line)
	{
		float speed = 0;

		if (line.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse speed.\n                Loading default maps..."));
		if (!Utils::tryParseFloat(line, speed))
			throw (ParserError("Error with saved map: Couldn't parse speed.\n                Loading default maps..."));
		return (speed);
	}

	MapGenerator::BlockType ParserYAML::_parseBlockType(std::string blockType)
	{
		if (blockType.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse block type.\n                Loading default maps..."));
		int block = 0;
		if (!Utils::tryParseInteger(blockType, block))
			throw (ParserError("Error with saved map: Couldn't parse block type.\n                Loading default maps..."));
		return (static_cast<MapGenerator::BlockType>(block));
	}

	Bonus::BonusType ParserYAML::_parseBonusType(std::string bonusType)
	{
		if (bonusType.find("-") != std::string::npos)
			throw (ParserError("Error with saved map: Couldn't parse bonus type.\n                Loading default maps..."));
		int bonus = 0;
		if (!Utils::tryParseInteger(bonusType, bonus))
			throw (ParserError("Error with saved map: Couldn't parse bonus type.\n                Loading default maps..."));
		return (static_cast<Bonus::BonusType>(bonus));
	}

	std::string ParserYAML::parseHeader(const std::string &line)
	{
		std::stringstream ss(line);
		std::string headerName;
		std::string garbage;

		ss >> headerName >> garbage;


		if (!garbage.empty()) {
			throw ParserError("ill formed header, line: " + Utils::trimCopy(line));
		}
		if (headerName.back() != ':') {
			throw ParserError("header not ended with ':' , line: " + Utils::trimCopy(line));
		}
		headerName.pop_back();
		return headerName;
	}

	std::pair<std::string, std::string> ParserYAML::parseProperty(const std::string &line)
	{
		std::stringstream ss(line);
		std::string propertyName;
		std::string propertyValue;
		std::string garbage;

		ss >> propertyName >> propertyValue >> garbage;

		if (!garbage.empty()) {
			throw ParserError("ill formed property, line: " + Utils::trimCopy(line));
		}
		if (propertyName.back() != ':') {
			throw ParserError("property name not ended with ':' , line: " + Utils::trimCopy(line));
		}
		propertyName.pop_back();
		return std::make_pair(propertyName, propertyValue);
	}

	bool ParserYAML::isHeader(const std::string &line)
	{
		return line.back() == ':';
	}

	Node ParserYAML::parseFile(const std::string &path)
	{
		std::ifstream file(path);

		if (!file.good())
			throw ParserError("can't read file");
		return parseNode(file, "root");
	}

	Node ParserYAML::parseNode(std::ifstream &file, const std::string &nodeName, int indentLevel)
	{
		std::string line;
		Node node(nodeName);
#ifdef __linux__
		int endlNbChars = 1;
#elif _WIN32
		int endlNbChars = 2;
#endif

		while(std::getline(file, line)) {
			if (line.empty())
				continue;
			float lineIndentLevel = getIndent(line);
			if (lineIndentLevel != static_cast<int>(lineIndentLevel)) {
				throw ParserError("Yaml only support 2 spaces as indent");
			}
			if (lineIndentLevel > indentLevel) {
				throw ParserError("indent issue");
			}
			if (lineIndentLevel < indentLevel) {
				file.seekg(static_cast<size_t>(file.tellg()) - (line.length() + endlNbChars));
				return node;
			}
			if (isHeader(line)) {
				node.addChildNode(parseNode(file, parseHeader(line), indentLevel + 1));
			} else {
				node.setProperty(parseProperty(line));
			}
		}
		return node;
	}

	float ParserYAML::getIndent(const std::string &line)
	{
		int nb = 0;
		for (const auto &c : line) {
			if (!std::isspace(c))
				break;
			if (c != ' ')
				throw ParserError("Yaml only support 2 spaces as indent");
			nb++;
		}
		return static_cast<float>(nb / 2.);
	}
}