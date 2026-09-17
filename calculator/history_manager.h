#ifndef CALCULATOR_HISTORY_MANAGER_H
#define CALCULATOR_HISTORY_MANAGER_H

#include <string>
#include <vector>
#include <memory>

namespace calculator {

// History entry structure
struct HistoryEntry {
    std::string expression;
    double result;
    
    HistoryEntry(const std::string& expr, double res) : expression(expr), result(res) {}
};

// History manager class
class HistoryManager {
private:
    std::vector<HistoryEntry> history;
    size_t maxHistorySize;
    
public:
    explicit HistoryManager(size_t maxSize = 20);
    
    // Add a new calculation to history
    void addEntry(const std::string& expression, double result);
    
    // Get history entries
    const std::vector<HistoryEntry>& getHistory() const;
    
    // Get specific entry by index
    HistoryEntry getEntry(size_t index) const;
    
    // Get number of entries
    size_t size() const;
    
    // Clear history
    void clear();
    
    // Get maximum history size
    size_t getMaxSize() const;
};

} // namespace calculator

#endif // CALCULATOR_HISTORY_MANAGER_H