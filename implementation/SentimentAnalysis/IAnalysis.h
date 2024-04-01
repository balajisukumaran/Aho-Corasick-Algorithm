#pragma once

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
};