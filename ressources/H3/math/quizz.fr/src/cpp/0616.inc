\title{Question 0616 Billes}
\keywords{pbsolving,multiplication}
\text{prenom=Yann,Tom,Karim,Julien,Léo,Gabin,Inès,Lou,Sarah,Léa}
\text{chp=wims(shuffle 10)}
\text{pronom=(\chp[1]<=6)? Il:Elle}
\integer{type=randitem(1,1,1,2,2,3,4)}
\integer{b=(\type==1)? randint(2,3):randint(3..9)}
\integer{a=(\type==1)? \b*randint(4..9):randint((\b+2)..18)}
\if{\type==1}{\text{info=\(\b\) fois plus de billes}
\integer{rep=\a/\b}}
\if{\type==2}{\text{info=\(\b\) fois moins de billes}
\integer{rep=\a*\b}}
\if{\type==3}{\text{info=\(\b\) billes de plus}
\integer{rep=\a-\b}}
\if{\type==4}{\text{info=\(\b\) billes de moins}
\integer{rep=\a+\b}}
\text{enonce=\prenom[\chp[1]] a \(\a\) billes. \pronom a \info que \prenom[\chp[2]]. \prenom[\chp[2]] a }
\text{enonceb=billes.}
\text{feedback=}
