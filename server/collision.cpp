#include "collision.h"


bool Collision::detect(const Car& a, const Car& b, float radius) {
    float dist = Vector2D<float>::distance(a.getPosition(), b.getPosition());
    return dist < radius * 2;
}


float Collision::calculateImpactAngleEffect(const Car& a, const Car& b) {
    Vector2D<float> dirA = a.getDirection();
    Vector2D<float> dirB = b.getDirection();

    float dot = dirA.x * dirB.x + dirA.y * dirB.y;
    return (1.0f - dot) * 0.5f; // 0 = mismo sentido, 1 = choque frontal
}

float Collision::calculateRelativeSpeedImpact(const Car& car1, const Car& car2) {
    return std::abs(car1.getSpeed() - car2.getSpeed());
}

float Collision::calculateImpactSpeedLoss(float relativeSpeed, float severity) {
    return severity * (relativeSpeed / (car1.getSpeed() + car2.getSpeed()));
}


float Collision::calculateImpactDamage(float relativeSpeed, float severity) {
    return relativeSpeed * severity * 5.0f; // factor de daño arbitrario
}


void Collision::verifyCollisionExplosion(const Car& car1, const Car& car2) {
    car1.isDestroyed();
    car2.isDestroyed();
}



void Collision::handleCollisionCar(Car& car1, Car& car2) {
    if (!detect(car1, car2, 1.0f)) return; // 1.0f sería el radio de colisión

    float severity = calculateImpactAngleEffect(car1, car2);
    float relativeSpeed = calculateRelativeSpeedImpact(car1, car2);
    float speedLoss = calculateImpactSpeedLoss(relativeSpeed, severity);
    float damage = calculateImpactDamage(relativeSpeed, severity);

    car1.takeDamage(damage);
    car2.takeDamage(damage);

    verifyCollisionExplosion(car1, car2);

    car1.setSpeed(car1.getSpeed() * (1.0f - speedLoss));
    car2.setSpeed(car2.getSpeed() * (1.0f - speedLoss));

    
}



