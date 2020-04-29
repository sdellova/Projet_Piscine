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
    void ponderation();
    void dessiner();
    void menu();
    Sommet* getSommetByIndice(int indice);
    void Dijkstrat(int num_s0, int num_Sf);


private:
    bool m_orientation;
    int m_ordre;
    int m_taille;
    std::vector<Sommet*> m_sommets;
    std::vector<std::pair<Sommet*, Sommet*>> m_aretes;
    std::vector<float> m_poids;
};

#endif // GRAPHE_H_INCLUDED
