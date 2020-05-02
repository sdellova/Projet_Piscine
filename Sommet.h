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
    int getPositionSommetByIndice(int indice);
    void retirer_voisins(Sommet* sommet);
    double getIndice_degre();
    void setIndice_degre(double indice);
    void setIndice_proximite(float indice_proximite);
    float getIndice_proximite();
    void setIndice_vecteur_propreNormalise(double indice_vecteur_propreNormalise);
    double getIndice_vecteur_propreNormalise();
    double getIndice_degreNormalise();
    void setIndice_degreNormalise(double indice);
    void setIndice_proximiteNormalise(float indice_proximite);
    float getIndice_proximiteNormalise();
    bool getContamine();
    void setContamine(bool valeur);
private:
    int m_indice;
    std::string m_nom;
    double m_x;
    double m_y;
    std::vector<Sommet*> m_voisins;
    double m_indice_vecteur_propre;
    double m_indice_degre;
    float m_indice_proximite;
    double m_indice_vecteur_propreNormalise;
    double m_indice_degreNormalise;
    float m_indice_proximiteNormalise;

    float m_nbrchemins;
    bool m_contamine;
};

#endif // SOMMET_H_INCLUDED
