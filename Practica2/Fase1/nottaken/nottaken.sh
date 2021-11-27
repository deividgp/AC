#Ammp
sim-bpred -redir:sim nottakenAmmp -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../ammp/exe/ammp.exe ammp < ../ammp/data/ref/ammp.in > ./ammp.out 2> ./ammp.err
#Gap
sim-bpred -redir:sim nottakenGap -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../gap/exe/gap.exe -l ./ -q -m 192M < ../gap/data/ref/ref.in > ./gap.out 2> ./gap.err
#Bzip2
sim-bpred -redir:sim nottakenBzip2 -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../bzip2/exe/bzip2.exe ../bzip2/data/ref/input.source 58 > ./bzip2.out 2> ./bzip2.err
#Vpr
sim-bpred -redir:sim nottakenVpr -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../vpr/exe/vpr.exe ../vpr/data/ref/net.in ../vpr/data/ref/arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2 > vpr_log.out 2> vpr_log.err
#Art
sim-bpred -redir:sim nottakenArt -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../art/exe/art.exe -scanfile ../art/data/ref/c756hel.in -trainfile1 ../art/data/ref/a10.img -stride 2 -startx 134 -starty 220 -endx 139 -endy 225 -objects 1 > ./art.out 2> ./art.err