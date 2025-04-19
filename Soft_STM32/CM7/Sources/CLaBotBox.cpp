/*! \file CLaBotBox.cpp
	\brief Classe qui contient les méthodes pour le dialogue avec ANACONBOT
*/
#include "CLaBotBox.h"
#include "RessourcesHardware.h"
#include "CGlobale.h"

//___________________________________________________________________________
 /*!
   \brief Constructeur

   \param --
   \return --
*/
CLaBotBox::CLaBotBox() 
{
    m_rx_enabled = false;
    m_tx_enabled = false;
    initListeTrames();
}

//___________________________________________________________________________
 /*!
   \brief Destructeur

   \param --
   \return --
*/
CLaBotBox::~CLaBotBox() 
{

}

//___________________________________________________________________________
 /*!
   \brief Créé la liste des trames.
    En cas d'ajout d'une trame à la messagerie, ajouter cette trame à la liste

   \param --
   \return --
*/
void CLaBotBox::initListeTrames()
{
    m_nombre_trames = 0;

    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_POWER_ELECTROBOT;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_POWER_ELECTROBOT;
    m_liste_trames[m_nombre_trames++] = &m_ELECTROBOT_CDE_MOTEURS;
    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_MVT_XY;
    m_liste_trames[m_nombre_trames++] = &m_ASSERV_RESET;
    m_liste_trames[m_nombre_trames++] = &m_ASSERV_DIAG_WRITE_PARAM;
    m_liste_trames[m_nombre_trames++] = &m_AUTOAPPRENTISSAGE_ASSERV;
    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_REINIT_XY_TETA;
    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_VITESSE_MVT;
    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_REGUL_VITESSE;
    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_DISTANCE_ANGLE;
    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_MVT_XY_TETA;
    m_liste_trames[m_nombre_trames++] = &m_ELECTROBOT_CDE_SERVOS;
    m_liste_trames[m_nombre_trames++] = &m_ELECTROBOT_CDE_SERVOS_AX;
    m_liste_trames[m_nombre_trames++] = &m_ELECTROBOT_CONFIG_SERVOS;
    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_MVT_MANUEL;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_PID_ASSERVISSEMENT;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_ASSERVISSEMENT;
    m_liste_trames[m_nombre_trames++] = &m_POSITION_CODEURS;
    m_liste_trames[m_nombre_trames++] = &m_POSITION_ABSOLUE_XY_TETA;
    m_liste_trames[m_nombre_trames++] = &m_ELECTROBOT_ETAT_CODEURS_1_2;
    m_liste_trames[m_nombre_trames++] = &m_ELECTROBOT_ETAT_TELEMETRES;
    m_liste_trames[m_nombre_trames++] = &m_ELECTROBOT_ETAT_CODEURS_3_4;
    m_liste_trames[m_nombre_trames++] = &m_ELECTROBOT_ETAT_CAPTEURS_2;
    m_liste_trames[m_nombre_trames++] = &m_ELECTROBOT_ETAT_CAPTEURS_1;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_ECRAN;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_MATCH;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_DETECTION_EVITEMENT_OBSTACLE;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_RACK;
    m_liste_trames[m_nombre_trames++] = &m_COLOR_SENSOR;
    m_liste_trames[m_nombre_trames++] = &m_CONFIG_PERIODE_TRAME;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_SERVO_AX;
    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_KMAR;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_KMAR_GENERAL;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_LIDAR;
    m_liste_trames[m_nombre_trames++] = &m_FREE_STRING;
    m_liste_trames[m_nombre_trames++] = &m_ETAT_CHARGE_CPU;
    m_liste_trames[m_nombre_trames++] = &m_RESET_CPU;
    m_liste_trames[m_nombre_trames++] = &m_COMMANDE_MODE_FONCTIONNEMENT_CPU;
}


//___________________________________________________________________________
/*!
   \brief Renvoie le pointeur sur la trame à partir de son identifiant.

    - Fonction appelee lorsqu'une trame valide est recue
    - Implemente le necessaire pour transformer une trame brute en signaux de la structure dediee

   \param trameRecue la trame brute recue
   \return --
   */
CTrameLaBotBox* CLaBotBox::getTrameFromID(unsigned int ID)
{
    for (unsigned int i=0; i<m_nombre_trames; i++)
    {
        if (m_liste_trames[i]) {
            if (ID == m_liste_trames[i]->m_ID)
                return m_liste_trames[i];
        }
    }
    return nullptr;
}

//___________________________________________________________________________
 /*!
   \brief Commence la communication avec Labotbox

   \param --
   \return --
*/
void CLaBotBox::Start()
{
    if (!m_rx_enabled) {
        //while (_rs232_pc_rx.readable()) _rs232_pc_rx.getc(); // Nettoie tout octet en attente dans le buffer
        for (unsigned int i=0; i<m_nombre_trames; i++) {  // Supprime les trames reçues en attente pas encore traitées
            if (m_liste_trames[i]) m_liste_trames[i]->isNewTrame();
        }
    }

    // TODO : à voir la possibilité de réactiver les IRQ RX sur huart3
    //_rs232_pc_rx.attach(this, &CLaBotBox::IRQ_ReceiveRS232);  	// Callback sur réception d'une donnée sur la RS232

    m_rx_enabled = true;
    m_tx_enabled = true;
}

//___________________________________________________________________________
 /*!
   \brief Stoppe toute communication avec Labotbox

   \param --
   \return --
*/
void CLaBotBox::Stop()
{
    StopRx();
    StopTx();
}

//___________________________________________________________________________
 /*!
   \brief Stoppe la communication entrante (uniquement) avec Labotbox

   \param --
   \return --
   \remark Cette méthode permet d'inhiber les octets entrants
            tout en laissant la possibilité d'envoyer des octets
           Une fois que le match a commencé, cela permet de sécuriser
           les informations entrantes et ne pas prendre le risque de recevoir
           une trame par erreur qui pourrait perturber le match.
*/
void CLaBotBox::StopRx()
{
    // TODO : à voir la possibilité d'interrompre les IRQ RS232 sur huart3
    //_rs232_pc_rx.attach(NULL); // Supprime l'IRQ sur réception RS232
    m_rx_enabled = false;
}
//___________________________________________________________________________
 /*!
   \brief Stoppe la communication sortante (uniquement) avec Labotbox

   \param --
   \return --
*/
void CLaBotBox::StopTx()
{
    m_tx_enabled = false;
}

//___________________________________________________________________________
 /*!
   \brief Indique si la communication entrante est activée

   \param --
   \return --
*/
bool CLaBotBox::isRxEnabled()
{
    return m_rx_enabled;
}

//___________________________________________________________________________
 /*!
   \brief Indique si la communication sortante est activée

   \param --
   \return --
*/
bool CLaBotBox::isTxEnabled()
{
    return m_tx_enabled;
}

//___________________________________________________________________________
 /*!
   \brief Réalise les traitements périodiques

   \param --
   \return --
   \remark Fonction à appeler périodiquement par la couche supérieure (toutes les 10msec)
*/
void CLaBotBox::Execute()
{
    if (m_rx_enabled)
    {
        CheckReceptionTrame();
    }

    if (m_tx_enabled)
    {
        SendTramesLaBotBox();
    }
}


// =============================================================
//                      RECEPTION
// =============================================================

// _____________________________________________________________
void CLaBotBox::IRQ_ReceiveRS232(void)
{
  //char rxData;
  //rxData = _rs232_pc_rx.getc();
  //Reconstitution(rxData);
}

//___________________________________________________________________________
 /*!
   \brief Point d'entree du module.

    - Fonction appelee lorsqu'une donnee arrive sur la liaison serie
    -   Implemente la machine d'etat de reconstitution d'une trame, de detection d'erreur, d'interception de messages specifiques

   \param newData la donnee nouvellement recue
   \return --
   */
void CLaBotBox::Reconstitution(unsigned char newData)
{
   switch(m_etatReconst)
   {
   // -----------------------------------------
   case  cETAT_INIT :
       // Initialise les champs d'une précédente réception
       Init_Reconstitution();

       // Le message est une trame
       if (newData == 'T') {
           m_etatReconst = cETAT_ID_MSB;
       }
       break;

   // -----------------------------------------
   case  cETAT_ID_MSB :
       m_trameCourante.ID = ((unsigned short)newData << 8);
       m_etatReconst = cETAT_ID_LSB;
       break;
   // -----------------------------------------
   case  cETAT_ID_LSB :
       m_trameCourante.ID |= (newData&0xFF);
       m_etatReconst = cETAT_DLC;
       break;
   // -----------------------------------------
   case  cETAT_DLC :
       m_trameCourante.DLC = newData;
       if (newData > LABOTBOX_MAX_DATA_LEN) {  // la taille du message dépasse la taille max autorisé
           m_etatReconst = cETAT_INIT;
       }
       else if (newData > 0) {  // il y a des données utiles a lire dans la trame
           m_etatReconst = cETAT_DATA_i;
       }
       else {   // aucune donnée utile, juste un message de commande
           m_etatReconst = cETAT_CHECKSUM;
       }
       break;
   // -----------------------------------------
   case cETAT_DATA_i :
       m_trameCourante.Data[m_data_number] = newData;
       m_data_number++;
       if (m_trameCourante.DLC > m_data_number)
       {  /* ne rien faire : il reste des données à recevoir */ }
       else {  // transfert des donnees utiles termine -> la prochaine donnee est le checksum
           m_etatReconst = cETAT_CHECKSUM;
       }
       break;
   // -----------------------------------------
   case  cETAT_CHECKSUM :
       if (isChecksumTrameCouranteOK(newData)) {
           DecodeTrame(&m_trameCourante);
       }
       m_etatReconst = cETAT_INIT;
       break;
   }
}


//___________________________________________________________________________
 /*!
   \brief Initialisation du module Reconstitution

    - Initialise tous les champs de la structure de donnee courante

   \param --
   \return --
   */
void CLaBotBox::Init_Reconstitution(void)
{
    m_data_number = 0;  // comptabilise le numero d'octet de donnees recu
    // Initialise les champs de la trame courante
    m_trameCourante.ID = 0xFFFF;
    m_trameCourante.DLC = 0xFF;
    for (unsigned int i=0; i<LABOTBOX_MAX_DATA_LEN; i++) {
        m_trameCourante.Data[i] = 0xFF;
    }
}



//___________________________________________________________________________
 /*!
   \brief Verifie la conformite du checksum de la trame courante

    - Calcul le checksum de la trame courante et le compare au parametre d'entree de la fonction

   \param CS_attendu le checksum attendu à  comparer avec le checksum calcule de la trame courante
   \return 	1 si le checksum est OK \n
                0 sinon
   */
unsigned char CLaBotBox::isChecksumTrameCouranteOK(unsigned char CS_attendu)
{
    unsigned char CS_calcule = 0;
    unsigned char i=0;

    CS_calcule += m_trameCourante.ID;
    CS_calcule += m_trameCourante.DLC;
    for(i=0; i<m_trameCourante.DLC; i++) {
        CS_calcule += m_trameCourante.Data[i];
    }

    return(CS_calcule == CS_attendu);
    // return(1); // toujours vrai pour les tests
}




//___________________________________________________________________________
/*!
   \brief Point d'entree du module.

    - Fonction appelee lorsqu'une trame valide est recue
    - Implemente le necessaire pour transformer une trame brute en signaux de la structure dediee

   \param trameRecue la trame brute recue
   \return --
   */
void CLaBotBox::DecodeTrame(tStructTrameLaBotBox *trameRecue)
{
    for (unsigned int i=0; i<m_nombre_trames; i++)
    {
        if (m_liste_trames[i]) {
            if (trameRecue->ID == m_liste_trames[i]->m_ID) {
                m_liste_trames[i]->Decode(trameRecue);
                return;
            }
        }
    }
}


//___________________________________________________________________________
 /*!
   \brief Verifie et traite les trames recues en attente

   \param --
   \return --
*/
void CLaBotBox::CheckReceptionTrame(void)
{
  // ___________________________
  if  (m_COMMANDE_POWER_ELECTROBOT.isNewTrame() ) {
      switch(m_COMMANDE_POWER_ELECTROBOT.commande) {
          case cCDE_PWR_ELECTROBOT_ALL_OUTPUTS :
              Application.m_power_electrobot.setAllOutputs(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case  cCDE_PWR_ELECTROBOT_OUTPUT_1:
              Application.m_power_electrobot.setOutput(PowerElectrobot::OUTPUT_STOR1, m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case  cCDE_PWR_ELECTROBOT_OUTPUT_2:
              Application.m_power_electrobot.setOutput(PowerElectrobot::OUTPUT_STOR2, m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case  cCDE_PWR_ELECTROBOT_OUTPUT_3:
              Application.m_power_electrobot.setOutput(PowerElectrobot::OUTPUT_STOR3, m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case  cCDE_PWR_ELECTROBOT_OUTPUT_4:
              Application.m_power_electrobot.setOutput(PowerElectrobot::OUTPUT_STOR4, m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case  cCDE_PWR_ELECTROBOT_OUTPUT_5:
              Application.m_power_electrobot.setOutput(PowerElectrobot::OUTPUT_STOR5, m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case  cCDE_PWR_ELECTROBOT_OUTPUT_6:
              Application.m_power_electrobot.setOutput(PowerElectrobot::OUTPUT_STOR6, m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case  cCDE_PWR_ELECTROBOT_OUTPUT_7:
              Application.m_power_electrobot.setOutput(PowerElectrobot::OUTPUT_STOR7, m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case  cCDE_PWR_ELECTROBOT_OUTPUT_8:
              Application.m_power_electrobot.setOutput(PowerElectrobot::OUTPUT_STOR8, m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case cCDE_PWR_ELECTROBOT_CHANGE_I2C_ADDR:
              Application.m_power_electrobot.changeI2CAddress(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case cCDE_PWR_ELECTROBOT_UNLOCK_EEPROM:
              Application.m_power_electrobot.unlockWriteEEPROM();
          break;
          case cCDE_PWR_ELECTROBOT_RESET_FACTORY:
              Application.m_power_electrobot.resetFactoryEEPROM();
          break;
          case cCDE_PWR_ELECTROBOT_CALIB_BATTERY_VOLTAGE_POINT1:
              Application.m_power_electrobot.setCalibrationBatteryVoltagePoint1(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case cCDE_PWR_ELECTROBOT_CALIB_BATTERY_VOLTAGE_POINT2:
              Application.m_power_electrobot.setCalibrationBatteryVoltagePoint2(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case cCDE_PWR_ELECTROBOT_CALIB_GLOBAL_CURRENT_POINT1:
              Application.m_power_electrobot.setCalibrationGlobalCurrentPoint1(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case cCDE_PWR_ELECTROBOT_CALIB_GLOBAL_CURRENT_POINT2:
              Application.m_power_electrobot.setCalibrationGlobalCurrentPoint2(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case cCDE_PWR_ELECTROBOT_CALIB_CURRENT_OUT1_POINT1:
              Application.m_power_electrobot.setCalibrationCurrentOut1Point1(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case cCDE_PWR_ELECTROBOT_CALIB_CURRENT_OUT1_POINT2:
              Application.m_power_electrobot.setCalibrationCurrentOut1Point2(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case cCDE_PWR_ELECTROBOT_CALIB_CURRENT_OUT2_POINT1:
              Application.m_power_electrobot.setCalibrationCurrentOut2Point1(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          case cCDE_PWR_ELECTROBOT_CALIB_CURRENT_OUT2_POINT2:
              Application.m_power_electrobot.setCalibrationCurrentOut2Point2(m_COMMANDE_POWER_ELECTROBOT.val);
          break;
          default :
          break;
      }
  }
  // ___________________________
  if  (m_ELECTROBOT_CDE_MOTEURS.isNewTrame() ) {
    Application.m_moteurs.CommandeVitesse(CMoteurs::MOTEUR_1, (signed char)m_ELECTROBOT_CDE_MOTEURS.cde_moteur_1);  // Attention : obligation de mettre le cast explicit en "signed", sinon, la valeur est interprétée non signée
    wait_ms(5);
    Application.m_moteurs.CommandeVitesse(CMoteurs::MOTEUR_2, (signed char)m_ELECTROBOT_CDE_MOTEURS.cde_moteur_2);
    wait_ms(5);
    Application.m_moteurs.CommandeVitesse(CMoteurs::MOTEUR_3, (signed char)m_ELECTROBOT_CDE_MOTEURS.cde_moteur_3);
    wait_ms(5);
    Application.m_moteurs.CommandeVitesse(CMoteurs::MOTEUR_4, (signed char)m_ELECTROBOT_CDE_MOTEURS.cde_moteur_4);
    wait_ms(5);
  }

  // ___________________________
  if  (m_ELECTROBOT_CDE_SERVOS.isNewTrame() ) {
        // TODO : mettre en place une classe dédiée PWM servo pour gérer :
        //          la vitesse de déplacement des servo
        //          les butées min/max
        //          les valeurs d'init
        Application.m_servos.CommandePositionVitesse(
                    m_ELECTROBOT_CDE_SERVOS.NumeroServoMoteur1,
                    m_ELECTROBOT_CDE_SERVOS.PositionServoMoteur1,
                    m_ELECTROBOT_CDE_SERVOS.VitesseServoMoteur1);
        Application.m_servos.CommandePositionVitesse(
                    m_ELECTROBOT_CDE_SERVOS.NumeroServoMoteur2,
                    m_ELECTROBOT_CDE_SERVOS.PositionServoMoteur2,
                    m_ELECTROBOT_CDE_SERVOS.VitesseServoMoteur2);
   }

  // ___________________________
  if  (m_ELECTROBOT_CDE_SERVOS_AX.isNewTrame() ) {
    // sous adressage : le champ commande_ax donne le type d'action à  réaliser

    switch (m_ELECTROBOT_CDE_SERVOS_AX.commande_ax) {
        case cSERVO_AX_POSITION :
            Application.m_servos_ax.setPosition(
                        m_ELECTROBOT_CDE_SERVOS_AX.num_servo_ax,
                        m_ELECTROBOT_CDE_SERVOS_AX.valeur_commande_ax);
        break;
        case cSERVO_AX_VITESSE :
            Application.m_servos_ax.setSpeed(
                        m_ELECTROBOT_CDE_SERVOS_AX.num_servo_ax,
                        m_ELECTROBOT_CDE_SERVOS_AX.valeur_commande_ax);
        break;

        case cSERVO_AX_CHANGE_ID :
            Application.m_servos_ax.changeID(
                        m_ELECTROBOT_CDE_SERVOS_AX.num_servo_ax,
                        m_ELECTROBOT_CDE_SERVOS_AX.valeur_commande_ax);
        break;

        case cSERVO_AX_LED_STATE :
            Application.m_servos_ax.setLed(
                        m_ELECTROBOT_CDE_SERVOS_AX.num_servo_ax,
                        m_ELECTROBOT_CDE_SERVOS_AX.valeur_commande_ax);
        break;

        case cSERVO_AX_BUTEE_MIN :
            Application.m_servos_ax.setLimitPositionMin(
                        m_ELECTROBOT_CDE_SERVOS_AX.num_servo_ax,
                        m_ELECTROBOT_CDE_SERVOS_AX.valeur_commande_ax);
            // TODO : sauvegarder dans l'EEPROM
            //sprintf(cbuff, "butee_min_servo_ax_%d", m_ELECTROBOT_CDE_SERVOS_AX.num_servo_ax);
            //Application.m_eeprom.setValue(cbuff, m_ELECTROBOT_CDE_SERVOS_AX.valeur_commande_ax);
        break;

        case cSERVO_AX_BUTEE_MAX :
            Application.m_servos_ax.setLimitPositionMax(
                        m_ELECTROBOT_CDE_SERVOS_AX.num_servo_ax,
                        m_ELECTROBOT_CDE_SERVOS_AX.valeur_commande_ax);
            // TODO : sauvegarder dans l'EEPROM
            //sprintf(cbuff, "butee_max_servo_ax_%d", m_ELECTROBOT_CDE_SERVOS_AX.num_servo_ax);
            //Application.m_eeprom.setValue(cbuff, m_ELECTROBOT_CDE_SERVOS_AX.valeur_commande_ax);
        break;

        case cSERVO_AX_POSITION_INIT :
            // TODO : sauvegarder dans l'EEPROM
            //sprintf(cbuff, "position_initiale_servo_ax_%d", m_ELECTROBOT_CDE_SERVOS_AX.num_servo_ax);
            //Application.m_eeprom.setValue(cbuff, m_ELECTROBOT_CDE_SERVOS_AX.valeur_commande_ax);
        break;

        default :
        break; //  ne rien faire

    } // switch commande_ax

   }

  // ___________________________
  if  (m_ELECTROBOT_CONFIG_SERVOS.isNewTrame() ) {
    // sous adressage : le champ commande_sd20 donne le type d'action à  réaliser
    switch (m_ELECTROBOT_CONFIG_SERVOS.commande) {
        case cCONFIG_SERVO_POSITION :
        CdeServo(m_ELECTROBOT_CONFIG_SERVOS.num_servo,
                 m_ELECTROBOT_CONFIG_SERVOS.valeur_commande);
        break;

        case cCONFIG_SERVO_BUTEE_MIN :
            Application.m_servos.setButeeMinPosition(
                        m_ELECTROBOT_CONFIG_SERVOS.num_servo,
                        m_ELECTROBOT_CONFIG_SERVOS.valeur_commande);
            //sprintf(cbuff, "butee_min_servo_sd20_%d", m_ELECTROBOT_CONFIG_SERVOS.num_servo_sd20);
            //Application.m_eeprom.setValue(cbuff, m_ELECTROBOT_CONFIG_SERVOS.valeur_commande_sd20);
        break;

        case cCONFIG_SERVO_BUTEE_MAX :
            Application.m_servos.setButeeMaxPosition(
                        m_ELECTROBOT_CONFIG_SERVOS.num_servo,
                        m_ELECTROBOT_CONFIG_SERVOS.valeur_commande);
            //sprintf(cbuff, "butee_max_servo_sd20_%d", m_ELECTROBOT_CONFIG_SERVOS.num_servo_sd20);
            //Application.m_eeprom.setValue(cbuff, m_ELECTROBOT_CONFIG_SERVOS.valeur_commande_sd20);
        break;

        case cCONFIG_SERVO_POSITION_INIT :
            //sprintf(cbuff, "position_initiale_servo_sd20_%d", m_ELECTROBOT_CONFIG_SERVOS.num_servo_sd20);
            //Application.m_eeprom.setValue(cbuff, m_ELECTROBOT_CONFIG_SERVOS.valeur_commande_sd20);
        break;

        default :
        break; //  ne rien faire

    } // switch commande_sd20
   }
  // ___________________________
  if  (m_ASSERV_DIAG_WRITE_PARAM.isNewTrame() ) {
    float fval_coef100 	= (float)m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE / 100.0f;
    //float fval_coef10 	= (float)m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE / 10.0f;
    // sous adressage : le champ commande_ax donne le type d'action à  réaliser
    switch (m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_PARAM) {
        case cASSERV_SEUIL_CONV_DIST :
            Application.m_asservissement.seuil_conv_distance=fval_coef100;
            Application.m_eeprom.write_float(EEPROM_MAPPING::SEUIL_CONV_DISTANCE, fval_coef100);
        break;

        case cASSERV_SEUIL_CONV_ANGLE :
            Application.m_asservissement.seuil_conv_angle=fval_coef100;
            Application.m_eeprom.write_float(EEPROM_MAPPING::SEUIL_CONV_ANGLE, fval_coef100);
        break;

        case cASSERV_DIAG_WR_KI_ANGLE :
            Application.m_asservissement.ki_angle=fval_coef100;
            Application.m_eeprom.write_float(EEPROM_MAPPING::KI_ANGLE, fval_coef100);
        break;

        case cASSERV_DIAG_WR_KP_ANGLE :
            Application.m_asservissement.kp_angle=fval_coef100;
            Application.m_eeprom.write_float(EEPROM_MAPPING::KP_ANGLE, fval_coef100);
        break;

        case cASSERV_DIAG_WR_KI_DISTANCE :
            Application.m_asservissement.ki_distance=fval_coef100;
            Application.m_eeprom.write_float(EEPROM_MAPPING::KI_DISTANCE, fval_coef100);
        break;

        case cASSERV_DIAG_WR_KP_DISTANCE :
            Application.m_asservissement.kp_distance=fval_coef100;
            Application.m_eeprom.write_float(EEPROM_MAPPING::KP_DISTANCE, fval_coef100);
        break;

        case cASSERV_DIAG_WR_CDE_MIN :
            Application.m_asservissement.cde_min=m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE;
            Application.m_eeprom.write_int32(EEPROM_MAPPING::CDE_MIN, m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE);
        break;

        case cASSERV_DIAG_WR_CDE_MAX :
            Application.m_asservissement.cde_max=m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE;
            Application.m_eeprom.write_uint32(EEPROM_MAPPING::CDE_MAX, m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE);
        break;

        case cASSERV_DIAG_WR_K_ANGLE :
            Application.m_asservissement.k_angle=fval_coef100;
            Application.m_eeprom.write_float(EEPROM_MAPPING::K_ANGLE, fval_coef100);
        break;

    case cASSERV_DIAG_WR_COMPTEUR_MAX :
        Application.m_asservissement.cde_max=m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE;
        Application.m_eeprom.write_uint32(EEPROM_MAPPING::COMPTEUR_MAX, m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE);
    break;

    case cASSERV_DIAG_WR_ZONE_MORTE_D :
        Application.m_asservissement.zone_morte_D=m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE;
        Application.m_eeprom.write_uint32(EEPROM_MAPPING::ZONE_MORTE_D, m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE);
    break;

    case cASSERV_DIAG_WR_ZONE_MORTE_G :
        Application.m_asservissement.zone_morte_G=m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE;
        Application.m_eeprom.write_uint32(EEPROM_MAPPING::ZONE_MORTE_G, m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE);
    break;

/*
        case cASSERV_DIAG_RACK_CDE_MAX :
            Application.m_asservissement_chariot.setCommandeMax(m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE);
            Application.m_eeprom.setValue("rackCommandeMax", (float)m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE);
            break;

        case cASSERV_DIAG_RACK_K_POSVIT :
            Application.m_asservissement_chariot.setGainPosVit(fval_coef100);
            Application.m_eeprom.setValue("rackGainPosVit", (float)fval_coef100);
        break;

        case cASSERV_DIAG_RACK_KP :
            Application.m_asservissement_chariot.setGainP(fval_coef100);
            Application.m_eeprom.setValue("rackGainP", (float)fval_coef100);
        break;

        case cASSERV_DIAG_RACK_KI :
            Application.m_asservissement_chariot.setGainI(fval_coef100);
            Application.m_eeprom.setValue("rackGainI", (float)fval_coef100);
        break;

        case cASSERV_DIAG_RACK_CONV :
            Application.m_asservissement_chariot.setSeuilConv(m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE);
            Application.m_eeprom.setValue("rackSeuilConv", (float)m_ASSERV_DIAG_WRITE_PARAM.ASSERV_DIAG_WRITE_VALUE);
        break;
*/
    } // switch
  }

  // ___________________________
  if  (m_COMMANDE_MVT_MANUEL.isNewTrame() ) {
      Application.m_asservissement.CommandeManuelle(
                  m_COMMANDE_MVT_MANUEL.PuissanceMotG,
                  m_COMMANDE_MVT_MANUEL.PuissanceMotD);
  }
  // ___________________________
  if  (m_COMMANDE_DISTANCE_ANGLE.isNewTrame() ) {
      Application.m_asservissement.CommandeMouvementDistanceAngle(
                  m_COMMANDE_DISTANCE_ANGLE.distance_consigne,
                  BRUTE2PHYS_angle_consigne(m_COMMANDE_DISTANCE_ANGLE.angle_consigne));
  }
  // ___________________________
  if  (m_COMMANDE_MVT_XY.isNewTrame() ) {
      Application.m_asservissement.CommandeMouvementXY(
                  m_COMMANDE_MVT_XY.X_consigne,
                  m_COMMANDE_MVT_XY.Y_consigne);
  }
  // ___________________________
  if  (m_COMMANDE_MVT_XY_TETA.isNewTrame() ) {
        Application.m_asservissement.CommandeMouvementXY_TETA(
                m_COMMANDE_MVT_XY_TETA.X_consigne,
                m_COMMANDE_MVT_XY_TETA.Y_consigne,
                BRUTE2PHYS_angle_consigne(m_COMMANDE_MVT_XY_TETA.angle_consigne));
    }
  // ___________________________
  if  (m_COMMANDE_VITESSE_MVT.isNewTrame() ) {
      Application.m_asservissement.CommandeVitesseMouvement(
                  (float)m_COMMANDE_VITESSE_MVT.vitesse_avance_max,
                  (float)m_COMMANDE_VITESSE_MVT.vitesse_rotation_max);

      //TODO : a quelle variable relier les indices de sportivité de la trame
      //m_COMMANDE_VITESSE_MVT.indice_sportivite_decel;
      Application.m_asservissement.Ind_perfo=m_COMMANDE_VITESSE_MVT.indice_sportivite_accel;
  }
  // ___________________________
  if (m_COMMANDE_REINIT_XY_TETA.isNewTrame()){
      Application.m_asservissement.setPosition_XYTeta(
                  m_COMMANDE_REINIT_XY_TETA.reinit_x_pos,
                  m_COMMANDE_REINIT_XY_TETA.reinit_y_pos,
                  BRUTE2PHYS_angle_consigne(m_COMMANDE_REINIT_XY_TETA.reinit_teta_pos));
  }
  // ___________________________
  if  (m_ETAT_ECRAN.isNewTrame() ) {
      switch(m_ETAT_ECRAN.CodeCommande) {
      // _________________________________________
      case LBB_CMDE_CHOIX_EQUIPE : // Choix couleur équipe
          Application.m_modelia.m_inputs_interface.dde_couleur_equipe = m_ETAT_ECRAN.Valeur;
          break;
      // _________________________________________
      case LBB_CMDE_TEST_ACTIONNEURS :
          Application.m_modelia.m_inputs_interface.dde_test_actionneurs=1;
          break;
      // _________________________________________
      case LBB_CMDE_CHOIX_NUMERO_STRATEGIE : //Choix de la stratégie
          Application.m_modelia.setStrategie(m_ETAT_ECRAN.Valeur);
          break;
      // _______________________
      default :
          //_led1 = !_led1;
          break;
      } // switch
  }
  // ___________________________
  if  (m_CONFIG_PERIODE_TRAME.isNewTrame() ) {
      // Valeur particulière pour indiquer que la demande concerne toutes les trames d'un seul coup
      if (m_CONFIG_PERIODE_TRAME.ID == 0xFFFF)
      {
          setAllTransmitPeriod(m_CONFIG_PERIODE_TRAME.Periode);
      }
      else
      {
          CTrameLaBotBox *trame = getTrameFromID(m_CONFIG_PERIODE_TRAME.ID);
          if (trame)
          {
              trame->setTransmitPeriod(m_CONFIG_PERIODE_TRAME.Periode);
          }
      }
  }
  // ___________________________
  if (m_MBED_CMDE_TRAME.isNewTrame())
  {
/*
      Application.m_modelia.m_datas_interface.m_rx_code_cmd=m_MBED_CMDE_TRAME.CodeCommande;
      Application.m_modelia.m_datas_interface.m_rx_value_01=m_MBED_CMDE_TRAME.Valeur_01;
      Application.m_modelia.m_datas_interface.m_rx_value_02=m_MBED_CMDE_TRAME.Valeur_02;
      Application.m_modelia.m_datas_interface.m_rx_value_03=m_MBED_CMDE_TRAME.Valeur_03;
      Application.m_modelia.m_datas_interface.m_rx_value_04=m_MBED_CMDE_TRAME.Valeur_04;
*/
  }
  // ___________________________
  if (m_COMMANDE_KMAR.isNewTrame())
  {
/*
      CKmarBase *selected_kmar = nullptr;
      if (m_COMMANDE_KMAR.num_kmar == 1) selected_kmar = &Application.m_kmar;
      // TODO: ajouter ici l'aiguillage si plusieurs Kmar sur le même robot
      else                               selected_kmar = &Application.m_kmar;  // pour éviter un pointeur null
      if (selected_kmar) {
          switch(m_COMMANDE_KMAR.cmd_kmar) {
          // ___________________________
          case CTrameLaBotBox_COMMANDE_KMAR::KMAR_CMD_MOUVEMENT:
              selected_kmar->start(m_COMMANDE_KMAR.value_cmd_kmar);
              break;
          // ___________________________
          case CTrameLaBotBox_COMMANDE_KMAR::KMAR_CMD_VITESSE :
              selected_kmar->setSpeedFactor(m_COMMANDE_KMAR.value_cmd_kmar/100.);
              break;
          // ___________________________
          case CTrameLaBotBox_COMMANDE_KMAR::KMAR_CMD_STOP_AND_FIX_POSITION :
              selected_kmar->stop();
              break;
          // ___________________________
          case CTrameLaBotBox_COMMANDE_KMAR::KMAR_CMD_STOP_AND_DISARM_ALL :
              selected_kmar->emergencyStop();
              break;
          // ___________________________
          case CTrameLaBotBox_COMMANDE_KMAR::KMAR_CMD_ARM_ALL :
              selected_kmar->arm();
              break;
          // ___________________________
          case CTrameLaBotBox_COMMANDE_KMAR::KMAR_CMD_DISARM_AXIS :
              selected_kmar->disarm(m_COMMANDE_KMAR.value_cmd_kmar);
              break;
          // ___________________________
          case CTrameLaBotBox_COMMANDE_KMAR::KMAR_CMD_ARM_AXIS :
              selected_kmar->arm(m_COMMANDE_KMAR.value_cmd_kmar);
              break;
          // ___________________________
          case CTrameLaBotBox_COMMANDE_KMAR::KMAR_CMD_CATCH_OBJECT :
              selected_kmar->catchObject();
              break;
          // ___________________________
          case CTrameLaBotBox_COMMANDE_KMAR::KMAR_CMD_RELEASE_OBJECT :
              selected_kmar->releaseObject();
              break;
          // ___________________________
          default:  // ne rien faire
              break;
          }
      }
*/
  }
  // ___________________________
  if (m_ETAT_LIDAR.isNewTrame())
  {
/*
      LidarUtils::copy_tab_obstacles(m_ETAT_LIDAR.m_obstacles, Application.m_modelia.m_inputs_interface.m_lidar_obstacles);
      Application.m_modelia.m_inputs_interface.m_lidar_status = m_ETAT_LIDAR.m_status;
*/
  }
  else // recherche une perte de communication et force le statut LIDAR si c'est le cas
  {
/*
      const int LOST_COM_ETAT_LIDAR = 500; // msec
      int _current_time = getTime();
      if ((_current_time - m_ETAT_LIDAR.m_last_time_rx) > LOST_COM_ETAT_LIDAR) {
        Application.m_modelia.m_inputs_interface.m_lidar_status = LidarUtils::LIDAR_DISCONNECTED;
      }
  */
  }

  // ___________________________
  if (m_RESET_CPU.isNewTrame())
  {
      if (m_RESET_CPU.secure_code == 0x69) {
          reset_cpu(RESET_CPU_SECURE_CODE);
      }
  }
  // ___________________________
  if (m_COMMANDE_MODE_FONCTIONNEMENT_CPU.isNewTrame())
  {
      Application.m_eeprom.write_uint32(EEPROM_MAPPING::MODE_FONCTIONNEMENT, m_COMMANDE_MODE_FONCTIONNEMENT_CPU.ModeFonctionnement);
  }
}



// =============================================================
//                      EMISSION
// =============================================================

//___________________________________________________________________________
 /*!
   \brief Envoie les trames vers LABOTBOX

   \param --
   \return --
*/
void CLaBotBox::SendTramesLaBotBox(void)
{
    tStructTrameLaBotBox trame;

    // _____________________________________________
    if (m_ETAT_ASSERVISSEMENT.isTimeToSend())
    {
        m_ETAT_ASSERVISSEMENT.cde_moteur_G = (int)Application.m_roues.m_cde_roue_G;
        m_ETAT_ASSERVISSEMENT.cde_moteur_D = (int)Application.m_roues.m_cde_roue_D;
        m_ETAT_ASSERVISSEMENT.Convergence = (Application.m_asservissement.diag_blocage==1)?2:Application.m_asservissement.convergence_conf;
        m_ETAT_ASSERVISSEMENT.ModeAsservissement = Application.m_asservissement.ModeAsservissement;
        SerialiseTrame(m_ETAT_ASSERVISSEMENT.Encode(&trame));
    }
    // _____________________________________________
    if (m_POSITION_CODEURS.isTimeToSend())
    {
        m_POSITION_CODEURS.PosCodeurG = Application.m_roues.getCodeurG();
        m_POSITION_CODEURS.PosCodeurD = Application.m_roues.getCodeurD();
        SerialiseTrame(m_POSITION_CODEURS.Encode(&trame));
    }
    // _____________________________________________
    if (m_POSITION_ABSOLUE_XY_TETA.isTimeToSend())
    {
        m_POSITION_ABSOLUE_XY_TETA.x_pos = PHYS2BRUTE_x_pos(Application.m_asservissement.X_robot);
        m_POSITION_ABSOLUE_XY_TETA.y_pos = PHYS2BRUTE_y_pos(Application.m_asservissement.Y_robot);
        m_POSITION_ABSOLUE_XY_TETA.teta_pos = PHYS2BRUTE_teta_pos(Application.m_asservissement.angle_robot);
        SerialiseTrame(m_POSITION_ABSOLUE_XY_TETA.Encode(&trame));
    }
    // _____________________________________________
    if (m_ETAT_PID_ASSERVISSEMENT.isTimeToSend())
    {
        m_ETAT_PID_ASSERVISSEMENT.vitesse_avance_robot_filt      = PHYS2BRUTE_vitesse_avance_robot_filt(Application.m_asservissement.vitesse_avance_robot_filt);
        m_ETAT_PID_ASSERVISSEMENT.consigne_vitesse_avance_filt   = PHYS2BRUTE_consigne_vitesse_avance_filt(Application.m_asservissement.consigne_vitesse_avance_filt);
        m_ETAT_PID_ASSERVISSEMENT.vitesse_rotation_robot_filt    = PHYS2BRUTE_vitesse_rotation_robot_filt(Application.m_asservissement.vitesse_rotation_robot_filt);
        m_ETAT_PID_ASSERVISSEMENT.consigne_vitesse_rotation_filt = PHYS2BRUTE_consigne_vitesse_rotation_filt(Application.m_asservissement.consigne_vitesse_rotation_filt);
        SerialiseTrame(m_ETAT_PID_ASSERVISSEMENT.Encode(&trame));
    }
    // _____________________________________________
    if (m_ELECTROBOT_ETAT_CAPTEURS_1.isTimeToSend())
    {
        m_ELECTROBOT_ETAT_CAPTEURS_1.Eana1 = PHYS2BRUTE_Eana1(Application.m_electrobot.m_b_Eana1);
        m_ELECTROBOT_ETAT_CAPTEURS_1.Eana2 = PHYS2BRUTE_Eana2(Application.m_electrobot.m_b_Eana2);
        m_ELECTROBOT_ETAT_CAPTEURS_1.Eana3 = PHYS2BRUTE_Eana3(Application.m_electrobot.m_b_Eana3);
        m_ELECTROBOT_ETAT_CAPTEURS_1.Eana4 = PHYS2BRUTE_Eana4(Application.m_electrobot.m_b_Eana4);
        m_ELECTROBOT_ETAT_CAPTEURS_1.Eana5 = PHYS2BRUTE_Eana5(Application.m_electrobot.m_b_Eana5);
        m_ELECTROBOT_ETAT_CAPTEURS_1.Eana6 = PHYS2BRUTE_Eana6(Application.m_electrobot.m_b_Eana6);
        m_ELECTROBOT_ETAT_CAPTEURS_1.Eana7 = PHYS2BRUTE_Eana7(Application.m_electrobot.m_b_Eana7);
        m_ELECTROBOT_ETAT_CAPTEURS_1.Eana8 = PHYS2BRUTE_Eana8(Application.m_electrobot.m_b_Eana8);
        SerialiseTrame(m_ELECTROBOT_ETAT_CAPTEURS_1.Encode(&trame));
    }
    // _____________________________________________
    if (m_ELECTROBOT_ETAT_CAPTEURS_2.isTimeToSend())
    {
        m_ELECTROBOT_ETAT_CAPTEURS_2.Eana9 = PHYS2BRUTE_Eana9(Application.m_electrobot.m_b_Eana9);
        m_ELECTROBOT_ETAT_CAPTEURS_2.Eana10 = PHYS2BRUTE_Eana10(Application.m_electrobot.m_b_Eana10);
        m_ELECTROBOT_ETAT_CAPTEURS_2.Eana11 = PHYS2BRUTE_Eana11(Application.m_electrobot.m_b_Eana11);
        m_ELECTROBOT_ETAT_CAPTEURS_2.Eana12 = PHYS2BRUTE_Eana12(Application.m_electrobot.m_b_Eana12);
        m_ELECTROBOT_ETAT_CAPTEURS_2.Eana13 = PHYS2BRUTE_Eana13(Application.m_electrobot.m_b_Eana13);
        m_ELECTROBOT_ETAT_CAPTEURS_2.Vbat = PHYS2BRUTE_Vbat(Application.m_electrobot.m_tension_batterie);
        m_ELECTROBOT_ETAT_CAPTEURS_2.Etor1 = !Application.m_electrobot.m_b_Etor1;
        m_ELECTROBOT_ETAT_CAPTEURS_2.Etor2 = !Application.m_electrobot.m_b_Etor2;
        m_ELECTROBOT_ETAT_CAPTEURS_2.Etor3 = !Application.m_electrobot.m_b_Etor3;
        m_ELECTROBOT_ETAT_CAPTEURS_2.Etor4 = !Application.m_electrobot.m_b_Etor4;
        SerialiseTrame(m_ELECTROBOT_ETAT_CAPTEURS_2.Encode(&trame));
    }
    // _____________________________________________
    if (m_ELECTROBOT_ETAT_CODEURS_1_2.isTimeToSend())
    {
        m_ELECTROBOT_ETAT_CODEURS_1_2.Codeur_1 = Application.m_codeurs.m_CumulCodeurPosition1;
        m_ELECTROBOT_ETAT_CODEURS_1_2.Codeur_2 = Application.m_codeurs.m_CumulCodeurPosition2;
        SerialiseTrame(m_ELECTROBOT_ETAT_CODEURS_1_2.Encode(&trame));
    }
    // _____________________________________________
    if (m_ELECTROBOT_ETAT_CODEURS_3_4.isTimeToSend())
    {
        m_ELECTROBOT_ETAT_CODEURS_3_4.Codeur_3 = Application.m_codeurs.m_CumulCodeurPosition3;
        m_ELECTROBOT_ETAT_CODEURS_3_4.Codeur_4 = Application.m_codeurs.m_CumulCodeurPosition4;
        SerialiseTrame(m_ELECTROBOT_ETAT_CODEURS_3_4.Encode(&trame));
    }
    // _____________________________________________
    if (m_ELECTROBOT_ETAT_TELEMETRES.isTimeToSend())
    {
        m_ELECTROBOT_ETAT_TELEMETRES.Telemetre1 = Application.m_telemetres.getDistanceAVG();
        m_ELECTROBOT_ETAT_TELEMETRES.Telemetre2 = Application.m_telemetres.getDistanceAVD();
        m_ELECTROBOT_ETAT_TELEMETRES.Telemetre3 = Application.m_telemetres.getDistanceARG();
        m_ELECTROBOT_ETAT_TELEMETRES.Telemetre4 = Application.m_telemetres.getDistanceARD();
        m_ELECTROBOT_ETAT_TELEMETRES.Telemetre5 = Application.m_telemetres.getDistanceARGCentre();
        m_ELECTROBOT_ETAT_TELEMETRES.Telemetre6 = Application.m_telemetres.getDistanceARDCentre();
        SerialiseTrame(m_ELECTROBOT_ETAT_TELEMETRES.Encode(&trame));
    }
    // _____________________________________________
    if (m_ETAT_MATCH.isTimeToSend())
    {
        m_ETAT_MATCH.TempsMatch = (unsigned char)(Application.m_modelia.m_datas_interface.TempsMatch);
        m_ETAT_MATCH.CouleurEquipe = Application.m_modelia.m_datas_interface.couleur_equipe;
        m_ETAT_MATCH.ModeFonctionnement = Application.ModeFonctionnement;
        m_ETAT_MATCH.ObstacleDetecte = Application.m_modelia.m_inputs_interface.obstacleDetecte;
        m_ETAT_MATCH.OrigineDetectionObstacle = (Application.m_modelia.m_inputs_interface.m_lidar_status==LidarUtils::LIDAR_OK);
        m_ETAT_MATCH.ConvergenceAsserv = (Application.m_asservissement.convergence_conf == 1);
        m_ETAT_MATCH.DiagBlocage = Application.m_asservissement.diag_blocage;
        m_ETAT_MATCH.Score = Application.m_modelia.getScore();
        m_ETAT_MATCH.ChoixStrategie = Application.m_modelia.m_datas_interface.ChoixStrategieMatch;
        SerialiseTrame(m_ETAT_MATCH.Encode(&trame));
    }
    // _____________________________________________
    if (m_ETAT_DETECTION_EVITEMENT_OBSTACLE.isTimeToSend())
    {
/*
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.x_robot = Application.m_modelia.m_inputs_interface.X_robot;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.y_robot = Application.m_modelia.m_inputs_interface.Y_robot;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.teta_robot = Application.m_modelia.m_inputs_interface.angle_robot*100;  // rad
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.SensDeplacement = Application.m_asservissement.getSensDeplacement();;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.ObstacleBitfield = Application.m_modelia.m_datas_interface.evit_detection_obstacle_bitfield;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.NombreObstaclesPresents = Application.m_modelia.m_datas_interface.nombre_obstacles_presents;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.AnglePremierObstacleDetecte = Application.m_modelia.m_datas_interface.angle_premier_obstacle_detecte;  // degre
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.DistancePremierObstacleDetecte = Application.m_modelia.m_datas_interface.distance_premier_obstacle_detecte;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.ObstacleDetecte = Application.m_modelia.m_inputs_interface.obstacleDetecte;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.ObstacleAVD = Application.m_modelia.m_inputs_interface.obstacle_AVD;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.ObstacleAVG = Application.m_modelia.m_inputs_interface.obstacle_AVG;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.ObstacleARD = Application.m_modelia.m_inputs_interface.obstacle_ARD;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.ObstacleARG = Application.m_modelia.m_inputs_interface.obstacle_ARG;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.ObstacleInhibe = Application.m_modelia.m_datas_interface.evit_inhibe_obstacle;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.ForcageDetectObstacleSansPosition = 0;//Application.m_modelia.m_forcage_detect_obstacle_sans_position;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.OrigineDetectionObstacle = (Application.m_modelia.m_inputs_interface.m_lidar_status==LidarUtils::LIDAR_OK);
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.SeuilDetectionObstacleLidar = SEUIL_DETECTION_LIDAR;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.SeuilDetectionObstacleTelemetre = SEUIL_DETECTION_US;

        // --------------------------------------
        // Evitement d'obstacles
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.NumeroEtape = Application.m_modelia.m_datas_interface.evit_debug_etape;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.NombreTentatives = Application.m_modelia.m_datas_interface.evit_nombre_tentatives;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.ChoixStrategieEvitement = Application.m_modelia.m_datas_interface.evit_choix_strategie;
        m_ETAT_DETECTION_EVITEMENT_OBSTACLE.EvitementEnCours = Application.m_modelia.m_datas_interface.evit_strategie_evitement_en_cours;

        SerialiseTrame(m_ETAT_DETECTION_EVITEMENT_OBSTACLE.Encode(&trame));
*/
    }
    // _____________________________________________
    if (m_ETAT_RACK.isTimeToSend())
    {
/*
        m_ETAT_RACK.rack_cde_moteur = (int)Application.m_moteurs.m_cde_mot_6;
        m_ETAT_RACK.rack_consigne_moteur = (int)Application.m_asservissement_chariot.commande_moteur_chariot;
        m_ETAT_RACK.rack_convergence = (Application.m_asservissement_chariot.etat_asser_chariot==2)?1:0;
        m_ETAT_RACK.rack_modeAsservissement = Application.m_asservissement_chariot.etat_asser_chariot;
        SerialiseTrame(m_ETAT_RACK.Encode(&trame));
*/
    }
    // _____________________________________________
    if (m_COLOR_SENSOR.isTimeToSend())
    {
/*
        m_COLOR_SENSOR.R=0;//Application.m_electrobot.m_color_sensor_R;
        m_COLOR_SENSOR.G=0;//Application.m_electrobot.m_color_sensor_G;
        m_COLOR_SENSOR.B=0;//Application.m_electrobot.m_color_sensor_B;
        SerialiseTrame(m_COLOR_SENSOR.Encode(&trame));
*/
    }
    // _____________________________________________
    if (m_ETAT_POWER_ELECTROBOT.isTimeToSend())
    {
        m_ETAT_POWER_ELECTROBOT.battery_voltage_mV = Application.m_power_electrobot.getRawBatteryVoltage();
        m_ETAT_POWER_ELECTROBOT.global_current_mA = Application.m_power_electrobot.getRawGlobalCurrent();
        m_ETAT_POWER_ELECTROBOT.current_out1_mA = Application.m_power_electrobot.getRawCurrentOut1();
        m_ETAT_POWER_ELECTROBOT.current_out2_mA = Application.m_power_electrobot.getRawCurrentOut2();
        SerialiseTrame(m_ETAT_POWER_ELECTROBOT.Encode(&trame));
    }
    // _____________________________________________
    if (m_MBED_ETAT_TRAME.isTimeToSend())
    {
/*
        m_MBED_ETAT_TRAME.Valeur_mbed_etat_01=Application.m_modelia.m_datas_interface.m_tx_value_01;
        m_MBED_ETAT_TRAME.Valeur_mbed_etat_02=Application.m_modelia.m_datas_interface.m_tx_value_02;
        m_MBED_ETAT_TRAME.Valeur_mbed_etat_03=Application.m_modelia.m_datas_interface.m_tx_value_03;
        m_MBED_ETAT_TRAME.Valeur_mbed_etat_04=Application.m_modelia.m_datas_interface.m_tx_value_04;
        m_MBED_ETAT_TRAME.Cde_mbed_etat=Application.m_modelia.m_datas_interface.m_tx_code_cmd;
        SerialiseTrame(m_MBED_ETAT_TRAME.Encode(&trame));
*/
    }
    // _____________________________________________
    if (m_ETAT_SERVO_AX.isTimeToSend())
    {
        // Envoie tous les servos détectés au démarrage, à la suite
        // Si aucun servo n'a été détecté,
        for(unsigned int i=0; i<Application.m_servos_ax.m_present_count; i++)
        {
            int servo_id = Application.m_servos_ax.m_presents_list[i];
            if (servo_id != -1) {
                m_ETAT_SERVO_AX.num_servo_ax = servo_id;
                m_ETAT_SERVO_AX.position = Application.m_servos_ax.m_positions[i];
                m_ETAT_SERVO_AX.mouvement_en_cours = Application.m_servos_ax.m_moving[i];
                m_ETAT_SERVO_AX.couple = Application.m_servos_ax.m_rx_err_count;
                m_ETAT_SERVO_AX.temperature = Application.m_servos_ax.m_tx_err_count;

                SerialiseTrame(m_ETAT_SERVO_AX.Encode(&trame));
            }
        }
    }
    // _____________________________________________
    if (m_ETAT_KMAR_GENERAL.isTimeToSend())
    {
/*
        m_ETAT_KMAR_GENERAL.num_kmar = 1;   // TODO : à voir si plusieurs sur le même robot
        m_ETAT_KMAR_GENERAL.status = 1;     // pour le moment
        m_ETAT_KMAR_GENERAL.moving = Application.m_kmar.isMoveInProgress();
        m_ETAT_KMAR_GENERAL.num_mouvement_en_cours = Application.m_kmar.getNumMouvementInProgress();
        m_ETAT_KMAR_GENERAL.axis1_moving = Application.m_kmar.isMoving(CKmar::AXIS_1);
        m_ETAT_KMAR_GENERAL.axis2_moving = Application.m_kmar.isMoving(CKmar::AXIS_2);
        m_ETAT_KMAR_GENERAL.axis3_moving = Application.m_kmar.isMoving(CKmar::AXIS_3);
        m_ETAT_KMAR_GENERAL.axis4_moving = Application.m_kmar.isMoving(CKmar::AXIS_4);
        m_ETAT_KMAR_GENERAL.object_catched = Application.m_kmar.isObjectCatched();
        m_ETAT_KMAR_GENERAL.axis1_position = Application.m_kmar.getPosition(CKmar::AXIS_1);
        m_ETAT_KMAR_GENERAL.axis2_position = Application.m_kmar.getPosition(CKmar::AXIS_2);
        m_ETAT_KMAR_GENERAL.axis3_position = Application.m_kmar.getPosition(CKmar::AXIS_3);
        m_ETAT_KMAR_GENERAL.axis4_position = Application.m_kmar.getPosition(CKmar::AXIS_4);
        SerialiseTrame(m_ETAT_KMAR_GENERAL.Encode(&trame));
*/
    }
    // _____________________________________________
    if (m_ETAT_CHARGE_CPU.isTimeToSend())
    {
/*
        m_ETAT_CHARGE_CPU.cpu_overload_counter = Application.m_cpu_overload_counter; //Application.m_cpu_overload_counter;
        m_ETAT_CHARGE_CPU.task_real_period_usec= Application.m_cpu_load_delta_t;
        SerialiseTrame(m_ETAT_CHARGE_CPU.Encode(&trame));
*/
    }
}




//___________________________________________________________________________
 /*!
   \brief Point d'entree du module pour la serialisation de la trame

    - Fonction appelee pour demander la transformation d'une trame en serie d'octet envoyes sur la liaison serie
    - Prend les donnees une par une et les envoie sur la liaison serie
   \param trameBrute la trame a envoyer avec ses octets bruts
   \return --
   */
void CLaBotBox::SerialiseTrame(tStructTrameLaBotBox *trameBrute)
{
  int i=0;
  int trame_len = trameBrute->DLC + 5;
  unsigned char buff[trame_len];

  buff[i++] = 'T';
  buff[i++] = trameBrute->ID>>8;
  buff[i++] = trameBrute->ID;
  buff[i++] = trameBrute->DLC;
  for(int j=0; j<trameBrute->DLC; j++) {
      buff[i++] = trameBrute->Data[j];
  }
  buff[i++] = getCheckSumTrame(trameBrute);
  HAL_UART_Transmit(&huart3, buff, trame_len, 200);
}



//___________________________________________________________________________
 /*!
   \brief Calcul le checksum de la trame

    - Calcul le checksum de la trame courante et le compare au parametre d'entree de la fonction

   \param trameBrute la trame pour laquelle calculer le checksum
   \return 	le checksum sur 8 bits
   */
unsigned char CLaBotBox::getCheckSumTrame(tStructTrameLaBotBox *trameBrute)
{
    unsigned char checksum = 0;
    unsigned char i=0;

    checksum += trameBrute->ID;
    checksum += trameBrute->DLC;
    for(i=0; i<trameBrute->DLC; i++) {
        checksum += trameBrute->Data[i];
    }
    return(checksum);
}


//___________________________________________________________________________
 /*!
   \brief Fixe la même période d'émission pour toutes les trames
   \param period_msec la période souhaitée pour toutes les trames
            CTrameLaBotBox::NO_PERIODIC pour mettre toutes les trames non périodiques
   \return --
   */
void CLaBotBox::setAllTransmitPeriod(int period_msec)
{
    for (unsigned int i=0; i<m_nombre_trames; i++)
    {
        if (m_liste_trames[i])
        {
            m_liste_trames[i]->setTransmitPeriod(period_msec);
        }
    }
}











