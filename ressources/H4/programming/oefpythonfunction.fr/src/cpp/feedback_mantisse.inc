\text{xi_alg=\xi}
\text{pas_alg=\pas}
\text{xm_alg=\xm}
\text{fct_alggg=wims(replace t by x in \fct_pari)}
\text{fct_alg=wims(replace \^ by ** in \fct_alggg)}

\text{codee=
\#Initialisation des variables#
x=\xi_alg
a=\pas_alg
xm=\xm_alg

\#Définition d'une fonction#
def f(x):
  return \fct_alg

\#Initialisation des listes#
x_list=[]
y_list=[]
\#Boucle afin de construire les listes#
while x<=xm:
  y=f(x)
  x_list.append(x)
  y_list.append(y)
  x=x+a
\#Affichage les 3 derniers termes des listes#
print(x_list[-3\:])
print(y_list[-3\:])}

\text{BB=slib(runcode [python,[\codee]],id3,init,Jouer le code !)}
\matrix{re=\reply1}
\matrix{ree=wims(declosing \re[1;2])}
\real{xxxw=\xl[\nx]}

\feedback{\ree[\nx]== }{<div class="enonce">Votre réponse est évaluée
  comme étant fausse car c'est effectivement le cas. Néanmoins la note reste excellente car
  les notions abordées dépassent le référentiel de seconde. Les conditions sur
  la boucle While sont à durcir. En effet la construction des nombres sous Python ne permet
  pas d'évaluer correctement l'inégalité <code>While x&#60;=xm :</code>. Si on exécute le code
  ci-dessous qui renvoit les 3 dernières valeurs du tableau alors on constate que la prochaine
  itération n'est pas possible. En effet la valeur de \(\text{x + a}\) dépasse \(\text{xm}\)
  donc l'algorithme s'arrête. Afin de remédier à cette problématique, on peut rajouter
  une condition supplémentaire
  <code>While x&#60;xm or abs(x-xm)&#60;=0.0001:</code>.
  <div>
  \BB
  </div>
  <div class="solution"> Cette condition d'arrêt de l'algorithme qui est mal écrite n'a pas
  d'importance dans l'exemple abordé. Néanmoins il faut avoir conscience que des programmes
  mal codés peuvent avoir des conséquences désastreuses. Deux exemples qui matérialisent
  ces erreurs de programmation extraits du rapport de recherche "Arithmétique flottante" sont :
  <ul><li> L'importance du traitement des exceptions est parfaitement illustré par le crash du vol
  501 d'Ariane en 1996, qui a coûté quelques 500 millions de dollars.</li>
  <li>L'importance de l'arrondi est illustré par l'échec du missile Patriot en 1991. Pendant
  la guerre du Golfe, un anti-missile Patriot tiré de Dahran (Arabie Saoudite) ayant manqué
  l'interception d'un missile irakien Scud, ce dernier a tué 28 soldats et blessé quelques 100
  autres personnes.</li></ul>
  </div>
  </div>
}
