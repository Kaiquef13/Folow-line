#ifndef herbie_h
#define herbie_h

#include <Itamotorino.h> // Convertida pra ESP

typedef enum {
    ESQUERDA,
    DIREITA
} DirecaoDaManobra;

class Herbie
{
    public:

    Herbie(Itamotorino* itamotorino, double pidOutputMinimo, double pidOutputMaximo);

    void setVelocidade(uint8_t velocidadeMaxima, 
                       uint8_t velocidadeMinima,
                       double _deltaVelocidade);

    String debugString();

    void act(double erro, double pidOutput); // Pensar num nome melhor pra esse método

    private:

    int calculaVelocidadeMotorAtuado(double pidOutputMapeado);

    Itamotorino* _itamotorino;
    uint8_t _velocidadeMaxima, _velocidadeMinima;
    int _velocidadeMotorDireito, _velocidadeMotorEsquerdo;
    double _erro;
    DirecaoDaManobra _direcao;
    double _pidOutputMaximo, _pidOutputMinimo, _pidOutpuMapeado;
    double _deltaVelocidade;
};

double mapDouble(double x, double in_min, double in_max, double out_min, double out_max);

// double coefiecienteDeVelocidade(double erroInicial, double erroAtual, double veloFinal);
#endif