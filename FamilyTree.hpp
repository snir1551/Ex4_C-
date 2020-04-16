#pragma once
#include <string>
#include <iostream>
#include <map>
#include <set>
using namespace std;
namespace family //namespace of the tree family
{
    class NotFoundException : public std::exception // new exception extends from Exception
    {
		public:
			const char* what() const throw();
    };

	class removeRootException : public std::exception // new exception extends from Exception
    {
		public:
			const char* what() const throw();
    };

	class UnhandledRelationException : public std::exception
	{
		private:
			std::string relation;
			std::string message;

		public:
			UnhandledRelationException(std::string relation);
			const char* what() const throw();
	};

	class NodeTree
	{
		private:
			NodeTree *mother, *father;
			NodeTree* child;
			std::string name;
			int rank;
			
		public:
			NodeTree(const std::string& name, int rank,
				NodeTree* child = nullptr, NodeTree* mother = nullptr, NodeTree* father = nullptr);

			NodeTree* getMother() const;
			void setMother(NodeTree* mother);
			NodeTree* getFather() const;
			void setFather(NodeTree* father);
			NodeTree* getChild() const;
			void setChild(NodeTree* child);
			const std::string& getName() const;
			int getRank() const;
			void NewDisplay();
			void print2DUtil(NodeTree *root, int space);
	};

    class Tree { //our class Tree
        private:
            std::map <int,std::set<NodeTree*>> rankToNodeTreeSetMap;
            std::map <std::string,NodeTree*> nameToNodeTreeMap;

			void updateNameRelation(const std::string& name_parent, 
				const std::string& name_child, bool addFather); //O(1)
			void removeParentsRec(NodeTree* node); //O(n)
			void addToRankToNodeTreeSetMap(NodeTree* node); // O(1)
			void removeFromRankToNodeTreeSetMap(NodeTree* node);//O(1)
			void deleteNodeTreeRec(NodeTree* node);//O(n)
			bool isRelationValid(const std::string& relation) const;//O(1)
        public:
            Tree(const std::string& name); //declaration constructor
			
			~Tree();

			Tree& addFather(const std::string& name_child, const std::string& name_father); //O(1)

			Tree& addMother(const std::string& child_name, const std::string& name_mother); //O(1)

            void display() const; //O(n)

            std::string relation(const std::string& name) const; //O(1)

			const std::string& find(const std::string& relation) const; //O(1)

            void remove(const std::string& name); //O(n)
            

    };


};
