#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <ncurses.h>

#include "oo_model.hpp"

using namespace std::chrono;

Tela::Tela(Bola *bola, ListaDeParticulas *barra, int maxI, int maxJ, float maxX, float maxY) {
  this->atualBola = bola;
  this->anteriorBola = new Bola(bola->get_velocidadeX(),\
                                bola->get_velocidadeY(),\
                                bola->get_posicaoX(),\
                                bola->get_posicaoY());
  this->atualBarra = barra;
  this->anteriorBarra = new ListaDeParticulas();
  this->anteriorBarra->hard_copy(this->atualBarra);
  this->maxI = maxI;
  this->maxJ = maxJ;
  this->maxX = maxX;
  this->maxY = maxY;
}

void Tela::init() {
  initscr();			      	 /* Start curses mode 		*/
  raw();				           /* Line buffering disabled	*/
  curs_set(0);           	 /* Do not display cursor */
  erase();
}

//Function to draw static interface
void Tela::draw() {
  
  for(int i = 0; i < this->maxI; i++){
    for(int j = 0; j < this->maxJ; j++){
      if(i == 0 || j == 0 || j == this->maxJ - 1){
        move(i,j);
        echochar('*');
      }
    }
  }
}

void Tela::update() {
    
    int i, j;

    //Apaga a barra na tela
     for (int i = 0; i < (*(anteriorBarra->get_particulas())).size(); ++i){
    	move( SCREEN_HEIGHT - 1 , (*(anteriorBarra->get_particulas()))[i]->get_posicao());
    	echochar(' ');
    }

    //Apaga bola da tela
    i = (int) anteriorBola->get_posicaoX() * \
        (this->maxI / this->maxX);
    j = (int) anteriorBola->get_posicaoY() * \
        (this->maxJ / this->maxY);
    
    if(i > 0 && i <= this->maxY){
      move(i, j);                 /* Move cursor to position */
      echochar(' ');              /* Prints character, advances a position */
    }

    //Desenha barra na tela
    for (int i = 0; i < (*(atualBarra->get_particulas())).size(); ++i){
    	move( SCREEN_HEIGHT - 1 , (*(atualBarra->get_particulas()))[i]->get_posicao());
    	echochar('_');

    	(*(anteriorBarra->get_particulas()))[i]->update((*(atualBarra->get_particulas()))[i]->get_posicao());
    }
  
    // Desenha bola na tela
    i = (int) atualBola->get_posicaoX() * \
        (this->maxI / this->maxX);

    j = (int) atualBola->get_posicaoY() * \
        (this->maxJ / this->maxY);
    
    if(i > 0 && i <= this->maxY){
      move(i, j);   /* Move cursor to position */
      echochar('o');  /* Prints character, advances a position */
    }

    // Atualiza corpos antigos
    anteriorBola->update(atualBola->get_posicaoX(), atualBola->get_posicaoY(), atualBola->get_velocidadeX(), atualBola->get_velocidadeY());

  // Atualiza tela
  refresh();
}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
  this->stop();;
}