/**
 * HOMEWORK 6 Programming Project
 * CSE 331
 * 
 * Author: Daniel Thompson
 * MSU ID: A43550656
 * 
 * TO COMPILE:
 * g++ bsf.cpp -o bsf
 * !!OR!!
 * make 
 * 
 * TO RUN:
 * ./bsf <graph file> <starting node>
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

#define WHITE 0
#define GREEN  1
#define RED 2

/** \brief: Class for a node
 */
class Node
{
    private:
        /// Value held by node
        int key;
        /// List of all adjacent nodes
        vector<Node *> adjacentNodes;
        /// Number of adjacent nodes
        int numOfAd;
        /// Visited state
        int state;
        /// Parent Node
        Node * parent;
        /// Distance from parent node
        int dist;

    public:
        /** 
         * \Constructor
         */
        Node(){ numOfAd = 0; parent = NULL; state = WHITE;}
        
        /** 
         * \Destructor
         */
        ~Node(){}
        
        /** 
         * \brief Sets the key of node
         * \param: integer
         */
        void setKey(int x) { key = x; }
        
        /** 
         * \brief Adds a left subtree to the node
         * \param: Address to subtree
         */
        void addAdjacentNode(Node* n){ adjacentNodes.push_back(n); numOfAd +=1;}
        
        /** 
         * \brief Gets the key of node
         * \returns: key
         */
        int getKey() { return key; }
        
        vector<Node*> getAdjacentNodes() { return adjacentNodes; }
        
        void goGreen() { state = GREEN; }
        void goRed() { state = RED; }
        
        int getState() { return state; }
        
        void setParentNode(Node* n) { parent = n; }
        void setDistance(int d) { dist = d; }
	
        int getDistance() { return dist; }
        Node* getParent() { return parent; }
};

/**
 * \brief: Finds a node with a certain key
 * \param: key, v
 * \returns: pointer to Node
 */
Node* findNode(int key, vector<Node*>* v)
{
    for(int i = 0; i < v->size(); i++)
    {
        if(v->at(i)->getKey() == key)
            return v->at(i);
    }
    return NULL;
}
/**
 * \brief: Sends nodes through bfs
 * \param: start, output
 */
void bfs(Node *start, vector<Node*>* output)
{
    start->setParentNode(NULL);
    start->setDistance(0);
    vector<Node*> queue;
    
    queue.push_back(start);
    
    Node* v;
    while(!queue.empty())
    {
        v = queue[0];
        queue.erase(queue.begin());
        output->push_back(v);
        v->goRed();
        for(int x = 0; x < v->getAdjacentNodes().size(); x++)
        {
            if(v->getAdjacentNodes()[x]->getState()==WHITE)
            {
                queue.push_back(v->getAdjacentNodes()[x]);
                v->getAdjacentNodes()[x]->goGreen();
                v->getAdjacentNodes()[x]->setDistance(v->getDistance() + 1);
                v->getAdjacentNodes()[x]->setParentNode(v);
            }
        }
    }
    
}

/** \brief: main function
 * Takes in a file, makes the graph through nodes, and sends the start node
 * through bfs function
 */
int main(int argc, char *argv[]) 
{
   // Check for right number of arguments
    if(argc != 3){
        cout << "\nUSAGE: " << argv[0] << " <graph filename> <starting node key>\n" << endl;
        return 0;
    }
    
    //Open file for reading
    ifstream input ( argv[1] );
    // Check for valid input
    if ( !input.is_open() ){
        cout<<"Could not open graph file: "<< argv[1] << endl;
        return 0;
    }
    
    
    //Setup for file read
    bool firstLine = true;
    int numberOfNodes, nodeKey, index;
    string line, adjacentString;
    vector<Node*> nodes;
    
    // Check each line
    while(getline(input, line))
    {
        //If first line, make a vector of Nodes
        if(firstLine)
        {
            numberOfNodes = atoi(line.c_str());
            for(int i = 1; i <= numberOfNodes; i++)
            {
                nodes.push_back(new Node());
            }
            firstLine = false;
            index = 0;
        } else
        {
            nodeKey = atoi(line.substr(0, line.find(":")).c_str());
            nodes[index]->setKey(nodeKey);
            index += 1;
        } 
    }
    
    // Let's read the file again
    ifstream input2 ( argv[1] );
    // Check for valid input
    if ( !input.is_open() ){
        cout<<"Could not open graph file: "<< argv[1] << endl;
        return 0;
    }
    //Don't need the first line again
    getline(input2,line);
    
    
    while(getline(input2,line))
    {
        nodeKey = atoi(line.substr(0, line.find(":")).c_str());
        Node* n = findNode(nodeKey, &nodes);
        if(n == NULL)
            continue;
        adjacentString = line.substr(line.find(":") + 1, line.length());
        istringstream iss(adjacentString);
        string keyS;
        while(iss >> keyS){
            int key = atoi(keyS.c_str());
            Node* adjacent = findNode(key, &nodes);
            if(adjacent == NULL)
                continue;
            n->addAdjacentNode(adjacent);
        }
    }
    
    // Get the starting node and output vector
    Node* start = findNode(atoi(argv[2]), &nodes);
    vector<Node*> output;
    
    //BFS!!!
    bfs(start, &output);
    
    int i;
    //Output
    cout << "D: ";
    for(i=0; i<output.size(); i++){ cout << output[i]->getKey() << " ";}
    cout << endl;
    for(i=0; i<output.size(); i++)
    { 
        if(output[i]->getParent() != NULL)
            cout << output[i]->getKey() << ".p=" << output[i]->getParent()->getKey() << ", ";
        else
            cout << output[i]->getKey() << ".p=NULL" << ", ";
    
    }
    cout << endl;
    for(i=0; i<output.size(); i++){ cout << output[i]->getKey() << ".d=" << output[i]->getDistance() << ", ";}
    cout << endl;
    
    for(int i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
    nodes.clear();
}