target=trigo3
#include "lang_titles.inc"
#include "author.inc"
\precision{10000}

#include "lang.inc"

\text{sincos=random(sin,cos,tan)}
\text{pa= pari(randint(0..120)/60)}
\text{A=\pa*pi}
\if{(\pa=1/2 or \pa = 3/2) and (tan isin \sincos)}{
	\text{a=sign(1-\pa)*inf}
	}{
	\real{a=\sincos(\A)}
	}
\integer{u=randint(-50..50)}
\integer{v=\u+randint(3*pi..5*pi)}

\integer{k0=floor((\u-(\A))/(2*pi))}
\integer{k1= floor((\v-(\A))/(2*pi))}
\integer{k1=\k1=(\v-(\A))/(2*pi) ? \k1-1}
\real{sol=\A+(2*(\k0+1)*pi)}
\for{i=\k0+2 to \k1}{
	\real{so=\A+(2*(\i)*pi)}
	\text{sol=\sol,\so}
}
\real{AA=sin isin \sincos ? pi-(\A): -(\A)}
\real{AA= tan isin \sincos ? pi+(\A)}
\integer{k2=floor((\u-(\AA))/(2*pi))}
\integer{k3=floor( (\v-(\AA))/(2*pi))}
\integer{k3=\k3=(\v-(\AA))/(2*pi) ? \k3-1}
\for{i=\k2+1 to \k3}{
	\real{so=\AA+(2*(\i)*pi)}
	\text{sol=\sol,\so}
}
\text{sol=wims(sort numeric list \sol)}
\text{dessin= tan isin\sincos and \pa != 1/2 and \pa != 3/2 ? max(\abs(\a),3):1.2}

\statement{\name_instruction[1]
<div class="wimscenter">\( \sincos(x) = \a)</div>
\name_instruction[2] &#93;\( \u , \v) &#91; \name_instruction[3]
}
\answer{\name_solution}{\sol}{type=vector}

\hint{\name_hint[1] \sincos \name_hint[2] [\u , \v] :
<div class="wimscenter"> \draw{150,150}{
	xrange \u,\v
	yrange -\dessin,\dessin
	hline \u,0, black
	linewidth 2
	plot green, \sincos(x)
	hline \u,\a, navy
}
</div>
}
\text{test=1}
\for{s in \reply1}{\text{test= \s <= \u or \s >= \v ? 0}}

\feedback{\test =0}{\name_feed}
