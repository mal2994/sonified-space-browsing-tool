;;; MODE 2.0 no hrtf ;;;
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
																																		; works for my soundcard anyway, make bs-out dummy channels
;;; INITIALIZE RABBIT CHANNELS ;;;
	chnset	1,		"r0distance"
	chnset	90,		"r0angle"
	chnset	1,		"r1distance"
	chnset	270,	"r1angle"
	chnset	1,		"r2distance"
	chnset	180,	"r2angle"

;;; OTHER CHANNELS ;;;
	chnset	0,		"drumackamp"														; drum acknowledge amplitude

;;; ORCHESTRA ;;;
instr 1																									; world instrument
ifn = p4                                                ; sound source function table number, created using GEN01
kamp = 1                                                ; amplitude control
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 26.48                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
					outs asig, asig
endin

instr 2																									; world instrument
ifn = p4                                                ; sound source function table number, created using GEN01
kamp = 1                                                ; amplitude control
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 26.48                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
					outs asig, asig
endin

instr 3																									; drum acknowledge instrument
ifn = p4                                                ; sound source function table number, created using GEN01
kamp chnget "drumackamp"                                ; amplitude control
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 26.48                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
					outs asig, asig
endin

instr 4																									; rabbit0 instrument
ifn = p4                                                ; sound source function table number, created using GEN01
kamp chnget "r0distance"                                ; amplitude control
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 26.48                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
kazim chnget "r0angle" ; kazim is 0-360 but we need 0-1
kazim = abs((kazim-180) / 360)
aL,aR	pan2	asig, kazim   ; sent across image
	outs	aL, aR
endin

instr 5																									; rabbit1 instrument
ifn = p4                                                ; sound source function table number, created using GEN01
kamp chnget "r1distance"                               ; amplitude control
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 26.48                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
kazim chnget "r1angle"
kazim = abs((kazim-180) / 360)
aL,aR	pan2	asig, kazim   ; sent across image
	outs	aL, aR
endin

instr 6																									; rabbit2 instrument
ifn = p4                                                ; sound source function table number, created using GEN01
kamp chnget "r2distance"                                ; amplitude control
kpitch = 1		                                			  	; pitch control
kloopstart = 0                                          ; loop start point (although krate, updates only once per loop)
kloopend = 26.48                                        ; loop end point (in seconds)
kcrossfade = 0.00                                       ; 0.00 seconds crossfade
asig flooper2 kamp, kpitch, kloopstart, kloopend, kcrossfade, ifn
kazim chnget "r2angle"
kazim = abs((kazim-180) / 360)
aL,aR	pan2	asig, kazim   ; sent across image
	outs	aL, aR
endin

</CsInstruments>
<CsScore>
;;; F TABLE CONTAINS WAVEFORMS ;;;
f 1 0 0  1 "mdrum_c_loop.wav"					0 0 0							;makes fn table from gen01 in i-statement in score
f 2 0 0  1 "mbass_c_loop.wav"					0 0 0
f 3 0 0  1 "mdrum_ack_loop_8bar.wav"	0 0 0
f 4 0 0  1 "macc_c_loop.wav"					0 0 0
f 5 0 0  1 "mpiano_c_loop.wav"				0 0 0
f 6 0 0  1 "macou_c_loop.wav"					0 0 0

;;; I TABLE CONTAINS ARRANGEMENT DATA ;;;
i 1 0 84600   1
i 2 0 84600   2																					; p4 selects sample
i 3 0 84600   3																					; if this is 60bpm, then ~1400minutes
i 4 0 84600   4																					; instr 4 plays 1400 minutes of flooper2 function table 4...
i 5 0 84600   5
i 6 0 84600   6
e																												; end
</CsScore>
</CsoundSynthesizer>
