#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

//#include <state.h>
#include <string.h>

using namespace std;
//using namespace state;

const char* HELP_MESSAGE =R"V0G0N(
usage: client <command> [<args>]

    hello       Print a Hello World message to the console.
)V0G0N";

int main(int argc, char* argv[])
{
    //Exemple exemple;
    //exemple.setX(53);


    // parse arguments
    if (argc>1) {
        if (strncmp(argv[1], "hello", 5) == 0) {
            cout << "Hello PLT !" << endl;
        }
    }
    else {
        cout << HELP_MESSAGE << endl;
    }

    return 0;
}
