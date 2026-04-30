%%%%% FEEDBACK %%%%%

\matrix{recup=\sc_reply1}
\if{\recup[1;]=1}
   {\text{test=1}
    \text{borderColor=green}
    \text{sigle=tick}
   }
   {\if{1 isin \recup[2;]}
      {\text{test=0.5}
       \text{borderColor=orange}
       \text{sigle=approx}
      }
      {\text{test=0}
       \text{borderColor=red}
       \text{sigle=croix}
      }
    }
\integer{nb_objets=wims(line 1 of \reply1)}
\text{def_form=wims(line 2..\nb_objets+1 of \reply1)}
\text{def_num=wims(line \nb_objets+2..-1 of \reply1)}

\text{ptD=wims(getopt \D in \def_form)}
\integer{xptD=\ptD[1]}
\integer{yptD=\ptD[2]}

\text{vec_v=wims(getopt v in \def_num)}
\text{vec_v=wims(item 2,3 of \vec_v)}

\if{\conf1=1}
  {\if{\vec[1;1]!=0}
    {\text{coef_colin=pari(\vec_v[1]/\vec[1;1])}}
    {\text{coef_colin=pari(\vec_v[2]/\vec[1;2])}}
   \if{\coef_colin=1}
     {\text{coef_colin=}}
     {\if{\coef_colin=-1}
       {\text{coef_colin=-}}
       {\text{coef_colin=texmath(\coef_colin)}}
     } 
  }
#if defined TARGET_01colineaire || defined TARGET_02memesens || TARGET_03sensoppose
\if{\xC=\xptD and \yC=\yptD}
  {\text{verif1=0}}
  {\text{verif1=1}}
#endif

#if defined TARGET_04egaux || defined TARGET_05oppose || defined TARGET_06memenorme || defined TARGET_07memenormenoncoli
\text{norme=pari((\vec[1;1])^2+(\vec[1;2])^2-(\vec_v[1])^2-(\vec_v[2])^2)}
\if{\norme!=0}
  {\text{verif1=0}}
  {\text{verif1=1}}
#endif

#if defined TARGET_01colineaire || defined TARGET_02memesens || defined TARGET_03sensoppose || defined TARGET_04egaux || defined TARGET_05oppose || defined TARGET_07memenormenoncoli 
\text{determin=pari(matdet([\vec[1;];\vec_v]))}
\if{\determin!=0}
  {\text{verif2=0}}
  {\text{verif2=1}}
#endif
  
#if defined TARGET_02memesens || defined TARGET_03sensoppose || defined TARGET_04egaux || defined TARGET_05oppose
\text{prodscal=pari((\vec[1;1])*(\vec_v[1])+(\vec[1;2])*(\vec_v[2]))}

# if defined TARGET_02memesens || defined TARGET_03sensoppose
\if{\verif1=1 and \verif2=1 and 
#  if defined TARGET_02memesens
\prodscal<0}
#  else
\prodscal>0}
#  endif
  {\text{verif3=0}}
  {\text{verif3=1}}
# endif

# if defined TARGET_04egaux || defined TARGET_05oppose
\if{ 
#  if defined TARGET_04egaux
\prodscal<0}
#  else
\prodscal>0}
#  endif
  {\text{verif3=0}}
  {\text{verif3=1}}
#  endif
# endif

#endif
