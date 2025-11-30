#include "cheatDetector.h"

using namespace CheatsConstants;

bool CheatDetector::check_sequence(const std::deque<int>& buffer, const std::vector<int>& sequence, unsigned int sequence_size) {
    
    if (buffer.size() < sequence_size) {
        return false;
    }
    
    for (size_t i = 0; i < sequence_size; ++i) {
        if (buffer[buffer.size() - sequence_size + i] != sequence[i]) {
            return false;
        }
    }
    return true;
}


void CheatDetector::add_key_press(int key_code) {
    key_buffer.push_back(key_code);
    
    if (key_buffer.size() > CHEAT_BUFFER_SIZE) {
        key_buffer.pop_front();
    }
}


std::string CheatDetector::detect_cheat() {
    
    if (check_instant_win()) {
        key_buffer.clear();
        std::cout << "DEBUG: Cheat detectado: Victoria Instantanea" << std::endl;
        return CHEAT_INSTANT_WIN;
    }

    if (check_instant_kill()) {
        key_buffer.clear();
        std::cout << "DEBUG: Cheat detectado: Derrota Instantanea" << std::endl;
        return CHEAT_INSTANT_LOSE;
    }
    
    if (check_god_mode()) {
        key_buffer.clear();
        std::cout << "DEBUG: Cheat detectado: Modo Dios" << std::endl;
        return CHEAT_GOD_MODE;
    }
    
    if(check_finish_race()){
        key_buffer.clear();
        std::cout << "DEBUG: Cheat detectado: Finalizar Carrera" << std::endl;
        return CHEAT_FINISH_RACE;
    }

    return "";
}


bool CheatDetector::check_god_mode() const {
    return check_sequence(key_buffer, GOD_SEQUENCE, CHEAT_BUFFER_SIZE);
}


bool CheatDetector::check_instant_win() const {
    return check_sequence(key_buffer, INSTANT_WIN_SEQUENCE, INSTANT_WIN_BUFFER_SIZE);
}


bool CheatDetector::check_instant_kill() const {
    return check_sequence(key_buffer, INSTANT_KILL_SEQUENCE, INSTANT_KILL_BUFFER_SIZE);
}


bool CheatDetector::check_finish_race() const {
    return check_sequence(key_buffer, FINISH_RACE_SEQUENCE, FINISH_RACE_BUFFER_SIZE);
}
