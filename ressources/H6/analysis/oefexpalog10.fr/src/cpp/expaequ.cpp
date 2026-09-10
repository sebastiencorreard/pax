target=expaequ1 expaequ2 expaequ3 expaequ4 expaequ5
\author{Cyrille, Douriez}##Adaptation d'un module de Régine Mangeard, aide de Bruno Mifsud pour la mise en forme##
\email{cyrille.douriez@ac-amiens.fr}
\format{html}
\language{fr}
\range{-5..5}
\computeanswer{no}
\precision{100000}
<!-- log interprété comme ln , peut engendrer des erreurs dans le cas où log(10) apparaît par exmeple-->
#define TITRE Equation avec une exponentielle de base a
\integer{a=randint(1..10)*randitem(1,1,1,-1)}
#if (defined TARGET_expaequ1 || defined TARGET_expaequ2 ||defined TARGET_expaequ3 ||defined TARGET_expaequ4||defined TARGET_expaequ5)
\integer{base=randint(2..9)}
#endif
#if (defined TARGET_expaequ1 ||defined TARGET_expaequ2 ||defined TARGET_expaequ3 ||defined TARGET_expaequ4)
\integer{b=randint(1..20)*randitem(1,1,1,-1)}
\integer{b=(\b==10)? randint(1..9):\b}
#endif
#if (defined TARGET_expaequ3 )

#endif

#if defined TARGET_expaequ1
\title{TITRE 1}
\text{equat=\base^{x}=\b}
\real{val=log(\b)/log(\base)}
\if{\b<0}{\text{sol=aucune}}{\real{sol=\val}}
\text{typesol=function}
\text{corrige=(\b<0)? \(\b\leq 0) et \(\base^{x}>0) donc il n'y a pas de solution:\(\base^{x}=\b) &hArr; \(log(\base^{x})=log(\b)) &hArr; \(x log(\base)=log(\b)) &hArr; \(x=\frac{log(\b)}{log(\base)})}
\text{corrige=(floor(\val)=\val)? \corrige\(=\val).:\corrige.}
\integer{affinstruction=0}##Affichage de l'instruction##
\text{listrep=\sol issametext aucune ?r1:r1;r2}
\integer{nbquest=2}#Nombre maximal de questions##
#endif

#if defined TARGET_expaequ2
\title{TITRE 2}
\function{f=maxima(\a*x+\b)}
\text{f=texmath(\f)}
\integer{c=randitem(1,1,1,1,0,-1)}
\text{equat=\base^{\f}=\c}
\if{\c==1}{\rational{sol=-\b/\a}}{\text{sol=aucune}}
\text{typesol=numeric}
\text{corrige=(\c<1)? \(\base^{\f}>0) donc il n'y a aucune solution.:\(\base^{\f}=1) &hArr; \(\f=0)  &hArr; \(x=\sol).}
\integer{affinstruction=0}
\text{listrep=\sol issametext aucune ?r1:r1;r2}
\integer{nbquest=2}
#endif
#if defined TARGET_expaequ3
\title{TITRE 3}
\function{f=maxima(\a*x+\b)}
\text{f=texmath(\f)}
\integer{c=randint(1..9)*randitem(1,1,-1)}
\text{equat=\base^{\f}=\base^{\c}}
\integer{s=\c-\b}
\rational{sol=\s/\a}
\text{typesol=numeric}
\text{corrige=\(\base^{\f}=\base^{\c}) &hArr; \(\f=\c)  &hArr; \(x=\sol).}
\integer{affinstruction=0}
\text{listrep=r2}
\integer{nbquest=1}
#endif
#if defined TARGET_expaequ4
\title{TITRE 4}
\integer{c=randint(2..10)}
\function{f=maxima(\a*x+\b)}
\text{f=texmath(\f)}
\text{equat=\frac{\base^{\f}}{\base^{\c}}=1}
\integer{s=\b-\c}
\rational{sol=-\s/\a}
\text{sol=\sol}
\text{typesol=numeric}
\text{corrige=\(\frac{\base^{\f}}{\base^{\c}}=1) &hArr; \(\base^{\f-\c}=1)  &hArr; \(\f-\c=0) &hArr; \(x=\sol).}
\integer{affinstruction=0}
\text{listrep=r2}
\integer{nbquest=1}
#endif
#if defined TARGET_expaequ5
\title{TITRE 5}
\integer{b=\a*randint(0..20)*randint(-1,-1,-1,1)}
\function{f=maxima(\a*x^2+\b)}
\text{f=texmath(\f)}
\text{equat=\base^{\f}=1}
\rational{s=-\b/\a}
\integer{cas=(\s>=0)? 2:1}
\text{x1=sqrt(\s)}
\text{x2=-sqrt(\s)}
\text{sol=(\cas=1)? aucune:\x1,\x2}
\text{sol=(\s=0)? 0:\sol}
\text{typesol=fset}
\integer{babs=abs(\b)}
\text{corrige=\(\base^{\f}=1) &hArr; \(\f=0)}
\text{corrige=(\b>=0)? \corrige <br>&hArr; \(\a x^2=-\b):\corrige <br>&hArr; \(\a x^2=\babs)}
\text{corrige= \corrige <br>&hArr; \( x^2=\s)}
\if{\s=0}{\text{corrige=\corrige<br> &hArr; \(x=0).}}
{\text{corrige=(\s<0)? \corrige. <br>\(x^2 \geq 0) et \(\s<0) donc il n'y a pas de solution. :\corrige<br> &hArr; \(x=\sqrt{\s}) ou \(x=-\sqrt{\s}).}}
\integer{affinstruction=1}
\text{instruction=Séparer les solutions éventuelles par une virgule. Pour \(\sqrt{...}), écrire : sqrt(...).</div>}
\text{listrep=\sol issametext aucune ?r1:r1;r2}
\integer{nbquest=2}
#endif

\integer{nbsol=\sol issametext aucune ?2:1}
\steps{\listrep}

\statement{
On considère l'équation \( \equat \) dans \(\mathbb{R}).
\if{\step=1 and \nbquest>1}{<div class="wims_question">Cette équation a-t-elle des solutions ? \embed{reply1,10} </div>}
\if{\step=1 and \nbquest=1}{<div class="wims_question">
\if{\typesol issametext fset}{L'ensemble des solutions est}{La solution est } \embed{reply2,8}.</div>
}
\if{\step=2}{<div class="wims_question">
\if{\typesol issametext fset}{L'ensemble des solutions est}{La solution est } \embed{reply2,8}.</div>
\if{\affinstruction=1}{<div class="wims_instruction">\instruction</div> }}}

\answer{}{\nbsol;Oui,Non}{type=radio}{weight=1}
\answer{}{\sol}{type=\typesol}{option=absolute comma}{weight=3}

\solution{\corrige}
