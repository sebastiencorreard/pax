target=solveeq1 solveeq2 solveeq3 solveeq4 solveeq5
#define TITRE Résoudre une équation
\author{Régine, Mangeard;Jean-Pierre, Boudine}
\email{regine@mangeard.fr}
#if defined TARGET_solveeq1
\title{TITRE 1}
\integer{a=randint(2..9)*randitem(1,-1)}
\integer{c=randint(2..9)*randitem(1,-1)}
\integer{c=\c=\a?-1*(\c)}
\integer{b=randint(2..9)*randitem(1,-1)}
\integer{d=randint(2..9)*randitem(1,-1)}
\integer{d=\d=\b?-1*(\d)}
\rational{x=(\d-\b)/ (\a - \c)}

\text{equat=\(texmath(\a*x+\b)=texmath(\c*x+\d)\)}
\text{tcons=Donner la valeur exacte de <span class="nowrap">\(x\),</span> éventuellement sous forme de fraction.
}
#endif
#if defined TARGET_solveeq2
\title{TITRE 2}
\integer{a=randint(2..9)*randitem(1,-1)}
\integer{c=randitem(2,3,5,6,7,8)}
\integer{b=randint(2..9)*randitem(1,-1)}
\rational{x=(-\b)/(\a + sqrt(\c))}
\integer{x=ceil(\x*100)}
\rational{x=\x/ 100}

\text{equat=\(texmath(\a*x+\b)+\sqrt{\c}x=0\)}
\text{tcons=Donner la valeur de \(x\) sous forme décimale approchée à la deuxième décimale par excès.
}
#endif
#if defined TARGET_solveeq3
\title{TITRE 3}
\integer{a=randint(2..9)*randitem(1,-1)}
\integer{p=randint(2..9)*randitem(1,-1)}
\integer{q=randint(2..9)*randitem(1,-1)}
\rational{x=\a*(\q)/ (\p)}

\text{equat=\(texmath(\a/x)=texmath(\p/\q)\)}
\text{tcons=Donner la valeur exacte de <span class="nowrap">\(x\),</span> éventuellement sous forme de fraction.
}
#endif
#if defined TARGET_solveeq4
\title{TITRE 4}
\integer{a=randint(2..5)*randitem(1,-1)}
\integer{b=randint(2..5)*randitem(1,-1)}
\real{x=-100*\a*2^(\b)}

\text{equat=\(texmath(0=10^(-2)*x+\a*2^\b)\)}
\text{tcons=}
#endif
#if defined TARGET_solveeq5
\title{TITRE 5}
\integer{a=randint(2..9)*randitem(1,-1)}
\integer{b=randint(2..9)*randitem(1,-1)}
\integer{b=\a+\b=0? \a+randitem(1,2,-1,-2)}
\rational{x=2*\a*\b/(\a + \b)}

\text{equat=\(texmath(2/x=1/\a+1/\b)\)}
\text{tcons=Donner la valeur exacte de <span class="nowrap">\(x\),</span> éventuellement sous forme de fraction.
}
#endif
\statement{
  Résoudre l'équation suivante, où \(x\) est l'inconnue&nbsp;:
<div class="wimscenter">\equat</div>
<div class="wimscenter">
<label for="reply1">\(x=)</label>\embed{reply1,5}
</div>
<div class="wims_instruction">\tcons</div>
}
\answer{x}{\x}{type=numeric}
