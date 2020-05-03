#include "Sommet.h"


 ///constructeur de la classe arrete
Sommet::Sommet(int indice, std::string nom, double x, double y) : m_indice{indice}, m_nom{nom}, m_x{x}, m_y{y}, m_contamine{0}, m_immunise{0}
{

}

///recupere l'indice d'un sommet///
int Sommet::getIndice()
{
    return m_indice;
}

///recupere le nom d'un sommet///
std::string Sommet::getNom()
{
    return m_nom;
}

///recupere la position x d'un sommet///
double Sommet::getX()
{
    return m_x;
}

///recupere la position y d'un sommet///
double Sommet::getY()
{
    return m_y;
}

///modifie l'indice vecteur propre d'un sommet///
void Sommet::setIndice_vecteur_propre(double indice_vecteur_propre)
{
    m_indice_vecteur_propre = indice_vecteur_propre;
}

///modifie l'indice vecteur propre normalise d'un sommet///
void Sommet::setIndice_vecteur_propreNormalise(double indice_vecteur_propreNormalise)
{
    m_indice_vecteur_propreNormalise = indice_vecteur_propreNormalise;
}

///recupere l'indice vecteur propre d'un sommet///
double Sommet::getIndice_vecteur_propre()
{
    return m_indice_vecteur_propre;
}

///recupere l'indice vecteur propre d'un vecteur normalise///
double Sommet::getIndice_vecteur_propreNormalise()
{
    return m_indice_vecteur_propreNormalise;
}

///recupere tous les voisins d'un sommet///
const std::vector<Sommet*> Sommet::getVoisins()
{
    return m_voisins;
}

///ajoute un voisin a un sommet///
void Sommet::ajouter_voisins(Sommet* s)
{
    m_voisins.push_back(s);
}

///recupere le degre d'un sommet///
double Sommet::getIndice_degre()
{
    return m_indice_degre;
}

///modifie le degre d'un sommet///
void Sommet::setIndice_degre(double indice)
{
    m_indice_degre = indice;
}

///recupere l'indice de degre normalise d'un sommet///
double Sommet::getIndice_degreNormalise()
{
    return m_indice_degreNormalise;
}

///modifie le degre normalise d'un sommet///
void Sommet::setIndice_degreNormalise(double indice)
{
    m_indice_degreNormalise = indice;
}

///modifie l'indice de proximite d'un degre///
void Sommet::setIndice_proximite(float indice_proximite)
{
    m_indice_proximite = indice_proximite;
}

///recupere l'indice de proximite d'un degre///
float Sommet::getIndice_proximite()
{
    return m_indice_proximite;
}

///modifie l'indice de proximite normalise d'un degre///
void Sommet::setIndice_proximiteNormalise(float indice_proximite)
{
    m_indice_proximiteNormalise = indice_proximite;
}

///recupere l'indice de proximite normalise d'un sommet///
float Sommet::getIndice_proximiteNormalise()
{
    return m_indice_proximiteNormalise;
}

///retourne la position d'un sommet dans son vecteur a partir de son indice///
int Sommet::getPositionSommetByIndice(int indice)
{
    int i = 0;
    while(m_voisins[i]->getIndice() != indice)
    {
        ++i;
    }
    return i;
}

///permet de retirer le voisin d'un sommet///
void Sommet::retirer_voisins(Sommet* sommet)
{
    m_voisins.erase(m_voisins.begin() + getPositionSommetByIndice(sommet->getIndice()));
}

///retourne 1 ou 0 si on sommet est contamine///
bool Sommet::getContamine()
{
    return m_contamine;
}

///modifie la contamination d'un sommet///
void Sommet::setContamine(bool valeur)
{
    m_contamine = valeur;
}

///modifie l'indice d'intermediarite d'un sommet///
void Sommet::setIndice_intermediarite(float indice_intermediarite)
{
    m_indice_intermediarite += indice_intermediarite;
}

///retourne l'indice d'intermediarite d'un sommet///
float Sommet::getIndice_intermediarite()
{
    return m_indice_intermediarite;
}

///modifie l'indice d'intermediarite normalise d'un sommet///
void Sommet::setIndice_intermediarite_normalise(float indice_intermediarite_normalise)
{
    m_indice_intermediarite_normalise = indice_intermediarite_normalise;
}

///retourne l'indice d'intermediarite normalise d'un sommet///
float Sommet::getIndice_intermediarite_normalise()
{
    return m_indice_intermediarite_normalise;
}

///retourne le nombre de chemin le plus court entre i et j par lequel un sommet passe///
float Sommet::getnbrchemin()
{
    return m_nbrchemins;
}

///ajoute un nouveau chemin d'un sommet present dans un chemin le court entre i et j///
void Sommet::ajoutnbrchemin()
{
    m_nbrchemins++;
}

///initialise le nombre de chemin le plus court passant par un sommet entre i et j a 0///
void Sommet::setzeronbrchemin()
{
    m_nbrchemins = 0;
}
