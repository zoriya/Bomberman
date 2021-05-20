//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#pragma once

#include "lib/wal/sources/Component/Component.hpp"
#include "lib/wal/sources/Entity/Entity.hpp"

class PowerUpComponent : public WAL::Component
{
    public:
    
        enum PowerUpType {
            SPEED,
            FIREPOWER,
            BOMBCOUNT,
            BOMBKICK
        };

        PowerUpComponent(WAL::Entity &entity, PowerUpType powerType, int duration, bool infinite = false);
        ~PowerUpComponent();
        //! @brief A power up component is copyable
		PowerUpComponent(const PowerUpComponent &) = default;
		//! @brief A power up component is assignable
		PowerUpComponent &operator=(const PowerUpComponent &) = delete;
        
        //! @brief Get is the power up infinite
        bool getIsInfinite() const;
        //! @brief Get duration
        unsigned getDuration() const;
        //! @brief Get power up type
        PowerUpType getPowerUpType() const;

        //! @brief Set if bomb duration infinite
        void setIsInfinite(bool isInfinite);
        //! @brief Set duration
        void setDuration(unsigned duration);
        //! @brief Set power up type
        void setPowerUpType(PowerUpType powerUpType);

    protected:
    private:

        
        //! @brief Is the power up infinite
        bool _isInfinite;
        //! @brief Duration of the power up
        unsigned _duration;
        //! @brief Power up type
        PowerUpType _powerUpType;
        

};
