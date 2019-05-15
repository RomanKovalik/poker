#!/usr/bin/env fish

set NUM_OFFSET +11+15
set NUM_OFFSET_FLIP +37+65
set SUIT_OFFSET +16+32

for n in nums/*.png
    for s in bsuits/*.png
        convert card.png \
        -page $NUM_OFFSET $n \
        -page $NUM_OFFSET_FLIP \( $n -flip -flop \) \
        -page $SUIT_OFFSET $s \
        -background none \
        -flatten out/(basename $n .png)_(basename $s .png).png
    end
end

for n in nums/*.png
    for s in rsuits/*.png
        convert card.png \
        -page $NUM_OFFSET \( $n -fuzz 0% -fill "#ff0000" -opaque "#000000" \) \
        -page $NUM_OFFSET_FLIP \( $n -fuzz 0% -fill "#ff0000" -opaque "#000000" -flip -flop \) \
        -page $SUIT_OFFSET $s \
        -background none \
        -flatten out/(basename $n .png)_(basename $s .png).png
    end
end

set T_NUM_OFFSET +2-1
set T_SUIT_OFFSET +2+11

for n in t_nums/*.png
    for s in t_bsuits/*.png
        convert t_card.png \
        -page $T_NUM_OFFSET $n \
        -page $T_SUIT_OFFSET $s \
        -background none \
        -flatten out/(basename $n .png)_(basename $s .png)_t.png
    end
end

for n in t_nums/*.png
    for s in t_rsuits/*.png
        convert t_card.png \
        -page $T_NUM_OFFSET \( $n -fuzz 0% -fill "#ff0000" -opaque "#000000" \) \
        -page $T_SUIT_OFFSET $s \
        -background none \
        -flatten out/(basename $n .png)_(basename $s .png)_t.png
    end
end
