\observation{Dans cet exercice, il est demandé d'extraire la racine carrée d'un nombre.
<br>L'élève doit coder un programme du type "tant que a est supérieur à 0, on lui retire
 un nombre impair".}

\title{Extraire une racine carrée entière}
\text{prob=Utiliser une propriété mathématique pour écrire un script}
\text{instruction=On cherche à extraire la racine carrée entière d'un nombre entier lorsqu'elle
 existe. Pour écrire le script, on utilise la propriété mathématique sur
 la somme des nombres impairs de 1 à \(N\) dont le résultat est toujours un carré.
<br> <strong>Exemples :</strong>
<ul><li>\(1+3=4=2^2\)</li>
<li>\(1+3+5=9=3^2\)</li>
<li>\(1+3+5+7=16=4^2\)</li>
<li>\(1+3+5+7+9=25=5^2\)</li>
<li>...</li>
<li>\(1+3+5+...+(2n-1)={\displaystyle \sum_{i=0}^{n-1} (2i+1)}=n^2\)</li>
</ul>
Cette propriété s'illustre grâce à la figure proposée :
<div class="wimscenter">
<img src="\imagedir/rc.jpg" alt="Figure illustrant la propriété">
<figcaption>
<cite><a href="http://villemin.gerard.free.fr/aNombre/FIGURE/Carre.htm#impair" target="_blank">Gérard Villemin</a></cite>
</figcaption>

</div>
On va donc soustraire les différents nombres impairs au nombre de départ. Le nombre de
 soustractions correspond à la valeur de la racine carrée.
<br> <strong>Exemples et contre-exemples :</strong>
<ul><li>\(4\underset{\text{2 soustractions }}\underbrace{-1-3}=0 \Longrightarrow \text{2 soustractions} \Longrightarrow \sqrt{4}={2}\)</li>
<li>\(9\underset{\text{3 soustractions }}\underbrace{-1-3-5}=0 \Longrightarrow \text{3 soustractions} \Longrightarrow \sqrt{9}={3}\)</li>
<li>\(16\underset{\text{4 soustractions }}\underbrace{-1-3-5-7}=0 \Longrightarrow \text{4 soustractions} \Longrightarrow \sqrt{16}={4}\)</li>
<li>\(25\underset{\text{5 soustractions }}\underbrace{-1-3-5-7-9}=0 \Longrightarrow \text{5 soustractions} \Longrightarrow \sqrt{25}={5}\)</li>
<li>...</li>
<li>\(n^2\underset{\text{n soustractions }}\underbrace{-1-3-5-...-(2n-1)}=0 \Longrightarrow \text{n soustractions} \Longrightarrow \sqrt{n^2}={n}\)</li>
<li>\(17\underset{\text{5 soustractions }}\underbrace{-1-3-5-7-9}=-8 \Longrightarrow \sqrt{17}\) n'admet pas de racine carrée entière</li>
<li>\(31\underset{\text{6 soustractions }}\underbrace{-1-3-5-7-9-11}=-5 \Longrightarrow \sqrt{31}\) n'admet pas de racine carrée entière</li>
</ul> 
 Le programme devra afficher la racine carrée du nombre \(a\).}
\text{xl= wims(makelist x for x = 0 to \nbrech-1)}
\text{lista=wims(makelist x^2 for x=19 to 100)}
\integer{a=randitem(\lista)*1}
\integer{ra=sqrt(\a)}

\text{result=\ra}

\text{enonce=À l'aide des différentes instructions, réaliser le programme suivant écrit en langage
 Python.}

\text{instruction_code=instruction=[a=\a,n=0,n_imp=0,n=1,n_imp=1,while a>0:,while n>0:,while n_imp>0:,a=a+1,n=n+1,a=a-1,n_imp=2*n-1,n_imp=2*n,n_imp=2*n+1,n_imp=n_imp+2,n_imp=n_imp-2,a=a-n_imp,a=a+n_imp,a=a-2*n+1,a=a-2*n,a=a-2*n-1,print(n),print(n_imp),print(a),&#32;&#32;]}
