#include "tachecomposite.h"
#include <iostream>

void TacheComposite::ajouterTache(Tache& tache)
{
    map_tache.insert(std::make_pair(tache.getId(), &tache));
}

void TacheComposite::retirerTache(Tache& tache)
{
    //à voir en fct de si suppr tache ou juste enlève de cette tachecompo
    //voir cycles de vies liés ou pas
    std::map<QString, Tache*>::iterator it = map_tache.find(tache.getId());
    Tache* tu = (*it).second;
    map_tache.erase(it);
    delete tu;
}

void TacheComposite::afficher() const
{
    std::cout << "id: " << getId().toStdString() << std::endl;
    std::cout << "titre: " << getTitre().toStdString() << std::endl;
    std::cout << "description: " << getDescription().toStdString() << std::endl;
    std::cout << "dispo: " << getDispo().toString().toStdString() << std::endl;
    std::cout << "echeance: " << getEcheance().toString().toStdString() << std::endl;
    std::cout << "tache contenues: " << std::endl;
    for (std::map<QString, Tache*>::const_iterator it=map_tache.begin(); it!=map_tache.end(); ++it)
    {
        it->second->afficher();
    }
}

TacheComposite::~TacheComposite()
{
    for(std::map<QString, Tache*>::iterator it = map_tache.begin(); it != map_tache.end(); ++it)
        delete (*it).second;
}
