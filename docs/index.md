# title


## afspraken

* HLD berekent positie noodstop op basis van tijd
* HLD geeft positie feedback op basis van tijd

## vragen

* Waar willen we de queu
  * instruction handler
* Hoe kunnen we de posities halen als we binnen de range of motion moeten blijven
  * per gewrichten een min en max

## todo

* [x] noodstop && feedback positie -M
* [x] range of motion beperking apendix A
* [x] meerdere robot armen posities werkend.
* [x] Servo begrenzing
* [x] integratie ros met hld robot arm
* [x] dll lld -M
* [ ] QoS
* [x] doxygen
* [ ] sequence diagram - H
* [ ] protocol state machine
* [x] use cases
* [x] component diagram
* [ ] state diagram
* [ ] timing diagram
* [ ] rosout info
  * [x] info state
  * [ ] debug event
  * [x] warning QoS
* [x] Costum pos implementeren - M

## REQ

### legenda (MoSCoW)

* **bold** = must
* *italic* = should
* regular = could or would

### Functionaliteit

* [x] **SA01**
* [x] *SA02*
* [ ] *SA03* <- timing diagram
* [x] **PO01**
* [x] *PO02*
* [x] PO03
* [x] **VE01**
* [x] *VE02*
* [x] *VE03* - deels niet haalbaar (documenteren)
* [ ] **INF01**
  * [x] code
  * [ ] protocol statemachine
* [ ] **INF02**
  * [x] code
  * [ ] protocol statamachine
* [x] INF03
* [x] EX01
* [ ] EX02
* [x] **SY01**
* [ ] *SY02*
  * [x] compenenten diagram
  * [ ] beschrijving
    * [ ] systeem
    * [ ] interfaces
    * [ ] poorten
* [ ] *SY03*
* [ ] *SY04*
  * [ ] beschrijving systeem gedrag
  * [ ] state diagram
* [x] *US01*
  * [ ] opstart instialisatie
    * [ ] sequence diagram
    * [ ] beschrijving
* [ ] **US02**
* [ ] *QS01*
* [ ] *QS02*
* [x] **IM01**
* [x] **IM02**
* [X] *IM03*
* [x] IM04
* [X] **IM05**
* [x] **IM06**
* [ ] **DE01**
* [ ] DE02