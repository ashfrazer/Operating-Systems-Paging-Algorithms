#include <iostream>
#include <fstream>
#include <string>

void perform_optimal(std::string input);
void perform_fifo(std::string input);
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
    perform_fifo(*fifo_input);

    // Delete memory
    delete[] fifo_input;
    delete[] opt_input;

    // Exit
    return 0;
}

std::string* read_file(std::ifstream& file) {
    // Initialize vars
    const int MAX = 50;
    std::string* input = new std::string[MAX];
    char algo_char;
    int num_frame = 0;
    int index = 0;

    if (file.is_open()) {
        // Initialize vars
        std::string line;

        // Read in algo char and numbers
        while (std::getline(file, line)) {
            // Initialize num_string
            std::string num_string = "";

            // Initialize algo_char
            algo_char = line[0];
            int num_frame = std::stoi(line.substr(2, 2));
            // Store each number in numbers array (ignoring algo_char)
            for (int i = 2; i <= line.size(); i++) {
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
            std::cout << "Algorithm: " << algo_char << std::endl;
            std::cout << "# of Frames: " << num_frame << std::endl;
            std::cout << "Nums: ";
            for (int i = 0; i < index; i++) {
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

void perform_optimal(std::string input) {
    // Get number of frames
    int num_frames = std::stoi(input.substr(0, 1));
}

void perform_fifo(std::string input) {
    // Get number of frames
    int num_frames = std::stoi(input.substr(0, 1));

    // Initialize count
    int count = 0;

    // Initialize ref_string
    int ref_string[50];

    // Convert string input array to int array
    for (int i = 2; i < 50; i++) {
        if (input[i] != ' ') {
            ref_string[count] = std::stoi(input.substr(i, 1));
        }

        // Increment count
        count++;
    }
    std::cout << ref_string << std::endl;
}