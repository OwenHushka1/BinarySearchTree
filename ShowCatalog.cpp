#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::ShowCatalog()
{
    root = nullptr;
}

/* Completed functions. DO NOT MODIFY*/
void destroyNode(ShowItem *current)
{
    if (current != nullptr)
    {
        destroyNode(current->left);
        destroyNode(current->right);

        delete current;
        current = nullptr;
    }
}

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::~ShowCatalog()
{
    destroyNode(root);
}

/* Completed functions. DO NOT MODIFY*/
void printShowHelper(ShowItem *m)
{
    if (m != nullptr)
    {
        cout << "Show: " << m->title << " " << m->userRating << endl;
        printShowHelper(m->left);
        printShowHelper(m->right);
    }
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::printShowCatalog()
{
    if (root == nullptr)
    {
        cout << "Tree is Empty. Cannot print" << endl;
        return;
    }
    printShowHelper(root);
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *getShowHelper(ShowItem *current, string title)
{
    if (current == NULL)
        return NULL;

    if (current->title == title)
        return current;

    if (current->title > title)
        return getShowHelper(current->left, title);

    return getShowHelper(current->right, title);
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::getShow(string title)
{
    ShowItem *node = getShowHelper(root, title);
    if (node != nullptr)
    {
        cout << "Show Info:" << endl;
        cout << "==================" << endl;
        cout << "Title :" << node->title << endl;
        cout << "Year :" << node->year << endl;
        cout << "Show Rating :" << node->showRating << endl;
        cout << "User Rating :" << node->userRating << endl;
        return;
    }

    cout << "Show not found." << endl;
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *addNodeHelper(ShowItem *current, ShowItem *newNode)
{
    if (current == nullptr)
    {
        return newNode;
    }

    if (current->title > newNode->title)
    {
        current->left = addNodeHelper(current->left, newNode);
    }
    else
    {
        current->right = addNodeHelper(current->right, newNode);
    }

    return current;
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating)
{
    if (root == nullptr)
    {
        root = new ShowItem(title, year, showRating, userRating);
        return;
    }

    root = addNodeHelper(root, new ShowItem(title, year, showRating, userRating));
}







ShowItem* getMinValueNode(ShowItem* currNode){

    if(currNode->left == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->left);
}


ShowItem* deleteNodeHelper(ShowItem* currNode, string value)
{
    // TODO: Recitation 8 
    // HINT: You might have to use the minValueNode function for one of the cases.
     
  if(currNode == NULL)
  {
    return NULL;
  }
  else if(value < currNode->title)
  {
    currNode->left = deleteNodeHelper(currNode->left, value);
  }
  else if(value > currNode->title)
  {
    currNode->right = deleteNodeHelper(currNode->right, value);
  }
  // We found the node with the value
  else
  {
    //TODO Case : No child
    if(currNode->left == NULL && currNode->right == NULL)
    {
        delete currNode;
        currNode = NULL;
    }
    //TODO Case : Only right child
    else if(currNode->left == NULL)
    {
        ShowItem* temp = currNode->right;
        delete currNode;
        currNode = temp;

    }
    //TODO Case : Only left child
    else if(currNode->right == NULL)
    {
        ShowItem* temp = currNode->left;
        delete currNode;
        currNode = temp;
    }
    //TODO Case: Both left and right child
    else
    {
      ///Replace with Minimum from right subtree
        ShowItem* temp = getMinValueNode(currNode->right);
        currNode->title = temp->title; //i kind of want to change this
        currNode->year = temp->year;
        currNode->showRating = temp->showRating;
        currNode->userRating = temp->userRating;

        currNode ->right = deleteNodeHelper(temp, temp->title);
    }

  }
return currNode;

}



/* TODO */
void ShowCatalog::removeShow(std::string title)
{
    // TODO
    root = deleteNodeHelper(root, title);
}


ShowItem* getParent(ShowItem *current, string title){

if (current == NULL)
        return NULL;

    if (current->left->title == title || current->right->title == title)
        return current;

    if (current->title > title)
        return getParent(current->left, title);

    return getShowHelper(current->right, title);

}
/* TODO */
void ShowCatalog::rightRotate(std::string title)
{
    // TODO

    ShowItem* temp = getShowHelper(root, title);


}

/* TODO */
void ShowCatalog::leftRotate(std::string title)
{
    // TODO
    
    ShowItem* temp = getShowHelper(root, title);
    if(temp->left == NULL)
        return;
    ShowItem* temp2 = temp->right;
    
    temp->right = temp2->left;
    if(temp2->left!=NULL){
        ShowItem* temp3 = getParent(temp2->left, temp2->left->title);
        temp3->showRating = temp->showRating;
        temp3->title = temp->title;
        temp3->userRating = temp->userRating;
        temp3->year = temp->year;
    }
    ShowItem* temp4 = getParent(temp2, temp2->title);
    ShowItem* temp5 = getParent(temp, temp->title);
    temp4->showRating = temp5->showRating;
    temp4->title = temp5->title;
    temp4->userRating = temp5->userRating;
    temp4->year = temp5->year;


    if(temp5 == NULL){
        root = temp2;
    }
    else if(temp == temp5->left){
        temp5->left->showRating = temp2->showRating;
        temp5->left->title = temp2->title;
        temp5->left->userRating = temp2->userRating;
        temp5->left->year = temp2->year;
    }
    else{
        temp5->right->showRating = temp2->showRating;
        temp5->right->title = temp2->title;
        temp5->right->userRating = temp2->userRating;
        temp5->right->year = temp2->year;
    }
    temp2->left->showRating = temp->showRating;
    temp2->left->title = temp->title;
    temp2->left->userRating = temp->userRating;
    temp2->left->year = temp->year;
    temp5->showRating = temp2->showRating;
    temp5->title = temp2->title;
    temp5->userRating = temp->userRating;
    temp5->year = temp->year;
}
