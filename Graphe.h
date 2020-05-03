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
#include <ctime>
#include <cstdlib>

#define M_PI 3.14159265358979323846

class Graphe
{
public:
    Graphe(std::ifstream ifs); /// constructeur du graphe
    void ponderation(); /// permet de charger un fichier de ponderation
    void dessiner(int valeur = 0); /// méthode pour dessiner sur le svg
    void menu(); /// le menu
    void supprimerAretes(); /// methode pour supprimer des aretes
    Sommet* getSommetByIndice(int indice); /// permet d'avoir un sommet par son indice
    Arete* getAreteByIndice(int indice); /// permet d'avoir une arete par son indice
    int getOrdre() const; /// getter
    int getTaille(); /// getter
    void centralite_degre(bool valeur); /// algo de centralite de degré
    void centralite_vecteur_propre(bool valeur); /// algo de centralité de vecteur propre
    float Dijkstrat(int num_s0, int num_Sf); /// algo de Dijkstra
    std::vector<Arete*> getAretesBySommet(Sommet* sommet); /// renvoie les aretes liées à un sommet
    std::vector<Arete*> getAretesBy2Sommets(Sommet* sommet1, Sommet* sommet2); /// méthode qui permet d'obtenir les aretes correspondant à 2 sommets
    int getPositionAreteByIndice(int indice); /// pour obtenir la position d'une arete dans le vecteur d'aretes du graphe via son indice
    int getPositionSommetByIndice(int indice); /// pour obtenir la position d'un sommet dans le vecteur de sommets du graphe via son indice
    bool areteExistante(int indice); /// renvoie 1 si l'arete existe, 0 sinon
    bool sommetExistant(int indice, std::string nom = ""); /// renvoie 1 si le sommet existe, 0 sinon
    bool indice_proximite(bool a); /// algo de centralite de proximite
    void intermediarite(); /// algorithme de centralite d'intermediarite
    void sauvegarde(); /// pour sauvegarder dans un fichier
    void connexite(); /// méthode qui permet de tester la connexite
    std::vector<int> Dijkstrat2(int num_s0, int num_Sf, int p, int m); /// variante de Dijkstra utilisée pour l'intermediarite
    void ajouterAretes(); /// ajoute des aretes
    void ajouterSommets(); /// ajoute des sommets
    void supprimerSommets(); /// supprime des sommets
    int getDegreMax(); ///renvoie le degre max de graphe
    std::ifstream afficherMenu(); /// affiche le menu
    double getIndiceProximiteMax(); /// renvoie l'indice de proximite max
    void simulation(); /// méthode qui permet de simuler la propagation d'une maladie
    void parcours(Sommet* sommet); /// colore les sommets lors de la simulation
    bool appelBFS(); /// appelle le BFS pour chaque sommet
    std::vector<int> BFS(int num_s0)const; /// algo BFS
    bool effectue(int n, int p); /// pour la k-connexite
    bool combinaisons(int n, int p, int k, int *L, int *t, int r); /// pour la k-connexite
    bool afficher_parcours(int num,const std::vector<int>& arbre); /// pour les résultats du BFS

private:
    bool m_orientation; /// oriente ou non
    int m_ordre; /// ordre du graphe
    int m_taille; /// taille du graphe
    std::vector<Sommet*> m_sommets; /// tous les sommets du graphe
    std::vector<Arete*> m_aretes; /// toutes les aretes du graphe
    double m_indiceCentraliteProximiteGlobal; /// indice de centralite global du graphe
};

#endif // GRAPHE_H_INCLUDED
