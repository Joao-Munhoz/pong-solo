
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include <thread>

#define SCREEN_WIDTH  70
#define SCREEN_HEIGHT 20
#define HALF_BAR      5
#define INI_VELOCITY  5

class Bola {
  private:
    float velocidadeX;
    float velocidadeY;
    float posicaoX;
    float posicaoY;

  public:
    Bola(float velocidadeX, float velocidadeY, float posicaoX, float posicaoY);
    void update(float new_posX, float new_posY, float new_velX, float new_velY);
    float get_velocidadeX();
    float get_velocidadeY();
    float get_posicaoX();
    float get_posicaoY();
    void set_choque(int new_velX);
};

class particulaBarra {
  private:
    int posicao;
    char iconeBarra;

  public:
    particulaBarra(int posicao);
    void update(int nova_posicao);
    int get_posicao();
    char get_char();
};

class ListaDeParticulas {
 private:
    std::vector<particulaBarra*> *particulas;

  public:
    ListaDeParticulas();
    void hard_copy(ListaDeParticulas *ldc);
    void add_particula(particulaBarra *c);
    std::vector<particulaBarra*> *get_particulas();
};

class Fisica {
  private:
    Bola *bola;

  public:
    Fisica(Bola *bola);
    void choque(float velocidade);
    void update(float deltaT);
    int get_posicao();
    void choque(Bola *bola, ListaDeParticulas *barra);
};

class Tela {
  private:
    Bola *atualBola, *anteriorBola;
   	ListaDeParticulas *atualBarra;
    ListaDeParticulas *anteriorBarra;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(Bola *bola, ListaDeParticulas *barra, int maxI, int maxJ, float maxX, float maxY);
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
