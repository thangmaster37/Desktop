// __Author: Pham Ngoc Hai _ Harito__
// #pragma once
#include <vector>
#include <utility>
// #include <bits/stdc++.h> // find max element of a array: *max_element(a.begin(), a.end());
#include <cstdlib>   // create random value: srand(time(NULL)); int answer = std::rand() % 20; - create a random value from 0 to 20
#include <algorithm> // find index of max element in vector

#include "Maze.cpp"
#include "Object.cpp"
#include "algo/AStar.cpp"
#include "algo/ACO.cpp"

class Problem
{
public:
    Maze maze;
    std::pair<std::pair<int, int>, std::pair<int, int>> startEnd;
    std::vector<std::pair<Object, bool>> objects;
    std::unordered_map<std::pair<int, int>, std::pair<int, int>, AStar::HashPairAStar> aStarPath;
    std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, double, ACO::HashPairACO> acoMap;
    std::pair<double, double> result; // <time from start to end; percent reached end point>

public:
    Problem(std::pair<int, int> shape, int numberObject)
    {
        maze = Maze(shape);
        startEnd = maze.selectStartAndEnd();
        std::cout << "Create maze and start-end point successful" << std::endl;
        for (int i = 0; i < numberObject; ++i)
        {
            Object object(startEnd.first);
            objects.push_back(std::make_pair(object, false)); // object hadn't dead yet
        }
        std::cout << "Create objects successful" << std::endl;
    }

    void preDyMazeSerial(AStar &astar, ACO &aco)
    {
        // Use A* fine optimize path - return map
        aStarPath = astar.solve_serial(maze, startEnd.first, startEnd.second).second;
        std::cout << "Got A*'s optimize path in serial way" << std::endl;
        // Use ACO get pheromone map - return map
        acoMap = aco.solve_serial(maze, startEnd.first, startEnd.second).second;
        std::cout << "Got ACO's pheromone map in serial way" << std::endl;
    }

    void preDyMazeParallel(AStar &astar, ACO &aco)
    {
        // Use A* fine optimize path - return map
        aStarPath = astar.solve_serial(maze, startEnd.first, startEnd.second).second;
        std::cout << "Got A*'s optimize path in parallel way" << std::endl;
        // Use ACO get pheromone map - return map
        acoMap = aco.solve_parallel(maze, startEnd.first, startEnd.second).second;
        std::cout << "Got ACO's pheromone map in parallel way" << std::endl;
    }

    // Algorithms
    std::vector<std::pair<Object, bool>> &getObjects()
    {
        return objects;
    }

    Maze &getMaze()
    {
        return maze;
    }

    std::pair<std::pair<int, int>, std::pair<int, int>> &getStatEnd()
    {
        return startEnd;
    }

    bool stopCondition()
    {
        for (auto &object : objects)
        {
            if (object.second == false)
            {
                return false;
            }
        }
        return true;
    }

    void getChoice(std::pair<Object, bool> &object)
    {
        std::vector<std::pair<int, int>> neighbors = maze.getNeighbors(object.first.currentPoint());
        if (neighbors.empty())
        {
            object.second = true; // Object dead
            return;
        }
        std::cout << neighbors.size() << std::endl;
        for (auto &neighbor : neighbors)
        {
            std::cout << neighbor.first << " " << neighbor.second << std::endl;
        }
        std::vector<double> probities(neighbors.size());
        for (int i = 0; i < neighbors.size(); ++i)
        {
            if (neighbors[i] == startEnd.second)
            // if (neighbors.at(i).first == startEnd.second.first && neighbors.at(i).second == startEnd.second.second)
            {
                // Object get target point
                object.first.move(neighbors[i]);
                object.first.gotTarget();
                object.second = true; // Object got target point
                std::cout << object.first.currentPoint().first << "-" << object.first.currentPoint().second << " " << object.second << " <-> " << object.first.isTarget() << " " << object.first.length() << std::endl;
                return;
            }
            if (acoMap.find(std::make_pair(object.first.currentPoint(), neighbors.at(i))) != acoMap.end())
            {
                probities[i] += ((double)rand() / RAND_MAX) * (acoMap.find(std::make_pair(object.first.currentPoint(), neighbors.at(i)))->second);
            }
            if (aStarPath.find(object.first.currentPoint())->second == neighbors[i])
            {
                // The way go to neighbor is a part of aStarPath
                probities[i] *= ((double)rand() / RAND_MAX + 1);
            }
        }
        auto maxProbityIndex = std::max_element(probities.begin(), probities.end()) - probities.begin();
        object.first.move(neighbors[maxProbityIndex]);
        std::cout << object.first.currentPoint().first << "-" << object.first.currentPoint().second << " " << object.second << " <-> " << object.first.isTarget() << " " << object.first.length() << std::endl;
    }
};

int main()
{
    srand(time(NULL));
    // 0. Create maze with custom size. Choose start and end point
    std::pair<int, int> shape = {15, 15};
    int numberObject = 3;
    Problem problem(shape, numberObject);
    problem.getMaze().print();
    std::cout << problem.getStatEnd().first.first << "-" << problem.getStatEnd().first.second << " " << problem.getStatEnd().second.first << "-" << problem.getStatEnd().second.second << std::endl;
    // 1. Prepare work on static maze
    AStar astar;
    ACO aco;
    problem.preDyMazeSerial(astar, aco);
    // 2. Start main problem in dynamic maze
    // Condition to stop while loop:
    // +    All maze have no more path to go <-> every object that haven't reach target yet have the neighbors list = {}
    // +    All object reached the target <-> every object have getTarget property = true
    while (!problem.stopCondition())
    {
        // Each object consider it's choice
        for (auto &object : problem.getObjects())
        {
            problem.getChoice(object);
        }
        problem.getMaze().changeMaze(0.01, 0.0);
        problem.getMaze().print();
    }

    std::cout << "RESULT: \n";
    for (auto &object : problem.getObjects())
    {
        std::cout << object.first.currentPoint().first << "-" << object.first.currentPoint().second << " " << object.second << " <-> " << object.first.isTarget() << " " << object.first.length() << std::endl;
    }

    return 0;
}
