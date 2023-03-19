#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <stdexcept>
#include "GatorTaxi.h"

class Ride
{
public:
    int rideNumber;
    int rideCost;
    int tripDuration;

    Ride(int rideNumber, int rideCost, int tripDuration)
        : rideNumber(rideNumber), rideCost(rideCost), tripDuration(tripDuration) {}
};

// Comparator for min heap
struct RideComparator
{
    bool operator()(const Ride &a, const Ride &b)
    {
        if (a.rideCost == b.rideCost)
            return a.tripDuration > b.tripDuration;
        return a.rideCost > b.rideCost;
    }
};

class MinHeap
{
private:
    std::vector<Ride> heap;

public:
    MinHeap() {}

    void insert(Ride ride)
    {
        heap.push_back(ride);
        std::push_heap(heap.begin(), heap.end(), RideComparator());
    }

    Ride removeMin()
    {
        if (heap.empty())
            throw std::runtime_error("No active ride requests");

        std::pop_heap(heap.begin(), heap.end(), RideComparator());
        Ride minRide = heap.back();
        heap.pop_back();
        return minRide;
    }

    void removeRide(int rideNumber)
    {
        auto it = std::find_if(heap.begin(), heap.end(), [&](const Ride &ride)
                               { return ride.rideNumber == rideNumber; });
        if (it != heap.end())
        {
            heap.erase(it);
            std::make_heap(heap.begin(), heap.end(), RideComparator());
        }
    }

    bool isEmpty()
    {
        return heap.empty();
    }
};

enum Color
{
    RED,
    BLACK
};

class RBTNode
{
public:
    Ride data;
    RBTNode *parent;
    RBTNode *left;
    RBTNode *right;
    Color color;

    RBTNode(Ride data) : data(data), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}
};

class RedBlackTree
{
private:
    RBTNode *root;
    RBTNode *NIL;

    void leftRotate(RBTNode *x)
    {
        RBTNode *y = x->right;
        x->right = y->left;

        if (y->left != NIL)
            y->left->parent = x;
        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(RBTNode *y)
    {
        RBTNode *x = y->left;
        y->left = x->right;

        if (x->right != NIL)
            x->right->parent = y;
        x->parent = y->parent;

        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        // else
        //     y->parent->left;
        x->right = y;
        y->parent = x;
    }

    void insertFixup(RBTNode *z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                RBTNode *y = z->parent->parent->right;
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                RBTNode *y = z->parent->parent->left;
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void insertRBT(RBTNode *z)
    {
        RBTNode *y = NIL;
        RBTNode *x = root;

        while (x != NIL)
        {
            y = x;
            if (z->data.rideNumber < x->data.rideNumber)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == NIL)
            root = z;
        else if (z->data.rideNumber < y->data.rideNumber)
            y->left = z;
        else
            y->right = z;

        z->left = NIL;
        z->right = NIL;
        z->color = RED;
        insertFixup(z);
    }

    void transplant(RBTNode *u, RBTNode *v)
    {
        if (u->parent == NIL)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    RBTNode *treeMinimum(RBTNode *x)
    {
        while (x->left != NIL)
            x = x->left;
        return x;
    }

    void deleteFixup(RBTNode *x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                RBTNode *w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                RBTNode *w = x->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void deleteRBT(RBTNode *z)
    {
        RBTNode *y = z;
        RBTNode *x;
        Color y_original_color = y->color;

        if (z->left == NIL)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == NIL)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = treeMinimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (y_original_color == BLACK)
            deleteFixup(x);
    }

public:
    RedBlackTree()
    {
        NIL = new RBTNode(Ride(-1, -1, -1));
        NIL->color = BLACK;
        root = NIL;
    }

    void insert(Ride ride)
    {
        RBTNode *newNode = new RBTNode(ride);
        insertRBT(newNode);
    }

    void remove(int rideNumber)
    {
        RBTNode *node = search(rideNumber);
        if (node != NIL)
            deleteRBT(node);
    }

    RBTNode *search(int rideNumber)
    {
        RBTNode *node = root;
        while (node != NIL && rideNumber != node->data.rideNumber)
        {
            if (rideNumber < node->data.rideNumber)
                node = node->left;
            else
                node = node->right;
        }
        return node;
    }

    void printRange(RBTNode *node, int rideNumber1, int rideNumber2, std::vector<Ride> &rides)
    {
        if (node == NIL)
            return;

        if (rideNumber1 < node->data.rideNumber)
            printRange(node->left, rideNumber1, rideNumber2, rides);

        if (rideNumber1 <= node->data.rideNumber && node->data.rideNumber <= rideNumber2)
            rides.push_back(node->data);

        if (node->data.rideNumber < rideNumber2)
            printRange(node->right, rideNumber1, rideNumber2, rides);
    }

    std::vector<Ride> printRange(int rideNumber1, int rideNumber2)
    {
        std::vector<Ride> rides;
        printRange(root, rideNumber1, rideNumber2, rides);
        return rides;
    }
};

GatorTaxi::GatorTaxi()
{
    // Initialize your data structures (min-heap and Red-Black Tree) here, if necessary
}

void GatorTaxi::executeCommand(const std::string &command)
{
    // Parse the command string and execute the corresponding GatorTaxi class methods
    // You need to implement the logic to parse the input and call the correct methods with the correct arguments

    std::cout << "Executing command: " << command << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
    std::ifstream infile(input_file);

    if (!infile.is_open())
    {
        std::cerr << "Error opening input file: " << input_file << std::endl;
        return 1;
    }

    GatorTaxi gatorTaxi;

    // Read input file and process each line
    std::string line;
    while (std::getline(infile, line))
    {
        // Parse and execute commands from the input file
        // You will need to implement a function to parse the input and execute the corresponding GatorTaxi class methods
        gatorTaxi.executeCommand(line);
    }

    infile.close();

    return 0;
}