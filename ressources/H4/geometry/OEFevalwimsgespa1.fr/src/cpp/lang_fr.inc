#if defined TARGET_posreldte1 || defined TARGET_posreldte2 || defined TARGET_posreldte3 || defined TARGET_Internonpar1 || defined TARGET_Internonpar2 || defined TARGET_Internonpar3 || defined TARGET_inter2pl1 || defined TARGET_inter2pl2 || defined TARGET_inter2pl3 || defined TARGET_Interpar1 || defined TARGET_Interpar2 || defined TARGET_Interpar3 || defined TARGET_pos2pl1 || defined TARGET_pos2pl2 || defined TARGET_pos2pl3 || defined TARGET_posrelpl1 || defined TARGET_posrelpl2 || defined TARGET_posrelpl3 || defined TARGET_posorthdte4 || defined TARGET_posorthdte5 || defined TARGET_posorthdte1 || defined TARGET_posorthdte2 || defined TARGET_posorthdte3 || defined TARGET_posorthdte4 || defined TARGET_posorthdte5 || defined TARGET_interdtepl1 || defined TARGET_interdtepl2 || defined TARGET_interdtepl3
\text{objet=On considère le cube <span style="color:blue">ABCDEFGH</span>}
 \text{tpoints=Les points <span style="color:green">I,J,K,L,M,N,O,P,Q,R,S,T</span> sont les milieux
 des arêtes auxquelles ils appartiennent}
#endif
#if defined TARGET_Interpar5 || defined TARGET_Internonpar5 || defined TARGET_pos2pl5 || defined TARGET_posreldte4 || defined TARGET_posreldte5 || defined TARGET_inter2pl5 || defined TARGET_Interpar5 || defined TARGET_posrelpl5 || defined TARGET_interdtepl4 || defined TARGET_posrelpl4 || defined TARGET_interdtepl5
 \text{objet=On considère le tétraèdre <span style="color:blue">ABCD</span>}
 \text{tpoints=Les points <span style="color:green">I,J,K,L,M,N,O,P,Q,R,S,T</span>
 	divisent les arêtes auxquelles ils appartiennent en 3 segments égaux}
#endif
#if defined TARGET_Internonpar4 || defined TARGET_pos2pl4 || defined TARGET_Interpar4 || defined TARGET_inter2pl4
\text{objet=On considère la pyramide à base parallélogramme <span style="color:blue">SABCD</span>}
\text{tpoints=Les points <span style="color:green">I,J,K,L,M,N,O,P</span> sont les milieux
	des arêtes auxquelles ils appartiennent}
#endif
#if defined TARGET_inter2pl1 || defined TARGET_inter2pl2 || defined TARGET_inter2pl3 || defined TARGET_inter2pl4 || defined TARGET_inter2pl5 || defined TARGET_pos2pl4 || defined TARGET_pos2pl1 || defined TARGET_pos2pl2 || defined TARGET_pos2pl3 || defined TARGET_pos2pl5
\text{lstposrel= sécants, strictement parallèles, confondus}
#endif
#if defined TARGET_posreldte1 || defined TARGET_posreldte2 || defined TARGET_posreldte3 || defined TARGET_posreldte4 || defined TARGET_posreldte5
\text{lstposrel=non coplanaires, coplanaires sécantes, coplanaires parallèles}
#endif
#if defined_TARGET_posrelpl1 || defined TARGET_posrelpl2 || defined TARGET_posrelpl3 || defined TARGET_posrelpl4 || defined TARGET_posrelpl5
\text{lstposrel=strictement parallèle, incluse, sécante}
#endif
#if defined TARGET_posorthdte4 || defined TARGET_posorthdte5
\text{lstposrel=rectangle, isocèle, rectangle isocèle, équilatéral, quelconque}
#endif
#if defined TARGET_Calculdist1 || defined TARGET_Calculdist2 || defined TARGET_Calculdist3 || defined TARGET_Calculdist5
\text{objet=On considère le cube <span style="color:blue">\(A B C D E F G H\)</span>}
\text{tpoints=Les points <span style="color:green">\(I,J,K,L,M,N,O,P,Q,R,S,T\)</span> sont les
	milieux des arêtes auxquelles ils appartiennent}
\text{dimension=L'arête du cube vaut \(a)}
#endif
#if defined TARGET_Calculdist4
\text{objet=On considère la pyramide à base parallélogramme <span style="color:blue">\(S A B C D\)</span>}
\text{dimension=\(S A=S B=S C=S D=h\), l'aire de la base vaut \(S\)}
#endif
