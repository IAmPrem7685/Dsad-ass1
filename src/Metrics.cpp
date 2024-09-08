#include "Metrics.h"
#include <iostream>

// Constructor initializes all metrics to (0, 0)
Metrics::Metrics() : insertMetrics(0, 0), successSearchMetrics(0, 0), unsuccessfulSearchMetrics(0, 0), successRemoveMetrics(0, 0), unsuccessfulRemoveMetrics(0, 0) {}

// Increment insert probes
void Metrics::incrementInsertProbes() { insertMetrics.first++; }

// Increment successful search probes by probCount
void Metrics::incrementSuccessSearchProbes(int probCount) { successSearchMetrics.first += probCount; }

// Increment unsuccessful search probes by probCount
void Metrics::incrementUnsuccessSearchProbes(int probCount) { unsuccessfulSearchMetrics.first += probCount; }

// Increment successful remove probes by probCount
void Metrics::incrementSuccessRemoveProbes(int probCount) { successRemoveMetrics.first += probCount; }

// Increment unsuccessful remove probes by probCount
void Metrics::incrementUnsuccessRemoveProbes(int probCount) { unsuccessfulRemoveMetrics.first += probCount; }

// Increment number of insert operations
void Metrics::incrementInsertOpr() { insertMetrics.second++; }

// Increment number of successful search operations
void Metrics::incrementSuccessSearchOpr() { successSearchMetrics.second++; }

// Increment number of unsuccessful search operations
void Metrics::incrementUnsuccessSearchOpr() { unsuccessfulSearchMetrics.second++; }

// Increment number of successful remove operations
void Metrics::incrementSuccessRemoveOpr() { successRemoveMetrics.second++; }

// Increment number of unsuccessful remove operations
void Metrics::incrementUnsuccessRemoveOpr() { unsuccessfulRemoveMetrics.second++; }

// Get average probes for insert operations
double Metrics::getAverageInsertProbes() const { return (insertMetrics.second > 0) ? static_cast<double>(insertMetrics.first) / insertMetrics.second : 0.0; }

// Get average probes for successful search operations
double Metrics::getAverageSuccessSearchProbes() const { return (successSearchMetrics.second > 0) ? static_cast<double>(successSearchMetrics.first) / successSearchMetrics.second : 0.0; }

// Get average probes for unsuccessful search operations
double Metrics::getAverageUnsuccessSearchProbes() const { return (unsuccessfulSearchMetrics.second > 0) ? static_cast<double>(unsuccessfulSearchMetrics.first) / unsuccessfulSearchMetrics.second : 0.0; }

double Metrics::getAverageTotalSearchProbes() const { return static_cast<double>((successSearchMetrics.first + unsuccessfulSearchMetrics.first) / (unsuccessfulSearchMetrics.second + successSearchMetrics.second)); }
// Get average probes for successful remove operations
double Metrics::getAverageSuccessRemoveProbes() const { return (successRemoveMetrics.second > 0) ? static_cast<double>(successRemoveMetrics.first) / successRemoveMetrics.second : 0.0; }

// Get average probes for unsuccessful remove operations
double Metrics::getAverageUnsuccessRemoveProbes() const { return (unsuccessfulRemoveMetrics.second > 0) ? static_cast<double>(unsuccessfulRemoveMetrics.first) / unsuccessfulRemoveMetrics.second : 0.0; }

double Metrics::getAverageTotalRemoveProbes() const { return static_cast<double>((successRemoveMetrics.first + unsuccessfulRemoveMetrics.first) / (unsuccessfulRemoveMetrics.second + successRemoveMetrics.second)); }
