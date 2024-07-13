#include "include/Node.hpp"

Node::Node(): Children(std::vector<Node*>()), Parent(nullptr){
}
Node::~Node(){
}
void Node::AttachChild(Node* child){
	child->Parent = this;
	Children.push_back(child);
}
Node* Node::DetachChild(const Node* node){
	//search in children vector for node. if found -> assign &node to found(Node);
	//erase found in children.
	//return as ptr;
	Node* result = nullptr;
	auto child = std::find(Children.begin(), Children.end(),node);
	if( child != Children.end() ){
		result = *child ;
		result->Parent = nullptr;
		Children.erase( child );
		return result;
	}
	return nullptr;
}
void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	drawCurrent( target, states );
	for (auto child : Children)
		child->draw(target, states);
}
/*
void Node::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
	for( const Node* child: Children )
		child->draw( target, states );
}
*/
void Node::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	
}
