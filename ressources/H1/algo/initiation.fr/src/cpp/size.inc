\text{tailled=}
\text{tailleg=}
\text{tailleh=}
\for{m=1 to \M}{
  \text{tailled_=wims(lookup \QUEST[\m;2] in imagesize)}
  \text{tailled=wims(append item \tailled_[1] to \tailled)}
  \text{tailleg_=wims(lookup \QUEST[\m;1] in imagesize)}
  \text{tailleg=wims(append item \tailleg_[1] to \tailleg)}
  \text{tailleh=wims(append item \tailleg_[2],\tailled_[2] to \tailleh)}
}
\text{size=pari([vecmax([\tailleh]),vecmax([\tailleg]),vecmax([\tailled])])}
\text{size=wims(replace internal , by x in \size)}
