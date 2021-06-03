//
// Created by Zoe Roux on 2021-05-14.
//


#ifndef WAL_SCENE
#define WAL_SCENE

#include <vector>
#include <functional>
#include "Entity/Entity.hpp"

namespace WAL
{
	//! @brief Represent a single scene that contains entities.
	class Scene
	{
	private:
		//! @brief The list of registered entities
		std::vector<Entity> _entities = {};

		//! @brief Notify this scene that a component has been added to the given entity.
		//! @param entity The entity with the new component
		//! @param type The type of the component added.
		void _componentAdded(const Entity &entity, std::type_index type);
		//! @brief Notify this scene that a component has been removed to the given entity.
		//! @param entity The entity with the removed component
		//! @param type The type of the component removed.
		void _componentRemoved(const Entity &entity, std::type_index type);
	public:
		//! @brief Get the list of entities.
		std::vector<Entity> &getEntities();

		//! @brief Add a new entity to the scene.
		//! @param name The name of the created entity.
		//! @return The created entity is returned.
		Entity &addEntity(const std::string &name);

		template<typename ...Components>
		std::vector<std::reference_wrapper<Entity>> &view()
		{
			return this->view(typeid(Components)...);
		}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
		template<typename ...Components>
		std::vector<std::reference_wrapper<Entity>> &view(const Components &...index) requires(std::is_same_v<Components...>)
		{
			static std::vector<std::reference_wrapper<Entity>> view;

			std::copy_if(this->_entities.begin(), this->_entities.end(), std::back_inserter(view), [&index...](Entity &entity) {
				return (entity.hasComponent(index) && ...);
			});
			return view;
		}
#pragma clang diagnostic pop

		//! @brief A default constructor
		Scene() = default;
		//! @brief A scene is copy constructable
		Scene(const Scene &) = default;
		//! @brief A default destructor
		~Scene() = default;
		//! @brief A scene is assignable
		Scene &operator=(const Scene &);
		Scene(Scene &&) = default;

		friend Entity;
	};
} // namespace WAL

#else

#endif