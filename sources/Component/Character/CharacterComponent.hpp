//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#include "lib/wal/sources/Component/Component.hpp"
#include "sources/Component/Bomb/BombComponent.hpp"
#include "lib/wal/sources/Models/Vector3.hpp"

class CharacterComponent : public WAL::Component
{
    private:
        //! @brief player number
        unsigned _playerNumber;
        //! @brief health point of the character
        unsigned _healthPoint;
        //! @brief maximum number of bombs a character can put
        unsigned _maxBombCount;
        //! @brief bomb type of the character
        BombComponent::BombType _bombType;
        //! @brief is player a human being
        bool _isHuman;
        //! @brief Remote bomb trigger available
        bool _canTriggerRemote;
        static unsigned _nextPlayer;
    protected:
    public:

        CharacterComponent(WAL::Entity &entity, BombComponent::BombType bombType);
        ~CharacterComponent() override = default;
        //! @brief A character component is copyable
		CharacterComponent(const CharacterComponent &) = default;
		//! @brief A character component is assignable
		CharacterComponent &operator=(const CharacterComponent &) = delete;

        //! @brief get player number
        unsigned getPlayerNumber() const;
        //! @brief get health point of the character
        unsigned getHealthPoint() const;
        //! @brief get maximum number of bombs a character can put
        unsigned getMaxBombCount() const;
        //! @brief get bomb type of the character
        BombComponent::BombType getBombType() const;
        //! @brief is player a human being
        bool isHuman() const;
        //! @brief trigger can be remote
        bool canTriggerRemote() const;

        //! @brief set player number
        void setPlayerNumber(unsigned playerNumber);
        //! @brief set health point of the character
        void setHealthPoint(unsigned healthPoint);
        //! @brief set maximum number of bombs a character can put
        unsigned setMaxBombCount(unsigned maxBombCount);
        //! @brief set bomb type of the character
        BombComponent::BombType setBombType(BombComponent::BombType bombType);
        //! @brief set if player is a human being
        bool setIsHuman(bool isHuman);
        //! @brief Remote bomb trigger available
        bool setCanTriggerRemote(bool canTriggerRemote);
        
};