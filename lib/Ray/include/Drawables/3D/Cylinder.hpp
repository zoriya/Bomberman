/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Pixel
*/

#ifndef CYLINDER_HPP_
#define CYLINDER_HPP_

#include <raylib.h>
#include "Drawables/ADrawable3D.hpp"

namespace Ray::Drawable3D {
    class Cylinder: public ADrawable3D
	{
        public:
            //! @brief Cylinder constructor
            //! @param position position of the center 
            //! @param radiusTop radius at the top  the cylinder(in percentage)
            //! @param radiusBottom radius at the bottom of the cylinder(in percentage)
            //! @param radiusBottom heighth of the cylinder(in percentage)
            //! @param Color Color of the cylinder
            Cylinder(Vector3 position, float radiusTop, float radiusBottom, float height, Color color);

            
            //! @brief A default copy constructor
            Cylinder(const Cylinder &) = default;

            //! @brief A cylinder is assignable
            Cylinder &operator=(const Cylinder &) = default;

            //! @brief A default destructor
            ~Cylinder() = default;

            //! @return the radius of the cylinder
            int getTopRadius(void) const;

            //! @brief set radius
            Cylinder &setTopRadius(float radius) const;

            //! @return the radius of the cylinder
            int getBottomRadius(void) const;

            //! @brief set radius
            Cylinder &setBottopRadius(float radius) const;

            //! @return the position of the center
            const Vector3 &getPosition(void) const;

            //! @brief the position of the center
            Cylinder &setPosition(const Vector3 &) const;

            //! @return the Heigth
            const Vector3 &getHeigth(void) const;

            //! @brief the Heigth
            Cylinder &setHeigth(float heigth) const;


        private:
            //! @brief Radius of the cylinder (in percentage)
            float _topRadius;

            //! @brief Radius of the cylinder (in percentage)
            float _bootomRadius;

            //! @brief heigth of the cylinder (in percentage)
            float _heigth;

            //! @brief position of the center
            Vector3 _centerPos;
    };
};

#endif /* !PIXEL_HPP_ */
