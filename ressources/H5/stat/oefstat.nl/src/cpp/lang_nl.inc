#if defined TARGET_histo
  \text{name_header=Intervallen,Totale frequentie,Histogram}
  \text{name_instruction0=Gegeven is de onderstaande tabel
    met intervallen en de bijbehorende totale frequentie}
  \text{name_instruction=Bepaal het histogram, welke hoort bij de gegeven tabel.}
#endif
#if defined TARGET_ajustement
  \text{question=lineair, parabolisch,exponentieel,logaritmisch}
  \text{name_instruction0=Gegeven is de volgende puntenwolk}
 %%% leave the comma
  \text{name_instruction=Welk type functie past bij benadering het best bij deze puntenwolk,.}
  \text{name_feedback=De rode lijn is bij benadering de best passende lijn en is \question[\choix]}
  \text{name_prompt=Ajustement}
#endif
#if defined TARGET_repstat
  \text{name_header=Eigenschap}
  \text{\name_eff=Totale frequentie}
  \text{name_listechoix=een histogram,
    een cumulatief histogram,
    een dalend cumulatief histogram,
    een frequentie polygoon,
    een cumulatief frequentie polygoon,
    een dalende cumulatieve frequentie polygoonde}
  \text{name_instruction0=Gegeven zijn een serie getallen en een bijbehorend diagram.}
  \text{name_instruction=Om welk soort diagram gaat het}
  \text{name_prompt=Het gaat om}
#endif
