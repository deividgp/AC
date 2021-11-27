#Applu
sim-bpred -redir:sim nottakenApplu -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../../applu/exe/applu.exe < ../../../applu/data/ref/applu.in
#Crafty
sim-bpred -redir:sim nottakenCrafty -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../../crafty/exe/crafty.exe < ../../../crafty/data/ref/crafty.in
#Mesa
sim-bpred -redir:sim nottakenMesa -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../../mesa/exe/mesa.exe -frames 1000 -meshfile ../../../mesa/data/ref/mesa.in -ppmfile ../../../mesa/data/ref/mesa.ppm
#Vpr
sim-bpred -redir:sim nottakenVpr -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../../vpr/exe/vpr.exe ../../../vpr/data/ref/net.in ../../../vpr/data/ref/arch.in place.out dum.out -nodisp -place_only -init_t 5 -exit_t 0.005 -alpha_t 0.9412 -inner_num 2
#Vortex
sim-bpred -redir:sim nottakenVortex -fastfwd 50000000 -max:inst 65000000 -bpred nottaken ../../../vortex/exe/vortex.exe ../../../vortex/data/ref/lendian1.raw