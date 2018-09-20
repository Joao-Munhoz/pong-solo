
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <thread>

class Bola {
  private:
    float velocidadeX;
    float velocidadeY;
    float posicaoX;
    float posicaoY;

  public:
    Bola(float velocidadeX, float velocidadeY, float posicaoX, float posicaoY);
    void update(float new_posX, float new_posY);
    void updateDifficult(float new_velX, float new_velY);
    float get_velocidadeX();
    float get_velocidadeY();
    float get_posicaoX();
    float get_posicaoY();
};

class particulaBarra {
  private:
    float posicao;
    char iconeBarra;

  public:
    particulaBarra(float posicao);
    void update(float nova_posicao);
    float get_posicao();
    float get_char();
} 

class Fisica {
  private:
    Bola bola;

  public:
    Fisica(Bola bola);
    void choque(float velocidade);
    void update(float deltaT);
};

class Tela {
  private:
    Bola atualBola, anteriorBola;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(Bola bola, int maxI, int maxJ, float maxX, float maxY);
    ~Tela();
    void stop();
    void init();
    void draw();
    void update();
};

void threadfun (char *keybuffer, int *control);

class Teclado {
  private:
    char ultima_captura;
    int rodando;

    std::thread kb_thread;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    char getchar();
};

#endif
