\text{prob=Étude d'une pièce de monnaie}
\text{instructionf=Jouer le code et envoyer la réponse.<br/>
<img src="\imagedir/attention.png" alt="Attention" /> : L'algorithme proposé est lent et il
 met une trentaine de secondes à s'exécuter. }

\text{enonce2=<br>On associe les événements suivants :
<ul><li>P : la face visible de la pièce est sur pile. La valeur associée est 0.</li>
<li>F : la face visible de la pièce est sur face. La valeur associée est 1.</li>
</ul>
La méthode <code>\pp()</code> arrondit un nombre décimal à l'entier en coupant la partie
décimale donc en couplant ses deux méthodes, on simule l'expérience aléatoire
 de la pièce de monnaie.}

\text{code=\code
nt=??
pt=??
nf=nl=ff=0
\#initialisation des listes\#
y_list = []
issue_list = []
\#################
for i in range(nt):
  issue = \pp(\ppp()+pt)
  nf=??
  nl=??
  ff=??
  y_list.append(ff)
  issue_list.append(issue)
\#Affichage des 5 premiers termes des listes#
print(y_list[\:5])
\#Ne pas modifier#
donne=issue_list[\:20]
test=y_list[\:20]}
\text{instruction3=<li>Compléter le script Python en sachant que :
<ul><li>La variable \(\text{nf}\) compte le nombre de fois où la pièce tombe sur face</li>
<li>La variable \(\text{nl}\) compte le nombre de lancers</li>
<li>La variable \(\text{ff}\) calcule la fréquence d'apparition de la pièce face</li>
</ul>
</li>}
\text{jsss3_1=donne=Sk.ffi.remapToJs(Sk.globals["donne"]);
test=Sk.ffi.remapToJs(Sk.globals["test"]);}

\text{donne=}
\text{donnef=}
\matrix{aadon=}

\text{embb=reply2,[python,[\code]];[idtest2,theme=\theme canvas init \instruction_code,Jouer le code !]}
\text{variable=[nt,\ntt],[pt,0.5]}
