#include "mapSetObjects.h"
#include <iostream>
#include <vector>



void MapSetObjects::createStaticBody(b2WorldId world, const b2Vec2& position, const std::vector<b2Polygon>& fixtures) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_staticBody;
    bodyDef.position = position;

    b2BodyId body = b2CreateBody(world, &bodyDef);
    
    b2ShapeDef shapeDef = b2DefaultShapeDef();

    for (const auto& shape : fixtures) {
        b2CreatePolygonShape(body, &shapeDef, &shape);
    }
}


void MapSetObjects::createBodiesFromObjects(
    b2WorldId world,
    const std::vector<MapObject>& objects)
{
    std::cout << "[Box2D] Creando " << objects.size() << " cuerpos estáticos..." << std::endl;

    for (const auto& obj : objects) {
        
        std::vector<b2Polygon> fixtures;

        // if (!obj.isPolygon) {
        //     // --- 1. OBJETO RECTÁNGULO (BOX) ---
            
        //     // Los valores obj.width y obj.height YA ESTÁN EN METROS.
        //     // 1.1. Calcular dimensiones en metros (half-widths)
        //     float halfWidthMeters = obj.width * 0.5f;
        //     float halfHeightMeters = obj.height * 0.5f;
            
        //     // 1.2. Crear el Box. b2MakeBox espera half-dimensions.
        //     b2Polygon poly = b2MakeBox(halfWidthMeters, halfHeightMeters); 

        //     fixtures.push_back(poly);

        //     // 1.3. Calcular la posición CENTRAL en el sistema de Box2D (Y invertida)
        //     b2Vec2 pos;
            
        //     // Posición X: Tiled X (metros) + Half-Width (metros)
        //     // obj.x YA está en metros.
        //     pos.x = obj.x + halfWidthMeters;
            
        //     // Posición Y: Inversión del eje Y (MAP_HEIGHT_METERS - Tiled Y en Metros) - Centrado (Half-Height)
        //     // obj.y YA está en metros.
        //     pos.y = Constants::MAP_HEIGHT_METERS - obj.y - halfHeightMeters;
            
        //     createStaticBody(world, pos, fixtures);
        // }
        if (!obj.isPolygon) {

                float halfWidth = obj.width ;   // metros
                float halfHeight = obj.height ; // metros

                b2Polygon poly = b2MakeBox(halfWidth, halfHeight);
                fixtures.push_back(poly);

                // posición CENTRAL del rectángulo en METROS (corrigiendo eje Y)
                b2Vec2 pos;
                pos.x = obj.x + halfWidth;

                // invertir eje Y: (altura total - y - alto)
                pos.y = Constants::MAP_HEIGHT_METERS - obj.y - halfHeight;

                createStaticBody(world, pos, fixtures);
        }

        else {

            if (obj.polygonPoints.size() < 3) continue;

            std::vector<b2Vec2> scaledVertices;
            scaledVertices.reserve(obj.polygonPoints.size());

            for (const auto& pt : obj.polygonPoints) {
                // YA en metros → solo invertir la Y local
                scaledVertices.push_back({ pt.x, -pt.y });
            }

            b2Hull hull = b2ComputeHull(scaledVertices.data(),
                                        (int)scaledVertices.size());
            if (hull.count == 0) continue;

            b2Polygon poly = b2MakePolygon(&hull, 0.0f);
            fixtures.push_back(poly);

            // posición base en METROS
            b2Vec2 pos;
            pos.x = obj.x;
            pos.y = Constants::MAP_HEIGHT_METERS - obj.y;

            createStaticBody(world, pos, fixtures);
            // --- 2. OBJETO POLÍGONO ---

            // if (obj.polygonPoints.size() < 3) continue;
            // if (obj.polygonPoints.size() > 8) {
            //     std::cerr << "Advertencia: Polígono ignorado, Box2D C API solo soporta 8 vértices convexos." << std::endl;
            //     continue;
            // }

            // // 2.1. Vértices (YA ESTÁN EN METROS)
            // std::vector<b2Vec2> scaledVertices;
            // scaledVertices.reserve(obj.polygonPoints.size());
            
            // for (const auto& point : obj.polygonPoints) {
            //     // SOLO se invierte el eje Y local del polígono (los valores ya son metros).
            //     scaledVertices.push_back({
            //         point.x, 
            //         -point.y 
            //     });
            // }

            // // 2.2. Calcular el Convex Hull y crear la forma
            // b2Hull hull = b2ComputeHull(scaledVertices.data(), (int)scaledVertices.size());
            
            // if (hull.count > 0) {
            //     b2Polygon poly = b2MakePolygon(&hull, 0.0f);
            //     fixtures.push_back(poly);

            //     // 2.3. Posición del cuerpo: Tiled X/Y de la esquina superior izquierda (invertida)
            //     b2Vec2 pos;
                
            //     // obj.x YA está en metros.
            //     pos.x = obj.x;
                
            //     // obj.y YA está en metros.
            //     // Posición Y: Inversión del eje Y
            //     pos.y = Constants::MAP_HEIGHT_METERS - obj.y; 
                
            //     createStaticBody(world, pos, fixtures);
            // } else {
            //      std::cerr << "Advertencia: Falló el cálculo del Convex Hull. Polígono ignorado." << std::endl;
            // }
        }
    }
    std::cout << "[Box2D] Creación de cuerpos estáticos finalizada." << std::endl;
}