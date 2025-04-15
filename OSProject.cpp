#include <iostream>
#include <fstream>
#include <string>

void perform_optimal(std::string input);
void perform_fifo(std::string input);
std::string* read_file(std::ifstream& file);
void set_size(int array_size);
int get_size();
void set_fifo_frame(int no_frames);
void set_opt_frame(int no_frames);
int get_frame(char algo);
int size;
int fifo_frame;
int opt_frame;

int main() {
    // Initialize files
    std::ifstream fifo("FIFO.txt");
    std::ifstream opt("OPT.txt");

    // Perform FIFO algorithm
    std::string* fifo_input = read_file(fifo);
    perform_fifo(*fifo_input);

    // Perform OPT algorithm
    std::string* opt_input = read_file(opt);
    perform_optimal(*opt_input);

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

            // Parse number of frames
            num_frame = std::stoi(line.substr(2, 1));

            // Set frames
            if (algo_char == 'F') {
                set_fifo_frame(num_frame);
            }
            else if (algo_char == 'O') {
                set_opt_frame(num_frame);
            }

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

void set_fifo_frame(int no_frames) {
    fifo_frame = no_frames;
}

void set_opt_frame(int no_frames) {
    opt_frame = no_frames;
}

int get_frame(char algo) {
    if (algo == 'F') {
        return fifo_frame;
    }
    else if (algo == 'O') {
        return opt_frame;
    }
}

void perform_optimal(std::string input) {
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
    }

    // Debugging
    for (int i = 0; i < count; i++) {
        std::cout << ref_string[i] << " ";
    }

    //Array for our active mem
    int* ActiveMem = new int[opt_frame];
    for (int i = 0; i < opt_frame; i++) {
        ActiveMem[i] = -1;
    }

    bool PageFound = false;
    int OpenMem = opt_frame;
    int PageFaults = 0;
    int Needed = 0;
    int LowestBar = 9999999;
    int KickOutPos = 0;

    std::cout << OpenMem << std::endl;
    for (int i = 0; i < count; i++) {

        //Formatting to look nice in terminal
        std::cout << ref_string[i] << "     ";

        //Check ActiveMem for page
        for (int x = 0; x < opt_frame; x++) {
            if (ref_string[i] == ActiveMem[x]) {
                PageFound = true;
                break;
            }
        }

        //if page is not found and there is no open memory slots
        //find the least needed and replace
        if (!PageFound && OpenMem == 0) {
            
            for (int x = 0; x < opt_frame; x++) {
                for (int z = i+1; z < count; z++) {
                    if (ActiveMem[x] == ref_string[z]) {
                        Needed++;
                    }
                }

                if (Needed < LowestBar) {
                    KickOutPos = x;
                }

                if (Needed == 0) {
                    break;
                }

                Needed = 0;
            }

            ActiveMem[KickOutPos] = ref_string[i];
            PageFaults++;
        }

        //if page is not found and there is open memory slots
        //Then put the page in the lowest open mem slot
        if (!PageFound && OpenMem > 0) {
            ActiveMem[opt_frame - OpenMem] = ref_string[i];
            OpenMem--;
            PageFaults++;
        }

        //Formatting to look nice in terminal
        if (!PageFound) {
            for (int x = 0; x < opt_frame; x++) {
                if (ActiveMem[x] != -1) {
                    std::cout << ActiveMem[x] << " ";
                }
            }
        }
        
        std::cout << std::endl;
        PageFound = false;
    }

    std::cout << "\nPage Faults: " << PageFaults << std::endl;
    //Delete Memory
    delete[] ref_string;
}

void perform_fifo(std::string input) {
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
    }

    // Debugging
    for (int i = 0; i < count; i++) {
        std::cout << ref_string[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // Set FRAMES constant
    const int FRAMES = get_frame('F');

    // Initialize and allocate frame array
    int* frames = new int[FRAMES];
    //std::cout << "frames: " << FRAMES << std::endl;
    for (int i = 0; i < FRAMES; i++) {
        frames[i] = -99;
    }

    // Initialize fault count
    int faults = 0;

    // Initialize index
    int index = 0;

    // Iterate through each integer
    for (int i = 0; i < count; i++) {
        // Initialize flag to false
        bool present = false;
        // Iterate through frames
        for (int j = 0; j < FRAMES; j++) {
            // Set flag to true if integer already in frames
            if (frames[j] == ref_string[i]) {
                present = true;
                break;
            }
        }

        // Add integer to frames if not already present
        if (!present) {
            // Flag to track if there's a spot for integer
            bool added = false;
            for (int j = 0; j < FRAMES; j++) {
                // Fill starting frames
                if (frames[j] == -99) {
                    frames[j] = ref_string[i];

                    // Increment page faults
                    faults++;

                    // Set flag to true
                    added = true;

                    // Display integer and break from loop
                    std::cout << ref_string[i] << "     ";
                    break;
                }
            }

            // If there's no empty spot, replace oldest frame
            if (!added) {
                frames[index] = ref_string[i];

                // Increment page faults
                faults++;

                // Print integer
                std::cout << ref_string[i] << "     ";

                // Increment index
                index = (index + 1) % FRAMES;
            }

            // Print frames
            for (int k = 0; k < FRAMES; k++) {
                if (frames[k] != -99) {
                    std::cout << frames[k] << " ";
                }
            }
            std::cout << std::endl;
        }
        // If integer is already present
        else {
            // Print integer but no frames
            std::cout << ref_string[i] << std::endl;
        }
    }

    // Print faults
    std::cout << "\nPage Faults: " << faults << "\n\n" << std::endl;

    // Delete memory
    delete[] ref_string;
}