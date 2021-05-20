//
// Created by Tom Augier on 2021-05-20.
// Edited by Benjamin Henry on 2021-05-20.
// Edited by Louis Auzuret on 2021-05-20.
//

#pragma once

#include <string>
#include "lib/wal/sources/Entity/Entity.hpp"
#include "lib/wal/sources/Models/Vector3.hpp"

class Camera : public WAL::Entity
{
    private:
        std::string _name;
    protected:
    public:   
        Camera(std::string name);
        ~Camera();

        //! @brief camera zoom in
        void zoomIn(WAL::Vector3f) const;
        //! @brief camera zoom out
        void zoomOut(WAL::Vector3f) const;
        //! @brief camera zoom on 
        void zoomOn(WAL::Entity &) const;

};