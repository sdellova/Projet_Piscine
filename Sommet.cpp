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

const std::vector<Sommet*> Sommet::getVoisins()
{
    return m_voisins;
}

void Sommet::ajouter_voisins(Sommet* s)
{
    m_voisins.push_back(s);
}
/*
void Sommet::ajouter_aretevoisins(std::pair<const Sommet*, const Arete*> n)
{
    m_aretevoisins.push_back(n);
}

const std::vector<std::pair<const Sommet*, const Arete*>> Sommet::getaretevoisins()
{
    return m_aretevoisins;
}*/
