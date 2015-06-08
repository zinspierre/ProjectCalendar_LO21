#ifndef AFFICHABLE_H
#define AFFICHABLE_H
#include <QString>

/**
 * @class Affichable
 * @brief Interface permettant aux classes d'être facilement affichée dans un Text Browser
 */
class Affichable
{
public:
    Affichable();
    ~Affichable();
    /**
     * @brief info : crée un QString destiné à être affiché dans un Text Browser
     * @return une QString contenant toutes les informations sur l'objet
     */
    virtual const QString info() const=0;

};

#endif // AFFICHABLE_H