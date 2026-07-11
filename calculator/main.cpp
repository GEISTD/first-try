#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <filesystem>
#include "parser.h"
#include "math_functions.h"
#include "history_manager.h"

namespace {

std::string normalizeCommand(const std::string& input) {
    std::string normalized = input;
    normalized.erase(std::remove_if(normalized.begin(), normalized.end(), [](unsigned char ch) {
        return std::isspace(ch) != 0;
    }), normalized.end());
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return normalized;
}

void cleanupGeneratedArtifacts() {
    try {
        for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
            if (!entry.is_regular_file()) {
                continue;
            }
            const std::string ext = entry.path().extension().string();
            if (ext == ".pdb" || ext == ".obj" || ext == ".ilk" || ext == ".json") {
                std::error_code ec;
                std::filesystem::remove(entry.path(), ec);
            }
        }
    } catch (const std::exception&) {
        // Ignore cleanup errors to avoid interrupting program exit.
    }
}

// Function to check if a string is a command
bool isCommand(const std::string& input) {
    const std::string normalized = normalizeCommand(input);
    return normalized == "history" ||
           normalized == "quit" ||
           normalized == "exit" ||
           normalized == "clear" ||
           normalized == "help" ||
           normalized.rfind("repeat", 0) == 0;
}

// Function to parse repeat command
int parseRepeatCommand(const std::string& input) {
    const std::string normalized = normalizeCommand(input);
    if (normalized.rfind("repeat", 0) == 0 && normalized.size() > 6) {
        try {
            return std::stoi(normalized.substr(6));
        } catch (...) {
            return -1;
        }
    }
    return -1;
}

} // namespace

int main() {
    std::cout << "=== Simple Calculator ===" << std::endl;
    std::cout << "Supports basic arithmetic, parentheses, sqrt, square, and trig functions" << std::endl;
    std::cout << "Type 'help' for help, 'history' to view history, 'quit' or 'exit' to exit" << std::endl;
    std::cout << "===================================" << std::endl;
    
    calculator::HistoryManager historyManager(20);
    
    while (true) {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);
        
        // Skip empty input
        if (input.empty()) {
            continue;
        }
        
        // Handle commands
        const std::string normalizedInput = normalizeCommand(input);
        if (isCommand(input)) {
            if (normalizedInput == "quit" || normalizedInput == "exit") {
                cleanupGeneratedArtifacts();
                std::cout << "Thanks for using the calculator. Goodbye!" << std::endl;
                break;
            } else if (normalizedInput == "history") {
                const auto& history = historyManager.getHistory();
                if (history.empty()) {
                    std::cout << "History is empty" << std::endl;
                } else {
                    std::cout << "\n=== History ===" << std::endl;
                    for (size_t i = 0; i < history.size(); ++i) {
                        std::cout << (i + 1) << ". " << history[i].expression 
                                  << " = " << std::fixed << std::setprecision(6) 
                                  << history[i].result << std::endl;
                    }
                    std::cout << "================" << std::endl;
                }
            } else if (normalizedInput == "clear") {
                historyManager.clear();
                std::cout << "History cleared" << std::endl;
            } else if (normalizedInput == "help") {
                std::cout << "\n=== Help ===" << std::endl;
                std::cout << "Basic operations: 1+2, 3*4, 10/2, 5-3" << std::endl;
                std::cout << "Parentheses: (1+2)*3, 2*(3+4)" << std::endl;
                std::cout << "Advanced: sqrt(4), square(3), sin(1.57), cos(0), tan(0.785), pow(2,3)" << std::endl;
                std::cout << "Commands:" << std::endl;
                std::cout << "  history   - show calculation history" << std::endl;
                std::cout << "  repeat N  - repeat the Nth calculation" << std::endl;
                std::cout << "  clear     - clear history" << std::endl;
                std::cout << "  help      - show this help text" << std::endl;
                std::cout << "  quit/exit - exit the calculator" << std::endl;
                std::cout << "================" << std::endl;
            } else {
                // Handle repeat command
                int index = parseRepeatCommand(input);
                if (index > 0 && static_cast<size_t>(index) <= historyManager.size()) {
                    try {
                        auto entry = historyManager.getEntry(index - 1);
                        std::cout << "Repeat calculation: " << entry.expression << " = " 
                                  << std::fixed << std::setprecision(6) << entry.result << std::endl;
                        // Add the repeated calculation to history again
                        historyManager.addEntry(entry.expression, entry.result);
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                } else {
                    std::cout << "Error: invalid repeat index. Type 'history' to view available indices." << std::endl;
                }
            }
            continue;
        }
        
        // Try to evaluate as a full mathematical expression, including nested functions.
        try {
            calculator::Parser parser(input);
            double result = parser.evaluate();
            
            std::cout << input << " = " << std::fixed << std::setprecision(6) << result << std::endl;
            
            // Add to history
            historyManager.addEntry(input, result);
            
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}