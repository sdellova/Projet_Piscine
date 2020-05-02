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
#include <windows.h>

class Graphe
{
public:
    Graphe(std::ifstream ifs);
    void ponderation();
    void dessiner(int valeur = 0);
    void menu();
    void supprimerAretes();
    Sommet* getSommetByIndice(int indice);
    Arete* getAreteByIndice(int indice);
    int getOrdre() const;
    int getTaille();
    void centralite_degre(bool valeur);
    void centralite_vecteur_propre(bool valeur);
    float Dijkstrat(int num_s0, int num_Sf);
    std::vector<Arete*> getAretesBySommet(Sommet* sommet);
    std::vector<Arete*> getAretesBy2Sommets(Sommet* sommet1, Sommet* sommet2);
    float indice_proximite_normalise(int s);
    int getPositionAreteByIndice(int indice);
    int getPositionSommetByIndice(int indice);
    bool areteExistante(int indice);
    bool sommetExistant(int indice, std::string nom = "");
    bool indice_proximite(bool a);
    void intermediarite();
    void sauvegarde();
    void connexite();
    int Dijkstrat2(int num_s0, int num_Sf, int p, int m);
//    std::vector<Arete> Graphe::getAretesBy2Sommets(Sommet* sommet1, Sommet* sommet2);
    void ajouterAretes();
    void ajouterSommets();
    void supprimerSommets();
    bool effectue(int taille, int k);
    bool combinaisons(int taille, int k, int x, int *L, int *t, int r);
    int getDegreMax();
    std::ifstream afficherMenu();
    double getIndiceProximiteMax();
    void coloration();
private:
    bool m_orientation;
    int m_ordre;
    int m_taille;
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
    std::vector<std::vector<int>> m_chemins;
    std::vector<int>m_coul;
    double m_indiceCentraliteProximiteGlobal;
};

#endif // GRAPHE_H_INCLUDED
