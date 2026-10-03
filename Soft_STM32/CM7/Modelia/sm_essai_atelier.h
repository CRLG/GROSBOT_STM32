/**
 * Atelier evitement 2027 -- mission generique des essais sur table.
 *
 * Un essai est un SCRIPT : une suite de pas (aller a une pose, attendre une date du match, changer de
 * vitesse, choisir l'evitement) ecrite une fois pour la couleur 1. Les deux robots choisissent la meme
 * strategie et des couleurs opposees ; chacun joue le script de sa couleur, ce qui lui donne son role.
 *
 * REPERE DES SCRIPTS : coordonnees TERRAIN vues de la couleur 1, en cm.
 *   X = distance a SA PROPRE petite bordure (celle contre laquelle le robot part) ; Y = ordonnee terrain
 *   (0 en bas, 200 en haut ; depart a Y = 100) ; teta = 0 face au centre du terrain, -PI/2 face au bas,
 *   PI/2 face au haut, PI face a sa propre bordure.
 *   La mission convertit vers le repere de l'asservissement en retranchant le point de depart du robot
 *   qui la joue (X_ROBOT_TERRAIN_INIT_*, propre a chaque robot) : un script est donc juste pour CRLG
 *   comme pour CRLGirls. En couleur 2, CommandeMouvementXY_TETA_sym() donne le miroir exact : deux robots
 *   en X = 100 et X = 140 sur la meme ordonnee sont a 300 - 100 - 140 = 60 cm l'un de l'autre.
 *
 * Les dates (PAS_JUSQUA) sont des secondes de TempsMatch : les deux robots, lances a la meme tirette,
 * partagent ainsi la meme chronologie. Le match s'arrete a DUREE_MATCH : un essai tient en 95 s.
 *
 * Apres un evitement, la machine repasse dans le onEntry() du pas en cours (cf. interruptForEvitement) :
 * le deplacement interrompu est simplement recommande.
 */
#ifndef SM_ESSAI_ATELIER_H
#define SM_ESSAI_ATELIER_H

#include "sm_statemachinebase.h"

//! Nature d'un pas de script
typedef enum {
    PAS_FIN = 0,            //!< fin du script : la mission se termine, le robot tient sa derniere consigne
    PAS_ALLER,              //!< aller a (x, y, teta) ; pas suivant a la convergence ou au timeout
    PAS_JUSQUA,             //!< attendre que TempsMatch atteigne valeur [s]
    PAS_VITESSE,            //!< vitesses max : x = avance [cm/s], y = rotation [rad/s]
    PAS_EVITEMENT           //!< choix de l'evitement pour la suite : valeur = tModeEvitementEssai
} tTypePasEssai;

//! Comportement d'evitement d'un role
typedef enum {
    EVIT_ESSAI_INHIBE = 0,  //!< aucune reaction : le robot sert de cible ou de mobile de reference
    EVIT_ESSAI_AE,          //!< nouvelle strategie d'evitement (atelier)
    EVIT_ESSAI_ATTENDRE     //!< evitement historique du club
} tModeEvitementEssai;

typedef struct {
    unsigned char type;     //!< tTypePasEssai
    float x;
    float y;
    float teta;
    float valeur;
    unsigned short timeout_ms;
    unsigned char points;   //!< points marques si le PAS_ALLER converge (essais de parcours)
} tPasEssai;

typedef struct {
    const char *nom;            //!< identique au nom affiche par l'ecran (CEcran::strategyNumToString)
    const tPasEssai *role_couleur_1;
    const tPasEssai *role_couleur_2;
} tEssaiAtelier;

//! Table des essais, indexee par le numero de strategie (eATTRIBUTION_STRATEGIES)
extern const tEssaiAtelier ESSAIS_ATELIER[];
extern const unsigned char NOMBRE_ESSAIS_ATELIER;

class SM_EssaiAtelier : public SM_StateMachineBase
{
public:
    SM_EssaiAtelier();
    void step();
    const char* getName();
    const char* stateToName(unsigned short state);

    //! Choisit l'essai joue au prochain match (appele par IA::setStrategie)
    void setEssai(const tEssaiAtelier *essai);
    //! Nombre de points d'un role (pour le score maximal)
    static unsigned short pointsDuRole(const tPasEssai *role);
    //! Avant le match : applique le mode d'evitement du role (premier PAS_EVITEMENT de son script),
    //! pour qu'il soit en place des la tirette (cf. IA::step)
    void preparerEvitement();

private:
    const tEssaiAtelier *m_essai;
    const tPasEssai *roleCourant();
    void appliquerEvitement(unsigned char mode);
    void allerTerrain(float x_terrain, float y_terrain, float teta);
};

#endif // SM_ESSAI_ATELIER_H
