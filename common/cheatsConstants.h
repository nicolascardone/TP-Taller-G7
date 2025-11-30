#ifndef CHEATS_CONSTANTS_H
#define CHEATS_CONSTANTS_H


#include <string>
#include <vector>
#include <SDL.h>

namespace CheatsConstants {

    static constexpr unsigned int CHEAT_BUFFER_SIZE = 10;
    static constexpr unsigned int INSTANT_WIN_BUFFER_SIZE = 3;
    static constexpr unsigned int INSTANT_KILL_BUFFER_SIZE = 3;
    static constexpr unsigned int FINISH_RACE_BUFFER_SIZE = 3;

    static const std::string CHEAT_GOD_MODE = "GOD_MODE";        
    static const std::string CHEAT_INSTANT_WIN = "INSTANT_WIN";  
    static const std::string CHEAT_INSTANT_LOSE = "INSTANT_LOSE"; 
    static const std::string CHEAT_FINISH_RACE = "FINISH_RACE";

    static constexpr int CHEAT_GENERIC_KEY = SDLK_F12;
    
    static const std::vector<int> GOD_SEQUENCE = {
        SDLK_UP, SDLK_UP, SDLK_DOWN, SDLK_DOWN, 
        SDLK_LEFT, SDLK_LEFT, SDLK_RIGHT, SDLK_RIGHT,
        SDLK_UP, SDLK_UP
    };
   
    static const std::vector<int> INSTANT_WIN_SEQUENCE = {
        SDLK_DOWN, SDLK_DOWN, SDLK_DOWN
    };
 
    static const std::vector<int> INSTANT_KILL_SEQUENCE = {
        SDLK_UP, SDLK_UP, SDLK_UP
    };

    static const std::vector<int> FINISH_RACE_SEQUENCE = {
        SDLK_RIGHT, SDLK_RIGHT, SDLK_RIGHT
    };
}
#endif //CHEATS_CONSTANTS_H
