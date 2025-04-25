#include <stdio.h>
#include "CAsservLogger.h"
#include "CGlobale.h"

// Exploitation des résultats :
// Dans gtkterm :
//   Démarrer la capture dans un fichier log.csv par exemple et s'assurer que le fichier est vide
//
// Sur le CPU, lancer l'affichage des logs par la touche 'p' dans le menu console "Data Logger"

// Une fois le fichier présent sur le disque dur, l'ouvrir avec Libre Office Calc
// Supprimer les premières lignes qui peuvent être des restes des derniers affichage console
// Remplacer les "." par des "," pour que les valeurs soient considérées comme des valeurs numériques


// TODO : introduire la notion de rollback pour recommencer l'écriture à l'index "0" en cas de débordement
// et assurer ainsi l'enregistrement des X dernières secondes
// La première colonne étant l'heure, il suffira dans Excel de trier par ordre croissant pour remttre tout dans le bon ordre avant d'exploiter
// Vu avec Guigui : en mode rollback mettre un arrêt de l'enregistrement sur convergence confirmée

#ifdef UTILISATION_ASSERV_LOGGER
typedef struct
{
    long _time;
    int codeur_g;
    int codeur_d;
    float x_pos;
    float y_pos;
    float teta_pos;
    float erreur_distance;
    float erreur_angle;
    float cde_moteur_g;
    float cde_moteur_d;
    float vitesse_avance_robot;
    float vitesse_rotation_robot;
    float consigne_vitesse_avance;
    float consigne_vitesse_rotation;
    int compteur_diag_blocage;
    char diag_blocage;
    char convergence_rapide;
    char convergence_conf;
}tLogData;

static const int NBRE_LIGNES = 7500;
static tLogData m_datas[NBRE_LIGNES];

#endif // UTILISATION_ASSERV_LOGGER


CAsservLogger::CAsservLogger()
    : m_started(false),
      m_start_time(0),
      m_index(0),
      m_rollback_until_convergence(false)
{
}
#include <string.h>
// ________________________________________
/*! Démarre le logger
 */
void CAsservLogger::start()
{
#ifdef UTILISATION_ASSERV_LOGGER
    memset(m_datas, 0, sizeof(m_datas));    // RAZ de la strucuture
#endif // UTILISATION_ASSERV_LOGGER
    m_index = 0;
    m_started = true;
}

// ________________________________________
/*! Arrêt le logger
 */
void CAsservLogger::stop()
{
    m_started = false;
}

// ________________________________________
/*! Log un pas
 * return true si l'enregistrement a pu être fait / false en cas de buffer plein
 */
bool CAsservLogger::step()
{
    if (!m_started)             return false;
#ifdef UTILISATION_ASSERV_LOGGER
    m_datas[m_index]._time = getTime();
    m_datas[m_index].codeur_g =                 Application.m_roues.getCodeurG();
    m_datas[m_index].codeur_d =                 Application.m_roues.getCodeurD();
    m_datas[m_index].x_pos =                    Application.m_asservissement.X_robot;
    m_datas[m_index].y_pos =                    Application.m_asservissement.Y_robot;
    m_datas[m_index].teta_pos =                 Application.m_asservissement.angle_robot;
    m_datas[m_index].erreur_distance =          Application.m_asservissement.erreur_distance;
    m_datas[m_index].erreur_angle =             Application.m_asservissement.erreur_angle;
    m_datas[m_index].cde_moteur_g =             Application.m_roues.m_cde_roue_G;
    m_datas[m_index].cde_moteur_d =             Application.m_roues.m_cde_roue_D;
    m_datas[m_index].vitesse_avance_robot =     Application.m_asservissement.vitesse_avance_robot;
    m_datas[m_index].vitesse_rotation_robot =   Application.m_asservissement.vitesse_rotation_robot;
    m_datas[m_index].consigne_vitesse_avance =  Application.m_asservissement.consigne_vitesse_avance;
    m_datas[m_index].consigne_vitesse_rotation = Application.m_asservissement.consigne_vitesse_rotation;
    m_datas[m_index].compteur_diag_blocage =    Application.m_asservissement.compteur_diag_blocage;
    m_datas[m_index].diag_blocage =             Application.m_asservissement.diag_blocage;
    m_datas[m_index].convergence_rapide =       Application.m_asservissement.convergence_rapide;
    m_datas[m_index].convergence_conf =         Application.m_asservissement.convergence_conf;

    // Si on arrive en fin de buffer du logger, 2 solutions :
    //  (1). On est en mode rollback jusqu'à la convergence -> on reboucle et on continue de logger (ce qu'on chercheà logger, c'est la phase finale)
    //  (2). On est pas en mode rollback -> dans ce cas, on arrête le logger
    m_index++;
    if (m_index >= NBRE_LIGNES) {
        if (m_rollback_until_convergence)   m_index = 0;        // cas (1) ci-dessus
        else                                m_started = false;  // cas (2) ci-dessus
    }
    // arrêt du logger si convergence confirmé en mode roolback
    if (m_rollback_until_convergence) {
        if (Application.m_asservissement.convergence_conf) m_started = false;
    }
#endif
    return true;
}


// ________________________________________
/*! Affiche dans la console le log complet au format csv
 */
void CAsservLogger::print()
{
#ifdef UTILISATION_ASSERV_LOGGER
    printf("Time; codeur_g; codeur_d; x_pos; y_pos; teta_pos; erreur_distance; erreur_angle; cde_moteur_g; cde_moteur_d; vitesse_avance_robot; vitesse_rotation_robot; consigne_vitesse_avance; consigne_vitesse_rotation; compteur_diag_blocage; diag_blocage; convergence_rapide; convergence_conf");
    printf("\n\r");
    for (long i=0; i<m_index; i++)
    {
        printf("%ld;", m_datas[i]._time);
        printf("%d;", m_datas[i].codeur_d);
        printf("%d;", m_datas[i].codeur_g);
        printf("%f;", m_datas[i].x_pos);
        printf("%f;", m_datas[i].y_pos);
        printf("%f;", m_datas[i].teta_pos);
        printf("%f;", m_datas[i].erreur_distance);
        printf("%f;", m_datas[i].erreur_angle);
        printf("%f;", m_datas[i].cde_moteur_g);
        printf("%f;", m_datas[i].cde_moteur_d);
        printf("%f;", m_datas[i].vitesse_avance_robot);
        printf("%f;", m_datas[i].vitesse_rotation_robot);
        printf("%f;", m_datas[i].consigne_vitesse_avance);
        printf("%f;", m_datas[i].consigne_vitesse_rotation);
        printf("%d;", m_datas[i].compteur_diag_blocage);
        printf("%d;", m_datas[i].diag_blocage);
        printf("%d;", m_datas[i].convergence_rapide);
        printf("%d", m_datas[i].convergence_conf);

        // ...
        printf("\n\r");
    }
    printf("\n\r");
#endif // UTILISATION_ASSERV_LOGGER

}

