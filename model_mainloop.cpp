/* 
 * Atividade Pratica 04 
 * Utima atualizacao: 07/09/2018 - 18:16
 *
 * Leonardo Rodrigues Marques - 178610
 * Joao Victor da Conceicao Munhoz - 160174
 *
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "sound_model.hpp"
#include "oo_model.hpp"

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{

  std::vector<particulaBarra> Barra;
  Barra.resize(9);

  
  Fisica *f = new Fisica(l);

  //Tela
  Tela *tela = new Tela(l, 20, 70, 20, 70);
  tela->init();
  tela->draw();

  //Teclado
  Teclado *teclado = new Teclado();
  teclado->init();

  //Audio
  Audio::Sample *asample_beep1;
  asample_beep1 = new Audio::Sample();
  asample_beep1->load("assets/beep-01.dat");

  Audio::Sample *asample_beep2;
  asample_beep2 = new Audio::Sample();
  asample_beep2->load("assets/beep-02.dat");

  Audio::Sample *asample_beep3;
  asample_beep3= new Audio::Sample();
  asample_beep3->load("assets/beep-03.dat");

  Audio::Player *player;
  player = new Audio::Player();
  player->init();

  uint64_t t0, t1, deltaT, T;
  uint64_t time0, time1;
  int i = 0;

  T = get_now_ms();
  t1 = T;
  while (1) {
    // Atualiza timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;

    // Atualiza modelo
    f->update(deltaT);

    // Atualiza tela
    tela->update();

    // Lê o teclado
    char c = teclado->getchar();
    if (c== 'w') {
      player->play(asample_beep1);
      f->choque(-5);
      asample_beep1->set_position(0);
    }

    if(c == 's'){
      player->play(asample_beep2);
      f->choque(5);
      asample_beep2->set_position(0);
    }

    if (c=='q') {
      player->play(asample_beep3);
      asample_beep3->set_position(0);
      break;
    } 

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    i++;
  }
  tela->stop();
  teclado->stop();
  return 0;
}


void wait(){

  uint64_t t0, t1;

  while (1) {
    std::this_thread::sleep_for (std::chrono::milliseconds(1));
    t1 = get_now_ms();
    if (t1-t0 > 500) break;
  }
}
