%%%%% VARIABLES DE L'EXERCICE %%%%%

\text{Liste=AIL,AIR,AME,AMI,ARC,ART,BAC,BAL,BAM,BAS,BEC,BIP,BIS,BLE,BOA,BOL,BON,BUS,BUT,BZH,CAP,CAR,CIL,
CLE,COL,COR,COU,CRI,CRU,DIX,DON,DOS,DRU,DUO,DUR,EAU,EST,FAC,FAR,FAT,FER,FEU,FIL,FIN,FOL,FOU,FUT,GAI,GEL,
GUI,ILE,INF,IRE,JET,JEU,JUS,LAC,LET,LIN,LIT,LOI,LOT,LUI,LYS,MAI,MAL,MAT,MER,MIE,MIL,MOI,MON,MOT,MOU,MUR,
NEF,NEZ,OUI,PAF,PAS,PEU,PIC,PIE,PIN,PLI,POC,POF,PRO,PUR,RAP,RAS,RAZ,RIA,RIO,RIZ,ROC,ROI,RUE,SAC,SEC,SEL,
SET,SIX,SOC,SOL,SON,SOU,SPI,SUD,SUP,SUR,TAC,TAS,TER,THE,TIC,TIR,TOC,TOI,TON,TRI,UNE,UNI,VAL,VAN,VER,VIE,
VIS,VUE,YEN,ZEN
}
\text{nom = randitem(\Liste)}
\text{A = wims(char 1 of \nom)}
\text{B = wims(char 2 of \nom)}
\text{C = wims(char 3 of \nom)}
\text{Triangle=\A,\B,\C}
\integer{Alea=randint(1..3)}
\text{Sommet=\Triangle[\Alea]}
\text{Hyp=wims(listcomplement \Sommet in \Triangle)}

#if defined TARGET_01CliquerHypotenuse || defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose
# if defined TARGET_01CliquerHypotenuse
\text{seg1=[B,C]}
\text{seg2=[A,B]}
\text{seg3=[A,C]}
\text{segt1=[\Hyp[1]\Hyp[2]]}
\text{segt2=[\Sommet\Hyp[1]]}
\text{segt3=[\Sommet\Hyp[2]]}
# else
#  if defined TARGET_02CliquerAdjacent
\text{seg1=[A,B]}
\text{seg2=[B,C]}
\text{seg3=[A,C]}
\text{segt1=[\Hyp[1]\Sommet]}
\text{segt2=[\Hyp[1]\Hyp[2]]}
\text{segt3=[\Sommet\Hyp[2]]}
#  else
\text{seg1=[A,C]}
\text{seg2=[B,C]}
\text{seg3=[A,B]}
\text{segt1=[\Hyp[2]\Sommet]}
\text{segt2=[\Hyp[1]\Hyp[2]]}
\text{segt3=[\Sommet\Hyp[1]]}
#  endif
# endif
#endif


\integer{red=randint(0..255)}
\integer{green=randint(0..255)}
\integer{blue=randint(0..255)}
\text{couleur=rgb(\red,\green,\blue)}

%%%%%% LES POINTS %%%%%%

\real{x_B=randint(10..90)/10}
%% x_B est le côté adjacent.
\real{y_C=randint(10..90)/10}
%% y_C est le côté opposé.
\real{angleRot=random(0..6.28)}
\real{angleRot2=Pi/2+\angleRot}
\real{x_B2=\x_B*cos(\angleRot)}
\real{y_B2=\x_B*sin(\angleRot)}
\real{x_C2=\y_C*cos(\angleRot2)}
\real{y_C2=\y_C*sin(\angleRot2)}
\real{radiusAngle=min(1,min(\x_B/6,\y_C/6))}

%%%%%% LES LONGUEURS %%%%%%%%
\real{Longueur_BC=round(10*sqrt(\x_B^2+\y_C^2))/10}
%% C'est l'hypoténuse.
\text{x_B_t=wims(replace internal . by , in \x_B)}
\text{y_C_t=wims(replace internal . by , in \y_C)}

%%%%%%% LE CADRE %%%%%%%% 
\real{xMin=min(min(0,\x_B2),\x_C2)-1.5}
\real{xMax=max(max(0,\x_B2),\x_C2)+1.5}
\real{yMin=min(min(0,\y_B2),\y_C2)-1.5}
\real{yMax=max(max(0,\y_B2),\y_C2)+1.5}
\integer{cCadreMax=250}
\real{CoeffCadre=\xMax-\xMin > \yMax-\yMin?\cCadreMax/(\xMax-\xMin):\cCadreMax/(\yMax-\yMin)}
\integer{LCadre=((\xMax-\xMin)*\CoeffCadre)}
\integer{hCadre=((\yMax-\yMin)*\CoeffCadre)}


#if !defined TARGET_01CliquerHypotenuse && !defined TARGET_02CliquerAdjacent && !defined TARGET_03CliquerOppose
%%%%%%%% NOM ANGLE %%%%%%%%%
\text{NomAngle=randint(1,2)=1?\Sommet\Hyp[1]\Hyp[2]:\Hyp[2]\Hyp[1]\Sommet}
\text{NomAngle_compl=randint(1,2)=1?\Sommet\Hyp[2]\Hyp[1]:\Hyp[1]\Hyp[2]\Sommet}
# if defined TARGET_10DeuxMesures
\text{NomAngle2=randint(1,2)=1?\Sommet\Hyp[2]\Hyp[1]:\Hyp[1]\Hyp[2]\Sommet}
\text{Cat1=randint(1,2)=1?\Sommet\Hyp[1]:\Hyp[1]\Sommet}
\text{Cat2=randint(1,2)=1?\Sommet\Hyp[2]:\Hyp[2]\Sommet}
# endif
#endif

%%%%%%% BESOIN VARIABLES DANS LA LANGUE %%%%%%
#include "lang_data.inc"

#if defined TARGET_10DeuxMesures
\text{ListeLignesTrigo=
\Line_name[1] \delangle \(\widehat{\NomAngle}\),\Line_name[2] \delangle \(\widehat{\NomAngle2}\),
\Line_name[2] \delangle \(\widehat{\NomAngle}\),\Line_name[1] \delangle \(\widehat{\NomAngle2}\),
\Line_name[3] \delangle \(\widehat{\NomAngle}\),\Line_name[3] \delangle \(\widehat{\NomAngle2}\)
}

\text{ListeLignesTrigo2=
sin(\(\widehat{\NomAngle}\)),cos(\(\widehat{\NomAngle2}\)),
cos(\(\widehat{\NomAngle}\)),sin(\(\widehat{\NomAngle2}\)),
tan(\(\widehat{\NomAngle}\)),tan(\(\widehat{\NomAngle2}\))
}
#endif


#if defined TARGET_07IdentifierLigneTrigo1 || defined TARGET_08IdentifierLigneTrigo2 || defined TARGET_09DonnerLigneTrigo || defined TARGET_10DeuxMesures || defined TARGET_11LigneTrigoUniteEtape || defined TARGET_12LigneTrigoUnite
%%%%%%% LONGUEURS POUR AFFICHAGE %%%%%%%
\text{Longueur_BC_t=slib(numeration/ecriturenombre [\Longueur_BC], comma)}
\text{Longueur_AB_t=slib(numeration/ecriturenombre [\x_B], comma)}
\text{Longueur_AC_t=slib(numeration/ecriturenombre [\y_C], comma)}

%%%%%%% MATRICE TRIGO %%%%%%

\matrix{trigo=\Line_name[1],\Line_name[2],\Line_name[3]
sin,cos,tan
opp,\Sommet,\Hyp[2] , \y_C,\Line_cote[1],\Line_cote[2]
adj,\Sommet,\Hyp[1] , \x_B,\Line_cote[3],\Line_cote[4]
hyp,\Hyp[1],\Hyp[2] , \Longueur_BC,\Line_cote[5],\Line_cote[5]
}

# if defined TARGET_09DonnerLigneTrigo || defined TARGET_10DeuxMesures || defined TARGET_11LigneTrigoUniteEtape
%%%%% CONFPARM 3 AFFICHAGE REPONSES INTERMEDIAIRES OUI PAR DEFAUT %%%%%%
\text{conf3=\confparm3!= ? \confparm3:2}
\if{\conf3!=1}{\text{opt=nonstop}}{\text{opt=}}

# if defined TARGET_10DeuxMesures
\if{\conf3!=1}{\text{opt_split=split}}{\text{opt_split=}}
# endif

# endif



# if !defined TARGET_10DeuxMesures
%%%%% GESTION  confparm2 avec 1 pour sin, 2 pour cos et 3 pour tan %%%%%
\if{\confparm2=}{\text{typeLigne=randint(1..3)}}{
\text{typeLigne=randitem(\confparm2)}}
# endif

# if defined TARGET_10DeuxMesures
\text{typeLigne=randint(1..3)}
# endif

\matrix{NUM=\typeLigne=2? \trigo[4;]:\trigo[3;]}
\matrix{DEN=\typeLigne=3? \trigo[4;]:\trigo[5;]}
\text{NomNum=randitem(1,2)=1?\NUM[2]\NUM[3]:\NUM[3]\NUM[2]}
\text{NomDen=randitem(1,2)=1?\DEN[2]\DEN[3]:\DEN[3]\DEN[2]}

\real{num=\NUM[4]}
\real{den=\DEN[4]}

\text{num_t=wims(replace internal . by , in \num)}
\text{den_t=wims(replace internal . by , in \den)}

#  if defined TARGET_10DeuxMesures
%%% Pour bloc sol
\if{\typeLigne=1}
  {\text{suiv=2}}
  {\if {\typeLigne=2}
    {\text{suiv=1}}
    {\text{suiv=3}}
  }
\matrix{NUM_suiv=\typeLigne=2? \trigo[3;]:\trigo[4;]}
# endif

%%%%% LES BONS COTES SELON confparm2 avec 1 pour sin, 2 pour cos et 3 pour tan  %%%%%%
\matrix{BonsCotes=\trigo[3;6] \(\widehat{\NomAngle}\),
\trigo[4;6] \(\widehat{\NomAngle}\),
\trigo[5;6]}
\if{\typeLigne=1}{\text{BonsCotesSol=1,3}}
\if{\typeLigne=2}{\text{BonsCotesSol=2,3}}
\if{\typeLigne=3}{\text{BonsCotesSol=1,2}}

\text{donnee1=\NomNum = \num_t}
\text{donnee2=\NomDen = \den_t}
\text{donnee=randitem(1,2)=1?\donnee1;\donnee2:\donnee2;\donnee1}


# if defined TARGET_11LigneTrigoUniteEtape || defined TARGET_12LigneTrigoUnite || defined TARGET_10DeuxMesures

%%%% MESURE ET ARRONDI ANGLE %%%%

\if{\typeLigne=1}{\real{angle=(asin(\num/\den))/pi*180}}{
\real{angle=\typeLigne=2? (acos(\num/\den))/pi*180:(atan(\num/\den))/pi*180}}
\text{angle_t=wims(replace internal . by , in \angle)}
\real{Solution_1=round(\angle)}

\if{\typeLigne=1}
 {\text{calculatrice=<span class="calculator nowrap">Arcsin</span> <span class="calculator nowrap">arcsin</span> <span class="calculator nowrap">sin<sup>-1</sup></span>}}
 {\if{\typeLigne=2}
  {\text{calculatrice=<span class="calculator nowrap">Arccos</span> <span class="calculator nowrap">arccos</span> <span class="calculator nowrap">cos<sup>-1</sup></span>}}
  {\text{calculatrice=<span class="calculator nowrap">Arctan</span> <span class="calculator nowrap">arctan</span> <span class="calculator nowrap">tan<sup>-1</sup></span>}}
 }

#  if defined TARGET_10DeuxMesures
\real{angle2=90-\angle}
\text{angle2_t=wims(replace internal . by , in \angle2)}
\real{Solution_2=90-\Solution_1}

\if{\suiv=1}
 {\text{calculatrice_suiv=<span class="calculator nowrap">Arcsin</span> <span class="calculator nowrap">arcsin</span> <span class="calculator nowrap">sin<sup>-1</sup></span>}}
 {\if{\suiv=2}
  {\text{calculatrice_suiv=<span class="calculator nowrap">Arccos</span> <span class="calculator nowrap">arccos</span> <span class="calculator nowrap">cos<sup>-1</sup></span>}}
  {\text{calculatrice_suiv=}}
 }

#  endif



 
 
# endif

#endif
