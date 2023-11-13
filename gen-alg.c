#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

struct Individuo {
    std::vector<int> cromossomo;
    int fitness;

    Individuo(int tamanho) {
        cromossomo.resize(tamanho);
        for (int i = 0; i < tamanho; ++i) {
            cromossomo[i] = rand() % 2;
        }
        calcularFitness();
    }

    void calcularFitness() {
        fitness = std::count(cromossomo.begin(), cromossomo.end(), 1);
    }

    bool operator<(const Individuo& outro) const {
        return fitness > outro.fitness; // Quanto maior o fitness, melhor
    }
};

class AlgoritmoGenetico {
    int tamanhoPopulacao;
    int tamanhoCromossomo;
    float taxaMutacao;
    std::vector<Individuo> populacao;

public:
    AlgoritmoGenetico(int popSize, int chromoSize, float mutationRate)
        : tamanhoPopulacao(popSize), tamanhoCromossomo(chromoSize), taxaMutacao(mutationRate) {
        populacao.reserve(tamanhoPopulacao);
        for (int i = 0; i < tamanhoPopulacao; ++i) {
            populacao.emplace_back(tamanhoCromossomo);
        }
    }

    void crossover() {
        std::sort(populacao.begin(), populacao.end());

        for (int i = tamanhoPopulacao / 2; i < tamanhoPopulacao; i += 2) {
            int pontoCorte = rand() % tamanhoCromossomo;

            for (int j = pontoCorte; j < tamanhoCromossomo; ++j) {
                std::swap(populacao[i].cromossomo[j], populacao[i + 1].cromossomo[j]);
            }

            populacao[i].calcularFitness();
            populacao[i + 1].calcularFitness();
        }
    }

    void mutacao() {
        for (auto& individuo : populacao) {
            for (int i = 0; i < tamanhoCromossomo; ++i) {
                if ((rand() % 100) / 100.0 < taxaMutacao) {
                    individuo.cromossomo[i] = 1 - individuo.cromossomo[i]; // Troca 0 por 1 ou vice-versa
                }
            }
            individuo.calcularFitness();
        }
    }

    void imprimirMelhorIndividuo() {
        std::cout << "Melhor Indivíduo - Fitness: " << populacao[0].fitness << ", Cromossomo: ";
        for (int gene : populacao[0].cromossomo) {
            std::cout << gene;
        }
        std::cout << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    const int tamanhoPopulacao = 100;
    const int tamanhoCromossomo = 20;
    const float taxaMutacao = 0.01;

    AlgoritmoGenetico ag(tamanhoPopulacao, tamanhoCromossomo, taxaMutacao);

    const int geracoes = 100;

    for (int geracao = 0; geracao < geracoes; ++geracao) {
        ag.crossover();
        ag.mutacao();
        ag.imprimirMelhorIndividuo();
    }

    return 0;
}
