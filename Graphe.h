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
#include <time.h>
#include <ctime>
#include <cstdlib>
#include<math.h>
#define M_PI 3.14159265358979323846

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
    int getPositionAreteByIndice(int indice);
    int getPositionSommetByIndice(int indice);
    bool areteExistante(int indice);
    bool sommetExistant(int indice, std::string nom = "");
    bool indice_proximite(bool a);
    void intermediarite();
    void calculintermediarite(int indice1, int indice2);
    void sauvegarde();
    void connexite();
    std::vector<int> Dijkstrat2(int num_s0, int num_Sf);
    void ajouterAretes();
    void ajouterSommets();
    void supprimerSommets();
    int getDegreMax();
    std::ifstream afficherMenu();
    double getIndiceProximiteMax();
    void simulation();
    void parcours(Sommet* sommet);
    bool appelBFS();
    std::vector<int> BFS(int num_s0)const;
    bool effectue(int n, int p);
    bool combinaisons(int n, int p, int k, int *L, int *t, int r);
    bool afficher_parcours(int num,const std::vector<int>& arbre);

private:
    bool m_orientation;
    int m_ordre;
    int m_taille;
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;
    double m_indiceCentraliteProximiteGlobal;
};

#endif // GRAPHE_H_INCLUDED
