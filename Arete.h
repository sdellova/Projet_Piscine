#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "Sommet.h"

class Arete
{
public:
    Arete(int indice, Sommet* extremite1, Sommet* extremite2, float poids = 1); /// Constructeur
    std::pair<Sommet*, Sommet*> getExtremites(); /// renvoie les extremites de l'arete
    int getIndice(); /// getter
    void setPoids(float poids); /// setter
    float getPoids(); /// getter
private:
    int m_indice; /// indice de l'arete
    std::pair<Sommet*, Sommet*> m_extremites; /// sommets (extremites) de l'arete
    float m_poids; /// poids de l'arete
};


#endif // ARETE_H_INCLUDED
