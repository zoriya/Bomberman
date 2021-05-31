
#pragma once

#include "Component.hpp"

namespace BBM {
    class DimensionComponent : public WAL::Component {
    private:
        //! @brief width of the dimension
        float _width;
        //! @brief height of the dimension
        float _width;
    public:
        //! @brief Instanciate the component with null dimensions
		explicit DimensionComponent(WAL::Entity &entity);

        //! @brief Instanciate the component with given dimensions
		DimensionComponent(WAL::Entity &entity, float width, float height);

		//! @brief Default destructor
		~DimensionComponent() override = default;

		//! @brief A DimensionComponent can't be assigned
		DimensionComponent &operator=(const DimensionComponent &) = delete;

		//! @brief A component can't be instantiated, it should be derived.
		DimensionComponent(const DimensionComponent &) = default;

		//! @brief Clone a component for another or the same entity.
		//! @param entity The entity that owns the new component.
		DimensionComponent *clone(WAL::Entity &entity) const override;

        //! @return 
        float getWidth() const;
        float getHeight() const;

        DimensionComponent &setWidth(float width);
        DimensionComponent &setHeight(float height);
    protected:
    private:
    };
}
