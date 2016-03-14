//
//  kali.hpp
//  Kali
//
//  Created by Cinda Heeren on 11/12/15.
//  Copyright © 2015 Cinda Heeren. All rights reserved.
//

#ifndef kali_hpp
#define kali_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#define PI 3.14159265

class snowflake : public sf::Drawable, public sf::Transformable {
public:
    snowflake(double_t edge, sf::ConvexShape origTri);
    sf::ConvexShape rollTexture(double angle);
    double_t getSize();
    sf::ConvexShape getBaseTri();
    
private:
    double_t size;
    sf::Vertex center;
    sf::VertexArray equiTriangles;
    sf::ConvexShape baseTri;
    
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
    sf::Vector2f doRotation(sf::Vector2f rotateAbout,sf::Vector2f pt,double angle);
    
};

#endif /* kali_hpp */
