\text{good=wims(nonempty items \good)}
\text{bad=wims(nonempty items \bad)}
\integer{badcnt=random(1,1,2,2,3)}
\integer{goodcnt=4-\badcnt}
\text{bads=item(1..\badcnt,1,1,1,1,1,1)}
\text{gb=item(1..4,\bads,0,0,0,0,0,0)}
\text{bads=item(1..\badcnt,\bad)}
\text{goods=item(1..4-\badcnt,\good)}
\text{order=shuffle(4)}
\text{list=item(\order,\bads,\goods)}
\text{gb=item(\order,\gb)}
\text{bad=wims(positionof item 1 in \gb)}
\text{good=wims(positionof item 0 in \gb)}
\text{l1=item(1,\list)}
\text{l1=\(texmath(\l1)\)}
\text{l2=item(2,\list)}
\text{l2=\(texmath(\l2)\)}
\text{l3=item(3,\list)}
\text{l3=\(texmath(\l3)\)}
\text{l4=item(4,\list)}
\text{l4=\(texmath(\l4)\)}
\if{random(1,2) = 1}{
  \text{ask=\name_ask[2]}
  \text{cond=\name_cond[2]}
  \text{ans=\bad}
}{
  \text{ask=\name_ask[1]}
  \text{cond=\name_cond[1]}
  \text{ans=\good}
}

