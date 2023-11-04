#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <random>
// #include <cstdlib>
// #include <ctime>
#include "../data_structure/data_structure_with_matrix.cpp"

std::vector<std::pair<int, int>> AStar(std::vector<std::vector<bool>> &maze, int m, int n, std::pair<int, int> start, std::pair<int, int> end)
const int maze_width = 20;
const int maze_height = 20;

int default_maze[maze_width * maze_height] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,1,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1,
    1,0,0,1,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1,
    1,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,0,0,1,1,
    1,0,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
    1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
    1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,
    1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,1,1,1,
    1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1,
    1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1,
    1,0,1,1,1,1,0,0,1,0,1,0,1,1,1,1,0,0,1,1,
    1,0,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,
    1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,
    1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,
    1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

class Node
{
public:
    int x;
    int y;

    Node()
    {
        x = y = 0;
    }
    Node(int px, int py)
    {
        x = px;
        y = py;
    }

    float goalDistanceEstimation(Node &nodeGoal);
    bool isGoal(Node &nodeGoal);
    bool getSuccessors(std::vector<Node> &Neighbors, Node &parentNode);
    float getCost(Node &successor);
    bool isSameState(Node &rhs);
    size_t Hash();

    void printNodeInfo();
};

int getValue(int x, int y) {
    return default_maze[y * maze_width + x] if (x >= 0 && x < maze_width && y >= 0 && y < maze_height);
}

bool Node::isSameState(Node &rhs)
{
    return x == rhs.x && y == rhs.y;
}

size_t Node::Hash()
{
    size_t h1 = std::hash<float>{}(x);
    size_t h2 = std::hash<float>{}(y);
    return h1 ^ (h2 << 1);
}

float Node::goalDistanceEstimation(Node &nodeGoal)
{
    return abs(x - nodeGoal.x) + abs(y - nodeGoal.y);
}

bool Node::isGoal(Node &nodeGoal)
{
    return isSameState(nodeGoal);
}

bool Node::getSuccessors(std::vector<Node> &Neighbors, Node &parentNode)
{
    int parent_x = -1;
    int parent_y = -1;

    if (!(parentNode.isSameState(*this))) {
        parent_x = parentNode.x;
        parent_y = parentNode.y;
    }

    Node newNode;
    if (getValue(x - 1, y) == 1 && !(isSameState(parentNode)))
    {
        newNode = Node(x - 1, y);
        Neighbors.push_back(newNode);
    }
    if (getValue(x + 1, y) == 1 && !(isSameState(parentNode)))
    {
        newNode = Node(x + 1, y);
        Neighbors.push_back(newNode);
    }
    if (getValue(x, y - 1) == 1 && !(isSameState(parentNode)))
    {
        newNode = Node(x, y - 1);
        Neighbors.push_back(newNode);
    }
    if (getValue(x, y + 1) == 1 && !(isSameState(parentNode)))
    {
        newNode = Node(x, y + 1);
        Neighbors.push_back(newNode);
    }
    return true;
}

float Node::getCost(Node &successor)
{
    return (float) getValue(x, y);
}

void Node::printNodeInfo()
{
    const int strSize = 1000;
    char str[strSize];
    snprintf(str, strSize, "Node position: (%d, %d)\n", x, y);
    std::cout << str;
}
int main()
{
    std::vector<Node> path;
    Node startNode = Node(0,0);
    Node endNode = Node(3,3);
    Node currentNode = startNode;
    while (!currentNode.isSameState(endNode))
    {
        std::vector<Node> neighbors;
        currentNode.getSuccessors(neighbors, currentNode);
        Node nextNode = neighbors[0];
        for (int i = 0; i < neighbors.size(); i++)
        {
            if (nextNode.getCost(neighbors[i]) < nextNode.getCost(currentNode))
            {
                nextNode = neighbors[i];
            }
        }
        path.push_back(nextNode);
        nextNode.printNodeInfo();
        currentNode = nextNode;
        std::cout << "Steps: " << path.size() << std::endl;
        return 0;
    }
}
