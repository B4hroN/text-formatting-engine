#ifndef setting_hpp
#define setting_hpp

struct Parameters{
    size_t size_of_screen;
    size_t size_of_textplace;
    size_t size_of_left_decorations;
    size_t size_of_right_decorations;
    size_t guaranteed_left_spaces;
    size_t guaranteed_right_spaces;
    size_t width_of_text(){return this->size_of_textplace - this->size_of_left_decorations - this->size_of_right_decorations;};
};

extern Parameters parameters;

namespace Files {
    extern const std::string replicas;
}

#endif
