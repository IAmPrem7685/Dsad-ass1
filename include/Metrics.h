#ifndef METRICS_H
#define METRICS_H

#include <string>
#include <vector>

// Class to track performance metrics for hash table operations.
class Metrics
{
public:
    Metrics();

    // Metrics: <total probes, total operations>.
    std::pair<int, int> insertMetrics;
    std::pair<int, int> successSearchMetrics;
    std::pair<int, int> unsuccessfulSearchMetrics;
    std::pair<int, int> successRemoveMetrics;
    std::pair<int, int> unsuccessfulRemoveMetrics;

    // Increment probe counts for each operation type.
    void incrementInsertProbes();
    void incrementSuccessSearchProbes(int probCount = 1);
    void incrementUnsuccessSearchProbes(int probCount = 1);
    void incrementSuccessRemoveProbes(int probCount = 1);
    void incrementUnsuccessRemoveProbes(int probCount = 1);

    // Increment operation counts.
    void incrementInsertOpr();
    void incrementSuccessSearchOpr();
    void incrementUnsuccessSearchOpr();
    void incrementSuccessRemoveOpr();
    void incrementUnsuccessRemoveOpr();

    // Get average number of probes for each operation.
    double getAverageInsertProbes() const;
    double getAverageSuccessSearchProbes() const;
    double getAverageUnsuccessSearchProbes() const;
    double getAverageTotalSearchProbes() const;
    double getAverageSuccessRemoveProbes() const;
    double getAverageUnsuccessRemoveProbes() const;
    double getAverageTotalRemoveProbes() const;
};

#endif // METRICS_H
