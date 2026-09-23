// ________________________________________________
// !! ATTENTION !!
// Ce code est commun aux projets du robot réel et simulation
// Il ne doit pas y avoir de code spécifique CPU
//  ou d'appel à une classe non gérée par une couche d'abstraction
//  au risque de ne plus pouvoir tourner en simulation

#include "ia.h"
#include "CGlobale.h"
#include "ConfigSpecifiqueCoupe.h"
#include "math.h"
#include "lidar_blob.h"

IA::IA()
    : IABase()
{
    m_sm_liste[m_state_machine_count++] = &m_sm_autotest;
    m_sm_liste[m_state_machine_count++] = &m_sm_chasse_neige;
    m_sm_liste[m_state_machine_count++] = &m_sm_centre;
    m_sm_liste[m_state_machine_count++] = &m_sm_curseur;
    m_sm_liste[m_state_machine_count++] = &m_sm_retour_zone_depart;
    m_sm_liste[m_state_machine_count++] = &m_sm_petite_bordure;
    m_sm_liste[m_state_machine_count++] = &m_sm_grande_bordure;

    // Pour Blockly débutant:
    m_sm_liste[m_state_machine_count++] = &m_sm_tache1;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache2;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache3;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache4;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache5;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache6;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache7;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache8;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache9;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache10;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache_post_match;
    m_sm_liste[m_state_machine_count++] = &m_sm_tache_avant_match;
}

// ________________________________________________
void IA::init()
{
    m_inputs_interface.TE_Modele = PERIODE_APPEL_MODELIA;
    m_date_ms = 0;
    m_obstacle_tracker.init();
    m_evaluateur_tactique.init();
    m_datas_interface.init();
    m_inputs_interface.init();
    m_outputs_interface.init();
    for (int i=0; i<m_state_machine_count; i++) {
        if (m_sm_liste[i]) {
            m_sm_liste[i]->init(this);
        }
    }
    setMaxScores();
    //Valeur par défaut au démarrage de la cmde de la trame générique
    //utile par exemple si on veut faire de la reconnaissance vidéo pendant l'installation du robot
    //avant le début du match
    m_datas_interface.m_tx_code_cmd=DMDE_DISTANCE_BALISE;
    m_sm_main.start();
}

// ________________________________________________
void IA::match_started()
{
    //Application.m_power_electrobot.setOutput((dsPicPowerElectrobotBase::tSwitchOutput)DECO_LED_CRLG, true);)
    m_outputs_interface.setPosition_XYTeta_sym(0, 0, -M_PI/2); // pour l'année 2026 Teta=-PI/2
}

// ________________________________________________
void IA::match_finished()
{
    //Application.m_power_electrobot.setOutput((dsPicPowerElectrobotBase::tSwitchOutput)DECO_LED_CRLG, false);
}

// ________________________________________________
// Définit l'ordre d'exécution des "main missions"
// sm_xxxx.setPrioriteExecution(ordre++);
//      Active la mission xxx
//      Lui fixe une priorité d'exécution (0 étant la priorité la plus haute)
void IA::setStrategie(unsigned char strategie)
{
    int ordre = 0;
    resetAllSMPriority();
    disableAllSM(); // Désactive toutes les SM par défaut (elles seront activées une par une avec la priorité associée en fonction de la stratégie)

    //strategie = STRATEGIE_PAR_DEFAUT;
    switch (strategie) {
    // ________________________
    case STRATEGIE_HOMOLO1:
        m_datas_interface.choix_algo_next_mission = ALGO_PERTINENT_MISSION_CHOIX_PRIORITE;
        m_datas_interface.evit_inhibe_obstacle=false;
        //Application.m_detection_obstacles.inhibeDetection(true);
        Application.m_asservissement.CommandeVitesseMouvement(40.,2); //normalement 80 cm.s-1 et 3 rad.s-1
        Application.m_asservissement.setIndiceSportivite(0.5);
        m_datas_interface.evit_choix_strategie= SM_DatasInterface::STRATEGIE_EVITEMENT_ATTENDRE;
        Application.m_detection_obstacles.setSeuilDetectionObstacle(SEUIL_DETECTION_US); //par défaut seuil de détection avec les capteurs US en backup
        m_datas_interface.evit_nombre_max_tentatives=1;

        m_sm_centre.setPrioriteExecution(ordre++);
        m_sm_curseur.setPrioriteExecution(ordre++);
        m_sm_petite_bordure.setPrioriteExecution(ordre++);
        /*m_sm_curseur.setPrioriteExecution(ordre++);
        m_sm_retour_zone_depart.setPrioriteExecution(ordre++);
        m_sm_petite_bordure.setPrioriteExecution(ordre++);
        m_sm_grande_bordure.setPrioriteExecution(ordre++);*/

        break;
    // ________________________
    case STRATEGIE_HOMOLO2:
        m_datas_interface.choix_algo_next_mission = ALGO_PERTINENT_MISSION_CHOIX_PRIORITE;
        m_datas_interface.evit_inhibe_obstacle=false;
        //Application.m_detection_obstacles.inhibeDetection(true);
        Application.m_asservissement.CommandeVitesseMouvement(40.,2); //normalement 80 cm.s-1 et 3 rad.s-1
        Application.m_asservissement.setIndiceSportivite(0.5);
        m_datas_interface.evit_choix_strategie= SM_DatasInterface::STRATEGIE_EVITEMENT_ATTENDRE;
        Application.m_detection_obstacles.setSeuilDetectionObstacle(SEUIL_DETECTION_US); //par défaut seuil de détection avec les capteurs US en backup
        m_datas_interface.evit_nombre_max_tentatives=1;

        m_sm_centre.setPrioriteExecution(ordre++);
        m_sm_curseur.setPrioriteExecution(ordre++);
        m_sm_petite_bordure.setPrioriteExecution(ordre++);
        /*m_sm_curseur.setPrioriteExecution(ordre++);
        m_sm_retour_zone_depart.setPrioriteExecution(ordre++);
        m_sm_petite_bordure.setPrioriteExecution(ordre++);
        m_sm_grande_bordure.setPrioriteExecution(ordre++);*/
        break;
    // ________________________
    case STRATEGIE_01:
        m_datas_interface.choix_algo_next_mission = ALGO_PERTINENT_MISSION_CHOIX_PRIORITE;
        m_datas_interface.evit_inhibe_obstacle=false;
        //Application.m_detection_obstacles.inhibeDetection(true);
        Application.m_asservissement.CommandeVitesseMouvement(40.,2); //normalement 80 cm.s-1 et 3 rad.s-1
        Application.m_asservissement.setIndiceSportivite(0.5);
        m_datas_interface.evit_choix_strategie= SM_DatasInterface::STRATEGIE_EVITEMENT_ATTENDRE;
        Application.m_detection_obstacles.setSeuilDetectionObstacle(SEUIL_DETECTION_US); //par défaut seuil de détection avec les capteurs US en backup
        m_datas_interface.evit_nombre_max_tentatives=1;

        m_sm_centre.setPrioriteExecution(ordre++);
        m_sm_curseur.setPrioriteExecution(ordre++);
        m_sm_petite_bordure.setPrioriteExecution(ordre++);
        /*m_sm_curseur.setPrioriteExecution(ordre++);
        m_sm_retour_zone_depart.setPrioriteExecution(ordre++);
        m_sm_petite_bordure.setPrioriteExecution(ordre++);
        m_sm_grande_bordure.setPrioriteExecution(ordre++);*/
        break;
    case STRATEGIE_PAR_DEFAUT:
    default:
        m_datas_interface.choix_algo_next_mission = ALGO_PERTINENT_MISSION_CHOIX_PRIORITE;
        m_datas_interface.evit_inhibe_obstacle=false;
        //Application.m_detection_obstacles.inhibeDetection(true);
        Application.m_asservissement.CommandeVitesseMouvement(40.,2); //normalement 80 cm.s-1 et 3 rad.s-1
        Application.m_asservissement.setIndiceSportivite(0.5);
        m_datas_interface.evit_choix_strategie= SM_DatasInterface::STRATEGIE_EVITEMENT_ATTENDRE;
        Application.m_detection_obstacles.setSeuilDetectionObstacle(SEUIL_DETECTION_US); //par défaut seuil de détection avec les capteurs US en backup
        m_datas_interface.evit_nombre_max_tentatives=1;

        m_sm_centre.setPrioriteExecution(ordre++);
        m_sm_curseur.setPrioriteExecution(ordre++);
        m_sm_petite_bordure.setPrioriteExecution(ordre++);
        /*m_sm_curseur.setPrioriteExecution(ordre++);
        m_sm_retour_zone_depart.setPrioriteExecution(ordre++);
        m_sm_petite_bordure.setPrioriteExecution(ordre++);
        m_sm_grande_bordure.setPrioriteExecution(ordre++);*/
        break;
    }


    m_datas_interface.ChoixStrategieMatch = strategie;
}

// ________________________________________________
void IA::setMaxScores()
{
    // TODO : valeurs des scores max fixées au pif.
    // Mettre les vraies valeurs
    m_sm_centre.setScoreMax(25);
    m_sm_curseur.setScoreMax(0);
    m_sm_retour_zone_depart.setScoreMax(4);
    m_sm_chasse_neige.setScoreMax(0);
    m_sm_grande_bordure.setScoreMax(10);
    m_sm_petite_bordure.setScoreMax(10);
}

// ________________________________________________
// TODO : à voir sur le long terme si la couche de recopie des donées
// externes dans m_inputs_interface.xxxx est toujours nécessaire
// ou si le modèle ne peut pas utiliser directement Application.m_xxxxx.yyyy
void IA::step()
{
    // Date interne du modele : le lidar tourne a ~8 Hz et le modele a 50 Hz, le suivi temporel a
    // besoin de savoir quand chaque tour de balayage lui est parvenu.
    m_date_ms += (unsigned long)(PERIODE_APPEL_MODELIA * 1000.f);

    m_inputs_interface.Tirette             = Application.m_capteurs.getTirette();

    if (UTILISATION_LIDAR == LIDAR_INTERNE) {
        LidarUtils::copy_tab_obstacles(Application.m_lidar.m_obstacles, m_inputs_interface.m_lidar_obstacles);
        m_inputs_interface.m_lidar_status = Application.m_lidar.is_present() ? LidarUtils::LIDAR_OK : LidarUtils::LIDAR_ERROR;
    }

    //commandes ou traitements venant de LABOTBOX via la trame générique
    switch(m_datas_interface.m_rx_code_cmd)
    {
        case CMDE_DISTANCE_BALISE:
            m_inputs_interface.m_distance_balise1=m_datas_interface.m_rx_value_01;
            m_inputs_interface.m_distance_balise2=m_datas_interface.m_rx_value_02;
            break;
        case CMDE_VIDEO_NORD_SUD:
            m_inputs_interface.m_nord=m_datas_interface.m_rx_value_03;
            m_inputs_interface.m_sud=m_datas_interface.m_rx_value_04;
            break;
        default: break;
    }

    m_inputs_interface.Convergence         = Application.m_asservissement.convergence_conf;
    m_inputs_interface.Convergence_rapide  = Application.m_asservissement.convergence_rapide;
//    m_inputs_interface.ConvergenceRack     = Application.m_asservissement_chariot.isConverged();
    m_inputs_interface.X_robot             = Application.m_asservissement.X_robot;
    m_inputs_interface.Y_robot             = Application.m_asservissement.Y_robot;
    m_inputs_interface.angle_robot         = Application.m_asservissement.angle_robot;
//    m_inputs_interface.ConvergenceKmar     = Application.m_kmar.isFinished();

    // Coordonnées du robot dans le repère absolue terrain (pour que ce soit valable pour les 2 couleurs d'équipe)
    if (m_datas_interface.couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1) {
        m_inputs_interface.X_robot_terrain     = X_ROBOT_TERRAIN_INIT_COULEUR_1 + Application.m_asservissement.X_robot;
        m_inputs_interface.Y_robot_terrain     = Y_ROBOT_TERRAIN_INIT_COULEUR_1 + Application.m_asservissement.Y_robot;
        m_inputs_interface.angle_robot_terrain = Application.m_asservissement.angle_robot - ANGLE_ROBOT_TERRAIN_INIT_COULEUR_1;
    }
    else {
        m_inputs_interface.X_robot_terrain     = X_ROBOT_TERRAIN_INIT_COULEUR_2 - Application.m_asservissement.X_robot;
        m_inputs_interface.Y_robot_terrain     = Y_ROBOT_TERRAIN_INIT_COULEUR_2 - Application.m_asservissement.Y_robot;
        m_inputs_interface.angle_robot_terrain = Application.m_asservissement.angle_robot - ANGLE_ROBOT_TERRAIN_INIT_COULEUR_2;
        // Ramène l'angle entre [-Pi;Pi]
        if (m_inputs_interface.angle_robot_terrain > 3.14)   m_inputs_interface.angle_robot_terrain = m_inputs_interface.angle_robot_terrain - 6.28;
        if (m_inputs_interface.angle_robot_terrain <= -3.14) m_inputs_interface.angle_robot_terrain = m_inputs_interface.angle_robot_terrain + 6.28;
    }

    // Télémètres et obstacles
    m_inputs_interface.Telemetre_AVG       = Application.m_telemetres.getDistanceAVG();
    m_inputs_interface.Telemetre_AVD       = Application.m_telemetres.getDistanceAVD();
    m_inputs_interface.Telemetre_ARG       = Application.m_telemetres.getDistanceARG();
    m_inputs_interface.Telemetre_ARD       = Application.m_telemetres.getDistanceARD();
    m_inputs_interface.Telemetre_ARGCentre = Application.m_telemetres.getDistanceARGCentre();
    m_inputs_interface.Telemetre_ARDCentre = Application.m_telemetres.getDistanceARDCentre();

	//ajouter un watchdog sur l'état du LIDAR pour assurer le backup sur les capteurs US afin d'avoir toujours
	//une solution d'évitement, idéalement l'intégrité des données est vérifiée au niveau raspbberry
    if(m_inputs_interface.m_lidar_status==LidarUtils::LIDAR_OK)
	{
		//TODO:
		//vérifier le rafraichissement des données
		//vérifier l'intégrité des données
    }
    m_datas_interface.nombre_obstacles_presents = 0;
    m_datas_interface.angle_premier_obstacle_detecte = 0;
    m_datas_interface.distance_premier_obstacle_detecte = LidarUtils::NO_OBSTACLE;

    // Sens de référence (avant/arrière) de la détection lidar, calculé à chaque pas pour que le
    // dernier sens de mouvement franc reste à jour même quand le lidar est absent
    const float sens_reference_detection = calculerSensReferenceDetection();

	//Traitements Lidar pour évitement
    if(m_inputs_interface.m_lidar_status==LidarUtils::LIDAR_OK)
	{
        Application.m_detection_obstacles.setSeuilDetectionObstacle(SEUIL_DETECTION_LIDAR);

        //récupération de données utiles pour l'évitement
        m_inputs_interface.obstacleDetecte_non_filtre=false;

        // Les drapeaux de quadrant et le champ de bits sont remis à zéro à chaque pas, puis CUMULÉS
        // sur tous les points détectés (étape 0 de l'atelier évitement 2027). Auparavant ils
        // n'étaient écrits qu'en cas de détection : le champ de bits restait collé à la première
        // détection, si bien qu'EVITEMENT_INIT_CHOICE ne voyait jamais la voie se libérer ; et chaque
        // point écrasait le quadrant du précédent au lieu de s'y ajouter.
        m_inputs_interface.obstacle_AVG = false;
        m_inputs_interface.obstacle_AVD = false;
        m_inputs_interface.obstacle_ARG = false;
        m_inputs_interface.obstacle_ARD = false;

        // Source des points : la plus riche disponible, choisie à l'exécution.
        //  - lidar interne (YDLIDAR sur le CPU) ou lidar simulé (Simulia) : les objets découpés par
        //    le filtre, avec leur largeur angulaire ;
        //  - lidar externe (RPI via LaBotBox) : pas de filtre local, seulement la liste des
        //    obstacles les plus proches, déjà filtrée en amont.
        // Un choix à la compilation (UTILISATION_LIDAR) ne conviendrait pas : la logique robot
        // compilée pour Simulia partage ConfigSpecifiqueCoupe.h avec le firmware. Auparavant seul le
        // balayage brut était parcouru : l'évitement lidar ne se déclenchait jamais en lidar externe
        // ni en simulation.
        // Les objets marqués douteux par le facteur de forme sont traités ICI COMME LES AUTRES : à
        // ce stade la chaîne ne fait que de la proximité, et un objet qui ne ressemble à aucun mât
        // balise est justement quelque chose devant quoi il faut s'arrêter. Le cas qui tranche est
        // l'homologation : l'arbitre éprouve l'évitement en poussant un robot factice, et le lidar
        // voit alors le mât ET une partie de son bras -- l'ensemble ne respecte aucun facteur de
        // forme. C'est la couche tactique qui exploitera la distinction.
        CLidarBlobs observations;
        if (Application.m_lidar.blobs().m_count > 0)
        {
            observations = Application.m_lidar.blobs();
        }
        else
        {
            // lidar externe : pas de filtre local, donc pas de largeur angulaire ni de verdict de
            // forme. Les obstacles sont repris tels quels, sans doute attache.
            for (int i=0; i<LidarUtils::NBRE_MAX_OBSTACLES; i++)
            {
                if (m_inputs_interface.m_lidar_obstacles[i].distance == LidarUtils::NO_OBSTACLE) continue;
                observations.append((float)m_inputs_interface.m_lidar_obstacles[i].angle,
                                    (float)m_inputs_interface.m_lidar_obstacles[i].distance,
                                    0.f, false);
            }
        }

        //Pour 2026: émulation des capteurs US avec le ydlidar
        for(int i=0;i<observations.m_count; i++)
        {
            traiterPointLidar(observations.m_blobs[i].distance_mm, observations.m_blobs[i].angle_deg,
                              sens_reference_detection);
        }

        // ---- Couche 2 : suivi temporel des objets, en repère terrain.
        // Un tour de balayage nourrit le suivi ; entre deux tours, les pistes sont simplement
        // avancées de leur vitesse. Sans ce découpage, le même balayage serait pris pour une
        // nouvelle mesure à chaque pas de modèle et toutes les vitesses seraient nulles.
        if (Application.m_lidar.is_new_scan())
        {
            Application.m_lidar.consume_scan();
            m_datas_interface.evit_age_scan_ms = 0;
            m_obstacle_tracker.nouveauScan(observations,
                                           m_inputs_interface.X_robot_terrain,
                                           m_inputs_interface.Y_robot_terrain,
                                           capTerrainRobot(),
                                           m_date_ms);
        }
        else
        {
            m_obstacle_tracker.extrapoler(m_date_ms);
            const unsigned long age = (unsigned long)m_datas_interface.evit_age_scan_ms
                                    + (unsigned long)(PERIODE_APPEL_MODELIA * 1000.f);
            m_datas_interface.evit_age_scan_ms = (age > 60000UL) ? 60000 : (unsigned short)age;
        }

        // Indicateurs du suivi, pour le réglage et la télémétrie
        m_datas_interface.evit_nb_pistes = (unsigned char)m_obstacle_tracker.count();
        const tObstacleTrack *piste = m_obstacle_tracker.plusProche(m_inputs_interface.X_robot_terrain,
                                                                   m_inputs_interface.Y_robot_terrain);
        if (piste) {
            m_datas_interface.evit_piste_proche_X_cm = piste->X_cm;
            m_datas_interface.evit_piste_proche_Y_cm = piste->Y_cm;
            m_datas_interface.evit_piste_proche_V_cms = sqrtf(piste->Vx_cms*piste->Vx_cms
                                                            + piste->Vy_cms*piste->Vy_cms);
            m_datas_interface.evit_piste_proche_statique = piste->statique;
        }
        else {
            m_datas_interface.evit_piste_proche_V_cms = 0.f;
            m_datas_interface.evit_piste_proche_statique = false;
        }

        // ---- Couche 3 : évaluation tactique. Quelle piste gêne, et à quel point.
        // Le couloir suit la TRAJECTOIRE et non l'axe géométrique du robot : en marche arrière,
        // c'est le cap opposé qu'il faut surveiller.
        const float cap_trajectoire = (sens_reference_detection >= 0.f) ? capTerrainRobot()
                                                                       : capTerrainRobot() + (float)M_PI;
        m_evaluateur_tactique.evaluer(m_obstacle_tracker,
                                      m_inputs_interface.X_robot_terrain,
                                      m_inputs_interface.Y_robot_terrain,
                                      cap_trajectoire,
                                      fabsf(Application.m_asservissement.vitesse_avance_robot_filt));
        const tMenace &menace = m_evaluateur_tactique.menace();
        m_datas_interface.evit_menace = menace.niveau;
        m_datas_interface.evit_D_cm = menace.D_cm;
        m_datas_interface.evit_phi_rad = menace.phi_rad;
        m_datas_interface.evit_ttc_s = menace.ttc_s;
        m_datas_interface.evit_dmin_cm = menace.dmin_cm;
        m_datas_interface.evit_cote_libre = menace.cote_libre;

        //afin de réutiliser l'évitement existant
        // Permet de reconstituer une valeur entre 0 et 15 représentant toutes les situations de blocage
        m_datas_interface.evit_detection_obstacle_bitfield =
                (m_inputs_interface.obstacle_ARG << 3) |
                (m_inputs_interface.obstacle_ARD << 2) |
                (m_inputs_interface.obstacle_AVG << 1) |
                (m_inputs_interface.obstacle_AVD << 0);
    }//fin Traitement LIDAR pour évitement
	//Traitements capteurs US pour évitement
	else
	{
        // Le lidar est hors service : les pistes et le verdict tactique deviennent faux, on ne les
        // garde pas. La chaîne US reprend la main, inchangée.
        m_obstacle_tracker.init();
        m_evaluateur_tactique.init();
        m_datas_interface.evit_nb_pistes = 0;
        m_datas_interface.evit_menace = MENACE_LIBRE;
        m_datas_interface.evit_piste_proche_V_cms = 0.f;
        m_datas_interface.evit_piste_proche_statique = false;
        m_datas_interface.evit_cote_libre = 0;

        Application.m_detection_obstacles.setSeuilDetectionObstacle(SEUIL_DETECTION_US);

        //    inhibition forcée de la détection d'obstacle
		if (m_datas_interface.evit_inhibe_obstacle) {
            Application.m_detection_obstacles.inhibeDetection(false);
		}
		//    Tient compte de la position du robot sur le terrain pour inhiber les obstacles
		//      -> Trop proche des bordures -> inhibe la détection
		//      Inhibe soit les capteurs AV soit les capteurs AR en fonction de l'angle robot et de la proximité bordure si l'obstacle est détecté en dehors du terrain
		else if (m_datas_interface.evit_force_obstacle == false) {
			m_datas_interface.proximite_bordure_Xdroite = m_inputs_interface.X_robot_terrain > X_MAX_INTERDIT_DETECTION;
			m_datas_interface.proximite_bordure_Xgauche = m_inputs_interface.X_robot_terrain < X_MIN_INTERDIT_DETECTION;
			m_datas_interface.proximite_bordure_Ybasse = m_inputs_interface.Y_robot_terrain < Y_MIN_INTERDIT_DETECTION;
			m_datas_interface.proximite_bordure_Yhaute = m_inputs_interface.Y_robot_terrain > Y_MAX_INTERDIT_DETECTION;
			m_datas_interface.inhibe_detection_AV = false;
			m_datas_interface.inhibe_detection_AR = false;

			if (m_datas_interface.proximite_bordure_Ybasse) {
				if ( (m_inputs_interface.angle_robot_terrain >= -3.14) && (m_inputs_interface.angle_robot_terrain <= 0) ) {
				   m_datas_interface.inhibe_detection_AV = true;
				}
				if ( (m_inputs_interface.angle_robot_terrain >= 0.) && (m_inputs_interface.angle_robot_terrain <= 3.14) ) {
				   m_datas_interface.inhibe_detection_AR = true;
				}
			}
			if (m_datas_interface.proximite_bordure_Yhaute) {
				if ( (m_inputs_interface.angle_robot_terrain >= -3.14) && (m_inputs_interface.angle_robot_terrain <= 0) ) {
				   m_datas_interface.inhibe_detection_AR = true;
				}
				if ( (m_inputs_interface.angle_robot_terrain >= 0.) && (m_inputs_interface.angle_robot_terrain <= 3.14) ) {
				   m_datas_interface.inhibe_detection_AV = true;
				}
			}
			if (m_datas_interface.proximite_bordure_Xgauche) {
				if (    ((m_inputs_interface.angle_robot_terrain >= 1.57) && (m_inputs_interface.angle_robot_terrain <= 3.14) )
					 || ((m_inputs_interface.angle_robot_terrain <= -1.57) && (m_inputs_interface.angle_robot_terrain >= -3.14))
				   ) {
				   m_datas_interface.inhibe_detection_AV = true;
				}
				if (    ((m_inputs_interface.angle_robot_terrain >= 0) && (m_inputs_interface.angle_robot_terrain <= 1.57) )
					 || ((m_inputs_interface.angle_robot_terrain >= -1.57) && (m_inputs_interface.angle_robot_terrain <= 0.))
				   ) {
				   m_datas_interface.inhibe_detection_AR = true;
				}
			}
			if (m_datas_interface.proximite_bordure_Xdroite) {
				if (    ((m_inputs_interface.angle_robot_terrain >= 1.57) && (m_inputs_interface.angle_robot_terrain <= 3.14) )
					 || ((m_inputs_interface.angle_robot_terrain <= -1.57) && (m_inputs_interface.angle_robot_terrain >= -3.14))
				   ) {
				   m_datas_interface.inhibe_detection_AR = true;
				}
				if (    ((m_inputs_interface.angle_robot_terrain >= 0) && (m_inputs_interface.angle_robot_terrain <= 1.57) )
					 || ((m_inputs_interface.angle_robot_terrain >= -1.57) && (m_inputs_interface.angle_robot_terrain <= 0.))
				   ) {
				   m_datas_interface.inhibe_detection_AV = true;
				}
			}
			Application.m_detection_obstacles.inhibeDetectionAV(m_datas_interface.inhibe_detection_AV);
			Application.m_detection_obstacles.inhibeDetectionAR(m_datas_interface.inhibe_detection_AR);
		}
		else {
			Application.m_detection_obstacles.inhibeDetection(false);
		}

		m_inputs_interface.obstacle_AVG        = Application.m_detection_obstacles.isObstacleAVG();
		m_inputs_interface.obstacle_AVD        = Application.m_detection_obstacles.isObstacleAVD();
        m_inputs_interface.obstacle_ARG        = Application.m_detection_obstacles.isObstacleARG() || Application.m_detection_obstacles.isObstacleARGCentre();
        m_inputs_interface.obstacle_ARD        = Application.m_detection_obstacles.isObstacleARD() || Application.m_detection_obstacles.isObstacleARDCentre();
        m_inputs_interface.obstacleDetecte_non_filtre     = Application.m_detection_obstacles.isObstacle();

		// Permet de reconstituer une valeur entre 0 et 15 représentant toutes les situations de blocage
		m_datas_interface.evit_detection_obstacle_bitfield =
				(m_inputs_interface.obstacle_ARG << 3) |
				(m_inputs_interface.obstacle_ARD << 2) |
				(m_inputs_interface.obstacle_AVG << 1) |
				(m_inputs_interface.obstacle_AVD << 0);
	}//fin Traitements capteurs US pour évitement

    // Mise en forme de données pour le modèle
    m_inputs_interface.FrontM_Convergence = m_inputs_interface.Convergence && !m_inputs_interface.Convergence_old;
    m_inputs_interface.Convergence_old = m_inputs_interface.Convergence;

    m_inputs_interface.FrontM_Convergence_rapide = m_inputs_interface.Convergence_rapide && !m_inputs_interface.Convergence_rapide_old;
    m_inputs_interface.Convergence_rapide_old = m_inputs_interface.Convergence_rapide;

    m_inputs_interface.FrontM_ConvergenceRack = m_inputs_interface.ConvergenceRack && !m_inputs_interface.ConvergenceRack_old;
    m_inputs_interface.ConvergenceRack_old = m_inputs_interface.ConvergenceRack;

    // filtrage de l'info obstacleDetecte_non_filtre utilise pour passer en evitement d'obstacle
    //   -> filtre de confirmation de detection => filtrage a l'apparition de l'obstacle
    //   -> filtre de confirmation de disparition => l'obstacle doit etre absent pendant
    //      FILTRE_DISPARITION_OBSTACLE_LIDAR (ou _US) passages consecutifs avant de retomber.
    //      Etape 0 de l'atelier evitement 2027 : a 50 Hz, un scan lidar manque couvre 6 passages, et
    //      une tache intermittente faisait clignoter l'entree en evitement. Seuil nul cote capteurs
    //      US, donc comportement strictement identique a l'existant sur cette chaine.
    if (m_inputs_interface.obstacleDetecte_non_filtre) {
        if (m_datas_interface.cpt_filtrage_obstacle_detecte < UINT32_MAX) m_datas_interface.cpt_filtrage_obstacle_detecte++;
        m_datas_interface.cpt_filtrage_disparition_obstacle = 0;
    }
    else {
        m_datas_interface.cpt_filtrage_obstacle_detecte = 0;
        if (m_datas_interface.cpt_filtrage_disparition_obstacle < UINT32_MAX) m_datas_interface.cpt_filtrage_disparition_obstacle++;
    }
    const unsigned int filtre_disparition = (m_inputs_interface.m_lidar_status == LidarUtils::LIDAR_OK) ?
                                            FILTRE_DISPARITION_OBSTACLE_LIDAR : FILTRE_DISPARITION_OBSTACLE_US;
    if (m_datas_interface.cpt_filtrage_obstacle_detecte > FILTRE_CONFIRMATION_OBSTACLE_DETECTE) {
        m_inputs_interface.obstacleDetecte = true;
    }
    else if (m_datas_interface.cpt_filtrage_disparition_obstacle > filtre_disparition) {
        m_inputs_interface.obstacleDetecte = false;
    }


    stepAllStateMachines();
}




// ________________________________________________
/*!
 * \brief Traite un point lidar pour la détection d'obstacle (émulation des 4 capteurs US)
 * \param distance_detectee distance du point [mm], LidarUtils::NO_OBSTACLE si pas de mesure
 * \param angle_detectee angle du point par rapport à l'axe du robot [degrés]
 * \param sens_reference sens de déplacement de référence : >0 marche avant, <0 marche arrière
 *
 * Les drapeaux obstacle_AVG/AVD/ARG/ARD sont CUMULÉS (OU logique) d'un point à l'autre :
 * l'appelant les remet à zéro avant le premier point et reconstitue le champ de bits après
 * le dernier.
 */
void IA::traiterPointLidar(double distance_detectee, double angle_detectee, float sens_reference)
{
    //Si le point est trop lointain on ne traite pas
    if(distance_detectee!=LidarUtils::NO_OBSTACLE)
    {
        //angle de l'obstacle par rapport à l'axe du robot (converti en radian)
        float _Phi=CDetectionObstaclesBase::modulo_pi(M_PI*angle_detectee/180);	// [degres signe / -180;+180]

        //distance de l'obstacle
        int _D=(distance_detectee/10);	// [mm] converti en [cm]
        //angle du robot dans le repère terrain (une seule convention, cf. capTerrainRobot())
        float _teta=capTerrainRobot();

        //#	coordonnées en X,Y des points détectés
        float X_detected = m_inputs_interface.X_robot_terrain + _D*cos(_teta+_Phi);
        float Y_detected = m_inputs_interface.Y_robot_terrain + _D*sin(_teta+_Phi);


        //est-ce que le point détecté par le lidar est hors du terrain
        bool isOutOfField=((X_detected<=10.) || (X_detected>=290.) || (Y_detected<=10.) || (Y_detected>=190.));

        //# D et Phi sur la trajectoire du robot en excluant les points détectés hors du terrain (plus besoin d'inhiber la détection)
        if((!isOutOfField) && (_D>0) && (_D<SEUIL_DETECTION_LIDAR))
        {
            // Couloir de demi-largeur SEUIL_DETECTION_LIDAR_TRANSVERSE, du seul côté où l'on se déplace
            if (Application.m_detection_obstacles.isObstacleLIDARDansSens(_D, _Phi, SEUIL_DETECTION_LIDAR_TRANSVERSE, sens_reference))
            {
                m_inputs_interface.obstacleDetecte_non_filtre=true;
                m_datas_interface.nombre_obstacles_presents++;
                // Cumul : un point ne doit pas effacer le quadrant d'un point précédent
                m_inputs_interface.obstacle_AVG |= ((_Phi<=(M_PI/2)) && (_Phi>=0));
                m_inputs_interface.obstacle_AVD |= ((_Phi>=(-M_PI/2)) && (_Phi<0));
                m_inputs_interface.obstacle_ARG |= ((_Phi>(M_PI/2))&&(_Phi<=(M_PI)));
                m_inputs_interface.obstacle_ARD |= ((_Phi<(-M_PI/2))&&(_Phi>(-M_PI)));

                // Obstacle détecté le plus proche, publié en télémétrie dans la trame
                // ETAT_DETECTION_EVITEMENT_OBSTACLE (ces deux champs restaient jusqu'ici vides)
                if (distance_detectee < m_datas_interface.distance_premier_obstacle_detecte) {
                    m_datas_interface.distance_premier_obstacle_detecte = (unsigned short)distance_detectee;       // [mm]
                    m_datas_interface.angle_premier_obstacle_detecte = (signed short)roundf(_Phi*180.0f/M_PI);   // [degrés]
                }
            }
        }
    }
}

// ________________________________________________
/*!
 * \brief Sens de déplacement de référence pour la détection lidar : +1 marche avant, -1 arrière
 *
 * getSensDeplacement() rend le signe de l'erreur de distance de l'asservissement : il vaut
 * toujours +1 ou -1, jamais 0, et robot arrêté il ne traduit que le signe d'un résidu. Tant que
 * la détection testait sens>0 pour l'avant comme pour l'arrière, cela passait inaperçu ; une fois
 * l'arrière corrigé (sens<0), un robot arrêté face à l'adversaire pourrait ne plus le voir une
 * fois sur deux, et sortir de l'évitement alors que la voie est toujours bouchée. D'où :
 *  - pendant un évitement : le sens mémorisé à son entrée (evit_sens_avant_detection), celui
 *    dans lequel on veut repartir -- le freinage, avec son éventuel dépassement de consigne, ne
 *    doit pas le retourner ;
 *  - hors évitement, en mouvement franc (erreur de distance au-delà du seuil de convergence) :
 *    le sens courant, qui est alors mémorisé ;
 *  - hors évitement, à l'arrêt : le dernier sens de mouvement franc.
 */
float IA::calculerSensReferenceDetection()
{
    const float sens_courant = Application.m_asservissement.getSensDeplacement();
    const bool mouvement_franc = fabsf(Application.m_asservissement.erreur_distance)
                                 > Application.m_asservissement.seuil_conv_distance;

    if (m_datas_interface.evitementEnCours) {
        return m_datas_interface.evit_sens_avant_detection;
    }
    if (mouvement_franc) {
        m_datas_interface.evit_dernier_sens_franc = sens_courant;
        return sens_courant;
    }
    return m_datas_interface.evit_dernier_sens_franc;
}

// ________________________________________________
/*!
 * \brief Cap du robot dans le repère TERRAIN [rad], pour projeter un point vu par le lidar
 *
 * Les coordonnées terrain se déduisent de celles de l'asservissement par une translation
 * (couleur 1) ou par une symétrie centrale (couleur 2) : le cap du robot dans le repère terrain
 * vaut donc angle_robot, ou angle_robot + PI.
 *
 * ATTENTION : angle_robot_terrain n'est PAS ce cap. C'est le cap RELATIF AU DÉPART
 * (angle_robot - ANGLE_ROBOT_TERRAIN_INIT, soit 90 degrés d'écart cette année) ; s'en servir pour
 * projeter un point ferait pivoter d'un quart de tour tout ce que voit le lidar.
 */
float IA::capTerrainRobot()
{
    if (m_datas_interface.couleur_equipe == SM_DatasInterface::EQUIPE_COULEUR_1) {
        return m_inputs_interface.angle_robot;
    }
    return m_inputs_interface.angle_robot + (float)M_PI;
}
