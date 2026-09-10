#if defined TARGET_arg || defined TARGET_conj || defined TARGET_module
\text{name_ask=zijn waar,zijn niet waar}
\text{name_cond=goed,slecht}
\matrix{name_amongst=Welke van de volgende
}
\text{name_answer=De,zijn}
\text{propsname=formules}
#endif
#if defined TARGET_arg
\text{name_instruction=Laat \(z_1,z_2\) twee complexe getallen zijn (niet nul).}
#endif
#if defined TARGET_conj
\text{name_instruction=Laat \(z_1\), \(z_2\), \(z_3\) complexe getallen zijn.}
#endif
#if defined TARGET_module
\text{name_instruction=Laat \(z_1,z_2\) twee complexe getallen zijn.}
#endif
#if defined TARGET_reim
\text{name_instruction=Laat \(z = x + i y\) een complex getal zijn, waarin \(x\) en \(y\) re&euml;le getallen zijn.
  Wat is het reële gedeelte en wat het imaginaire gedeelte van}
\text{name_answer=Het reële gedeelte,Het imaginaire gedeelte}
#endif
#if defined TARGET_arggiven
\matrix{name_instruction=Bereken het reële en imaginaire gedeelte van het complexe getal
  met en
  als argument}
#endif
#if defined TARGET_arg0
\text{name_instruction=Let \(z_1,z_2\) two non-zero complex numbers.
 Amongst the following equalities, which one are true}
#endif
#if defined TARGET_argask
\text{name_instruction=Gegeven de modules en argument van het complexe getal}
\text{name_feed=is eenn argument van}
#endif
