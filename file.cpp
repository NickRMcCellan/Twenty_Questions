#include "qtree.h"

//(Intended to be) recursive function to build a tree from the input file
QuestionTree::Node* QuestionTree::buildTreeFromStream(std::istream& in) {
  //Read the header
  std::string kind;
  in >> kind;
  //Read the space character
  in.get();
  //Read the rest of the line
  std::string restOfLine;
  std::getline(in, restOfLine);
  //Now, do something with the stuff we read!
  //FIXME: don't just return NULL!
	QuestionTree::Node* root = NULL;
	if(kind == "FG:"){
		FinalGuess* newNode = new FinalGuess(restOfLine, *this);
		root = newNode;
		return newNode;
	} else if(kind == "D:"){
		Distinguish* newNode = new Distinguish(restOfLine, *this);
		newNode->yesSubtree = buildTreeFromStream(in);
		newNode->yesSubtree->setParent(newNode);
		newNode->noSubtree = buildTreeFromStream(in);
		newNode->noSubtree->setParent(newNode);
		root = newNode;
		return newNode;
	}
	return root;
}

void QuestionTree::readFromStream(std::istream& in) {
  root = buildTreeFromStream(in);
}

void QuestionTree::writeToStream(std::ostream& out) {
  root->printSubtree(out);
}
    