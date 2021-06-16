//
// Created by cbihan on 16/06/2021.
//

#pragma once

#include <vector>
#include <map>
#include <string>

namespace BBM
{
	class Node
	{
	private:
		//! @brief Node name
		std::string _name;

		//! @brief child nodes
		std::vector<Node> _childNodes;

		//! @brief node's properties
		std::map<std::string, std::string> _properties;

	public:

		std::string getName() const;

		void setName(const std::string &name);

		void addChildNode(const Node &childNode);

		std::vector<Node> getChildNodes(const std::string &childNodeName);

		void setProperty(const std::string &propertyName, const std::string &propertyValue);
		void setProperty(const std::pair<std::string, std::string> &propertyNameValue);

		std::string getProperty(const std::string &propertyName) const;

		//! @brief ctor
		explicit Node(std::string name);
		//! @brief copy ctor
		Node(const Node &) = default;
		//! @brief dtor
		~Node() = default;
		//! @brief assignment operator
		Node &operator=(const Node &) = default;
	};
}

