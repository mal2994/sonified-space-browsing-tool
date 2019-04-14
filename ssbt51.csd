;;; MODE 5.1 surround 4 rabbits ;;;
<CsoundSynthesizer>
<CsOptions>
; Select audio/midi flags here according to platform
-odac -m0	;;;realtime audio out, suppress messages
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
idim	 = 2			                                              ; 2D not 3D
ilsnum = 6			                                              ; 6 channel
vbaplsinit idim, ilsnum,	288,	72,		0,		0,		216,	144		; initialize speaker angles for vector based amplitude panning
;													ff-r,	ff-l,	cb-r,	cb-l,	ss-l,	ss-r	; these angles are "where are YOUR speakers"
																															; works for my soundcard anyway

;;; INITIALIZE RABBIT CHANNELS ;;;
	chnset	0,		"r0distance"
	chnset	90,		"r0angle"
	chnset	0,		"r1distance"
	chnset	270,	"r1angle"
	chnset	0,		"r2distance"
	chnset	180,	"r2angle"
	chnset	0,		"r3distance"
	chnset	180,	"r3angle"

;;; OTHER CHANNELS ;;;
	chnset	0,		"drumackamp"														; drum acknowledge amplitude
  chnset  0,    "song"                                  ; channel
  ksong = 0                                             ; variable
  chnset  0,    "swishamp"

;;; ORCHESTRA ;;;
instr 1																									; world instrument
ksong chnget "song"
kamp = 0.2                                              ; amplitude control
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 13.24                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade

if (ksong == 0.00000) kgoto floop0                      ; pick a parameter which links to each song
if (ksong == 1.00000) kgoto floop1

floop0:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p4
  kgoto playit
floop1:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p5
  kgoto playit

playit:
					outo asig, asig, asig, asig, asig, asig, asig, asig
endin

instr 2																									; world instrument
ksong chnget "song"
kamp = 0.2                                              ; amplitude control
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 13.24                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade

if (ksong == 0.00000) kgoto floop0                      ; pick a parameter which links to each song
if (ksong == 1.00000) kgoto floop1

floop0:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p4
  kgoto playit
floop1:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p5
  kgoto playit

playit:
					outo asig, asig, asig, asig, asig, asig, asig, asig
endin

instr 3																									; drum acknowledge instrument
ksong chnget "song"
kamp chnget "drumackamp"                                ; amplitude control
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 13.24                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade

if (ksong == 0.00000) kgoto floop0                      ; pick a parameter which links to each song
if (ksong == 1.00000) kgoto floop1

floop0:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p4
  kgoto playit
floop1:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p4
  kgoto playit

playit:
					outo asig, asig, asig, asig, asig, asig, asig, asig
endin

instr 8                                                ; you got the fox instrument
kamp chnget "swishamp"                                 ; amplitude control
kpitch = 1                                              ; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 13.24                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade

  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p4

          outo asig, asig, asig, asig, asig, asig, asig, asig
endin

instr 4																									; rabbit0 instrument
ksong chnget "song"
kamp chnget "r0distance"                                ; amplitude control
kazim chnget "r0angle"
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 13.24                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade

if (ksong == 0.00000) kgoto floop0                      ; pick a parameter which links to each song
if (ksong == 1.00000) kgoto floop1

floop0:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p4
  kgoto playit
floop1:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p5
  kgoto playit

playit:
          a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource
					outo a1,a2,a3,a4,a5,a6,a7,a8
endin

instr 5																									; rabbit1 instrument
ksong chnget "song"
kamp chnget "r1distance"                                ; amplitude control
kazim chnget "r1angle"
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 13.24                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade

if (ksong == 0.00000) kgoto floop0                      ; pick a parameter which links to each song
if (ksong == 1.00000) kgoto floop1

floop0:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p4
  kgoto playit
floop1:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p5
  kgoto playit

playit:
          a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource
					outo a1,a2,a3,a4,a5,a6,a7,a8
endin

instr 6																									; rabbit2 instrument
ksong chnget "song"
kamp chnget "r2distance"                                ; amplitude control
kazim chnget "r2angle"
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 13.24                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade

if (ksong == 0.00000) kgoto floop0                      ; pick a parameter which links to each song
if (ksong == 1.00000) kgoto floop1

floop0:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p4
  kgoto playit
floop1:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p5
  kgoto playit

playit:
          a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource
					outo a1,a2,a3,a4,a5,a6,a7,a8
endin

instr 7																									; rabbit3 instrument
ksong chnget "song"
kamp chnget "r3distance"                                ; amplitude control
kazim chnget "r3angle"
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 13.24                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade

if (ksong == 0.00000) kgoto floop0                      ; pick a parameter which links to each song
if (ksong == 1.00000) kgoto floop1

floop0:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p4
  kgoto playit
floop1:
  asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, p5
  kgoto playit

playit:
          a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource
					outo a1,a2,a3,a4,a5,a6,a7,a8
endin



</CsInstruments>
<CsScore>
;;; F TABLE CONTAINS WAVEFORMS ;;;                      ; makes fn table from gen01 in i-statement in score
f 1  0 0  1 "mdrum_v_loop.wav"				0 0 0
f 2  0 0  1 "mbass_v_loop.wav"				0 0 0
f 3  0 0  1 "mdrum_ack_loop_8bar.wav"	0 0 0
f 4  0 0  1 "macc_c_loop.wav"					0 0 0
f 5  0 0  1 "mpiano_v_loop.wav"				0 0 0
f 6  0 0  1 "macou_v_loop.wav"				0 0 0
f 7  0 0  1 "mooo_v_loop.wav"					0 0 0

f 8  0 0  1 "mdrum_c_loop.wav"				0 0 0
f 9  0 0  1 "mbass_c_loop.wav"				0 0 0
f 10 0 0  1 "mdrum_ack_loop_8bar.wav"	0 0 0
f 11 0 0  1 "macc_c_loop.wav"					0 0 0
f 12 0 0  1 "mpiano_c_loop.wav"				0 0 0
f 13 0 0  1 "macou_c_loop.wav"				0 0 0
f 14 0 0  1 "mooo_c_loop.wav"					0 0 0

f 15 0 0  1 "swish.wav"               0 0 0

;;; I TABLE CONTAINS ARRANGEMENT DATA ;;;
i 1 0 84600   1   8
i 2 0 84600   2		9																			; p4 selects sample for song 0. p5 for song 1. etc.
i 3 0 84600   3		3																			; if this is 60bpm, then ~1400minutes
i 4 0 84600   4		11																		; instr 4 plays 1400 minutes of flooper2 function table 4...
i 5 0 84600   5   12
i 6 0 84600   6   13
i 7 0 84600   7   14
i 8 0 84600   15  15
e																												; end
</CsScore>
</CsoundSynthesizer>
