#include "herbie.h"
#include <Itamotorino.h> // Convertida pra ESP

double coefiecienteDeVelocidade(double erroInicial, double erroAtual, double veloFinal)
{
    if (erroAtual < erroInicial)
    {
        return 1.0;
    }

    double a = (veloFinal - 1) / (3000 - erroInicial);
    double b = 1 - (a * erroInicial);
    return (a * erroAtual) + b;
}
Herbie::Herbie(Itamotorino *itamotorino, double pidOutputMinimo, double pidOutputMaximo)
{
    _itamotorino = itamotorino;
    _pidOutputMaximo = pidOutputMaximo;
    _pidOutputMinimo = pidOutputMinimo;
    _velocidadeMaxima = 150; // 130
    _velocidadeMinima = 20; // 80
    _deltaVelocidade = 0.8;  // Valor em %
}

void Herbie::setVelocidade(uint8_t velocidadeMaxima, uint8_t velocidadeMinima, double _deltaVelocidade)
{
    _velocidadeMaxima = velocidadeMaxima;
    _velocidadeMinima = velocidadeMinima;
    _deltaVelocidade = _deltaVelocidade;
}

void Herbie::act(double erro, double pidOutput)
{
    _erro = erro;

    if (pidOutput >= 0) // Valor de pid positivo - Manobrar para Direita
    {
        _direcao = DIREITA;
    }
    else
    {
        _direcao = ESQUERDA;
    }

    // logica de controle
    /*
    Transforma o pidOutput em uma porcentagem entre [0, 1] de
    acordo com os valores maximos e minimos estabelecidos;
    Calcula o valor de saída do motor que irá girar menos
    de acordo com a função:
            rpm = _velocidadeMaxima * (1 - (deltaVelocidade * pidOutputMapeado))
    O outro motor manterá sua rotacao maxima;
    A maxima diferenca de rotacao entre motores será _velocidadeMaxima será:
            rpm = _velocidadeMaxima * (1 - deltaVelocidade);
    */

    _pidOutpuMapeado = mapDouble(pidOutput, _pidOutputMinimo, _pidOutputMaximo, -1.0, 1.0);
    _pidOutpuMapeado = abs(_pidOutpuMapeado);

    if (_direcao == DIREITA) // motor direito precisa girar mais devagar
    {
        _velocidadeMotorDireito = calculaVelocidadeMotorAtuado(_pidOutpuMapeado);
        _velocidadeMotorEsquerdo = _velocidadeMaxima;
    }
    else // Direcao == ESQUERDA // motor esquerdo precisa girar mais devagar
    {
        _velocidadeMotorDireito = _velocidadeMaxima;
        _velocidadeMotorEsquerdo = calculaVelocidadeMotorAtuado(_pidOutpuMapeado);
    }

    double c = coefiecienteDeVelocidade(1000.0, _erro, 0.75);
    _velocidadeMotorDireito *= c;
    _velocidadeMotorEsquerdo *= c;

    if (_direcao == DIREITA)
    {
        _velocidadeMotorEsquerdo = constrain(_velocidadeMotorEsquerdo, _velocidadeMinima, 255);
    }
    else
    {
        double v = _velocidadeMinima;
        _velocidadeMotorDireito = constrain(_velocidadeMotorDireito, _velocidadeMinima, 255);
    }

    if (erro > -1000 && erro < 1000)
    {
        if (_direcao == DIREITA)
        {
            _velocidadeMotorDireito = constrain(_velocidadeMotorDireito, 20, 255);
        }
        else
        {
            _velocidadeMotorEsquerdo = constrain(_velocidadeMotorEsquerdo, 20, 255);
        }
    }
    // Correção de velocidade
    _itamotorino->setSpeeds(_velocidadeMotorEsquerdo, _velocidadeMotorDireito);
}

int Herbie::calculaVelocidadeMotorAtuado(double pidOutputMapeado)
{
    // Converte a velocidade para double e depois converte o resultado para uint8_t
    // return (uint8_t)((double)_velocidadeMaxima * (1 -  pidOutputMapeado));
    return (int)(_velocidadeMaxima - ((double)_velocidadeMaxima * 2 * pidOutputMapeado));
}

String Herbie::debugString()
{
    String _string;
    _string.concat(_velocidadeMotorEsquerdo);
    _string.concat(";");
    _string.concat(_velocidadeMotorDireito);
    _string.concat(";");
    _string.concat(_erro);
    _string.concat(";");
    _string.concat(_pidOutpuMapeado);
    return _string;
}

double mapDouble(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// TODO: Implementar comportamentos diferenciados curvas
