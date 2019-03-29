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

;;; FILE TYPE: SAME IN, SAME OUT ;;;
sr = 44100
ksmps = 16
nchnls = 8
0dbfs  = 1

;;; SURROUND SOUND: VECTOR-BASED AMPLITUDE PANNING / ROOM CORRECTION ;;;
idim	= 2			; 2D not 3D																								; careful these are global
ilsnum	= 5			; 8 ch (2 dummies)

vbaplsinit idim, ilsnum,	288,	72,		0,		0,		216,	144		; initialize speaker angles for vector based amplitude panning
;							        ff-r,	ff-l,	cb-r,	cb-l,	bs-r,	bs-l,	;;ss-l,	ss-r;;	; these angles are "where are YOUR speakers"
																																					; works for my soundcard anyway, dont use bs-out

;;; ORCHESTRA ;;;
instr 1																									; world instrument
ifn = p4                                                ; sound source function table number, created using GEN01
kamp = 1                                                ; amplitude control
kpitch = 1	                     			    ; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 26.48                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
kazim line 0, 10.0, 359                                ; 360 deg in one 8 * 4 beats 145bpm  

a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim;, 0, 1        ;change azimuth of soundsource
          outo a1,a2,a3,a4,a5,a6,a7,a8
endin

</CsInstruments>
<CsScore>
;;; F TABLE CONTAINS WAVEFORMS ;;;
f 1 0 0  1 "mdrum_c_loop.wav"					0 0 0							;makes fn table from gen01 in i-statement in score

;;; I TABLE CONTAINS ARRANGEMENT DATA ;;;
i 1 0 84600   1																					; p4 selects sample
e																												; end
</CsScore>
</CsoundSynthesizer>
