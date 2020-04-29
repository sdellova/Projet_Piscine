#include "Arete.h"

Arete::Arete(int indice, Sommet* extremite1, Sommet* extremite2, float poids) : m_indice{indice}, m_extremites{std::make_pair(extremite1, extremite2)}, m_poids{poids}
{

}

std::pair<Sommet*, Sommet*> Arete::getExtremites()
{
    return m_extremites;
}

int Arete::getIndice()
{
    return m_indice;
}

void Arete::setPoids(float poids)
{
    m_poids = poids;
}

float Arete::getPoids()
{
    return m_poids;
}

