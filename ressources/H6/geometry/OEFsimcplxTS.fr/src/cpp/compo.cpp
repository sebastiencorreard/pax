target=comporottr comporotrot
\email{regine@mangeard}
\author{Régine, Mangeard}
\language{fr}
\range{-5..5}
\computeanswer{yes}
\format{html}
\precision{100}

\text{lsta=0,1/6,1/4,1/3,1/2,2/3,3/4,5/6,1,-5/6,-3/4,-2/3,-1/2,-1/3,-1/4,-1/6}
\text{lstc=1,sqrt(3)/2,sqrt(2)/2,1/2,0,-1/2,-sqrt(2)/2,-sqrt(3)/2,-1,-sqrt(3)/2,-sqrt(2)/2,-1/2,0,1/2,sqrt(2)/2,sqrt(3)/2}
\text{lsts=0,1/2,sqrt(2)/2,sqrt(3)/2,0,sqrt(3)/2,sqrt(2)/2,1/2,0,-1/2,-sqrt(2)/2,-sqrt(3)/2,-1,-sqrt(3)/2,-sqrt(2)/2,-1/2}
\text{lsttc=1,\frac{\sqrt{3}}{2},\frac{\sqrt{2}}{2},\frac{1}{2},,-\frac{1}{2},-\frac{\sqrt{2}}{2},-\frac{\sqrt{3}}{2},-1,-\frac{\sqrt{3}}{2},-\frac{\sqrt{2}}{2},-\frac{1}{2},,\frac{1}{2},\frac{\sqrt{2}}{2},\frac{\sqrt{3}}{2}}
\text{lstts=0,\frac{1}{2},\frac{\sqrt{2}}{2},\frac{\sqrt{3}}{2},1,\frac{\sqrt{3}}{2},\frac{\sqrt{2}}{2},\frac{1}{2},0,-\frac{1}{2},-\frac{\sqrt{2}}{2},-\frac{\sqrt{3}}{2},-1,-\frac{\sqrt{3}}{2},-\frac{\sqrt{2}}{2},-\frac{1}{2}}
%%
a pour sqrt(2)/2
b pour sqrt(3)/2
\text{Lstc=1,b/2,a/2,1/2,0,-1/2,-a/2,-b/2,-1,-b/2,-a/2,-1/2,0,1/2,a/2,b/2}
\text{Lsts=0,1/2,a/2,b/2,1,b/2,a/2,1/2,0,-1/2,-a/2,-b/2,-1,-b/2,-a/2,-1/2}

\text{angcor=1,1
2,4, 16,1, 4,5, 14,16, 5,6, 13,14, 6,8, 12,13, 8,9, 10,12
3,5, 15,1, 5,7, 13,15, 7,9, 11,13
4,6, 14,1, 2,5, 16,2, 5,8, 13,16
5,9, 13,1, 3,7, 15,3, 4,8, 14,2
6,12, 12,1, 2,8, 16,5, 4,9, 14,4
7,13, 11,1, 3,9, 15,5, 5,14, 13,3
8,14, 10,1, 2,4, 16,6, 4,10, 14,5
}


#if defined TARGET_comporottr
\title{Composée de translation et rotation}
\author{Régine, Mangeard}
inspiré par Hélène Brion, Véronique Royer


/*** Centre, angle de la rotation et expression complexe de la rotation***/
%% choix d'un angle
\integer{ia=randint(2..items(\lsta))}
\integer{ia=randint(2..8)}
%% choix d'un centre qui va bien avec cet angle
\text{cecor=row(\ia,\angcor)}
\integer{icor=randint(1..items(\cecor)/2)}
\integer{angw=\cecor[2*\icor-1]}
\integer{angu=\cecor[2*\icor]}
\integer{mw=randint(1..3)}
\text{wx=maxima(\mw*(\Lstc[\angw]))}
\text{wy=maxima(\mw*(\Lsts[\angw]))}
\integer{mu=randint(-3..3)}
\text{ux=maxima(\mw*\Lstc[\angu]+\mu)}
\text{uy=maxima(\mw*\Lsts[\angu])}

\complex{W=\wx+i*(\wy)}
\complex{U=\ux+i*(\uy)}

\rational{ang=\lsta[\ia]}
\text{tangle=texmath(maxima(\ang*x))}
\text{tangle=wims(replace internal x by \pi in \tangle)}
\complex{z2=\W}
\complex{z1=\U}


\complex{A=\Lstc[\ia]+i*(\Lsts[\ia])}
\complex{Abar=\Lstc[\ia]-i*(\Lsts[\ia])}
\complex{B=simplify((\z2)*(1-(\A)))}
/***Selon la version, z'=Az+C est l'expression complexe de rot ou tor nommée f***/
\integer{version=randitem(1,2)}
\if {\version = 1} {\complex{C= simplify((\A)*(\z1)+(\B))}
        \text{f=r \circ t}}
\if {\version = 2} {\complex{C= simplify(\z1+(\B))}
        \text{f=t \circ r}}
/*** Calcul de I affixe du point invariant ***/
\complex{I=simplify((\C)*(1-(\Abar))/(2-2*(\Lstc[\ia])))}
complex{I=simplify(\W+(\U)*(1-(\Lstc[\ia])+i*(\Lsts[\ia])))} ancienne version ??

\text{A=wims(replace a by sqrt(2) in \A)}
\text{A=wims(replace b by sqrt(3) in \A)}
\text{B=wims(replace a^2 by 2 in \B)}
\text{B=wims(replace b^2 by 3 in \B)}
\complex{B=simplify(maxima(\B))}
\text{B=wims(replace a by sqrt(2) in \B)}
\text{B=wims(replace b by sqrt(3) in \B)}
\text{C=wims(replace a^2 by 2 in \C)}
\text{C=wims(replace b^2 by 3 in \C)}
\complex{C=simplify(maxima(\C))}
\text{C=wims(replace a by sqrt(2) in \C)}
\text{C=wims(replace b by sqrt(3) in \C)}
\text{W=wims(replace a by sqrt(2) in \W)}
\text{W=wims(replace b by sqrt(3) in \W)}
\text{U=wims(replace a by sqrt(2) in \U)}
\text{U=wims(replace b by sqrt(3) in \U)}

\text{I=wims(replace a^2 by 2 in \I)}
\text{I=wims(replace b^2 by 3 in \I)}
\text{I=wims(replace b^3 by 3*b in \I)}
\text{I=wims(replace a^3 by 2*a in \I)}
\complex{I=simplify(maxima(\I))}
\text{I=wims(replace a by sqrt(2) in \I)}
\text{I=wims(replace b by sqrt(3) in \I)}

\text{indication= , , , L'affixe du point invariant vérifie l'équation : \(z_I = (\A)z_I+\C), }
/*** Exercice en 5 étapes (translation, homothétie, composée, point invariant, vérification)***/
\steps{reply 1
reply 2, reply 3
reply 4, reply 5
reply 6
reply 7, reply 8
}
\statement{<p>
Cet exercice est en cinq étapes. On considère successivement plusieurs
transformations du plan complexe dont on va déterminer l'écriture complexe.
 </p>
<ul>
<li>Soit \(t) la translation de vecteur \(u(\U)).<br>
Donner l'écriture complexe de la translation \(t) : <br>
\(z' = z + ) \embed{reply1, 20}
\if{\step>1}{<div class="wimscenter">
        \if{\sc_reply1=1}
         {<span class="oef_indgood"> Bonne réponse !}
         {<span class="oef_indbad"> Mauvaise réponse...}
        L'écriture complexe de \(t) est \( z'  = z + \U).</span></div>
</li><li>
        Donner l'écriture complexe de la rotation \(r) de centre
        \(C(\W)) et d'angle \(\tangle) : <br>
        \(z' = ) \embed{reply2, 20}\(z ) + \embed{reply3, 20}
        }
\if{\step>2}{<div class="wimscenter">
        \if{\sc_reply2=1 and \sc_reply3=1}
         {<span class="oef_indgood"> Bonne réponse !}
         {<span class="oef_indbad"> Mauvaise réponse...}
        L'écriture complexe de \(r\) est \(z' = (\A)z + \B). </span></div>
</li><li>
        On considère maintenant la composée \(f = \f).
        Donner l'écriture complexe de la transformation \(f) :<br>
        \(z' = ) \embed{reply4, 20}\(z )+ \embed{reply5, 20}
        }
\if{\step>3}{<div class="wimscenter">
        \if{\sc_reply4=1 and \sc_reply5=1}
         {<span class="oef_indgood"> Bonne réponse !}
         {<span class="oef_indbad"> Mauvaise réponse...}
        L'écriture complexe de \(f) est \( z' = (\A)z + \C) .</span></div>
</li><li>
        Rechercher l'affixe du point \(I) invariant par \(f). <br>
        \(z_I = )\embed{reply6, 20}
        }
\if{\step>4}{<div class="wimscenter">
        \if{\sc_reply6=1}
         {<span class="oef_indgood"> Bonne réponse !}
         {<span class="oef_indbad"> Mauvaise réponse...}
         On a \(z_I) = \(\I) .</span></div>
</li><li>
  Donner l'écriture complexe de la rotation de centre I et d'angle \(\tangle).<br>
        \(z' = ) \embed{reply7, 20}\(z) + \embed{reply8, 20}
        }
</li></ul>
}
\answer{tranlation}{\U}{type=complex}{option=nonstop}
\answer{ coeffr}{\A}{type=complex}{option=nonstop}
\answer{ constr}{\B}{type=complex}{option=nonstop}
\answer{ coeff}{\A}{type=complex}{option=nonstop}
\answer{ constf}{\C}{type=complex}{option=nonstop}
\answer{ zI}{\I}{type=complex}{option=nonstop}
\help{\indication[\step]}
\answer{ coeff1}{\A}{type=complex}
\answer{ constf1}{\C}{type=complex}
#endif

#if defined TARGET_comporotrot
\title{Composée de rotations}
\author{Régine, Mangeard}
inspiré par Hélène Brion, Véronique Royer


/*** Centre, angle de la rotation et expression complexe de la rotation***/
%% choix d'un angle
\integer{ia=randint(2..items(\lsta))}
\integer{ia=randint(2..8)}
\integer{angma=18-\ia}
%% choix d'un centre qui va bien avec cet angle
\text{cecor=row(\ia,\angcor)}
\integer{icor=randint(1..items(\cecor)/4)}
\integer{angb=\cecor[4*\icor-3]}
\integer{angapb=\cecor[4*\icor-2]}
\integer{angmb=\cecor[4*\icor-1]}
\integer{angamb=\cecor[4*\icor]}

\integer{mw=randint(1..3)}
\text{wx=maxima(\mw*\Lstc[\angma])}
\text{wy=maxima(\mw*\Lsts[\angma])}
\integer{mu=randint(-3..3)}
\text{ux=maxima(\mu*\Lstc[\angb])}
\text{uy=maxima(\mu*\Lsts[\angb])}

\complex{W=\wx+i*\wy}
\complex{U=\ux+i*\uy}

\rational{ang=\lsta[\ia]}
\rational{ang=\lsta[\angmb]}
\text{tangle=texmath(maxima(\ang*x))}
\text{tangle=wims(replace internal x by \pi in \tangle)}
\rational{ang2=\lsta[\ia]}
\text{tangle2=texmath(maxima(\ang2*x))}
\text{tangle2=wims(replace internal x by \pi in \tangle2)}
\text{tangled=texmath(maxima(\angamb*x))}
\text{tangled=wims(replace internal x by \pi in \tangled)}
\complex{z2=\W}
\complex{z1=\U}


\complex{A=\Lstc[\angmb]+i*(\Lsts[\angmb])}
\complex{Abar=\Lstc[\angmb]-i*(\Lsts[\angmb])}
\complex{B=simplify((\W)*(1-(\A)))}
\complex{A2=\Lstc[\ia]+i*(\Lsts[\ia])}
\complex{A2bar=\Lstc[\ia]-i*(\Lsts[\ia])}
\complex{B2=simplify((\U)*(1-(\A2)))}
\complex{A3=\Lstc[\angamb]+i*(\Lsts[\angamb])}
\complex{A3bar=\Lstc[\angamb]-i*(\Lsts[\angamb])}

/***Selon la version, z'=Az+C est l'expression complexe de rot ou tor nommée f***/
\integer{version=randitem(1,2)}
\if {\version = 1}
 {\complex{C= simplify(\mu*(1-(\Lstc[\ia])-i*(\Lsts[\ia]))+\mw*(\Lstc[\angma]-(\Lstc[\angapb])+i*(\Lsts[\angma]+(\Lsts[\angapb]))))}
        \text{f=r_1 \circ r_2}}
\if {\version = 2}
  {\complex{C= simplify(\mw*(1-(\Lstc[\angmb])-i*(\Lsts[\angmb]))+\mu*(\Lstc[\angb]-(\Lstc[\angapb])+i*(\Lsts[\angb]-(\Lsts[\angapb]))))}
       \text{f=r_2 \circ r_1}}

\text{A=wims(replace a by sqrt(2) in \A)}
\text{A=wims(replace b by sqrt(3) in \A)}

\text{B=wims(replace a^2 by 2 in \B)}
\text{B=wims(replace b^2 by 3 in \B)}
\complex{B=simplify(maxima(\B))}
\text{B=wims(replace a by sqrt(2) in \B)}
\text{B=wims(replace b by sqrt(3) in \B)}

\text{A2=wims(replace a by sqrt(2) in \A2)}
\text{A2=wims(replace b by sqrt(3) in \A2)}

\text{A3=wims(replace a by sqrt(2) in \A3)}
\text{A3=wims(replace b by sqrt(3) in \A3)}

\text{B2=wims(replace a^2 by 2 in \B2)}
\text{B2=wims(replace b^2 by 3 in \B2)}
\complex{B2=simplify(maxima(\B2))}
\text{B2=wims(replace a by sqrt(2) in \B2)}
\text{B2=wims(replace b by sqrt(3) in \B2)}

\text{C=wims(replace a^2 by 2 in \C)}
\text{C=wims(replace b^2 by 3 in \C)}
\complex{C=simplify(maxima(\C))}
\text{C=wims(replace a by sqrt(2) in \C)}
\text{C=wims(replace b by sqrt(3) in \C)}

\text{W=wims(replace a by sqrt(2) in \W)}
\text{W=wims(replace b by sqrt(3) in \W)}

\text{U=wims(replace a by sqrt(2) in \U)}
\text{U=wims(replace b by sqrt(3) in \U)}

/*** Exercice en 5 étapes (translation, homothétie, composée, point invariant, vérification)***/
\steps{reply 1, reply2
reply 3, reply 4
reply 5, reply 6
}
\statement{<p>
Cet exercice est en trois étapes. On considère successivement plusieurs transformations
du plan complexe, dont on va déterminer l'écriture complexe.
 </p>
<ul>
<li>Soit \(r_1) la rotation de centre
        \(W(\W)) et d'angle \(\tangle) : <br>
Donner l'écriture complexe de la rotation \(r_1) : <br>
        \(z' = ) \embed{reply1, 20}\(z ) + \embed{reply2, 20}.
\if{\step>1}{<div class="wimscenter">
        \if{\sc_reply1=1 and \sc_reply2=1}
         {<span class="oef_indgood"> Bonne réponse !}
         {<span class="oef_indbad"> Mauvaise réponse...}
        L'écriture complexe de \( r_1\) est \(z' = (\A)z + \B). </span></div>
</li><li>
        Donner l'écriture complexe de la rotation \(r_2) de centre
        \(U(\U)) et d'angle \(\tangle2) : <br>
        \(z' = ) \embed{reply3, 20}\(z ) + \embed{reply4, 20}.
        }
\if{\step>2}{<div class="wimscenter">
        \if{\sc_reply3=1 and \sc_reply4=1}
         {<span class="oef_indgood"> Bonne réponse !}
         {<span class="oef_indbad"> Mauvaise réponse...}
         L'écriture complexe de \( r_2) est \(z' = (\A2)z + \B2). </span></div>
</li><li>
        On considère maintenant la composée \(f = \f).
        Donner l'écriture complexe de la transformation \(f) :<br>
        \(z' = ) \embed{reply5, 20}\(z )+ \embed{reply6, 20}
        }
</li></ul>
}
\answer{ coeffr1}{\A}{type=complex}{option=nonstop}
\answer{ constr1}{\B}{type=complex}{option=nonstop}
\answer{ coeffr2}{\A2}{type=complex}{option=nonstop}
\answer{ constr2}{\B2}{type=complex}{option=nonstop}
\answer{ coeff}{\A3}{type=complex}{option=nonstop}
\answer{ constf}{\C}{type=complex}{option=nonstop}
#endif



\help{
<p>Soit \(f) une transformation du plan complexe. Soit \(M(z)) un point
du plan complexe et \(M'(z')) son image par \(f) (\(f : M \mapsto M')). <br>
L'<i>écriture complexe</i> ou <i>expression complexe</i>
de \(f) est la relation qui permet d'exprimer \(z') en fonction de \(z).
</p><p>
Pour déterminer cette relation (si l'on  n'a pas mémorisé les formules du cours !),
on part d'une condition géométrique définissant le point \(M') en fonction du point \(M)
et on passe aux affixes complexes.
</p>
<table class="wimsborder">
<tr><th>Nature de \(f) </th><th>Condition géométrique </th><th>Traduction complexe </th></tr>
<tr><td>Translation de vecteur \(\vec{u})( a ; b) </td>
    <td> \(\vec{M M'} = \vec{u} )</td>
     <td> \( z' - z = a + i b )</td>
</tr>
<tr><td> Homothétie de centre \(\Omega(\omega)) et de rapport \(k) </td>
    <td> \(\vec{\Omega M'} = k \vec{\Omega M} )</td>
   <td> \( z' - \omega = k(z - \omega))</td>
</tr>
<tr><td> Rotation de centre \(\Omega(\omega)) et d'angle \(\theta) </td>
    <td> \(\Omega M' = \Omega M ) et &nbsp;\((\vec{\Omega M} , \vec{\Omega M'}) = \theta \quad [2\pi] )</td>
    <td> \( z' - \omega = e^{i\theta}(z - \omega))</td>
</tr>
</table>}
