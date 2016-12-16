#include "inputreader.h"


template <class T>
Anytype<T>::Anytype(T value) : _value(value){}

template <class T>
T& Anytype<T>::operator() () {
    return _value;
}

template <class T>
T& Anytype<T>::value () {
	return _value;
}

template <class T>
Anytype<T>& Anytype<T>::operator= (const Anytype<T>& rhs) {
    if (this != &rhs) {
        this._value = rhs._value;
    }
    return *this;
}



Dictionary::Dictionary() : _map() {}

Alltypes& Dictionary::operator[] (std::string key) {
    return _map[key];
}

void Dictionary::add(std::string key, Alltypes value) {
    _map.insert(std::pair<std::string, Alltypes>(key, value));
}



Dictionary argv_to_dict(int argc, char** argv) {
    /* go through argv and assign each a type and put it into dictionary. 
       argv entries should be of the form NAME_TYPE_VALUE, e.g. alpha_int_15
    */

    Dictionary dict = Dictionary();

    int count = 0;
    char *cur_arg = argv[0];
    
    std::string name, value;
    prim_type type;

    Alltypes tvalue;

    while (count < argc){
        str_to_vals(std::string(cur_arg), name, value, type);
        switch (type) {
            case prim_type::INT :
                tvalue = Anytype<int>(std::stoi(value));
            case prim_type::FLOAT :
                tvalue = Anytype<float>(std::stof(value));
            case prim_type::DOUBLE :
                tvalue = Anytype<double>(std::stod(value));
            case prim_type::STRING :
                tvalue = Anytype<std::string>(value);
        }

        dict.add(name, tvalue);
		++count;
    }

    return dict;
}

prim_type str_to_type(std::string input) {
    /*
      Convert std::string input to Types.
    */
    if (input.compare(std::string("int")) == 0) {
        return prim_type::INT;
    }
    if (input.compare(std::string("float")) == 0) {
        return prim_type::FLOAT;
    }
    if (input.compare(std::string("double")) == 0) {
        return prim_type::DOUBLE;
    }
    if (input.compare(std::string("string")) == 0) {
        return prim_type::STRING;
    }

    /* Error */
	
	throw "Invalid type";
}

void str_to_vals(std::string input, std::string& name, std::string& value, prim_type& type) {
    /* A typical string should consist of three parts separated by '/'.
     * name/type/value
    */

    int stage = 1;

    name = std::string();              // clear name
    value = std::string();             // clear value
    std::string stype = std::string(); // type string

    char temp;

    for (auto it=std::begin(input); it!=std::end(input); ++it){
        temp = *it;
		std::cout << temp;
        //if (std::string('_').compare(std::string(&temp)) == 0){
        if (temp == '/'){
            ++stage;
            
        }
        else{
            switch (stage) {
				case 1: 
					name += temp;
					break;
                case 2 : 
					stype += temp;
					break;
                case 3 : 
					value += temp;
					break;
            }
        }
    }

    type = str_to_type(stype);

}