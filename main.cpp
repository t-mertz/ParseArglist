#include <iostream>
#include "inputreader.h"


int main(int argc, char** argv) {

	char* testargv = "a/int/4";
    Dictionary dict = argv_to_dict(argc, &testargv);

    //Alltypes test = dict["test"];
    Anytype<int> test = Anytype<int> (dict["test"]);
	//std::cout << test.value();
    //std::cout << dict["test"]();

    return EXIT_SUCCESS;
}