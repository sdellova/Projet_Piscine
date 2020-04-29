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
    const std::vector<Sommet*> getVoisins();
private:
    int m_indice;
    std::string m_nom;
    double m_x;
    double m_y;
    std::vector<Sommet*> m_voisins;
};

#endif // SOMMET_H_INCLUDED
