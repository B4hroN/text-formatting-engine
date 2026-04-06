#ifndef StringSplitter_hpp
#define StringSplitter_hpp

class StringSplitter{
public:
    StringSplitter(){}
    void operator() (std::string_view input_string_for_print, size_t input_last_index_of_string,
                     size_t input_last_symbol_index, std::vector<size_t>* indexes_of_lines) {
        string_for_print = input_string_for_print;
        last_index_of_string = input_last_index_of_string;
        last_symbol_index = input_last_symbol_index;
        start_index_in_line = 0;
        auto getRemainigLen = [&](){return last_index_of_string - start_index_in_line;};
        while (getRemainigLen() > 0){
            start_index_in_line = getNextUnspaceIndex();
            end_index_in_line = getPreviousUnspaceIndex(getSubstringEndIndex());
            if (not((start_index_in_line == end_index_in_line) and (string_for_print[start_index_in_line] == ' '))){
                indexes_of_lines->push_back(start_index_in_line);
                indexes_of_lines->push_back(end_index_in_line);
            }
            start_index_in_line = std::min(end_index_in_line + 1, last_index_of_string);
        }
        indexes_of_lines->push_back(size_t(-1));
    }
private:
    std::string_view string_for_print;
    size_t last_symbol_index;
    size_t last_index_of_string;
    static inline const char symbol_for_start_string[] = {' ', '(', '"', '\''};
    static inline const char symbol_for_end_string[] = {' ', '.', '!', '?', ',', ')', '"', '\''};
    size_t start_index_in_line;
    size_t end_index_in_line;


    size_t getNextUnspaceIndex (){
        size_t buffer = string_for_print.find_first_not_of(' ', start_index_in_line);
        return (buffer != std::string_view::npos) ? buffer : last_index_of_string;
    }
    size_t getPreviousUnspaceIndex (size_t expected_end_index){
        size_t buffer = string_for_print.find_last_not_of(' ', expected_end_index);
        return (buffer != std::string_view::npos) ? std::max(buffer , start_index_in_line) : expected_end_index;
    }
    bool isThisLastLine (){
        return end_index_in_line >= last_index_of_string;
    }
    bool isThisEndOfLineInstantly (){
        return isBelongToContainer(string_for_print[end_index_in_line + 1], symbol_for_start_string);
    }
    bool isThisEndOfLineNow (size_t expected_end_index){
        return isBelongToContainer(string_for_print[expected_end_index], symbol_for_end_string);
    }
    size_t calculateBestEndIndex (size_t expected_end_index){
        if (start_index_in_line >= expected_end_index) return -1;
        return isThisEndOfLineNow(expected_end_index) ? expected_end_index : calculateBestEndIndex(expected_end_index - 1);
    }
    size_t getSubstringEndIndex(){
        end_index_in_line = start_index_in_line + last_symbol_index;

        if (isThisLastLine()) return last_index_of_string;
        if (isThisEndOfLineInstantly()) return end_index_in_line;
        size_t buffer = calculateBestEndIndex(end_index_in_line);
        return (buffer != -1) ? buffer : end_index_in_line;
    }
};


#endif
