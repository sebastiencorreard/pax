target=expaequ6 expaequ7
\author{Cyrille, Douriez}##Adaptation d'un module de Régine Mangeard##
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
\language{fr}
\range{-5..5}
\computeanswer{no}
\precision{100000}
<!-- log interprété comme ln , peut engendrer des réponses mal testées si solution donnée très manipulée-->
#define TITRE Equation avec une exponentielle de base a
\integer{a=randint(1..9)*randitem(1,1,1,-1)}
\integer{c=randint(1..9)*randitem(1,1,1,-1)}
#if defined TARGET_expaequ7
\integer{s=randint(0..15)*randitem(1,1,1,-1)}
\integer{b= \c-\a*\s}
#endif



#if defined TARGET_expaequ6
\title{TITRE 6}
\text{equat=10^{\x}=\c}
\if{\c<=0}{\text{sol=aucune}}{\real{sol=log(\c)/log(10)}}
\text{affinstruction=1}
\text{instruction=En cas d'absence de solution, écrire : aucune}
\if{\c<=0}{\text{corrige=\(10^{x}>0) et \(\c\leq 0) donc il n'y a pas de solution.}}
{\text{corrige= \(10^{x}=\c) &hArr; \(x=log(\c))}}
\integer{s=\c}
#endif

#if defined TARGET_expaequ7
\title{TITRE 7}
\function{f=maxima(\a*(10^x)+\b)}
\text{f=texmath(\f)}
\text{equat=\f=\c}
\text{sol=log(\s)/log(10)}
\text{sol=(\s<=0)? aucune:\sol}
\text{sol=(\s=10)? 1:\sol}
\text{typesol=formal}
\integer{babs=abs(\b)}
\integer{m2=\c-\b}
\text{corrige=\sol \(\f=\c\) &hArr; \(\a 10^x=\m2\) <br>&hArr; \(10^x=\s\).}
\text{corrige=(\s<=0)? \corrige <br>\(10^{x}>0) et \(\s\leq 0) donc il n'y a pas de solution. :\corrige<br> &hArr; \(x=log(\s)).}
\text{affinstruction=1}
\text{instruction=En cas d'absence de solution, écrire : aucune.}
#endif

\statement{
<div class="wims_question">Résoudre dans \(\mathbb{R}\) l'équation :
\( \equat \)</div>
\if{\typesol issametext fset}{L'ensemble des solutions est}{La solution est } \embed{reply1,8}.
\if{\affinstruction=1}{<div class="wims_instruction">\instruction</div>}
}

\answer{}{\var}{type=raw}{option=absolute comma}
\text{reputilm=(\var)/ln(10)}

#if defined TARGET_expaequ6
\real{equ=10^(\reputilm)}
#endif
#if defined TARGET_expaequ7
\real{equ=\a*10^(\reputilm)+\b}
#endif

\condition{Réponse correcte ?}{(\s<=0 and \var issametext aucune) or (\s>0 and \var==\sol) or (\s>0 and (log isin \var) and \equ==\c)}

\solution{\corrige}
