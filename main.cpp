#include <iostream>
#include "Graphe.h"

int main()
{
    std::string afficherMenu();
    Graphe graphe(afficherMenu());
    graphe.ponderation();
    graphe.centralite_degre(0);
    graphe.centralite_vecteur_propre(0);
    graphe.indice_proximite(0);
    graphe.sauvegarde();
    graphe.dessiner();
    graphe.menu();
    return 0;
}

std::string afficherMenu()
{
    std::string nomFichier;
    std::cout << "Ecrivez le nom du graphe a charger : ";
    std::cin >> nomFichier;
    return nomFichier;
}
