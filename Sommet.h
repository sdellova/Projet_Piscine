#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <string>
#include <vector>

class Sommet
{
public:
    Sommet(int indice, std::string nom, double x, double y);
    int getIndice();
    std::string getNom();
    double getX();
    double getY();
    void setIndice_vecteur_propre(int indice_vecteur_propre);
    int getIndice_vecteur_propre();
    const std::vector<Sommet*> getVoisins();
    void ajouter_voisins(Sommet* s);
    void ajouter_aretevoisins(std::pair<const Sommet*, float >);
    const std::vector<std::pair<const Sommet*, float>> getaretevoisins();
private:
    int m_indice;
    std::string m_nom;
    double m_x;
    double m_y;
    std::vector<Sommet*> m_voisins;
    int m_indice_vecteur_propre;
    std::vector<std::pair<const Sommet*, float>> m_aretevoisins;
};

#endif // SOMMET_H_INCLUDED
