target=TVF1 TVF2 TVF3 TVF21 TVF22 TVF24

#include "author.inc"
#if defined TARGET_TVF1 || defined TARGET_TVF2 || defined TARGET_TVF3
# define NUM I
#endif
#if defined TARGET_TVF21 || defined TARGET_TVF22 || defined TARGET_TVF24
# define NUM II
#endif

#include "lang_titles.inc"
#include "lang.inc"
/* u = nombre de singularites ou zeros de la derivee
t = 0 si première est une discontinuité,
s= 0 si seconde est une discontinuité */
#if defined TARGET_TVF1 || defined TARGET_TVF2 || defined TARGET_TVF3
\integer{u=randitem(2,3)}
\integer{t=0}
\integer{s=0}
#endif
#if defined TARGET_TVF24 ||defined TARGET_TVF21 || defined TARGET_TVF22
\integer{u=randitem(2,3)}
\integer{t=randitem(0,1)}
\integer{s=\u=3 ? randitem(0,1):\t}
#endif
#include "data.inc"

#if defined TARGET_TVF1
\text{M=randitem(randint(\x1+1..\x2-1), randint(\x2+1..\x3-2), randint(\x3+1..\x4-3))}
\text{M=randitem(randint(\x1+1..\x2-1), randint(\x2+1..\x3+2), randint(\x3+4..\x4-3))} %%% modif MB
N est toujours supérieur à M
\text{N=\x2}
\while{\N=\x2}{
  \text{N=\M>=\x3-1 ? randint(\M+2..\x4-1): randitem(randint(\M+1..\x3-1),randint(\x3+1..\x4-1))}
}
\text{sol1= \u=2 and \t=0 and \test[5]>0 ? item(sign(\a2-(\a1))+2,\choix):ouf}
\text{sol1= \u=2 and \t=0 and \test[5]=0 ? zut}
\text{sol1= \u=2 and \t=0 and \test[5]<0 and \N <= \x2 ? item(sign(\a2-(\a1))+2,\choix)}
\text{sol1= \u=2 and \t=0 and \test[5]<0 and \M >= \x2 ? item(sign(\a4-(\a2))+2,\choix)}
\text{sol1= \u=2 and \t=0 and \test[5]<0 and \M<\x2 and \N>\x2 ? \choix[2]}
\text{sol1= \u=2 and \t=1 and \N < \x2 ? item(sign(\a2-(\a1))+2,\choix)}
\text{sol1= \u=2 and \t=1 and \M >= \x2 ? item(sign(\a4-(\a2d))+2,\choix)}
text{sol1= \u=2 and \t=1 and \M >= \x2 and \a4=(\a2d) ? item(sign(\a4)+2,\choix)}
\text{sol1= \u=2 and \t=1 and \N <= \x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=2 and \t=1 and \M < \x2 and \N>\x2 ? \choix[2]}
\text{sol1= \u=3 and \s=1 and \t=0 and (\N-(\x2))*(\M-(\x2))<0 and \test[1]>0 ? item(sign(\a2-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=0 and (\N-(\x2))*(\M-(\x2))<0 and \test[1]<0 ? \choix[2]}
\text{sol1= \u=3 and \s=1 and \t=0 and (\N-(\x3))*(\M-(\x3))<0 ? \choix[2]}
\text{sol1= \u=3 and \s=1 and \t=0 and \M>\x3 ? item(sign((\a4)-(\a3d))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=0 and \N<\x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=0 and \M>\x2 and \N<\x3 ? item(sign((\a3)-(\a2d))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=1 and \N<\x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=1 and \M<\x2 and \N>=\x2 ? \choix[2]}
\text{sol1= \u=3 and \s=0 and \t=1 and \M>\x2 and \N<\x3 ? item(sign(\a3-(\a2d))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=1 and \M>\x2 and \N>\x3 and \test[4]>0 ? item(sign((\a3)-(\a2d))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=1 and \M>\x2 and \N>\x3 and \test[4]<0 ?\choix[2]}
\text{sol1= \u=3 and \s=0 and \t=1 and \M>\x3 ? item(sign((\a4)-(\a3d))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=1 and ((\N-(\x3))*(\M-(\x3)) <0 or (\N-(\x2))*(\M-(\x2))<0)? \choix[2]}
\text{sol1= \u=3 and \s=1 and \t=1 and \N<\x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=1 and \M>\x2 and \N<\x3 ? item(sign((\a3)-(\a2d))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=1 and \M>\x3 ? item(sign((\a4)-(\a3d))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=0 and \N <=\x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=0 and \M<\x2 and \N>=\x2 and \test[1]<0? \choix[2]}
\text{sol1= \u=3 and \s=0 and \t=0 and \M<\x2 and \N>=\x2 and \test[1]>=0? item(sign((\a2)-(\a1))+2,\choix) }
\text{sol1= \u=3 and \s=0 and \t=0 and \M<\x2 and \N>=\x3 and \test[3]<0? \choix[2] }
\text{sol1= \u=3 and \s=0 and \t=0 and \M>=\x2 and \N<=\x3 ? item(sign((\a3)-(\a2))+2,\choix) }
\text{sol1= \u=3 and \s=0 and \t=0 and \M>=\x2 and \N>=\x3 and \test[3]>=0 ? item(sign(\a3-(\a2))+2,\choix) }
\text{sol1= \u=3 and \s=0 and \t=0 and \M>=\x2 and \N>=\x3 and \test[3]<0 ? \choix[2] }
\text{sol1= \u=3 and \s=0 and \t=0 and \M>=\x3 ? item(sign((\a4)-(\a3))+2,\choix) }
\text{sol1= \u=3 and \s=0 and \t=0 and \M<\x1
  and \N > \x3 and \test[1] >=0 and \test[3] >=0 ? item(sign((\a2)-(\a3))+2,\choix)}
#endif
#if defined TARGET_TVF2 || defined TARGET_TVF22
\text{cent=randint(\x1+1 ..\x4-2)}
\real{valeur= random( min(min(\a1,min(\a2,\a2d)),min(\a3,min(\a3d,\a4)))..max(max(\a1,max(\a2,\a2d)),max(\a3,max(\a3d,\a4))))}
\text{sol1= (\cent < \x2 and sign((\valeur-(\a1))*(\valeur-(\a2)))<>1)
  or (\cent >\x2 and \cent <\x3 and sign((\valeur-(\a2d))*(\valeur-(\a3)))<>1)
  or (\cent >\x3 and sign((\valeur-(\a3d))*(\valeur-(\a4)))<>1)
  or (\cent=\x2 and \t=0 and \valeur=\a2)
  or (\cent=\x3 and \s=0 and \valeur=\a3) ?
\choix[1] : \choix[2]}

\text{sol1= (\cent < \x2 and +inf issametext \aa1 and (\a2 -\valeur)<0)
  or (\cent < \x2 and +inf issametext \aa2 and (\a1 -\valeur)>0)
  or (\cent < \x2 and inf isin \aa2 and inf isin \aa1)
  or (\cent < \x2 and -inf issametext \aa1 and (\a2 -\valeur)>0)
  or (\cent < \x2 and -inf issametext \aa2 and (\a1 -\valeur)>0)
  or (\cent > \x2 and \cent <\x3 and +inf issametext \aa2d and (\a3 -\valeur)<0)
  or (\cent > \x2 and \cent <\x3 and +inf issametext \aa3 and (\a2d -\valeur)<0)
  or (\cent > \x2 and \cent <\x3 and inf isin \aa3 and inf isin \aa2d)
  or (\cent > \x2 and \cent <\x3 and -inf issametext \aa2d and (\a3 -\valeur)>0)
  or (\cent > \x2 and \cent <\x3 and -inf issametext \aa3 and (\a2d -\valeur)>0)
  or (\cent > \x3 and +inf issametext \aa3d and (\a4 -\valeur)<0)
  or (\cent > \x3 and +inf issametext \aa4 and (\valeur-\a3d )>0)
  or (\cent > \x3 and inf isin \aa4 and inf isin \aa3d)
  or (\cent > \x3 and -inf issametext \aa3d and (\a4 -\valeur)>0)
  or (\cent > \x3 and -inf issametext \aa4 and (\a3d -\valeur)>0) ? \choix[1]}
#endif
#if defined TARGET_TVF3
\text{M=\u=3 ? randitem(\xx1,\x2,\x3):randitem(\xx1,\x2)}
\text{N=\M=\x2 and \u=3 ?randitem(\x3,\xx4):randitem(\x2,\x3,\xx4)}
\text{N=(\M=\x2 and \u=2) or \M=\x3 ?\xx4}
\text{choixx= shuffle(\choix)}
\text{posi=randitem(-1,1)}
\text{pos= \posi= 1? \name_pos[1]: \name_pos[2]}
\text{sol1= \M issametext \xx1 and \N=\x2 ? min(\a2,\a1),, max(\a2,\a1)}
\text{sol1= \M issametext \xx1 and \N=\x3 ? min(\a3,min(\a2,\a1)),, max(\a3,max(\a2,\a1))}
\text{sol1= \M issametext \xx1 and \N issametext \xx4 ? min(\a4,min(\a3,min(\a2,\a1))),, max(\a4,max(\a3,max(\a2,\a1)))}
\text{sol1= \M=\x2 and \N=\x3 ? min(\a2,\a3),, max(\a2,\a3)}
\text{sol1= \M=\x2 and \N issametext \xx4 ? min(min(\a2,\a3),\a4),, max(max(\a2,\a3),\a4)}
\text{sol1= \M=\x3 and \N issametext \xx4 ? min(\a3,\a4),, max(\a3,\a4)}

\text{sol1= \posi*(item(2-(\posi), \sol1))>=0 ? \choix[1]:\choix[2]}
#endif
#if defined TARGET_TVF21
\text{nombre=wims(wordcnt \dessinxx)}

text{M=randitem(randint(\x1+1..\x2-1), randint(\x2+1..\x3-2), randint(\x3+1..\x4-3))}
N est toujours supérieur à M
%%%%% MB
%%%% pb : ce n'est pas tjrs le cas car \x2 peut être égal à \x3
%%%% modif MB
\integer{M=randitem(randint(\x1+1..\x2-1), randint(\x2+1..\x3+2), randint(\x3+4..\x4-3))}

%%%% Fin modif MB

\text{N=\x2}
\while{\N=\x2}{
  \text{N=\M>=\x3-1 ? randint(\M+2..\x4-1): randitem(randint(\M+1..\x3-1),randint(\x3+1..\x4-1))}
}

\text{sol1= \u=2 and \t=0 and \test[5]>0 ? item(sign(\a2-(\a1))+2,\choix):ouf}
\text{sol1= \u=2 and \t=0 and \test[5]=0 ? zut}
\text{sol1= \u=2 and \t=0 and \test[5]<0 and \N <= \x2 ? item(sign(\a2-(\a1))+2,\choix)}
\text{sol1= \u=2 and \t=0 and \test[5]<0 and \M >= \x2 ? item(sign(\a4-(\a2))+2,\choix)}
\text{sol1= \u=2 and \t=0 and \test[5]<0 and \M<\x2 and \N>\x2 ? \choix[2]}

\text{sol1= \u=2 and \t=1 and \N < \x2 ? item(sign(\a2-(\a1))+2,\choix)}
\text{sol1= \u=2 and \t=1 and \M >= \x2 ? item(sign(\a4-(\a2d))+2,\choix)}
\text{sol1= \u=2 and \t=1 and \N <= \x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=2 and \t=1 and \M < \x2 and \N>\x2 ? \choix[2]}
%%%%% modif MB cas où x2=x3 ie s=1 ou t=1 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% %%%%%%%%%%%%%%%%%%%%% on recalcule tout %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\if{\x2=\x3}{
  \text{sol1= \u=2 and \t=0 and \s=0 and \test[6]>0 ? item(sign(\a2-(\a1))+2,\choix):ouf}
  \text{sol1= \u=2 and \t=0 and \s=0 and \test[6]=0 ? zut}
  \text{sol1= \u=2 and \t=0 and \s=0 and \test[6]<0 and \N <= \x2 ? item(sign(\a2-(\a1))+2,\choix)}
  \text{sol1= \u=2 and \t=0 and \s=0 and \test[6]<0 and \M >= \x2 ? item(sign(\a4-(\a3d))+2,\choix)}
  \text{sol1= \u=2 and \t=0 and \s=0 \test[6]<0 and \M<\x2 and \N>\x2 ? \choix[2]}

  \text{sol1= \u=2 and (\t=1 or \s=1) and \N < \x2 ? item(sign(\a2-(\a1))+2,\choix)}
  \text{sol1= \u=2 and (\t=1 or \s=1) and \M >= \x2 ? item(sign(\a4-(\a3d))+2,\choix)}
  \text{sol1= \u=2 and (\t=1 or \s=1) and \N <= \x2 ? item(sign((\a2)-(\a1))+2,\choix)}
  \text{sol1= \u=2 and (\t=1 or \s=1) and \M < \x2 and \N>\x2 ? \choix[2]}
}
%%%%%%%%%%%%%%%%%%%%%%%%%%%% fin modif MB %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\text{sol1= \u=3 and \s=1 and \t=0 and (\N-(\x2))*(\M-(\x2))<0 and \test[1]>0 ? item(sign(\a2-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=0 and (\N-(\x2))*(\M-(\x2))<0 and \test[1]<0 ? \choix[2]}
\text{sol1= \u=3 and \s=1 and \t=0 and (\N-(\x3))*(\M-(\x3))<0 ? \choix[2]}
\text{sol1= \u=3 and \s=1 and \t=0 and \M>\x3 ? item(sign((\a4)-(\a3d))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=0 and \N<\x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=0 and \M>\x2 and \N<\x3 ? item(sign((\a3)-(\a2d))+2,\choix)}

\text{sol1= \u=3 and \s=0 and \t=1 and \N<\x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=1 and \M<\x2 and \N>=\x2 ? \choix[2]}
\text{sol1= \u=3 and \s=0 and \t=1 and \M>\x2 and \N<\x3 ? item(sign(\a3-(\a2d))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=1 and \M>\x2 and \N>\x3 and \test[4]>0 ? item(sign((\a3)-(\a2d))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=1 and \M>\x2 and \N>\x3 and \test[4]<0 ?\choix[2]}
\text{sol1= \u=3 and \s=0 and \t=1 and \M>\x3 ? item(sign((\a4)-(\a3d))+2,\choix)}

\text{sol1= \u=3 and \s=1 and \t=1 and ((\N-(\x3))*(\M-(\x3)) <0 or (\N-(\x2))*(\M-(\x2))<0)? \choix[2]}
\text{sol1= \u=3 and \s=1 and \t=1 and \N<\x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=1 and \M>\x2 and \N<\x3 ? item(sign((\a3)-(\a2d))+2,\choix)}
\text{sol1= \u=3 and \s=1 and \t=1 and \M>\x3 ? item(sign((\a4)-(\a3d))+2,\choix)}

\text{sol1= \u=3 and \s=0 and \t=0 and \N <=\x2 ? item(sign((\a2)-(\a1))+2,\choix)}
\text{sol1= \u=3 and \s=0 and \t=0 and \M<\x2 and \N>=\x2 and \test[1]<0? \choix[2] }
\text{sol1= \u=3 and \s=0 and \t=0 and \M<\x2 and \N>=\x2 and \test[1]>=0? item(sign((\a2)-(\a1))+2,\choix) }
\text{sol1= \u=3 and \s=0 and \t=0 and \M>=\x2 and \N<=\x3 ? item(sign((\a3)-(\a2))+2,\choix) }
\text{sol1= \u=3 and \s=0 and \t=0 and \M>=\x2 and \N>=\x3 and \test[3]>=0 ? item(sign(\a3-(\a2))+2,\choix) }
\text{sol1= \u=3 and \s=0 and \t=0 and \M>=\x2 and \N>=\x3 and \test[3]<0 ? \choix[2] }
\text{sol1= \u=3 and \s=0 and \t=0 and \M>=\x3 ? item(sign((\a4)-(\a3))+2,\choix) }
\text{sol1= \u=3 and \s=0 and \t=0 and \M<\x1 and \N > \x3 and \test[1] >=0 and \test[3] >=0 ?
  item(sign((\a2)-(\a3))+2,\choix)}

#endif
#if defined TARGET_TVF24
\text{Inf=inf}
\text{sol1= \u=2 and \Inf notin \aa1 and \Inf notin \aa2 and \Inf notin \aa3d and \Inf notin \aa4 ? 1:2}
\text{sol1= \u=3 and \Inf notin \aa1 and \Inf notin \aa2 and
  \Inf notin \aa2d and \Inf notin \aa3 and \Inf notin \aa3d and \Inf notin \aa4 ? 1}

\text{majo=randitem(\name_majo)}
\text{signe=maj isin \majo? +:-}

\if{\sol1 = 1}{
  \text{sol2= ( \Inf isin \xx1 and \a1 >max(\a2d,max(\a2,max(\a3,max(\a3d,\a4)))))
   or ( \Inf isin \xx4 and \a4 >= max(\a2d,max(\a2,max(\a3,max(\a3d,\a1)))))
   or (\t=1 and max(\a2,\a2d) >max(\a1,max(\a3,max(\a3d,\a4))))
   or (\s=1 and max(\a3,\a3d) >max(\a1,max(\a2,max(\a2d,\a4)))) ? 2: 1}
 }{
 \text{sol3=(\u=3 and \signe\Inf issametext \aa1)
  or \signe\Inf issametext \aa2
  or \signe\Inf issametext \aa2d
  or \signe\Inf issametext \aa3
  or \signe\Inf issametext \aa3d
  or \signe\Inf issametext \aa4 ? 2:1}
 \text{sol3=(\u=2 and \signe\Inf issametext \aa1)
  or \signe\Inf issametext \aa2
  or \signe\Inf issametext \aa3d
  or \signe\Inf issametext \aa4 ? 2}
}

\matrix{STEP=\sol1 = 1? reply1;reply2 }
\matrix{STEP=\sol1 = 2 ? reply1;reply3}
\steps{\STEP}
#endif
\text{debug=%%% debug
<br>valeur= \valeur
<br>sol1=\sol1
<br>x1=\x1 ;x2=\x2 ;x3=\x3 ;x4=\x4 ;
<br>M=\M, N=\N
<br>t=\t ; s=\s ; u=\u
<br>a4=\a4 a2d=\a2d a2=\a2 a3=\a3 a3d=\a3d signe(a4-a2d)=}
#if defined TARGET_TVF2 || defined TARGET_TVF3
\text{cont=\name_cont}
#else
\text{cont=}
#endif
\statement{
Le tableau de variation de la fonction \cont \(f\) entre \(\xx1\) et
\if{\xx4 issametext +inf}{+\(\xx4 \)}{\(\xx4\)} est le suivant:
<div class="wimscenter"><img src="\tableau" alt=""></div>
#if defined TARGET_TVF1 || defined TARGET_TVF21 ||defined TARGET_TVF22
La fonction \(f\) est continue là où elle est définie.
#endif
<div class="wims_question">
#if defined TARGET_TVF1
Sur l'intervalle [\M ,\N], que peut-on dire de la croissance de \(f\) ?
#endif
#if defined TARGET_TVF2 || defined TARGET_TVF22
Est-il possible que \(f(\cent) = \valeur \) ?
\embed{\choice 1}
#endif
#if defined TARGET_TVF3
La fonction \(f) est-elle \pos ou nulle sur [\(\M, \N )] ?
#endif
#if defined TARGET_TVF21
Sur l'intervalle [\M ,\N], que peut-on dire de la croissance de \(f\) ?
#endif
#if defined TARGET_TVF24
\if{\step = 1}{<label for="reply1">La fonction \(f\) est-elle bornée ?</label> \embed{reply1}}
\if{\step=2}{
  \if{\sol1 = 1}{Admet-elle un maximum ? \embed{reply 2 }}
  {<label for="reply3">Est-elle \majo ?</label>\embed{reply 3}}}
#endif
</div>
}
#if defined TARGET_TVF1 || defined TARGET_TVF21 || defined TARGET_TVF3
\choice{}{\sol1}{\choix}
#endif
#if defined TARGET_TVF2|| defined TARGET_TVF22
\choice{Possible ?}{\sol1}{\choix}
#endif
#if defined TARGET_TVF24
\answer{bornée}{\sol1;\choix}{type=radio}
\answer{maximum}{\sol2;\choix}{type=radio}
\answer{\majo}{\sol3;\choix}{type=radio}
#endif
