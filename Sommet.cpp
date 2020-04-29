#include "Sommet.h"

Sommet::Sommet(int indice, std::string nom, double x, double y) : m_indice{indice}, m_nom{nom}, m_x{x}, m_y{y}
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

void Sommet::setIndice_vecteur_propre(int indice_vecteur_propre)
{
    m_indice_vecteur_propre = indice_vecteur_propre;
}

int Sommet::getIndice_vecteur_propre()
{
    return m_indice_vecteur_propre;
}
