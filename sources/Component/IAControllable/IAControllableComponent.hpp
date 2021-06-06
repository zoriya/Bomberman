/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** IAComponent
*/

#ifndef IACOMPONENT_HPP_
#define IACOMPONENT_HPP_

#include "Component/Component.hpp"
#include "Entity/Entity.hpp"
#include "Models/Vector3.hpp"
#include "lua.hpp"

namespace BBM
{
    class IAControllableComponent : public WAL::Component
    {    
        private:
            //! @brief path to the lua script
            const std::string _scriptPath;
        public:
            //! @brief Lua executing state
            lua_State *state;

            //! @inherit
            WAL::Component *clone(WAL::Entity &entity) const override;

            //! @brief Constructor
            IAControllableComponent(WAL::Entity &entity, std::string scripPath);

            //! @brief A IA component can't be instantiated, it should be derived.
            IAControllableComponent(const IAControllableComponent &) = default;

            //! @brief default destructor
            ~IAControllableComponent() override = default;

            //! @brief A IA component can't be assigned
            IAControllableComponent &operator=(const IAControllableComponent &) = delete;
        protected:
    };
}


#endif /* !IACOMPONENT_HPP_ */
