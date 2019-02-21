#include "qtree.h"
#include <exception>
#include <iostream>

const std::string QuestionTree::INTERNAL_HEADER("D:");
const std::string QuestionTree::LEAF_HEADER("FG:");

//Ask the user a yes/no question, and get a true/false answer, respectively
bool QuestionTree::getAnswer(const std::string& question) {
  std::cout << question << std::endl;
  std::string response("?");
  do {
    std::cout << "Enter (y)es or (n)o: ";
    std::getline(std::cin, response);
  } while (!std::cin.fail() && response[0] != 'y' && response[0] != 'n');
  if (response[0] == 'y') {
    return true;
  } else if (response[0] == 'n') {
    return false;
  } else {
    throw new std::exception();
  }
}

//Play a guessing game, beginning with the question described in this node.
void QuestionTree::Distinguish::play() {
  bool answer = QuestionTree::getAnswer(q);
//  //FIXME: well, we have an answer, now what do we do?
	if(answer){ //if the answer was true
		if(yesSubtree != NULL){ //if the yes subtree exists
			yesSubtree->play();
		}
	} else { //if the answer was false
		if(noSubtree != NULL){ //if the no subtree exists
			noSubtree->play();
		}
	}
}

//Invoke the user interface to:
//   create another final guess
//   create a new question that will distinguish between the two final guesses
//   make this node a child of the new distinguish node, and in this node's former 
//      parent, replace this node with the new distinguish node subtree.
void QuestionTree::FinalGuess::expand() {
  std::cin.clear();
  std::cout << "What were you thinking of?  "
    << "Include an article (a, an, the) if appropriate:" << std::endl;
  std::string response;
  //Need to use this to read a whole line/phrase instead of one word
  std::getline(std::cin, response);
  std::cout << "What is a yes/no question that would distinguish between " 
    << guess << " and " << response << "?" << std::endl;
  std::string question;
  //Need to use this to read a whole line/phrase instead of one word
  std::getline(std::cin, question);
  bool answerForNew = QuestionTree::getAnswer(std::string("What is the correct answer for ") + response + '?');

  FinalGuess* newGuess = new FinalGuess(response, tree);
  Distinguish* newQuestion = new Distinguish(question, tree);
  //FIXME: create new question node with appropriate yes/no children, and 
  //put the new question node in the tree
	
	//if the decision tree is empty or only one FinalGuess node,
	//set the decision tree root node
	
	if(this->getParent() == NULL){
		(tree.root) = newQuestion;
	} else { //if there is a parent node already
		//if the current node is in the yes subtree of it's parent,
		//set the parent's yes subtree to the newQuestion
		if(getParent()->yesSubtree == this){
			parent->yesSubtree = newQuestion;
		} else { //if not, do the opposite
			parent->noSubtree = newQuestion;
		}
		//set the new question's parent to this nodes parent
		newQuestion->setParent(getParent());
	}
	
	//set the current node's parent to the new question
	this->setParent(newQuestion);
	//set the newGuess's parent to the new question
	newGuess->setParent(newQuestion);
	
	//if the new node is the yes answer to the new question,
	//set it to the new question's yes subtree
	if(answerForNew){
		newQuestion->yesSubtree = newGuess;
		newQuestion->noSubtree = this;
	} else { //if it is the no answer, do the opposite
		newQuestion->noSubtree = newGuess;
		newQuestion->yesSubtree = this;
	}
}

//Play a guessing game, beginning with the question described in this node.
void QuestionTree::FinalGuess::play() {
  std::string question;
  question = std::string("Are you thinking of ") + guess + std::string("?");
  if (QuestionTree::getAnswer(question)) {
    std::cout << "Naturally." << std::endl;
  } else {
    std::cout << "Well, drat." << std::endl;
    if (tree.expand()) {
      expand();
    }
  }
}
