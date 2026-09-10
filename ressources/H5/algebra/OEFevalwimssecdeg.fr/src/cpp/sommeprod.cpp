target=sommeprod1 sommeprod2
#if defined TARGET_sommeprod1
# define NUM 1
#endif
#if defined TARGET_sommeprod2
# define NUM 2
#endif
#include "lang_titles.inc"
\language{fr}
\author{Marie-Claude, David}
\email{mcldavid@orange.fr}
\computeanswer{no}
\precision{10000}
\range{-5..5}
\description{Somme et produit des racines d'un polynôme du second degré.}
\keywords{equations,trinomial,roots}

\integer{e = random(1..4)}
\integer{f = random(-2..5)}
\integer{s = \e + (\f)}
\integer{b = -\s}
\integer{c = \e*\f}
\integer{d = (\b)^2-4*(\c)} ne sert pas
#if defined TARGET_sommeprod1
\text{E = pari(x^2+\b*x+\c)}
#endif
#if defined TARGET_sommeprod2
\integer{g = randitem(-1,1)*randint(2..5)}
\text{E=pari(\g*(x^2+\b*x+\c))}
#endif
\statement{
<p>Soit \(P(x) = \E\). Ce polynôme admet deux racines distinctes ou confondues.
  Calculer leur somme et leur produit.</p>
<div>Les deux racines du polynômes ont pour somme
  \embed{reply 1,20} et pour produit \embed{reply 2,20}.
</div>
}
\answer{somme}{\s}{type=numeric}
\answer{produit}{\c}{type=numeric}

\hint{On peut connaître la somme et le produit des racines du polynôme
  sans les calculer. Il suffit d'imaginer le trinôme factorisé.
}
