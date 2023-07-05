#include <iostream>
#include <gtest/gtest.h>
#include "../src/include/InputHandler.h"
#include <chrono>
#include <vector>
#include <fstream>
#include <numeric>

#ifdef _WIN32
#include <Windows.h>
#define MAX_PATH_LENGTH 260 // Maximum path length on Windows
#else
#include <unistd.h>
#endif

std::string GetCurrentWorkingDirectory()
{
    std::string cwd;
#ifdef _WIN32
    char buffer[MAX_PATH_LENGTH];
    GetCurrentDirectoryA(MAX_PATH_LENGTH, buffer);
    cwd = buffer;
#else
    char buffer[PATH_MAX];
    if (getcwd(buffer, PATH_MAX) != nullptr)
        cwd = buffer;
#endif
    return cwd;
}

TEST(TetrisTests, PollingWCET)
{
    InputHandler inputHandler;

    // Perform the keyboard input polling multiple times
    const int numIterations = 10000;

    // Logging
    std::vector<long long> timeArray;
    timeArray.reserve(numIterations);

    for (int i = 0; i < numIterations; i++)
    {
        auto iterationStartTime = std::chrono::high_resolution_clock::now();
        // Call the method
        char key = inputHandler.pollingServer();
        auto iterationEndTime = std::chrono::high_resolution_clock::now();
        auto iterationDuration = std::chrono::duration_cast<std::chrono::microseconds>(iterationEndTime - iterationStartTime).count();
        timeArray.push_back(iterationDuration);
    }

    auto minDuration = *std::min_element(timeArray.begin(), timeArray.end());
    auto maxDuration = *std::max_element(timeArray.begin(), timeArray.end());
    auto sumDuration = std::accumulate(timeArray.begin(), timeArray.end(), 0LL);

    std::cout 
        << "PollingWCET | Iterations: " << numIterations << " | "
        << "Average: " << sumDuration / numIterations << " | "
        << "Minimum: " << minDuration << " | "
        << "Maximum: " << maxDuration << " | "
        << "Microseconds "
        << std::endl;

    // Save durations to a file
    std::ofstream outputFile("PollingWCET.txt");
    if (outputFile.is_open())
    {
        for (const auto& duration : timeArray)
        {
            outputFile << duration << std::endl;
        }
        outputFile.close();
        
        std::cout << "WCET file saved to: " << GetCurrentWorkingDirectory() << std::endl;
    }
    else
    {
        std::cout << "Unable to open file, results not written!" << std::endl;
    }
}