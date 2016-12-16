#include<string>
#include <map>
#include <iostream>

enum class prim_type {
    INT, FLOAT, DOUBLE, STRING
};

class Alltypes {
	public:
		Alltypes();
		template <class T>
		T& as(void);
};

/*
template<class T>
class Anytype : Alltypes {
    public:
        T& operator() (void);
        T& operator= (Anytype&);
};
*/

template <typename T>
class Anytype : public Alltypes {
    /*
     * Template for a generic type. Contains only a value of template type T,
     * which can be accessed publicly by calling the object.
     * This class masks types so containers containing different types can be constructed.
    */
    private:
        T _value;

    public:
        Anytype(T value);
        T& operator() ();
        Anytype& operator= (const Anytype& rhs);
		T& Anytype<T>::value();
};

class Dictionary {
    private:
        std::map<std::string, Alltypes> _map;
    public:
        Dictionary();
        Alltypes& operator[] (std::string);
        void add(std::string key, Alltypes value);
};

Dictionary argv_to_dict(int argc, char** argv);
void str_to_vals(std::string input, std::string& name, std::string& value, prim_type& type);
prim_type str_to_type(std::string input);