#ifndef COLLISION_H
#define COLLISION_H

#include "car.h"
#include "vector2D.h"
#include "../common/mapEntities.h"
#include <cmath>

class Collision {

private:

public:
    /*
    * Detecta si dos autos colisionan, usando un radio de colisión.
    *
    * */
    bool detect(const Car& car1, const Car& car2, float collisionRadius);

    /*
    * Calcula el efecto del ángulo de impacto entre dos autos.
    * Devuelve un valor entre 0 (mismo sentido) y 1 (choque frontal).
    * */
    float calculateImpactAngleEffect(const Car& car1, const Car& car2);

    /*
    * Calcula la velocidad relativa entre dos autos.
    *
    * */
    float calculateRelativeSpeedImpact(const Car& car1, const Car& car2);

    /*
    * Calcula la pérdida de velocidad tras el impacto basado en la severidad.
    *
    * */
    float calculateImpactSpeedLoss(float relativeSpeed, float severity);

    /*
    * Calcula el daño causado por el impacto basado en la velocidad relativa y severidad.
    *
    * */
    float calculateImpactDamage(float relativeSpeed, float severity);

    /*
    * 
    *
    * */
    void verifyCollisionExplosion(const Car& car1, const Car& car2);

    /*
    * Maneja la colisión entre dos autos, aplicando el daño correspondiente a cada uno.
    *
    * */
    void handleCollisionCar(Car& car1, Car& car2);

    /*
    * Maneja la colisión entre un auto y una entidad del mapa,
    * aplicando el daño correspondiente al auto.
    *
    * */
    void handleCollisionEntity(Car& car, const MapEntity& entity);
};
#endif // COLLISION_H
