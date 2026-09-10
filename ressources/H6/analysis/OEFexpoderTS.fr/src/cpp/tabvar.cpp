target=tabvar1 tabvar2
\language{fr}
\range{-5..5}
\author{Régine,Mangeard}
%%% la résolution du zéro demande de connaitre le logarithme
%%% c'est pourquoi je l'ai retiré!
\email{regine@mangeard.fr}
\computeanswer{yes}
\format{html}
\precision{100}

\text{etiquette=40x35}
#if defined TARGET_tabvar1
\title{Tableau de variations avec exp 1}
\integer{B = random(-1,1)}
\integer{C = random(-1,1)}
\integer{b = \B * random(1..4)}
\integer{c = \C * random(1..4)}
\integer{a = random(-(\b)*(\c), 0 , \B*\C*random(1..6), \B*\C*random(-6..-1) ,\B*\C*random(-6..-1))}
\integer{k = random(-6..6)}

\integer{\nbcol= \a*\b*\c < 0 ? 2 : 1}
\text{etapes= reply3,reply4}
\text{etapes= \nbcol >1 ? \etapes,reply5,reply6 : \etapes}
\steps{reply1,reply2
\etapes}

\text{zero= \nbcol =2 ? ln(-(\a)/(\b * \c))/\c:}
\text{zero = simplify(\zero)}
\text{zero=wims(replace internal log by ln in \zero)}
\function{f= pari(\a *x + \k )+ \b* e^(\c*x)}
\text{ft=texmath(\f)}
\function{d=diff(\f,x)}
\text{dt=texmath(\d)}

\text{inf= - \infty}
\text{sup= + \infty}


\text{fz=evalue(\f,x=\zero)}
\text{fz=simplify(\fz)}
\text{fz=wims(replace internal log by ln in \fz)}


\text{signes= + , - }
\text{variations = \(\nearrow),\(\searrow)}


***par colonnes : 1 pour croissant, 2 pour décroissant

\text{cc= \B < 0 ? 1,2 : 2,1}
\text{cc= \nbcol = 1 ? (3-\B*\C)/2}
\text{s=\signes[\cc]}
\text{v=\variations[\cc]}



\statement{<p>
  Soit \(f) la fonction définie par \(f(x) = \ft).
</p>
\if{\step=1}{Calculer \(f'(x)). <div>\(f'(x) = )\embed{reply1}</div>
<div>Combien y a-t-il de valeurs dans \(\rbrack \inf ; \sup \lbrack) annulant \(f'(x)) ? \embed{reply2}</div>}
\if{\step=2}{Vous avez trouvé que sa dérivée est : \(f'(x) = \dt).
\if{\nbcol>1}
{<p>On note \(\displaystyle{\alpha}\) l'unique réel annulant \(f'(x)).</p>}
  Compléter le tableau de variation de \(f).
<table class="wimsborder wimscenter" style="width:70%">
<tr>
<td style="width:10%">\(x)</td>
<td  style="width:5%;text-align:left">\(\inf)</td>
<td width="25%"></td>
\if{\nbcol>1}{<td  style="width:5%">\(\displaystyle{\alpha}\)</td>
<td width="25%"></td>
}
<td style="width:5%;text-align:right">\(\sup)</td>
</tr><tr>
<td>\(f'(x))</td><td></td><td>\embed{reply3,\etiquette}</td>
\if{\nbcol>1}{<td>0</td><td>\embed{reply5,\etiquette}</td>}
<td></td>
</tr><tr>
<td>\(f(x))</td><td style="text-align:left"></td><td>\embed{reply4,\etiquette}</td>
\if{\nbcol>1}{<td>\(f(\alpha))</td><td>\embed{reply6,\etiquette} </td>}
<td style="text-align:right"></td>
</tr>
</table>}
}

\answer{}{\d}{type=formal}
\answer{}{\nbcol ; 0,1,2,3,autre}{type=menu}
\answer{}{\s[1];\variations,\signes}{type=clickfill}
\answer{}{\v[1] }{type=clickfill}
\answer{}{\s[2] }{type=clickfill}
\answer{}{\v[2] }{type=clickfill}



\text{err1 = vous avez trouvé que la dérivée \(f'(x)) est négative ; vous devriez donc dire que la fonction \(f) est décroissante sur cet intervalle.}
\text{err2 = vous avez trouvé que la dérivée \(f'(x)) est positive ; vous devriez donc dire que la fonction \(f) est croissante sur cet intervalle.}

\feedback{\reply3 isitemof \variations or \reply7 isitemof \variations}{Pour obtenir les variations de \(f), on indique le SIGNE de la dérivée \(f'(x)).}
\feedback{\reply4 isitemof \signes or \reply8 isitemof \signes }{Ce sont les VARIATIONS de la fonction \(f) qu'on cherche, et pas son signe.}
\feedback{\reply3 isitemof - and \reply4 isitemof \(\nearrow)}{Incohérence dans la première colonne du tableau : \err1}
\feedback{\reply3 isitemof + and \reply4 isitemof \(\searrow)}{Incohérence dans la première colonne du tableau : \err2}
\feedback{\reply7 isitemof - and \reply8 isitemof \(\nearrow)}{Incohérence dans la deuxième colonne du tableau : \err1}
\feedback{\reply7 isitemof + and \reply8 isitemof \(\searrow)}{Incohérence dans la deuxième colonne du tableau : \err2}

\solution{\(f'(x) = \dt). <br>Cette dérivée
\if{\nbcol=1}{ ne s'annule pas.}
\if{\nbcol=2}{ s'annule une fois : pour \(x = \zero).}<br>On en déduit le tableau de variations de \(f) :
<table class="wimscenter wimsborder" style="width:70%;">
<tr>
<td style="width:10%">\(x)</td><td style="width:5%;text-align:left">\(\inf)</td>
<td style="width:25%;"></td>
\if{\nbcol>1}{
<td style="width:5%">\zero</td><td style="width:25%;" ></td>}
<td style="width:5%;text-align:right">\(\sup)</td>
</tr>
<tr>
<td>\(f'(x))</td><td></td><td>\s[1] </td>
\if{\nbcol>1}{<td>0</td><td>\s[2] </td>}
<td></td>
</tr>
<tr>
<td>\(f(x))</td><td></td><td>\v[1] </td>
\if{\nbcol>1}{<td>\fz</td><td>\v[2] </td>}
<td></td>
</tr>
</table>}
#endif

#if defined TARGET_tabvar2
\title{Tableau de variations avec exp 2}
\integer{singa=randint(1..5)*randint(1,-1)}
\integer{singb=randint(1..5)*randint(1,-1)}
\integer{sing1=\singa<\singb?\singa:\singb}
\integer{sing2=\singa<\singb?\singb:\singa}

integer{sing2=\sing1}
\integer{k=randint(1..3)*randint(1,-1)}
\integer{d=randint(-5..5)}
\integer{s=\sing1+\sing2}
\integer{p=\sing1*\sing2}

\rational{b=simplify(-\s-2/\k)}
\rational{c=simplify(\p-\b/\k)}

\text{u=texmath(maxima(\k*x+\d))}
\text{v=texmath(maxima(x^2+\b*x+\c))}


\integer{\nbcol= \sing1=\sing2 ? 2 : 3}
\text{etapes= reply3,reply4,reply5,reply6,reply7,reply8}
\text{etapes= \nbcol >2 ? \etapes,reply9,reply10,reply11,reply12 : \etapes}
\steps{reply1,reply2
\etapes}

\function{f= (x^2+\b*x + \c )* exp(\k*x+\d)}
\text{ft=(\v)e^{\u}}
\function{fder=diff(\f,x)}
\function{fder=maxima(factor(\fder))}
\text{dt=(texmath(maxima((\k*x^2+(\k*\b+2)*x+\k*\c+\b))))e^{\u}}

\text{inf= - \infty}
\text{sup= + \infty}


\text{fs1=evalue(\f,x=\sing1)}
\text{fs1=simplify(\fs1)}
\text{fs2=evalue(\f,x=\sing2)}
\text{fs2=simplify(\fs2)}


\text{signes= + , - }
\text{variations = \(\nearrow),\(\searrow)}

\if{\sing1=\sing2}
{
***par colonnes : 1 pour croissant, 2 pour décroissant

\text{cc= \k > 0 ? 1,1 : 2,2}
}
{
\text{cc= \k > 0 ? 1,2,1 : 2,1,2}
}
\text{s=\signes[\cc]}
\text{v=\variations[\cc]}
\text{dersigne=\k<0?négatif:positif}


\statement{<p>
  Soit \(f) la fonction définie par \(f(x) = \ft).
</p>

\if{\step=1}{<p>Calculer \(f'(x)). </p>
<div>\(f'(x)=)\embed{reply1}</div>
<div class="wims_instruction"> Taper e^(...) pour \(e^{...}).</div>
<p>Combien y a-t-il de valeurs dans \(\rbrack \inf ; \sup \lbrack)annulant \(f'(x)) ? \embed{reply2}
</p>}

\if{\step=2}{Vous avez trouvé que sa dérivée est : \(f'(x) = \dt).
  Compléter le tableau de variation de \(f).
  <div class="wims_instruction">Indiquer la valeur exacte de x. Pour f(x),
  indiquer la valeur exacte en tapant e^(...) pour \(e^{...}).</div>
<table class="wimsborder wimscenter">
<tr>
<td style="width:10%">\(x)</td>
<td style="width:5%;text-align:left">\(-\infty)</td>
<td style="width:25%;"></td>
<td style="width:5%">\embed{reply3,4}</td>
<td style="width:25%;"></td>
\if{\nbcol>2}{<td style="width:5%">\embed{reply9,4}</td><td style="width:25%;"></td>
}
<td style="width:5%;text-align:right">\(+\infty)</td>
</tr>
<tr>
<td>\(f'(x))</td>
<td></td>
<td>\embed{reply4,\etiquette} </td>
<td>0</td>
<td>\embed{reply6,\etiquette} </td>
\if{\nbcol>2}{<td>0</td><td>\embed{reply10,\etiquette} </td>}
<td></td>
</tr>
<tr>
<td>\(f(x))</td>
<td style="text-align:left"></td>
<td>\embed{reply5,\etiquette} </td>
<td>\embed{reply7,4}</td>
<td>\embed{reply8,\etiquette} </td>
\if{\nbcol>2}{<td>\embed{reply11,4}</td><td>\embed{reply12,\etiquette} </td>}
<td style="text-align:right"></td>
</tr>
</table>
}
}

\answer{}{\fder}{type=formal}
\answer{}{\nbcol ; 0,1,2,3,autre}{type=menu}
\answer{Singularité}{\sing1}{type=numeric}
\answer{}{\s[1];\variations,\signes}{type=clickfill}
\answer{}{\v[1] }{type=clickfill}
\answer{}{\s[2] }{type=clickfill}
\answer{}{\fs1}{type=numeric}
\answer{}{\v[2] }{type=clickfill}
\answer{Singularité 2}{\sing2}{type=numeric}
\answer{}{\s[3];\variations,\signes}{type=clickfill}
\answer{}{\fs2}{type=numeric}
\answer{}{\v[3] }{type=clickfill}


\text{err1 = vous avez trouvé que la dérivée \(f'(x)) est négative ; vous devriez donc dire que la fonction \(f) est décroissante sur cet intervalle.}
\text{err2 = vous avez trouvé que la dérivée \(f'(x)) est positive ; vous devriez donc dire que la fonction \(f) est croissante sur cet intervalle.}

\feedback{\reply4 isitemof \variations or \reply6 isitemof \variations or \reply10 isitemof \variations }{Pour obtenir les variations de \(f), on indique le SIGNE de la dérivée \(f'(x)).}
\feedback{\reply5 isitemof \signes or \reply8 isitemof \signes or \reply12 isitemof \signes }{Ce sont les VARIATIONS de la fonction \(f(x)) qu'on cherche, et pas son signe.}
\feedback{\reply4 isitemof - and \reply5 isitemof \(\nearrow)}{Incohérence dans la première colonne du tableau : \err1}
\feedback{\reply4 isitemof + and \reply5 isitemof \(\searrow)}{Incohérence dans la première colonne du tableau : \err2}
\feedback{\reply6 isitemof - and \reply8 isitemof \(\nearrow)}{Incohérence dans la deuxième colonne du tableau : \err1}
\feedback{\reply6 isitemof + and \reply8 isitemof \(\searrow)}{Incohérence dans la deuxième colonne du tableau : \err2}
\feedback{\reply10 isitemof - and \reply12 isitemof \(\nearrow)}{Incohérence dans la troisième colonne du tableau : \err1}
\feedback{\reply10 isitemof + and \reply12 isitemof \(\searrow)}{Incohérence dans la troisième colonne du tableau : \err2}

\solution{\(f'(x) = \dt). <br>Cette dérivée
\if{\nbcol=2}{ s'annule pas une fois pour \(x=\sing1) et la dérivée est de signe constant, \dersigne.}
\if{\nbcol=3}{ s'annule deux fois : pour \(x = \sing1) et pour \(x=\sing2) et la dérivée est de signe \dersigne à l'extérieur des racines.}<br>
  On en déduit le tableau de variations de \(f).
}

#endif
