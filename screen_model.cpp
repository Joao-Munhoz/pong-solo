#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <ncurses.h>

#include "oo_model.hpp"

using namespace std::chrono;

Tela::Tela(Bola bola, int maxI, int maxJ, float maxX, float maxY) {
  this->atualBola = bola;
  this->anteriorBola = new Bola(bola->get_velocidadeX(),\
                                bola->get_velocidadeY(),\
                                bola->get_posicaoX(),\
                                bola->get_posicaoY());
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

    //Apaga bola da tela
    i = (int) anteriorBola->get_posicaoX() * \
        (this->maxI / this->maxX);
    j = (int) anteriorBola->get_posicaoY() * \
        (this->maxJ / this->maxY);
    
    if(i > 0 && i <= this->maxY){
      move(i, k);                 /* Move cursor to position */
      echochar(' ');              /* Prints character, advances a position */
    }
  

    // Desenha bola na tela
    i = (int) atualBola->get_posicaoX() * \
        (this->maxI / this->maxX);

    j = (int) atualBola->get_posicaoY() * \
        (this->maxJ / this->maxY);
    
    if(i > 0 && i <= this->maxY){
      move(i, k);   /* Move cursor to position */
      echochar('*');  /* Prints character, advances a position */
    }

    // Atualiza corpos antigos
    anteriorBola->update(atualBola->get_velocidadeX(), atualBola->get_velocidadeY(),
                         atualBola->get_posicaoX(), atualBola->get_velocidadeY());
  

  // Atualiza tela
  refresh();
}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
  this->stop();;
}