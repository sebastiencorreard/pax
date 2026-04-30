\title{Fonction n°2}
//code modifié par Paul Byache, pbyache@ac-aix-marseille.fr
\integer{tot=3}
\integer{choix=random(1,2)}
\integer{x=randint(6..12)}
\integer{y=randint(15..30)}
\integer{u=\x+\y}
\integer{v=abs(\x-\y)}
\integer{rep1=(\u+\v)/2}
\integer{rep2=(\u-\v)/2}
\real{rep3=(\x+\y)/2}
\text{rep1=\rep1}
\text{rep2=\rep2}
\text{rep3=\rep3}
\integer{rep=item(\choix,\rep1,\rep2)}

\text{rept=item(\choix,(u+v)/2,(u-v)/2)}
\text{reptt=item(\choix,(\u+\v)/2,(\u-\v)/2)}
\text{reptt1=item(\choix,Le plus grand des deux nombres \x et \y,Le plus petit des deux nombres \x et \y)}
\text{reptt2=item(\choix, Le maximum de \x et \y, Le minimum de \x et \y)}

\integer{choix2=item(\choix,2,1)}
\text{false=item(\choix2,(u+v)/2,(u-v)/2)}
\text{false1=item(\choix2,Le plus grand des deux nombres \x et \y,Le plus petit des deux nombres \x et \y)}
\text{false2=item(\choix2, Le maximum de \x et \y, Le minimum de \x et \y)}

\text{explain0=asis(Que retourne <span class="tt">mystere(\x,\y)</span>
  écrit en langage Python ?)}
\text{explain=def mystere(x,y):
  u=x+y
  v=abs(x-y)
  return(\rept)}

\integer{choixformulation=random(1,2)}
\text{repf=item(\choixformulation,\reptt1,\reptt2)}
\text{falsef=item(\choixformulation,\false2,\false1)}

\matrix{datatrue=asis(
 \rep
 \repf )}

\matrix{datafalse=asis(
\rep3
\false
\falsef)}

\text{maxmin=item(\choix,maximum,minimum)}

\text{feedback_generalpre=C'est une fonction en langage Python,
  <span class="tt">mystere(\x,\y)</span> fait la chose suivante :}
\text{feedback_program=
\(u\) prend la valeur \(\x+\y\)
\(v\) prend la valeur \(abs(\x-\y))
Retourner la valeur \(\reptt)}
\text{feedback_generalpost= La fonction retourne donc \rep, soit le \maxmin entre \x et \y.</p><p> ... Mais au fait : pourquoi cette fonction retourne-t-elle <b>toujours</b> le \maxmin entre x et y &#63; ...}
