#include <iostream>
#include <string>
#include <cstring>
#include "pa2.h"
using namespace std;

//node constructor
Node::Node(string data, Node* next) {

  this->data = data;
  this->next = next;
}

//returns the next node
Node* Node::getNext() {

  return this->next;
}

//returns this node's data
string Node::getData() {

  return this->data;
}

//sets this node's next node
void Node::setNext(Node* next) {

  this->next = next;
}

//sets the node's data to the string that is passed in
void Node::setData(string toSet) {

  this->data = toSet;
}

//removes data from the list
bool LinkedList::remove(string toRemove) {

    //if the head is null then there are no nodes and thus no string to remove
    if (head == NULL) {
      return false;
    }

    //start at the head
    Node * temp = head;

    //if the head is equal to the element we want to remove
    if (temp->getData().compare(toRemove)==0) {
      temp->setData("Free");
      return true;
    }

    /* keep going until the next node in the linked list is null or the next
     node in the linked list is the element that we are searching for */
    while (temp->getNext() != NULL && !(temp->getNext()->getData().compare(toRemove)==0)) {
      temp = temp->getNext();
    }

    /* from the previous while loop, if the next element is null, then the
    element is not present in the list */
    if (temp->getNext() == NULL) return false;

    /* if the previous if statement is not executed, then we know the next
    element is the one that we are searching for! set it to free to delete it */
    temp->getNext()->setData("Free");
    return true;
}

//data to insert
void LinkedList::insert(string toInsert) {

  //start at the head
  Node* current = head;

  //if the head is null, then the element is inserted as the head
  if (current == NULL) {

    head = new Node(toInsert, NULL);
    return;
  }

  //keep going until the next node in the linked list is null
  while (current->getNext() != NULL) {

    current = current->getNext();
  }

  /* set the next node in the linked list, which is null at this point, to
  the element we want to insert */
  current->setNext(new Node(toInsert, NULL));
}

/* returns 'success' if successful add, 'memory' if there is not enough memory,
or 'running' if a program with that name is currently running. using the
'best case' memory allocation algorithm */
string LinkedList::worstMemoryAlg(string program, int pages) {

    Node* current = head;
    int currentPartitionSize;
    Node* beginCurrentPartition;
    int worstPartitionSize = INT_MIN;
    Node* beginWorstPartition;

    //verifies that the program is not currently running
    while (current->getNext() != NULL) {
      if (current->getData().compare(program)==0) return "running";
      current = current->getNext();
    }

    current = head;

    //determines the best partition size, and places it's starting node in beginBestPartition
    while (true) {

      currentPartitionSize = INT_MIN;

      //finds the current partition size
      if (current->getData().compare("Free")==0) {

        currentPartitionSize = 1;
        beginCurrentPartition = current;

        /* as long as the next node is not null and it is equal to free, then
        our current memory partition is still ongoing */
        while (current->getNext() != NULL && current->getNext()->getData().compare("Free")==0) {

          currentPartitionSize++;
          current = current->getNext();
        }
      }

      /* if the current partition size is sufficient to fit the program and is
      smaller than our current best partition, the current partition is our new best partition */
      if (currentPartitionSize > worstPartitionSize && currentPartitionSize >= pages) {

        beginWorstPartition = beginCurrentPartition;
        worstPartitionSize = currentPartitionSize;
      }

      if (current->getNext() != NULL) current = current->getNext();
      else break;
    }

    //if no valid partition size was found
    if (worstPartitionSize == INT_MIN) return "memory";

    //if a proper partion was found, then place the program there!
    current = beginWorstPartition;
    for (int i = 0; i < pages; i++) {

      current->setData(program);
      if (current->getNext() != NULL) current = current->getNext();
    }

    //if we've gotten this far, it worked!
    return "success";
}

/* returns 'success' if successful add, 'memory' if there is not enough memory,
or 'running' if a program with that name is currently running. using the
'best case' memory allocation algorithm */
string LinkedList::bestMemoryAlg(string program, int pages) {

    Node* current = head;
    int currentPartitionSize;
    Node* beginCurrentPartition;
    int bestPartitionSize = INT_MAX;
    Node* beginBestPartition;

    //verifies that the program is not currently running
    while (current->getNext() != NULL) {
      if (current->getData().compare(program)==0) return "running";
      current = current->getNext();
    }

    current = head;

    //determines the best partition size, and places it's starting node in beginBestPartition
    while (true) {

      currentPartitionSize = INT_MAX;

      //finds the current partition size
      if (current->getData().compare("Free")==0) {

        currentPartitionSize = 1;
        beginCurrentPartition = current;

        /* as long as the next node is not null and it is equal to free, then
        our current memory partition is still ongoing */
        while (current->getNext() != NULL && current->getNext()->getData().compare("Free")==0) {

          currentPartitionSize++;
          current = current->getNext();
        }
      }

      /* if the current partition size is sufficient to fit the program and is
      smaller than our current best partition, the current partition is our new best partition */
      if (currentPartitionSize < bestPartitionSize && currentPartitionSize >= pages) {

        beginBestPartition = beginCurrentPartition;
        bestPartitionSize = currentPartitionSize;
      }

      if (current->getNext() != NULL) current = current->getNext();
      else break;
    }

    //if no valid partition size was found
    if (bestPartitionSize == INT_MAX) return "memory";

    //if a proper partion was found, then place the program there!
    current = beginBestPartition;
    for (int i = 0; i < pages; i++) {

      current->setData(program);
      if (current->getNext() != NULL) current = current->getNext();
    }

    //if we've gotten this far, it worked!
    return "success";
}

//return the head of the linked list
Node* LinkedList::getHead() {

  return this->head;
}

//print the linked list, seperated by spaces
void LinkedList::traverse() {

  //start at the head
  Node* temp = head;

  //we've printed none, so far
  int count = 0;

  //so long as there's elements in the linked list that havent been printed...
  while (temp != NULL) {

    //print the current element
    cout << temp->getData();

    //increment the amount of printed elements
    count++;

    /* these lines control the formatting. if we have printed a multiple of 8
    elements, then we are at the end of the line and should indent. if we have
    printed between 0 and 8 noninclusive, then we must seperate the elements
    with a tab*/
    if (count%8 > 0 && count%8 < 8) cout << "\t";
    if (count % 8 == 0) cout << endl;

    //move to the next element
    temp = temp->getNext();
  }

  //print additional line
  cout << endl;
}

//search the linked list and return the node's memory address
Node* LinkedList::search(string toFind) {

  //start at the head
  Node * temp = head;

  /* if the head is null, then there are no elements in the linked list and
  thus no element that we are searching for */
  if (temp == NULL) return NULL;

  //if the current element (the head) is equal to the element we want to find, return it!
  if (temp->getData().compare(toFind)==0) return temp;

  /* so long as the next element is not null and it is not the element we are
  looking for, move to the next element */
  while (temp->getNext() != NULL && !(temp->getNext()->getData().compare(toFind)==0)) {

    temp = temp->getNext();
  }

  //from the previous loop, if the next element is null then the element isnt in the list
  if (temp->getNext() == NULL) return NULL;

  //if we have gotten this far, then the next element is the element we're looking for!
  return temp->getNext();
}

//returns the memory LinkedList
LinkedList* pa2::getMemory() {

  return this->memory;
}

//pa2 constructor. initializes the memory LinkedList
pa2::pa2(){

  this->memory = new LinkedList();
  //start every element as free space
  for (int i = 0; i < 32; i++) {
    memory->insert("Free");
  }
}

//returns the current number of fragmented memory
int pa2::getFrag() {

  //start at the head
  int fragments = 0;
  Node* current = memory->getHead();

  //determines the best partition size, and places it's starting node in beginBestPartition
  while (true) {

    //the start of a new partition (and fragment)
    if (current->getData().compare("Free")==0) {

      //add this fragment to our total amount of fragments!
      fragments++;

      /* as long as the next node is not null and it is equal to free, then
      our current memory partition is still ongoing */
      while (current->getNext() != NULL && current->getNext()->getData().compare("Free")==0) {

        current = current->getNext();
      }
    }

    //move the current node to the next, so long as it isnt null
    if (current->getNext() != NULL) current = current->getNext();
    else break;
  }

  //return total fragments
  return fragments;
}

//used to delete memory and all it's contained nodes at the end of our main
void pa2::deleteMemory() {

  //start with the head
  Node* current = memory->getHead();
  Node* next;

  //delete all the nodes in the memory simulation LinkedList
  while (current != NULL) {
    next = current->getNext();
    delete current;
    current = next;
  }

  //delete the memory simulation LinkedList!
  delete memory;
}

int main(int argc, char ** argv) {

  //declaring variables for use in program control loop
  bool usingBest, usingWorst, validAlg, foundProgram;
  string alg, tempName, addMessage;
  int tempSize, pages, pagesRemoved;
  pa2* p = new pa2();

  //to check to see if the command line args were supplied with correct number of elements
  validAlg = (argc == 2);

  //if there were the correct # of elem, check to see if it requested the best or the worst case alg
  if (validAlg) {
    alg = argv[1];
    usingBest = alg.compare("best")==0;
    usingWorst = alg.compare("worst")==0;
    validAlg = validAlg && (usingWorst || usingBest);
  }

  //a valid algorithm is one that was passed in with 2 elements and is either best or worst
  if (!validAlg) {
    cout << "Must specify 'best' or 'worst' algorithm through command line." << endl;
    return 0;
  }

  //prints to console the algorithm that is being used
  if (usingWorst) cout << "Using worst fit algorithm\n" << endl;
  else cout << "Using best fit algorithm\n" << endl;

  //initialize the user input variable
  int choice = 0;

  //prints menu choices
  cout << "\t1.\tAdd program\n\t2.\tKill program\n\t3.\tFragmentation\n\t4.\tPrint memory\n\t5.\tExit\n" << endl;

  //program control loop
  do {

    //confirms that the user input is a valid integer between 1 and 5 inclusive
    if ((cout << "choice - " && !(cin >> choice)) || (choice < 1 || choice > 5)) {
      cin.clear(); //clear bad input flag
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
      cout << "Invalid input; please re-enter.\n";
      continue;
    }

    if (choice == 1) {

      //get valid name for program. cannot be 'Free'
      while ((cout << "Program name - " && !(cin >> tempName)) || (tempName.compare("Free")==0)) {
        cin.clear(); //clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter.\n";
      }

      //gets program size, confirms that it is an int
      while ((cout << "Program size (KB) - " && !(cin >> tempSize)) || tempSize<=0) {
        cin.clear(); //clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter.\n";
      }

      /* the amount of pages used is always equal to the integer division of
      the size of the program and 4, plus 1 if the size is not a multiple of 4.
      if the size of the program is not a multiple of 4, we have fragmented memory*/
      pages = tempSize/4;
      if (tempSize%4 != 0) {
        pages++;
      }

      //if using the worst memory algorithm. storing the return in addMessage
      if (usingWorst) addMessage = p->getMemory()->worstMemoryAlg(tempName, pages);

      //else using the worst memory algorithm. storing the return in addMessage
      else addMessage = p->getMemory()->bestMemoryAlg(tempName, pages);

      //extra output line
      cout << endl;

      //if the program was added successfully
      if (addMessage.compare("success")==0) cout << "Program " << tempName << " added successfully: " << pages << " page(s) used." << endl;

      //if the program wasnt added because there wasnt enough memory
      else if (addMessage.compare("memory")==0) cout << "Error, Not enough memory for Program " << tempName << "." << endl;

      //if the program wasnt added because it was already running
      else if (addMessage.compare("running")==0) cout << "Error, Program "<< tempName <<" already running." << endl;

      //this should never happen
      else cout << "something went wrong!!!!" << endl;

      /* for additional information on the return of the memory
      allocation algorithms, refer to their function definitions */

      //extra output line
      cout << endl;
    }

    else if (choice == 2) {

      //get valid name for program. cannot be 'Free'
      while ((cout << "Program name - " && !(cin >> tempName)) || (tempName.compare("Free")==0)) {
        cin.clear(); //clear bad input flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
        cout << "Invalid input; please re-enter.\n";
      }

      //by default, there have been 0 pages removed and the program hasnt been found
      pagesRemoved = 0;
      foundProgram = false;

      do {

        //if a program page has been fount, foundProgram is true
        foundProgram = p->getMemory()->remove(tempName);

        //if a program page has been found, increment the pages removed
        if (foundProgram) pagesRemoved++;

      } while (foundProgram);

      //extra output line
      cout << endl;

      //if the program pages removed is greater than 0, then the program has been removed
      if (pagesRemoved > 0) {

        cout << "Program " << tempName << " successfully killed, " << pagesRemoved << " page(s) reclaimed.\n";
      }
      else cout << "Error, Program "<< tempName <<" unsuccessfully killed.\n";

      //extra output line
      cout << endl;
    }

    else if (choice == 3) {

      //print the amount of fragments in the memory
      cout << "\nThere are " << p->getFrag() << " fragment(s).\n" << endl;
    }

    else if (choice == 4) {

      //print the memory array
      cout << endl;
      p->getMemory()->traverse();
      cout << endl;
    }

    else if (choice == 5) break;

  } while (true);

  //clean up and end program
  p->deleteMemory();
  delete p;
  return 0;
}
