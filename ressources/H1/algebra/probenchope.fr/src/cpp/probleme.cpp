target=randonnee bonbon pomme librairie chocolat lacourse panini supermarche depense pile prog1 autobus camion

%%%%%%%%%%%%%%%%%%%%%%%%%%% TO DO
mettre un ex de geom ?
si confparm1=1 la longueur des étiquettes doit-elle correspondre exactement à la long expression attendue ou on met une marge ??
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include "common.inc"
#include "lang.inc"
#include "lang_titles.inc"

\if{\confparm1=}{\text{confparm1=1}}

\title{TITLE}

%%Choix du prénom d'un personnage%%
\integer{s=randint(2)}
\if{\s=1}{\text{prenom=slib(lang/fname fr, boy)}
         \text{name_text=wims(replace internal word QQQ by Il in \name_text)}
         \text{name_text=wims(replace internal word qqq by il in \name_text)}
         \text{name_ans=wims(replace internal word QQQ by Il in \name_ans)}
         }
         {\text{prenom=slib(lang/fname fr, girl)}
         \text{name_text=wims(replace internal word QQQ by Elle in \name_text)}
         \text{name_text=wims(replace internal word qqq by elle in \name_text)}
         \text{name_ans=wims(replace internal word QQQ by elle in \name_ans)}
         }
\text{name_text=wims(replace internal word PPP by \prenom in \name_text)}
\text{name_quest1=wims(replace internal word PPP. by \prenom. in \name_quest1)}
\text{name_quest2=wims(replace internal word PPP. by \prenom. in \name_quest2)}
\text{name_sol2=wims(replace internal word QQQ by \prenom in \name_sol2)}

%%Chargement des données pour les exercices%%
#if defined TARGET_randonnee
\matrix{a=wims(record 1 of donnees)}
#endif
#if defined TARGET_bonbon
\text{a = wims(record 2 of donnees)}
#endif
#if defined TARGET_pomme
\text{a = wims(record 3 of donnees)}
#endif
#if defined TARGET_librairie
\matrix{a=wims(record 4 of donnees)}
#endif
#if defined TARGET_chocolat
\text{a = wims(record 5 of donnees)}
#endif
#if defined TARGET_lacourse
\text{a = wims(record 6 of donnees)}
#endif
#if defined TARGET_panini
\text{a = wims(record 7 of donnees)}
#endif
#if defined TARGET_supermarche
\text{a = wims(record 8 of donnees)}
#endif
#if defined TARGET_depense
\text{a = wims(record 9 of donnees)}
#endif
#if defined TARGET_pile
\text{a = wims(record 10 of donnees)}
#endif
#if defined TARGET_prog1
\text{a = wims(record 11 of donnees)}
#endif
#if defined TARGET_autobus
\text{a = wims(record 12 of donnees)}
#endif
#if defined TARGET_camion
\text{a = wims(record 13 of donnees)}
#endif

\integer{nbdon=rows(\a)}

%%Création des données aléatoires%%
\text{don=}
\for{i=1 to \nbdon}{\integer{nbitems=items(\a[\i;])}
                    \if{\nbitems=2}{\text{d=randint(\a[\i;1] .. \a[\i;2])}}
                    \if{\nbitems>2}{\text{d=shuffle(\a[\i;])}
                                    \text{d=\d[1]}
                                   }
                     \if{\nbitems=1}{\text{d=\a[\i;1]}}     
                     \text{don=wims(append item \d to \don)}
                   }
%%Les nombres sont écrits avec une virgule%%
\text{tdon1=slib(numeration/ecriturenombre \don[1],comma)}
\text{tdon2=slib(numeration/ecriturenombre \don[2],comma)}
\text{tdon3=slib(numeration/ecriturenombre \don[3],comma)}
\text{tdon4=slib(numeration/ecriturenombre \don[4],comma)}
\text{tdon5=slib(numeration/ecriturenombre \don[5],comma)}
\text{tdon6=slib(numeration/ecriturenombre \don[6],comma)}
\text{tdon7=slib(numeration/ecriturenombre \don[7],comma)}
      
#if defined TARGET_randonnee                                    
\text{good1=wims(replace internal .  by &#44; in \don[1] \times ( \don[2] \plus \don[3] ) \minus \don[4])}
\text{good2=wims(replace internal .  by &#44; in \don[1] \times \don[2] \plus \don[1] \times \don[3] \minus \don[4])}                                   
\text{good=\good1,\good2}
\text{bad1=wims(replace internal .  by &#44; in \don[1] \times ( \don[2] \plus \don[3] ) \plus \don[4])}
\text{bad2=wims(replace internal .  by &#44; in \don[1] \times \don[2] \plus \don[1] \times \don[3] \plus \don[4])}
\text{bad=\bad1,\bad2}
\text{ngood=1,2}
\real{sol=\don[1]*(\don[2]+\don[3])-\don[4]}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}
\integer{nbrechar=9}
%%Calculs intermédiaires de la solution%%
\real{inter1=\don[2]+\don[3]}
\text{tinter1=slib(numeration/ecriturenombre \inter1,comma)}
\real{prod=\don[1]*\inter1}
\text{tprod=slib(numeration/ecriturenombre \prod,comma)}
\real{p1=\don[1]*\don[2]}
\text{tp1=slib(numeration/ecriturenombre \p1,comma)}
\real{p2=\don[1]*\don[3]}
\text{tp2=slib(numeration/ecriturenombre \p2,comma)}
\real{som=\p1+\p2}
\text{tsom=slib(numeration/ecriturenombre \som,comma)}
\solution{1. \name_sol1 <li class="wims_nopuce">\(D=\good1\)</li> \sol1 <li class="wims_nopuce"><span class="nowrap">\(D=\good2\).</span></li>
<p>2. \(D= \tdon1 \times ( \tdon2 \plus \tdon3 ) \minus \tdon4\)</p>
\(D=\tdon1 \times \tinter1 - \tdon4\)
<p>\(D=\tprod - \tdon4\)</p>
\(\D=\tsol\)
<p>\name_sol2 \(\tsol\) km.</p>
\sol2
<p>\(\D=\tdon1 \times \tdon2 + \tdon1 \times \tdon3 \minus \tdon4\)</p>
\(\D=\tp1 + \tp2 - \tdon4\)
</p>\(\D=\tsom - \tdon4\)</p>
\(\D=\tsol\)
<p>\name_sol2 \(\tsol\) km.</p>}
#endif

#if defined TARGET_bonbon
\text{good1=wims(replace internal .  by &#44; in \don[1] \times \don[2] \minus \don[3])}
\text{good=\good1}
\text{bad1=wims(replace internal .  by &#44; in \don[1] \times \don[2] \plus \don[3])}
\text{bad2=wims(replace internal .  by &#44; in (\don[1] \minus \don[3]) \times \don[2])}
\text{bad3=wims(replace internal .  by &#44; in \don[1] \times \don[2])}
\text{bad=\bad1,\bad2,\bad3}
\text{ngood=1}
\integer{nbrechar=5}
\real{sol=\don[1]*\don[2]-\don[3]}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}
%%Calculs intermédiaires de la solution%%
\real{inter=\don[1]*\don[2]}
\text{tinter=slib(numeration/ecriturenombre \inter,comma)}
\real{dif=\inter-\don[3]}
\text{tdif=slib(numeration/ecriturenombre \dif,comma)}
\text{bonbon=\sol=1?\name_sing:\name_plur}
\solution{1. \name_sol1 <span class="nowrap">\(B= \tdon1 \times \tdon2 \minus \tdon3\).</span>
<p>2. \(B= \tdon1 \times \tdon2 \minus \tdon3\)</p>
\(B=\tinter - \tdon3\)
<p>\(B=\tsol\)</p>
\name_sol2 \(\tsol\) \bonbon}
#endif

#if defined TARGET_pomme
\text{good1=wims(replace internal .  by &#44; in (\don[1] \plus \don[2]) \times \don[3])}
\text{good2=wims(replace internal .  by &#44; in \don[3] \times \don[1]+ \don[3] \times \don[2])}
\text{good3=wims(replace internal .  by &#44; in \don[3] \times (\don[1]+\don[2]))}
\text{good=\good1,\good2,\good3}
\text{bad1=wims(replace internal .  by &#44; in (\don[1] \minus \don[2]) \times \don[3])}
\text{bad2=wims(replace internal .  by &#44; in \don[3] \times \don[1] \minus \don[3] \times \don[2])}
\text{bad3=wims(replace internal .  by &#44; in \don[3] \times (\don[1] \minus \don[2]))}
\text{bad=\bad1,\bad2,\bad3}
\text{ngood=1,2}
\integer{nbrechar=9}
\real{tmp=(\don[1]+\don[2])*\don[3]}
\text{ttmp=slib(numeration/ecriturenombre \tmp,comma)}
\real{tmp1=\don[1]+\don[2]}
\text{ttmp1=slib(numeration/ecriturenombre \tmp1,comma)}
\real{sol=\tmp1*\don[3]}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}

\solution{1. \name_sol1 <li class="wims_nopuce"><span class="nowrap">\(P=\good1\)</li> \sol1 <li class="wims_nopuce">\(P=\good2\)</li> \sol1 <li class="wims_nopuce"><span class="nowrap">\(P=\good3\).</span></li>
<p>2. \(P=\tdon3 \times (\tdon1+\tdon2)\)</p>
\(P=\tdon3 \times \ttmp1\)
<p>\(P=\tsol\)</p>
\name_sol2 \tsol\name_unit}
#endif

#if defined TARGET_librairie
\text{good1=wims(replace internal .  by &#44; in \don[3]-(\don[1]+\don[2]))}
\text{good2=wims(replace internal .  by &#44; in \don[3] \minus \don[1] \minus \don[2])}
\text{good=\good1,\good2}
\text{bad1=wims(replace internal .  by &#44; in \don[1]+\don[2])}
\text{bad2=wims(replace internal .  by &#44; in (\don[1]+\don[2]) \minus \don[3])}
\text{bad=\bad1,\bad2}
\text{ngood=1,2}
\integer{nbrechar=7}
\real{tmp=\don[1]+\don[2]}
\text{ttmp=slib(numeration/ecriturenombre \tmp,comma)}
\real{sol=\don[3]-\tmp}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}
\solution{1. \name_sol1 <li class="wims_nopuce"><span class="nowrap">\(R=\good1\)</li> \sol1 <li class="wims_nopuce"><span class="nowrap">\(R=\good2\).</span></li>
<p>2. \(R=\tdon3-(\tdon1+\tdon2)\)</p>
\(R=\tdon3-\ttmp\)
<p>\(R=\tsol\)</p>
\name_sol2 <span class="nowrap">\(\tsol\) \name_unit</span>}
#endif

#if defined TARGET_chocolat
\text{good1=wims(replace internal .  by &#44; in \don[1] \times \don[2] - \don[3])}
\text{good=\good1}
\text{bad1=wims(replace internal .  by &#44; in \don[4] \minus \don[1] \times \don[2] \minus \don[3])}
\text{bad2=wims(replace internal .  by &#44; in \don[4] \minus \don[1] \times \don[2] \plus \don[3])}
\text{bad=\bad1,\bad2}
\text{ngood=1}
\integer{nbrechar=7}
\real{tmp=\don[1]*\don[2]}
\text{ttmp=slib(numeration/ecriturenombre \tmp,comma)}
\real{sol=\tmp-\don[3]}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}
\solution{1. \name_sol1 <span class="nowrap">\(P=\tdon1 \times \tdon2 - \tdon3\).</span>
<p>2. \(P=\tdon1 \times \tdon2 - \tdon3\).</p>
\(P=\ttmp -\tdon3\)
<p>\(P=\tsol\)</p>
\name_sol2 <span class="nowrap">\(\tsol\) \name_unit</span>}
#endif

#if defined TARGET_lacourse
\text{good1=wims(replace internal .  by &#44; in \don[1] \minus \don[2] \times \don[3])}
\text{good=\good1}
\text{bad1=wims(replace internal .  by &#44; in \don[2] \times \don[3] \minus \don[1])}
\text{bad2=wims(replace internal .  by &#44; in \don[2] \times \don[3] \plus \don[1])}
\text{bad3=wims(replace internal .  by &#44; in \don[1] \plus \don[2] \times \don[3])}
\text{bad=\bad1,\bad2,\bad3}
\text{ngood=1}
\integer{nbrechar=7}
\real{tmp=\don[2]*\don[3]}
\text{ttmp=slib(numeration/ecriturenombre \tmp,comma)}
\real{sol=\don[1]-\tmp}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}
\solution{1. \name_sol1 <span class="nowrap">\(M=\tdon1-\tdon2 \times \tdon3\).</span>
<p>2. \(M=\tdon1-\tdon2 \times \tdon3\)</p>
\(M=\tdon1-\ttmp\)
<p>\(M=\tsol\)</p>
\name_sol2 <span class="nowrap">\(\tsol\) \name_unit</span>}
#endif

#if defined TARGET_panini
\real{tmp=\don[1]*\don[2]+\don[3]*\don[4]}
\real{tmp0=\don[5]-\tmp}
\text{don=wims(append item \tmp0 to \don)}
\integer{nbdon=\nbdon+1}
\text{good1=wims(replace internal .  by &#44; in (\don[5] - \don[6] - \don[1] \times \don[2]) \div \don[3])}
\text{good2=wims(replace internal .  by &#44; in (\don[5] - (\don[6] + \don[1] \times \don[2])) \div \don[3])}
\text{good=\good1,\good2}
\text{bad1=wims(replace internal .  by &#44; in \don[5] - \don[6] - \don[1] \times \don[2])}
\text{bad2=wims(replace internal .  by &#44; in \don[5] - (\don[6] + \don[1] \times \don[2]))}
\text{bad=\bad1,\bad2}
\text{ngood=1,2}
\integer{nbrechar=13}
\real{tmp=\don[1]*\don[2]+\don[3]*\don[4]}
\real{tmp0=\don[5]-\tmp}
\text{ttmp0=slib(numeration/ecriturenombre \tmp0,comma)}
\text{don=wims(append item \tmp0 to \don)}
\real{tmp=\don[1]*\don[2]}
\text{ttmp=slib(numeration/ecriturenombre \tmp,comma)}
\text{tmp1=(\tdon5 - \ttmp0 - \ttmp ) \div \tdon3}
\text{ttmp1=slib(numeration/ecriturenombre \tmp1,comma)}
\real{tmp2=\don[5] - \don[6]}
\text{ttmp2=slib(numeration/ecriturenombre \tmp2,comma)}
\text{tmp3=(\ttmp2 - \ttmp ) \div \tdon3}
\text{ttmp3=slib(numeration/ecriturenombre \tmp3,comma)}
\real{tmp4=\tmp2-\tmp}
\text{ttmp4=slib(numeration/ecriturenombre \tmp4,comma)}
\text{tmp5=\ttmp4 \div \tdon3}
\text{ttmp5=slib(numeration/ecriturenombre \tmp5,comma)}
\real{sol=\tmp4/\don[3]}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}
\solution{1. \name_sol1 <li class="wims_nopuce"><span class="nowrap">\(P=\good1\)</li> \sol1 <li class="wims_nopuce"><span class="nowrap">\(P=\good2\).</span></li>
<p>2. \(P=(\tdon5 - \ttmp0 - \tdon1 \times \tdon2) \div \tdon3\)</p>
\(P=\tmp1\)
<p>\(P=\tmp3\)</p>
\(P=\tmp5\)
<p>\(P=\tsol\)</p>
\name_sol2 <span class="nowrap">\(\tsol\) \name_unit</span>}
#endif

#if defined TARGET_supermarche
\text{good1=wims(replace internal .  by &#44; in \don[1]-(\don[2] \times \don[3] + \don[4] \times \don[5] + \don[6] \times \don[7]))}
\text{good2=wims(replace internal .  by &#44; in \don[1] \minus \don[2] \times \don[3] \minus \don[4] \times \don[5] \minus \don[6] \times \don[7])}
\text{good=\good1,\good2}
\text{bad1=wims(replace internal .  by &#44; in \don[2] \times \don[3] + \don[4] \times \don[5] + \don[6] \times \don[7])}
\text{bad2=wims(replace internal .  by &#44; in (\don[2] \times \don[3] + \don[4] \times \don[5] + \don[6] \times \don[7]) \minus \don[1])}
\text{bad=\bad1,\bad2}
\text{ngood=1,2}
\integer{nbrechar=15}
\real{sol=\don[1]-(\don[2]*\don[3]+\don[4]*\don[5]+\don[6]*\don[7])}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}
\text{tempu=\tdon1 \minus (\tdon2 \times \tdon3 \plus \tdon4 \times \tdon5 \plus \tdon6 \times \tdon7)}
\real{tmp1=\don[2]*\don[3]}
\text{ttmp1=slib(numeration/ecriturenombre \tmp1,comma)}
\real{tmp2=\don[4]*\don[5]}
\text{ttmp2=slib(numeration/ecriturenombre \tmp2,comma)}
\real{tmp3=\don[6]*\don[7]}
\text{ttmp3=slib(numeration/ecriturenombre \tmp3,comma)}
\text{tmp4=wims(texmath \tdon1-(\ttmp1 + \ttmp2 + \ttmp3))}
\real{tmp5=\tmp1+\tmp2}
\text{ttmp5=slib(numeration/ecriturenombre \tmp5,comma)}
\text{tmp6=wims(texmath \tdon1-(\ttmp5 + \ttmp3))}
\real{tmp7=\tmp5 + \tmp3}
\text{ttmp7=slib(numeration/ecriturenombre \tmp7,comma)}
\text{tmp8=wims(texmath \tdon1 -\ttmp7)}
\real{tmp9=\tdon1- \ttmp7}
\text{ttmp9=slib(numeration/ecriturenombre \tmp9,comma)}
\solution{1. \name_sol1 <li class="wims_nopuce"><span class="nowrap">\(R=\good1\)<li> \sol1 <li class="wims_nopuce"><span class="nowrap">\(R=\good2\).</span></li>
<p>2. \(R=\tempu\)</p>
\(R=\tmp4\)
<p>\(R=\tmp6\)</p>
\(R=\tmp8\)
<p>\(R=\tsol\)</p>
\name_sol2 <span class="nowrap">\(\tsol\) \name_unit</span>}
#endif

#if defined TARGET_depense
\text{good1=wims(replace internal .  by &#44; in \don[1]\plus\don[2]\times\don[3])}
\text{good2=wims(replace internal .  by &#44; in \don[2]\times\don[3]+\don[1])}
\text{good=\good1,\good2}
\text{bad1=wims(replace internal .  by &#44; in (\don[1]+\don[2]) \times \don[3])}
\text{bad2=wims(replace internal .  by &#44; in \don[2] \times (\don[3]+\don[1]))}
\text{bad=\bad1,\bad2}
\text{ngood=1,2}
\integer{nbrechar=8}
\real{sol=\don[1]+\don[2]*\don[3]}
\text{tmp=\don[1] \plus \don[2] \times \don[3]}
\real{tmp1=\don[2]*\don[3]}
\text{tmp2=wims(texmath \don[1] + \tmp1)}
\solution{1. \name_sol1 <li class="wims_nopuce"><span class="nowrap">\(R=\good1\)</li> \sol1 <li class="wims_nopuce"><span class="nowrap">\(R=\good2\).</span></li>
<p>2. \(R=\good1\)</p>
\(R=\tmp2\)
<p>\(R=\sol\)</p>
\name_sol2 <span class="nowrap">\(\sol\) \name_unit</span>}
#endif

#if defined TARGET_pile
\real{sol=randint(1..2)+randint(1..9)/10+randint(1..9)/100}
\real{don2=randint(29..39)+randint(1..9)/10+randint(1..9)/100}
\integer{don3=randint(2..8)}
\real{don1=\don3*\sol+\don2}
\text{don=\don1,\don2,\don3}
\text{tdon1=slib(numeration/ecriturenombre \don[1],comma)}
\text{tdon2=slib(numeration/ecriturenombre \don[2],comma)}
\text{tdon3=slib(numeration/ecriturenombre \don[3],comma)}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}
\real{tmp1=\don1-\don2}
\text{ttmp1=slib(numeration/ecriturenombre \tmp1,comma)}
\text{ttsol=(\tdon1 \minus \tdon2) \div \tdon3}
\text{good1=wims(replace internal .  by &#44; in (\don1 \minus \don2) \div \don3)}
text{tgood1=wims(texmath \good1)}
\text{good=\good1}
\text{bad1=wims(replace internal .  by &#44; in \don1-\don2)}
\text{bad2=wims(replace internal .  by &#44; in \don1-\don2 \div \don3)}
\text{bad=\bad1,\bad2}
\text{ngood=1}
\integer{nbrechar=9}
\solution{1. \name_sol1 <span class="nowrap">\(P=\ttsol\).</span>
<p>2. \(P=\ttsol\)</p>
\(P=\ttmp1 \div \tdon3\)
<p>\(P=\tsol\)</p>
\name_sol2 <span class="nowrap">\(\tsol\) \name_unit</span>}
\real{badrep=\don1 - \don2/\don3}
#endif

#if defined TARGET_prog1                                               
\real{sol=(\don[1]*\don[2]+\don[3])*2-\don[4]}
\text{tsol=slib(numeration/ecriturenombre \sol,comma)}
\real{tmp1=\don[1]*\don[2]}
\text{ttmp1=slib(numeration/ecriturenombre \tmp1,comma)}
\text{tdon1=slib(numeration/ecriturenombre \don[1],comma)}
\text{tdon2=slib(numeration/ecriturenombre \don[2],comma)}
\text{tdon3=slib(numeration/ecriturenombre \don[3],comma)}
\text{ttsol=(\tdon1 \times \tdon2 \plus \tdon3) \times 2 \minus \tdon4}
\text{good1=wims(replace internal .  by &#44; in (\tdon1 \times \tdon2 \plus \tdon3) \times 2 \minus \tdon4)}
text{tgood1=wims(texmath \good1)}
\text{good=\good1}
\text{bad1=wims(replace internal .  by &#44; in \tdon1 \times \tdon2 \plus \tdon3 \times 2 \minus \tdon4)}
\text{bad2=wims(replace internal .  by &#44; in (\tdon1 \times \tdon2 \plus \tdon3) \times 3 \minus \tdon4)}
\text{bad3=wims(replace internal . by #44; in (\don[1] \plus \don[2] \plus \don[3]) \times 2-\don[4])}
\text{bad=\bad1,\bad2,\bad3}
\text{ngood=1}
\integer{nbrechar=12}
\real{tmp2=(\tmp1+\don[3])*2-\don[4]}
\real{tmp3=\tmp1+\don[3]}
\real{tmp4=\tmp3*2}
\text{ttmp2=(\ttmp1+\tdon3)*2-\tdon4}
\text{ttmp3=\tmp3 \times 2 \minus \tdon4}
\text{ttmp4=\tmp4 \minus \tdon4}
\solution{1. \name_sol1 <span class="nowrap">\(R=\ttsol\).</span>
<p>2. \(R=\ttsol\)</p>
\(R=\ttmp2\)
<p>\(R=\ttmp3\)</p>
\(R=\ttmp4\)
<p>\(R=\tsol\)</p>
\name_sol2 <span class="nowrap">\(\tsol\)\name_unit</span>}
\real{badrep=\don1 \times \don2 \plus \don3 \times 2 \minus \don4}
#endif

#if defined TARGET_autobus
\integer{nbrechar=9}
\integer{sol=\don[1]-\don[2]+\don[3]-\don[4]+\don[5]}
\text{tsol=\don[1] \minus \don[2] \plus \don[3] \minus \don[4] \plus \don[5]}
\text{good1=\tsol}
\text{good2=\don[1] \plus \don[3] \plus \don[5] \minus \don[2] \minus \don[4]}
\text{good=\good1,\good2}
\text{ngood=1,2}
\text{bad1=\don[1] \plus \don[2] \minus \don[3] \plus \don[4] \minus \don[5]}
\text{bad2=\don[2] \minus \don[3] \plus \don[4] \minus \don[5]}
\text{bad3=\don[2] \plus \don[3] \minus \don[4] \plus \don[5]}
\text{bad=\bad1,\bad2,\bad3}
\integer{tmp2=\don[1]-\don[2]}
\text{ttmp2=\tmp2 \plus \don[3] \minus \don[4] \plus \don[5]}
\integer{tmp3=\tmp2 + \don[3]}
\text{ttmp3=\tmp3 \minus \don[4] \plus \don[5]}
\real{tmp4=\tmp3-\don[4]}
\text{ttmp4=\tmp4 \plus \don[5]}
\solution{1. \name_sol1 <li class="wims_nopuce"><span class="nowrap">\(A=\good1\)</li> \sol1 <li class="wims_nopuce"><span class="nowrap">\(A=\good2\).</span></li>
<p>2. \(A=\tsol\)</p>
\(A=\ttmp2\)
<p>\(A=\ttmp3\)</p>
\(A=\ttmp4\)
<p>\(A=\sol\)</p>
\name_sol2 <span class="nowrap">\(\sol\) \name_unit</span>}
#endif

#if defined TARGET_camion
\integer{nbrechar=9}
\integer{sol=\don[1]-\don[3]*\don[2]}
\text{tsol=\don[1] \minus \don[3] \times \don[2]}
\text{good1=\tsol}
\text{good=\good1}
\text{ngood=1}
\text{bad1=\don[1] \plus \don[3] \times \don[2]}
\text{bad2=(\don[1] \minus \don[2]) \times \don[3]}
\text{bad3=\don[2] \times \don[3]}
\text{bad=\bad1,\bad2,\bad3}
\integer{tmp2=\don[3]*\don[2]}
\text{ttmp2=\don[1] \minus \tmp2}
\solution{1. \name_sol1 <span class="nowrap">\(C=\good1\).</span>
<p>2. \(C=\tsol\)</p>
\(C=\ttmp2\)
<p>\(C=\sol\)</p>
\name_sol2 <span class="nowrap">\(\sol\) \name_unit</span>}
#endif

%%Remplacement des NNNi par les valeurs numériques%%
\text{listedon=}
\for{i=1 to \nbdon}{\if{NNN\i iswordof \name_text or NNN\i iswordof \name_quest1 or NNN\i iswordof \name_quest1_1}{\text{tmp=\don[\i]}
                                                   \text{ttmp=slib(numeration/ecriturenombre \tmp,comma)}
                                                   \text{ttmpu=wims(replace internal . by &#44; in \don[\i])}
                                                   \text{name_text=wims(replace internal word NNN\i by \(\ttmp\) in \name_text)}
                                                   \text{listedon=wims(append item \ttmpu to \listedon)}
                                               }
                   } 
%%% Remplacement supplementaire dans les questions ou solutions de certains exercices %%%%%         
#if defined TARGET_prog1
\text{listedon=wims(append item 2,\(\don[1]\) to \listedon)}
\if{NNN1 iswordof \name_quest1}{\text{name_quest1=wims(replace internal word NNN1 by \(\don[1]\) in \name_quest1)}}
\if{NNN1 iswordof \name_quest1_1}{\text{name_quest1_1=wims(replace internal word NNN1 by \(\don[1]\) in \name_quest1_1)}}
\if{NNN1 iswordof \name_sol2}{\text{name_sol2=wims(replace internal word NNN1 by \(\don[1]\) in \name_sol2)}} 
#endif                   
#if defined TARGET_camion
\if{NNN3 iswordof \name_quest1}{\text{name_quest1=wims(replace internal word NNN3 by \(\don[3]\) in \name_quest1)}}
\if{NNN3 iswordof \name_quest1_1}{\text{name_quest1_1=wims(replace internal word NNN3 by \(\don[3]\) in \name_quest1_1)}}
\if{NNN3 iswordof \name_sol2}{\text{name_sol2=wims(replace internal word NNN3 by \(\don[3]\) in \name_sol2)}} 
\if{NNN3 iswordof \name_quest2}{\text{name_quest2=wims(replace internal word NNN3 by \(\don[3]\) in \name_quest2)}} 
#endif    

%%Type de réponse%%
\if{1 isitemof \confparm1 and 2 isitemof \confparm1}{\text{\confparm1=randint(2)}}
\text{aux=\listedon,+,-,\(\times\),\(\div\),&#40;,&#41;}                                
\text{list=\good,\bad}
\text{list=wims(nonempty item \list)}
\integer{nbprop=items(\list)}
\text{shf=shuffle(\nbprop)}
\text{propo=\list[\shf]}
#if defined TARGET_pile || defined TARGET_bonbon ||defined TARGET_chocolat || defined TARGET_lacourse || defined TARGET_pile || defined TARGET_prog1 || defined TARGET_camion
\text{rep=position(1,\shf)}
#endif
#if defined TARGET_randonnee | defined TARGET_librairie | defined TARGET_panini | defined TARGET_supermarche | defined TARGET_depense | defined TARGET_autobus
\text{rep=position(1,\shf),position(2,\shf)}
#endif                
#if defined TARGET_pomme
\text{rep=position(1,\shf),position(2,\shf),position(3,\shf)}
#endif
\text{r=\confparm1=1?r1,r3:r2,r3}
\steps{\r} 

\integer{truepick=items(\good)}
\text{ind=wims(makelist 1 for x=1 to \truepick),wims(makelist 0 for x=1 to \nbprop-\truepick)}
\text{ind=\ind[\shf]}

%%% Variables pour après statement%%%
\matrix{checked=}
\text{repons=}
\text{screply=}
\text{sigle=}
\integer{diffe2=0}

%%%STATEMENT%%%
                                 
\statement{
<div class="euler_quest">\name_text</div>

\if{\confparm1=1}{1. \name_quest1
                  <div class="\if{\diffe2=0}{euler_answer}\if{\diffe2=1}{euler_rep_good_nobg}\if{\diffe2=2}{euler_rep_bad_nobg}">
                       <div class="wims_instruction">\name_instruction</div>
                       \embed{r1,50x40x\nbrechar}
                  </div>
                 }
\if{\confparm1=2}{1. \name_quest1_1
                  <fieldset class="euler_field">
                    <div class="\if{\sc_reply2=}{euler_answer}\if{\sc_reply2=1}{euler_rep_good_nobg}\if{\sc_reply2=0}{euler_rep_bad_nobg}\if{\sc_reply2=0.5}{euler_rep_prec_nobg}">
                       <legend>\if{\sc_reply2=}{}{\reprise_rep}</legend>
                       <ul class="wims_nopuce euler_ul_check">
                         \for{h=1 to \nbprop}{
                           <li \if{\sc_reply2!=}{\if{\checked[\h]=1}{class="euler_box_checked"}{class="euler_box_nochecked"}}>
                               \embed{r2,\h,\(\propo[\h]\)}
                               \if{\sc_reply2!=}{<span class="\sigle[\h]"></span>}
                           </li>
                                             }
                      </ul>
                   </div>
                 </fieldset>
    }                              
2. \name_quest2
<div class="\if{\sc_reply3=}{euler_answer}\if{\sc_reply3=1}{euler_rep_good_nobg}\if{\sc_reply3=0}{euler_rep_bad_nobg}\if{\sc_reply3=0.5}{euler_rep_prec_nobg}">
    <label for="reply3">\name_sol2</label>
    \embed{r3,5} \name_unit
</div>  
}    
                       
\answer{\name_ans1}{\rep1;\aux}{type=clickfill}
\answer{\name_ans2}{\rep;\propo}{type=checkbox}{option=split}
\answer{\name_ans3}{\sol}{type=numeric}{option=comma}
\text{screply=\sc_reply2}
\text{repons=\reply2}
\text{checked=}
\text{sigle=}
\for {j=1 to \nbprop}
  {\if{\propo[\j] isitemof \repons}
    {\text{temp1=1}
     \if{\ind[\j]=1}
      {\text{temp2=oef_indgood tick}}
      {\text{temp2=oef_indbad cross}} 
    }
    {\text{temp1=0}
     \if{\ind[\j]=1}
      {\text{temp2=oef_indforget forget}}
      {\text{temp2=oef_indneutral}} 
    }
   \text{checked=wims(append item \temp1 to \checked)}
   \text{sigle=wims(append item \temp2 to \sigle)}
  }

%%%% Gestion des parenthèses dans la réponse de l'élève si confparm1=1%%
\if{\confparm1=1}{
                  \integer{nbrecharep=items(\rep1)}
                  \integer{test=\nbrecharep-\nbrechar/2}
                  \text{rep2=}
                  \for{s=1 to \nbrecharep}{\text{tempb=wims(replace &#44; by . in \rep1[\s])}
                                           \text{rep2=wims(append item \tempb to \rep2)}
                                           }
                  \text{parent=()}
                  \text{ouv=wims(char 1 of \parent)}
                  \text{ferm=wims(char 2 of \parent)}
                  \text{rep2=wims(replace internal &#41; by \ferm in \rep2)}
                  \text{rep2=wims(replace internal &#40; by \ouv in \rep2)}
                  \text{rep2=wims(replace internal , by  in \rep2)}
                  \text{rep2=wims(replace internal \(\times\) by * in \rep2)}
                  \text{rep2=wims(replace internal \(\div\) by / in \rep2)}
                  %%%Pour accepter le produit sans l'utilisation de *%%
                  \text{rep2=wims(rawmath \rep2)}
                  \real{evalrep=pari(\rep2)}
                  \real{diffe=\evalrep-\sol}
                  \integer{weigh=2}
                  \if{\diffe=0}{\integer{\diffe2=1}}{\integer{\diffe2=2}}}
\if{\confparm1=2}{\integer{weigh=0}
                  \text{hid=hide}}
                  
               
\condition{\name_cond}{\diffe=0}{weight=\weigh}{option=\hid}

#include "feedback.inc"
 
%%%Refuser certaines expressions trop courtes (inferieures à la moitie de la longueur de celle attendue)%%
\feedback{\test<0}{<p class="oef_condbad">\name_feed1</p>}

%%%Quelques feedback%%
\css{<style>
.feed{background-color: #fefbd8}
</style>}

#if defined TARGET_pile
\text{rep5=\don1,-,\don2,\(\div\),\don3}
\real{temp2=\don2/\don3}
\text{ttemp2=slib(numeration/ecriturenombre \temp2,comma)}
\real{temp3=\don1-\temp2}
\text{ttemp3=slib(numeration/ecriturenombre \temp3,comma)}
\feedback{\reply2 issametext \bad2}{<div class="feed">\name_feed</div>}
#endif
