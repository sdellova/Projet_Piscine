#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include "Sommet.h"

class Arete
{
public:
    Arete(int indice, Sommet* extremite1, Sommet* extremite2, float poids = 1);
    std::pair<Sommet*, Sommet*> getExtremites();
    int getIndice();
    void setPoids(float poids);
    float getPoids();
private:
    int m_indice;
    std::pair<Sommet*, Sommet*> m_extremites;
    float m_poids;
};


#endif // ARETE_H_INCLUDED
