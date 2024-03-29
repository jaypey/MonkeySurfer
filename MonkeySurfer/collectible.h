#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "elementjeu.h"

class Collectible : public ElementJeu
{
public:
	Collectible();
	virtual ~Collectible();

	float getDuree();
	void setDuree(float p_duree);
	
	bool getEtat();
	void setEtat(bool p_etat);


	virtual bool collision(Joueur& _joueur) = 0;
	virtual void stocker(Joueur& joueur) = 0;
	virtual void appliquerEffet(Joueur& joueur) = 0;
	virtual void afficherInfo() const = 0;

private:
	//std::chrono::steady_clock::time_point lastUpdate;
	float duree;
	bool etat;
};


#endif // COLLECTIBLE_H
