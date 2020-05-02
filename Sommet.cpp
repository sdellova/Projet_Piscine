#include "Sommet.h"

Sommet::Sommet(int indice, std::string nom, double x, double y) : m_indice{indice}, m_nom{nom}, m_x{x}, m_y{y}, m_contamine{0}
{

}

int Sommet::getIndice()
{
    return m_indice;
}

std::string Sommet::getNom()
{
    return m_nom;
}

double Sommet::getX()
{
    return m_x;
}

double Sommet::getY()
{
    return m_y;
}

void Sommet::setIndice_vecteur_propre(double indice_vecteur_propre)
{
    m_indice_vecteur_propre = indice_vecteur_propre;
}

void Sommet::setIndice_vecteur_propreNormalise(double indice_vecteur_propreNormalise)
{
    m_indice_vecteur_propreNormalise = indice_vecteur_propreNormalise;
}

double Sommet::getIndice_vecteur_propre()
{
    return m_indice_vecteur_propre;
}

double Sommet::getIndice_vecteur_propreNormalise()
{
    return m_indice_vecteur_propreNormalise;
}

const std::vector<Sommet*> Sommet::getVoisins()
{
    return m_voisins;
}

void Sommet::ajouter_voisins(Sommet* s)
{
    m_voisins.push_back(s);
}

double Sommet::getIndice_degre()
{
    return m_indice_degre;
}

void Sommet::setIndice_degre(double indice)
{
    m_indice_degre = indice;
}

double Sommet::getIndice_degreNormalise()
{
    return m_indice_degreNormalise;
}

void Sommet::setIndice_degreNormalise(double indice)
{
    m_indice_degreNormalise = indice;
}

void Sommet::setIndice_proximite(float indice_proximite)
{
    m_indice_proximite = indice_proximite;
}
float Sommet::getIndice_proximite()
{
    return m_indice_proximite;
}

void Sommet::setIndice_proximiteNormalise(float indice_proximite)
{
    m_indice_proximiteNormalise = indice_proximite;
}
float Sommet::getIndice_proximiteNormalise()
{
    return m_indice_proximiteNormalise;
}

int Sommet::getPositionSommetByIndice(int indice)
{
    int i = 0;
    while(m_voisins[i]->getIndice() != indice)
    {
        ++i;
    }
    return i;
}

void Sommet::retirer_voisins(Sommet* sommet)
{
    m_voisins.erase(m_voisins.begin() + getPositionSommetByIndice(sommet->getIndice()));
}

bool Sommet::getContamine()
{
    return m_contamine;
}

void Sommet::setContamine(bool valeur)
{
    m_contamine = valeur;
}
