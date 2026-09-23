// Cette interface de donnees porte les variables de la strategie d'evitement AE (atelier evitement
// 2027). Le define ci-dessous autorise sm_evitement.cpp, partage par tous les robots du club via
// CppRobLib, a compiler la branche AE : un robot dont l'interface ne porte pas ces variables ne le
// definit pas, et la branche n'est pas compilee chez lui.
#define SM_DATASINTERFACE_EVITEMENT_AE

#ifndef SM_DATASINTERFACE_H
#define SM_DATASINTERFACE_H

class SM_DatasInterface
{
public:
    typedef enum {
        EQUIPE_COULEUR_1 = 0,
        EQUIPE_COULEUR_2,
    }tCouleurEquipe;

    typedef enum {
        STRATEGIE_EVITEMENT_ATTENDRE = 0,
        STRATEGIE_EVITEMENT_CONTOURNER,
        STRATEGIE_EVITEMENT_AE          //!< echelle de phases reentrante (atelier evitement 2027)
    }tChoixStrategieEvitement;

    SM_DatasInterface();

    void init();

    int couleur_equipe;
    bool inverse_consignes_XYTeta;          // Inverse les commandes  XYTeta de mouvements envoyés à l'asserv en fonction de la couleur de l'équipe
    float TempsMatch;
    unsigned char ChoixStrategieMatch;

    int choix_algo_next_mission;

    // Detection d'obstacle
    unsigned char nombre_obstacles_presents;
    signed short angle_premier_obstacle_detecte;    // [degres] signe, + a gauche
    unsigned short distance_premier_obstacle_detecte; // [mm], LidarUtils::NO_OBSTACLE si aucun
    unsigned int cpt_filtrage_obstacle_detecte;
    unsigned int cpt_filtrage_disparition_obstacle; // passages consecutifs sans obstacle

    // Suivi temporel des objets (couche 2) : indicateurs publies pour le reglage et la telemetrie
    unsigned char evit_nb_pistes;            // pistes vivantes
    unsigned short evit_age_scan_ms;         // fraicheur du dernier tour de balayage [ms]
    float evit_piste_proche_X_cm;            // piste la plus proche du robot, repere terrain
    float evit_piste_proche_Y_cm;
    float evit_piste_proche_V_cms;           // norme de sa vitesse
    bool evit_piste_proche_statique;

    //! Marches de l'echelle d'evitement AE, memorisees d'une entree dans l'evitement a la suivante.
    //! LIBRE, PRUDENCE et RALENTI sont poses par IA (plafond de vitesse, sans manoeuvre) ; les
    //! suivantes sont tenues par la machine a etats.
    typedef enum {
        ETAT_AE_LIBRE = 0,
        ETAT_AE_PRUDENCE,
        ETAT_AE_RALENTI,
        ETAT_AE_ARRET,
        ETAT_AE_GENTLEMAN,
        ETAT_AE_ESQUIVE,
        ETAT_AE_BLOCAGE
    }tEtatAE;

    // Evaluation tactique (couche 3) : verdict et piste qui l'a motive
    unsigned char evit_menace;               // eNiveauMenace : LIBRE, PRUDENCE, RALENTI, ARRET
    float evit_D_cm;                         // distance de la piste retenue
    float evit_phi_rad;                      // angle relatif au cap de trajectoire (+ a gauche)
    float evit_ttc_s;                        // temps avant approche minimale (negatif : s'eloigne)
    float evit_dmin_cm;                      // distance d'approche minimale
    signed char evit_cote_libre;             // +1 gauche, -1 droite, 0 aucun

    // Strategie d'evitement AE (couche 4) : echelle de phases reentrante
    unsigned char evit_ae_state;             // tEtatAE : marche atteinte sur l'echelle
    float evit_ae_memo_X;                    // pose memorisee a l'arret (repere asservissement)
    float evit_ae_memo_Y;
    float evit_ae_memo_Theta;
    unsigned long evit_ae_tempo_arret_ms;    // duree de l'arret, avec son alea de desynchronisation
    unsigned long evit_ae_chrono_blocage_ms; // duree passee en blocage
    unsigned long evit_ae_graine;            // generateur pseudo-aleatoire de l'alea temporel
    bool evit_recul_possible;                // un recul de 10 cm reste dans le terrain
    bool evit_esquive_possible;              // une esquive de 10 cm reste dans le terrain
    float evit_esquive_cap_rad;              // cap d'esquive (repere asservissement)

    // Stratégie d'évitement d'obstacles
    bool evitementEnCours;
    bool evit_inhibe_obstacle;
    bool evit_force_obstacle;
    unsigned long evit_memo_cde_min;
    unsigned long  evit_memo_cde_max;
    float evit_memo_idx_sportiv;
    float evit_memo_vitesse_avance;
    float evit_memo_vitesse_angle;
    bool evit_memo_force_obstacle;
    int evit_memo_choix_strategie;
    float evit_sens_avant_detection;
    float evit_dernier_sens_franc;  // dernier sens de deplacement franc (+1/-1), pour la detection a l'arret
    unsigned char evit_nombre_tentatives;
    unsigned char evit_nombre_max_tentatives;
    unsigned short evit_detection_obstacle_bitfield;
    bool evit_strategie_evitement_en_cours;
    signed char evit_sgn_dist_eloigne;
    signed char evit_sgn_angle_pivote;
    signed char evit_sgn_dist_evacue;
    signed char evit_toggle_signe;
    unsigned long evit_debug_etape;
    unsigned char evit_choix_strategie;
    unsigned short evit_seuil_detection_obstacle;
    unsigned char evit_comportement_retour_evitement;

    // Pour l'inhibition de détection des obstacles
    bool proximite_bordure_Xdroite;
    bool proximite_bordure_Xgauche;
    bool proximite_bordure_Ybasse;
    bool proximite_bordure_Yhaute;
    bool inhibe_detection_AV;
    bool inhibe_detection_AR;

    //pour la messagerie générique (utilisé par la caméra entre autre)
    short m_tx_value_01;
    short m_tx_value_02;
    unsigned char m_tx_value_03;
    unsigned char m_tx_value_04;
    unsigned m_tx_code_cmd;

    short m_rx_value_01;
    short m_rx_value_02;
    unsigned char m_rx_value_03;
    unsigned char m_rx_value_04;
    unsigned m_rx_code_cmd;
};

#endif // SM_DATASINTERFACE_H
