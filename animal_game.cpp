#include <iostream>
#include <string>
#include "binary_tree.h"
#include <limits>

using namespace std;

bool isVowel(char c) {return c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U';}
bool getAnswer(string question);
int main(int argc, char *argv[]) {
  string filename = "animal_tree.data";
  string input, animal;
  bool play_again = true;
  binary_tree::node *current_node;

  binary_tree animals = binary_tree::read(filename.c_str());
  if (animals.isEmpty())
    animals.addRoot("Eagle");
  
  while(play_again) {
    cout << "Think of an animal... \t Hit enter when you are ready.";
    getline(cin, input);
    current_node = animals.getRoot();
    
    while (!current_node->isLeaf()) {
      if (getAnswer(current_node->data + " (Y/N)? "))
	current_node = current_node->getRight();
      else
	current_node = current_node->getLeft();
    }

    if (!getAnswer((string)"Is it " + (isVowel(current_node->data.at(0)) ? "an " : "a ") + current_node->data + "(Y/N)? ")) {
      cout << "What animal is it? ";
      getline(cin, animal);
      cout << "What Yes/No question could I have asked to identify your animal? ";
      getline(cin, input);
      
      if (getAnswer(input + " (Y/N)? ")) {
	animals.addRight(current_node, animal);
	animals.addLeft(current_node, current_node->data);
      }
      else {
	animals.addLeft(current_node, animal);
	animals.addRight(current_node, current_node->data);
      }
     
      current_node->data = input;
    }
    else 
	cout << "Well that was easy" << endl;

    if (!getAnswer("Play again? (Y/N)? "))
      play_again = false;   
  }
  animals.write(filename.c_str());
  return 0;
}

bool getAnswer(string question) {
  string input;
  while (1) {
    cout << question;
    getline(cin, input);
    if (input[0] == 'y' || input[0] == 'Y')
      return true;
    else if (input[0] == 'n' || input[0] == 'N')
      return false;

    cout << "Yes or no answers only please" << endl;
  }
}
  
