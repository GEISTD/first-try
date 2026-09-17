#include "history_manager.h"
#include <algorithm>
#include <stdexcept>

namespace calculator {

HistoryManager::HistoryManager(size_t maxSize) : maxHistorySize(maxSize) {
    // Initialize with empty history
}

void HistoryManager::addEntry(const std::string& expression, double result) {
    // Add new entry
    history.emplace_back(expression, result);
    
    // Keep only the most recent entries
    if (history.size() > maxHistorySize) {
        history.erase(history.begin());
    }
}

const std::vector<HistoryEntry>& HistoryManager::getHistory() const {
    return history;
}

HistoryEntry HistoryManager::getEntry(size_t index) const {
    if (index >= history.size()) {
        throw std::out_of_range("History index out of range");
    }
    return history[index];
}

size_t HistoryManager::size() const {
    return history.size();
}

void HistoryManager::clear() {
    history.clear();
}

size_t HistoryManager::getMaxSize() const {
    return maxHistorySize;
}

} // namespace calculator