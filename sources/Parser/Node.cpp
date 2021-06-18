//
// Created by cbihan on 16/06/2021.
//

#include "Node.hpp"

namespace BBM
{

	Node::Node(std::string name) :
		_name(std::move(name))
	{
	}

	void Node::setProperty(const std::string &propertyName, const std::string &propertyValue)
	{
		this->_properties[propertyName] = propertyValue;
	}

	std::string Node::getProperty(const std::string &propertyName) const
	{
		return this->_properties.at(propertyName);
	}

	std::string Node::getName() const
	{
		return this->_name;
	}

	void Node::addChildNode(const Node &childNode)
	{
		this->_childNodes.emplace_back(childNode);
	}

	std::vector<Node> Node::getChildNodes(const std::string &childNodeName)
	{
		std::vector<Node> childs;

		for (const auto &child : this->_childNodes) {
			if (child.getName() == childNodeName) {
				childs.emplace_back(child);
			}
		}
		return childs;
	}

	std::vector<Node> Node::getChildNodes(void)
	{
		return this->_childNodes;
	}

	void Node::setName(const std::string &name)
	{
		this->_name = name;
	}

	void Node::setProperty(const std::pair<std::string, std::string> &propertyNameValue)
	{
		this->setProperty(propertyNameValue.first, propertyNameValue.second);
	}
}