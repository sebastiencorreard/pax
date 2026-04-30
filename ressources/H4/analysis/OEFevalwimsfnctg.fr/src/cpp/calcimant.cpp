target=calcimant1 calcimant2 calcimant3 calcimant4 calcimant5
\author{Régine, Mangeard}
\email{regine@mangeard}
\format{html}
#define TITRE Détermination d'image et d'antécédent
#if (defined TARGET_calcimant1)
# define NUM 1
#endif
#if (defined TARGET_calcimant2)
# define NUM 2
#endif
#if (defined TARGET_calcimant3)
# define NUM 3
#endif
#if (defined TARGET_calcimant4)
# define NUM 4
#endif
#if (defined TARGET_calcimant5)
# define NUM 5
#endif
\title{TITRE NUM}
#if (defined TARGET_calcimant1 || defined TARGET_calcimant2 )
%%%% Choix de 10 points dans le cadre
\integer{nbpt=10}
\integer{xmin=-10}
\integer{xmax=10}
\integer{x=\xmin}
\text{listx=}
\text{listy=}
\for{i=1 to \nbpt}{
\real{x=\x+randint(0..2)+randint(1..10)/10}
\text{listx=wims(append item \x to \listx)}
\real{y=randint(-100..100)/10}
\text{listy=wims(append item \y to \listy)}
}

\text{listy2=\listy}
\integer{k=randint(1,2)}

# if defined TARGET_calcimant1
\text{typequest=l'image}
\text{typequest2=les images}
\text{typerep=numeric}
%%%% Choix des questions
\text{listind=shuffle(\nbpt)}
\text{q1=\listx[\listind[1]]}
\text{q2=\listx[\listind[2]]}
\text{q3=\listx[\listind[3]]}
\text{q4=\listx[\listind[4]]}
\text{rep1=\listy[\listind[1]]}
\text{rep2=\listy[\listind[2]]}
\text{rep3=\listy[\listind[3]]}
\text{rep4=\listy[\listind[4]]}

%%%% pour tester la compréhension
\text{listy=wims(replace item number \listind[5] by \q2 in \listy)}
\text{listy=wims(replace item number \listind[6] by \q4 in \listy)}
\text{listy=wims(replace item number \listind[7] by \q4 in \listy)}
# endif

# if defined TARGET_calcimant2
\text{typequest=le ou les antécédents}
\text{typequest2=les antécédents}
\text{typerep=fset}
%%%% Choix des questions
\text{listind=shuffle(\nbpt)}
\text{rep1=\listx[\listind[1]]}
\text{rep2=\listx[\listind[2]]}
\text{rep3=\listx[\listind[3]]}
\text{rep4=\listx[\listind[4]]}

%%%% pour tester la compréhension
\text{listy=wims(replace item number \listind[2] by \listx[\listind[5]] in \listy)}
\text{listy=wims(replace item number \listind[4] by \listx[\listind[7]] in \listy)}

%%%% on veut au moins une image avec 2 antécédents
\integer{i=random(1..4)}
\integer{j=random(5..10)}
\text{listy=wims(replace item number \listind[\j] by \listy[\listind[\i]] in \listy)}

\text{q1=\listy[\listind[1]]}
\text{q2=\listy[\listind[2]]}
\text{q3=\listy[\listind[3]]}
\text{q4=\listy[\listind[4]]}
%%%% On teste la présence de plusieurs antécédents
\text{indrep1=wims(positionof item \q1 in \listy)}
\integer{nr=items(\indrep1)}
\if{\nr>1}{
  \text{rep1=}
  \for{i=1 to \nr}{\text{rep1=wims(append item \listx[\indrep1[\i]] to \rep1)}}
}
\text{indrep2=wims(positionof item \q2 in \listy)}
\integer{nr=items(\indrep2)}
\if{\nr>1}{
  \text{rep2=}
  \for{i=1 to \nr}{\text{rep2=wims(append item \listx[\indrep2[\i]] to \rep2)}}
}

\text{indrep3=wims(positionof item \q3 in \listy)}
\integer{nr=items(\indrep3)}
\if{\nr>1}{
  \text{rep3=}
  \for{i=1 to \nr}{\text{rep3=wims(append item \listx[\indrep3[\i]] to \rep3)}}
}

\text{indrep4=wims(positionof item \q4 in \listy)}
\integer{nr=items(\indrep4)}
\if{\nr>1}{
  \text{rep4=}
  \for{i=1 to \nr}{\text{rep4=wims(append item \listx[\indrep4[\i]] to \rep4)}}
}
# endif

\text{lignex=}
\for{i=1 to \nbpt}{\text{lignex=\lignex <td>\listx[\i]</td>}}
\text{ligney=}
\for{i=1 to \nbpt}{\text{ligney=\ligney <td> \listy[\i]</td>}}

\statement{
  On considère une fonction \(f) donnée par son tableau de valeurs:
<table class="wimscenter wimsborder">
 <tr><td>\(x)</td>\lignex
 </tr><tr>
  <td>\(f(x))</td>\ligney</tr>
</table>
<p>
  Par lecture du tableau, déterminer \typequest2 des réels suivants:
</p>
<div class="wims_question">
  Votre réponse :
<ul>
<li><label for="reply1">\typequest de \q1</label>: \embed{reply 1,3}</li>
<li><label for="reply2">\typequest de \q2</label>: \embed{reply 2,3}</li>
<li><label for="reply3">\typequest de \q3</label>: \embed{reply 3,3}</li>
<li><label for="reply4">\typequest de \q4</label>: \embed{reply 4,3}</li>
</ul>
</div>
}
\answer{\quest}{\rep1}{type=\typerep}
\answer{\quest}{\rep2}{type=\typerep}
\answer{\quest}{\rep3}{type=\typerep}
\answer{\quest}{\rep4}{type=\typerep}
#else
\integer{a=randint(1..9)*randitem(1,-1)}
\integer{b=randint(-9..9)}
\integer{c=randint(1..9)*randitem(1,-1)}
\integer{d=randint(-9..9)}
\integer{q1=randint(-9..9)}
\integer{q2=0}
\integer{d=\c*\q1+\d=0? \d-1}
\text{typequest1=l'image}
\text{typequest2=le (ou les) antécédent(s)}
\text{typerep1=numeric}
\text{typerep2=fset}

# if defined TARGET_calcimant3
\text{f=texmath(maxima(\a*x+\b))}
\integer{q2=randint(-9..9)}
\integer{rep1=\a*\q1+\b}
\rational{rep2=(\q2-\b)/(\a)}
# endif
# if defined TARGET_calcimant4
\text{f=texmath(maxima((\a*x+\b)*(\c*x+\d)))}
\integer{rep1=(\a*\q1+\b)*(\c*\q1+\d)}
\rational{r2=-\b /(\a)}
\rational{r3=-\d /(\c)}
\text{rep2=\r2,\r3}
# endif
# if defined TARGET_calcimant5
\text{f=texmath(maxima((\a*x+\b)/(\c*x+\d)))}
\rational{rep1=(\a*\q1+\b)/(\c*\q1+\d)}
\rational{rep2=-\b /(\a)}
# endif

\statement{
  On considère une fonction \(f) donnée par son expression algébrique:
<div class="wimscenter">\(f(x)=\f).</div>
<div class="wims_question">Déterminer \typequest1 de \q1 et \typequest2 de \q2 :
<ul>
<li><label for="reply1">\typequest1 de \q1:</label> \embed{reply1,5}</li>
<li><label for="reply2">\typequest2 de \q2:</label>\embed{reply2,5}
<div class="wims_instruction">
  S'il y a plusieurs réponses, les séparer par une virgule.</div>
</li>
</ul>
</div>
}
\answer{}{\rep1}{type=\typerep1}
\answer{}{\rep2}{type=\typerep2}
#endif
