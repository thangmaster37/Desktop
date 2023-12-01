// __Author: Pham Ngoc Hai _ Harito__
// #pragma once
#include <vector>
#include <utility>
#include <bits/stdc++.h> // find max element of a array: *max_element(a.begin(), a.end());
#include <cstdlib>       // create random value: srand(time(NULL)); int answer = std::rand() % 20; - create a random value from 0 to 20
#include <algorithm>     // find index of max element in vector

#include "Maze.cpp"
#include "Object.cpp"
#include "algo/AStar.cpp"
#include "algo/ACO.cpp"

class Problem
{
private:
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

    void preDyMazeSerial(AStar astar, ACO aco)
    {
        // Use A* fine optimize path - return map
        aStarPath = astar.solve_serial(maze, startEnd.first, startEnd.second).second;
        std::cout << "Got A*'s optimize path in serial way" << std::endl;
        // Use ACO get pheromone map - return map
        acoMap = aco.solve_serial(maze, startEnd.first, startEnd.second).second;
        std::cout << "Got ACO's pheromone map in serial way" << std::endl;
    }

    // void preDyMazeParallel(AStar astar, ACO aco)
    // {
    //     // Use A* fine optimize path - return map
    //     aStarPath = astar.solve_parallel(maze, startEnd.first, startEnd.second).second;
    //     std::cout << "Got A*'s optimize path in parallel way" << std::endl;
    //     // Use ACO get pheromone map - return map
    //     acoMap = aco.solve_parallel(maze, startEnd.first, startEnd.second).second;
    //     std::cout << "Got ACO's pheromone map in parallel way" << std::endl;
    // }

    // Algorithms
    std::vector<std::pair<Object, bool>> getObjects()
    {
        return objects;
    }

    Maze getMaze()
    {
        return maze;
    }

    bool stopCondition()
    {
        for (auto object : objects)
        {
            if (object.second == false)
            {
                return false;
            }
        }
        return true;
    }

    void getChoice(std::pair<Object, bool> object)
    {
        std::vector<std::pair<int, int>> neighbors = maze.getNeighbors(object.first.currentPoint());
        if (neighbors.size() == 0)
        {
            object.second = true; // Object dead
            return;
        }
        std::vector<double> probities(neighbors.size());
        for (int i = 0; i < neighbors.size(); ++i)
        {
            if (neighbors[i] == startEnd.second)
            {
                // Object get target point
                object.first.move(neighbors[i]);
                object.first.gotTarget();
                object.second = true; // Object got target point
                return;
            }
            srand(time(NULL));
            if (aStarPath.find(object.first.currentPoint())->second == neighbors[i])
            {
                // The way go to neighbor is a part of aStarPath
                probities[i] += std::rand() % 100 * 100;
            }
            // if (acoMap.find(object.currentPoint(), neighbors[i]) != acoMap.end()){
            probities[i] += std::rand() % 200 * (acoMap.find(std::pair<object.first.currentPoint(), neighbors[i]>)->second);
            // }
        }
        auto maxProbityIndex = std::max_element(probities.begin(), probities.end()) - probities.begin();
        object.first.move(neighbors[maxProbityIndex]);
    }
};

int main()
{
    // 0. Create maze with custom size. Choose start and end point
    std::pair<int, int> shape = {5, 5};
    int numberObject = 50;
    Problem problem(shape, numberObject);
    // 1. Prepare work on static maze
    AStar astar;
    ACO aco;
    problem.preDyMazeSerial(astar, aco);
    // 2. Start main problem in dynamic maze
    // Condition to stop while loop:
    // +    All maze have no more path to go <-> every object that haven't reach target yet have the neighbors list = {}
    // +    All object reached the target <-> every object have getTarget property = true
    bool noPath = false;
    bool allReached = false;
    while (problem.stopCondition())
    {
        // Each object consider it's choice
        for (auto object : problem.getObjects())
        {
            problem.getChoice(object);
        }
        problem.getMaze().changeMaze(0.03, 0);
        problem.getMaze().print();
    }
    return 0;
}
