#if defined TARGET_ecran1 || defined TARGET_ecran2 || defined TARGET_ecran3|| defined TARGET_ecran4
# define TITRE Écran
#endif
#if defined TARGET_ombre1 || defined TARGET_ombre2
# define TITRE Ombre
#endif
#if defined TARGET_trajet1
# define TITRE Trajet de la lumière
#endif
#if defined TARGET_tabouret
# define TITRE Tabouret
#endif
#if defined TARGET_ordphase1 || defined TARGET_ordphase1P || defined TARGET_ordphase2
# define TITRE Phases de la Lune
#endif
#if defined TARGET_phase1T || defined TARGET_phase2T || defined TARGET_phase3T || defined TARGET_phase4T
# define TITRE Phases de la Lune
#endif
#if defined TARGET_phase1P || defined TARGET_phase2P || defined TARGET_phase3P || defined TARGET_phase4P || defined TARGET_phase5P
# define TITRE Phases de la Lune
#endif
#if defined TARGET_date1 || defined TARGET_date2
# define TITRE Prévoir la phase de la Lune
#endif
#if defined TARGET_date1P || defined TARGET_date2P
# define TITRE Prévoir la phase de la Lune
#endif
#if defined TARGET_qcm1 || defined TARGET_qcm2
# define TITRE Sources de lumière
#endif
#if defined TARGET_poslune
# define TITRE Où et quand voit-on la Lune
#endif
#if defined TARGET_eclipse1
# define TITRE Éclipse
#endif
#if defined TARGET_eclipse2
# define TITRE Éclipse (sans aide graphique)
#endif

