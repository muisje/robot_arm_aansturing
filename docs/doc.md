---
title: "Robot arm controller"
output: pdf_document
author: 
- David Hendrik Nusselder
- Maurits Muijsert
date: 17-04-2019
---

\centering

![AL5D robot arm](picture.jpg){width=50%}

\raggedright
\clearpage
\tableofcontents
\clearpage

# Robot arm controller

##inleiding

In het volgende document wordt de documentatie beschreven van de aansturings interface van de LynxMotion AL5D robot arm. Er wordt in dit document beschreven hoe het systeem in elkaar zit met behulp van een Use case diagram, Component, Behavioral state machine, Protocol state machine , Timings diagram en een Sequence diagram. In dit document zullen we ook nader toelichting geven over de bruikbaarheid van deze arm, hierbij kijken we naar de gestelde eisen in de opdracht.

\clearpage

## Use Cases

In het Use case diagram worden alle eigenschappen beschreven waarmee de gebruiker kan interacteren. In dit diagram hebben we twee systemen beschreven die elk een applicatie representeren de onderlingen contacten gaan met behulp van Ros Messages, dit kan via 3 ontvanger nodes. De eerste node is voor de emergency stop, de tweede node voor een preset position en de derde voor een custom  position.

![UCD](http://www.plantuml.com/plantuml/png/3SB1IWCn403Gkr-X1uzkm2YA8BAei7ihzDAUbjdiaAH99jl935lwzUtZFJn5SbaNLCwFGMHjNyOmR9sF4dJMXkmg2P9qhXPJDBOJ6gvpbGcuJ03KH3cIDmMQ89ibWcSepQXRkZK3YPRy8pKXVVU0hnzNdzx2kFkrXqlGRHYKq1wJtO_n9RLtby__drl_RF_kRm00)

\clearpage

## Componenten

In het Component diagram beschrijven we de verschillende componenten in het systeem, hierbij wordt onderscheid gemaakt tussen de verschillende drivers en de subsystemen daarvan. De “getCurrenPosition()” in de High level driver is gemaakt omdat de robotarm zelf geen feedback verzorgt. Deze functie maakt een schatting van de verwachte positie als de robotarm geen problemen ondervindt. Deze functionaliteit is essentieel om er achter te komen of de arm klaar is met zijn taak, hierdoor kan de Queue geïmplementeerd worden.

![Component diagram](http://www.plantuml.com/plantuml/png/5SrFIuP04CVn-_Cgwj3LXQA485BwSqcAA0DFCgw3RhixQpEp2htwH-5t_7tuLgB0ccCuNJgo8O-OELpCgelS6yEm5PFJEGzPa6qYHTB2fcXYTlABXjEGj0UEFG29PdOqcGYYo6PqC354CVj_INJ89G0TiKTD7kcX1hmkI_hvAb-_iRrxyLtxr3GV-F_vlgxhc_ToQyDVvxVwwkPvtwb26dT-1W00)

\clearpage

## Behavioral state machine

In het Behavioral state machine diagram hebben we een abstracte weergaven van de werkelijkheid beschreven. Bij dit gedrag hebben we onderscheid gemaakt tussen “MOVING” en “STAND_BY”. Het systeem zal terug keren naar “STAND_BY” als hij zijn positie heeft bereikt en of de Emergency stop wordt geactiveerd. Pas als het systeem in “STAND_BY” stand staat kan hij een nieuwe opdracht uitvoeren uit de Queue.

![Behavioral state machine](http://www.plantuml.com/plantuml/png/5SrDIyD0483XUt-57ZoQXOGG4CG6Fmu5GT5xc6p6xDhPsJWV5l-zBRpNbsUl1c9UQ7UTEP8lw49NoMpJkn04JisQBVdiYX8h6x8riPPGFEit1gbpjGcaJ02ivf9v3GNKKCAIOHKe6cPCy9kh07qO6Bv2J9cnsGZu8ZzOFIBVZu3jyDUFNy_J-z3rRTiztl8XRRGSFWbzE6eVwUVjvJJUT4_dTdlavRp_0m00)

\clearpage

## Protocol state machine

In het Protocol state machine diagram hieronder wordt beschreven wat de pre en postcondities zijn van elke state verandering van de applicatie. Bij elke transitie wordt er ook beschreven wat de actie is die de transitie activeert. De beiden applicaties hebben onderling contact met de ros Action messages, de gebruikte topic zijn “pose_action”, “costum_pose_action” en "emergency”. De Robotarm controller zal naar de gepaste note een bericht sturen met de gebruikers voorkeur, dit gebeurt in “Send_message”.

![Protocol state machine](http://www.plantuml.com/plantuml/png/9OrDIyD0443l_HLwy6XM52a8Oei5UqYbMEd1IvbkXksQtPbaFiZVDr9ufmUFjr83CQzbSPif5k_GfTnSp0Pz2K5WQbAsYvzTKIAJ8LaJkORgMNyn29_PJY3r141gBfbIgA264heCIQ1gs0iRHou70yFDrJP30Vh_lXdtIAzhmCVbSdVO7jjf_tFS-VOXVO_lQX_jFVQjzleSo_ZrEQtldZOpYnLID-T_)

\clearpage

## Timing gripper

..

![Timing diagram gripper](http://www.plantuml.com/plantuml/png/5OrDImCn443l_HLwyEX65544iGkYBXIyI3qkqsHCqoQJx7om-_FTmZizUBojAB1QoPlhH3vRGEDyTLHjyk8Smzp5f4Sxc23xIegadQ_55KjoGiVrK7K4BYC0YHedYgw0AB8B2I934QUfhFgJKsl8NSj0b-6RrZFIQmzu_tIh7pBOz_vd3Bjzh7U_Ip_yJL_BwNbtbaUVfq7c_kRXVMMpHGfh_Wy0)

\clearpage

## Init

Het sequence diagram is gemaakt ter ondersteuning voor het Timing diagram. Hierbij gaan we bij dit diagram dieper in op de verschillende functie aanroepingen en de Alt/if eisen. Daarnaast beschrijven we met behulp van notities de functionelen eisen van elke vrijheidsgraden. 

![Sequence diagram init](http://www.plantuml.com/plantuml/png/5SrDImCn483XUt-57hnkm0yAWjY283dq8AAKNi8qEwHnaydkV13qrxk5z_hox4I1rMhPt6QAnKOqBZSNrLcUdMFeGyfwiRC9ScoaI3h4LbsrB3_ek9sR1k0Q04ZKE5Do5KIHtPWXCLHnWeiXHVIKTPWBqDLxrJOXlUm1xxVRhu_Qq-bq-En_nzz7FV9x-FRcS_2JFCMo77pVtpsyhMrsIEEw_mC0)
