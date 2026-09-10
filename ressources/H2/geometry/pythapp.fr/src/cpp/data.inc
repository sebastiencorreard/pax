%%%%% VARIABLES DE L'EXERCICE %%%%%
%%
%%% Noms des triangles
\text{noms_triangles=AME,AMI,ARC,ART,BAC,BAL,BAM,BAS,BEC,BLE,BOA,BOL,BON,BUS,BUT,BZH,
CAP,CAR,CIL,CLE,COL,COR,COU,CRI,CRU,DIX,DON,DOS,DRU,DUO,DUR,
EAU,EST,FAC,FAR,FAT,FER,FEU,FIL,FIN,FOL,FOU,FUT,GAI,GEL,INF,
JEU,JET,JUS,LAC,LET,LIN,LIT,LOI,LOT,LYS,MAI,MAL,MAT,MER,MIL,MOI,MON,MOT,MOU,MUR,
NEF,NEZ,PAF,PIC,PIN,PLI,POC,POF,POT,PUR,RAP,RAS,RAZ,RIA,RIO,RIZ,RUE,
SAC,SEC,SEL,SET,SIX,SOC,SOL,SON,SOU,SPI,SUD,SUP,
TAC,TAS,TIC,TIR,THE,TOI,TON,TRI,UNE,UNI,VAL,VAN,VER,VUE,YEN,ZEN
}

%% Les noms des objets géométriques
\text{nom = randitem(\noms_triangles)}
#######POUR TEST ########
%%%text{nom = ABC}
#########################
\text{A = wims(char 1 of \nom)}
\text{B = wims(char 2 of \nom)}
\text{C = wims(char 3 of \nom)}

#if defined TARGET_01a || defined TARGET_01b ||  defined TARGET_02a || defined TARGET_02b ||   defined TARGET_03a || defined TARGET_03b ||  defined TARGET_04a || defined TARGET_04b ||   defined TARGET_05a || defined TARGET_05b   
\text{Triangle=\A,\B,\C}
\integer{Alea=randint(1..3)}
\text{Sommet=\Triangle[\Alea]}
\text{Hyp=wims(listcomplement \Sommet in \Triangle)}

  #if defined TARGET_02a || defined TARGET_02b || defined TARGET_04a || defined TARGET_04b
  \integer{Hypo=randint(6..10)}
  \integer{A_Hyp=\Hypo*\Hypo}
  \integer{Opp_Hyp=-1*\Hypo}
  \integer{A_B=randint(4..25)}
  \integer{A_C=\A_Hyp-\A_B}
  #endif
  #if defined TARGET_03a || defined TARGET_03b || defined TARGET_05a || defined TARGET_05b
  \integer{L_C=randint(2..10)}
  \integer{A_C=\L_C*\L_C}
  \integer{OppL_C=-1*\L_C}
  \integer{A_B=randint(4..25)}
  \integer{A_Hyp=\A_B+\A_C}
  #endif

%%% Variable pour après statement
\text{sigle=}
  #if defined TARGET_01a || TARGET_01b
  \text{sigle_title=}
  \text{checked=}
  #endif
#endif

#if defined TARGET_01a || defined TARGET_01b 
  \text{liste_cotes=randitem(\(\left[\Hyp[1]\Hyp[2]\right]\),\(\left[\Hyp[2]\Hyp[1]\right]\)),randitem(\(\left[\Hyp[1]\Sommet\right]\),\(\left[\Sommet\Hyp[1]\right]\)),randitem(\(\left[\Hyp[2]\Sommet\right]\),\(\left[\Sommet\Hyp[2]\right]\))}
  \text{liste_cotes=wims(shuffle \liste_cotes)}
  \integer{posi=wims(positionof item \(\left[\Hyp[1]\Hyp[2]\right]\) in \liste_cotes)}
  \if{\posi=NaN}{\integer{posi=wims(positionof item \(\left[\Hyp[2]\Hyp[1]\right]\) in \liste_cotes)}}
  \text{shuf=shuffle(3)}
  \text{solution1=position(\posi,\shuf)}
  \text{propo=\liste_cotes[\shuf]}
#endif

#if defined TARGET_02a || defined TARGET_02b 
\text{solution1=\A_Hyp}
#endif

#if defined TARGET_03a || defined TARGET_03b 
\text{solution1=\A_C}
#endif

#if defined TARGET_04a || defined TARGET_04b 
\text{solution1=\Hypo}
#endif

#if defined TARGET_05a || defined TARGET_05b 
\text{solution1=\L_C}
#endif

#if defined TARGET_06 || defined TARGET_07 || defined TARGET_08 || defined TARGET_09

\text{liste_sommets=\(\mathrm{\A}\),\(\mathrm{\B}\), \(\mathrm{\C}\)}

%%% Pour chaque ligne : item 1 = égalité, item 2 = justifications pour bloc solution si nécessaires 
\matrix{mat1=\(\B\C^2=\A\B^2+\A\C^2\),
\(\C\B^2=\B\A^2+\A\C^2\),
\(\A\B^2+\A\C^2=\B\C^2\),
 #if  defined TARGET_07 || defined TARGET_08 || defined TARGET_09
\(\A\B^2+\A\C^2-\B\C^2=0\),\(\A\B^2+\A\C^2=\B\C^2\)<br>\(\A\B^2+\A\C^2-\B\C^2=\B\C^2-\B\C^2\)
\(\A\B^2-\C\B^2+\C\A^2=0\),\(\A\B^2+\C\A^2=\C\B^2\)<br>\(\A\B^2+\C\A^2-\C\B^2=\C\B^2-\C\B^2\)
\(\A\B^2=\B\C^2-\A\C^2\),\(\A\B^2+\A\C^2=\B\C^2\)<br>\(\A\B^2+\A\C^2-\A\C^2=\B\C^2-\A\C^2\)
\(\A\C^2=\B\C^2-\A\B^2\),\(\A\B^2+\A\C^2=\B\C^2\)<br>\(\A\B^2+\A\C^2-\A\B^2=\B\C^2-\A\B^2\)
 #endif
}

\integer{nb_egal=rows(\mat1)}

\matrix{mat2=wims(replace internal \A by @ in \mat1)}
\matrix{mat2=wims(replace internal \B by \A in \mat2)}
\matrix{mat2=wims(replace internal @ by \B in \mat2)}
\matrix{mat3=wims(replace internal \B by @ in \mat2)}
\matrix{mat3=wims(replace internal \C by \B in \mat3)}
\matrix{mat3=wims(replace internal @ by \C in \mat3)}


 #if defined TARGET_06 || defined TARGET_07
\matrix{mat1=\mat1[randint(1..\nb_egal);]}
\matrix{mat2=\mat2[randint(1..\nb_egal);]}
\matrix{mat3=\mat3[randint(1..\nb_egal);]}
\matrix{data_egalites=\mat1
\mat2
\mat3}
 #endif

 #if defined TARGET_08 || defined TARGET_09
\matrix{mat1=\mat1[randitem(1,2,3);]
\mat1[randitem(4,5);]
\mat1[6;]
\mat1[7;]}
\matrix{mat2=\mat2[randitem(1,2,3);]
\mat2[randitem(4,5);]
\mat2[6;]
\mat2[7;]}
\matrix{mat3=\mat3[randitem(1,2,3);]
\mat3[randitem(4,5);]
\mat3[6;]
\mat3[7;]}
   
\text{shf_r = shuffle(\nb_egal)}
\text{mat1 = \mat1[\shf_r[1..\nb_egal]; ]}
\text{shf_r = shuffle(\nb_egal)}
\text{mat2 = \mat2[\shf_r[1..\nb_egal]; ]}
\text{shf_r = shuffle(\nb_egal)}
\text{mat3 = \mat3[\shf_r[1..\nb_egal]; ]}
   
\matrix{data_egalites=[\mat1]
[\mat2]
[\mat3]}
 #endif
 
 #if defined TARGET_06 || defined TARGET_07 || defined TARGET_08
\matrix{data=1,a,b
a,1,b
a,b,1}
   #if defined TARGET_06 || defined TARGET_07
\text{mix = shuffle(rows(\data))}
\text{data2 = \data[\mix[1..3]; ]}
   #endif
   #if defined TARGET_08
\matrix{data2=\data[randint(1..3);]
\data[randint(1..3);]
\data[randint(1..3);]}   
   #endif 
\text{rep1=position(1,\data2[1;])}
\text{rep2=position(1,\data2[2;])}
\text{rep3=position(1,\data2[3;])}
 #endif
 
 #if defined TARGET_08
  \text{reponses=\rep1,\rep2,\rep3}
  \matrix{liste_egalites=}
  \text{liste_sommets_sol=}
  \text{nb_config=pari(c=[0,0,0])}
  \for{q=1 to 3}
   {\text{ligne=}
    \text{temp=\reponses[\q]}
    \text{nb_config=pari(c[\temp]=c[\temp]+1;c)}
    \matrix{mattemp=wims(declosing \data_egalites[\temp;])}
    \text{ligne=\mattemp[\nb_config[\temp];] }
    \matrix{liste_egalites=\liste_egalites
    \ligne}
    \text{liste_sommets_sol=wims(append item \liste_sommets[\temp] to \liste_sommets_sol)}
   }
 #endif

 #if defined TARGET_09 

%%% Choix configuration %%%
\integer{config=randint(1..3)}
\text{autres_config=wims(listcomplement \config in 1,2,3)}
%%% Nbre proposition %%%
%%% Recup confparm %%%
\text{tot=\confparm1 == ? 3 : \confparm1}
\integer{tot=randitem(\tot)}
\text{figure=\confparm2 == ? 1 : \confparm2}
\integer{figure=randitem(\figure)}
%%% Minimum de phrases vraies %%%
\integer{mintrue=1}
%%% Minimum de phrases fausses %%%
\integer{minfalse=1}
%%% Affirmations vraies %%%
\matrix{datatrue=wims(declosing \data_egalites[\config;])}
\integer{truecnt=rows(\datatrue)}
\text{tsh=shuffle(\truecnt)}
%%% Affirmations fausses %%%
\matrix{datafalse=wims(declosing \data_egalites[\autres_config[1];])
wims(declosing \data_egalites[\autres_config[2];])}
\integer{falsecnt=rows(\datafalse)}
\text{fsh=shuffle(\falsecnt)}
%%% Propositions %%%
\integer{truepick=randint(\mintrue..\tot-\minfalse)}
\matrix{propo_true=\datatrue[\tsh[1..\truepick];]}
\matrix{propo_false=\datafalse[\fsh[1..\tot-\truepick];]}
\text{psh=shuffle(\tot)}
\matrix{propo=\propo_true
\propo_false}
\matrix{propo=\propo[\psh[1..\tot];]}
%%% Bonnes réponses %%%
\text{ind=wims(makelist 1 for x=1 to \truepick),wims(makelist 0 for x=1 to \tot-\truepick)}
\text{ind=item(\psh,\ind)}
\text{goodrep=positionof(1,\ind)}

%%% Pour figure %%%
\text{Triangle=\A,\B,\C}
\text{Sommet=\Triangle[\config]}
\text{Hyp=wims(listcomplement \Sommet in \Triangle)}

 #endif
 
%%% Variables pour analyses après statement
\text{checked=}
\text{repons=}
\text{screply=}
\text{sigle=}
\text{sigle_title=}


#endif
