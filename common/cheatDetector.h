#ifndef CHEATDETECTOR_H
#define CHEATDETECTOR_H


#include <deque>
#include <string>
#include <iostream>
#include <vector>

#include "cheatsConstants.h"


class CheatDetector {

public:

    /*
    * Constructor por defecto
    *
    * */
    CheatDetector() {}

    /*
    * Agregar la tecla presionada al buffer de cheats
    *
    * */
    void add_key_press(int key_code);

    /*
    * Detectar si se ha ingresado algun cheat
    *
    * */
    std::string detect_cheat();

private:

    std::deque<int> key_buffer;

    /*
    * Verifica si la secuencia dada esta al final del buffer
    *
    * */
    static bool check_sequence(const std::deque<int>& buffer, const std::vector<int>& sequence, unsigned int sequence_size);

    /*
    * verifica si se ingreso el cheat de activar modo dios
    *
    * */
    bool check_god_mode() const;

    /*
    * verifica si se ingreso el cheat de ganar instantaneamente
    *
    * */
    bool check_instant_win() const;

    /*
    * verifica si se ingreso el cheat de matar instantaneamente
    *
    * */
    bool check_instant_kill() const;

    /*
    *  verifica si se ingreso el cheat de finalizar carrera
    *
    * */
    bool check_finish_race() const;
};
#endif // CHEATDETECTOR_H

