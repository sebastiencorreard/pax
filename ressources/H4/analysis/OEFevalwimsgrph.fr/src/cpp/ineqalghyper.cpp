target=ineqalghyper1 ineqalghyper2 ineqalghyper3 ineqalghyper4 ineqalghyper5

#include "author.inc"
#include "lang_titles.inc"
#include "vartab.inc"
#define TITRE Inéquation algébrique quotient
\integer{a=randint(1..10)*(randitem(1,-1))}
\integer{b=randint(1..10)*(randitem(1,-1))}
\integer{c=randint(1..10)^2*(randitem(1,-1))}
\integer{d=randint(1..10)*(randitem(1,-1))}
\integer{e=randint(1..10)*(randitem(1,-1))}
\integer{f=randint(1..10)*(randitem(1,-1))}
\integer{det=\a*\f-\b*\e}
\integer{f=\det=0?-(\f)}
\integer{ef=\e*\f}
\integer{f=\ef<0?-\f}
\integer{g=randint(2..5)*(randitem(1,-1))}
\integer{h=randint(2..5)*(randitem(1,-1))}

%%%% choix de la question
\integer{sensineq=randint(1..2)}
\integer{strictineq=randint(0..1)}
\text{sgt=>}
\text{sge=\ge }
\text{slt=<}
\text{sle=\le }
%%%% la liste des objets que l'on peut cliquer pour résoudre l'exercice %%%%
\text{crocg=\(\lbrack)}
\text{crocd=\(\rbrack)}
\text{bracg=&#123;}
\text{bracd=&#125;}
\text{union=\(\cup)}
\text{inter=\(\cap)}
\text{infg=\(-\infty)}
\text{infd=\(+\infty)}
\text{empt=\(\emptyset)}
\text{ptvirg=\(\star)}
\text{ptvirg=&#59;}
\text{crochg=\strictineq=0?\crocd:\crocg}
\text{crochd=\strictineq=0?\crocg:\crocd}
%%%% préparation de la question
\text{symb=\slt,\sgt,\sle,\sge}
\text{wsymb=<,>,<=,>=}
\integer{indsymb=\sensineq+2*\strictineq}

#if defined TARGET_ineqalghyper1
\text{tintro=on a construit le tableau des signes suivant}
\text{tverb=A l'aide de ce tableau, cocher}
#endif
#if defined TARGET_ineqalghyper2
\text{tintro=Commencer par remplir le tableau des signes suivant}
\text{tverb=Puis cocher}
#endif
#if defined TARGET_ineqalghyper3
\text{tintro=Commencer par remplir le tableau des signes suivant}
\text{tverb= Puis indiquer}
#endif
#if defined TARGET_ineqalghyper4
\text{tintro=Commencer par remplir le tableau des signes suivant}
\text{tverb=Puis indiquer}
#endif
#if defined TARGET_ineqalghyper5
\text{tintro=Commencer par remplir le tableau des signes suivant}
\text{tverb=Puis indiquer}
#endif
   \rational{nv1=simplify(-(\b) /(\a))}
   \rational{x1=\nv1}
   \rational{nv2=simplify(-(\f) /(\e))}
   \rational{x2=\nv2}
   \rational{nv3=simplify(\a /(\b))}
   \rational{nv4=simplify(-(\a) /(\b))}
   \rational{nv5=simplify(\b /(\a))}
   \rational{nv6=simplify(\f /(\e))}
   \rational{nv7=simplify(\e /(\f))}
   \rational{nv8=simplify(-(\e) /(\f))}
   \text{v1=\(texmath(\nv1))}
   \text{v2=\(texmath(\nv2))}
   \text{v3=\(texmath(\nv3))}
   \text{v4=\(texmath(\nv4))}
   \text{v5=\(texmath(\nv5))}
   \text{v6=\(texmath(\nv6))}
   \text{v7=\(texmath(\nv7))}
   \text{v8=\(texmath(\nv8))}
   \text{v9=0}
   \text{permut=\v1,\v2,\v3,\v4,\v5,\v6,\v7,\v8,\v9}
   \text{permut=wims(listuniq \permut)}
   \text{permut=shuffle(\permut)}
   \text{tsing1=\nv1<\nv2?\v1:\v2}
   \text{tsing2=\nv1<\nv2?\v2:\v1}
   \rational{valmin=\nv1<\nv2?\nv1:\nv2}
   \rational{valmax=\nv1<\nv2?\nv2:\nv1}

#if (defined TARGET_ineqalghyper1  || defined TARGET_ineqalghyper2  || defined TARGET_ineqalghyper3 )
 \text{equat= (\a*x + \b)/(\e*x+\f)}
\text{fact1=\(texmath(\a*x+\b))}
\text{fact2=\(texmath(\e*x+\f))}
\text{equat=texmath(\equat)\symb[\indsymb] 0}
#endif
#if defined TARGET_ineqalghyper4
\integer{k=randint(1..2)}
\integer{k=2}
\if{\k=1}{
 \text{equat= (\a*x + \b)^2/(\e*x+\f)}
 \text{fact1=\(texmath((\a*x+\b)^2))}
 \text{fact2=\(texmath(\e*x+\f))}
 }
\if{\k=2}{
 \text{equat= (\a*x + \b)/(\e*x+\f)^2}
 \text{fact1=\(texmath(\a*x+\b))}
 \text{fact2=\(texmath((\e*x+\f)^2))}
 }
\text{equat=texmath(\equat)\symb[\indsymb] 0}
#endif
#if defined TARGET_ineqalghyper5
 \integer{c=\a+\g*\e}
 \integer{d=\b+\g*\f}
 \text{equat= (\c*x + \d)/(\e*x+\f)}
 \text{fact1=\(texmath((\a*x+\b)))}
 \text{vfact1=\a*x+\b}
 \text{fact2=\(texmath(\e*x+\f))}
\text{equat=texmath(\equat)\symb[\indsymb] \g}
#endif

\text{tableau=<table class="tab_var">
<tr>
<th>\(x)</th>
<td style="width:10%">\infg</td>
<td style="width:20%">&nbsp;</td>
<td style="width:10%">\(\valmin)</td>
<td style="width:20%">&nbsp;</td>
<td style="width:10%">\(\valmax)</td>
<td style="width:20%">&nbsp;</td>
<td style="width:10%"> \infd </td></tr>
}
  \text{z1g=\nv1 < \nv2? 0:|}
  \text{z1d=\nv1 < \nv2? |:0}
  \text{lstsgn=+,-}
  \text{lstz=0,|,||}
#if defined TARGET_ineqalghyper4
\if{\k=1}{
  \text{s1g=+}
  \text{s1m=+}
  \text{s1d=+}
  }{
\if{\a>0}{
  \text{s1g=-}
  \text{s1m=\nv1 < \nv2?+:-}
  \text{s1d=+}
  }{
  \text{s1g=+}
  \text{s1m=\nv1 < \nv2?-:+}
  \text{s1d=-}
  }
 }
#else
\if{\a>0}{
  \text{s1g=-}
  \text{s1m=\nv1 < \nv2?+:-}
  \text{s1d=+}
  }{
  \text{s1g=+}
  \text{s1m=\nv1 < \nv2?-:+}
  \text{s1d=-}
  }

#endif
  \text{ligne=<tr><td>\fact1</td><td>&nbsp;</td><td>\s1g</td><td>\z1g</td><td>\s1m</td><td>\z1d</td><td>\s1d</td><td>&nbsp;</td></tr>}
  \integer{ns1g=position(\s1g,\lstsgn)}
  \integer{ns1m=position(\s1m,\lstsgn)}
  \integer{ns1d=position(\s1d,\lstsgn)}
  \text{tableau=\tableau \ligne}
  \text{z2d=\nv1 < \nv2? 0:|}
  \text{z2g=\nv1 < \nv2? |:0}
#if defined TARGET_ineqalghyper4
\if{\k=2}{
  \text{s2g=+}
  \text{s2m=+}
  \text{s2d=+}
  }{
\if{\e>0}{
  \text{s2g=-}
  \text{s2m=\nv1 < \nv2?-:+}
  \text{s2d=+}
  }{
  \text{s2g=+}
  \text{s2m=\nv1 < \nv2?+:-}
  \text{s2d=-}
  }
}
#else
\if{\e>0}{
  \text{s2g=-}
  \text{s2m=\nv1 < \nv2?-:+}
  \text{s2d=+}
  }{
  \text{s2g=+}
  \text{s2m=\nv1 < \nv2?+:-}
  \text{s2d=-}
  }
#endif

  \text{ligne=<tr><td>\fact2</td><td>&nbsp;</td><td>\s2g</td><td>\z2g</td><td>\s2m</td><td>\z2d</td><td>\s2d</td><td>&nbsp;</td></tr>}
  \integer{ns2g=position(\s2g,\lstsgn)}
  \integer{ns2m=position(\s2m,\lstsgn)}
  \integer{ns2d=position(\s2d,\lstsgn)}
  \text{tableau=\tableau \ligne}
\integer{\ac=\a*\e}

#if defined TARGET_ineqalghyper4
\if{\k=1}{
   \text{s3g=\s2g}
   \text{s3m=\s2m}
   \text{s3d=\s2d}
  }{
   \text{s3g=\s1g}
   \text{s3m=\s1m}
   \text{s3d=\s1d}
  }
#else

\text{s3g=\ac>0?+:-}
\text{s3d=\ac>0?+:-}
\text{s3m=\ac>0?-:+}
#endif

  \integer{ns3g=position(\s3g,\lstsgn)}
  \integer{ns3m=position(\s3m,\lstsgn)}
  \integer{ns3d=position(\s3d,\lstsgn)}
  \text{z3g=\nv1 < \nv2? 0:||}
  \text{z3d=\nv1 < \nv2? ||:0}
  \integer{nz1g=position(\z1g,\lstz)}
  \integer{nz2g=position(\z2g,\lstz)}
  \integer{nz3g=position(\z3g,\lstz)}
  \integer{nz1d=position(\z1d,\lstz)}
  \integer{nz2d=position(\z2d,\lstz)}
  \integer{nz3d=position(\z3d,\lstz)}
\text{ligne=<tr><th>Quotient</th><td>&nbsp;</td><td>\s3g</td><td>\z3g</td><td>\s3m</td><td>\z3d</td><td>\s3d</td><td>&nbsp;</td></tr></table>}
  \text{tableau=\tableau \ligne}


%%%% détermination de la réponse
#if defined TARGET_ineqalghyper4
\if{\k=1}{
   \if{\e>0}{
    \if{\sensineq=1}{
       \if{(\nv1>\nv2) or (\strictineq=1)}{
          \text{grep=\crocd,\infg,\ptvirg,\v2,\crocg}
         }{
          \text{grep=\crocd,\infg,\ptvirg,\v1,\crocg,\union,\crocd,\v1,\ptvirg,\v2,\crocg}
         }
      }{
       \if{(\nv1<\nv2) or (\strictineq=1)}{
          \text{grep=\crocd,\v2,\ptvirg,\infd,\crocg}
         }{
          \text{grep=\crocd,\v2,\ptvirg,\v1,\crocg,\union,\crocd,\v1,\ptvirg,\infd,\crocg}
         }
      }
    }{
    \if{\sensineq=2}{
       \if{(\nv1>\nv2) or (\strictineq=1)}{
     \text{grep=\crocd,\infg,\ptvirg,\v2,\crocg}
         }{
     \text{grep=\crocd,\infg,\ptvirg,\v1,\crocg,\union,\crocd,\v1,\ptvirg,\v2,\crocg}
         }
      }{
       \if{(\nv1<\nv2) or (\strictineq=1)}{
     \text{grep=\crocd,\v2,\ptvirg,\infd,\crocg}
         }{
     \text{grep=\crocd,\v2,\ptvirg,\v1,\crocg,\union,\crocd,\v1,\ptvirg,\infd,\crocg}
         }
      }
    }
 }{
   \if{\a>0}{
    \if{\sensineq=1}{
       \if{\nv2>\nv1}{
     \text{grep=\crocd,\infg,\ptvirg,\v1,\crochd}
         }{
     \text{grep=\crocd,\infg,\ptvirg,\v2,\crocg,\union,\crocd,\v2,\ptvirg,\v1,\crochd}
         }
      }{
       \if{\nv2<\nv1}{
     \text{grep=\crochg,\v1,\ptvirg,\infd,\crocg}
         }{
     \text{grep=\crochg,\v1,\ptvirg,\v2,\crocg,\union,\crocd,\v2,\ptvirg,\infd,\crocg}
         }
      }
    }{
    \if{\sensineq=2}{
       \if{\nv2>\nv1}{
     \text{grep=\crocd,\infg,\ptvirg,\v1,\crochd}
         }{
     \text{grep=\crocd,\infg,\ptvirg,\v2,\crocg,\union,\crocd,\v2,\ptvirg,\v1,\crochd}
         }
      }{
       \if{\nv2<\nv1}{
     \text{grep=\crochg,\v1,\ptvirg,\infd,\crocg}
         }{
     \text{grep=\crochg,\v1,\ptvirg,\v2,\crocg,\union,\crocd,\v2,\ptvirg,\infd,\crocg}
         }
      }
    }
  }
#else
%%%%liste des réponses possibles
    \text{grep1=\crocg \tsing1 \ptvirg \tsing2 \crocd}
    \text{grep2=\crocd \tsing1 \ptvirg \tsing2 \crocg}
    \text{grep3=\crocg \tsing1 \ptvirg \tsing2 \crocg}
    \text{grep4=\crocd \tsing1 \ptvirg \tsing2 \crocd}
    \text{grep5=\crocd \infg \ptvirg \tsing1 \crocd \union \crocd \tsing2 \ptvirg \infd \crocg}
    \text{grep6=\crocd \infg \ptvirg \tsing1 \crocg \union \crocg \tsing2 \ptvirg \infd \crocg}
    \text{grep7=\crocd \infg \ptvirg \tsing1 \crocg \union \crocd \tsing2 \ptvirg \infd \crocg}
    \text{grep8=\crocd \infg \ptvirg \tsing1 \crocd \union \crocg \tsing2 \ptvirg \infd \crocg}
  \if{(\sensineq=1 and \ac>0) or (\sensineq=2 and \ac<0)}{
     \if{\nv1<\nv2}{
       \text{grep=\crochg,\tsing1,\ptvirg,\tsing2,\crocg}
       \integer{chrep=\strictineq=1?3:2}
       }{
       \text{grep=\crocd,\tsing1,\ptvirg,\tsing2,\crochd}
       \integer{chrep=\strictineq=1?4:2}
       }
    }{
     \if{\nv1<\nv2}{
        \text{grep=\crocd,\infg,\ptvirg,\tsing1,\crochd,\union,\crocd,\tsing2,\ptvirg,\infd,\crocg}
        \integer{chrep=\strictineq=1?5:7}
       }{
        \text{grep=\crocd,\infg,\ptvirg,\tsing1,\crocg,\union,\crochg,\tsing2,\ptvirg,\infd,\crocg}
        \integer{chrep=\strictineq=1?6:7}
       }
    }
#endif
\text{lstch=\grep1,\grep2,\grep3,\grep4,\grep5,\grep6, \grep7, \grep8}

\text{clicList=
\crocg,\ptvirg,\crocd,\union,\inter,\infg,\infd,\empt,\bracg,\bracd,\permut}
%%%% taille des symboles et des champs à remplir par clic LxHxnb %%%%
\text{size=50x40x18}
\statement{
  Pour résoudre dans \(\ \RR\) l'inéquation
<div class="wimscenter">\(\equat\).</div>
\tintro

#if defined TARGET_ineqalghyper1
\tableau
#else
<table class="tab_var">
 <tr>
  <th style="width:20%">\(x)</th>
  <td style="width:10%">\infg</td>
  <td style="width:20%">&nbsp;</td>
  <td style="width:10%">\embed{reply18,4}</td>
  <td style="width:20%">&nbsp;</td>
  <td style="width:10%">\embed{reply2,4}</td>
  <td style="width:20%">&nbsp;</td>
  <td style="width:10%"> \infd </td>
</tr>

#if defined TARGET_ineqalghyper5
<tr>
  <th>\embed{reply19,8}</th>
  <td>&nbsp;</td>
  <td>\embed{reply3}</td>
  <td>\embed{reply4}</td>
  <td>\embed{reply5}</td>
  <td>\embed{reply6}</td>
  <td>\embed{reply7}</td>
  <td>&nbsp;</td>
  </tr>
#else
<tr>
  <th>\fact1</th>
  <td>&nbsp;</td>
  <td>\embed{reply3}</td>
  <td>\embed{reply4}</td>
  <td>\embed{reply5}</td>
  <td>\embed{reply6}</td>
  <td>\embed{reply7}</td>
  <td>&nbsp;</td>
</tr>
#endif
<tr>
  <th>\fact2</th>
  <td>&nbsp;</td>
  <td>\embed{reply8}</td>
  <td>\embed{reply9}</td>
  <td>\embed{reply10}</td>
  <td>\embed{reply11}</td>
  <td>\embed{reply12}</td>
  <td>&nbsp;</td></tr>
<tr>
 <th>Quotient</th>
 <td>&nbsp;</td>
 <td>\embed{reply13}</td>
 <td>\embed{reply14}</td>
 <td>\embed{reply15}</td>
 <td>\embed{reply16}</td>
 <td>\embed{reply17}</td>
 <td>&nbsp;</td>
</tr>
</table>
#endif

<div>
  \tverb l'ensemble solution de l'inéquation :
</div>

#if (defined TARGET_ineqalghyper1  || defined TARGET_ineqalghyper2 )
\(S=)
<ul><li>\embed{reply1,1}</li>
<li>\embed{reply1,2}</li>
<li>\embed{reply1,3}</li>
<li>\embed{reply1,4}</li>
<li>\embed{reply1,5}</li>
<li>\embed{reply1,6}</li>
<li>\embed{reply1,7}</li>
<li>\embed{reply1,8}</li>
</ul>
#else
<div class="wimscenter"> \(S=)\embed{reply1,\size}</div>
#endif
}

#if (defined TARGET_ineqalghyper1  || defined TARGET_ineqalghyper2 )
\answer{}{\chrep1;\lstch}{type=radio}
\text{rep=wims(replace internal ; by &#59; in \reply1)}
\integer{posch=position(\rep,\lstch)}
\condition{\posch=\chrep}
\feedback{\posch<>\chrep}{La bonne réponse est \lstch[\chrep]}
#else
\answer{}{\grep;\clicList}{type=clickfill}
#endif

#if (defined TARGET_ineqalghyper2  || defined TARGET_ineqalghyper3  || defined TARGET_ineqalghyper4  || defined TARGET_ineqalghyper5 )
\answer{valmax}{\valmax}{type=numeric}
\answer{}{\ns1g;+,-}{type=menu}
\answer{}{\nz1g;0,|,||}{type=menu}
\answer{}{\ns1m;+,-}{type=menu}
\answer{}{\nz1d;0,|,||}{type=menu}
\answer{}{\ns1d;+,-}{type=menu}
\answer{}{\ns2g;+,-}{type=menu}
\answer{}{\nz2g;0,|,||}{type=menu}
\answer{}{\ns2m;+,-}{type=menu}
\answer{}{\nz2d;0,|,||}{type=menu}
\answer{}{\ns2d;+,-}{type=menu}
\answer{}{\ns3g;+,-}{type=menu}
\answer{}{\nz3g;0,|,||}{type=menu}
\answer{}{\ns3m;+,-}{type=menu}
\answer{}{\nz3d;0,|,||}{type=menu}
\answer{}{\ns3d;+,-}{type=menu}
\answer{valmin}{\valmin}{type=numeric}
#endif
#if defined TARGET_ineqalghyper5
\answer{facteur}{\vfact1}{type=algexp}
#endif
