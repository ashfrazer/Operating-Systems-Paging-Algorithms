#include <iostream>
#include <fstream>
#include <string>

void perform_optimal(std::string input);
void perform_fifo(std::string input);
std::string* read_file(std::ifstream& file);
void set_size(int array_size);
int get_size();
void set_frame(int no_frames);
int size;
int frame;

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
        // Initialize line
        std::string line;

        // Read in algo char and numbers
        while (std::getline(file, line)) {
            // Initialize num_string
            std::string num_string = "";

            // Initialize algo_char and num_frame
            algo_char = line[0];
            num_frame = std::stoi(line.substr(2, 1));

            // Store each number in numbers array (ignoring algo_char and num_frame)
            std::string ref_string = line.substr(4);

            // Store ref_string into input
            input[index++] = ref_string;

            // Set size of array
            set_size(ref_string.length());

            // Debugging
            std::cout << "Algorithm: " << algo_char << std::endl;
            std::cout << "# of Frames: " << num_frame << std::endl;
            std::cout << "Nums: " << ref_string << std::endl;
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


void set_size(int array_size) {
    size = array_size;
}

int get_size() {
    return size;
}

void set_frame(int no_frames) {
    frame = no_frames;
}

int get_frame() {
    return frame;
}

void perform_optimal(std::string input) {
    // Get number of frames
    int num_frames = std::stoi(input.substr(0, 1));
}

void perform_fifo(std::string input) {
    // Get number of frames
    int num_frames = std::stoi(input.substr(0, 1));

    // Store num_frames in frames
    set_frame(num_frames);

    // Initialize count
    int count = 0;

    // Set size
    const int MAX = get_size();

    // Initialize ref_string
    int* ref_string = new int[MAX];

    // Loop through input and parse into integers
    int i = 0;
    while (i < input.size()) {
        // Skip spaces and commas
        if (input[i] == ' ' || input[i] == ',') {
            i++;
            continue;
        }

        // Parse number
        std::string num_string = "";
        while (i < input.size() && input[i] != ' ' && input[i] != ',') {
            num_string += input[i];
            i++;
        }

        // Convert number_string to an integer and store in ref_string
        if (!num_string.empty()) {
            ref_string[count] = std::stoi(num_string);
            count++;
        }

        // Set FRAMES constant
        const int FRAMES = get_frame();

        // Initialize and allocate paging array
        int* paging = new int[FRAMES];
    }

    // Debugging
    for (int i = 0; i < count; i++) {
        std::cout << ref_string[i] << " ";
    }

    // Delete memory
    delete[] ref_string;
}