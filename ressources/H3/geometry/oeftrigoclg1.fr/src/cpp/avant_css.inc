%%% css commune autre que css euler et css particuliere %%%
\css{
<style>

.indication{
  font-weight:bold;color:#009999;
  margin-bottom: 0.8em;
  margin-top: 0.8em;
}
.quest{
  color:blue;
  font-weight:bold;
  margin:0;
}

#if defined TARGET_01CliquerHypotenuse || defined TARGET_02CliquerAdjacent || defined TARGET_03CliquerOppose ||defined TARGET_06AssocVocTrigo
.ui-accordion .ui-accordion-content{
  padding-left:1em;
  padding-right:1em;
}
#endif

#if defined TARGET_04ReconTrRect1
.wims_button_help{
  float:right;
}
#endif 

#if defined TARGET_05ReconTrRect3 

#endif
#if defined TARGET_06AssocVocTrigo

table.tabSol td {
  border:solid 1px;
  padding:0.3em; 
  }
table.tabSol th {
  border:solid 1px; 
  background-color:#CEE3F6; 
  color:#2609AB;
  }
table.tabSol th.vide {
  border: none;
  background: none;
  }
table.tabSol tr:nth-child(2n+3) {
  background-color:#EFF5FB;
  }
#endif

#if defined TARGET_10DeuxMesures || defined TARGET_11LigneTrigoUniteEtape || defined TARGET_12LigneTrigoUnite

.calculator{
  font-weight: bold;
  border: 2px solid grey;
  border-radius: 10px;
  padding: 0.15em;
  background-color: lightgrey;
}
.pad_cond{
  padding-left:5em;
}
#endif
</style>
}
