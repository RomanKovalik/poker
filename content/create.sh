#!/bin/bash

NUM_OFFSET=+11+15
NUM_OFFSET_FLIP=+37+65
SUIT_OFFSET=+16+32

for n in nums/*.png; do
    for s in bsuits/*.png; do
        convert card.png \
        -page $NUM_OFFSET $n \
        -page $NUM_OFFSET_FLIP \( $n -flip -flop \) \
        -page $SUIT_OFFSET $s \
        -background none \
        -flatten "out/$(basename ${n%.*})_$(basename ${s%.*}).png"
    done
done

for n in nums/*.png; do
    for s in rsuits/*.png; do
        convert card.png \
        -page $NUM_OFFSET \( $n -fuzz 0% -fill "#ff0000" -opaque "#000000" \) \
        -page $NUM_OFFSET_FLIP \( $n -fuzz 0% -fill "#ff0000" -opaque "#000000" -flip -flop \) \
        -page $SUIT_OFFSET $s \
        -background none \
        -flatten "out/$(basename ${n%.*})_$(basename ${s%.*}).png"
    done
done

T_NUM_OFFSET=+2-1
T_SUIT_OFFSET=+2+11

for n in t_nums/*.png; do
    for s in t_bsuits/*.png; do
        convert t_card.png \
        -page $T_NUM_OFFSET $n \
        -page $T_SUIT_OFFSET $s \
        -background none \
        -flatten "out/$(basename ${n%.*})_$(basename ${s%.*})_t.png"
    done
done

for n in t_nums/*.png; do
    for s in t_rsuits/*.png; do
        convert t_card.png \
        -page $T_NUM_OFFSET \( $n -fuzz 0% -fill "#ff0000" -opaque "#000000" \) \
        -page $T_SUIT_OFFSET $s \
        -background none \
        -flatten "out/$(basename ${n%.*})_$(basename ${s%.*})_t.png"
    done
done
