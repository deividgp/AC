#Ammp
sim-bpred -redir:sim nottakenAmmp -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../exe/ammp.exe ammp < ammp.in > ammp.out 2> ammp.err
#Gap
sim-bpred -redir:sim nottakenGap -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../exe/gap.exe -l ./ -q -m 192M < ref.in > ref.out 2> ref.err
#Bzip2
sim-bpred -redir:sim nottakenBzip2 -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../exe/bzip2.exe input.source 58 > input.source.out 2> input.source.err
#Vpr
sim-bpred -redir:sim nottakenVpr -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../exe/vpr.exe net.in arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2 > place_log.out 2> place_log.err
#Art
sim-bpred -redir:sim nottakenArt -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../exe/art.exe -scanfile c756hel.in -trainfile1 a10.img -stride 2 -startx 134 -starty 220 -endx 139 -endy 225 -objects 1 > test.out 2> test.err