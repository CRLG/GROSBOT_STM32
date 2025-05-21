/*! \file CElectrobot.h
    \brief Classe qui contient la gestion de la carte Electrobot
*/

#ifndef _ELECTROBOT_H_
#define _ELECTROBOT_H_

#define TENSION_REF_EANA_CPU	3.3

#define SEUIL_TENSION_BATT_FAIBLE 14.0

#define COEF_TENSION_ANA_dsPIC  (0.075796875)

// -----------------------------
//! Classe de gestion des options d'exécution passees en ligne de commande
class CElectrobot {
public :
    // Valeurs brutes sur les entrées TOR ("_b" pour "brute")
	unsigned char m_b_Etor1;
	unsigned char m_b_Etor2;
	unsigned char m_b_Etor3;
	unsigned char m_b_Etor4;

    // Valeurs brutes sur les entrées analogiques
	float m_b_Mes_Vbat;
	float m_b_Eana1;
	float m_b_Eana2;
	float m_b_Eana3;
	float m_b_Eana4;
	float m_b_Eana5;
	float m_b_Eana6;
	float m_b_Eana7;
	float m_b_Eana8;
	float m_b_Eana9;
	float m_b_Eana10;
	float m_b_Eana11;
	float m_b_Eana12;
	float m_b_Eana13;

    // ___________________________________________________
    // Les grandeurs mises en forme pou l'application
    float m_tension_batterie;
    unsigned char m_alerte_batterie_faible;

    CElectrobot();
    ~CElectrobot();

	//! Initialisation des capteurs
	void Init(void);
	//! Traitement des capteurs (aqcuisition, filtrage)
	void Traitement(void);

private : 

    float _pulsewidth, _period;

    //! Traitements pour les entrées TOR du CPU
	void AcquisitionEntreesTOR(void);
    //! Traitements pour les entrées analogiques du CPU
	void AcquisitionEntreesANA(void);
    //! Traitement pour la mesure de la tension batterie
    void TraitementTensionBatterie(void);

    // ____________________________________________
	// Fonctions de traitement du signal
	//! Moyenne glissante	
	float MoyenneGlissante_float(float currentVal, float *buf_oldSamples, unsigned int samplesNumbers);
 	//! Hysterisis
    unsigned char Hysterisis (float vin, unsigned char *etat, float swapOff, float swapOn, unsigned char valOff, unsigned char valOn);
};
#endif
