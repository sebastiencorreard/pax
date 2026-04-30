target=expalg1 expalg2 expalg3 expalg4 expalg5
\author{Régine, Mangeard}
\email{regine@mangeard.fr}
\computeanswer{yes}
#if defined TARGET_expalg1
# define NUM 1
#endif
#if defined TARGET_expalg2
# define NUM 2
#endif
#if defined TARGET_expalg3
# define NUM 3
#endif
#if defined TARGET_expalg4
# define NUM 4
#endif
#if defined TARGET_expalg5
# define NUM 5
#endif
#include "lang_titles.inc"
\integer{x1=randint(1..20)*randint(1,-1)}
\integer{x2=randint(1..20)*randint(1,-1)}
\integer{x2=\x2=\x1?\x2+1}
\rational{a=simplify(randint(1..9)*randint(1,-1)/randint(1..5))}

#if defined TARGET_expalg1
\integer{b=0}
\rational{y1=\a*\x1}
\text{typefct=linéaire}
\text{quest=\(f(\x1)=\y1)}
#endif
#if defined TARGET_expalg2
\integer{b=0}
\rational{y1=\a*\x1}
\text{typefct=linéaire}
\text{quest=La courbe représentative de \(f) passe par le point \(A(\x1;\y1))}
#endif
#if defined TARGET_expalg3
\rational{b=simplify(randint(1..9)*randint(1,-1)/randint(1..3))}
\rational{y1=\a*\x1+\b}
\rational{y2=\a*\x2+\b}
\text{typefct=affine}
\text{quest=\(f(\x1)=\y1) et \(f(\x2)=\y2)}
#endif
#if defined TARGET_expalg4
\rational{b=simplify(randint(1..9)*randint(1,-1)/randint(1..3))}
\text{typefct=affine}
\rational{y1=\a*\x1+\b}
\text{quest=le coefficient directeur de \(f) vaut \(\a) et \(f(\x1)=\y1)}
#endif
#if defined TARGET_expalg5
\rational{b=simplify(randint(1..9)*randint(1,-1)/randint(1..3))}
\text{typefct=affine}
\rational{y1=\a*\x1+\b}
\text{quest=l'ordonnée à l'origine de \(f) vaut \(\b) et \(f(\x1)=\y1)}
#endif
\text{rep=\b=0?\a*x:\a*x+\b}
\statement{
  On considère une fonction \typefct \(f) telle que
<div class="wimscenter">\quest</div>
  Déterminer l'expression algébrique de \(f).
<div class="wimscenter"><label for="reply1">\(f(x))=</label>\embed{reply1,7}</div>
}
\answer{\(f(x))}{\rep}{type=function}
