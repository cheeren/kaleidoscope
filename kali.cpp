//
//  kali.cpp
//  Kali
//
//  Created by Cinda Heeren on 11/12/15.
//  Copyright © 2015 Cinda Heeren. All rights reserved.
//

#include "kali.hpp"

double_t snowflake::getSize() { return size; }

snowflake::snowflake(double_t edge, sf::ConvexShape origTri){
    size = edge;
    center = sf::Vector2f(0,0);
    
    baseTri = origTri; // texture to use at start of kaleidoscope
    
    double sin60 = sqrt(3)/2;
    
    equiTriangles.resize(8);
    equiTriangles.setPrimitiveType(sf::TrianglesFan);
    equiTriangles[0] =center;
    equiTriangles[1] =sf::Vector2f(center.position.x + size, center.position.y);
    equiTriangles[2] =sf::Vector2f(center.position.x + size/2, center.position.y + sin60*size);
    equiTriangles[3] =sf::Vector2f(center.position.x - size/2, center.position.y + sin60*size);
    equiTriangles[4] =sf::Vector2f(center.position.x - size, center.position.y);
    equiTriangles[5] =sf::Vector2f(center.position.x - size/2, center.position.y - sin60*size);
    equiTriangles[6] =sf::Vector2f(center.position.x + size/2, center.position.y - sin60*size);
    equiTriangles[7] =sf::Vector2f(center.position.x + size, center.position.y);
    
    // hard coded kali triangle
    equiTriangles[0].texCoords = baseTri.getPoint(0);
    for (int i = 1; i < 8; i++)
        if (i%2==0) equiTriangles[i].texCoords = baseTri.getPoint(2);
        else equiTriangles[i].texCoords = baseTri.getPoint(1);
    
}

sf::ConvexShape snowflake::getBaseTri(){
    return baseTri;
}

sf::Vector2f snowflake::doRotation(sf::Vector2f rotateAbout,sf::Vector2f pt, double angle) {
    
    double sinA = sin(angle*PI/180);
    double cosA = cos(angle*PI/180);
    
    sf::Vector2f newpt;
    newpt.x = (pt.x - rotateAbout.x)*cosA + (pt.y - rotateAbout.y)*sinA;
    newpt.y = (pt.y - rotateAbout.y)*cosA - (pt.x - rotateAbout.x)*sinA;
    newpt.x += rotateAbout.x;
    newpt.y += rotateAbout.y;
    
    return newpt;
    
}

sf::ConvexShape snowflake::rollTexture(double angle){
    
    
    sf::Vector2f center = equiTriangles[0].texCoords;
    sf::Vector2f p1 = equiTriangles[1].texCoords;
    sf::Vector2f p2 = equiTriangles[2].texCoords;
    
    
    sf::Vector2f newcenter = doRotation(center,center,angle);
    sf::Vector2f newp1 = doRotation(center,p1,angle);
    sf::Vector2f newp2 = doRotation(center,p2,angle);
    
    equiTriangles[0].texCoords = newcenter;
    for (int i = 1; i < 8; i++)
        if (i%2==0) equiTriangles[i].texCoords = newp2;
        else equiTriangles[i].texCoords = newp1;
    
    sf::ConvexShape currTri;
    currTri.setPointCount(3);
    currTri.setPoint(0,newcenter);
    currTri.setPoint(1,newp1);
    currTri.setPoint(2,newp2);
    
    return currTri;
}


void snowflake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    // apply the transform
    states.transform *= getTransform();
    
    target.draw(equiTriangles,states);
    
}



