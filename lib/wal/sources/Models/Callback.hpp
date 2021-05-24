//
// Created by Zoe Roux on 5/21/21.
//


#pragma once

#include <functional>

namespace WAL
{
	//! @brief A callback where you can subscribe to and emit it.
	template<typename ...Types>
	class Callback
	{
	private:
		int _nextID = 0;
		//! @brief The list of functions to call.
		std::unordered_map<int, std::function<void (Types...)>> _functions = {};

	public:
		//! @brief Add a method to be called when this callback is invoked.
		//! @param callback The list of arguments of the callback method
		//! @return A unique ID for this callback. That can be used to remove the callback later.
		int addCallback(std::function<void (Types...)> callback)
		{
			int id = this->_nextID++;
			this->_functions[id] = std::move(callback);
			return id;
		}

		//! @brief Remove a function from this callback.
		//! @param id The ID of the function.
		void removeCallback(int id)
		{
			this->_functions.erase(id);
		}

		void operator()(Types ...args) const
		{
			for (const auto &[_, callback] : this->_functions)
				callback(args...);
		}

		//! @brief A default constructor
		Callback() = default;
		//! @brief A default copy constructor
		Callback(const Callback &) = default;
		//! @brief A default destructor
		~Callback() = default;
		//! @brief A default assignment operator
		Callback &operator=(const Callback &) = default;

		//! @brief Implicitly transform a function into a callback.
		Callback(std::function<void (Types...)> callback) // NOLINT(google-explicit-constructor)
		{
			this->addCallback(callback);
		}
	};
}