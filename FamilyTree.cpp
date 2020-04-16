

#include "FamilyTree.hpp"
#include <algorithm>
#include <regex>
#include <cmath>
namespace family
{
	// exceptions
	const char* NotFoundException::what() const throw()
	{
		return "The name not found";
	}

	const char* removeRootException::what() const throw()
	{
		return "Can't remove root";
	}
	//contructor exception
	UnhandledRelationException::UnhandledRelationException(std::string relation)
		: relation(relation), message(std::string("The tree cannot handle the '")
			+ relation + std::string("' relation"))
	{

	}

	const char* UnhandledRelationException::what() const throw()
	{
		return message.c_str();
	}

	// NodeTree
	NodeTree::NodeTree(const std::string& name, int rank,
		NodeTree* child, NodeTree* mother, NodeTree* father)
		: name(name), rank(rank), child(child), mother(mother), father(father)
	{

	}
	//getter
	NodeTree* NodeTree::getMother() const
	{
		return mother;
	}

	NodeTree* NodeTree::getFather() const
	{
		return father;
	}

	const std::string& NodeTree::getName() const
	{
		return name;
	}

	NodeTree* NodeTree::getChild() const
	{
		return child;
	}

	int NodeTree::getRank() const
	{
		return rank;
	}

	//set
	void NodeTree::setFather(NodeTree* father)
	{
		this->father = father;
	}

	void NodeTree::setMother(NodeTree* mother)
	{
		this->mother = mother;
	}

	void NodeTree::NewDisplay()
	{

		// Pass initial space count as 0
		print2DUtil(this, 0);
	}
	//geeksforgeeks.org/print-binary-tree-2-dimensions helped that but changed
	void NodeTree::print2DUtil(NodeTree* root, int space)
	{
		// Base case  
		if (root == NULL)
			return;

		// Increase distance between levels
		space += 5;

		// Process right child first  
		print2DUtil(root->getFather(), space);
		// Print current node after space  
		// count  
		std::cout << std::endl;
		for (int i = 5; i < space; i++)
			std::cout << " ";
		std::cout << root->getName() << std::endl;

		// Process left child  
		print2DUtil(root->getMother(), space);
	}

	void NodeTree::setChild(NodeTree* child)
	{
		this->child = child;
	}

	// tree

	Tree::Tree(const std::string& name)
	{
		//if(name.length() == 0)
			//throw NotFoundException();
		NodeTree* root = new NodeTree(name, 0);
		nameToNodeTreeMap[name] = root;
		addToRankToNodeTreeSetMap(root);
	}

	Tree::~Tree()
	{
		if (rankToNodeTreeSetMap.count(0) > 0)
		{
			deleteNodeTreeRec(*rankToNodeTreeSetMap[0].begin());
		}
	}

	void Tree::deleteNodeTreeRec(NodeTree* node)
	{
		if (node == nullptr)
		{
			return;
		}

		deleteNodeTreeRec(node->getFather());
		deleteNodeTreeRec(node->getMother());

		delete node;
	}

	void Tree::updateNameRelation(const std::string& name_parent, const std::string& name_child, bool addFather)
	{
		NodeTree* childNode = nameToNodeTreeMap[name_child];
		NodeTree* parentNode;

		int childNodeRankAbs = abs(childNode->getRank());

		if (addFather)
		{
			parentNode = new NodeTree(name_parent, childNodeRankAbs + 1, childNode);
			childNode->setFather(parentNode);
		}
		else // mother
		{
			parentNode = new NodeTree(name_parent, -1 * childNodeRankAbs - 1, childNode);
			childNode->setMother(parentNode);
		}

		addToRankToNodeTreeSetMap(parentNode);
		nameToNodeTreeMap[name_parent] = parentNode;
	}

	Tree& Tree::addFather(const std::string& name_child, const std::string& name_father)
	{
		if (nameToNodeTreeMap.count(name_child) == 0)
			throw NotFoundException();
		//if(name_father.length() == 0)
			//throw NotFoundException();
		if (nameToNodeTreeMap[name_child]->getFather() != nullptr)
			throw NotFoundException();

		updateNameRelation(name_father, name_child, true);


		return *this;
	}

	Tree& Tree::addMother(const std::string& child_name, const std::string& name_mother)
	{
		if (nameToNodeTreeMap.count(child_name) == 0)
			throw NotFoundException();
		//if(name_mother.length() == 0)
			//throw NotFoundException();
		if (nameToNodeTreeMap[child_name]->getMother() != nullptr)
			throw NotFoundException();
		updateNameRelation(name_mother, child_name, false);

		return *this;
	}

	std::string Tree::relation(const std::string& name) const
	{

		if (nameToNodeTreeMap.count(name) == 0)
			return "unrelated";

		// at() instead of [], because this method is const and [] is a non-const function
		int relationToRoot = nameToNodeTreeMap.at(name)->getRank();

		if (relationToRoot == 0)
			return "me";


		bool femaleFlag = false;

		if (relationToRoot < 0)
		{
			femaleFlag = true;
			relationToRoot *= -1;
		}

		std::string relativeName = "";

		while (relationToRoot > 1)
		{
			if (relationToRoot > 2)
				relativeName += "great-";
			else
				relativeName += "grand";
			relationToRoot--;
		}

		relativeName += femaleFlag ? "mother" : "father";

		return relativeName;
	}

	const std::string& Tree::find(const std::string& relation) const
	{
		int count = 0;

		if (!isRelationValid(relation))
		{
			throw UnhandledRelationException(relation);
		}

		if (relation.compare("me") == 0)
			// at() instead of [], because this method is const and [] is a non-const function
			return (*rankToNodeTreeSetMap.at(0).begin())->getName();

		// 'xfather' or 'xmother'
		int base_relation = relation.find("father") != -1 ? 1 : -1;
		int rank;

		if (relation.find("grand") == -1) // no grand - just 'father' or 'mother'
		{
			rank = base_relation;
		}
		else // grand in string
		{
			rank = 2 * base_relation;

			// check number of great-
			int number_of_greats = std::count(relation.begin(), relation.end(), '-');

			rank += number_of_greats * base_relation;
		}

		if (rankToNodeTreeSetMap.count(rank) == 0)
		{
			throw NotFoundException();
		}
		else
		{
			// at() instead of [], because this method is const and [] is a non-const function
			return (*rankToNodeTreeSetMap.at(rank).begin())->getName();
		}
	}

	bool Tree::isRelationValid(const std::string& relation) const
	{
		// accept "me", "mother", "father"; or a string which contains
		// any number of "great-", followed by "grand", and then either "mother" or "father"
		std::regex relationRegex("me|mother|father|(great-)*grand(mother|father)");
		return std::regex_match(relation, relationRegex);
	}

	void Tree::remove(const std::string& name)
	{
		if (nameToNodeTreeMap.count(name) == 0)
			throw NotFoundException();

		if ((*rankToNodeTreeSetMap[0].begin())->getName().compare(name) == 0)
			throw removeRootException();

		NodeTree* nodeToRemove = nameToNodeTreeMap[name];

		if (nodeToRemove->getChild() != nullptr)
		{
			if (nodeToRemove->getRank() > 0) // male - father
			{
				nodeToRemove->getChild()->setFather(nullptr);
			}
			else // female - mother
			{
				nodeToRemove->getChild()->setMother(nullptr);
			}
		}

		removeParentsRec(nodeToRemove);
	}

	void Tree::removeParentsRec(NodeTree* node)
	{
		if (node == nullptr)
		{
			return;
		}

		removeParentsRec(node->getFather());
		removeParentsRec(node->getMother());
		nameToNodeTreeMap.erase(node->getName());
		removeFromRankToNodeTreeSetMap(node);
		delete node;
	}

	void Tree::display() const
	{
		NodeTree* root = *rankToNodeTreeSetMap.at(0).begin();
		root->NewDisplay();
	}

	void Tree::addToRankToNodeTreeSetMap(NodeTree* node)
	{
		if (rankToNodeTreeSetMap.count(node->getRank()) == 0)
		{
			rankToNodeTreeSetMap[node->getRank()] = std::set<NodeTree*>();
		}

		rankToNodeTreeSetMap[node->getRank()].insert(node);
	}

	void Tree::removeFromRankToNodeTreeSetMap(NodeTree* node)
	{
		if (rankToNodeTreeSetMap[node->getRank()].size() == 1)
		{
			// remove entire set from map
			rankToNodeTreeSetMap.erase(node->getRank());
		}
		else
		{
			// remove node from set
			std::set<NodeTree*>& set = rankToNodeTreeSetMap[node->getRank()];
			set.erase(set.find(node));
		}
	}
}
