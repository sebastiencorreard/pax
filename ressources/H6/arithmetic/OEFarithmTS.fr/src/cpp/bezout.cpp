target=bezout1 bezout2 bezout3 bezout4
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\format{html}
\css{<style>
.red {color:red}
.orange {color:orange}
.blue {color:blue}
.green {color:green}
</style>}
#define TITRE Théorème de Bezout
\text{lstprime=shuffle(2,3,5,7,11,13,17,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97)}
\integer{p1=\lstprime[1]}
\integer{p2=\lstprime[2]}
\integer{a=randint(1..10)*\p1}
\integer{b=randint(1..5)*\p1+randint(1..10)*\p2}
\integer{q4=randint(2..5)}
\integer{b4=randint(1..6)}
\integer{q3=\b4*\q4+1}
\integer{b3=randint(1..6)}
\integer{q2=\b3*\q3+\q4}
\integer{b2=randint(1..6)}
\integer{b=\b2*\q2+\q3}
\integer{b1=randint(111..221)}
\integer{a=\b1*\b+\q2}
\integer{u3=1+\b4*\b3}
\integer{u2=\u3*\b2+\b4}
\integer{u1=\u3+\u2* \b1}
\integer{u=-\u2}
\integer{v=\u1}
\text{tsol=L'algorithme d'Euclide donne:<br>
<span class="red">\a</span>= \(\b1 \times )<span class="red">\b</span>+<span class="orange">\q2</span><br>
\(\b= \b2 \times \q2+)<span class="green">\q3</span><br>
\(\q2= \b3 \times \q3+)<span class="blue">\q4</span><br>
\(\q3= \b4 \times \q4+1)<p>
  On obtient les coefficients de Bezout en remontant l'algorithme:</p>
\(1= )<span class="green">\q3</span>\( - \b4 \times )<span class="blue">\q4</span><br>
\(1= )<span class="green">\q3</span>\( - \b4 \times )(<span class="orange">\q2</span>\( -\b3 \times) <span class="green">\q3</span>)\(=(1+\b4 \times \b3))<span class="green"> \q3</span>\( -\b4 \times)<span class="orange"> \q2</span><br>
\(1= \u3 \times )<span class="green">\q3</span>\( - \b4 \times)<span class="orange"> \q2</span>\(= \u3 \times)(<span class="red">\b</span> \(-\b2 \times) <span class="orange">\q2</span>)\( -\b4 \times) <span class="orange">\q2</span>\(= \u3 \times )<span class="red">\b</span>\( - (\u3 \times \b2 +\b4) \times)<span class="orange"> \q2</span><br>
\(1= \u3 \times )<span class="red">\b</span>\(- \u2 \times )<span class="orange">\q2</span>\(= \u3 \times) <span class="red">\b</span>\( - \u2 \times) (<span class="red">\a</span> \( - \b1 \times )<span class="red">\b</span>)\(= (\u3+ \u2 \times \b1) \times) <span class="red">\b</span>\( - \u2 \times) <span class="red">\a</span><br>
\(1= \u1 \times) <span class="red">\b</span>\( -\u2 \times) <span class="red">\a</span>}

#if defined TARGET_bezout1
\title{TITRE 1}
\statement{
  Trouver des entiers relatifs \(u) et \(v) tels que :
<div class="wimscenter"> \a u + \b v=1</div>
}
\answer{u}{\u}{type=numeric}
\answer{v}{\v}{type=numeric}
\condition{\a*\u+\b*\v=1}
\solution{\tsol}
#endif
#if defined TARGET_bezout3
\title{TITRE 3}
\integer{k=randint(10..20)*randint(1,-1)}
\integer{x=\u+\k*\b}
\integer{y=\v-\k*\a}
\integer{x1=\x-randint(1..\b-1)}
\integer{x2=\x+randint(1..\b-1)}
\statement{<p>
  Connaissant une solution particulière (\u,\v) de l'équation diophantienne
</p>
<div class="wimscenter"> \a x + \b y=1</div>
  déterminer une solution vérifiant \( \x1 < x < \x2):
<div class="wimscenter"> \(x=) \embed{reply1} </div>
<div class="wimscenter"> \(y=) \embed{reply2} </div>

}
\answer{x}{\x}{type=numeric}
\answer{y}{\y}{type=numeric}
\solution{Les solutions sont de la forme (\u+k \b;\v-k \a) avec \(k \in \ZZ).}
#endif


#if (defined TARGET_bezout2 || defined TARGET_bezout4 )
# if defined TARGET_bezout2
\title{TITRE 2}
\integer{rep=randint(1,2)}
# endif
# if defined TARGET_bezout4
\title{TITRE 4}
\integer{rep=1}
# endif
\text{mstep=\rep=2?r1:r1
r2,r3}
\text{cond=\rep=1?1}
\integer{q3=randint(2..5)}
\integer{k=randint(2..5)}
\integer{c=\rep=1?\k*\q3:\k*\q3+randint(1..\q3-1)}
\integer{b3=randint(1..6)}
\integer{q2=\b3*\q3}
\integer{b2=randint(1..6)}
\integer{b=\b2*\q2+\q3}
\integer{b1=randint(111..221)}
\integer{a=\b1*\b+\q2}
\integer{u3=1+\b4*\b3}
\integer{u2=\u3*\b2+\b4}
\integer{u1=1+\b2* \b1}
\integer{uu=-\b2}
\integer{vv=\u1}
\integer{u=-\b2*\k}
\integer{v=\u1*\k}

\text{tsol=L'algorithme d'Euclide donne:<br>
<span class="red">\a</span>
= \(\b1 \times )<span class="red">\b</span>+<span class="orange">
\q2</span><br>
\(\b= \b2 \times \q2+)<span class="green">\q3</span><br>
\(\q2= \b3 \times \q3)<p>
  Donc PGCD(\a,\b)=\q3.</p>}

\text{tsol=\rep=1? \tsol
  Or \q3 divise \c.<br>
  On obtient les coefficients de Bezout en remontant l'algorithme.<p>
\(\q3= )<span class="red">\b</span>\( - \b2 \times )<span class="orange">\q2</span><br>
\(\q3= )<span class="red">\b</span>\( - \b2 \times )
( <span class="red">\a</span>\( - \b1 \times) <span class="red">\b</span>)<br>
\(\q3= \u1 \times )<span class="red">\b</span>\(- \b2 \times )<span class="red">\a</span>
</p>
  donc
\(\c= \u \times) <span class="red">\a</span>\( +\v \times) <span class="red">\b</span>
: \tsol
  Mais \q3 ne divise pas \c, on ne peut donc pas trouver de couples (u,v) vérifiant l'équation. }


# if defined TARGET_bezout2
\steps{\mstep}
\conditions{\cond}
\statement{
\if{\step=1}{
  Peut-on trouver des entiers relatifs \(u) et \(v) tels que :
<div class="wimscenter"> \a u + \b v = \c</div>
\embed{reply1}
 }{
  Trouver des entiers relatifs \(u) et \(v) tels que :
<div class="wimscenter"> \a u + \b v=\c</div>
 }
}
\answer{Possible}{\rep;Oui,Non}{type=radio}
\answer{u}{\urep}{type=numeric}
\answer{v}{\vrep}{type=numeric}
\condition{\a \urep+\b \vrep=1 ?}{\a*\urep + \b*\vrep=\c}
\solution{\tsol}
# endif
# if defined TARGET_bezout4
\integer{choix=randint(1,2)}
\integer{choix=1}
\integer{d_=gcd(\a,\b)}
\integer{a_=\a/\d_}
\integer{b_=\b/\d_}
\integer{c_=\c/\d_}
\text{sol=pari(\c_*bezout(\a_,\b_))}
\text{u_=\sol[1]}
\text{v_=\sol[2]}

\if{\choix=1}{
 \text{var=x}
 \integer{x=pari(lift(Mod(\u_,\b_)))}
 \integer{k_=(\u_-\x)/\b_}
 \integer{y=\v_+\k_*\a_}
 }{
 \text{var=y}
 \integer{y=pari(lift(Mod(\v_,\a_)))}
 \integer{k_=(\v_-\y)/\a_}
 \integer{x=\u_+\k_*\b_}
 }
\statement{
  Connaissant une solution particulière (\u, \v) de l'équation diophantienne:
<div class="wimscenter"> \a x + \b y = \c</div>
  déterminer la solution (x;y) avec \(\var) un entier positif et le plus petit possible :
<div class="wimscenter"> \(x=\) \embed{reply1} </div>
<div class="wimscenter"> \(y=\) \embed{reply2} </div>
}
\answer{x}{\x}{type=numeric}
\answer{y}{\y}{type=numeric}
\solution{Les solutions sont de la forme (\u + \b_ k;\v - \a_ k) avec \(k \in \ZZ).}
# endif
#endif
