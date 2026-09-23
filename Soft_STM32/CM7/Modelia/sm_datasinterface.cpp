#include "sm_datasinterface.h"
#include "sm_sequenceur.h"

SM_DatasInterface::SM_DatasInterface()
{
    init();
}

// Valeurs d'init par défaut.
void SM_DatasInterface::init()
{
    ChoixStrategieMatch                 = 255; // = non défini
    TempsMatch                          = -1;
    inverse_consignes_XYTeta            = false;

    // Stratégie d'évitement d'obstacles
    evitementEnCours                    = false;
    evit_inhibe_obstacle                = false;
    evit_force_obstacle                 = false;
    evit_nombre_tentatives              = 0;
    evit_nombre_max_tentatives          = 5;
    evit_detection_obstacle_bitfield    = 0;
    evit_strategie_evitement_en_cours   = false;
    evit_sgn_dist_eloigne               = 1;
    evit_sgn_angle_pivote               = 1;
    evit_sgn_dist_evacue                = 1;
    evit_toggle_signe                   = 1;
    evit_debug_etape                    = 0;
    evit_choix_strategie                = STRATEGIE_EVITEMENT_CONTOURNER;
    evit_seuil_detection_obstacle       = 15; // [cm]
    evit_comportement_retour_evitement  = SM_Sequenceur::RETOUR_EVIT_REPRENDS_MISSION_INTERROMPUE;
    cpt_filtrage_obstacle_detecte       = 0;
    cpt_filtrage_disparition_obstacle   = 0;
    evit_nb_pistes                      = 0;
    evit_age_scan_ms                    = 0;
    evit_piste_proche_X_cm              = 0;
    evit_piste_proche_Y_cm              = 0;
    evit_piste_proche_V_cms             = 0;
    evit_piste_proche_statique          = false;
    evit_menace                         = 0;
    evit_D_cm                           = 0;
    evit_phi_rad                        = 0;
    evit_ttc_s                          = 0;
    evit_dmin_cm                        = 0;
    evit_cote_libre                     = 0;
    evit_sens_avant_detection           = 1;
    evit_dernier_sens_franc             = 1;

    //init de la messagerie générique
    m_tx_value_01=0;
    m_tx_value_02=0;
    m_tx_value_03=0;
    m_tx_value_04=0;
    m_tx_code_cmd=1;

    m_rx_value_01=0;
    m_rx_value_02=0;
    m_rx_value_03=0;
    m_rx_value_04=0;
    m_rx_code_cmd=1;
}
