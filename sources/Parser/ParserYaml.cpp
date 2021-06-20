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
#include "Component/Speed/SpeedComponent.hpp"
#include <algorithm>
#include <Component/Levitate/LevitateComponent.hpp>
#include <Runner/Runner.hpp>
#include <cstring>
#include <sstream>
#include <Component/Gamepad/GamepadComponent.hpp>
#include <Component/Renderer/Drawable2DComponent.hpp>
#include <System/Lobby/LobbySystem.hpp>
#include <filesystem>
#include <Component/Lobby/ResumeLobbyComponent.hpp>
#include "Utils/Utils.hpp"

namespace RAY3D = RAY::Drawables::Drawables3D;
namespace RAY2D = RAY::Drawables::Drawables2D;

namespace BBM {

	const std::string ParserYAML::fileName = "save";
	std::stringstream ParserYAML::_block("");
	std::stringstream ParserYAML::_bonus("");
	std::stringstream ParserYAML::_player("");
	std::vector<ParserYAML::PlayerInfos> ParserYAML::playersInfos = {};

	std::string ParserYAML::_getBlockType(const std::string& blockName)
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

	std::string ParserYAML::_getBonusType(const std::string& bonusName)
	{
		static std::map<std::string, Bonus::BonusType> map {
			{"Bonus Bomb Up", Bonus::BonusType::BOMBSTOCK},
			{"Bonus Speed Up", Bonus::BonusType::SPEEDUP},
			{"Bonus Fire Up", Bonus::BonusType::EXPLOSIONINC},
			{"Bonus Wallpass", Bonus::BonusType::NOCLIP}
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
		auto *speed = entity.tryGetComponent<SpeedComponent>();
		auto *controllable = entity.tryGetComponent<ControllableComponent>();
		auto name = entity.getName();

		if (!position || !bombHolder || !model || !speed)
			return;
		std::replace(name.begin(), name.end(), ' ', '_');
		_player << std::endl << "  " << name << ":" << std::endl << "    ";
		_player << "texture_path: " << dynamic_cast<RAY3D::Model *>(model->drawable.get())->getTextureByMaterial(MAP_DIFFUSE).getResourcePath() << std::endl << "    ";
		_player << "max_bomb: " << std::to_string(bombHolder->maxBombCount) << std::endl << "    ";
		_player << "explosion_radius: " << std::to_string(bombHolder->explosionRadius) << std::endl << "    ";
		_player << "speed: " << std::to_string(speed->speed) << std::endl << "    ";
		_player << "ia: " << (controllable->layout == ControllableComponent::AI ? "true" : "false") << std::endl << "    ";
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
		auto &ret = scene->view<TagComponent<Timer>, TimerComponent>();
		if (ret.size())
			_block << "timer: " << ret.front().get<TimerComponent>().ringIn.count();
		else
			_block << "timer: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::minutes(3)).count();

		_player << "players:";
		_bonus << "bonuses:";
		_block << std::endl << "width: " << std::to_string(Runner::mapWidth);
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
		std::map<std::string, int> colors = {
				{"red", 1},
				{"blue", 0},
				{"yellow", 3},
				{"green", 2}
		};


		playersInfos.emplace_back(PlayerInfos{
			node.getName(),
			_parsePosition(node.getProperty("position")),
			_parseMaxBomb(node.getProperty("max_bomb")),
			_parseExplosionRadius(node.getProperty("explosion_radius")),
			_parseSpeed(node.getProperty("speed")),
			node.getProperty("texture_path")
		});

		if ((tmpAssets.find("red.png") == std::string::npos && tmpAssets.find("blue.png") == std::string::npos &&
		tmpAssets.find("green.png") == std::string::npos && tmpAssets.find("yellow.png") == std::string::npos)
		|| !std::filesystem::exists(tmpAssets)) {
			throw (ParserError("One asset is invalid."));
		}
		auto start = tmpAssets.find_last_of('/') + 1;
		auto colorStr = tmpAssets.substr(start, tmpAssets.length() - start - 4);
		auto color = map.at(colorStr);
		auto resumeScene = Runner::gameState.loadedScenes[GameState::SceneID::ResumeLobbyScene];
		auto &playerTile = resumeScene->addEntity("player tile")
			.addComponent<PositionComponent>(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY2D::Rectangle>(RAY::Vector2(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3), RAY::Vector2(200, 200), color);
		auto &playerLogo = resumeScene->addEntity("player")
			.addComponent<PositionComponent>(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>(tmpAssets.replace(tmpAssets.find("textures"), 8, "icons"));
		auto &ready = resumeScene->addEntity("ready")
			.addComponent<PositionComponent>(224 * (countPlayer + 1) + 200 * countPlayer, 1080 / 3, 0)
			.addComponent<Drawable2DComponent, RAY::Texture>();
		auto *lobby = playerLogo.addComponent<ResumeLobbyComponent>(countPlayer, ready, playerTile, colors.at(colorStr)).tryGetComponent<ResumeLobbyComponent>();
		std::string iaPropertyValue = node.getProperty("ia");
		if (iaPropertyValue != "false" && iaPropertyValue != "true") {
			throw ParserError("Invalid value for ia property");
		}
		if (node.getProperty("ia") == "true") {
			auto *texture = dynamic_cast<RAY::Texture *>(ready.getComponent<Drawable2DComponent>().drawable.get());
			lobby->ready = true;
			lobby->layout = ControllableComponent::AI;
			if (texture)
				texture->use("assets/player/icons/ai.png");
		}
	}

	void ParserYAML::_loadPlayers(std::shared_ptr<WAL::Scene> scene, Node &node)
	{
		int countPlayer = 0;
		auto childNode = node.getChildNodes("players").at(0).getChildNodes();

		if (childNode.size() < 2)
			throw (ParserError("There isn't enough players to load this saved map."));
		for (auto &child : childNode) {
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

		if (!Utils::tryParse(node.getProperty("width"), size)) {
			throw ParserError("width property must be an int");
		}
		Runner::mapWidth = size;
		if (!Utils::tryParse(node.getProperty("height"), size)) {
			throw ParserError("width property must be an int");
		}
		Runner::mapHeight = size;
		std::chrono::nanoseconds::rep timer = 0;
		if (!Utils::tryParse(node.getProperty("timer"), timer)) {
			throw ParserError("timer property must be a long");
		}
		Runner::timerDelay = std::chrono::nanoseconds(timer);

		for (int i = 0; i < Runner::mapWidth; i++)
			for (int j = 0; j < Runner::mapHeight; j++)
				map[std::make_tuple(i, 0, j)] = MapGenerator::NOTHING;
		auto childNode = node.getChildNodes("blocks").at(0).getChildNodes();
		for (const auto& child : childNode)
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
		auto childNode = node.getChildNodes("bonuses").at(0).getChildNodes();
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

	Vector3f ParserYAML::_parsePosition(const std::string& line)
	{
		float x;
		float y;
		float z;
		std::string subStr;

		try {
			auto start = line.find('[') + 1;
			auto end = line.find(']');
			if (line.front() != '[' || end == std::string::npos || line.back() != ']') {
				throw ParserError("Error parsing position.");
			}
			subStr = line.substr(start, end - start);
			auto pos = Utils::splitStr(subStr, ',');
			if (pos.size() != 3)
				throw (ParserError("Error parsing position."));
			if (!Utils::tryParse(pos[0], x) || !Utils::tryParse(pos[1], y) || !Utils::tryParse(pos[2], z))
				throw (ParserError("Error parsing position."));
		} catch (const std::out_of_range &err) {
			throw (ParserError("Error parsing position."));
		}
		return Vector3f(x, y, z);
	}

	int ParserYAML::_parseMaxBomb(const std::string &str)
	{
		int maxBomb = 0;

		if (str.find('-') != std::string::npos)
			throw (ParserError("Couldn't parse max bomb."));
		if (!Utils::tryParse(str, maxBomb))
			throw (ParserError("Couldn't parse max bomb."));
		return (maxBomb);
	}

	int ParserYAML::_parseExplosionRadius(const std::string& line)
	{
		int explosionRadius = 0;

		if (line.find('-') != std::string::npos)
			throw (ParserError("Couldn't parse explosion radius."));
		if (!Utils::tryParse(line, explosionRadius))
			throw (ParserError("Couldn't parse explosion radius."));
		return (explosionRadius);
	}

	float ParserYAML::_parseSpeed(const std::string& line)
	{
		float speed = 0;

		if (line.find('-') != std::string::npos)
			throw (ParserError("Couldn't parse speed."));
		if (!Utils::tryParse(line, speed))
			throw (ParserError("Couldn't parse speed."));
		return (speed);
	}

	MapGenerator::BlockType ParserYAML::_parseBlockType(const std::string& blockType)
	{
		if (blockType.find('-') != std::string::npos)
			throw (ParserError("Couldn't parse block type."));
		int block = 0;
		if (!Utils::tryParse(blockType, block))
			throw (ParserError("Couldn't parse block type."));
		if (block < 0 || block > 7)
			throw (ParserError("Couldn't parse block type."));
		return (static_cast<MapGenerator::BlockType>(block));
	}

	Bonus::BonusType ParserYAML::_parseBonusType(const std::string& bonusType)
	{
		if (bonusType.find('-') != std::string::npos)
			throw (ParserError("Couldn't parse bonus type."));
		int bonus = 0;
		if (!Utils::tryParse(bonusType, bonus))
			throw (ParserError("Couldn't parse bonus type."));
		if (bonus < 0 || bonus > 4)
			throw (ParserError("Couldn't parse bonus type."));
		return (static_cast<Bonus::BonusType>(bonus));
	}

	std::string ParserYAML::parseHeader(const std::string &line)
	{
		std::stringstream ss(line);
		std::string headerName;
		std::string garbage;

		ss >> headerName >> garbage;


		if (!garbage.empty()) {
			throw ParserError("Ill formed header,\nline: " + Utils::trimCopy(line));
		}
		if (headerName.back() != ':') {
			throw ParserError("Header not ended with ':',\nline: " + Utils::trimCopy(line));
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
			throw ParserError("ill formed property, \nline: " + Utils::trimCopy(line));
		}
		if (propertyName.back() != ':') {
			throw ParserError("property name not ended with ':', \nline: " + Utils::trimCopy(line));
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
			throw ParserError("Can't read file");
		return parseNode(file, "root");
	}

	Node ParserYAML::parseNode(std::ifstream &file, const std::string &nodeName, int indentLevel)
	{
		std::string line;
		Node node(nodeName);

		while(std::getline(file, line)) {
			if (line.empty())
				continue;
			float lineIndentLevel = getIndent(line);
			if (lineIndentLevel != static_cast<int>(lineIndentLevel)) {
				throw ParserError("Yaml only support 2 spaces as indent");
			}
			if (lineIndentLevel > static_cast<float>(indentLevel)) {
				throw ParserError("Indent issue");
			}
			if (lineIndentLevel < static_cast<float>(indentLevel)) {
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