targets=corrcodename corrcodecap corrnamecap corrdepreg corrregcap corrcodereg corrcapreg

#include "header.inc"

#if #TARGET (corrcodename)
 \title{Correspondance code/département}
# include "frdept.inc"
 \text{name1=un code}
 \text{name2=le nom du département}
 \integer{c1=1}
 \integer{c2=2}
#endif

#if #TARGET (corrcodecap)
 \title{Correspondance code/chef-lieu}
# include "frdept.inc"
 \text{name1=un code}
 \text{name2=le chef-lieu du département}
 \integer{c1=1}
 \integer{c2=3}
#endif

#if #TARGET (corrcodereg)
 \title{Correspondance code/région}
# include "frdept.inc"
 \text{name1=un code}
 \text{name2=la région où appartient le département du code}
 \integer{c1=1}
 \integer{c2=4}
#endif

#if #TARGET (corrnamecap)
 \title{Correspondance département/chef-lieu}
# include "frdept.inc"
 \text{name1=un département}
 \text{name2=le chef-lieu}
 \integer{c1=2}
 \integer{c2=3}
#endif

#if #TARGET (corrdepreg)
 \title{Correspondance département/région}
# include "frdept.inc"
 \text{name1=un département}
 \text{name2=la région où il appartient}
 \integer{c1=2}
 \integer{c2=4}
#endif

#if #TARGET (corrcapreg)
 \title{Correspondance ville/région}
# include "frdept.inc"
 \text{name1=une ville}
 \text{name2=la région où il appartient}
 \integer{c1=3}
 \integer{c2=4}
#endif

#if #TARGET (corrregcap)
 \title{Correspondance région/chef-lieu}
# include "frreg.inc"
 \text{name1=une région}
 \text{name2=son chef-lieu}
 \integer{c1=4}
 \integer{c2=5}
#endif

\integer{n=rows(\data)}
\text{sh=item(1..6,shuffle(\n))}
\text{pick=row(\sh,\data)}
\text{lefts=column(\c1,\pick)}
\if{\c1=1}{
 \text{lefts=wims(replace internal , by </div>,<div class="wims_center"> in <div class="wims_center">\lefts</div>)
 }
}
\integer{leftw=item(\c1,30,250,250,250,250)}
\integer{rightw=item(\c2,30,250,250,250,250)}
\text{rights=column(\c2,\pick)}
\text{ans=\lefts ; \rights}

\statement{Etablissez une correspondance correcte, en cliquant sur \name1
puis sur \name2.
<div class="wimscenter">
\embed{reply 1,30 \leftw \rightw}</div>
}

\answer{La correspondance}{\ans}{type=correspond}

