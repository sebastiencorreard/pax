\matrix{reee=wims(declosing \re[1;3])}
\real{xxxw=\reee[\nzero]}
\text{codeee=
\#Initialisation des variables\#
x=\xi_alg
a=\pas_alg
xm=\xm_alg
\#Définition d'une fonction\#
def f(x):
  return \fct_alg
\#Initialisation des listes\#
x_list=[]
y_list=[]
\#Boucle afin de construire les listes\#
while x<=xm:
  y=f(x)
  x_list.append(x)
  y_list.append(y)
  x=x+a
\#Affichage du terme des listes proche de zéro\#
print(x_list[\nzero-1])
print(y_list[\nzero-1])}
\text{CC=slib(coding/runcode [python,[\codeee]],id4,init,Jouer le code !)}
\feedback{abs(\yl[\nzero])<10^(-9) and \xxxw<0}{<div class="enonce">Votre réponse est
  évaluée comme partiellement bonne. Zoomer sur le  point du graphique qui se trouve à
  l'intersection de l'axe des abscisses et de la courbe. Constater que le point n'est pas de
  la bonne couleur. L'instruction conditionnelle <code>if else</code> est donc à durcir. En effet la
  construction des nombres sous Python ne permet pas d'évaluer correctement l'inégalité
  <code>y_list[n] \colorin 0</code>. Si on exécute le code ci-dessous qui renvoie
  les coordonnées du point proche de zéro, on comprend la problématique.
  <div>\CC</div></div>}
