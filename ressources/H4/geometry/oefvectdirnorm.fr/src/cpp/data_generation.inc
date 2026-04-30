%%%%% VARIABLES DE L'EXERCICE %%%%%

%%% GESTION CONFPARM %%%
\text{conf1=\confparm1!= ? \confparm1:1}

!if !defined TARGET_06memenorme
\text{conf2=\confparm2!= ? \confparm2:1}
\text{conf2=randitem(\conf2)}
#endif

!if !defined TARGET_06memenorme && !defined TARGET_07memenormenoncoli
\text{conf3=\confparm3!= ? \confparm3:2}
#endif

%%% VARIABLES APPLET GGB %%%
#if defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
\text{tryagain=0}
\while{\tryagain=0}
  {\text{matA=slib(matrix/random 1,2,6)}
   \if{\matA=0,0}{\text{tryagain=0}}{\text{tryagain=1}}
  }
\integer{nb1=randitem(-3,-2,-1,1,2,3)}
\if{\nb1=1 or \nb1=-1}
  {\integer{nb2=randitem(-3,-2,2,3)}}
  {\integer{nb2=randitem(-3,-2,-1,1,2,3)}}

\if{\matA[1;1]=0}
  {\text{matB=pari([\nb1,\nb2*(\matA[1;2])])}} 
  {\if{\matA[1;2]=0}
    {\text{matB=pari([\nb1*(\matA[1;1]),\nb2])}}
    {\text{matB=pari([\nb1*(\matA[1;1]),\nb2*(\matA[1;2])])}}
  }  

\text{vec=\matA;\matB}
#else
\text{vec=slib(matrix/invertible 2,4)}
#endif


\integer{xA=0}
\integer{yA=0}
\integer{xB=\vec[1;1]}
\integer{yB=\vec[1;2]}
\integer{xC=wims(randitem -6,-5,-4,-3,-2,2,3,4,5,6)}
\integer{yC=wims(randitem -6,-5,-4,-3,-2,2,3,4,5,6)}
\integer{xD=\xC+(\vec[2;1])}
\integer{yD=\yC+(\vec[2;2])}
\text{list_coord=\xA,\yA,\xC,\yC,\xB,\yB,\xD,\yD}
\integer{max=pari(vecmax([\list_coord]))}
\integer{min=pari(vecmin([\list_coord]))}
\integer{maxi=pari(vecmax([\max,abs(\min)])+5)}
\text{sizeh=600}
\text{sizew=600}

#if defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
\integer{abs_xB=abs(\xB)}
\integer{abs_yB=abs(\yB)}
\text{OPP=pari([\vec[1;1],-1*(\vec[1;2])])}
\matrix{R=0,-1
1,0}
# if defined TARGET_06memenorme
\text{fam1=(\vec[1;])}
\for{j=1 to 3}
  {\text{T=pari(B=[\vec[1;]];R=[\R];B*(R^\j))}
   \text{fam1=\fam1,(\T)}
  }
\text{fam2=(\OPP)}
\for{jj=1 to 3}
  {\text{TT=pari(OPP=[\OPP];R=[\R];OPP*(R^\jj))}
   \text{fam2=\fam2,(\TT)}
  }
# else
\text{fam1=}
\for{j=1 to 3 step 2}
  {\text{T=pari(B=[\vec[1;]];R=[\R];B*(R^\j))}
   \text{fam1=\fam1,(\T)}
  }
\if{\xB=0 or \yB=0 or (\abs_xB=\abs_yB)}
  {\text{fam2=}}
  {\text{fam2=(\OPP)}
  \for{jj=1 to 3}
    {\text{TT=pari(OPP=[\OPP];R=[\R];OPP*(R^\jj))}
     \text{fam2=\fam2,(\TT)}
    }
  }
# endif
\text{sol=wims(listunion \fam1 and \fam2)}
\text{sol=wims(listuniq \sol)}
\integer{nb_sol=wims(itemcnt \sol)}
#endif

\integer{pgcd=pari(gcd(\xB-\xA,\yB-\yA))}
#if defined TARGET_01colineaire
\text{slide_range=-4,4,1}
#endif
#if defined TARGET_02memesens
\text{slide_range=0,5,1}
#endif
#if defined TARGET_03sensoppose
\text{slide_range=-5,0,1}
#endif
#if defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
\text{slide_range=1,\nb_sol,1}
#endif

%%%% NOMS DES POINTS %%%%
\text{ens_pt=A,B,C,D,E,F,G,H}
\text{name_pt=slib(data/random 4,item,\ens_pt)}
\text{A=\name_pt[1]}
\text{B=\name_pt[2]}
\text{C=\name_pt[3]}
\text{D=\name_pt[4]}

\text{recup=}
\text{test=}
\text{borderColor=blue}
\text{sigle=}
\text{ptD=}
\text{determin=}
\text{def_num=}
\text{def_form=}
\text{vec_v=}
