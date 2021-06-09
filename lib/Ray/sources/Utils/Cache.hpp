/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Cache
*/

#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <raylib.h>
#include <vector>
#include <algorithm>
#include <string>

namespace RAY {
	//! @brief A templated class used to cache ressources, indexed with a string
	template<typename T>
	class Cache {
		public:
			//! @brief 
			Cache(std::function<T(const char *)> dataLoader, std::function<void(T)> dataUnloader):
				_dataLoader(dataLoader), _dataUnloader(dataUnloader)
			{};

			//! @brief Default destructor, will destroy ray's data
			~Cache() = default;

			//! @brief default copy constructor
			Cache(const Cache &) = default;

			//! @brief a cache is assignable
			Cache &operator=(const Cache &) = default;

			//! @param path path of the file
			//! @param lonely: should be set to true if the loaded data must be held by no other active entites
			//! @return a newly loaded ressource if it hasn't be previously loaded, or one from cache            
			std::shared_ptr<T>fetch(const std::string &path, bool lonely = false)
			{
				if (!this->_cache.contains(path))
					this->_cache.emplace(path, std::vector<std::shared_ptr<T>>());
				std::vector<std::shared_ptr<T>> &matchingDataVector = this->_cache.at(path);

				for (std::shared_ptr<T> &i: matchingDataVector) {
					if (!lonely)
						return i;
					if (lonely && i.use_count() == 1)
						return i;
				}
				matchingDataVector.emplace_back(std::shared_ptr<T>(
				new T(this->_dataLoader(path.c_str())), [this](T *p) {
					this->_dataUnloader(*p);
					delete p;
				}));
				return matchingDataVector.back();
			};
		private:
			//! @brief function to call to load data
			std::function<T(const char *)> _dataLoader;

			//! @brief function to call when the ray data will be unloaded
			std::function<void(T)> _dataUnloader;

			//! @brief map storing shared ptr of caches
			std::unordered_map<std::string, std::vector<std::shared_ptr<T>>> _cache;
	};

	template<>
	class Cache<::ModelAnimation> {
		public:
			Cache(std::function<::ModelAnimation *(const char *, int *)> dataLoader, std::function<void(::ModelAnimation *, unsigned int)>dataUnloader):
				_dataLoader(dataLoader), _dataUnloader(dataUnloader)
			{};
			std::shared_ptr<::ModelAnimation> fetch(const std::string &path, int *counter)
			{
				if (this->_cache.find(path) != this->_cache.end())
					return this->_cache[path];

				::ModelAnimation *animations = this->_dataLoader(path.c_str(), counter);
				unsigned int animCount = *counter;

				this->_cache.emplace(path, std::shared_ptr<::ModelAnimation>(
				animations, [this, animCount](::ModelAnimation *p) {
			        this->_dataUnloader(p, animCount);
				}));
				return this->_cache[path];
			};
		private:
			//! @brief function to call to load data
			std::function<::ModelAnimation *(const char *, int *)> _dataLoader;

			//! @brief function to call when the ray data will be unloaded
			std::function<void(::ModelAnimation *, unsigned int)> _dataUnloader;

			//! @brief map storing shared ptr of caches
			std::unordered_map<std::string, std::shared_ptr<::ModelAnimation>> _cache;
	};
}
