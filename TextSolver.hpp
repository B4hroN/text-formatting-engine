#ifndef TextSolver_hpp
#define TextSolver_hpp

template<typename Typevalue, typename Typecontainer>
bool isBelongToContainer(const Typevalue& value, const Typecontainer& container){
    return std::find(std::begin(container), std::end(container), value) != std::end(container);
}

class TextSolver{
public:
    std::string string_for_print;
    size_t last_index_of_string;

    virtual void cutString(){
    }
};

#endif
