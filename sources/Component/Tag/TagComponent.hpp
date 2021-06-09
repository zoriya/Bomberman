//
// Created by Zoe Roux on 6/9/21.
//

#pragma once

#include <Component/Component.hpp>
#include <string_view>

namespace BBM
{
	template<std::size_t I>
	struct StringLiteral
	{
	public:
		char value[I];

		//! @brief Implicitly convert an array of char to a string literal.
		constexpr StringLiteral(const char (&str)[I]) // NOLINT(google-explicit-constructor)
			: value()
		{
			std::copy_n(str, I, value);
		}
		//! @brief A string literal is copy constructable.
		constexpr StringLiteral(const StringLiteral &) = default;
		//! @brief A default destructor
		constexpr ~StringLiteral() = default;
		//! @brief A string literal is assignable.
		constexpr StringLiteral &operator=(const StringLiteral &) = default;
	};

	template <StringLiteral name>
	class TagComponent : public WAL::Component
	{
	public:
		Component *clone(WAL::Entity &entity) const override
		{
			return new TagComponent<name>(entity);
		}

		//! @brief Create a new empty tag component.
		explicit TagComponent(WAL::Entity &entity)
			: WAL::Component(entity)
		{}
		//! @brief A default copy constructor.
		TagComponent(const TagComponent &) = default;
		//! @brief A default destructor
		~TagComponent() override = default;
		//! @brief A tag component is not assignable.
		TagComponent &operator=(const TagComponent &) = delete;
	};

	constexpr const char Blowable[] = "Blowable";
	constexpr const char Unbreakable[] = "Unbreakable";
	constexpr const char Breakable[] = "Breakable";
	constexpr const char Hole[] = "Hole";
	constexpr const char Bumper[] = "Bumper";
	constexpr const char Player[] = "Player";
}
