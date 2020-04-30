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
    void setIndice_vecteur_propre(double indice_vecteur_propre);
    double getIndice_vecteur_propre();
    const std::vector<Sommet*> getVoisins();
    void ajouter_voisins(Sommet* s);
    void ajouter_aretevoisins(std::pair<const Sommet*, float >);
    double getIndice_degre();
    void setIndice_degre(double indice);
    void setIndice_proximite(float indice_proximite);
    float getIndice_proximite();
private:
    int m_indice;
    std::string m_nom;
    double m_x;
    double m_y;
    std::vector<Sommet*> m_voisins;
    double m_indice_vecteur_propre;
    double m_indice_degre;
    std::vector<std::pair<const Sommet*, float>> m_aretevoisins;
    float m_indice_proximite;
};

#endif // SOMMET_H_INCLUDED
