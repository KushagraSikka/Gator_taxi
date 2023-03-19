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
        else
            y->parent->left = x;

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

public:
    RedBlackTree()
    {
        NIL = new RBTNode(Ride(-1, INT_MAX, INT_MAX));
        NIL->color = BLACK;
        root = NIL;
    }

    void insert(Ride data)
    {
        RBTNode *z = new RBTNode(data);
        RBTNode *y = NIL;
        RBTNode *x = root;

        while (x != NIL)
        {
            y = x;
            if (data.rideNumber < x->data.rideNumber)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == NIL)
            root = z;
        else if (data.rideNumber < y->data.rideNumber)
            y->left = z;
        else
            y->right = z;

        z->left = NIL;
        z->right = NIL;

        insertFixup(z);
    }

    // Other RedBlackTree functions, like delete, search, etc.
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./GatorTaxi <input_file>" << std::endl;
        return 1;
    }

    GatorTaxi gatorTaxi;
    std::string inputFilename(argv[1]);
    std::ifstream inputFile(inputFilename);
    std::string command;

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    while (std::getline(inputFile, command))
    {
        gatorTaxi.executeCommand(command);
    }

    inputFile.close();
    return 0;
}