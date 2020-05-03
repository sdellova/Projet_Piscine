#include "Arete.h"

///constructeur de la classe arrête///
Arete::Arete(int indice, Sommet* extremite1, Sommet* extremite2, float poids) : m_indice{indice}, m_extremites{std::make_pair(extremite1, extremite2)}, m_poids{poids}
{

}

///recupere les extremites d'une arrete///
std::pair<Sommet*, Sommet*> Arete::getExtremites()
{
    return m_extremites;
}

///recupere l'indice de l'arrete///
int Arete::getIndice()
{
    return m_indice;
}

///modifie le poids de l'arrete///
void Arete::setPoids(float poids)
{
    m_poids = poids;
}

///recupere le poids de l'arrete///
float Arete::getPoids()
{
    return m_poids;
}

