#include "Lexer.hpp"
#include "Executor.hpp"
#include <iostream>
#include <string>

int main() {
    Executor executor;
    std::string input;
    
    std::cout << "CSV Mini Database & Query Engine\n";
    std::cout << "Type a SELECT query ending with ';' or 'exit' to quit.\n";

    while (true) {
        std::cout << "\ncsv_db> ";
        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input == "exit" || input == "quit") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }

        try {
            Query query = Lexer::parse(input);
            executor.execute(query, std::cout);
        } catch (const std::exception& e) {
            std::cout << e.what() << "\n";
        }
    }

    return 0;
}
