#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <ncurses.h>

#include "oo_model.hpp"

using namespace std::chrono;

Bola::Bola(float velocidadeX, float velocidadeY, float posicaoX, float posicaoY) {
  this->velocidadeX = velocidadeX;
  this->velocidadeY = velocidadeY;
  this->posicaoX = posicaoX;
  this->posicaoY = posicaoY;
}

void Bola::update(float new_posX, float new_posY, float new_velX, float new_velY) { 
  this->posicaoX = new_posX;
  this->posicaoY = new_posY;
  this->velocidadeX = new_velX;
  this->velocidadeY = new_velY;
}

float Bola::get_velocidadeX() {
  return this->velocidadeX;
}
float Bola::get_velocidadeY() {
  return this->velocidadeY;
}

float Bola::get_posicaoX() {
  return this->posicaoX;
}

float Bola::get_posicaoY() {
  return this->posicaoY;
}

particulaBarra::particulaBarra(int posicao) {
  this->posicao = posicao;
  this->iconeBarra = '_';
}

int particulaBarra::get_posicao(){
	return this->posicao;
}
void particulaBarra::update(int posicao){
  this->posicao = posicao;
}

ListaDeParticulas::ListaDeParticulas() {
  this->particulas = new std::vector<particulaBarra *>(0);
}

void ListaDeParticulas::add_particula(particulaBarra *c) {
  (this->particulas)->push_back(c);
}

std::vector<particulaBarra*> *ListaDeParticulas::get_particulas() {
  return (this->particulas);
}

void ListaDeParticulas::hard_copy(ListaDeParticulas *ldc) {
  std::vector<particulaBarra *> *particulas = ldc->get_particulas();

  for (int k = 0; k < particulas->size(); k++) {
    particulaBarra *c = new particulaBarra( (*particulas)[k]->get_posicao());
    this->add_particula(c);
  }
}

Fisica::Fisica(Bola *bola) {
  this->bola = bola;
}

void Fisica::update(float deltaT) {

  Bola *updateBola = this->bola;
  
  float new_velX = updateBola->get_velocidadeX();
  float new_velY = updateBola->get_velocidadeY();

  if(updateBola->get_posicaoY() > SCREEN_WIDTH - 2 || updateBola->get_posicaoY()  < 2){
  	new_velY = (-1)*updateBola->get_velocidadeY();
  }

  if(updateBola->get_posicaoX() > SCREEN_HEIGHT || updateBola->get_posicaoX() < 2){
  	new_velX = (-1)*updateBola->get_velocidadeX();
  }

  float new_posX = updateBola->get_posicaoX() + new_velX*deltaT/1000;
  float new_posY = updateBola->get_posicaoY() + new_velY*deltaT/1000;
  
  updateBola->update(new_posX, new_posY, new_velX, new_velY);
}

void Fisica::choque(float velocidade) {
  // Atualiza parametros dos corpos!
  
}