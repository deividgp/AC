#Ammp
sim-outorder -redir:sim gagAmmp -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../../exe/ammp.exe ammp < ammp.in > ammp.out 2> ammp.err
#Gap
sim-outorder -redir:sim gagGap -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../../exe/gap.exe -l ./ -q -m 192M < ref.in > ref.out 2> ref.err
#Bzip2
sim-outorder -redir:sim gagBzip2 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../../exe/bzip2.exe input.source 58 > input.source.out 2> input.source.err
#Vpr
sim-outorder -redir:sim gagVpr -fastfwd 50000000 -max:inst 65000000  -bpred 2lev -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../../exe/vpr.exe net.in arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2 > place_log.out 2> place_log.err
#Art
sim-outorder -redir:sim gagArt -fastfwd 50000000 -max:inst 65000000 -bpred 2lev -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../../exe/art.exe -scanfile c756hel.in -trainfile1 a10.img -stride 2 -startx 134 -starty 220 -endx 139 -endy 225 -objects 1 > test.out 2> test.err