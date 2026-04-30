\text{names=}
\for{i=1..\cnt}{
  \text{famille =wims(lookup \objs[\i] in descriptif)}
  \text{famille=\famille[\champ]}
  \text{famille=wims(translate  internal | to , in \famille)}
  \text{famille=randitem(\famille)}
  cas particulier des formules
  \text{names=\champ = 4 ? wims(append item \(\famille) to \names) : wims(append item \famille to \names)}
}
\text{badnames=}
\for{i=\cnt+1 to \cnt+\redundant}{
  \text{famille=wims(lookup \objs[\i] in descriptif)}
  \text{famille=\famille[\champ]}
  \text{famille=wims(translate  internal | to , in \famille)}
  \text{famille=randitem(\famille)}
  \text{badnames=\champ = 4 ? wims(append item \(\famille) to \names) : wims(append item \famille to \names)}
 }
