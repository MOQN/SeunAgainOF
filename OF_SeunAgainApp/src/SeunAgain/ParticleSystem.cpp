//
//  ParticleSystem.cpp
//  SeunAgain
//
//  Created by MOQN on 10/7/17.
//

#include "ParticleSystem.h"


ParticleSystem::ParticleSystem() {
  stage = 0;
  gravity = 0.05;
  
  pos = ofPoint( ofGetWidth()/2, ofGetHeight() );
  
  numOfParticles = int( ofRandom(100,200) );
  
  for (int i=0; i<numOfParticles; i++) {
    particles.push_back( Particle()
                        .velocity( ofPoint( 0, -9) )
                        );
  }
}


void ParticleSystem::update() {
  updateStage();
  
  for (int i = particles.size()-1; i>=0; i--) {
    Particle* p = &particles[i];
    p->update();
  }
}


void ParticleSystem::display() {
  ofPushStyle();
  
  ofPushMatrix();
  ofTranslate( pos );
  for (auto &p : particles) {
    p.display();
  }
  ofPopMatrix();
  
  ofSetColor( 255 );
  ofDrawBitmapString(particles.size(), 10, 20);
  
  ofPopStyle();
}


void ParticleSystem::updateStage() {
  switch( stage ) {
    case 0:
      applyGravity();
      if (particles[0].vel.y > 2) {
        gravity = 0;
        explode();
        nextStage();
      }
      break;
    case 1:
      slowDown( 0.9 );
      if (particles[0].vel.length() < 0.01) {
        nextStage();
      }
      break;
    case 2:
      gravity = ofLerp(gravity, 0.5, 0.01);
      applyGravity();
      break;
    case 3:
      break;
    case 4:
      break;
  }
  count++;
}

void ParticleSystem::nextStage() {
  count = 0;
  stage++;
}

void ParticleSystem::applyGravity() {
  for (auto &p : particles) {
    p.applyForce( ofPoint(0, gravity * p.mass) );
  }
}


void ParticleSystem::explode() {
  for (auto &p : particles) {
    float randomAngle = ofRandom(TWO_PI);
    float randomStrength = ofRandom(12,15);
    float x = mCos(randomAngle) * randomStrength;
    float y = mSin(randomAngle) * randomStrength;
    ofPoint force = ofPoint(x,y);
    p.applyForce( force );
  }
}


void ParticleSystem::slowDown( float amount ) {
  for (auto &p : particles) {
    p.vel *= amount;
  }
}







