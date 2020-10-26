#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp> 
#include <state.h>

/* ----------------------------------------------------------------------------
                                GLOBAL VARIABLE
-----------------------------------------------------------------------------*/
const char* HELP_MESSAGE = R"V0G0N(
usage: client <command> [<args>]

    hello       Print a Hello World message to the console.

    state       Test the State module
)V0G0N";

//const char* UNKNOWN_MESSAGE = "client: '?' is not a command. See 'command --help'."

/* ----------------------------------------------------------------------------
                         check if SFML is working
-----------------------------------------------------------------------------*/

void testSFML() {
    sf::Texture texture;
}

/* --------------------------------------------------------------------------*/

int main(int argc, char* argv[]){
    // parse arguments
    if (argc>1) {
        std::string arg1(argv[1]);

        if (arg1 == "hello") {
            std::cout << "Hello PLT !" << std::endl;
        }
        else if (arg1 == "state") {
            std::cout << "STATE" << std::endl;

            state::State state0();
        }
        else {
            //std::cout << "Unknown command" << std::endl;
        }
    }
    else {
        std::cout << HELP_MESSAGE << std::endl;
    }

    // begin test
    //testSFML();

    //Exemple exemple;
    //exemple.setX(53);
    return 0;
}
