#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>
#include <fstream>
#include <string>
#include "svgfile.h"
#include "Sommet.h"

class Graphe
{
public:
    Graphe(std::string);
    std::string ponderation();
    void dessiner();
    Sommet* getSommetByIndice(int indice);
private:
    bool m_orientation;
    int m_ordre;
    int m_taille;
    std::vector<Sommet*> m_sommets;
    std::vector<std::pair<Sommet*, Sommet*>> m_aretes;
    std::vector<double> m_poids;
};

#endif // GRAPHE_H_INCLUDED
