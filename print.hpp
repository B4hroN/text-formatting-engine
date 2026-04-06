#ifndef print_hpp
#define print_hpp

enum class TextAlignment: const char {Left = 'l', Right = 'r', Center = 'c'};



class Print : public TextSolver {
public:
    std::vector<size_t> indexes_of_lines;

    Print() = default;
    void operator()(std::string input_string, TextAlignment text_formating
                   , const char actual_border_vertical, const char actual_border_horizontal){
        if (input_string.size() != size_t(0)){
            //set start values
            string_for_print = input_string;
            last_symbol_index = parameters.width_of_text() - 1;
            last_index_of_string = input_string.size() - 1;
            text_format = text_formating;
            border_vertical = actual_border_vertical;
            border_horizontal = actual_border_horizontal;

            cutString();
            if (indexes_of_lines[0] != size_t(-1)){
                //print lines
                std::cout << std::string(parameters.size_of_textplace, border_horizontal) << std::endl;
                size_t i = 0;
                while (indexes_of_lines[i] != -1){
                    printOfLine(indexes_of_lines[i], indexes_of_lines[i + 1]);
                    i += 2;
                }

                std::cout << std::string(parameters.size_of_textplace,  border_horizontal) << std::endl;
            }
            else{
                std::cout << "Error: not found replicas" << std::endl;
            }
        }
        else{
            std::cout << "Error: not found replicas" << std::endl;
        }
    }
private:
    //constants
    StringSplitter stringSplitter = StringSplitter();

    size_t last_symbol_index;
    TextAlignment text_format;
    char border_vertical;
    char border_horizontal;
    //methods

    void cutString() override{
        indexes_of_lines.clear();
        stringSplitter(string_for_print, last_index_of_string, parameters.width_of_text() - 1, &indexes_of_lines);
    }

    void SpacesDistributer(size_t& free_spaces, size_t& left_spaces, size_t& right_spaces){
        if (text_format == TextAlignment::Left){
            left_spaces = 1;
            right_spaces = free_spaces - left_spaces;
        }
        if (text_format == TextAlignment::Right){
            right_spaces = 1;
            left_spaces = free_spaces - right_spaces;
        }
        if (text_format == TextAlignment::Center){
            left_spaces = free_spaces / 2;
            right_spaces = free_spaces - left_spaces;
        }
    }
    void printOfLine(size_t start_index_in_line, size_t end_index_in_line){
        size_t len = end_index_in_line - start_index_in_line + 1;
        size_t free_spaces = parameters.width_of_text() - len + parameters.guaranteed_left_spaces + parameters.guaranteed_right_spaces;
        size_t left_spaces;
        size_t right_spaces;

        SpacesDistributer(free_spaces, left_spaces, right_spaces);

        if (len > 1) std::cout << border_vertical << std::string(left_spaces, ' ')
                    << string_for_print.substr(start_index_in_line, len)
                    << std::string(right_spaces, ' ') << border_vertical << std::endl;
    }
};

extern Print print;

#endif
