<CsoundSynthesizer>
<CsOptions>
; combined gen01.csd and ../csound-vbaplsinit/test.csd 
; Select audio/midi flags here according to platform 
-odac     ;;;realtime audio out 
;-iadc    ;;;uncomment -iadc if realtime audio input is needed too 
; For Non-realtime ouput leave only the line below: 
; -o gen01.wav -W ;;; for file output any platform 
</CsOptions>
<CsInstruments>
sr = 44100 
ksmps = 16
nchnls = 8 
0dbfs  = 1
vbaplsinit 2, 8, 0, 72, 144, 216, 288, 0, 0, 0		; initialize speaker angles for vector based amplitude panning

instr 1
ifn = p4                                                ; sound source function table number, created using GEN01
kamp = 1                                                ; amplitude control
kpitch = 1                                              ; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 32.415                                       ; loop end point (in seconds)
kcrossfade = 0.05                                       ; 0.05 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
kazim=180
a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource
          outo a1,a2,a3,a4,a5,a6,a7,a8
endin

instr 2
ifn = p4						; sound source function table number, created using GEN01
kamp = 1                                                ; amplitude control
kpitch = 1                                              ; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 32.415                                       ; loop end point (in seconds)
kcrossfade = 0.05                                       ; 0.05 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
kazim=180
a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource
	  outo a1,a2,a3,a4,a5,a6,a7,a8
endin     

instr 3
ifn = p4						; sound source function table number, created using GEN01
ibas = 1						; for loscil(removed)
kamp = 1						; amplitude control
kpitch = 1						; pitch control
kloopstart = 0						; loop start point (although krate, updates only once per loop)
kloopend = 32.415					; loop end point (in seconds)
kcrossfade = 0.05					; 0.05 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
;asig loscil 1, 1, ifn, ibas				; (removed)
kazim=270
a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource
	  outo a1,a2,a3,a4,a5,a6,a7,a8
endin
</CsInstruments>
<CsScore>
f 1 0 0  1 "drum_c_loop_32.wav"	0 0 0			;non-deferred sound   ;makes fn table from gen01 in i-statement in score
f 2 0 0  1 "mbass_c_loop.wav"	0 0 0			;& deferred sounds in 
f 3 0 0  1 "macc_c_loop.wav"	0 0 0			;different formats					
i 1 0 84600   1
i 2 0 84600   2	; p4 selects sample
i 3 0 84600   3
e
</CsScore>
</CsoundSynthesizer>
