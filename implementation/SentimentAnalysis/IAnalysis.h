#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <psapi.h>

/// <summary>
/// Interface to analysis
/// </summary>
class IAnalysis {
public:

    /// <summary>
    /// assign patterns for search
    /// </summary>
    virtual	void assignPatterns() = 0;

    /// <summary>
    /// Generate the report
    /// </summary>
    virtual	void generateReport() = 0;

    void updateMemoryUsage(size_t& memoryVariable) {
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            memoryVariable = pmc.WorkingSetSize;
        }
    }
};