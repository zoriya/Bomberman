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

namespace BBM
{
    class IAComponent : public WAL::Component
    {    
        private:

            Vector3f _pos;
            const std::string _scriptPath;

        public:

            //! @brief get IA Position
            Vector3f getPosition(void) const;

            //! @param pos Position of the player
            //! @brief set IA position
            void setPosition(Vector3f &);

            //! @inherit
            WAL::Component *clone(WAL::Entity &entity) const override;
                
            //! @brief A IA component can't be instantiated, it should be derived.
            explicit IAComponent(WAL::Entity &entity);

            //! @brief Constructor
            IAComponent(WAL::Entity &entity, std::string scripPath);

            //! @brief A IA component can't be instantiated, it should be derived.
            IAComponent(const IAComponent &) = default;

            //! @brief default destructor
            ~IAComponent() override = default;

            //! @brief A IA component can't be assigned
            IAComponent &operator=(const IAComponent &) = delete;
        protected:
    };
}


#endif /* !IACOMPONENT_HPP_ */
