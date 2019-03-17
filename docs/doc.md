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

In het volgende document wordt de documentatie beschreven van de aansturing interface van de LynxMotion AL5D robotarm. Er wordt in dit document geïnformeerd hoe het systeem in elkaar zit met behulp van: een Use case diagram, Component, Behavioral state machine, Protocol state machine, Timing diagram en een Sequence diagram. In dit document zullen wij nader toelichting geven over de bruikbaarheid van deze arm, hierbij kijken we naar de gestelde eisen in de opdracht.

\clearpage

## Use Cases

In het Use case diagram worden alle eigenschappen beschreven waarmee de gebruiker kan interacteren. In dit diagram hebben we twee systemen beschreven die elk een applicatie representeren. De onderlinge contacten vinden plaats via Ros Messages, dit kan via drie ontvanger nodes. De eerste node is voor de emergency stop, de tweede node voor een preset position en de derde voor een custom position.

![UCD](http://www.plantuml.com/plantuml/png/3SB1IWCn403Gkr-X1uzkm2YA8BAei7ihzDAUbjdiaAH99jl935lwzUtZFJn5SbaNLCwFGMHjNyOmR9sF4dJMXkmg2P9qhXPJDBOJ6gvpbGcuJ03KH3cIDmMQ89ibWcSepQXRkZK3YPRy8pKXVVU0hnzNdzx2kFkrXqlGRHYKq1wJtO_n9RLtby__drl_RF_kRm00)

\clearpage

## Componenten

In het Component diagram beschrijven wij de verschillende componenten in het systeem. Hierbij wordt onderscheid gemaakt tussen de verschillende drivers en de subsystemen. De “getCurrenPosition()” in de High level driver is gemaakt, omdat de robotarm zelf geen feedback verzorgt. De functie maakt een schatting van de verwachte positie als de robotarm geen problemen ondervindt. Deze functionaliteit is essentieel om erachter te kunnen komen of de arm klaar is met zijn taak, hierdoor kan de Queue geïmplementeerd worden.

![Component diagram](http://www.plantuml.com/plantuml/png/5SrFIuP04CVn-_Cgwj3LXQA485BwSqcAA0DFCgw3RhixQpEp2htwH-5t_7tuLgB0ccCuNJgo8O-OELpCgelS6yEm5PFJEGzPa6qYHTB2fcXYTlABXjEGj0UEFG29PdOqcGYYo6PqC354CVj_INJ89G0TiKTD7kcX1hmkI_hvAb-_iRrxyLtxr3GV-F_vlgxhc_ToQyDVvxVwwkPvtwb26dT-1W00)

### robot_arm_controller

De **robot_arm_controller** package is een ROS Action client applicatie. Die publiceert een action specification. Die bestaat uit een goal, feedback en result. De mogelijke goals zijn *pose*, *custom pose* en *emergency*.

### robot_arm

De robot_arm package is een ROS action server applicatie. Die voert een action specification uit. Die reageert op *pose*, *custom pose* en *emergency*. Bij pose gaat de robot arm als het mogelijk is naar een *preset pose*. Dat houd in de robot arm naar een vooraf ingestelde positie gaat. De vooraf ingestelde posities zijn **park**, **ready** en **straight_up**. Park is de positie waarin de robot begint.

#### High Level Driver

De **High Level Driver** bestaat uit twee onderdelen. Namelijk het afhandelen van goals (met *MessageHandler*) en het aansturen van de **Low Level Driver** (met *AL5D*). AL5D bied de volgende functionaliteiten aan:

* **isAtDestination** : Geeft aan of de arm op de positie van de huidige instructie.
* **stopAllMotorFunctions** : Zorgt ervoor dat all servo's stoppen met bewegen. Dit betekent dat de robot arm zo snel mogelijk stil staat en dus niet meer beweegt.
* **getCurrentPosition** : Geeft de huidige positie terug van de AL5D robot arm waarin die zich op dat moment bevindt.
* **goToPosition** : Zorgt ervoor dat de AL5D robot arm naar een gespeficeerde positie gaat. Positie in graden kan voor elke gewricht en optioneel tijd is te specificeren. De gespecificeerde positie moet binnen de gespecificeerde range liggen van de gewrichten. Als dat niet zo is beweegt de robot arm niet en wordt dit terug gekoppeld dat de opgeven positie niet mogelijk is.

#### Low Level Driver

De **Low Level Driver** handelt communicatie af met de servo controller SCC32U van de AL5D robot arm. De driver bied de volgende functionaliteit aan door middel van commando's sturen over serial naar het servo controller bord:

* **move** : Stuurt een commando om een servo aan te sturen. Hoek in graden, optionele snelheid in ms en optionele tijd in ms kan gespecificeerd worden. Bij het niet speficeren van snelheid of tijd gaat de servo zo snel mogelijk naar de opgeven positie.
* **setPositionOffset**: Stuurt een commando naar het servo controller bord aan om de offset van een servo aan te passen. Dit gaat doormiddel van een pulse breedte afwijking wat kan liggen tussen -100 en 100 uS. Dit staat ongeveer gelijk aan 15 graden.

\clearpage

## Behavioral state machine

In het Behavioral state machine diagram hebben we een abstracte weergaven van de werkelijkheid beschreven. Bij dit gedrag hebben we onderscheid gemaakt tussen “MOVING” en “STAND_BY”. Het systeem zal terug keren naar “STAND_BY” als hij zijn positie heeft bereikt en of de Emergency stop wordt geactiveerd. Pas als het systeem in “STAND_BY” stand staat, kan hij een nieuwe opdracht uitvoeren uit de Queue.

![Behavioral state machine](http://www.plantuml.com/plantuml/png/5SrDIyD0483XUt-57ZoQXOGG4CG6Fmu5GT5xc6p6xDhPsJWV5l-zBRpNbsUl1c9UQ7UTEP8lw49NoMpJkn04JisQBVdiYX8h6x8riPPGFEit1gbpjGcaJ02ivf9v3GNKKCAIOHKe6cPCy9kh07qO6Bv2J9cnsGZu8ZzOFIBVZu3jyDUFNy_J-z3rRTiztl8XRRGSFWbzE6eVwUVjvJJUT4_dTdlavRp_0m00)

\clearpage

## Protocol state machine

In het Protocol state machine diagram hieronder wordt beschreven wat de pre- en postcondities zijn van elke state verandering van de applicatie. Bij elke transitie beschrijven wij wat de actie is die de transitie activeert. Beiden applicaties hebben onderling contact met de ros Action messages, de gebruikte topic zijn “pose action”, “costum_pose_action” en "emergency”. De Robotarm controller stuurt een bericht naar de gepaste note met de gebruikers voorkeur, dit gebeurt in “Send_message”.

![Protocol state machine](http://www.plantuml.com/plantuml/png/9OrDIyD0443l_HLwy6XM52a8Oei5UqYbMEd1IvbkXksQtPbaFiZVDr9ufmUFjr83CQzbSPif5k_GfTnSp0Pz2K5WQbAsYvzTKIAJ8LaJkORgMNyn29_PJY3r141gBfbIgA264heCIQ1gs0iRHou70yFDrJP30Vh_lXdtIAzhmCVbSdVO7jjf_tFS-VOXVO_lQX_jFVQjzleSo_ZrEQtldZOpYnLID-T_)

\clearpage

## Timing gripper

..

![Timing diagram gripper](http://www.plantuml.com/plantuml/png/5OrDImCn443l_HLwyEX65544iGkYBXIyI3qkqsHCqoQJx7om-_FTmZizUBojAB1QoPlhH3vRGEDyTLHjyk8Smzp5f4Sxc23xIegadQ_55KjoGiVrK7K4BYC0YHedYgw0AB8B2I934QUfhFgJKsl8NSj0b-6RrZFIQmzu_tIh7pBOz_vd3Bjzh7U_Ip_yJL_BwNbtbaUVfq7c_kRXVMMpHGfh_Wy0)

\clearpage

## Init

Het sequence diagram is gemaakt ter ondersteuning voor het Timing diagram. Bij dit diagram gaan wij dieper in op de verschillende functie aanroepingen en de Alt/if eisen. Daarnaast beschrijven wij met behulp van notities de functionele eisen van de vrijheidsgraden.

![Sequence diagram init](http://www.plantuml.com/plantuml/png/5SrDImCn483XUt-57hnkm0yAWjY283dq8AAKNi8qEwHnaydkV13qrxk5z_hox4I1rMhPt6QAnKOqBZSNrLcUdMFeGyfwiRC9ScoaI3h4LbsrB3_ek9sR1k0Q04ZKE5Do5KIHtPWXCLHnWeiXHVIKTPWBqDLxrJOXlUm1xxVRhu_Qq-bq-En_nzz7FV9x-FRcS_2JFCMo77pVtpsyhMrsIEEw_mC0)
