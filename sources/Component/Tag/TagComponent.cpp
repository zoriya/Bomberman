//
// Created By Louis Auzuret on 07/06/21
//

#include "Component/Tag/TagComponent.hpp"

namespace BBM
{
	WAL::Component *TagComponent::clone(WAL::Entity &entity) const
	{
		return new TagComponent(entity, tag);
	}

	TagComponent::TagComponent(WAL::Entity &entity, std::string tag)
	: Component(entity), tag(tag)
	{ }
}