#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <vector>
#include <fstream>
#include <string>
#include "svgfile.h"
#include "Sommet.h"
#include "Arete.h"
#include <cmath>
#include <conio.h>

class Graphe
{
public:
    Graphe(std::string);
    void ponderation();
    void dessiner();
    void menu();
    void supprimerAretes();
    Sommet* getSommetByIndice(int indice);
    Arete* getAreteByIndice(int indice);
    int getOrdre() const;
    int getTaille();
    void centralite_degre();
    void centralite_vecteur_propre();
    float Dijkstrat(int num_s0, int num_Sf);
    std::vector<Arete*> getAretesBySommet(Sommet* sommet);
    void indice_proximite();
private:
    bool m_orientation;
    int m_ordre;
    int m_taille;
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
};

#endif // GRAPHE_H_INCLUDED
