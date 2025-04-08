#include <iostream>
#include <fstream>
#include <string>

void perform_optimal(std::string input[]);
void perform_fifo(std::string input[]);
std::string* read_file(std::ifstream& file);

int main() {
    // Initialize files
    std::ifstream fifo("FIFO.txt");
    std::ifstream opt("OPT.txt");

    // Read in files and store into input strings
    std::string* fifo_input = read_file(fifo);
    std::string* opt_input = read_file(opt);

    // Perform OPT algorithm


    // Perform FIFO algorithm


    // Delete memory
    delete[] fifo_input;
    delete[] opt_input;

    // Exit
    return 0;
}

std::string* read_file(std::ifstream& file) {
    // Initialize vars
    const int MAX = 20;
    std::string* input = new std::string[MAX];
    int index = 0;

    if (file.is_open()) {
        // Initialize vars
        std::string line;

        // Read in algo char and numbers
        while (std::getline(file, line)) {
            // Initialize num_string
            std::string num_string = "";

            // Store each number in numbers array
            for (int i = 0; i <= line.size(); i++) {
                // Parse on comma
                if (line[i] == ',' || i == line.size()-1) {
                    // Add last integer if it's the last in array
                    if (i == line.size() - 1 && line[i] != ',') {
                        num_string += line[i];
                    }
                    // Skip comma and add next integer
                    input[index++] = num_string;
                    
                    // Empty num_string
                    num_string = "";
                }
                else {
                    // Add integer to num_string
                    num_string += line[i];
                }
            }
            // Debugging
            std::cout << "Algorithm: " << input[0] << std::endl;
            std::cout << "Nums: ";
            for (int i = 1; i < index; i++) {
                std::cout << input[i] << " ";
            }
            std::cout << "\n";
        }
        // Close file
        file.close();

        // Return input
        return input;
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }

    return NULL;
}

void perform_optimal(std::string input[]) {

}

void perform_fifo(std::string input[]) {

}