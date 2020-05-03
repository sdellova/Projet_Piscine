#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <string>
#include <vector>

class Sommet
{
public:
    Sommet(int indice, std::string nom, double x, double y); /// constructeur
    int getIndice(); /// getter
    std::string getNom(); /// getter
    double getX(); /// getter
    double getY(); /// getter
    void setIndice_vecteur_propre(double indice_vecteur_propre); /// setter
    double getIndice_vecteur_propre(); /// getter
    const std::vector<Sommet*> getVoisins(); /// renvoie les voisins du sommet
    void ajouter_voisins(Sommet* s); /// méthode pour ajouter des voisins au sommet
    int getPositionSommetByIndice(int indice); /// renvoie la position du sommet dans le vecteur de sommets du graphe via son indice
    void retirer_voisins(Sommet* sommet); /// pour retirer des voisins du vecteur de voisins
    double getIndice_degre(); /// getter
    void setIndice_degre(double indice); /// setter
    void setIndice_proximite(float indice_proximite); /// setter
    float getIndice_proximite(); /// getter
    void setIndice_vecteur_propreNormalise(double indice_vecteur_propreNormalise); /// setter
    double getIndice_vecteur_propreNormalise(); /// getter
    double getIndice_degreNormalise(); /// getter
    void setIndice_degreNormalise(double indice); /// setter
    void setIndice_proximiteNormalise(float indice_proximite); /// setter
    float getIndice_proximiteNormalise(); /// getter
    bool getContamine(); /// getter
    void setContamine(bool valeur); /// setter
    bool getImmunise(); /// getter
    void setImmunise(bool valeur); /// setter
    void setIndice_intermediarite(float indice_intermediarite);
    float getIndice_intermediarite();
    void setIndice_intermediarite_normalise(float indice_intermediarite_normalise);
    float getIndice_intermediarite_normalise();
    float getnbrchemin();
    void ajoutnbrchemin();
    void setzeronbrchemin();
private:
    int m_indice; /// indice du sommet
    std::string m_nom; /// nom du sommet
    double m_x; /// coordonnée x du sommet
    double m_y; /// coordonnée y du sommet
    std::vector<Sommet*> m_voisins; /// vecteur de voisins du sommet
    double m_indice_vecteur_propre; /// indice de centralite de vecteur propre
    double m_indice_degre; /// indice de centralité de degré
    float m_indice_proximite; /// indice de centralité de proximité
    double m_indice_vecteur_propreNormalise; /// indice de centralité de vecteur propre normalisé
    double m_indice_degreNormalise; /// indice de centralité de degré normalisé
    float m_indice_proximiteNormalise; /// indice de centralité de proximité normalisé
    float m_indice_intermediarite;
    float m_indice_intermediarite_normalise;
    float m_nbrchemins; /// compteur du nombre de plus courts chemins passant par ce chemin
    bool m_contamine; /// 1 si le sommet est contaminé, 0 sinon
    bool m_immunise; /// 1 si le sommet est immunisé, 0 sinon
};

#endif // SOMMET_H_INCLUDED
