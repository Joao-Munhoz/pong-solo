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

void Bola::update(float new_posX, float new_posY) { 
  this->posicaoX = new_posX;
  this->posicaoY = new_posY;
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

particulaBarra::particulaBarra(float posicao) {
  this->posicao = posicao;
  this->iconeBarra = '_';
}

void particulaBarra::update(float nova_posicao){
  this->posicao = nova_posicao;
}

Fisica::Fisica(Bola bola) {
  this->bola = bola;
}


void Fisica::update(float deltaT) {
  
  Bola updateBola = this->bola;
  float new_posX = updateBola->get_posicaoX() + updateBola->get_velocidadeX()*deltaT/1000;
  float new_posY = updateBola>get_posicao() + updateBola->get_velocidadeY()*deltaT/1000;
  updateBola->update(new_posX, new_posY);
}

void Fisica::choque(float velocidade) {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  for (int i = 0; i < (*c).size(); i++) {
    float new_vel = velocidade;
    float new_pos = (*c)[i]->get_posicao();
    float new_acc = (-((*c)[i]->get_constante_mola()*((*c)[i]->get_posicao() - (*c)[i]->get_posicao_equilibrio())) 
                    - (*c)[i]->get_constante_amortecimento() * (*c)[i]->get_velocidade()) /(*c)[i]->get_massa();
    (*c)[i]->update(new_vel, new_pos, new_acc);
  }
}