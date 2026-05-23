target= redfrac,critere1,critere2

\language{fr}
\range{-5..5}
\author{Fabrice, Guerimand}
\email{fwguerima@free.fr}
\computeanswer{no}
\format{html}
\precision{100}

#if defined TARGET_redfrac
 \title{Réduction fractions}
 \integer{a=random(1..50)}
 \integer{b=random(10..35)}
 \integer{c=random(10..35)}
 \integer{c=\c=\b?36}
 \hint{Calculer le pgcd de \A et \B.}
#endif

#if defined TARGET_critere1 |defined TARGET_critere2
# if defined TARGET_critere1
  \title{Critères de divisibilité 1}
  \integer{a=randitem(2,3,5,9,10)}
# else
  \title{Critères de divisibilité 2}
  \integer{a=randitem(2,3,5,9,10)*randitem(1,2,3,5,9,10)*randitem(2,3,5,10)}
# endif
 \text{complement=Utiliser les critères de divisibilité.}
 \integer{b=random(10..35)}
 \integer{c=random(10..35)}
 \integer{c=\c=\b?36}
 \integer{g=maxima(GCD(\b,\c);)}
 \integer{b=\b/\g}
 \integer{c=\c/\g}
 \if{\c=1}{
  \integer{b=2}
  \integer{c=3}
 }
 \hint{Une fraction est dite irréductible lorsque elle est simplifiée au maximum, c'est-à-dire lorsque le seul diviseur commun à son numérateur et son dénominateur est 1.}
#endif

\integer{A=\a*\b}
\integer{B=\a*\c}
\integer{p=maxima(GCD(\A,\B);)}
\integer{Ar=\A/\p}
\integer{Br=\B/\p}

\statement{
  Quelle est l'écriture irréductible de la fraction \(\frac{\A}{\B}) ?
\if{\complement!=}{
<div class="wims_instruction">\complement</div>
}{
<br>}
<b>Votre réponse :</b>
<table class="wimscenter">
 <tr>
    <td>\(\A)</td>
    <td></td>
    <td>\embed{reply 1,3}</td>
 </tr>
 <tr>
    <td><hr></td>
    <td>=</td>
    <td><hr></td>
 </tr>
 <tr>
    <td>\(\B)</td>
    <td></td>
    <td>\embed{reply 2,3}</td>
 </tr>
</table>
}

\answer{numérateur}{\Ar}{type=numexp}
\answer{dénominateur}{\Br}{type=numexp}
