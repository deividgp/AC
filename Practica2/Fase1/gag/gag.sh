#Ammp
sim-outorder -redir:sim gagAmmp -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../ammp/exe/ammp.exe ammp < ../ammp/data/ref/ammp.in > ./ammp.out 2> ./ammp.err
#Gap
sim-outorder -redir:sim gagGap -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../gap/exe/gap.exe -l ./ -q -m 192M < ../gap/data/ref/ref.in > ./gap.out 2> ./gap.err
#Bzip2
sim-outorder -redir:sim gagBzip2 -fastfwd 50000000 -max:inst 65000000 -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../bzip2/exe/bzip2.exe ../bzip2/data/ref/input.source 58 > ./bzip2.out 2> ./bzip2.err
#Vpr
sim-outorder -redir:sim gagVpr -fastfwd 50000000 -max:inst 65000000  -bpred 2lev -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../vpr/exe/vpr.exe ../vpr/data/ref/net.in ../vpr/data/ref/arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2 > vpr_log.out 2> vpr_log.err
#Art                                                                                                                                
sim-outorder -redir:sim gagArt -fastfwd 50000000 -max:inst 65000000 -bpred 2lev -bpred:2lev 1 8 3 0 -mem:width 32 -mem:lat 300 2 ../art/exe/art.exe -scanfile c756hel.in -trainfile1 ../art/data/ref/a10.img -stride 2 -startx 134 -starty 220 -endx 139 -endy 225 -objects 1 > ./art.out 2> ./art.err