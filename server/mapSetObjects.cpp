#include "mapSetObjects.h"
#include <iostream>
#include <vector>


void MapSetObjects::createStaticBody(b2WorldId world, const b2Vec2& position, const std::vector<b2Polygon>& fixtures) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    bodyDef.position = position;

    b2BodyId body = b2CreateBody(world, &bodyDef);
    
    b2ShapeDef shapeDef = b2DefaultShapeDef();

    
    //  // Configuración de Densidad/Fricción (Asegurarse que no sea cero)
    // shapeDef.density = 1.0f; // Importante para cualquier fixture.


    // // --- CONFIGURACIÓN CRÍTICA DE COLISIÓN ---
    // // Asumimos que el coche (el cuerpo dinámico) también usa 0x0001.
    shapeDef.filter.categoryBits = 0x0001; // El Muro pertenece a la Categoría 0x0001
    shapeDef.filter.maskBits = 0x0001;     // El Muro colisiona con la Categoría 0x0001 (¡el Coche!)

    // std::cout << "[Box2D] Muro Creado: Cat=" << shapeDef.filter.categoryBits 
    //           << ", Mask=" << shapeDef.filter.maskBits 
    //           << ", Posición: (" << position.x << ", " << position.y << ")\n";    

    for (const auto& shape : fixtures) {
        b2CreatePolygonShape(body, &shapeDef, &shape);
    }
    std::cout << "[Box2D] Cuerpo estático creado en posición (" 
              << position.x << ", " << position.y << ") con " 
              << fixtures.size() << " fixtures." << std::endl;
}


void MapSetObjects::createBodiesFromObjects(
    b2WorldId world,
    const std::vector<MapObject>& objects)
{
    std::cout << "[Box2D] Creando " << objects.size() << " cuerpos estáticos (solo rectángulos)..." << std::endl;

    for (const auto& obj : objects) {
        
        // 1. Calcular las dimensiones a la mitad (Half-Extents)
        // b2MakeBox requiere las semi-dimensiones (metros / 2).
        // obj.width y obj.height YA están en metros.
        float halfWidthMeters = obj.width / Constants::SCALE_METER_TO_PIXEL ;
        float halfHeightMeters = obj.height / Constants::SCALE_METER_TO_PIXEL ;
            
        // 2. Crear el Box (el fixture)
        // Se utiliza un vector para permitir la composición futura de figuras complejas.
        b2Polygon poly = b2MakeBox(halfWidthMeters, halfHeightMeters); 

        std::vector<b2Polygon> fixtures;
        fixtures.push_back(poly);

        // 3. Calcular la posición CENTRAL del cuerpo (bodyDef.position)
        b2Vec2 pos;
            
        // Posición X: Esquina Izquierda (obj.x) + Half-Width (Centrado)
        pos.x = obj.x + halfWidthMeters;
            
        // Posición Y: Inversión del eje Y y Centrado
        // Posición Central Y-down (Tiled): obj.y + halfHeightMeters
        // Conversión a Posición Central Y-up (Box2D): MAP_HEIGHT_METERS - (Y_down_center)
        pos.y = Constants::MAP_HEIGHT_METERS - (obj.y - halfHeightMeters);
            
        createStaticBody(world, pos, fixtures);
    }
    
    std::cout << "[Box2D] Creación de cuerpos estáticos finalizada, total creados: " << objects.size() << std::endl;


   
}